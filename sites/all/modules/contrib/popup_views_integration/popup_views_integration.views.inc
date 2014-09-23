<?php

/**
 * @file
 * Defines the Views new fields.
 */

/**
 * Implements hook_views_data()
 */
function popup_views_integration_views_data() {

  $data = array();
  
  $data['popup_views_integration']['table']['group'] = t('Global');

  $data['popup_views_integration']['table']['join'] = array(
    '#global' => array(),
  );

  $data['popup_views_integration']['popup'] = array(
    'group' => t('Global'),
    'field' => array(
      'title' => t('Popup'),
      'help' => t('Provide popup capability.'),
      'handler' => 'popup_views_integration_handler_field_popup',
    ),
  );

  return $data;
}
