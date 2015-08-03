<?php

/**
 * Annotator comment count plugin
 */
class CommentAnnotatorPlugin extends AnnotatorPlugin {

	public function settings($defaults = array()) {
		$defaults = array('base_root' => $GLOBALS['base_root']);
		return parent::settings($defaults);
	}


	public function setup() {
		$settings = $this->settings();

		// Sends the settings data to a global variable where JavaScript can access it.
		drupal_add_js(array('annotator_comment' => (array) $settings), 'setting');

		drupal_add_js(drupal_get_path('module', 'annotator') . '/js/annotator_comment.js');
		drupal_add_js(drupal_get_path('module', 'annotator') . '/js/comment.js');
	}

}
