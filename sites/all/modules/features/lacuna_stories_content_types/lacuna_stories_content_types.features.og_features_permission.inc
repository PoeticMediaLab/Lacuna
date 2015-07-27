<?php
/**
 * @file
 * lacuna_stories_content_types.features.og_features_permission.inc
 */

/**
 * Implements hook_og_features_default_permissions().
 */
function lacuna_stories_content_types_og_features_default_permissions() {
  $permissions = array();

  // Exported og permission: 'node:course:create response content'
  $permissions['node:course:create response content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:course:delete any response content'
  $permissions['node:course:delete any response content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:course:delete own response content'
  $permissions['node:course:delete own response content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:course:publish any response content'
  $permissions['node:course:publish any response content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:course:publish editable response content'
  $permissions['node:course:publish editable response content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:course:publish own response content'
  $permissions['node:course:publish own response content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:course:unpublish any response content'
  $permissions['node:course:unpublish any response content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:course:unpublish editable response content'
  $permissions['node:course:unpublish editable response content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:course:unpublish own response content'
  $permissions['node:course:unpublish own response content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:course:update any response content'
  $permissions['node:course:update any response content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:course:update own response content'
  $permissions['node:course:update own response content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:peer_group:create response content'
  $permissions['node:peer_group:create response content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:peer_group:delete any response content'
  $permissions['node:peer_group:delete any response content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:peer_group:delete own response content'
  $permissions['node:peer_group:delete own response content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:peer_group:publish any response content'
  $permissions['node:peer_group:publish any response content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:peer_group:publish editable response content'
  $permissions['node:peer_group:publish editable response content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:peer_group:publish own response content'
  $permissions['node:peer_group:publish own response content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:peer_group:unpublish any response content'
  $permissions['node:peer_group:unpublish any response content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:peer_group:unpublish editable response content'
  $permissions['node:peer_group:unpublish editable response content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:peer_group:unpublish own response content'
  $permissions['node:peer_group:unpublish own response content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:peer_group:update any response content'
  $permissions['node:peer_group:update any response content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:peer_group:update own response content'
  $permissions['node:peer_group:update own response content'] = array(
    'roles' => array(),
  );

  return $permissions;
}
