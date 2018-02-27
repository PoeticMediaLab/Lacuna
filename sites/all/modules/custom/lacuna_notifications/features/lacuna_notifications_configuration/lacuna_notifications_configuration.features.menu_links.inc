<?php
/**
 * @file
 * lacuna_notifications_configuration.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function lacuna_notifications_configuration_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: main-menu_latest-conversations:latest-conversations.
  $menu_links['main-menu_latest-conversations:latest-conversations'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'latest-conversations',
    'router_path' => 'latest-conversations',
    'link_title' => 'Latest Conversations',
    'options' => array(
      'link_badge' => array(
        'callback' => 'menu_badges_execute_view',
        'arguments' => array(
          'view_name' => 'total_notifications_view',
          'view_display_id' => 'menu_badge_1',
        ),
        'key' => 'views_total_notifications_view_menu_badge_1',
      ),
      'attributes' => array(),
      'identifier' => 'main-menu_latest-conversations:latest-conversations',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 10,
    'customized' => 1,
    'parent_identifier' => 'main-menu_reflect:<nolink>',
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Latest Conversations');

  return $menu_links;
}
