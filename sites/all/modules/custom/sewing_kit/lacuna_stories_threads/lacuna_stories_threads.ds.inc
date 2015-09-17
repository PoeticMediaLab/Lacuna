<?php
/**
 * @file
 * lacuna_stories_threads.ds.inc
 */

/**
 * Implements hook_ds_field_settings_info().
 */
function lacuna_stories_threads_ds_field_settings_info() {
  $export = array();

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'node|thread|default';
  $ds_fieldsetting->entity_type = 'node';
  $ds_fieldsetting->bundle = 'thread';
  $ds_fieldsetting->view_mode = 'default';
  $ds_fieldsetting->settings = array(
    'stitchings_block' => array(
      'weight' => '5',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'comments' => array(
      'weight' => '6',
      'label' => 'above',
      'format' => 'default',
    ),
    'submitted_by' => array(
      'weight' => '1',
      'label' => 'hidden',
      'format' => 'ds_post_date_medium',
    ),
    'ds_user_picture' => array(
      'weight' => '0',
      'label' => 'hidden',
      'format' => 'ds_picture_medium',
    ),
  );
  $export['node|thread|default'] = $ds_fieldsetting;

  return $export;
}

/**
 * Implements hook_ds_custom_fields_info().
 */
function lacuna_stories_threads_ds_custom_fields_info() {
  $export = array();

  $ds_field = new stdClass();
  $ds_field->api_version = 1;
  $ds_field->field = 'stitchings_block';
  $ds_field->label = 'Stitchings';
  $ds_field->field_type = 6;
  $ds_field->entities = array(
    'node' => 'node',
  );
  $ds_field->ui_limit = '';
  $ds_field->properties = array(
    'block' => 'views|stitchings-block',
    'block_render' => '1',
  );
  $export['stitchings_block'] = $ds_field;

  return $export;
}

/**
 * Implements hook_ds_layout_settings_info().
 */
function lacuna_stories_threads_ds_layout_settings_info() {
  $export = array();

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|thread|default';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'thread';
  $ds_layout->view_mode = 'default';
  $ds_layout->layout = 'ds_1col';
  $ds_layout->settings = array(
    'classes' => array(),
    'wrappers' => array(
      'ds_content' => 'div',
    ),
    'layout_wrapper' => 'div',
    'layout_attributes' => '',
    'layout_attributes_merge' => 1,
    'layout_link_attribute' => '',
    'layout_link_custom' => '',
    'layout_disable_css' => FALSE,
    'regions' => array(
      'ds_content' => array(
        0 => 'ds_user_picture',
        1 => 'submitted_by',
        2 => 'field_image',
        3 => 'field_tags',
        4 => 'thread_description',
        5 => 'stitchings_block',
        6 => 'comments',
      ),
    ),
    'fields' => array(
      'ds_user_picture' => 'ds_content',
      'submitted_by' => 'ds_content',
      'field_image' => 'ds_content',
      'field_tags' => 'ds_content',
      'thread_description' => 'ds_content',
      'stitchings_block' => 'ds_content',
      'comments' => 'ds_content',
    ),
  );
  $export['node|thread|default'] = $ds_layout;

  return $export;
}
