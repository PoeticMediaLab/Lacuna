<?php
/**
 * @file
 * lacuna_stories_menus.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function lacuna_stories_menus_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: main-menu_account:<nolink>
  $menu_links['main-menu_account:<nolink>'] = array(
    'menu_name' => 'main-menu',
    'link_path' => '<nolink>',
    'router_path' => '<nolink>',
    'link_title' => 'Account',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'main-menu_account:<nolink>',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => -46,
    'customized' => 1,
  );
  // Exported menu link: main-menu_bibliography:biblio
  $menu_links['main-menu_bibliography:biblio'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'biblio',
    'router_path' => 'biblio',
    'link_title' => 'Bibliography',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'main-menu_bibliography:biblio',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -47,
    'customized' => 1,
    'parent_identifier' => 'main-menu_explore:<nolink>',
  );
  // Exported menu link: main-menu_connect:<nolink>
  $menu_links['main-menu_connect:<nolink>'] = array(
    'menu_name' => 'main-menu',
    'link_path' => '<nolink>',
    'router_path' => '<nolink>',
    'link_title' => 'Connect',
    'options' => array(
      'attributes' => array(
        'title' => '
',
      ),
      'identifier' => 'main-menu_connect:<nolink>',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => -48,
    'customized' => 1,
  );
  // Exported menu link: main-menu_create:<nolink>
  $menu_links['main-menu_create:<nolink>'] = array(
    'menu_name' => 'main-menu',
    'link_path' => '<nolink>',
    'router_path' => '<nolink>',
    'link_title' => 'Create',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'main-menu_create:<nolink>',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => -49,
    'customized' => 1,
  );
  // Exported menu link: main-menu_explore:<nolink>
  $menu_links['main-menu_explore:<nolink>'] = array(
    'menu_name' => 'main-menu',
    'link_path' => '<nolink>',
    'router_path' => '<nolink>',
    'link_title' => 'Explore',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'main-menu_explore:<nolink>',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => -50,
    'customized' => 1,
  );
  // Exported menu link: main-menu_forums:forum
  $menu_links['main-menu_forums:forum'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'forum',
    'router_path' => 'forum',
    'link_title' => 'Forums',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'main-menu_forums:forum',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
    'parent_identifier' => 'main-menu_connect:<nolink>',
  );
  // Exported menu link: main-menu_help:contact
  $menu_links['main-menu_help:contact'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'contact',
    'router_path' => 'contact',
    'link_title' => 'Help',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'main-menu_help:contact',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -49,
    'customized' => 1,
    'parent_identifier' => 'main-menu_account:<nolink>',
  );
  // Exported menu link: main-menu_logout:user/logout
  $menu_links['main-menu_logout:user/logout'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'user/logout',
    'router_path' => 'user/logout',
    'link_title' => 'Logout',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'main-menu_logout:user/logout',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -48,
    'customized' => 1,
    'parent_identifier' => 'main-menu_account:<nolink>',
  );
  // Exported menu link: main-menu_materials:materials
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
  // Exported menu link: main-menu_my-annotations:my-annotations
  $menu_links['main-menu_my-annotations:my-annotations'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'my-annotations',
    'router_path' => 'my-annotations',
    'link_title' => 'My Annotations',
    'options' => array(
      'identifier' => 'main-menu_my-annotations:my-annotations',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -50,
    'customized' => 1,
    'parent_identifier' => 'main-menu_reflect:<nolink>',
  );
  // Exported menu link: main-menu_my-profile:user
  $menu_links['main-menu_my-profile:user'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'user',
    'router_path' => 'user',
    'link_title' => 'My Profile',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'main-menu_my-profile:user',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -50,
    'customized' => 1,
    'parent_identifier' => 'main-menu_account:<nolink>',
  );
  // Exported menu link: main-menu_my-threads:my-threads
  $menu_links['main-menu_my-threads:my-threads'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'my-threads',
    'router_path' => 'my-threads',
    'link_title' => 'My Threads',
    'options' => array(
      'identifier' => 'main-menu_my-threads:my-threads',
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
  // Exported menu link: main-menu_reflect:<nolink>
  $menu_links['main-menu_reflect:<nolink>'] = array(
    'menu_name' => 'main-menu',
    'link_path' => '<nolink>',
    'router_path' => '<nolink>',
    'link_title' => 'Reflect',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'main-menu_reflect:<nolink>',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => -47,
    'customized' => 1,
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
    'weight' => -49,
    'customized' => 1,
    'parent_identifier' => 'main-menu_explore:<nolink>',
  );
  // Exported menu link: main-menu_sewing-kit:sewing-kit
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
    'weight' => -50,
    'customized' => 1,
    'parent_identifier' => 'main-menu_create:<nolink>',
  );
  // Exported menu link: main-menu_topics:topics
  $menu_links['main-menu_topics:topics'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'topics',
    'router_path' => 'topics',
    'link_title' => 'Topics',
    'options' => array(
      'identifier' => 'main-menu_topics:topics',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -48,
    'customized' => 1,
    'parent_identifier' => 'main-menu_explore:<nolink>',
  );
  // Exported menu link: main-menu_write-a-response:node/add
  $menu_links['main-menu_write-a-response:node/add'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'node/add',
    'router_path' => 'node/add',
    'link_title' => 'Write a Response',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'main-menu_write-a-response:node/add',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -49,
    'customized' => 1,
    'parent_identifier' => 'main-menu_create:<nolink>',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Account');
  t('Bibliography');
  t('Connect');
  t('Create');
  t('Explore');
  t('Forums');
  t('Help');
  t('Logout');
  t('Materials');
  t('My Annotations');
  t('My Profile');
  t('My Threads');
  t('Reflect');
  t('Responses');
  t('Sewing Kit');
  t('Topics');
  t('Write a Response');


  return $menu_links;
}
