<?php

/***
 *
 * Set privacy on annotation nodes
 * Draws heavily on node_access_example.module
 * Translates the Annotator Permission module settings for each annotation
 * into access controls on the Annotation nodes themselves
 * so that Drupal will respect the user's preferences for each annotation
 *
 *
 *  Mike Widner <mikewidner@stanford.edu>
 *
 ***/

// @see http://www.phase2technology.com/blog/drupal-7-node-access-grants-locks-and-keys/
// Don't use hook_node_access()
// Use hook_node_grants()
// So that's what we're doing here
define('ANNOTATION_GRANT_ACCESS_ALL', 7);
function annotation_node_grants($account, $op) {
  $grants = array();
  // Grant users access to their own annotations
  if ($account->uid) {
    $grants['annotation_author'] = array($account->uid);
  }

  // If "access any private annotation" is allowed to the account,
  // grant view, update, or delete as necessary.
  if ($op == 'view' && user_access('access any private annotation', $account)) {
    $grants['annotation_view'] = array(ANNOTATION_GRANT_ACCESS_ALL);
  }

  if (($op == 'update' || $op == 'delete') && user_access('edit any private annotation', $account)) {
    $grants['annotation_edit'] = array(ANNOTATION_GRANT_ACCESS_ALL);
  }

  return $grants;
}

function annotation_node_access_records($node) {
  // We only care about the node if it's been marked private. If not, it is
  // treated just like any other node and we completely ignore it.
  // We're using list_boolean as our privacy setting field
  if (!empty($node->private) && $node->private[$node->language][0]['value'] == 1) {
    $grants = array();
    $grants[] = array(
      'realm' => 'annotation_view',
      'gid' => ANNOTATION_GRANT_ACCESS_ALL,
      'grant_view' => 1,
      'grant_update' => 0,
      'grant_delete' => 0,
      'priority' => 0,
    );
    $grants[] = array(
      'realm' => 'annotation_edit',
      'gid' => ANNOTATION_GRANT_ACCESS_ALL,
      'grant_view' => 1,
      'grant_update' => 1,
      'grant_delete' => 1,
      'priority' => 0,
    );

    // For the annotation_author realm, the grant ID (gid) is
    // equivalent to the node author's user ID (UID).
    // We check the node UID so that we don't grant author priviledges for
    // anonymous nodes to anonymous users.
    if ($node->uid) {
      $grants[] = array(
        'realm' => 'annotation_author',
        'gid' => $node->uid,
        'grant_view' => 1,
        'grant_update' => 1,
        'grant_delete' => 1,
        'priority' => 0,
      );
    }
    ddl($grants, 'grants');
    return $grants;
  }
  // Return nothing if the node has not been marked private.
}
