<?php
/**
 * @file
 * Contains helper functions for WorkflowTransitionForm.
 */

/**
 * Getter/Setter to tell if the action buttons are used.
 *
 * @param bool $new_value
 *   Options. If TRUE/FALSE, the value is set. If NULL, value is only 'getted'.
 *
 * @return bool
 *   Previous value. If TRUE, action buttons must be created.
 *
 * @see workflow_form_alter()
 * @see WorkflowDefaultWidget::formElement()
 *
 * Used to save some expensive operations on every form.
 */
function _workflow_use_action_buttons($new_value = NULL) {
  global $_workflow_use_actions_buttons;

  $old_value = $_workflow_use_actions_buttons ? TRUE : FALSE;
  // Reset value if requested.
  if ($new_value !== NULL) {
    $_workflow_use_actions_buttons = $new_value;
  }
  return $old_value;
}

/**
 * Form builder. Move action buttons next to the 'Save'/'Delete' buttons.
 *
 * This is only used if the set the 'options widget' to 'action buttons'.
 * Do not use with multiple workflows per entity: confusing UX.
 * ATM this works for:
 * - Workflow Field: create, edit, view, workflow tab, comment;
 * - Workflow Node: view, workflow tab;
 * (For forms with Workflow Node, the form_alter() is AFTER formElement(). )
 *
 * @todo: move this to WorkflowTransitionForm::_addActionButtons();
 */
function workflow_form_alter(&$form, &$form_state, $form_id) {

  // Use a fast, custom way to check if we need to do this.
  // @todo: Make this work with multiple workflows per entity.
  if (!_workflow_use_action_buttons()) {
    return;
  }

  // Find the first workflow.
  // (So this won't work with multiple workflows per entity.)
  $workflow_form = array();
  if (isset($form['workflow'])) {
    // Workflow Node or // Workflow History tab.
    $workflow_form = &$form['workflow'];
    $field_info = $workflow_form['workflow_field']['#value'];
    $field_name = $field_info['field_name'];
    $langcode = LANGUAGE_NONE;

    // Move non-standard 'Submit workflow' button in hook_node_view, workflow_tab_page, workflow_vbo.
    if (isset($form['workflow']['actions'])) {
      $form['actions'] = $form['workflow']['actions'];
      unset($form['workflow']['actions']);
    }
  }
  else {
    $field_name = '';
    foreach (element_children($form) as $key) {
      if (isset($form[$key]['#language'])) {
        $langcode = $form[$key]['#language'];
        if (isset($form[$key][$langcode][0]['workflow'])) {
          // Reference the Workflow Form, we'll remove the buttons later.
          $field_name = $key;
          $langcode = $form[$field_name]['#language'];
          $workflow_form = &$form[$key][$langcode][0]['workflow'];
          // Stop looping if found.
          break;
        }
      }
    }
  }

  // Quit if there is no Workflow on this page.
  if (!$workflow_form ) {
    return;
  }

  // Quit if there are no Workflow Action buttons.
  // (If user has only 1 workflow option, there are no Action buttons.)
  if (count($workflow_form['workflow_sid']['#options']) <= 1) {
    return;
  }

  // Find the default submit button and replace with our own action buttons.
  if (isset($form['actions']['submit'])) {
    $default_submit_action = $form['actions']['submit'];
    unset($form['actions']['submit']);
  }
  elseif (isset($form['actions']['save'])) {
    $default_submit_action = $form['actions']['save'];
    unset($form['actions']['save']);
  }
  if (isset($default_submit_action)) {
    $current_sid = $workflow_form['workflow_sid']['#default_value'];
    $scheduled = isset($workflow_form['workflow_scheduling']['scheduled']) && $workflow_form['workflow_scheduling']['scheduled']['#default_value'];

    // Get the min weight for our buttons.
    $option_weight = isset($default_submit_action['#weight']) ? $default_submit_action['#weight'] : 0;
    $option_weight = $option_weight - count($workflow_form['workflow_sid']['#options']);
    $min_weight = $option_weight;
    foreach ($workflow_form['workflow_sid']['#options'] as $sid => $option_name) {
      // Make the workflow button act exactly like the original submit button.

      $same_state_button = ($sid == $current_sid);
      // Add target State ID and Field name, to set correct value in validate_buttons callback.
      $workflow_submit_action = $default_submit_action + array(
        '#workflow_sid' => $sid,
        '#workflow_field_name' => $field_name,
      );
      // Keep option order. Put current state first.
      $workflow_submit_action['#weight'] = ($same_state_button) ? $min_weight : ++$option_weight;
      // Add/Overwrite some other settings.
      $workflow_submit_action['#access'] = TRUE;
      $workflow_submit_action['#value'] = $option_name;
      $workflow_submit_action['#attributes'] = ($same_state_button) ? array('class' => array('form-save-default-button')) : array();
      //$workflow_submit_action['#executes_submit_callback']  = TRUE;
      $workflow_submit_action['#attributes']['class'][] = drupal_html_class('workflow_button_' . $option_name);
      // Append the form's #validate function, or it won't be called upon submit,
      // because the workflow buttons have its own #validate.
      if (isset($default_submit_action['#validate'])) {
        $workflow_submit_action['#validate'] = $default_submit_action['#validate'];
      }
      elseif (isset($form['#validate'])) {
        $workflow_submit_action['#validate'] = $form['#validate'];
      }
      $workflow_submit_action['#validate'][] = '_workflow_transition_form_validate_buttons';
      // Append the submit-buttons's #submit function, or it won't be called upon submit.
      if (isset($default_submit_action['#submit'])) {
        $workflow_submit_action['#submit'] = $default_submit_action['#submit'];
      }
      elseif (isset($form['#submit'])) {
        $workflow_submit_action['#submit'] = $form['#submit'];
      }

      // Hide the same-state button in some cases.
      // Alternative: use hide($element);
      if ($same_state_button && !$scheduled) {
        if (substr( $form['#form_id'], 0, 24) == 'workflow_transition_form') {
          // Hide same-state-button on the transition-form (that is:
          // view page or workflow history tab) if there is nothing to do.
          // However, a Transition may be fieldable.
          if ($form['workflow']['workflow_comment']['#access'] == FALSE) {
            $workflow_submit_action['#access'] = FALSE;
          }
        }
        elseif ($form['#id'] == 'comment-form') {
          // On comment-form, the button must stay, since you can comment to same state.
        }
        else {
          // On a entity edit page, the button must stay.
        }
      }

      // Place the button with the other action buttons.
      $form['actions']['workflow_' . $sid] = $workflow_submit_action;
    }

    // On Edit page, remove the submit button from the workflow form.
    unset($workflow_form['actions']);
  }
}

/**
 * Form builder. Allow workflow comment change from menu item/Views link.
 *
 * @todo D8: This is used, because the D7 form workflow_transition_form
 * has the wrong parameters for the EntityUIController.
 * But changing it breaks backwards compatibility.
 */
function workflow_transition_wrapper_form(array $form, array &$form_state, $transition, $op, $form_id) {
  // Override the default function 'entity_ui_controller_form_<op>'; we're not ready for that yet.
  $form['#validate'] = array('workflow_transition_form_validate');
  $form['#submit'] = array('workflow_transition_form_submit');

  // The Workflow transition is provided as such:
  // $form_state['entity_type'] = 'WorkflowTransition';
  // $form_state['WorkflowTransition'] = (Object) WorkflowTransition;
  return workflow_transition_form($form, $form_state, array(), array(), '', NULL);
}

function workflow_transition_form(array $form, array &$form_state, array $field, $instance, $entity_type, $entity) {
  if (!isset ($instance['widget']['settings']['submit_function'])) {
    $instance['widget']['settings']['submit_function'] = 'workflow_transition_form_submit';
  }

  $transition_form = new WorkflowTransitionForm($field, $instance, $entity_type, $entity);
  return $transition_form->buildForm($form, $form_state);
}

/**
 * Submit callback function for the Workflow Form / DefaultWidget.
 *
 * Validate target state and either save a transition immediately or schedule
 * a transition to be executed later by cron.
 */
function workflow_transition_form_validate($form, &$form_state) {
  // Even if this function is empty, it must exist.
  // Validate the attached fields.
  // field_attach_form_validate('WorkflowTransition', $form_state['values'], $form, $form_state);

  // $transition_form = new WorkflowTransitionForm($field, $instance, $entity_type, $entity);
  // return $transition_form->submitForm($form, $form_state, $items);
}

/**
 * Submit callback function for the Workflow Form / DefaultWidget.
 *
 * Validate target state and either save a transition immediately or schedule
 * a transition to be executed later by cron.
 */
function workflow_transition_form_submit($form, &$form_state) {
  // Retrieve the data from the form.
  if (isset($form_state['values']['workflow_field'])) {
    // If $entity filled: We are on a Entity View page or Workflow History Tab page.
    // If $entity empty: We are on an Advanced Action page.
    $field = $form_state['values']['workflow_field'];
    $instance = $form_state['values']['workflow_instance'];
    $entity_type = $form_state['values']['workflow_entity_type'];
    $entity = $form_state['values']['workflow_entity'];

    $items = array();
    $transition_form = new WorkflowTransitionForm($field, $instance, $entity_type, $entity);
    return $transition_form->submitForm($form, $form_state, $items);
  }
  else {
    watchdog('workflow', 'workflow_transition_form_submit() is called with error.');
    // We are on an Entity/Node/Comment Form page.
    // We should not be here.
    return;
  }

}

/**
 * Submit callback function for the Workflow Form / DefaultWidget.
 *
 * Validate form data for 'time' element.
 */
function _workflow_transition_form_element_validate_time($element, &$form_state, $form) {
  if (!strtotime($element['#value'])) {
    form_error($element, t('Please enter a valid value for time.'));
  }
}

/**
 * Submit callback function for the Workflow Form / DefaultWidget.
 *
 * This is only used when using action buttons in Workflow form.
 * It sets the new state to proper
 * element and sets a submit function if needed, making sure the action is
 * executed, influencing function core/includes/form.inc/form_execute_handlers().
 * (While constructing the Workflow form, we were not yet aware of the submit
 * buttons of the complete form. We try to correct this here, without adding
 * another hook_form_alter. We guess the first button is the Save button.
 */
function _workflow_transition_form_validate_buttons($form, &$form_state) {
  $field_name = $form_state['triggering_element']['#workflow_field_name'];
  $new_sid = $form_state['triggering_element']['#workflow_sid'];

  $langcode = LANGUAGE_NONE;
  // Retrieve the data from the form.
  if (isset($form_state['values']['workflow_field'])) {
    // We are on a Entity View page or Workflow History Tab page.
    $entity_type = $form_state['values']['workflow_entity_type'];
    $entity = $form_state['values']['workflow_entity'];

    $langcode = _workflow_metadata_workflow_get_properties($entity, array(), 'langcode', $entity_type, $field_name);
  }

  /*
    if (isset($form_state['triggering_element']['#submit'])) {
      // We are on a View page or History tab. Try to fix the form_state.
    else {
      // We are on a Node/Entity/Comment form. Try to fix the form_state.
    }
   */

  if ($field_name) {
    $form_state['input']['workflow_sid'] = $new_sid;
    $form_state['values'][$field_name][$langcode][0]['workflow']['workflow_sid'] = $new_sid;
  }
  else {
    $form_state['input']['workflow_sid'] = $new_sid;
    $form_state['values']['workflow_sid'] = $new_sid;
  }
}
