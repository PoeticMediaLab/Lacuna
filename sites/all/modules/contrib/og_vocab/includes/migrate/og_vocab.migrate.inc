<?php

/**
 * @file
 * Migrate plugin to populate the OG vocabulary field by the term
 * references.
 */

class OgVocabMigrate extends DynamicMigration {

  /**
   * Hold the field names that
   */
  public $fieldNames;

  /**
   * The bundle name.
   */
  private $bundle;

  public function __construct(array $arguments) {
    $this->arguments = $arguments;
    parent::__construct();
    $this->bundle = $bundle = $arguments['bundle'];

    $this->description = t('Populate the OG vocabulary field by the term references.');

    // Indicate we're updating existing data.
    $this->systemOfRecord = Migration::DESTINATION;

    $this->fieldNames = $this->getTaxonomyFields();

    $query = db_select('node', 'n')
      ->fields('n')
      ->condition('n.type', $bundle)
      ->orderBy('n.nid');

    if (empty($this->fieldNames)) {
      // Falsify the query.
      $query->condition('n.nid', 0, '=');
    }

    $this->query = $query;

    $key = array(
      'nid' => array(
        'type' => 'int',
        'not null' => TRUE,
      ),
    );
    $this->map = new MigrateSQLMap($this->machineName, $key, MigrateDestinationNode::getKeySchema());

    // Create a MigrateSource object, which manages retrieving the input data.
    $this->source = new MigrateSourceSQL($this->query);
    $this->destination = new MigrateDestinationNode($bundle);

    if (empty($this->fieldNames)) {
      return;
    }

    $this->addFieldMapping('nid', 'nid');
    $this->addFieldMapping(OG_VOCAB_FIELD, OG_VOCAB_FIELD);
  }

  public function prepareRow($row) {
    if (empty($this->fieldNames)) {
      return;
    }

    $field_names = $this->fieldNames;

    // We don't have the fields in the $row, so we load the entity to get
    // them.
    $wrapper = entity_metadata_wrapper('node', $row->nid);
    $tids = array();
    foreach ($field_names as $field_name) {
      $field = field_info_field($field_name);
      $vocabulary = taxonomy_vocabulary_machine_name_load($field['settings']['allowed_values'][0]['vocabulary']);
      $this->addOgVocab($vocabulary->vid, $field_name);
      if ($values = $wrapper->{$field_name}->value(array('identifier' => TRUE))) {
        $values = is_array($values) ? $values : array($values);
        $tids = array_merge($tids, $values);
      }
    }

    $row->{OG_VOCAB_FIELD} = $tids;
    parent::prepareRow($row);
  }

  /**
   * Construct the machine name from the source file name.
   */
  protected function generateMachineName($class_name = NULL) {
    return drupal_strtolower('OgVocabMigrate' . ucfirst($this->arguments['bundle']));
  }

  /**
   * Add the OG-vocab field to the bundle.
   */
  public function preImport() {
    $bundle = $this->bundle;

    // Add OG-vocab field to bundle.
    if (!field_info_instance('node', OG_VOCAB_FIELD, $bundle)) {
      og_create_field(OG_VOCAB_FIELD, 'node', $bundle);
      self::displayMessage(t('Added "OG vocabulary" field to @bundle content-type.', array('@bundle' => $bundle)), 'success');
    }
  }

  /**
   * When the import if completed, delete the fields from the instance.
   */
  public function postImport() {
    if (!$this->isComplete()) {
      return;
    }
    foreach ($this->fieldNames as $field_name) {
      $instance = field_info_instance('node', $field_name, $this->bundle);
      field_delete_instance($instance);
    }
  }

  /**
   * Helper function to add the OG-vocab entity.
   *
   * @param $vid
   *   The vocabulary ID related to the group.
   * @param $field_name
   *   The taxonomy term reference field, that needs to be converted to
   *   and OG-vocab entity.
   */
  protected function addOgVocab($vid, $field_name) {
    // Cache the vocabulary ID and field names that were queried to avoid
    // hitting the DB multiple times.
    $cache = &drupal_static(__METHOD__, array());
    $bundle = $this->bundle;

    if (isset($cache[$bundle][$field_name][$vid])) {
      return;
    }

    $cache[$bundle][$field_name][$vid] = TRUE;

    if (!og_vocab_load_og_vocab($vid, 'node', $bundle)) {
      $field = field_info_field($field_name);
      $instance = field_info_instance('node', $field_name, $bundle);
      $settings = array(
        'required' => $instance['required'],
        'widget_type' => $instance['widget']['type'] == 'options_select' ? 'options_select' : 'entityreference_autocomplete_tags',
        'cardinality' => $field['cardinality'],
      );
      $og_vocab = og_vocab_create_og_vocab($vid, 'node', $bundle, $settings);
      $og_vocab->save();
    }
  }

  /**
   * Helper function; Get the field names of term references in node entity.
   *
   * @return
   *   Array of field names for the given bundle.
   */
  public function getTaxonomyFields() {
    $field_names = &drupal_static(__METHOD__, array());
    $bundle = $this->bundle;

    if (isset($field_names[$bundle])) {
      return $field_names[$bundle];
    }

    $field_names[$bundle] = array();

    foreach (field_info_instances('node', $bundle) as $field_name =>  $instance) {
      $field = field_info_field($field_name);
      if ($field['type'] != 'taxonomy_term_reference') {
        // Field is not taxonomy reference.
        continue;
      }

      $vocabulary = taxonomy_vocabulary_machine_name_load($field['settings']['allowed_values'][0]['vocabulary']);
      if (!og_vocab_relation_get($vocabulary->vid)) {
        // field is not referencing a vocabaulry that is associated
        // with a group.
        continue;
      }
      $field_names[$bundle][] = $field['field_name'];
    }
    return $field_names[$bundle];
  }
}
