<?php

/**
 * Implements hook_rules_action_info().
 * Modified version of the patch to og_rules @see https://www.drupal.org/node/1859698
 * Allows for loading all members of a group in Rules, by role, from the group node itself
 */
function course_registration_rules_action_info() {
  $items = array();
  $items['og_get_members_from_group'] = array(
    'label' => t('Get group members from a group node (rather than group content).'),
    'group' => t('Organic groups'),
    'parameter' => array(
      'group' => array(
        'type' => 'entity',
        'label' => t('Group node'),
        'description' => t('The group node determining the group audience.'),
      ),
      'states' => array(
        'type' => 'list<integer>',
        'label' => t('Membership states'),
        'options list' => 'og_group_states',
        'optional' => TRUE,
        'allow null' => TRUE,
        'description' => t('Filter group members by membership state. If no states are selected all members are loaded.'),
      ),
      'not_states' => array(
        'type' => 'boolean',
        'label' => t('Negate membership states'),
        'optional' => TRUE,
        'allow null' => FALSE,
        'description' => t('When checked only users not in the selected states will be loaded.'),
        'restriction' => 'input',
      ),
      'roles' => array(
        'type' => 'list<text>',
        'label' => t('Group roles'),
        'options list' => 'og_rules_group_roles_options_list',
        'optional' => TRUE,
        'allow null' => TRUE,
        'restriction' => 'input',
      ),
      'not_roles' => array(
        'type' => 'boolean',
        'label' => t('Negate group roles'),
        'optional' => TRUE,
        'allow null' => FALSE,
        'description' => t('When checked only users not in the selected roles will be loaded.'),
        'restriction' => 'input',
      ),
    ),
    'provides' => array(
      'group_members' => array('type' => 'list<user>', 'label' => t('List of group members')),
    ),
    'base' => 'course_registration_rules_get_members',
    'access callback' => 'og_rules_integration_access',
  );
  return $items;
}

/**
 * Action: Get group members from a group node.
 */
function course_registration_rules_get_members($group, $states = NULL, $not_states = FALSE, $roles = NULL, $not_roles = FALSE) {
  if (!isset($group->group_group)) {
    // Not a group.
    return;
  }

  $members = array();
  // Get the group members for the group.
  $query = db_select('og_membership', 'om')
    ->fields('om', array('etid'))
    ->condition('om.gid', $group->nid->value())
    ->condition('om.group_type', 'node')
    ->condition('om.entity_type', 'user');

  if (!empty($states)) {
    $op = $not_states ? 'NOT IN' : 'IN';
    $query->condition('om.state', $states, $op);
  }

  if (!empty($roles)) {
    $group_roles = og_roles('node', $group->type->value(), $group->nid->value());
    $rids = array();
    foreach ($roles as $role) {
      $rid = array_search($role, $group_roles);
      if ($rid !== FALSE) {
        $rids[] = $rid;
      }
    }
    if (!empty($rids)) {
      if ($not_roles) {
        // Use a subquery to find members with the roles we want to exclude,
        // since members may have multiple roles or no roles at all.
        $subquery = db_select('og_users_roles', 'our')
          ->fields('our', array('uid'))
          ->condition('our.gid', $group->nid->value())
          ->condition('our.group_type', 'node')
          ->condition('our.rid', $rids);
        $query->condition('om.etid', $subquery, 'NOT IN');
      }
      else {
        $query->innerJoin('og_users_roles', 'our', 'om.etid=our.uid AND om.gid=our.gid AND om.group_type=our.group_type');
        $query->condition('our.rid', $rids);
      }
    }
  }

  $current_members = $query
    ->execute()
    ->fetchCol();

  $members = array_merge($members, $current_members);
  // Remove duplicate items.
  $members = array_keys(array_flip($members));
  return array('group_members' => $members);
}