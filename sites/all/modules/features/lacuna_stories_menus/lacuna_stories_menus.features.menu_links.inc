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

  // Exported menu link: main-menu_about-this-course:node/248
  $menu_links['main-menu_about-this-course:node/248'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'node/248',
    'router_path' => 'node/%',
    'link_title' => 'About this Course',
    'options' => array(
      'identifier' => 'main-menu_about-this-course:node/248',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 0,
    'parent_identifier' => 'main-menu_explore:<nolink>',
  );
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
    'weight' => -46,
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
    'weight' => -48,
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
    'weight' => -47,
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
    'weight' => -49,
    'customized' => 1,
    'parent_identifier' => 'main-menu_create:<nolink>',
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
  // Exported menu link: main-menu_research-consent:node/225
  $menu_links['main-menu_research-consent:node/225'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'node/225',
    'router_path' => 'node/%',
    'link_title' => 'Research Consent',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'main-menu_research-consent:node/225',
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
    'parent_identifier' => 'main-menu_connect:<nolink>',
  );
  // Exported menu link: main-menu_syllabus:syllabus
  $menu_links['main-menu_syllabus:syllabus'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'syllabus',
    'router_path' => 'syllabus',
    'link_title' => 'Syllabus',
    'options' => array(
      'identifier' => 'main-menu_syllabus:syllabus',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -47,
    'customized' => 1,
    'parent_identifier' => 'main-menu_explore:<nolink>',
  );
  // Exported menu link: main-menu_threads:threads
  $menu_links['main-menu_threads:threads'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'threads',
    'router_path' => 'threads',
    'link_title' => 'Threads',
    'options' => array(
      'identifier' => 'main-menu_threads:threads',
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
  // Exported menu link: main-menu_write-a-response:node/add/blog
  $menu_links['main-menu_write-a-response:node/add/blog'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'node/add/blog',
    'router_path' => 'node/add/blog',
    'link_title' => 'Write a Response',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'main-menu_write-a-response:node/add/blog',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -50,
    'customized' => 1,
    'parent_identifier' => 'main-menu_create:<nolink>',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('About this Course');
  t('Account');
  t('Annotations Dashboard');
  t('Bibliography');
  t('Connect');
  t('Create');
  t('Explore');
  t('Help');
  t('Logout');
  t('Materials');
  t('My Profile');
  t('My Writing');
  t('Reflect');
  t('Research Consent');
  t('Responses');
  t('Responses Map');
  t('Sewing Kit');
  t('Syllabus');
  t('Threads');
  t('Write a Response');


  return $menu_links;
}
