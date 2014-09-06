<?php
/**
 * @file
 * lacuna_stories.features.menu_custom.inc
 */

/**
 * Implements hook_menu_default_menu_custom().
 */
function lacuna_stories_menu_default_menu_custom() {
  $menus = array();

  // Exported menu: main-menu.
  $menus['main-menu'] = array(
    'menu_name' => 'main-menu',
    'title' => 'Main menu',
    'description' => 'This is the main navigation menu for Lacuna Stories, shown along the top of the page.',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Main menu');
  t('This is the main navigation menu for Lacuna Stories, shown along the top of the page.');


  return $menus;
}
