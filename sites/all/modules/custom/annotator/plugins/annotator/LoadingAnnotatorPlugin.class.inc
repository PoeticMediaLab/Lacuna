<?php

/*  This code creates a very simple Annotator plugin to track status of
*   annotations loading on the page.
*/

class LoadingAnnotatorPlugin extends AnnotatorPlugin {

  public function setup() {

    // Sends the settings data to a global variable where JavaScript can access it.
    // In JS console, type: Drupal.settings.annotator_loading
    drupal_add_js(array('annotator_loading' => (array) $settings), 'setting');

    // Create the loading plugin for Annotator
    drupal_add_js(drupal_get_path('module', 'annotator') . '/js/annotator_loading.js');

    // Extend the Annotator Class to include the Loading plugin.
    drupal_add_js(drupal_get_path('module', 'annotator') . '/js/loading.js');
  }
}
