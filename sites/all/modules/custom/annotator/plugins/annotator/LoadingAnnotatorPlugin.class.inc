<?php

/*  This code creates a very simple Annotator plugin to track status of
*   annotations loading on the page.
*/

class LoadingAnnotatorPlugin extends AnnotatorPlugin {

  public function setup() {

    drupal_add_css('//maxcdn.bootstrapcdn.com/font-awesome/4.2.0/css/font-awesome.min.css', $type='external');

    // Create the loading plugin for Annotator
    drupal_add_js(drupal_get_path('module', 'annotator') . '/js/annotator_loading.js');

    // Extend the Annotator Class to include the Loading plugin.
    drupal_add_js(drupal_get_path('module', 'annotator') . '/js/loading.js');
  }
}
