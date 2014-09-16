<?php

/**
 * @file
 * Provide views data and handler information for workflow.module.
 *
 * Includes the 'workflow_node' and 'workflow_state' tables, but generates a
 * pseudo-table for each separate workflow that's been set up.
 *
 * @defgroup views_workflow_module workflow.module handlers
 */

/**
 * Implements hook_views_data_alter().
 */
function workflow_views_views_data_alter(&$data) {
  // In version 7.x-1.2, the following groups were defined in
  // workflow_views_views_data. Now, in 7.x-2.x the Transitions have become
  // entities, and are already declared by EntityDefaultViewsController.
  // So, the overrides have now moved to _alter.
  $data['workflow_transitions']['sid']['field']['handler'] = 'workflow_views_handler_field_sid';
  $data['workflow_transitions']['sid']['filter']['handler'] = 'workflow_views_handler_filter_sid';
  $data['workflow_transitions']['target_sid']['field']['handler'] = 'workflow_views_handler_field_sid';
  $data['workflow_transitions']['target_sid']['filter']['handler'] = 'workflow_views_handler_filter_sid';

  $data['workflow_node_history']['old_sid']['field']['handler'] = 'workflow_views_handler_field_sid';
  $data['workflow_node_history']['old_sid']['filter']['handler'] = 'workflow_views_handler_filter_sid';
  $data['workflow_node_history']['sid']['field']['handler'] = 'workflow_views_handler_field_sid';
  $data['workflow_node_history']['sid']['filter']['handler'] = 'workflow_views_handler_filter_sid';
  $data['workflow_node_history']['uid']['field']['handler'] = 'workflow_views_handler_field_username';
  $data['workflow_node_history']['uid']['filter']['handler'] = 'views_handler_filter_user_name';
  $data['workflow_node_history']['uid']['relationship'] = array(
    'handler' => 'views_handler_relationship',
    'base' => 'users',
    'base field' => 'uid',
    'label' => t('User'),
  );
  $data['workflow_node_history']['comment']['field']['handler'] = 'views_handler_field_xss';
  $data['workflow_node_history']['comment']['filter']['handler'] = 'views_handler_filter_string';
  $data['workflow_node_history']['stamp']['field']['handler'] = 'views_handler_field_date';
  $data['workflow_node_history']['stamp']['filter']['handler'] = 'views_handler_filter_date';
  $data['workflow_node_history']['stamp']['sort']['handler'] = 'views_handler_sort_date';
  $data['workflow_node_history']['hid']['filter']['numeric'] = TRUE;
  // This group's help and title are moved from hook_views_data to _alter(), to avoid Notices.
  $data['workflow_node_history']['old_sid']['title'] = t('Old state');
  $data['workflow_node_history']['old_sid']['help'] = t('The previous state, from the last state change.');
  $data['workflow_node_history']['sid']['title'] = t('New state');
  $data['workflow_node_history']['sid']['help'] = t('The new state in a transition. (For the latest transition, this is the current state.)');
  $data['workflow_node_history']['uid']['title'] = t('Previous user');
  $data['workflow_node_history']['uid']['help'] = t('The user that executed a state change.');
  $data['workflow_node_history']['comment']['title'] = t('Comment');
  $data['workflow_node_history']['comment']['help'] = t('The comment describing why the the state change was done.');
  $data['workflow_node_history']['stamp']['title'] = t('Time');
  $data['workflow_node_history']['stamp']['help'] = t('The time of the last state change.');
  // This group's help and title are moved from hook_views_data to _alter(), to avoid Notices.
  $data['workflow_node_history']['table']['group'] = t('Workflow history');
  $data['workflow_node_history']['table']['join'] = array(
    'node' => array(
      'field' => 'nid',
      'left_table' => 'node',
      'left_field' => 'nid',
    ),
  );
  // This Edit comment handler is copied from workflow_extensions.
  $data['workflow_node_history']['edit_comment'] = array(
    'title' => t('Edit comment'),
    'help' => t('Provide a link to edit the workflow log comment.'),
    'field' => array(
      'handler' => 'workflow_views_handler_field_comment_link_edit',
    ),
  );

  $data['workflow_node_current'] = $data['workflow_node_history'];
  $data['workflow_node_current']['table']['group'] = t('Workflow current');
  $data['workflow_node_current']['table']['join'] = array(
/*
    // For reference, the relationship used in Workflow versions below 7.x-2.x
    // 'node' => array(
    //   'table' => 'workflow_node_history',
    //   'field' => 'nid',
    //   'left_table' => 'workflow_node',
    //   'left_field' => 'nid',
    //   'extra' => 'workflow_node.stamp = workflow_node_current.stamp AND workflow_node.nid = workflow_node_current.nid',
    // ),
 */
    'node' => array(
      'table' => 'workflow_node_history',
      'field' => 'hid',
      'left_table' => 'node',
      'left_field' => 'nid',
      // Do not use the default 'views_join', but add a subquery.
      'handler' => 'views_join_subquery',
      'left_query' => " SELECT max(hid) FROM {workflow_node_history} where nid = node.nid and sid != old_sid ",
    ),
  );
  $data['workflow_node_current']['sid']['title'] = t('Current state');
  $data['workflow_node_current']['sid']['help'] = t('The current state, from the last state change.');
  $data['workflow_node_current']['old_sid']['title'] = t('Previous state');
  $data['workflow_node_current']['old_sid']['help'] = t('The previous state, from the last state change.');
  $data['workflow_node_current']['comment']['title'] = t('Current comment');
  $data['workflow_node_current']['comment']['help'] = t('The comment describing why the the state change was done.');
  $data['workflow_node_current']['uid']['title'] = t('Current user');
  $data['workflow_node_current']['uid']['help'] = t('The user that executed a state change.');
  $data['workflow_node_current']['stamp']['title'] = t('Time');
  $data['workflow_node_current']['stamp']['help'] = t('The time of the last state change.');

  // This group's help and title are moved from hook_views_data to _alter(), to avoid Notices.
  $data['workflow_scheduled_transition']['table']['group'] = t('Workflow scheduled');
  $data['workflow_scheduled_transition']['table']['join'] = array(
    'node' => array(
      'field' => 'nid',
      'left_table' => 'node',
      'left_field' => 'nid',
    ),
  );
  $data['workflow_scheduled_transition']['old_sid']['field']['handler'] = 'workflow_views_handler_field_sid';
  $data['workflow_scheduled_transition']['old_sid']['filter']['handler'] = 'workflow_views_handler_filter_sid';
  $data['workflow_scheduled_transition']['sid']['field']['handler'] = 'workflow_views_handler_field_sid';
  $data['workflow_scheduled_transition']['sid']['filter']['handler'] = 'workflow_views_handler_filter_sid';
  $data['workflow_scheduled_transition']['uid']['field']['handler'] = 'workflow_views_handler_field_username';
  $data['workflow_scheduled_transition']['uid']['filter']['handler'] = 'views_handler_filter_user_name';
  $data['workflow_scheduled_transition']['uid']['relationship'] = array(
    'handler' => 'views_handler_relationship',
    'base' => 'users',
    'base field' => 'uid',
    'label' => t('Scheduling user'),
  );
  $data['workflow_scheduled_transition']['comment']['field']['handler'] = 'views_handler_field_xss';
  $data['workflow_scheduled_transition']['comment']['filter']['handler'] = 'views_handler_filter_string';
  $data['workflow_scheduled_transition']['scheduled']['field']['handler'] = 'views_handler_field_date';
  $data['workflow_scheduled_transition']['scheduled']['filter']['handler'] = 'views_handler_filter_date';
  $data['workflow_scheduled_transition']['scheduled']['sort']['handler'] = 'views_handler_sort_date';
  // This group's help and title are moved from hook_views_data to _alter(), to avoid Notices.
  $data['workflow_scheduled_transition']['old_sid']['title'] = t('Current state');
  $data['workflow_scheduled_transition']['old_sid']['help'] = t('The current state that the node is in.');
  $data['workflow_scheduled_transition']['sid']['title'] = t('Scheduled state');
  $data['workflow_scheduled_transition']['sid']['help'] = t('The state, the node is scheduled for.');
  $data['workflow_scheduled_transition']['uid']['title'] = t('Scheduling user');
  $data['workflow_scheduled_transition']['uid']['help'] = t('The user that scheduled the state change.');
  $data['workflow_scheduled_transition']['comment']['title'] = t('Scheduled comment');
  $data['workflow_scheduled_transition']['comment']['help'] = t('A comment describing why the node was scheduled for state transition.');
  // Scheduled transitions do not have a stamp, but are scheduled.
  $data['workflow_scheduled_transition']['scheduled']['title'] = t('Scheduled time');
  $data['workflow_scheduled_transition']['scheduled']['help'] = t('The time at which the node will change workflow states.');

  // Workflow node.
  // Only use when 'Workflow Node' is active. Use separate title.
  if (module_exists('workflownode')) {
    $data['workflow_node'] = $data['workflow_node_history'];
    $data['workflow_node']['table']['group'] = t('Workflow node');
    $data['workflow_node']['table']['join'] = array(
      'node' => array(
        'field' => 'nid',
        'left_table' => 'node',
        'left_field' => 'nid',
      ),
    );
    // Workflow Node does not have these fields.
    unset($data['workflow_node']['hid']);
    unset($data['workflow_node']['entity_type']);
    unset($data['workflow_node']['field_name']);
    unset($data['workflow_node']['delta']);
    unset($data['workflow_node']['language']);
    unset($data['workflow_node']['old_sid']);
    $data['workflow_node']['sid']['title'] = t('Current state');
    $data['workflow_node']['sid']['help'] = t('The current workflow state that the node is in.');
    $data['workflow_node']['comment']['title'] = t('Scheduled comment');
    $data['workflow_node']['comment']['help'] = t('A comment describing why the node was scheduled for state transition.');
    $data['workflow_node']['uid']['title'] = t('Last changing user');
    $data['workflow_node']['uid']['help'] = t('The user who performed the last state change.');
    $data['workflow_node']['stamp']['title'] = t('Current time');
    $data['workflow_node']['stamp']['help'] = t('The time at which the node moved to the current state.');

    // The following 'uid' handlers are different between 'workflow node' and
    // the other ones. At the moment of rewriting in 2013: I'm not sure what's best,
    // and I don't want to break anything, so I'll just leave this untouched.
    unset($data['workflow_node']['uid']['argument']);
    unset($data['workflow_node']['uid']['filter']);
    $data['workflow_node']['uid'] += array(
      'filter' => array(
        'handler' => 'views_handler_filter_user_name',
        'numeric' => TRUE,
        'name table' => 'workflow_node',
        'name field' => 'uid',
      ),
      'argument' => array(
        'handler' => 'views_handler_argument_user_uid',
        'click sortable' => TRUE,
        'name table' => 'workflow_node',
        'name field' => 'uid',
      ),
    );
  }

  // Workflow states.
  // @todo: implement this as a proper relationship (like 'user').
  // To support Workflow Field, do not use workflow_node.
  if (module_exists('workflownode')) {
    $data['workflow_states']['table']['group'] = t('Workflow states (deprecated)');
    $data['workflow_states']['table']['join'] = array(
      'node' => array(
        'field' => 'sid',
        'left_table' => 'workflow_node',
        'left_field' => 'sid',
      ),
    );
    $data['workflow_states']['weight'] = array(
      'title' => t('State weight'),
      'help' => t('The weight of the current workflow state that the node is in.'),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
    );
    $data['workflow_states']['state'] = array(
      'title' => t('Current state name'),
      'help' => t('The readable name of the workflow state that the node is in. (Less efficient, use only when click-sorting by state name.)'),
      'field' => array(
        'handler' => 'workflow_views_handler_field_state',
        'click sortable' => TRUE,
      ),
    );
  }

  $data['entity_WorkflowConfigTransition']['target_sid']['field']['handler'] = 'workflow_views_handler_field_sid';
  $data['entity_WorkflowConfigTransition']['target_sid']['filter']['handler'] = 'workflow_views_handler_filter_sid';
  $data['entity_WorkflowConfigTransition']['sid']['field']['handler'] = 'workflow_views_handler_field_sid';
  $data['entity_WorkflowConfigTransition']['sid']['filter']['handler'] = 'workflow_views_handler_filter_sid';

  $data['entity_WorkflowTransition']['old_sid']['field']['handler'] = 'workflow_views_handler_field_sid';
  $data['entity_WorkflowTransition']['old_sid']['filter']['handler'] = 'workflow_views_handler_filter_sid';
  $data['entity_WorkflowTransition']['sid']['field']['handler'] = 'workflow_views_handler_field_sid';
  $data['entity_WorkflowTransition']['sid']['filter']['handler'] = 'workflow_views_handler_filter_sid';
  $data['entity_WorkflowTransition']['uid']['field']['handler'] = 'workflow_views_handler_field_username';
  $data['entity_WorkflowTransition']['uid']['filter']['handler'] = 'views_handler_filter_user_name';
  $data['entity_WorkflowTransition']['comment']['field']['handler'] = 'views_handler_field_xss';
  $data['entity_WorkflowTransition']['comment']['filter']['handler'] = 'views_handler_filter_string';
  $data['entity_WorkflowTransition']['stamp']['field']['handler'] = 'views_handler_field_date';
  $data['entity_WorkflowTransition']['stamp']['filter']['handler'] = 'views_handler_filter_date';
  $data['entity_WorkflowTransition']['stamp']['sort']['handler'] = 'views_handler_sort_date';

  $data['entity_WorkflowScheduledTransition']['old_sid']['field']['handler'] = 'workflow_views_handler_field_sid';
  $data['entity_WorkflowScheduledTransition']['old_sid']['filter']['handler'] = 'workflow_views_handler_filter_sid';
  $data['entity_WorkflowScheduledTransition']['sid']['field']['handler'] = 'workflow_views_handler_field_sid';
  $data['entity_WorkflowScheduledTransition']['sid']['filter']['handler'] = 'workflow_views_handler_filter_sid';
  $data['entity_WorkflowScheduledTransition']['uid']['field']['handler'] = 'workflow_views_handler_field_username';
  $data['entity_WorkflowScheduledTransition']['uid']['filter']['handler'] = 'views_handler_filter_user_name';
  $data['entity_WorkflowScheduledTransition']['comment']['field']['handler'] = 'views_handler_field_xss';
  $data['entity_WorkflowScheduledTransition']['comment']['filter']['handler'] = 'views_handler_filter_string';
  $data['entity_WorkflowScheduledTransition']['scheduled']['field']['handler'] = 'views_handler_field_date';
  $data['entity_WorkflowScheduledTransition']['scheduled']['filter']['handler'] = 'views_handler_filter_date';
  $data['entity_WorkflowScheduledTransition']['scheduled']['sort']['handler'] = 'views_handler_sort_date';
}

/**
 * Implements hook_views_data().
 */
function workflow_views_views_data() {

  // A 'workflow link'.
  $data['node']['workflow_node']['moved to'] = array('views_entity_node', 'workflow_node');
  $data['views_entity_node']['workflow_node'] = array(
    'field' => array(
      'title' => t('Workflow link'),
      'help' => t('Provide a link to the workflow history tab to change the state of the content.'),
      'handler' => 'workflow_views_handler_field_node_link_workflow',
    ),
  );

  return $data;
}
