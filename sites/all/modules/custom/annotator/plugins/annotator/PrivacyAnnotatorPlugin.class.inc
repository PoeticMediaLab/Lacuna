<?php

/**
 * Annotator ctools plugin
 */
class PrivacyAnnotatorPlugin extends AnnotatorPlugin {

  public function setup() {
    drupal_add_js(drupal_get_path('module', 'annotator') . '/js/annotator_privacy.js');
    drupal_add_js(drupal_get_path('module', 'annotator') . '/js/privacy.js');
    drupal_add_css(drupal_get_path('module', 'annotator') . '/css/privacy.css');
  }

}