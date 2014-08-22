<?php
/**
 * @file
 * lacuna_stories.features.user_role.inc
 */

/**
 * Implements hook_user_default_roles().
 */
function lacuna_stories_user_default_roles() {
  $roles = array();

  // Exported role: Blogger.
  $roles['Blogger'] = array(
    'name' => 'Blogger',
    'weight' => 4,
  );

  // Exported role: Content Manager.
  $roles['Content Manager'] = array(
    'name' => 'Content Manager',
    'weight' => 3,
  );

  // Exported role: administrator.
  $roles['administrator'] = array(
    'name' => 'administrator',
    'weight' => 2,
  );

  return $roles;
}
