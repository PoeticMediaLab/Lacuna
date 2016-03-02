<?php
/**
 * @file
 * lacuna_stories_annotations.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function lacuna_stories_annotations_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'administer annotations'.
  $permissions['administer annotations'] = array(
    'name' => 'administer annotations',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'Site Administrator' => 'Site Administrator',
    ),
    'module' => 'annotator',
  );

  // Exported permission: 'create annotation content'.
  $permissions['create annotation content'] = array(
    'name' => 'create annotation content',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'Instructor' => 'Instructor',
      'Site Administrator' => 'Site Administrator',
      'Student' => 'Student',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create annotations'.
  $permissions['create annotations'] = array(
    'name' => 'create annotations',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'Instructor' => 'Instructor',
      'Site Administrator' => 'Site Administrator',
      'Student' => 'Student',
    ),
    'module' => 'annotator',
  );

  // Exported permission: 'delete any annotation content'.
  $permissions['delete any annotation content'] = array(
    'name' => 'delete any annotation content',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'Site Administrator' => 'Site Administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own annotation content'.
  $permissions['delete own annotation content'] = array(
    'name' => 'delete own annotation content',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'Site Administrator' => 'Site Administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete terms in annotation_categories'.
  $permissions['delete terms in annotation_categories'] = array(
    'name' => 'delete terms in annotation_categories',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'Site Administrator' => 'Site Administrator',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: 'edit any annotation content'.
  $permissions['edit any annotation content'] = array(
    'name' => 'edit any annotation content',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'Site Administrator' => 'Site Administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any annotations'.
  $permissions['edit any annotations'] = array(
    'name' => 'edit any annotations',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'Site Administrator' => 'Site Administrator',
    ),
    'module' => 'annotator',
  );

  // Exported permission: 'edit own annotation content'.
  $permissions['edit own annotation content'] = array(
    'name' => 'edit own annotation content',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'Site Administrator' => 'Site Administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own annotations'.
  $permissions['edit own annotations'] = array(
    'name' => 'edit own annotations',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'Instructor' => 'Instructor',
      'Site Administrator' => 'Site Administrator',
      'Student' => 'Student',
    ),
    'module' => 'annotator',
  );

  // Exported permission: 'edit terms in annotation_categories'.
  $permissions['edit terms in annotation_categories'] = array(
    'name' => 'edit terms in annotation_categories',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'Site Administrator' => 'Site Administrator',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: 'publish any annotation content'.
  $permissions['publish any annotation content'] = array(
    'name' => 'publish any annotation content',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'Site Administrator' => 'Site Administrator',
    ),
    'module' => 'publishcontent',
  );

  // Exported permission: 'publish editable annotation content'.
  $permissions['publish editable annotation content'] = array(
    'name' => 'publish editable annotation content',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'Site Administrator' => 'Site Administrator',
    ),
    'module' => 'publishcontent',
  );

  // Exported permission: 'publish own annotation content'.
  $permissions['publish own annotation content'] = array(
    'name' => 'publish own annotation content',
    'roles' => array(
      'Site Administrator' => 'Site Administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'publishcontent',
  );

  // Exported permission: 'unpublish any annotation content'.
  $permissions['unpublish any annotation content'] = array(
    'name' => 'unpublish any annotation content',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'Site Administrator' => 'Site Administrator',
    ),
    'module' => 'publishcontent',
  );

  // Exported permission: 'unpublish editable annotation content'.
  $permissions['unpublish editable annotation content'] = array(
    'name' => 'unpublish editable annotation content',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'Site Administrator' => 'Site Administrator',
    ),
    'module' => 'publishcontent',
  );

  // Exported permission: 'unpublish own annotation content'.
  $permissions['unpublish own annotation content'] = array(
    'name' => 'unpublish own annotation content',
    'roles' => array(
      'Site Administrator' => 'Site Administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'publishcontent',
  );

  // Exported permission: 'view annotations'.
  $permissions['view annotations'] = array(
    'name' => 'view annotations',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'Instructor' => 'Instructor',
      'Site Administrator' => 'Site Administrator',
      'Student' => 'Student',
    ),
    'module' => 'annotator',
  );

  return $permissions;
}
