<?php

/**
 * Annotator ctools plugin
 */
class TagsAnnotatorPlugin extends AnnotatorPlugin {
  public function setup() {
    // MLW - Load tags for autocomplete in Annotator window
    // Possible refactor for speed? EFQ is slower than db_select
    $tags = taxonomy_vocabulary_machine_name_load('annotation_tags');
    $query = new EntityFieldQuery();
    $result = $query->entityCondition('entity_type', 'taxonomy_term')
      ->propertyCondition('vid', (int) $tags->vid, '=')
      ->execute();
    $tags = array();  // We're done with the previous $tags
    $flag = flag_get_flag('curated_tag');
    if (!empty($result['taxonomy_term'])) {
      $terms = taxonomy_term_load_multiple(array_keys($result['taxonomy_term']));
      foreach ($terms as $term) {
        if ($flag && $flag->is_flagged($term->tid)) {
          // Warning: hard-coded labels here - MLW
          $category = 'curated tags';
        } else {
          $category = 'custom tags';
        }
        array_push($tags, array('label' => $term->name, 'category' => $category));
      }
    }

    // Sort so that "curated tags" are on top
    // NB: curated comes before custom in alphabetical sort
    // if these labels change, then this sort algorithm needs
    // to update, too
    usort($tags, function($a, $b) {
      if ($a['category'] == $b['category']) {
        return (strtolower($a['label']) < strtolower($b['label'])) ? -1 : 1;
      }
      return ($a['category'] < $b['category']) ? -1 : 1;
    });

    // Loaded in annotator_tags.js
    drupal_add_js(drupal_get_path('module', 'annotator') . '/js/autocomplete_categories.js', array('weight' => 10));
    drupal_add_js(array('annotator_tags' => (array) $tags), 'setting');
    // drupal_add_library('system', 'ui.autocomplete', TRUE);
    drupal_add_js(drupal_get_path('module', 'annotator') . '/js/annotator_tags.js', array('weight' => 11));
    drupal_add_js(drupal_get_path('module', 'annotator') . '/js/tags.js', array('weight' => 12));
    drupal_add_css(drupal_get_path('module', 'annotator') . '/css/tags.css');
  }
}
