<?php
/**
 * @file
 * lacuna_stories_peer_groups.ds.inc
 */

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
