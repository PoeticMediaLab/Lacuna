<?php

/**
 * Annotator ctools plugin
 */
class TagsAnnotatorPlugin extends AnnotatorPlugin {
  public function settings($defaults = array()) {
    // Set labels for if something is flagged
    $defaults['flagged'] = array(0 => 'Custom Tags', 1 => 'Curated Tags');
    $loaded_tags = array();

    // Get the course context to know which tags to load into the annotator. If there is no context set (which should never happen when creating/editing an annotation) then do not load any tags.
    if ($current_course = course_get_selected_course()) {
      // Load tags for autocomplete in Annotator window
      $tags = taxonomy_vocabulary_machine_name_load('annotation_tags');
      $query = new EntityFieldQuery();
      $result = $query->entityCondition('entity_type', 'taxonomy_term')
        ->propertyCondition('vid', (int) $tags->vid, '=')
        ->fieldCondition('field_term_course', 'target_id', $current_course)
        ->execute();
      $flag = flag_get_flag('curated_tag');
      if (!empty($result['taxonomy_term'])) {
        $terms = taxonomy_term_load_multiple(array_keys($result['taxonomy_term']));
        foreach ($terms as $term) {
          if ($flag && $flag->is_flagged($term->tid)) {
            $flagged = 1;
          }
          else {
            $flagged = 0;
          }
          array_push($loaded_tags, array(
            'label' => $term->name,
            'flagged' => $flagged
          ));
        }
      }

      // Sort so that "curated tags" are on top
      usort($loaded_tags, function ($a, $b) {
        if ($a['flagged'] == $b['flagged']) {
          return (strtolower($a['label']) < strtolower($b['label'])) ? -1 : 1;
        }
        return ($a['flagged'] > $b['flagged']) ? -1 : 1;
      });
    }
    $defaults['tags'] = $loaded_tags;
    return parent::settings($defaults);
  }

  public function setup() {
    $settings = $this->settings();
    drupal_add_js(array('annotator_tags' => (array) $settings), 'setting');
    // Loaded in annotator_tags.js
    drupal_add_js(drupal_get_path('module', 'annotator') . '/js/autocomplete_categories.js', array('weight' => 10));
    drupal_add_js(drupal_get_path('module', 'annotator') . '/js/annotator_tags.js', array('weight' => 11));
    drupal_add_js(drupal_get_path('module', 'annotator') . '/js/tags.js', array('weight' => 12));
  }
}
