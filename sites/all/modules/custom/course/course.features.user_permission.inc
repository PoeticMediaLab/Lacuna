<?php
/**
 * @file
 * course.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function course_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'create course content'.
  $permissions['create course content'] = array(
    'name' => 'create course content',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'Instructor' => 'Instructor',
      'Site Administrator' => 'Site Administrator',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create og_user_node'.
  $permissions['create og_user_node'] = array(
    'name' => 'create og_user_node',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'Instructor' => 'Instructor',
      'Site Administrator' => 'Site Administrator',
      'administrator' => 'administrator',
      'anonymous user' => 'anonymous user',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'delete any course content'.
  $permissions['delete any course content'] = array(
    'name' => 'delete any course content',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'Site Administrator' => 'Site Administrator',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own course content'.
  $permissions['delete own course content'] = array(
    'name' => 'delete own course content',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'Site Administrator' => 'Site Administrator',
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any course content'.
  $permissions['edit any course content'] = array(
    'name' => 'edit any course content',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'Site Administrator' => 'Site Administrator',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit og_user_node'.
  $permissions['edit og_user_node'] = array(
    'name' => 'edit og_user_node',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'Site Administrator' => 'Site Administrator',
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit own course content'.
  $permissions['edit own course content'] = array(
    'name' => 'edit own course content',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'Instructor' => 'Instructor',
      'Site Administrator' => 'Site Administrator',
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own og_user_node'.
  $permissions['edit own og_user_node'] = array(
    'name' => 'edit own og_user_node',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'Instructor' => 'Instructor',
      'Site Administrator' => 'Site Administrator',
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view og_user_node'.
  $permissions['view og_user_node'] = array(
    'name' => 'view og_user_node',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'Site Administrator' => 'Site Administrator',
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view own og_user_node'.
  $permissions['view own og_user_node'] = array(
    'name' => 'view own og_user_node',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'Instructor' => 'Instructor',
      'Site Administrator' => 'Site Administrator',
      'Student' => 'Student',
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'field_permissions',
  );

  return $permissions;
}
