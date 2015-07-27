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

  // Exported menu link: main-menu_about-this-course:about-course
  $menu_links['main-menu_about-this-course:about-course'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'about-course',
    'router_path' => 'about-course',
    'link_title' => 'About This Course',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'main-menu_about-this-course:about-course',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
    'parent_identifier' => 'main-menu_explore:<nolink>',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('About This Course');


  return $menu_links;
}
