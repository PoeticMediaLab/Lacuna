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
  // Exported menu link: main-menu_all-content:all-content
  $menu_links['main-menu_all-content:all-content'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'all-content',
    'router_path' => 'all-content',
    'link_title' => 'All Content',
    'options' => array(
      'identifier' => 'main-menu_all-content:all-content',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -50,
    'customized' => 1,
    'parent_identifier' => 'main-menu_manage:<nolink>',
  );
  // Exported menu link: main-menu_all-emails:all-emails
  $menu_links['main-menu_all-emails:all-emails'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'all-emails',
    'router_path' => 'all-emails',
    'link_title' => 'All Emails',
    'options' => array(
      'identifier' => 'main-menu_all-emails:all-emails',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -49,
    'customized' => 1,
    'parent_identifier' => 'main-menu_manage:<nolink>',
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
  // Exported menu link: main-menu_bulk-update-annotations:bulk-update-annotations
  $menu_links['main-menu_bulk-update-annotations:bulk-update-annotations'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'bulk-update-annotations',
    'router_path' => 'bulk-update-annotations',
    'link_title' => 'Bulk Update Annotations',
    'options' => array(
      'attributes' => array(
        'title' => 'Bulk add/remove annotations to/from courses you teach. ',
      ),
      'identifier' => 'main-menu_bulk-update-annotations:bulk-update-annotations',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
    'parent_identifier' => 'main-menu_manage:<nolink>',
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
  // Exported menu link: main-menu_contact:contact
  $menu_links['main-menu_contact:contact'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'contact',
    'router_path' => 'contact',
    'link_title' => 'Contact',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'main-menu_contact:contact',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -47,
    'customized' => 1,
    'parent_identifier' => 'main-menu_help:<nolink>',
  );
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
  // Exported menu link: main-menu_curate-tags:curate-tags
  $menu_links['main-menu_curate-tags:curate-tags'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'curate-tags',
    'router_path' => 'curate-tags',
    'link_title' => 'Curate Tags',
    'options' => array(
      'identifier' => 'main-menu_curate-tags:curate-tags',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -48,
    'customized' => 1,
    'parent_identifier' => 'main-menu_manage:<nolink>',
  );
  // Exported menu link: main-menu_digital-research-consent-form:node/1
  $menu_links['main-menu_digital-research-consent-form:node/1'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'node/1',
    'router_path' => 'node/%',
    'link_title' => 'Digital Research Consent Form',
    'options' => array(
      'identifier' => 'main-menu_digital-research-consent-form:node/1',
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
  // Exported menu link: main-menu_faq:node/3
  $menu_links['main-menu_faq:node/3'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'node/3',
    'router_path' => 'node/%',
    'link_title' => 'FAQ',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'main-menu_faq:node/3',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -50,
    'customized' => 1,
    'parent_identifier' => 'main-menu_help:<nolink>',
  );
  // Exported menu link: main-menu_help:<nolink>
  $menu_links['main-menu_help:<nolink>'] = array(
    'menu_name' => 'main-menu',
    'link_path' => '<nolink>',
    'router_path' => '<nolink>',
    'link_title' => 'Help',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'main-menu_help:<nolink>',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => -44,
    'customized' => 1,
  );
  // Exported menu link: main-menu_instructors-guide:node/4
  $menu_links['main-menu_instructors-guide:node/4'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'node/4',
    'router_path' => 'node/%',
    'link_title' => 'Instructor\'s Guide',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'main-menu_instructors-guide:node/4',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -48,
    'customized' => 1,
    'parent_identifier' => 'main-menu_help:<nolink>',
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
  // Exported menu link: main-menu_manage:<nolink>
  $menu_links['main-menu_manage:<nolink>'] = array(
    'menu_name' => 'main-menu',
    'link_path' => '<nolink>',
    'router_path' => '<nolink>',
    'link_title' => 'Manage',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'main-menu_manage:<nolink>',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => -45,
    'customized' => 1,
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
  // Exported menu link: main-menu_peer-groups:peer-groups
  $menu_links['main-menu_peer-groups:peer-groups'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'peer-groups',
    'router_path' => 'peer-groups',
    'link_title' => 'Peer Groups',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'main-menu_peer-groups:peer-groups',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -47,
    'customized' => 1,
    'parent_identifier' => 'main-menu_connect:<nolink>',
  );
  // Exported menu link: main-menu_people:people
  $menu_links['main-menu_people:people'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'people',
    'router_path' => 'people',
    'link_title' => 'People',
    'options' => array(
      'identifier' => 'main-menu_people:people',
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
    'weight' => -49,
    'customized' => 1,
    'parent_identifier' => 'main-menu_connect:<nolink>',
  );
  // Exported menu link: main-menu_student-user-guide:node/5
  $menu_links['main-menu_student-user-guide:node/5'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'node/5',
    'router_path' => 'node/%',
    'link_title' => 'Student User Guide',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'main-menu_student-user-guide:node/5',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -49,
    'customized' => 1,
    'parent_identifier' => 'main-menu_help:<nolink>',
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
    'weight' => -48,
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
  // Exported menu link: menu-institutional-menu_about:http://lacunastories.com/
  $menu_links['menu-institutional-menu_about:http://lacunastories.com/'] = array(
    'menu_name' => 'menu-institutional-menu',
    'link_path' => 'http://lacunastories.com/',
    'router_path' => '',
    'link_title' => 'About',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'menu-institutional-menu_about:http://lacunastories.com/',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 1,
    'has_children' => 0,
    'expanded' => 1,
    'weight' => -50,
    'customized' => 1,
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
  // Exported menu link: menu-institutional-menu_log-in:user/login
  $menu_links['menu-institutional-menu_log-in:user/login'] = array(
    'menu_name' => 'menu-institutional-menu',
    'link_path' => 'user/login',
    'router_path' => 'user/login',
    'link_title' => 'Log In',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'menu-institutional-menu_log-in:user/login',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
  );
  // Exported menu link: menu-institutional-menu_log-out:user/logout
  $menu_links['menu-institutional-menu_log-out:user/logout'] = array(
    'menu_name' => 'menu-institutional-menu',
    'link_path' => 'user/logout',
    'router_path' => 'user/logout',
    'link_title' => 'Log Out',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'menu-institutional-menu_log-out:user/logout',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
  );
  // Exported menu link: menu-institutional-menu_register:user/register
  $menu_links['menu-institutional-menu_register:user/register'] = array(
    'menu_name' => 'menu-institutional-menu',
    'link_path' => 'user/register',
    'router_path' => 'user/register',
    'link_title' => 'Register',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'menu-institutional-menu_register:user/register',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('About');
  t('About This Course');
  t('Account');
  t('All Content');
  t('All Emails');
  t('Annotations Dashboard');
  t('Bulk Update Annotations');
  t('Connect');
  t('Contact');
  t('Courses');
  t('Create');
  t('Curate Tags');
  t('Digital Research Consent Form');
  t('Explore');
  t('FAQ');
  t('Help');
  t('Instructor\'s Guide');
  t('Log In');
  t('Log Out');
  t('Logout');
  t('Manage');
  t('Materials');
  t('My Profile');
  t('My Writing');
  t('Peer Groups');
  t('People');
  t('Reflect');
  t('Register');
  t('Responses');
  t('Responses Map');
  t('Sewing Kit');
  t('Student User Guide');
  t('Threads');
  t('Write a Response');


  return $menu_links;
}
