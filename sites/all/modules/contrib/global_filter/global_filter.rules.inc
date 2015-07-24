<?php

/**
 * @file
 * Views Global Filter Rules integration.
 */

/**
 * Implements hook_rules_action_info().
 */
function global_filter_rules_action_info() {
  $actions = array(
     // Register method to set the Global Filter as a Rules action.
    'global_filter_action_set_filter' => array(
      'label' => t('Set a Views Global Filter'),
      'group' => t('Views Global Filter'),
      'parameter' => array(
        'global_filter_name' => array(
          'type' => 'text',
          'label' => t('Global Filter name'),
          'options list' => 'global_filter_active_filter_names_list',
          'save' => FALSE,
        ),
        'global_filter_value' => array(
          'type' => 'text',
          'label' => t('Global Filter value'),
          'save' => FALSE,
        ),
      ),
    ),
  );

  return $actions;
}

/**
 * Implements hook_rules_event_info().
 */
function global_filter_rules_event_info() {
  $events = array();

  $events['global_filter_set_filter_done'] = array(
    'label' => t('A Views Global Filter has been set'),
    'group' => t('Views Global Filter'),
    'variables' => array(
      'filter_name' => array(
        'type' => 'text',
        'label' => t('The Global Filter name'),
        'options list' => 'global_filter_active_filter_names_list',
      ),
      'filter_value' => array(
        'type' => 'text',
        'label' => t('The Global Filter value'),
      ),
    ),
  );

  return $events;
}

/**
 * The action function for the 'global_filter_action_set_filter'.
 *
 * @param string $name
 *   eg 'field_country', must not be empty.
 * @param mixed $value
 *   to be set to filter of $name.
 */
function global_filter_action_set_filter($name, $value) {
  global_filter_set_on_session($name, $value);
}
