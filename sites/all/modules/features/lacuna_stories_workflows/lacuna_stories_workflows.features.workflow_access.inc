<?php
/**
 * @file
 * lacuna_stories_workflows.features.workflow_access.inc
 */

/**
 * Implements hook_workflow_access_features_default_settings().
 */
function lacuna_stories_workflows_workflow_access_features_default_settings() {
  $workflows = array();

  $workflows['materials_publication_states'] = array();

  return $workflows;
}
