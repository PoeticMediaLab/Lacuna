<?php
/**
 * @file
 * lacuna_stories_content_types.ds.inc
 */

/**
 * Implements hook_ds_field_settings_info().
 */
function lacuna_stories_content_types_ds_field_settings_info() {
  $export = array();

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'node|thread|default';
  $ds_fieldsetting->entity_type = 'node';
  $ds_fieldsetting->bundle = 'thread';
  $ds_fieldsetting->view_mode = 'default';
  $ds_fieldsetting->settings = array(
    'thread_stitchings' => array(
      'weight' => '4',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'comments' => array(
      'weight' => '5',
      'label' => 'hidden',
      'format' => 'default',
    ),
  );
  $export['node|thread|default'] = $ds_fieldsetting;

  return $export;
}

/**
 * Implements hook_ds_custom_fields_info().
 */
function lacuna_stories_content_types_ds_custom_fields_info() {
  $export = array();

  $ds_field = new stdClass();
  $ds_field->api_version = 1;
  $ds_field->field = 'thread_stitchings';
  $ds_field->label = 'Thread Stitchings';
  $ds_field->field_type = 6;
  $ds_field->entities = array(
    'node' => 'node',
  );
  $ds_field->ui_limit = '';
  $ds_field->properties = array(
    'block' => 'views|stitchings-block',
    'block_render' => '3',
  );
  $export['thread_stitchings'] = $ds_field;

  return $export;
}
