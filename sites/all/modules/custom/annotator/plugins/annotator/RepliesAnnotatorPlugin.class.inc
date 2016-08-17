<?php

/**
 * Plugin to allow replies to annotations
 */
class RepliesAnnotatorPlugin extends AnnotatorPlugin {

	public function settings($defaults = array()) {
		global $user;
		$defaults = array('current_uid' => $user->uid);
		return parent::settings($defaults);
	}


	public function setup() {
		$settings = $this->settings();

		// Sends the settings data to a global variable where JavaScript can access it.
		drupal_add_js(array('annotator_replies' => (array) $settings), 'setting');

		drupal_add_js(drupal_get_path('module', 'annotator') . '/js/annotator_replies.js');
		drupal_add_js(drupal_get_path('module', 'annotator') . '/js/replies.js');
	}

}
