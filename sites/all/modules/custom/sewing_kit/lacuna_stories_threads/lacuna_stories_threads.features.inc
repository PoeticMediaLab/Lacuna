<?php
/**
 * @file
 * lacuna_stories_threads.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function lacuna_stories_threads_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "context" && $api == "context") {
    return array("version" => "3");
  }
  if ($module == "ds" && $api == "ds") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function lacuna_stories_threads_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function lacuna_stories_threads_node_info() {
  $items = array(
    'thread' => array(
      'name' => t('Thread'),
      'base' => 'node_content',
      'description' => t('Stitch annotations together into a thread.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
