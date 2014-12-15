<?php

/**
 * Annotator ctools plugin
 */
class MarkdownAnnotatorPlugin extends AnnotatorPlugin {
  public function setup() {
    drupal_add_js(drupal_get_path('module', 'annotator') . '/js/showdown.js', 
      # IMPORTANT: Order matters, must be imported before markdown plugin
      array('weight' => -1)
    );
    drupal_add_js(drupal_get_path('module', 'annotator') . '/js/annotator_markdown.js');
  }
}
