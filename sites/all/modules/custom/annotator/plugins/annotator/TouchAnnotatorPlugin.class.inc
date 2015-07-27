<?php

/*
  Enable annotations on Touch devices
 */

class TouchAnnotatorPlugin extends AnnotatorPlugin {
  public function setup() {
    $settings = $this->settings();
    drupal_add_js(drupal_get_path('module', 'annotator') . '/js/annotator_touch.js');
    // Note: touch.js must be loaded first, other classes rely on it being defined
    drupal_add_js(drupal_get_path('module', 'annotator') . '/js/touch.js');
    drupal_add_js(drupal_get_path('module', 'annotator') . '/js/touch/utils.js');
    drupal_add_js(drupal_get_path('module', 'annotator') . '/js/touch/editor.js');
    drupal_add_js(drupal_get_path('module', 'annotator') . '/js/touch/viewer.js');
  }
}
