<?php

/**
 * Annotator ctools plugin
 */
class I18nAnnotatorPlugin extends AnnotatorPlugin {
  public function setup() {
    global $language;
    
    $element = array(
      '#tag' => 'link',
      '#attributes' => array(
        'href' => base_path() . drupal_get_path('module', 'annotator') . '/locale/' . $language->language . '.json',
        'rel' => 'gettext',
        'type' => 'application/json',
      ),
    );
    drupal_add_html_head($element, 'jsgettext');
  }
}