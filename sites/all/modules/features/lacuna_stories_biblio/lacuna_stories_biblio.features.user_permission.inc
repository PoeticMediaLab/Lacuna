<?php
/**
 * @file
 * lacuna_stories_biblio.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function lacuna_stories_biblio_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'access biblio content'.
  $permissions['access biblio content'] = array(
    'name' => 'access biblio content',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'Instructor' => 'Instructor',
      'Site Administrator' => 'Site Administrator',
      'Student' => 'Student',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'biblio',
  );

  // Exported permission: 'administer biblio'.
  $permissions['administer biblio'] = array(
    'name' => 'administer biblio',
    'roles' => array(
      'Site Administrator' => 'Site Administrator',
    ),
    'module' => 'biblio',
  );

  // Exported permission: 'edit biblio authors'.
  $permissions['edit biblio authors'] = array(
    'name' => 'edit biblio authors',
    'roles' => array(
      'Site Administrator' => 'Site Administrator',
    ),
    'module' => 'biblio',
  );

  // Exported permission: 'edit by all biblio authors'.
  $permissions['edit by all biblio authors'] = array(
    'name' => 'edit by all biblio authors',
    'roles' => array(
      'Site Administrator' => 'Site Administrator',
    ),
    'module' => 'biblio',
  );

  // Exported permission: 'import from file'.
  $permissions['import from file'] = array(
    'name' => 'import from file',
    'roles' => array(
      'Site Administrator' => 'Site Administrator',
    ),
    'module' => 'biblio',
  );

  // Exported permission: 'show download links'.
  $permissions['show download links'] = array(
    'name' => 'show download links',
    'roles' => array(
      'Site Administrator' => 'Site Administrator',
    ),
    'module' => 'biblio',
  );

  // Exported permission: 'show export links'.
  $permissions['show export links'] = array(
    'name' => 'show export links',
    'roles' => array(
      'Site Administrator' => 'Site Administrator',
    ),
    'module' => 'biblio',
  );

  // Exported permission: 'show filter tab'.
  $permissions['show filter tab'] = array(
    'name' => 'show filter tab',
    'roles' => array(
      'Site Administrator' => 'Site Administrator',
    ),
    'module' => 'biblio',
  );

  // Exported permission: 'show own download links'.
  $permissions['show own download links'] = array(
    'name' => 'show own download links',
    'roles' => array(
      'Site Administrator' => 'Site Administrator',
    ),
    'module' => 'biblio',
  );

  // Exported permission: 'show sort links'.
  $permissions['show sort links'] = array(
    'name' => 'show sort links',
    'roles' => array(
      'Site Administrator' => 'Site Administrator',
    ),
    'module' => 'biblio',
  );

  // Exported permission: 'view full text'.
  $permissions['view full text'] = array(
    'name' => 'view full text',
    'roles' => array(
      'Site Administrator' => 'Site Administrator',
    ),
    'module' => 'biblio',
  );

  return $permissions;
}
