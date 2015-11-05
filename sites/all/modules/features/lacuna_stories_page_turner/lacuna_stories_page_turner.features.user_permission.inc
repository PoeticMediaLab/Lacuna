<?php
/**
 * @file
 * lacuna_stories_page_turner.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function lacuna_stories_page_turner_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'flag page_turner_bookmark'.
  $permissions['flag page_turner_bookmark'] = array(
    'name' => 'flag page_turner_bookmark',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'Instructor' => 'Instructor',
      'Site Administrator' => 'Site Administrator',
      'Student' => 'Student',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'flag',
  );

  // Exported permission: 'unflag page_turner_bookmark'.
  $permissions['unflag page_turner_bookmark'] = array(
    'name' => 'unflag page_turner_bookmark',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'Instructor' => 'Instructor',
      'Site Administrator' => 'Site Administrator',
      'Student' => 'Student',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'flag',
  );

  return $permissions;
}
