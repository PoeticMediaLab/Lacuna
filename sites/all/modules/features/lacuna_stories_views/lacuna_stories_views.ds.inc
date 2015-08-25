<?php
/**
 * @file
 * lacuna_stories_views.ds.inc
 */

/**
 * Implements hook_ds_layout_settings_info().
 */
function lacuna_stories_views_ds_layout_settings_info() {
  $export = array();

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|thread|default';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'thread';
  $ds_layout->view_mode = 'default';
  $ds_layout->layout = 'ds_1col';
  $ds_layout->settings = array(
    'regions' => array(
      'ds_content' => array(
        0 => 'field_image',
        1 => 'thread_description',
        2 => 'field_tags',
        3 => 'og_group_ref',
        4 => 'thread_stitchings',
        5 => 'comments',
      ),
    ),
    'fields' => array(
      'field_image' => 'ds_content',
      'thread_description' => 'ds_content',
      'field_tags' => 'ds_content',
      'og_group_ref' => 'ds_content',
      'thread_stitchings' => 'ds_content',
      'comments' => 'ds_content',
    ),
    'classes' => array(),
    'wrappers' => array(
      'ds_content' => 'div',
    ),
    'layout_wrapper' => 'div',
    'layout_attributes' => '',
    'layout_attributes_merge' => 1,
    'layout_link_attribute' => '',
    'layout_link_custom' => '',
  );
  $export['node|thread|default'] = $ds_layout;

  return $export;
}
