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

  // Exported permission: 'administer exclude node title'.
  $permissions['administer exclude node title'] = array(
    'name' => 'administer exclude node title',
    'roles' => array(
      'Site Administrator' => 'Site Administrator',
    ),
    'module' => 'exclude_node_title',
  );

  // Exported permission: 'create course content'.
  $permissions['create course content'] = array(
    'name' => 'create course content',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'Instructor' => 'Instructor',
      'Site Administrator' => 'Site Administrator',
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
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own course content'.
  $permissions['delete own course content'] = array(
    'name' => 'delete own course content',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'Site Administrator' => 'Site Administrator',
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
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit og_user_node'.
  $permissions['edit og_user_node'] = array(
    'name' => 'edit og_user_node',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'Site Administrator' => 'Site Administrator',
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
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'exclude any node title'.
  $permissions['exclude any node title'] = array(
    'name' => 'exclude any node title',
    'roles' => array(
      'Site Administrator' => 'Site Administrator',
    ),
    'module' => 'exclude_node_title',
  );

  // Exported permission: 'exclude own node title'.
  $permissions['exclude own node title'] = array(
    'name' => 'exclude own node title',
    'roles' => array(
      'Site Administrator' => 'Site Administrator',
    ),
    'module' => 'exclude_node_title',
  );

  // Exported permission: 'use exclude node title'.
  $permissions['use exclude node title'] = array(
    'name' => 'use exclude node title',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'Instructor' => 'Instructor',
      'Researcher' => 'Researcher',
      'Site Administrator' => 'Site Administrator',
      'Student' => 'Student',
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'exclude_node_title',
  );

  // Exported permission: 'view og_user_node'.
  $permissions['view og_user_node'] = array(
    'name' => 'view og_user_node',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'Researcher' => 'Researcher',
      'Site Administrator' => 'Site Administrator',
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
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'field_permissions',
  );

  return $permissions;
}
