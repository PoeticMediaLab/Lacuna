<?php
/**
 * @file
 * lti_configuration.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function lti_configuration_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'lti_tool_provider_global_role_array';
  $strongarm->value = array(
    'Learner' => '6',
    'Instructor' => '4',
    'ContentDeveloper' => '3',
    'Member' => '2',
    'Manager' => '3',
    'Mentor' => '4',
    'Administrator' => '3',
    'TeachingAssistant' => '4',
  );
  $export['lti_tool_provider_global_role_array'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'lti_tool_provider_memberships_subgroups';
  $strongarm->value = 1;
  $export['lti_tool_provider_memberships_subgroups'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'lti_tool_provider_memberships_subgroup_mapping';
  $strongarm->value = array(
    'group_id' => 'field_group_description',
    'title' => 'title',
    'LTI context group reference' => 'og_group_ref',
  );
  $export['lti_tool_provider_memberships_subgroup_mapping'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'lti_tool_provider_memberships_subgroup_mapping_bundle';
  $strongarm->value = 'node:peer_group';
  $export['lti_tool_provider_memberships_subgroup_mapping_bundle'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'lti_tool_provider_memberships_subgroup_role_array';
  $strongarm->value = array(
    'Learner' => '5',
    'Instructor' => '5',
    'ContentDeveloper' => '5',
    'Member' => '5',
    'Manager' => '5',
    'Mentor' => '5',
    'Administrator' => '5',
    'TeachingAssistant' => '5',
  );
  $export['lti_tool_provider_memberships_subgroup_role_array'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'lti_tool_provider_og_group_mapping';
  $strongarm->value = array(
    'context_id' => 'field_lms_id',
    'context_label' => 'field_course_id',
    'context_title' => 'title',
    'context_type' => 'none',
  );
  $export['lti_tool_provider_og_group_mapping'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'lti_tool_provider_og_group_mapping_bundle';
  $strongarm->value = 'node:course';
  $export['lti_tool_provider_og_group_mapping_bundle'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'lti_tool_provider_og_group_role_array';
  $strongarm->value = array(
    'Learner' => '2',
    'Instructor' => '1',
    'ContentDeveloper' => '1',
    'Member' => '2',
    'Manager' => '1',
    'Mentor' => '1',
    'Administrator' => '1',
    'TeachingAssistant' => '1',
  );
  $export['lti_tool_provider_og_group_role_array'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'lti_tool_provider_og_provision_groups';
  $strongarm->value = 1;
  $export['lti_tool_provider_og_provision_groups'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'lti_tool_provider_og_provision_groups_anon';
  $strongarm->value = 0;
  $export['lti_tool_provider_og_provision_groups_anon'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'lti_tool_provider_user_attribute_mapping';
  $strongarm->value = array(
    'lis_person_name_given' => 'none',
    'lis_person_name_family' => 'none',
    'lis_person_name_full' => 'field_display_name',
  );
  $export['lti_tool_provider_user_attribute_mapping'] = $strongarm;

  return $export;
}
