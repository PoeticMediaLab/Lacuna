<?php
/**
 * @file
 * lacuna_notifications.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function lacuna_notifications_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: main-menu_recent-interactions:node/17.
  $menu_links['main-menu_recent-interactions:node/17'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'node/17',
    'router_path' => 'node/%',
    'link_title' => 'Recent Interactions',
    'options' => array(
      'identifier' => 'main-menu_recent-interactions:node/17',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 10,
    'customized' => 0,
    'parent_identifier' => 'main-menu_reflect:<nolink>',
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Recent Interactions');

  return $menu_links;
}
