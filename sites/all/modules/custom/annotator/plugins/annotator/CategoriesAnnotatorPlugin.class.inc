<?php

/*
  This code creates a form in Annotator settings for Categories, saves those selections to a global settings variable, and loads documents relevant to the plugin.
 */

class CategoriesAnnotatorPlugin extends AnnotatorPlugin {
  /*  Values in $defaults are initial values used to populate the Categories settings form. These values are overridden if changed in the actual form. To access the form values, go to JS console and type Drupal.settings.category_list.
  */

  // define('ANNOTATION_CATEGORY_TAXONOMY', 'annotation_categories');
  // TODO: change this to read from the taxonomy
  public function settings($defaults = array()) {
    $taxonomy = taxonomy_vocabulary_machine_name_load('annotation_categories');
    $defaults = array('category' => array());
    // TODO: check that taxonomy exists before trying to load
    // If not, send Drupal error message
    foreach(taxonomy_term_load_multiple(array(), array('vid' => $taxonomy->vid)) as $term) {
      $defaults['category'][] = $term->name;
    }
    return parent::settings($defaults);
  }

  public function setup() {
    $settings = $this->settings();
    // Sends the settings data to a global variable where JavaScript can access it.
    // In JS console, type: Drupal.settings.annotator_categories
    drupal_add_js(array('annotator_categories' => (array) $settings), 'setting');

    // Create the categories plugin for Annotator
    drupal_add_js(drupal_get_path('module', 'annotator') . '/js/annotator_categories.js');

    // Extend the Annotator Class to include the Categories plugin.
    drupal_add_js(drupal_get_path('module', 'annotator') . '/js/categories.js');
  }
}
