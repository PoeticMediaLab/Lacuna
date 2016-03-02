<?php
/**
 * @file
 * course.features.og_features_permission.inc
 */

/**
 * Implements hook_og_features_default_permissions().
 */
function course_og_features_default_permissions() {
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

  // Exported og permission: 'node:course:create annotation content'
  $permissions['node:course:create annotation content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:course:create document content'
  $permissions['node:course:create document content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:course:create response content'
  $permissions['node:course:create response content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:course:create thread content'
  $permissions['node:course:create thread content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:course:delete any annotation content'
  $permissions['node:course:delete any annotation content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:course:delete any document content'
  $permissions['node:course:delete any document content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:course:delete any response content'
  $permissions['node:course:delete any response content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:course:delete any thread content'
  $permissions['node:course:delete any thread content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:course:delete own annotation content'
  $permissions['node:course:delete own annotation content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:course:delete own document content'
  $permissions['node:course:delete own document content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:course:delete own response content'
  $permissions['node:course:delete own response content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:course:delete own thread content'
  $permissions['node:course:delete own thread content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
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
    'roles' => array(),
  );

  // Exported og permission: 'node:course:publish any annotation content'
  $permissions['node:course:publish any annotation content'] = array(
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

  // Exported og permission: 'node:course:publish any thread content'
  $permissions['node:course:publish any thread content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:course:publish editable annotation content'
  $permissions['node:course:publish editable annotation content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:course:publish editable content'
  $permissions['node:course:publish editable content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:course:publish editable thread content'
  $permissions['node:course:publish editable thread content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:course:publish own annotation content'
  $permissions['node:course:publish own annotation content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:course:publish own thread content'
  $permissions['node:course:publish own thread content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'member' => 'member',
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

  // Exported og permission: 'node:course:unpublish any annotation content'
  $permissions['node:course:unpublish any annotation content'] = array(
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

  // Exported og permission: 'node:course:unpublish any thread content'
  $permissions['node:course:unpublish any thread content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:course:unpublish editable annotation content'
  $permissions['node:course:unpublish editable annotation content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:course:unpublish editable content'
  $permissions['node:course:unpublish editable content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:course:unpublish editable thread content'
  $permissions['node:course:unpublish editable thread content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:course:unpublish own annotation content'
  $permissions['node:course:unpublish own annotation content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:course:unpublish own thread content'
  $permissions['node:course:unpublish own thread content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:course:unsubscribe'
  $permissions['node:course:unsubscribe'] = array(
    'roles' => array(
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:course:update any annotation content'
  $permissions['node:course:update any annotation content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:course:update any document content'
  $permissions['node:course:update any document content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:course:update any response content'
  $permissions['node:course:update any response content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:course:update any thread content'
  $permissions['node:course:update any thread content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:course:update group'
  $permissions['node:course:update group'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:course:update own annotation content'
  $permissions['node:course:update own annotation content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:course:update own document content'
  $permissions['node:course:update own document content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:course:update own response content'
  $permissions['node:course:update own response content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:course:update own thread content'
  $permissions['node:course:update own thread content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  return $permissions;
}
