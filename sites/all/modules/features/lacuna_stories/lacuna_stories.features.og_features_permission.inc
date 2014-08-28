<?php
/**
 * @file
 * lacuna_stories.features.og_features_permission.inc
 */

/**
 * Implements hook_og_features_default_permissions().
 */
function lacuna_stories_og_features_default_permissions() {
  $permissions = array();

  // Exported og permission: 'node:group:add user'
  $permissions['node:group:add user'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:group:administer group'
  $permissions['node:group:administer group'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:group:approve and deny subscription'
  $permissions['node:group:approve and deny subscription'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:group:create blog content'
  $permissions['node:group:create blog content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:group:create forum content'
  $permissions['node:group:create forum content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:group:create page content'
  $permissions['node:group:create page content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:group:delete any blog content'
  $permissions['node:group:delete any blog content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:group:delete any forum content'
  $permissions['node:group:delete any forum content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:group:delete any page content'
  $permissions['node:group:delete any page content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:group:delete own blog content'
  $permissions['node:group:delete own blog content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:group:delete own forum content'
  $permissions['node:group:delete own forum content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:group:delete own page content'
  $permissions['node:group:delete own page content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:group:manage members'
  $permissions['node:group:manage members'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:group:manage permissions'
  $permissions['node:group:manage permissions'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:group:manage roles'
  $permissions['node:group:manage roles'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:group:publish any content'
  $permissions['node:group:publish any content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:group:publish editable content'
  $permissions['node:group:publish editable content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:group:subscribe'
  $permissions['node:group:subscribe'] = array(
    'roles' => array(
      'non-member' => 'non-member',
    ),
  );

  // Exported og permission: 'node:group:subscribe without approval'
  $permissions['node:group:subscribe without approval'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:group:unpublish any content'
  $permissions['node:group:unpublish any content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:group:unpublish editable content'
  $permissions['node:group:unpublish editable content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:group:unsubscribe'
  $permissions['node:group:unsubscribe'] = array(
    'roles' => array(
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:group:update any blog content'
  $permissions['node:group:update any blog content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:group:update any forum content'
  $permissions['node:group:update any forum content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:group:update any page content'
  $permissions['node:group:update any page content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:group:update group'
  $permissions['node:group:update group'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:group:update own blog content'
  $permissions['node:group:update own blog content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:group:update own forum content'
  $permissions['node:group:update own forum content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:group:update own page content'
  $permissions['node:group:update own page content'] = array(
    'roles' => array(),
  );

  return $permissions;
}
