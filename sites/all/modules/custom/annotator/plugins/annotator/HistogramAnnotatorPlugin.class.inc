<?php

/*
  Generate a histogram of annotations
 */

class HistogramAnnotatorPlugin extends AnnotatorPlugin {
  public function settings($defaults = array()) {
		// Pass layout settings to the histogram
		$defaults['layout'] = array();
		if (variable_get('page_turner_active')) {
			$defaults['layout'] = array(
				'containerID' => 'page-turner-nav-parent',
				'horizontal' => 1
			);
		} else {
			$defaults['layout'] = array(
				'containerID' => 'content',
				'horizontal' => 0,
				'width' => '50px'
			);
		}
    return parent::settings($defaults);
  }

  public function setup() {
    $settings = $this->settings();
    libraries_load('d3');
		drupal_add_js(array('annotator_histogram' => (array) $settings), 'setting');
		drupal_add_js(drupal_get_path('module', 'annotator') . '/js/annotator_histogram.js');
		drupal_add_js(drupal_get_path('module', 'annotator') . '/js/histogram.js');
  }
}
