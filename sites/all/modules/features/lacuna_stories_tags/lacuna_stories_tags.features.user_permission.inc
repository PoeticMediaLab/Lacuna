<?php
/**
 * @file
 * lacuna_stories_tags.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function lacuna_stories_tags_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'delete terms in annotation_tags'.
  $permissions['delete terms in annotation_tags'] = array(
    'name' => 'delete terms in annotation_tags',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'Site Administrator' => 'Site Administrator',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: 'edit terms in annotation_tags'.
  $permissions['edit terms in annotation_tags'] = array(
    'name' => 'edit terms in annotation_tags',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'Instructor' => 'Instructor',
      'Site Administrator' => 'Site Administrator',
      'Student' => 'Student',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: 'flag curated_tag'.
  $permissions['flag curated_tag'] = array(
    'name' => 'flag curated_tag',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'Instructor' => 'Instructor',
      'Site Administrator' => 'Site Administrator',
    ),
    'module' => 'flag',
  );

  // Exported permission: 'unflag curated_tag'.
  $permissions['unflag curated_tag'] = array(
    'name' => 'unflag curated_tag',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'Instructor' => 'Instructor',
      'Site Administrator' => 'Site Administrator',
    ),
    'module' => 'flag',
  );

  return $permissions;
}
