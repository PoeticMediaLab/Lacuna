<?php
/**
 * @file
 * lacuna_stories_permissions.features.og_features_permission.inc
 */

/**
 * Implements hook_og_features_default_permissions().
 */
function lacuna_stories_permissions_og_features_default_permissions() {
  $permissions = array();

  // Exported og permission: 'node:course:add user'
  $permissions['node:course:add user'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:course:administer group'
  $permissions['node:course:administer group'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:course:approve and deny subscription'
  $permissions['node:course:approve and deny subscription'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:course:create blog content'
  $permissions['node:course:create blog content'] = array(
    'roles' => array(
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:course:delete any blog content'
  $permissions['node:course:delete any blog content'] = array(
    'roles' => array(
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:course:delete own blog content'
  $permissions['node:course:delete own blog content'] = array(
    'roles' => array(
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:course:manage members'
  $permissions['node:course:manage members'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:course:manage permissions'
  $permissions['node:course:manage permissions'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:course:manage roles'
  $permissions['node:course:manage roles'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:course:publish any blog content'
  $permissions['node:course:publish any blog content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:course:publish any content'
  $permissions['node:course:publish any content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:course:publish editable blog content'
  $permissions['node:course:publish editable blog content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:course:publish editable content'
  $permissions['node:course:publish editable content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:course:publish own blog content'
  $permissions['node:course:publish own blog content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:course:subscribe'
  $permissions['node:course:subscribe'] = array(
    'roles' => array(
      'non-member' => 'non-member',
    ),
  );

  // Exported og permission: 'node:course:subscribe without approval'
  $permissions['node:course:subscribe without approval'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:course:unpublish any blog content'
  $permissions['node:course:unpublish any blog content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:course:unpublish any content'
  $permissions['node:course:unpublish any content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:course:unpublish editable blog content'
  $permissions['node:course:unpublish editable blog content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:course:unpublish editable content'
  $permissions['node:course:unpublish editable content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:course:unpublish own blog content'
  $permissions['node:course:unpublish own blog content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:course:unsubscribe'
  $permissions['node:course:unsubscribe'] = array(
    'roles' => array(
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:course:update any blog content'
  $permissions['node:course:update any blog content'] = array(
    'roles' => array(
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:course:update group'
  $permissions['node:course:update group'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:course:update own blog content'
  $permissions['node:course:update own blog content'] = array(
    'roles' => array(
      'member' => 'member',
    ),
  );

  return $permissions;
}
