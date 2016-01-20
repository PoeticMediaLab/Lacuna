<?php
/**
 * @file
 * lacuna_stories_materials.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function lacuna_stories_materials_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: main-menu_materials:materials.
  $menu_links['main-menu_materials:materials'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'materials',
    'router_path' => 'materials',
    'link_title' => 'Materials',
    'options' => array(
      'identifier' => 'main-menu_materials:materials',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -50,
    'customized' => 1,
    'parent_identifier' => 'main-menu_explore:<nolink>',
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Materials');

  return $menu_links;
}
