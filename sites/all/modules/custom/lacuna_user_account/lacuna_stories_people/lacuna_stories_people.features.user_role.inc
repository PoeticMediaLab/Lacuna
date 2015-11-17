<?php
/**
 * @file
 * lacuna_stories_people.features.user_role.inc
 */

/**
 * Implements hook_user_default_roles().
 */
function lacuna_stories_people_user_default_roles() {
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

  // Exported role: Pre-authorized User.
  $roles['Pre-authorized User'] = array(
    'name' => 'Pre-authorized User',
    'weight' => 12,
  );

  // Exported role: Researcher.
  $roles['Researcher'] = array(
    'name' => 'Researcher',
    'weight' => 11,
  );

  // Exported role: Site Administrator.
  $roles['Site Administrator'] = array(
    'name' => 'Site Administrator',
    'weight' => 2,
  );

  // Exported role: Student.
  $roles['Student'] = array(
    'name' => 'Student',
    'weight' => 6,
  );

  return $roles;
}
