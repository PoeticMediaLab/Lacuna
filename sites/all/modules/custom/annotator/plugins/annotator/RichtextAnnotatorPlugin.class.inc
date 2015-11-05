<?php

/*
Adds CKEditor to the Annotator window
*/

class RichtextAnnotatorPlugin extends AnnotatorPlugin {
  public function settings($defaults = array()) {
    // settings are in the richtext plugin
    return parent::settings($defaults);
  }

  public function setup() {
		// When javascript is aggregated, CKEditor needs to know where its libraries are
		drupal_add_js('window.CKEDITOR_BASEPATH="' . base_path() . libraries_get_path('ckeditor_annotator') . '/";', 'inline', array('weight' => -100));
		drupal_add_js(libraries_get_path('ckeditor_annotator') . '/ckeditor.js', array('weight' => 8));
		drupal_add_js(drupal_get_path('module', 'annotator') . '/js/annotator_richtext.js', array('weight' => 9));
    drupal_add_js(drupal_get_path('module', 'annotator') . '/js/richtext.js', array('weight' => 10));
	}
}
