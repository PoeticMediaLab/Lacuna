<?php

class AuthorAnnotatorPlugin extends AnnotatorPlugin {
  public function settings($defaults = array()) {
    return parent::settings($defaults);
  }

  public function setup() {
//    $settings = $this->settings();
    drupal_add_js(drupal_get_path('module', 'annotator') . '/js/annotator_author.js');
    drupal_add_js(drupal_get_path('module', 'annotator') . '/js/author.js');
  }
}
