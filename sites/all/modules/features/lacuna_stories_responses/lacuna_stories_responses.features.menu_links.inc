<?php
/**
 * @file
 * lacuna_stories_responses.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function lacuna_stories_responses_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: main-menu_my-writing:my-writing
  $menu_links['main-menu_my-writing:my-writing'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'my-writing',
    'router_path' => 'my-writing',
    'link_title' => 'My Writing',
    'options' => array(
      'identifier' => 'main-menu_my-writing:my-writing',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 0,
  );
  // Exported menu link: main-menu_responses:responses
  $menu_links['main-menu_responses:responses'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'responses',
    'router_path' => 'responses',
    'link_title' => 'Responses',
    'options' => array(
      'identifier' => 'main-menu_responses:responses',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 0,
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('My Writing');
  t('Responses');

  return $menu_links;
}
