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
    'description' => 'The <em>Main</em> menu is used on many sites to show the major sections of the site, often in a top navigation bar.',
  );
  // Exported menu: menu-left-menu.
  $menus['menu-left-menu'] = array(
    'menu_name' => 'menu-left-menu',
    'title' => 'Left menu',
    'description' => 'This is the main navigation menu for Lacuna Stories, featured along the left side of the site.',
  );
  // Exported menu: menu-top-right.
  $menus['menu-top-right'] = array(
    'menu_name' => 'menu-top-right',
    'title' => 'Top right menu',
    'description' => '',
  );
  // Exported menu: navigation.
  $menus['navigation'] = array(
    'menu_name' => 'navigation',
    'title' => 'Navigation',
    'description' => 'The <em>Navigation</em> menu contains links intended for site visitors. Links are added to the <em>Navigation</em> menu automatically by some modules.',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Left menu');
  t('Main menu');
  t('Navigation');
  t('The <em>Main</em> menu is used on many sites to show the major sections of the site, often in a top navigation bar.');
  t('The <em>Navigation</em> menu contains links intended for site visitors. Links are added to the <em>Navigation</em> menu automatically by some modules.');
  t('This is the main navigation menu for Lacuna Stories, featured along the left side of the site.');
  t('Top right menu');


  return $menus;
}
