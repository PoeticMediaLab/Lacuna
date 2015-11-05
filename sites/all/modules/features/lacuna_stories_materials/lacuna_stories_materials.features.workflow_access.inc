<?php
/**
 * @file
 * lacuna_stories_materials.features.workflow_access.inc
 */

/**
 * Implements hook_workflow_access_features_default_settings().
 */
function lacuna_stories_materials_workflow_access_features_default_settings() {
  $workflows = array();

  $workflows['Materials Publication States'] = array();

  return $workflows;
}
