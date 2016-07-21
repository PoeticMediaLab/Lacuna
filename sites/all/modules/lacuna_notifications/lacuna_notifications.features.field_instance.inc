<?php
/**
 * @file
 * lacuna_notifications.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function lacuna_notifications_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'message-log_new_content-field_message_content'.
  $field_instances['message-log_new_content-field_message_content'] = array(
    'bundle' => 'log_new_content',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'entityreference',
        'settings' => array(
          'link' => FALSE,
        ),
        'type' => 'entityreference_label',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'message',
    'field_name' => 'field_message_content',
    'label' => 'Content',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_buttons',
      'weight' => 1,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Content');

  return $field_instances;
}
