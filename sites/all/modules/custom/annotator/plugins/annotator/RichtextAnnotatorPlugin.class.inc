<?php

/*
Implements annotator-richText plugin
@https://github.com/danielcebrian/richText-annotator
*/

class RichtextAnnotatorPlugin extends AnnotatorPlugin {
  public function settings($defaults = array()) {
    $defaults = array('optionsRichText' => array());
    $defaults['optionsRichText'] = array('tinymce' => array(
      'selector' => "li.annotator-item textarea",
      'plugins' => "",
      'menubar' => false,
      'toolbar_items_size' => 'small',
      'extended_valid_elements' => "iframe[src|frameborder|style|scrolling|class|width|height|name|align|id]",
      'toolbar' => "",
      ));
    return parent::settings($defaults);
  }

  public function setup() {
    $settings = $this->settings();
    drupal_add_js(array('annotator_richtext' => (array) $settings), 'setting');
    drupal_add_js(libraries_get_path('tinymce') . '/jscripts/tiny_mce/tiny_mce.js', array('weight' => -10));
    drupal_add_css(drupal_get_path('module', 'annotator') . '/css/richText-annotator.css');
    drupal_add_js(drupal_get_path('module', 'annotator') . '/js/annotator_richtext.js');
    drupal_add_js(drupal_get_path('module', 'annotator') . '/js/richText-annotator.js');
  }
}
