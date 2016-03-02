<?php
/**
 * @file
 * Provide user interface for changing workflow state.
 *
 * @todo D8: remove this in favour of View 'Workflow history per entity'.
 */

define('MARK_STATE_IS_DELETED', '*');

/**
 * Menu callback. Display workflow summary of a node.
 *
 * N.B. When having multiple workflows per bundle, use Views display
 *      'Workflow history per entity' instead!
 */
function workflow_tab_page($entity_type, $entity = NULL) {
  drupal_set_title(entity_label($entity_type, $entity));

  $form = array();
  $field_name = NULL;
  $workflow = NULL;

  // Figure out the $entity's bundle and id.
  list($entity_id, , $entity_bundle) = entity_extract_ids($entity_type, $entity);
  $entity_id = entity_id($entity_type, $entity);

  // Get the current sid. $field_name is updated with relevant value.
  $current_sid = workflow_node_current_state($entity, $entity_type, $field_name);
  $current_state = workflow_state_load_single($current_sid);
  $workflow = $current_state->getWorkflow();

  // Show the current state and the Workflow form to allow state changing.
  // N.B. This part is replicated in hook_node_view, workflow_tab_page, workflow_vbo, transition_edit.
  // @todo: support multiple workflows per entity.
  // For workflow_tab_page with multiple workflows, use a separate view. See [#2217291].
  $field = _workflow_info_field($field_name, $workflow);
  $field_id = $field['id'];
  $instance = field_info_instance($entity_type, $field_name, $entity_bundle);
  if (!$field_id) {
    // This is a Workflow Node workflow. Set widget options as in v7.x-1.2
    $field['settings']['widget']['comment'] = isset($workflow->options['comment_log_tab']) ? $workflow->options['comment_log_tab'] : 1; // vs. ['comment_log_node'];
    $field['settings']['widget']['current_status'] = TRUE;
  }

  $form_id = implode('_', array('workflow_transition_form', $entity_type, $entity_id, $field_id));
  $form += drupal_get_form($form_id, $field, $instance, $entity_type, $entity);

  $output = drupal_render($form);


  // Show the history table.
  $rows = array();
  $current_themed = FALSE;
  $limit = variable_get('workflow_states_per_page', 20);
  // Get the history for any field_name.
  foreach (workflow_transition_load_multiple($entity_type, array($entity_id), NULL, $limit) as $history) {
    $old_state_name = $new_state_name = '';

    $label = $name = '';
    $new_state = $history->getNewState();
    if ($new_state) {
      $name = $new_state->getName();
      $label = check_plain(t($new_state->label()));
    }

    if (!$new_state) {
      // This is an invalid/deleted state.
      $old_state_name = $label;
    }
    elseif ($history->new_sid == $current_sid && $new_state->isActive() && !$current_themed) {
      // Theme the current state differently so it stands out.
      $new_state_name = theme('workflow_history_current_state', array(
        'state_name' => $label,
        'state_system_name' => $name,
        'sid' => $history->new_sid,
      ));
      // Make a note that we have themed the current state; other times in the history
      // of this node where the node was in this state do not need to be specially themed.
      $current_themed = TRUE;
    }
    elseif (!$new_state->isActive()) {
      // The state has been deleted, but we include it in the history.
      $new_state_name = theme('workflow_deleted_state', array(
        'state_name' => $label,
        'state_system_name' => $name,
        'sid' => $history->new_sid,
      ));
      $footer_needed = TRUE;
    }
    else {
      // Regular state.
      $new_state_name = $label;
    }
    unset($new_state); // Not needed anymore.

    $label = $name = MARK_STATE_IS_DELETED;
    $old_state = $history->getOldState();
    if ($old_state) {
      $name = $old_state->getName();
      $label = check_plain(t($old_state->label()));
    }

    if (!$old_state) {
      // This is an invalid/deleted state.
      $old_state_name = $label;
    }
    elseif (!$old_state->isActive()) {
      $old_state_name = theme('workflow_deleted_state', array(
        'state_name' => $label,
        'state_system_name' => $name,
        'sid' => $history->old_sid,
      ));
      $footer_needed = TRUE;
    }
    else {
      // Regular state.
      $old_state_name = $label;
    }
    unset($old_state); // Not needed anymore.

    $variables = array(
      'transition' => $history, // @todo D8: pass this WorkflowTransition as only variable. It contains everything.
      'extra' => '',

      'history' => $history,  // @todo D8: remove, as this is the same as 'transition'.
      'old_sid' => $history->old_sid, // @todo D8: remove this redundant property.
      'sid' => $history->new_sid, // @todo D8: remove this redundant property.
      'uid' => $history->uid, // @todo D8: remove this redundant property.
      'old_state_name' => $old_state_name,
      'state_name' => $new_state_name,
    );

    // Allow other modules to modify the row.
    // $todo D8: pass only a $transition object.
    drupal_alter('workflow_history', $variables);

    $rows[] = theme('workflow_history_table_row', $variables);
  }

  // Mark the first and last rows.
  $rows[0]['class'][] = 'first';
  $last = count($rows) - 1;
  $rows[$last]['class'][] = 'last';

  $header = array(t('Date'), t('Field name'), t('Old State'), t('New State'), t('By'), t('Comment'));
  $header[] = array('data' => t('Operations'));

  // Only display the table if there's anything in it.
  if ($rows) {
    $variables = array(
      'header' => $header,
      'rows' => $rows,
      'footer' => !empty($footer_needed),
      'entity' => $entity,
      'entity_type' => $entity_type,
    );

    $output .= theme('workflow_history_table', $variables);
    $output .= theme('pager', array('tags' => $limit));
  }
  return $output;
}

/**
 * Theme one WorkflowTansition in a workflow history table row.
 *
 * $old_state_name and $state_name must be run through check_plain(t()) prior
 * to calling this theme function.
 */
function theme_workflow_history_table_row($variables) {
  $row = array();
  $old_state_name = $variables['old_state_name'];
  $state_name = $variables['state_name'];
  $transition = $variables['transition'];
  $row = array(
    'data' => array(
      array('data' => format_date($transition->stamp), 'class' => array('timestamp')),
      array('data' => $transition->field_name, 'class' => array('field-name')),
      array('data' => $old_state_name, 'class' => array('previous-state-name')),
      array('data' => $state_name, 'class' => array('state-name')),
      array('data' => theme('username', array('account' => $transition->getUser())), 'class' => array('user-name')),
      array('data' => filter_xss($transition->comment), 'class' => array('log-comment')),
      $variables['extra'],
    ),
    'class' => array('workflow_history_row'),
  );

  return $row;
}

/**
 * Theme entire workflow history table.
 */
function theme_workflow_history_table($variables) {
  $header = $variables['header'];
  $rows = $variables['rows'];
  $footer = $variables['footer'];
  $entity = $variables['entity'];
  $entity_type = $variables['entity_type'];
  $column_field_name = 1;
  $column_operations = 6;

  // Remove the Operations column if none are added.
  $empty = TRUE;
  foreach ($rows as $row) {
    $empty &= empty($row['data'][$column_operations]);
  }
  if ($empty) {
    foreach ($rows as &$row) {
      unset($row['data'][$column_operations]);
      unset($header[$column_operations]);
    }
  }

  // Remove the Field name column if only 1 workflow_field exists.
  if (count(_workflow_info_fields($entity, $entity_type)) < 2) {
    foreach ($rows as &$row) {
      unset($row['data'][$column_field_name]);
      unset($header[$column_field_name]);
    }

  }

  $output = theme('table', array('header' => $header, 'rows' => $rows, 'caption' => t('Workflow History')));
  if ($footer) {
    $output .= MARK_STATE_IS_DELETED . ' ' . t('State is no longer available.');
  }
  return $output;
}

/**
 * Theme the current state in the workflow history table.
 *
 * $state_name must be run through check_plain(t()) prior
 * to calling this theme function.
 */
function theme_workflow_history_current_state($variables) {
  return $variables['state_name'];
}

/**
 * Theme a deleted state in the workflow history table.
 *
 * $state_name must be run through check_plain(t()) prior
 * to calling this theme function.
 */
function theme_workflow_deleted_state($variables) {
  return $variables['state_name'] . MARK_STATE_IS_DELETED;
}
