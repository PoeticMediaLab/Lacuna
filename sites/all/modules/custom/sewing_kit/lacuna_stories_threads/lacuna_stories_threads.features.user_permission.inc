<?php
/**
 * @file
 * lacuna_stories_threads.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function lacuna_stories_threads_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'access draggableviews'.
  $permissions['access draggableviews'] = array(
    'name' => 'access draggableviews',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'draggableviews',
  );

  // Exported permission: 'create thread content'.
  $permissions['create thread content'] = array(
    'name' => 'create thread content',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'Instructor' => 'Instructor',
      'Site Administrator' => 'Site Administrator',
      'Student' => 'Student',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any thread content'.
  $permissions['delete any thread content'] = array(
    'name' => 'delete any thread content',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'Site Administrator' => 'Site Administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own thread content'.
  $permissions['delete own thread content'] = array(
    'name' => 'delete own thread content',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'Instructor' => 'Instructor',
      'Site Administrator' => 'Site Administrator',
      'Student' => 'Student',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any thread content'.
  $permissions['edit any thread content'] = array(
    'name' => 'edit any thread content',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'Site Administrator' => 'Site Administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own thread content'.
  $permissions['edit own thread content'] = array(
    'name' => 'edit own thread content',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'Instructor' => 'Instructor',
      'Site Administrator' => 'Site Administrator',
      'Student' => 'Student',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: 'publish any thread content'.
  $permissions['publish any thread content'] = array(
    'name' => 'publish any thread content',
    'roles' => array(
      'Site Administrator' => 'Site Administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'publishcontent',
  );

  // Exported permission: 'publish editable thread content'.
  $permissions['publish editable thread content'] = array(
    'name' => 'publish editable thread content',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'Site Administrator' => 'Site Administrator',
    ),
    'module' => 'publishcontent',
  );

  // Exported permission: 'publish own thread content'.
  $permissions['publish own thread content'] = array(
    'name' => 'publish own thread content',
    'roles' => array(
      'Instructor' => 'Instructor',
      'Site Administrator' => 'Site Administrator',
      'Student' => 'Student',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'publishcontent',
  );

  // Exported permission: 'unpublish any thread content'.
  $permissions['unpublish any thread content'] = array(
    'name' => 'unpublish any thread content',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'Site Administrator' => 'Site Administrator',
    ),
    'module' => 'publishcontent',
  );

  // Exported permission: 'unpublish editable thread content'.
  $permissions['unpublish editable thread content'] = array(
    'name' => 'unpublish editable thread content',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'Site Administrator' => 'Site Administrator',
    ),
    'module' => 'publishcontent',
  );

  // Exported permission: 'unpublish own thread content'.
  $permissions['unpublish own thread content'] = array(
    'name' => 'unpublish own thread content',
    'roles' => array(
      'Instructor' => 'Instructor',
      'Site Administrator' => 'Site Administrator',
      'Student' => 'Student',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'publishcontent',
  );

  return $permissions;
}
