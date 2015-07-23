<?php

/*
  Generate a heatmap of annotations
 */

class HeatmapAnnotatorPlugin extends AnnotatorPlugin {
  public function settings($defaults = array()) {
		// Pass layout settings to the heatmap
		$defaults['layout'] = array();
		if (TRUE) {
			$defaults['layout'] = array(
				'container' => '#page-turner-nav-parent',
				'orientation' => 'horizontal'
			);
		} else {
			$defaults['layout'] = array(
				'container' => 'div#content',
				'orientation' => 'vertical',
				'width' => '50px'
			);
		}
    return parent::settings($defaults);
  }

  public function setup() {
    $settings = $this->settings();

    libraries_load('d3');
		drupal_add_js(array('annotator_heatmap' => (array) $settings), 'setting');
    drupal_add_js(drupal_get_path('module', 'annotator') . '/js/annotator_heatmap.js');
    drupal_add_js(drupal_get_path('module', 'annotator') . '/js/heatmap.js');
  }
}
