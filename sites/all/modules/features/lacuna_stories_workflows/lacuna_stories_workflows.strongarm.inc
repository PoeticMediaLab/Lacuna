<?php
/**
 * @file
 * lacuna_stories_workflows.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function lacuna_stories_workflows_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'workflow_access_priority';
  $strongarm->value = '-1';
  $export['workflow_access_priority'] = $strongarm;

  return $export;
}
