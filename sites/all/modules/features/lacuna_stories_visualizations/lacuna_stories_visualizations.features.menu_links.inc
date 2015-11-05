<?php
/**
 * @file
 * lacuna_stories_visualizations.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function lacuna_stories_visualizations_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: main-menu_annotations-dashboard:visualization/dashboard
  $menu_links['main-menu_annotations-dashboard:visualization/dashboard'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'visualization/dashboard',
    'router_path' => 'visualization/dashboard',
    'link_title' => 'Annotations Dashboard',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'main-menu_annotations-dashboard:visualization/dashboard',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -50,
    'customized' => 1,
    'parent_identifier' => 'main-menu_reflect:<nolink>',
  );
  // Exported menu link: main-menu_responses-map:visualization/responses
  $menu_links['main-menu_responses-map:visualization/responses'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'visualization/responses',
    'router_path' => 'visualization/responses',
    'link_title' => 'Responses Map',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'main-menu_responses-map:visualization/responses',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -49,
    'customized' => 1,
    'parent_identifier' => 'main-menu_reflect:<nolink>',
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Annotations Dashboard');
  t('Responses Map');

  return $menu_links;
}
