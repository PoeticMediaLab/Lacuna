<?php
/**
 * @file
 * lacuna_stories_peer_groups.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function lacuna_stories_peer_groups_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: main-menu_peer-groups:peer-groups.
  $menu_links['main-menu_peer-groups:peer-groups'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'peer-groups',
    'router_path' => 'peer-groups',
    'link_title' => 'Peer Groups',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'main-menu_peer-groups:peer-groups',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -47,
    'customized' => 1,
    'parent_identifier' => 'main-menu_connect:<nolink>',
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Peer Groups');

  return $menu_links;
}
