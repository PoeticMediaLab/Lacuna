<?php

/*
  Generate a histogram of annotations
 */

class HistogramAnnotatorPlugin extends AnnotatorPlugin {
  public function settings($defaults = array()) {
    return parent::settings($defaults);
  }

  public function setup() {
    $settings = $this->settings();
    libraries_load('d3');
		drupal_add_js(array('annotator_histogram' => (array) $settings), 'setting');
		drupal_add_js(drupal_get_path('module', 'annotator') . '/js/annotator_histogram.js', array('weight' => 100));
		drupal_add_js(drupal_get_path('module', 'annotator') . '/js/histogram.js', array('weight' => 101));
  }
}
