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
  // Exported menu: navigation.
  $menus['navigation'] = array(
    'menu_name' => 'navigation',
    'title' => 'Navigation',
    'description' => 'The <em>Navigation</em> menu contains links intended for site visitors. Links are added to the <em>Navigation</em> menu automatically by some modules.',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Main menu');
  t('Navigation');
  t('The <em>Navigation</em> menu contains links intended for site visitors. Links are added to the <em>Navigation</em> menu automatically by some modules.');
  t('This is the main navigation menu for Lacuna Stories, shown along the top of the page.');


  return $menus;
}
