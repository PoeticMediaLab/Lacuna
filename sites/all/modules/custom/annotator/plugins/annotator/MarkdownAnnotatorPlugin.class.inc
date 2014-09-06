<?php

/**
 * Annotator ctools plugin
 */
class MarkdownAnnotatorPlugin extends AnnotatorPlugin {
  public function setup() {
    drupal_add_library('annotator', 'showdown', TRUE);
    drupal_add_js(drupal_get_path('module', 'annotator') . '/js/annotator_markdown.js');
  }
}