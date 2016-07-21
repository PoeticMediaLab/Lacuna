<?php
/**
 * @file
 * lacuna_notifications.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function lacuna_notifications_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'field_bundle_settings_message__log_new_content';
  $strongarm->value = array(
    'view_modes' => array(),
    'extra_fields' => array(
      'form' => array(),
      'display' => array(),
    ),
  );
  $export['field_bundle_settings_message__log_new_content'] = $strongarm;

  return $export;
}
