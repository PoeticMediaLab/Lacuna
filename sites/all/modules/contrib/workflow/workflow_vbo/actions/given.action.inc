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
function workflow_vbo_given_action_info() {
  return array(
    'workflow_vbo_given_state_action' => array(
      'type' => 'entity',
      'label' => t('Change workflow state of post to new state'),
      'configurable' => TRUE,
      'triggers' => array('any'),
    ),
  );
}

/**
 * Implements a Drupal action. Move a node to a specified state.
 */
function workflow_vbo_given_state_action($entity, array $context) {
  global $user;

  $entity_type = $context['entity_type'];
  if (!entity_id($entity_type, $entity)) {
    watchdog('workflow_vbo', 'Unable to get current entity ID - entity is not yet saved.');
    return;
  }

  $form = $context['form'];
  $form_state = $context['form_state'];

  // The initial form was a VBO form, so add the entity.
  $form_state['values']['workflow_entity'] = $entity;

  // Parse the $comment variables.
  $new_sid = $form_state['input']['workflow_sid'];
  $comment_string = $form_state['input']['workflow_comment'];
  $comment = t($comment_string, array(
      '%title' => entity_label($entity_type, $entity), // "@" and "%" will automatically run check_plain().
      '%state' => workflow_get_sid_label($new_sid),
      '%user' => theme('username', array('account' => $user)),
    )
  );
  $form_state['input']['workflow_comment'] = $comment;

  // Submit the transition.
  workflow_transition_form_submit($form, $form_state);
}

/**
 * Configuration form for "Change workflow state of post to new state" action.
 *
 * This copies functionality from workflow_tab_page, and overrides some fields.
 *
 * @see workflow_vbo_given_state_action()
 */
function workflow_vbo_given_state_action_form(array $context) {
  $form = array();

  // @todo: There's a problem here: we do not know the node types of the
  // selected items, and we do not know the field_names, so we have no clue
  // about the allowed workflows or states.
  $entity_info = entity_get_info($context['entity_type']);
  $entity_key = $entity_info['entity keys']['id'];
  $entity_type = $context['entity_type'];
  $result = $context['view']->result;

  // Get the common workflow from entities. With Workflow Node, we knew how to do this.
  // With Workflow Field, we need to determine the workflow.
  $wid = 0;
  $field_name = NULL;
  foreach ($result as $entity_data) {
    // @todo: what to do with multiple workflow_fields per bundle?
    // The 'result' does not contain 'real' entities, and they mess up subfunctions.
    // We could fetch it from the array, like this: $entity = $entity_data->_field_data[$entity_key]['entity'];
    // But this is not reliable, if you have no fields to show.
    // So, last resort, just fetch from database/cache.
    $entity = entity_load_single($entity_type, $entity_data->{$entity_key});
    $fields = _workflow_info_fields($entity, $entity_type);
    if (count($fields)) {
      $field = reset($fields);
      $field_name = $field['field_name'];
    }
    $current_sid = workflow_node_current_state($entity, $entity_type, $field_name);
    $state = workflow_state_load_single($current_sid);
    if (!$wid && $state) {
      $wid = $state->wid;
    }
    elseif ($wid && $state && $wid <> $state->wid) {
      watchdog('workflow', 'Multiple workflows found in VBO action.', WATCHDOG_ERROR);
      drupal_set_message(t('Error: the selection contains more then one workflow.'), 'error');

      return $form; // <--- exit !!
    }
  }

  // Preserve $entity's bundle and id, if only 1 is selected.
  if (count($result) != 1) {
    $entity = NULL;
  }
  $entity_id = '';
  $entity_bundle = '';

  // Get the common Workflow, or create a dummy Workflow.
  $workflow = $wid ? workflow_load($wid) : workflow_create('dummy VBO');
  // Show the current state and the Workflow form to allow state changing.
  // N.B. This part is replicated in hook_node_view, workflow_tab_page, workflow_vbo.
  if ($workflow) {
    $field = _workflow_info_field($field_name, $workflow);
    // $field = reset(_workflow_info_fields($entity, $entity_type));
    $field_name = $field['field_name'];
    $field_id = $field['id'];
    $instance = field_info_instance($entity_type, $field_name, $entity_bundle);

    // Hide the submit button. VBO has its own 'next' button.
    $instance['widget']['settings']['submit_function'] = '';
    if (!$field['id']) {
      // This is a Workflow Node workflow. Set widget options as in v7.x-1.2
      $field['settings']['widget']['comment'] = isset($workflow->options['comment_log_tab']) ? $workflow->options['comment_log_tab'] : 1; // vs. ['comment_log_node'];
      $field['settings']['widget']['current_status'] = TRUE;
      // As stated above, the options list is probably very long, so let's use select list.
      $field['settings']['widget']['options'] = 'select';
      // Do not show the default [Update workflow] button on the form.
      $instance['widget']['settings']['submit_function'] = '';
    }
  }

  // Add the form/widget to the formatter, and include the nid and field_id in the form id,
  // to allow multiple forms per page (in listings, with hook_forms() ).
  // Ultimately, this is a wrapper for WorkflowDefaultWidget.
  // $form['workflow_current_state'] = workflow_state_formatter($entity_type, $entity, $field, $instance);
  $form += drupal_get_form(implode('_', array('workflow_transition_form', $entity_type, $entity_id, $field_id)), $field, $instance, $entity_type, $entity);

  // Make adaptations for VBO-form:
  // Override the options widget.
  $form['workflow']['workflow_sid']['#title'] = t('Target state');
  $form['workflow']['workflow_sid']['#description'] = t('Please select the state that should be assigned when this action runs.');
  $form['workflow']['workflow_sid']['#default_value'] = isset($context['target_sid']) ? $context['target_sid'] : '';

  $form['workflow']['workflow_force'] = array(
    '#type' => 'checkbox',
    '#title' => t('Force transition'),
    '#description' => t('If this box is checked, the new state will be assigned even if workflow permissions disallow it.'),
    '#default_value' => isset($context['force']) ? $context['force'] : '',
  );

  $form['workflow']['workflow_comment'] = array(
    '#type' => 'textfield',
    '#title' => t('Message'),
    '#description' => t('This message will be written into the workflow history log when the action
      runs. You may include the following variables: %state, %title, %user.'),
    '#default_value' => isset($context['workflow_history']) ? $context['workflow_history'] : t('Action set %title to %state by %user.'),
  );

  return $form;
}

/**
 * Submit handler for "Change workflow state of post to new state" action configuration form.
 *
 * @see workflow_vbo_given_state_action_form()
 */
function workflow_vbo_given_state_action_submit($form, $form_state) {
  $new_sid = $form_state['input']['workflow_sid'];
  if (!$new_sid) {
    return;
  }

  return array(
    'force' => $form_state['input']['workflow_force'],
    'form' => $form,
    'form_state' => $form_state,
  );
}
