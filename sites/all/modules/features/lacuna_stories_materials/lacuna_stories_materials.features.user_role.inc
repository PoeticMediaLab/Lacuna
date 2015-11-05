<?php
/**
 * @file
 * lacuna_stories_materials.features.user_role.inc
 */

/**
 * Implements hook_user_default_roles().
 */
function lacuna_stories_materials_user_default_roles() {
  $roles = array();

  // Exported role: administrator.
  $roles['administrator'] = array(
    'name' => 'administrator',
    'weight' => 10,
  );

  return $roles;
}
