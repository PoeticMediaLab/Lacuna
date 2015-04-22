<?php

/**
 * @file
 * delete all Drush command
 */

/**
 * Implementation of hook_drush_command().
 */
function delete_all_drush_command() {
  $items = array();
  $items['delete-all'] = array(
    'callback' => 'delete_all_drush_delete',
    'description' => 'Delete all nodes, nodes of a specific content type or users.',
    'options' => array(
      'roles' => 'pick roles',
      'reset' => 'Reset counter for node, revision and comment tables.',
    ),
    'examples' => array(
      'drush delete-all article' => 'Delect all article nodes.',
      'drush delete-all all' => 'Delete nodes of all types.',
      'drush delete-all all --reset' => 'Delete nodes of all types, and reset node, revision and comment counters.',
      'drush delete-all users' => 'Delete users.',
     ),
    'aliases' => array('da'),
  );
  return $items;
}

/**
 * Implementation of hook_drush_help().
 */
function delete_all_drush_help($section) {
  switch ($section) {
    case 'drush:delete-all':
    return dt("Delete all nodes, nodes of a specific content type or users.");
  }
}

/**
 * Drush callback to delete content
 */
function delete_all_drush_delete() {
  $types = func_get_args();
  if ($types) {
    if (in_array('users', $types)) {
      if (!$types[1] && drush_get_option('roles')) {
        $choices = user_roles();
        $role = drush_choice($choices, dt("Choose a role to delete."));
        if ($role == 0) {
          return;
        }
      }
      else {
        $role = $types[1];
        if (strpos($role, ',')) {
          $role = explode(',', $role);
        }
      }
      drush_print('Deleted ' . delete_all_users_delete($role) . ' users');
    }
    elseif (in_array('all', $types)) {
      db_query("DELETE FROM {url_alias} WHERE source LIKE 'node/%%'");
      drush_print('Deleted ' . _delete_all_normal(TRUE, FALSE) . ' nodes');
      if (drush_get_option('reset')) {
        db_query("ALTER TABLE node AUTO_INCREMENT=1");
        db_query("ALTER TABLE node_revision AUTO_INCREMENT=1");
        if (module_exists('comment')) {
          db_query("ALTER TABLE comment AUTO_INCREMENT=1");
          drush_print('All node, revision and comment counts have been reset.');
        }
        else {
          drush_print('All node and revision counts have been reset.');
        }
      }
    }
    else {
      drush_print('Deleted ' . _delete_all_normal(FALSE, $types) . ' nodes');
    }
  }
  else {
    drush_print('Content types and number of nodes:');
    // This should be refactored back into delete_all_content
    $result = db_query("SELECT type, COUNT(*) AS num FROM {node} GROUP BY type");
    $count = array();
    foreach ($result as $record) {
    $count[$record->type] = $record->num;
    }
    foreach (node_type_get_types() as $type => $info) {
    drush_print($info->type . ' ' . ($count[$type] + 0));
    }
  }
}
