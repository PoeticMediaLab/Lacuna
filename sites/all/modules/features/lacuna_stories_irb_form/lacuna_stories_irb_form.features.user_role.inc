<?php
/**
 * @file
 * lacuna_stories_irb_form.features.user_role.inc
 */

/**
 * Implements hook_user_default_roles().
 */
function lacuna_stories_irb_form_user_default_roles() {
  $roles = array();

  // Exported role: Researcher.
  $roles['Researcher'] = array(
    'name' => 'Researcher',
    'weight' => 11,
  );

  return $roles;
}
