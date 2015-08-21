<?php
/**
 * @file
 * lacuna_stories_annotations.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function lacuna_stories_annotations_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function lacuna_stories_annotations_node_info() {
  $items = array(
    'annotation' => array(
      'name' => t('Annotation'),
      'base' => 'node_content',
      'description' => t('An annotation of a piece of content.'),
      'has_title' => '0',
      'title_label' => '',
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
