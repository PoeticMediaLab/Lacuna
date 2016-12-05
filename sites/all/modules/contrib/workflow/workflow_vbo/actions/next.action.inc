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
 *
 * @param $entity
 * @param array $context
 */
function workflow_vbo_next_state_action($entity, array $context) {
  global $user;

  // Get the entity type, entity and entity ID.
  if (isset($context['entity_type'])) {
    // In a VBO Action.
    $entity_type = $context['entity_type'];
  }
  else {
    // In an Advanced Action.
    $entity_type = str_replace(array('_insert', '_update' , '_delete'), '', $context['hook']);
  }
  // Change the state of latest revision, not current revision.
  if (isset($context[$entity_type])) {
    $entity = $context[$entity_type];
  }
  elseif (!isset($entity)) {
    $entity = $context['node'];
  }
  // In 'after saving new content', the node is already saved. Avoid second insert.
  // Todo: clone?
  unset($entity->is_new);

  list($entity_id, , $entity_bundle) = entity_extract_ids($entity_type, $entity);
  if (!$entity_id) {
    watchdog('workflow_vbo', 'Unable to get current entity ID - entity is not yet saved.');
    return;
  }

  // Get the current State Id. Also, $field_name will be set magically, by reference.
  $field_name = NULL;
  $current_sid = workflow_node_current_state($entity, $entity_type, $field_name);
  // Get the Comment. It is empty.
  $comment = '';
  // Only 'normal' state transitions are valid.
  $force = FALSE;

  // Get the node's new State Id (which is the next available state).
  $workflow = workflow_get_workflows_by_type($entity_bundle, $entity_type);
  if (!$workflow) {
    watchdog('workflow_vbo', 'Unable to get current workflow of entity %id.',
      array('%id' => $entity_id));
    return;
  }

  $new_sid = $workflow->getNextSid($entity_type, $entity, $field_name, $user, $force);
  if (!$new_sid) {
    watchdog('workflow_vbo', 'Unable to get current workflow state of entity %id.',
      array('%id' => $entity_id));
    return;
  }

  // Fire the transition.
  $transition = new WorkflowTransition();
  $transition->setValues($entity_type, $entity, $field_name, $current_sid, $new_sid, $user->uid, REQUEST_TIME, $comment);
  workflow_execute_transition($entity_type, $entity, $field_name, $transition, $force);
}
