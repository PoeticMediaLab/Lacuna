<?php
/**
 * @file
 * lacuna_stories_people.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function lacuna_stories_people_field_group_info() {
  $field_groups = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_biographical|user|user|form';
  $field_group->group_name = 'group_biographical';
  $field_group->entity_type = 'user';
  $field_group->bundle = 'user';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Biographical',
    'weight' => '2',
    'children' => array(
      0 => 'field_about_me',
      1 => 'field_date_of_birth',
      2 => 'field_display_name',
      3 => 'field_gender',
      4 => 'picture',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-biographical field-group-fieldset',
        'required_fields' => 1,
      ),
    ),
  );
  $field_groups['group_biographical|user|user|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_education|user|user|form';
  $field_group->group_name = 'group_education';
  $field_group->entity_type = 'user';
  $field_group->bundle = 'user';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Education',
    'weight' => '5',
    'children' => array(
      0 => 'field_education',
      1 => 'field_major_degree',
      2 => 'field_year_in_program',
      3 => 'og_user_node',
      4 => 'og_user_node1',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-education field-group-fieldset',
        'required_fields' => 1,
      ),
    ),
  );
  $field_groups['group_education|user|user|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_learning|user|user|form';
  $field_group->group_name = 'group_learning';
  $field_group->entity_type = 'user';
  $field_group->bundle = 'user';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Learning',
    'weight' => '3',
    'children' => array(
      0 => 'field_how_i_learn',
      1 => 'field_learning_goals',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-learning field-group-fieldset',
        'required_fields' => 1,
      ),
    ),
  );
  $field_groups['group_learning|user|user|form'] = $field_group;

  // Translatables
  // Included for use with string extractors like potx.
  t('Biographical');
  t('Education');
  t('Learning');

  return $field_groups;
}
