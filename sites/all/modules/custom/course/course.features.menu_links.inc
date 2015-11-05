<?php
/**
 * @file
 * course.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function course_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: main-menu_courses:<front>
  $menu_links['main-menu_courses:<front>'] = array(
    'menu_name' => 'main-menu',
    'link_path' => '<front>',
    'router_path' => '',
    'link_title' => 'Courses',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'main-menu_courses:<front>',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 1,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -49,
    'customized' => 1,
    'parent_identifier' => 'main-menu_account:<nolink>',
  );
  // Exported menu link: menu-institutional-menu_courses:<front>
  $menu_links['menu-institutional-menu_courses:<front>'] = array(
    'menu_name' => 'menu-institutional-menu',
    'link_path' => '<front>',
    'router_path' => '',
    'link_title' => 'Courses',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'menu-institutional-menu_courses:<front>',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 1,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Courses');

  return $menu_links;
}
