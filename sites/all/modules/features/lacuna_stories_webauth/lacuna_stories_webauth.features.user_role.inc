<?php
/**
 * @file
 * lacuna_stories_webauth.features.user_role.inc
 */

/**
 * Implements hook_user_default_roles().
 */
function lacuna_stories_webauth_user_default_roles() {
  $roles = array();

  // Exported role: SUNet User.
  $roles['SUNet User'] = array(
    'name' => 'SUNet User',
    'weight' => 0,
  );

  return $roles;
}
