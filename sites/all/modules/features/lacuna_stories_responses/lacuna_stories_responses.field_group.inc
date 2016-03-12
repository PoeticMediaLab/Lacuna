<?php
/**
 * @file
 * lacuna_stories_responses.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function lacuna_stories_responses_field_group_info() {
  $field_groups = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_about|node|response|default';
  $field_group->group_name = 'group_about';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'response';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'About',
    'weight' => '2',
    'children' => array(
      0 => 'field_response_genre',
      1 => 'field_bibliographic_item',
      2 => 'field_tags',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-about field-group-fieldset',
      ),
    ),
  );
  $field_groups['group_about|node|response|default'] = $field_group;

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
      0 => 'field_bibliographic_item',
      1 => 'field_response_genre',
      2 => 'field_tags',
      3 => 'og_group_ref',
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
  $field_groups['group_genre_about|node|response|form'] = $field_group;

  // Translatables
  // Included for use with string extractors like potx.
  t('About');

  return $field_groups;
}
