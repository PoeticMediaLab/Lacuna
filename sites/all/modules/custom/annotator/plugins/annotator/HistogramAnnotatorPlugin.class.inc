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
				'container' => 'page-turner-nav-parent',
				'horizontal' => 1,
				'page_turner_active' => TRUE,
			);
		} else {
			$defaults['layout'] = array(
				'container' => 'article',
				'horizontal' => 0,
				'width' => '25',
				'page_turner_active' => FALSE,
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
