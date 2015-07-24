<?php
/**
 * @file
 * lacuna_stories_content_types.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function lacuna_stories_content_types_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'create response content'.
  $permissions['create response content'] = array(
    'name' => 'create response content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'delete any response content'.
  $permissions['delete any response content'] = array(
    'name' => 'delete any response content',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'Site Administrator' => 'Site Administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own response content'.
  $permissions['delete own response content'] = array(
    'name' => 'delete own response content',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'Site Administrator' => 'Site Administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any response content'.
  $permissions['edit any response content'] = array(
    'name' => 'edit any response content',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'Site Administrator' => 'Site Administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own response content'.
  $permissions['edit own response content'] = array(
    'name' => 'edit own response content',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'Site Administrator' => 'Site Administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  return $permissions;
}
