<?php
/**
 * @file
 * lacuna_stories_permissions.features.user_role.inc
 */

/**
 * Implements hook_user_default_roles().
 */
function lacuna_stories_permissions_user_default_roles() {
  $roles = array();

  // Exported role: Content Manager.
  $roles['Content Manager'] = array(
    'name' => 'Content Manager',
    'weight' => 3,
  );

  // Exported role: Instructor.
  $roles['Instructor'] = array(
    'name' => 'Instructor',
    'weight' => 4,
  );

  // Exported role: Student.
  $roles['Student'] = array(
    'name' => 'Student',
    'weight' => 6,
  );

  // Exported role: administrator.
  $roles['administrator'] = array(
    'name' => 'administrator',
    'weight' => 2,
  );

  return $roles;
}
