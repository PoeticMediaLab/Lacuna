<?php
/**
 * @file
 * lacuna_stories_responses.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function lacuna_stories_responses_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_genre_about|node|response|form';
  $field_group->group_name = 'group_genre_about';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'response';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'About',
    'weight' => '4',
    'children' => array(
      0 => 'field_response_genre',
      1 => 'field_tags',
      2 => 'og_group_ref',
      3 => 'field_bibliographic_item',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-genre-about field-group-fieldset',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_genre_about|node|response|form'] = $field_group;

  return $export;
}
