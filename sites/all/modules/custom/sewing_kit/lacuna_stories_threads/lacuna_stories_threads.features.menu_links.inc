<?php
/**
 * @file
 * lacuna_stories_threads.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function lacuna_stories_threads_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: main-menu_sewing-kit:sewing-kit.
  $menu_links['main-menu_sewing-kit:sewing-kit'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'sewing-kit',
    'router_path' => 'sewing-kit',
    'link_title' => 'Sewing Kit',
    'options' => array(
      'identifier' => 'main-menu_sewing-kit:sewing-kit',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -49,
    'customized' => 1,
    'parent_identifier' => 'main-menu_connect:<nolink>',
  );
  // Exported menu link: main-menu_threads:threads.
  $menu_links['main-menu_threads:threads'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'threads',
    'router_path' => 'threads',
    'link_title' => 'Threads',
    'options' => array(
      'identifier' => 'main-menu_threads:threads',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -48,
    'customized' => 1,
    'parent_identifier' => 'main-menu_connect:<nolink>',
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Sewing Kit');
  t('Threads');

  return $menu_links;
}
