<?php
/**
 * @file
 * lacuna_stories_materials.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function lacuna_stories_materials_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'create document content'.
  $permissions['create document content'] = array(
    'name' => 'create document content',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'Instructor' => 'Instructor',
      'Site Administrator' => 'Site Administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create field_media'.
  $permissions['create field_media'] = array(
    'name' => 'create field_media',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'Instructor' => 'Instructor',
      'Site Administrator' => 'Site Administrator',
      'Student' => 'Student',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'create field_status'.
  $permissions['create field_status'] = array(
    'name' => 'create field_status',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'Instructor' => 'Instructor',
      'Site Administrator' => 'Site Administrator',
      'Student' => 'Student',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'delete any document content'.
  $permissions['delete any document content'] = array(
    'name' => 'delete any document content',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'Site Administrator' => 'Site Administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own document content'.
  $permissions['delete own document content'] = array(
    'name' => 'delete own document content',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'Site Administrator' => 'Site Administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete terms in genre_doc'.
  $permissions['delete terms in genre_doc'] = array(
    'name' => 'delete terms in genre_doc',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'Instructor' => 'Instructor',
      'Site Administrator' => 'Site Administrator',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: 'delete terms in medium'.
  $permissions['delete terms in medium'] = array(
    'name' => 'delete terms in medium',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'Site Administrator' => 'Site Administrator',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: 'delete terms in priority'.
  $permissions['delete terms in priority'] = array(
    'name' => 'delete terms in priority',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'Site Administrator' => 'Site Administrator',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: 'delete terms in units'.
  $permissions['delete terms in units'] = array(
    'name' => 'delete terms in units',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'Instructor' => 'Instructor',
      'Site Administrator' => 'Site Administrator',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: 'edit any document content'.
  $permissions['edit any document content'] = array(
    'name' => 'edit any document content',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'Site Administrator' => 'Site Administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit field_media'.
  $permissions['edit field_media'] = array(
    'name' => 'edit field_media',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'Instructor' => 'Instructor',
      'Site Administrator' => 'Site Administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit field_status'.
  $permissions['edit field_status'] = array(
    'name' => 'edit field_status',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'Site Administrator' => 'Site Administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit own document content'.
  $permissions['edit own document content'] = array(
    'name' => 'edit own document content',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'Site Administrator' => 'Site Administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own field_media'.
  $permissions['edit own field_media'] = array(
    'name' => 'edit own field_media',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'Instructor' => 'Instructor',
      'Site Administrator' => 'Site Administrator',
      'Student' => 'Student',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit own field_status'.
  $permissions['edit own field_status'] = array(
    'name' => 'edit own field_status',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'Instructor' => 'Instructor',
      'Site Administrator' => 'Site Administrator',
      'Student' => 'Student',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit terms in genre_doc'.
  $permissions['edit terms in genre_doc'] = array(
    'name' => 'edit terms in genre_doc',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'Instructor' => 'Instructor',
      'Site Administrator' => 'Site Administrator',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: 'edit terms in medium'.
  $permissions['edit terms in medium'] = array(
    'name' => 'edit terms in medium',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'Site Administrator' => 'Site Administrator',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: 'edit terms in priority'.
  $permissions['edit terms in priority'] = array(
    'name' => 'edit terms in priority',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'Site Administrator' => 'Site Administrator',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: 'edit terms in units'.
  $permissions['edit terms in units'] = array(
    'name' => 'edit terms in units',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'Instructor' => 'Instructor',
      'Site Administrator' => 'Site Administrator',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: 'view field_media'.
  $permissions['view field_media'] = array(
    'name' => 'view field_media',
    'roles' => array(
      'Site Administrator' => 'Site Administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view field_status'.
  $permissions['view field_status'] = array(
    'name' => 'view field_status',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'Site Administrator' => 'Site Administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view own field_media'.
  $permissions['view own field_media'] = array(
    'name' => 'view own field_media',
    'roles' => array(
      'Site Administrator' => 'Site Administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view own field_status'.
  $permissions['view own field_status'] = array(
    'name' => 'view own field_status',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'Instructor' => 'Instructor',
      'Site Administrator' => 'Site Administrator',
      'Student' => 'Student',
    ),
    'module' => 'field_permissions',
  );

  return $permissions;
}
