<?php
/**
 * @file
 * lacuna_stories_peer_groups.ds.inc
 */

/**
 * Implements hook_ds_field_settings_info().
 */
function lacuna_stories_peer_groups_ds_field_settings_info() {
  $export = array();

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'node|peer_group|default';
  $ds_fieldsetting->entity_type = 'node';
  $ds_fieldsetting->bundle = 'peer_group';
  $ds_fieldsetting->view_mode = 'default';
  $ds_fieldsetting->settings = array(
    'peer_group_members' => array(
      'weight' => '1',
      'label' => 'hidden',
      'format' => 'default',
    ),
  );
  $export['node|peer_group|default'] = $ds_fieldsetting;

  return $export;
}

/**
 * Implements hook_ds_custom_fields_info().
 */
function lacuna_stories_peer_groups_ds_custom_fields_info() {
  $export = array();

  $ds_field = new stdClass();
  $ds_field->api_version = 1;
  $ds_field->field = 'peer_group_members';
  $ds_field->label = 'Peer Group Members';
  $ds_field->field_type = 6;
  $ds_field->entities = array(
    'node' => 'node',
  );
  $ds_field->ui_limit = 'peer_group|*';
  $ds_field->properties = array(
    'block' => 'views|peer_group_members-block_1',
    'block_render' => '1',
  );
  $export['peer_group_members'] = $ds_field;

  return $export;
}

/**
 * Implements hook_ds_layout_settings_info().
 */
function lacuna_stories_peer_groups_ds_layout_settings_info() {
  $export = array();

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|peer_group|default';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'peer_group';
  $ds_layout->view_mode = 'default';
  $ds_layout->layout = 'ds_1col';
  $ds_layout->settings = array(
    'regions' => array(
      'ds_content' => array(
        0 => 'group_group',
        1 => 'peer_group_members',
      ),
    ),
    'fields' => array(
      'group_group' => 'ds_content',
      'peer_group_members' => 'ds_content',
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
  $export['node|peer_group|default'] = $ds_layout;

  return $export;
}
