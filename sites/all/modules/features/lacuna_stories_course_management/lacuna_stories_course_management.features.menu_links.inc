<?php
/**
 * @file
 * lacuna_stories_course_management.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function lacuna_stories_course_management_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: main-menu_add-materials:course-setup/add-materials.
  $menu_links['main-menu_add-materials:course-setup/add-materials'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'course-setup/add-materials',
    'router_path' => 'course-setup/add-materials',
    'link_title' => 'Add Materials',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'main-menu_add-materials:course-setup/add-materials',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -50,
    'customized' => 1,
    'parent_identifier' => 'main-menu_manage:<nolink>/node/add/course',
  );
  // Exported menu link: main-menu_all-content:all-content.
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
    'weight' => -47,
    'customized' => 1,
    'parent_identifier' => 'main-menu_manage:<nolink>/node/add/course',
  );
  // Exported menu link: main-menu_all-emails:all-emails.
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
    'weight' => -48,
    'customized' => 1,
    'parent_identifier' => 'main-menu_manage-users:<nolink>',
  );
  // Exported menu link: main-menu_bulk-update-annotations:bulk-update-annotations.
  $menu_links['main-menu_bulk-update-annotations:bulk-update-annotations'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'bulk-update-annotations',
    'router_path' => 'bulk-update-annotations',
    'link_title' => 'Bulk Update Annotations',
    'options' => array(
      'identifier' => 'main-menu_bulk-update-annotations:bulk-update-annotations',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -45,
    'customized' => 1,
    'parent_identifier' => 'main-menu_manage:<nolink>/node/add/course',
  );
  // Exported menu link: main-menu_curate-tags:curate-tags.
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
    'parent_identifier' => 'main-menu_manage:<nolink>/node/add/course',
  );
  // Exported menu link: main-menu_manage-enrollment:manage-enrollment.
  $menu_links['main-menu_manage-enrollment:manage-enrollment'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'manage-enrollment',
    'router_path' => 'manage-enrollment',
    'link_title' => 'Manage Enrollment',
    'options' => array(
      'identifier' => 'main-menu_manage-enrollment:manage-enrollment',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -50,
    'customized' => 1,
    'parent_identifier' => 'main-menu_manage-users:<nolink>',
  );
  // Exported menu link: main-menu_manage-users:<nolink>.
  $menu_links['main-menu_manage-users:<nolink>'] = array(
    'menu_name' => 'main-menu',
    'link_path' => '<nolink>',
    'router_path' => '<nolink>',
    'link_title' => 'Manage Users',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'main-menu_manage-users:<nolink>',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => -44,
    'customized' => 1,
    'parent_identifier' => 'main-menu_manage:<nolink>/node/add/course',
  );
  // Exported menu link: main-menu_manage:<nolink>/node/add/course.
  $menu_links['main-menu_manage:<nolink>/node/add/course'] = array(
    'menu_name' => 'main-menu',
    'link_path' => '<nolink>/node/add/course',
    'router_path' => '<nolink>/%/%',
    'link_title' => 'Manage',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'main-menu_manage:<nolink>/node/add/course',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => -45,
    'customized' => 1,
  );
  // Exported menu link: main-menu_organize-materials:course-setup/organize.
  $menu_links['main-menu_organize-materials:course-setup/organize'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'course-setup/organize',
    'router_path' => 'course-setup/organize',
    'link_title' => 'Organize Materials',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'main-menu_organize-materials:course-setup/organize',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -49,
    'customized' => 1,
    'parent_identifier' => 'main-menu_manage:<nolink>/node/add/course',
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Add Materials');
  t('All Content');
  t('All Emails');
  t('Bulk Update Annotations');
  t('Curate Tags');
  t('Manage');
  t('Manage Enrollment');
  t('Manage Users');
  t('Organize Materials');

  return $menu_links;
}
