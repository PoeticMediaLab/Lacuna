<?php

/**
 * @file
 * VBO action to modify entity values (properties and fields).
 */

/**
 * Implements hook_action_info().
 *
 * Registers custom VBO actions as Drupal actions.
 */
function workflow_vbo_next_action_info() {
  return array(
    'workflow_vbo_next_state_action' => array(
      'type' => 'entity',
      'label' => t('Change workflow state of post to next state'),
      'configurable' => FALSE,
      'triggers' => array('any'),
    ),
  );
}

/**
 * Implements a Drupal action. Move a node to the next state in the workflow.
 */
function workflow_vbo_next_state_action($entity, array $context) {
  global $user;

  // If this action is being fired because it's attached to a workflow transition
  // then the node's new state (now its current state) should be in $entity->workflow
  // because that is where the value from the workflow form field is stored;
  // otherwise the current state is placed in $entity->workflow by our nodeapi load.
  $entity_type = $context['entity_type'];
  if (!$entity_id = entity_id($entity_type, $entity)) {
    watchdog('workflow_vbo', 'Unable to get current entity ID - entity is not yet saved.');
    return;
  }

  // Read the last transition to get the $field_name and $sid, whatever field exists.
  // @todo: it is cheaper to build this into workflow_node_current_state().
  // $current_sid = workflow_node_current_state($entity, $entity_type, $field_name);
  $last_transition = workflow_transition_load_single($entity_type, $entity_id, $field_name = NULL);
  if (!$last_transition || !$last_transition->new_sid) {
    watchdog('workflow_vbo', 'Unable to get current workflow state of entity %id.',
      array('%id' => $entity_id));
    return;
  }
  $field_name = $last_transition->field_name;
  $current_sid = $last_transition->new_sid;
  $current_state = workflow_state_load_single($current_sid);

  // Get the node's new state (which is the next available state).
  $options = $current_state->getOptions($entity_type, $entity, $field_name, $user, FALSE);
  $new_sid = $current_sid;
  $flag = $current_state->isCreationState();
  foreach ($options as $sid => $name) {
    if ($flag) {
      $new_sid = $sid;
      break;
    }
    if ($sid == $current_sid) {
      $flag = TRUE;
    }
  }

  // Fire the transition.
  $comment = '';
  $transition = new WorkflowTransition();
  $transition->setValues($entity_type, $entity, $field_name, $current_sid, $new_sid, $user->uid, REQUEST_TIME, $comment);
  workflow_execute_transition($entity_type, $entity, $field_name, $transition, FALSE);
}
