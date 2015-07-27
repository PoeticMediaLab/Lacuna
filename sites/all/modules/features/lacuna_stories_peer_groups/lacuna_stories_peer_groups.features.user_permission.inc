<?php
/**
 * @file
 * lacuna_stories_peer_groups.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function lacuna_stories_peer_groups_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'create peer_group content'.
  $permissions['create peer_group content'] = array(
    'name' => 'create peer_group content',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'Instructor' => 'Instructor',
      'Site Administrator' => 'Site Administrator',
      'Student' => 'Student',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any peer_group content'.
  $permissions['delete any peer_group content'] = array(
    'name' => 'delete any peer_group content',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'Site Administrator' => 'Site Administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own peer_group content'.
  $permissions['delete own peer_group content'] = array(
    'name' => 'delete own peer_group content',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'Site Administrator' => 'Site Administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any peer_group content'.
  $permissions['edit any peer_group content'] = array(
    'name' => 'edit any peer_group content',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'Site Administrator' => 'Site Administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own peer_group content'.
  $permissions['edit own peer_group content'] = array(
    'name' => 'edit own peer_group content',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'Site Administrator' => 'Site Administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  return $permissions;
}
