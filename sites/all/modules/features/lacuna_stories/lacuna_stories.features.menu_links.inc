<?php
/**
 * @file
 * lacuna_stories.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function lacuna_stories_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: menu-left-menu_bibliography:biblio
  $menu_links['menu-left-menu_bibliography:biblio'] = array(
    'menu_name' => 'menu-left-menu',
    'link_path' => 'biblio',
    'router_path' => 'biblio',
    'link_title' => 'Bibliography',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'menu-left-menu_bibliography:biblio',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -42,
    'customized' => 1,
  );
  // Exported menu link: menu-left-menu_dashboard:node/61
  $menu_links['menu-left-menu_dashboard:node/61'] = array(
    'menu_name' => 'menu-left-menu',
    'link_path' => 'node/61',
    'router_path' => 'node/%',
    'link_title' => 'Dashboard',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'menu-left-menu_dashboard:node/61',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -50,
    'customized' => 1,
  );
  // Exported menu link: menu-left-menu_forum:forum
  $menu_links['menu-left-menu_forum:forum'] = array(
    'menu_name' => 'menu-left-menu',
    'link_path' => 'forum',
    'router_path' => 'forum',
    'link_title' => 'Forum',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'menu-left-menu_forum:forum',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -45,
    'customized' => 1,
  );
  // Exported menu link: menu-left-menu_instructor-dashboard:node/62
  $menu_links['menu-left-menu_instructor-dashboard:node/62'] = array(
    'menu_name' => 'menu-left-menu',
    'link_path' => 'node/62',
    'router_path' => 'node/%',
    'link_title' => 'Instructor Dashboard',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'menu-left-menu_instructor-dashboard:node/62',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -49,
    'customized' => 1,
  );
  // Exported menu link: menu-left-menu_materials:materials
  $menu_links['menu-left-menu_materials:materials'] = array(
    'menu_name' => 'menu-left-menu',
    'link_path' => 'materials',
    'router_path' => 'materials',
    'link_title' => 'Materials',
    'options' => array(
      'identifier' => 'menu-left-menu_materials:materials',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -48,
    'customized' => 1,
  );
  // Exported menu link: menu-left-menu_my-writing:my-writing
  $menu_links['menu-left-menu_my-writing:my-writing'] = array(
    'menu_name' => 'menu-left-menu',
    'link_path' => 'my-writing',
    'router_path' => 'my-writing',
    'link_title' => 'My Writing',
    'options' => array(
      'identifier' => 'menu-left-menu_my-writing:my-writing',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -43,
    'customized' => 1,
  );
  // Exported menu link: menu-left-menu_responses:responses
  $menu_links['menu-left-menu_responses:responses'] = array(
    'menu_name' => 'menu-left-menu',
    'link_path' => 'responses',
    'router_path' => 'responses',
    'link_title' => 'Responses',
    'options' => array(
      'identifier' => 'menu-left-menu_responses:responses',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -44,
    'customized' => 1,
  );
  // Exported menu link: menu-left-menu_topics:topics
  $menu_links['menu-left-menu_topics:topics'] = array(
    'menu_name' => 'menu-left-menu',
    'link_path' => 'topics',
    'router_path' => 'topics',
    'link_title' => 'Topics',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'menu-left-menu_topics:topics',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -47,
    'customized' => 1,
  );
  // Exported menu link: menu-left-menu_wiki:http://www.lacunastories.com/wiki
  $menu_links['menu-left-menu_wiki:http://www.lacunastories.com/wiki'] = array(
    'menu_name' => 'menu-left-menu',
    'link_path' => 'http://www.lacunastories.com/wiki',
    'router_path' => '',
    'link_title' => 'Wiki',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'menu-left-menu_wiki:http://www.lacunastories.com/wiki',
    ),
    'module' => 'menu',
    'hidden' => 1,
    'external' => 1,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -46,
    'customized' => 1,
  );
  // Exported menu link: menu-top-right_about-this-course:node/50
  $menu_links['menu-top-right_about-this-course:node/50'] = array(
    'menu_name' => 'menu-top-right',
    'link_path' => 'node/50',
    'router_path' => 'node/%',
    'link_title' => 'About this Course',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'menu-top-right_about-this-course:node/50',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -50,
    'customized' => 1,
  );
  // Exported menu link: menu-top-right_logout:user/logout
  $menu_links['menu-top-right_logout:user/logout'] = array(
    'menu_name' => 'menu-top-right',
    'link_path' => 'user/logout',
    'router_path' => 'user/logout',
    'link_title' => 'Logout',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'alter' => TRUE,
      'identifier' => 'menu-top-right_logout:user/logout',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -48,
    'customized' => 1,
  );
  // Exported menu link: menu-top-right_my-account:user
  $menu_links['menu-top-right_my-account:user'] = array(
    'menu_name' => 'menu-top-right',
    'link_path' => 'user',
    'router_path' => 'user',
    'link_title' => 'My Account',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'alter' => TRUE,
      'identifier' => 'menu-top-right_my-account:user',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -49,
    'customized' => 1,
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('About this Course');
  t('Bibliography');
  t('Dashboard');
  t('Forum');
  t('Instructor Dashboard');
  t('Logout');
  t('Materials');
  t('My Account');
  t('My Writing');
  t('Responses');
  t('Topics');
  t('Wiki');


  return $menu_links;
}
