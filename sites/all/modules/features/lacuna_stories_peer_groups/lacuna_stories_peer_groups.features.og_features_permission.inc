<?php
/**
 * @file
 * lacuna_stories_peer_groups.features.og_features_permission.inc
 */

/**
 * Implements hook_og_features_default_permissions().
 */
function lacuna_stories_peer_groups_og_features_default_permissions() {
  $permissions = array();

  // Exported og permission: 'node:peer_group:add user'
  $permissions['node:peer_group:add user'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:peer_group:administer group'
  $permissions['node:peer_group:administer group'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:peer_group:approve and deny subscription'
  $permissions['node:peer_group:approve and deny subscription'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:peer_group:create annotation content'
  $permissions['node:peer_group:create annotation content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:peer_group:create document content'
  $permissions['node:peer_group:create document content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:peer_group:create response content'
  $permissions['node:peer_group:create response content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:peer_group:delete any annotation content'
  $permissions['node:peer_group:delete any annotation content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:peer_group:delete any document content'
  $permissions['node:peer_group:delete any document content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:peer_group:delete any response content'
  $permissions['node:peer_group:delete any response content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:peer_group:delete own annotation content'
  $permissions['node:peer_group:delete own annotation content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:peer_group:delete own document content'
  $permissions['node:peer_group:delete own document content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:peer_group:delete own response content'
  $permissions['node:peer_group:delete own response content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:peer_group:manage members'
  $permissions['node:peer_group:manage members'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:peer_group:manage permissions'
  $permissions['node:peer_group:manage permissions'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:peer_group:manage roles'
  $permissions['node:peer_group:manage roles'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:peer_group:publish any annotation content'
  $permissions['node:peer_group:publish any annotation content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:peer_group:publish any content'
  $permissions['node:peer_group:publish any content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:peer_group:publish any thread content'
  $permissions['node:peer_group:publish any thread content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:peer_group:publish editable annotation content'
  $permissions['node:peer_group:publish editable annotation content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:peer_group:publish editable content'
  $permissions['node:peer_group:publish editable content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:peer_group:publish editable thread content'
  $permissions['node:peer_group:publish editable thread content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:peer_group:publish own annotation content'
  $permissions['node:peer_group:publish own annotation content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:peer_group:publish own thread content'
  $permissions['node:peer_group:publish own thread content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:peer_group:subscribe'
  $permissions['node:peer_group:subscribe'] = array(
    'roles' => array(
      'non-member' => 'non-member',
    ),
  );

  // Exported og permission: 'node:peer_group:subscribe without approval'
  $permissions['node:peer_group:subscribe without approval'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:peer_group:unpublish any annotation content'
  $permissions['node:peer_group:unpublish any annotation content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:peer_group:unpublish any content'
  $permissions['node:peer_group:unpublish any content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:peer_group:unpublish any thread content'
  $permissions['node:peer_group:unpublish any thread content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:peer_group:unpublish editable annotation content'
  $permissions['node:peer_group:unpublish editable annotation content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:peer_group:unpublish editable content'
  $permissions['node:peer_group:unpublish editable content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:peer_group:unpublish editable thread content'
  $permissions['node:peer_group:unpublish editable thread content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:peer_group:unpublish own annotation content'
  $permissions['node:peer_group:unpublish own annotation content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:peer_group:unpublish own thread content'
  $permissions['node:peer_group:unpublish own thread content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:peer_group:unsubscribe'
  $permissions['node:peer_group:unsubscribe'] = array(
    'roles' => array(
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:peer_group:update any annotation content'
  $permissions['node:peer_group:update any annotation content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:peer_group:update any document content'
  $permissions['node:peer_group:update any document content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:peer_group:update any response content'
  $permissions['node:peer_group:update any response content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:peer_group:update group'
  $permissions['node:peer_group:update group'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:peer_group:update own annotation content'
  $permissions['node:peer_group:update own annotation content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:peer_group:update own document content'
  $permissions['node:peer_group:update own document content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:peer_group:update own response content'
  $permissions['node:peer_group:update own response content'] = array(
    'roles' => array(),
  );

  return $permissions;
}
