<?php

/**
 * Annotator ctools plugin
 */
class ControlsAnnotatorPlugin extends AnnotatorPlugin {

  public function setup() {
    drupal_add_js(drupal_get_path('module', 'annotator') . '/js/annotator_controls.js');
    drupal_add_js(drupal_get_path('module', 'annotator') . '/js/controls.js');
  }
}
