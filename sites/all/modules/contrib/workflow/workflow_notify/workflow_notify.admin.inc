<?php
/**
 * @file
 * Admin UI to Notify roles for Workflow state transitions.
 */

/**
 * Settings form.
 */
function workflow_notify_settings_form($form, $form_state, $workflow) {
  // If we don't have a workflow that goes with this, return to the admin pg.
  if ($workflow) {
    // Let's get a better page title.
    drupal_set_title(t('@name Notifications', array('@name' => ucwords($workflow->name))));

    // Let's add some breadcrumbs.
    workflow_admin_ui_breadcrumbs($workflow);

    $noyes = array(t('No'), t('Yes'));

    $form['wid'] = array('#type' => 'value', '#value' => $workflow->wid);
    $form['#workflow'] = $workflow;

    // Get all the states for this workflow, except the (creation) state.
//    $states = workflow_get_workflow_states_by_wid($workflow->wid,
//      array('status' => 1, 'sysid' => 0));
    $states = array();
    foreach ($workflow->states as $sid => $state) {
      if (!$state->sysid) {
        $states[$sid] = $state;
      }
    }
    if (!$states) {
      $form['error'] = array(
        '#type' => 'markup',
        '#value' => t('There are no states defined for this workflow.'),
      );
      return $form;
    }

    $form['#states'] = $states;

    // Get all roles, except anonymous.
    $roles = user_roles(TRUE);
    $roles = array('-1' => t('Author')) + user_roles(TRUE);

    // The module_invoke_all function does not allow passing by reference.
    $args = array('roles' => $roles);
    foreach (module_implements('workflow_notify') as $module) {
      $function = $module . '_workflow_notify';
      // Call the $op='roles' hooks so the list may be modified.
      $function('roles', $args);
    }
    // Get the modified list.
    $roles = $args['roles'];

    // Setting for "from" address.
    $form['from_address'] = array(
      '#title' => t('Set "From" address to'),
      '#type' => 'radios',
      '#options' => array(
        'site' => t('Site email address'),
        'changer' => t('Current user'),
        ),
      '#default_value' => variable_get('workflow_notify_from_address_' . $workflow->wid, 'site'),
      '#attributes' => array('class' => array('container-inline')),
      '#description' => t('Determines whether to use the site address or the address of the person
        causing the state change.'),
      );

    // Get the list of input formats.
    $formats = array();
    foreach (filter_formats() as $fid => $filter) {
      $formats[$fid] = $filter->name;
    }

    $form['filter'] = array(
      '#title' => t('Filter format to use on message'),
      '#type' => 'radios',
      '#options' => $formats,
      '#default_value' => variable_get('workflow_notify_filter_format_' . $workflow->wid, 'filtered_html'),
      '#attributes' => array('class' => array('container-inline')),
      '#description' => t('The message body will be processed using this filter format
        in order to ensure security.'),
      );

    $form['tokens'] = array(
      '#theme' => 'token_tree_link',
      '#token_types' => array('node', 'workflow'),
      );

    // Column names for theme function.
    $columns = array(
      'state' => t('State'),
      'roles' => t('Roles to notify'),
      );

    $args = array('columns' => $columns);
    // The module_invoke_all function does not allow passing by reference.
    foreach (module_implements('workflow_notify') as $module) {
      $function = $module . '_workflow_notify';
      $function('columns', $args);
    }
    $form['#columns'] = $args['columns'];

    // We always want subject and body last.
    $form['#columns']['subject'] = t('Subject');
    $form['#columns']['body'] = t('Body');

    $notify = variable_get('workflow_notify_roles', array());

    foreach ($states as $sid => $state) {
      // Allow modules to insert state operations.
      $state_links = module_invoke_all('workflow_operations', 'state', $workflow, $state);

      $form['states'][$sid] = array(
        'state' => array(
          '#type' => 'markup',
          '#markup' => filter_xss($state->state),
          ),

        'roles' => array(
          '#type' => 'checkboxes',
          '#options' => $roles,
          '#default_value' => (isset($notify[$sid]) ? $notify[$sid] : array()),
          '#attributes' => array('class' => array('state-roles')),
          ),

        'subject' => array(
          '#type' => 'textarea',
          '#rows' => 5,
          '#default_value' => variable_get('workflow_notify_subject_' . $sid,
            '[node:title] is now "[node:field_workflow_state:new-state:label]"'),
          '#attributes' => array('class' => array('subject')),
          ),

        'body' => array(
          '#type' => 'textarea',
          '#rows' => 5,
          '#default_value' => variable_get('workflow_notify_body_' . $sid,
            '<a href="[node:url:absolute]">[node:title]</a> is now "[node:field_workflow_state:new-state:label]".'),
          '#attributes' => array('class' => array('body')),
          ),
        );
    }

    $form['#tree'] = TRUE;
    $form['submit'] = array('#type' => 'submit', '#value' => 'Save notifications settings');

    return $form;
  }
  else {
    drupal_goto('admin/config/workflow/workflow');
  }
}

/**
 * Theme the settings form.
 */
function theme_workflow_notify_settings_form($variables) {
  $form = $variables['form'];
  $output = '';
  $table_id = 'workflow-notify-settings';

  $output .= drupal_render($form['from_address']);
  $output .= drupal_render($form['filter']);
  $output .= drupal_render($form['tokens']);

  $table = array(
    'rows' => array(),
    'header' => array(),    // To be filled in.
    'attributes' => array('id' => $table_id, 'style' => 'width: 100%; margin-top: 1em;'),
    );

  $columns = $form['#columns'];
  $colspan = count($columns);

  foreach ($columns as $field => $title) {
    $table['header'][] = $title;
  }

  // Iterate over each element in our $form['states'] array
  foreach (element_children($form['states']) as $id) {
    // We are now ready to add each element of our $form data to the rows
    // array, so that they end up as individual table cells when rendered
    // in the final table.
    $row = array();

    foreach ($columns as $field => $title) {
      $row[] = array(
        'data' => drupal_render($form['states'][$id][$field]),
        'class' => array(drupal_html_class($field)),
        );
    }

    // Put the data row into the table.
    $table['rows'][] = array('data' => $row);
  }

  $output .= theme('table', $table);

  $output .= drupal_render($form['explain']);

  // And then render any remaining form elements (such as our submit button)
  $output .= drupal_render_children($form);

  return $output;
}

function workflow_notify_settings_form_submit($form, $form_state) {
  $roles = variable_get('workflow_notify_roles', array());

  $workflow = $form['#workflow'];

  variable_set('workflow_notify_from_address_' . $workflow->wid , $form_state['values']['from_address']);
  variable_set('workflow_notify_filter_format_' . $workflow->wid , $form_state['values']['filter']);

  foreach ($form_state['values']['states'] as $sid => $values) {
    $selected = array_filter($values['roles']);
    // Are there any roles selected?
    if ($selected) {
      $roles[$sid] = $selected;
    }
    else {
      // No, so make sure this state is gone.
      unset($roles[$sid]);
    }

    variable_set("workflow_notify_subject_$sid", $values['subject']);
    variable_set("workflow_notify_body_$sid", $values['body']);
  }

  variable_set('workflow_notify_roles', $roles);

  drupal_set_message(t('The notification settings have been saved.'));
}
