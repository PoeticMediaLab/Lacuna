<?php

/**
 * Annotator ctools plugin
 */
class TagsAnnotatorPlugin extends AnnotatorPlugin {
  public function setup() {
    // MLW - Load tags for autocomplete in Annotator window
    $tags = taxonomy_vocabulary_machine_name_load('tags');
    $query = new EntityFieldQuery();
    $result = $query->entityCondition('entity_type', 'taxonomy_term')
      ->propertyCondition('vid', $tags->vid)
      ->execute();
    $term_names = array();
    if (!empty($result['taxonomy_term'])) {
      $terms = taxonomy_term_load_multiple(array_keys($result['taxonomy_term']));
      foreach ($terms as $term) {
        array_push($term_names, $term->name);
      }
    }
    // Loaded in annotator_tags.js
    drupal_add_js(array('annotator_tags' => (array) $term_names), 'setting');
    drupal_add_js(drupal_get_path('module', 'annotator') . '/js/annotator_tags.js');
  }
}
