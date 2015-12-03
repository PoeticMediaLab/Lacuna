<?php
/**
 * @file
 * lacuna_stories_menus.features.menu_custom.inc
 */

/**
 * Implements hook_menu_default_menu_custom().
 */
function lacuna_stories_menus_menu_default_menu_custom() {
  $menus = array();

  // Exported menu: main-menu.
  $menus['main-menu'] = array(
    'menu_name' => 'main-menu',
    'title' => 'Main menu',
    'description' => 'The <em>Main</em> menu is used on many sites to show the major sections of the site, often in a top navigation bar.',
  );
  // Exported menu: menu-institutional-menu.
  $menus['menu-institutional-menu'] = array(
    'menu_name' => 'menu-institutional-menu',
    'title' => 'Institutional Menu',
    'description' => 'Menu for institutional-level navigation',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Institutional Menu');
  t('Main menu');
  t('Menu for institutional-level navigation');
  t('The <em>Main</em> menu is used on many sites to show the major sections of the site, often in a top navigation bar.');

  return $menus;
}
