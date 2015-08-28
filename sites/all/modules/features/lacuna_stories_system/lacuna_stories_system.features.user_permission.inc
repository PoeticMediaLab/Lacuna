<?php
/**
 * @file
 * lacuna_stories_system.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function lacuna_stories_system_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'administer filters'.
  $permissions['administer filters'] = array(
    'name' => 'administer filters',
    'roles' => array(
      'Site Administrator' => 'Site Administrator',
      'administrator' => 'administrator',
    ),
    'module' => 'filter',
  );

  // Exported permission: 'use text format filtered_html'.
  $permissions['use text format filtered_html'] = array(
    'name' => 'use text format filtered_html',
    'roles' => array(
      'Site Administrator' => 'Site Administrator',
      'Student' => 'Student',
      'administrator' => 'administrator',
    ),
    'module' => 'filter',
  );

  // Exported permission: 'use text format full_html'.
  $permissions['use text format full_html'] = array(
    'name' => 'use text format full_html',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'Instructor' => 'Instructor',
      'Site Administrator' => 'Site Administrator',
      'administrator' => 'administrator',
    ),
    'module' => 'filter',
  );

  // Exported permission: 'use text format php_code'.
  $permissions['use text format php_code'] = array(
    'name' => 'use text format php_code',
    'roles' => array(
      'Site Administrator' => 'Site Administrator',
      'administrator' => 'administrator',
    ),
    'module' => 'filter',
  );

  return $permissions;
}
