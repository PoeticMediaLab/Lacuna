<?php
/**
 * @file
 * lacuna_stories_peer_groups.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function lacuna_stories_peer_groups_ctools_plugin_api($module = NULL, $api = NULL) {
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
function lacuna_stories_peer_groups_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function lacuna_stories_peer_groups_node_info() {
  $items = array(
    'peer_group' => array(
      'name' => t('Peer Group'),
      'base' => 'node_content',
      'description' => t('Groups that students can create to share annotations with each other.'),
      'has_title' => '1',
      'title_label' => t('Group Name'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
