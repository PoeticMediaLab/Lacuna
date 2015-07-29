<?php

/*
Implements annotator-richText plugin
@https://github.com/danielcebrian/richText-annotator
*/

class RichtextAnnotatorPlugin extends AnnotatorPlugin {
  public function settings($defaults = array()) {
    // Settings are in the richtext plugin
    return parent::settings($defaults);
  }

  public function setup() {
    $settings = $this->settings();
    drupal_add_js(array('annotator_richtext' => (array) $settings), 'setting');
    drupal_add_js(libraries_get_path('ckeditor') . '/ckeditor.js', array('weight' => -10));
    drupal_add_js(drupal_get_path('module', 'annotator') . '/js/annotator_richtext.js', array('weight' => 9));
    drupal_add_js(drupal_get_path('module', 'annotator') . '/js/richtext.js', array('weight' => 10));
  }
}
