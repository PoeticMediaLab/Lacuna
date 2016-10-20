<?php
/**
 * @file
 * lti_configuration.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function lti_configuration_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'access lti_tool_provider_consumer entities'.
  $permissions['access lti_tool_provider_consumer entities'] = array(
    'name' => 'access lti_tool_provider_consumer entities',
    'roles' => array(
      'Site Administrator' => 'Site Administrator',
    ),
    'module' => 'lti_tool_provider',
  );

  // Exported permission: 'administer lti resources'.
  $permissions['administer lti resources'] = array(
    'name' => 'administer lti resources',
    'roles' => array(
      'Student' => 'Student',
    ),
    'module' => 'lacuna_lti',
  );

  // Exported permission: 'administer lti_tool_provider module'.
  $permissions['administer lti_tool_provider module'] = array(
    'name' => 'administer lti_tool_provider module',
    'roles' => array(
      'Site Administrator' => 'Site Administrator',
    ),
    'module' => 'lti_tool_provider',
  );

  // Exported permission: 'populate lti memberships'.
  $permissions['populate lti memberships'] = array(
    'name' => 'populate lti memberships',
    'roles' => array(
      'Site Administrator' => 'Site Administrator',
    ),
    'module' => 'lti_tool_provider_memberships',
  );

  // Exported permission: 'search lti resources'.
  $permissions['search lti resources'] = array(
    'name' => 'search lti resources',
    'roles' => array(
      'Student' => 'Student',
    ),
    'module' => 'lacuna_lti',
  );

  // Exported permission: 'view lti info'.
  $permissions['view lti info'] = array(
    'name' => 'view lti info',
    'roles' => array(
      'Site Administrator' => 'Site Administrator',
    ),
    'module' => 'lti_tool_provider',
  );

  return $permissions;
}
