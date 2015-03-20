<?php
/**
 * @file
 * lacuna_stories_workflows.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function lacuna_stories_workflows_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'field_status'
  $field_bases['field_status'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_status',
    'field_permissions' => array(
      'type' => 2,
    ),
    'indexes' => array(
      'value' => array(
        0 => 'value',
      ),
    ),
    'locked' => 0,
    'module' => 'workflowfield',
    'settings' => array(
      'allowed_values_function' => 'workflowfield_allowed_values',
      'allowed_values_string' => '1 | (creation)
2 | Draft
3 | Ready for Annotation',
      'history' => array(
        'history_tab_show' => 1,
        'roles' => array(
          -1 => 0,
          3 => 3,
          4 => 4,
          5 => 0,
          6 => 0,
        ),
      ),
      'watchdog_log' => 1,
      'wid' => 1,
      'widget' => array(
        'comment' => 1,
        'name_as_title' => 1,
        'options' => 'select',
        'schedule' => 0,
        'schedule_timezone' => 0,
      ),
    ),
    'translatable' => 0,
    'type' => 'workflow',
  );

  return $field_bases;
}
