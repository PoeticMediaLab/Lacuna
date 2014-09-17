<?php
/**
 * @file
 * lacuna_stories_permissions.features.workflow_access.inc
 */

/**
 * Implements hook_workflow_access_features_default_settings().
 */
function lacuna_stories_permissions_workflow_access_features_default_settings() {
  $workflows = array();

  $workflows['materials_publication_states'] = array();
  $workflows['materials_publication_states']['draft'] = array();
  $workflows['materials_publication_states']['draft']['workflow_features_author_name'] = array(
    'grant_view' => 1,
    'grant_update' => 1,
    'grant_delete' => 1,
  );
  $workflows['materials_publication_states']['draft']['administrator'] = array(
    'grant_view' => 1,
    'grant_update' => 1,
    'grant_delete' => 1,
  );
  $workflows['materials_publication_states']['draft']['Content Manager'] = array(
    'grant_view' => 1,
    'grant_update' => 1,
    'grant_delete' => 1,
  );
  $workflows['materials_publication_states']['draft']['Instructor'] = array(
    'grant_view' => 1,
    'grant_update' => 1,
    'grant_delete' => 1,
  );
  $workflows['materials_publication_states']['draft']['Student'] = array(
    'grant_view' => 0,
    'grant_update' => 0,
    'grant_delete' => 0,
  );
  $workflows['materials_publication_states']['ready_for_annotation'] = array();
  $workflows['materials_publication_states']['ready_for_annotation']['workflow_features_author_name'] = array(
    'grant_view' => 1,
    'grant_update' => 0,
    'grant_delete' => 0,
  );
  $workflows['materials_publication_states']['ready_for_annotation']['administrator'] = array(
    'grant_view' => 1,
    'grant_update' => 1,
    'grant_delete' => 1,
  );
  $workflows['materials_publication_states']['ready_for_annotation']['Content Manager'] = array(
    'grant_view' => 1,
    'grant_update' => 1,
    'grant_delete' => 1,
  );
  $workflows['materials_publication_states']['ready_for_annotation']['Instructor'] = array(
    'grant_view' => 1,
    'grant_update' => 0,
    'grant_delete' => 0,
  );
  $workflows['materials_publication_states']['ready_for_annotation']['Student'] = array(
    'grant_view' => 1,
    'grant_update' => 0,
    'grant_delete' => 0,
  );

  return $workflows;
}
