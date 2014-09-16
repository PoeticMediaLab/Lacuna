<?php
/**
 * @file
 * Callback implementations for Rules integration for the Workflow module.
 *
 * These callbacks must be included in the module file.
 * It is not sufficient to have them in the rules_info file.
 */

/**
 * Helper function to parse a token "node:<field_name>".
 *
 * @param string $token
 *
 * @return string $field_name
 *
 * This is a poorman's effort to convert a token into a field name.
 */
function _workflow_rules_token_replace($field_name) {
  // Get the part after the first domain indicator.
  $list_parts = explode(':', $field_name, 2);
  $field_name = end($list_parts);

  $field_name = str_replace('-', '_', $field_name);
  return $field_name;
}

/**
 * Condition callback: gather all workflow states, to show in list_options.
 */
function _workflow_rules_workflow_get_options($data) {
  // This is a poorman's effort to convert a token into a field name.
  $field_name = isset($data->settings['field:select']) ? _workflow_rules_token_replace($data->settings['field:select']) : '';
  $field = _workflow_info_field($field_name, NULL);
  // $field['settings']['wid'] can be numeric or named.
  $workflow = workflow_load_single($field['settings']['wid']);

  $options['ANY'] = 'ANY state';
  $options += workflow_get_workflow_state_names($workflow->wid, $grouped = TRUE);
  return $options;
}

/**
 * Condition implementation helper function: check given state.
 *
 * @param mixed $sid
 *   A State ID, to compare with the given list of allowed State ID's.
 * @param array $sids
 *   A list of allowed State ID's.
 *
 * @return bool
 *   TRUE or FALSE.
 */
function _workflow_rules_workflow_check_given_state($sid, array $sids) {
  return in_array('ANY', $sids) || in_array($sid, $sids);
}


/**
 * Condition implementation: check state transition for Workflow Node API.
 *
 * @param object $node
 *   The node with the new values. Other entity types are not supported.
 * @param array $old_sids
 *   An array of old sids to meet the condition.
 * @param array $new_sids
 *   An array of new sids to meet the condition.
 * @param array $condition
 *   A RulesCondition->settings array.
 */
function _workflow_rules_node_check_transition($node, array $old_sids, array $new_sids, array $condition) {
  $last_transition = workflow_transition_load_single('node', $node->nid, '', 1);
  $old_sid = $last_transition->old_sid;
  $new_sid = $last_transition->new_sid;

  return
    _workflow_rules_workflow_check_given_state($old_sid, $old_sids) &&
    _workflow_rules_workflow_check_given_state($new_sid, $new_sids);
}

/**
 * Condition implementation: check current state for Workflow Node API.
 *
 * @param object $node
 *   The node with the new values. Other entity types are not supported.
 * @param array $sids
 *   An array of State IDs to meet the condition.
 */
function _workflow_rules_node_check_state($node, array $sids) {
  $sid = workflow_node_current_state($node, 'node', '');
  return _workflow_rules_workflow_check_given_state($sid, $sids);
}

/**
 * Condition implementation: check previous state.
 */
function _workflow_rules_node_check_previous_state($node, $sids) {
  // $sid = workflow_node_previous_state($node, 'node');
  $last_transition = workflow_transition_load_single('node', $node->nid, '', 1);
  $sid = $last_transition->old_sid;
  return _workflow_rules_workflow_check_given_state($sid, $sids);
}

/**
 * Action implementation: set current state, ignoring current user permission.
 */
function _workflow_rules_set_state(array $parameters, RulesAction $action) {
  global $user;

  // "$parameters['node']" is for backwards compatibility: can be any entity_type.
  $entity = $parameters['node']->value(); // $parameters['entity'] is an EntityDrupalWrapper.
  $entity_type = $parameters['node']->type();

  // This is a poorman's effort to convert a token into a field name.
  $field_name = isset($parameters['settings']['field:select']) ? _workflow_rules_token_replace($parameters['settings']['field:select']) : '';
  $old_sid = workflow_node_current_state($entity, $entity_type, $field_name);

  // Select the last state on the list.
  $new_sid = array_pop($parameters['workflow_state']);
  $comment = $parameters['workflow_comment'];

  $transition = new WorkflowTransition();
  $transition->setValues($entity_type, $entity, $field_name, $old_sid, $new_sid, $user->uid, REQUEST_TIME, $comment);

  // Set the Force, to ignore the limitations on the current user's permissions.
  // But the transition must be existent for a/any role!
  $force = TRUE;
  $transition->force($force);

  // Execute the transition. It may bounce, due to extra checks.
  $sid = $transition->execute($force);

  if ($field_name && isset($entity->{$field_name})) {
    $entity_id = entity_id($entity_type, $entity);

    // Save the entity, but not through entity_save(),
    // since this will check permissions again and trigger rules.
    // @TODO: replace below by a workflow_field setter callback.
    if ($sid == $new_sid) {
      // The transition was successfully executed, or else a message was raised.
      $entity->{$field_name}[LANGUAGE_NONE] = array();
      $entity->{$field_name}[LANGUAGE_NONE][0]['workflow']['workflow_sid'] = $new_sid;
      $entity->{$field_name}[LANGUAGE_NONE][0]['workflow']['workflow_comment'] = $comment;
      if ($entity_id) {
        field_attach_update($entity_type, $entity);
      }

      // Reset the entity cache after update.
      entity_get_controller($entity_type)->resetCache(array($entity_id));
    }
  }
}
