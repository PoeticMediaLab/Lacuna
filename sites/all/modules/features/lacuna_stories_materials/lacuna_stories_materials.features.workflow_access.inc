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
  $workflows['Materials Publication States']['Draft'] = array();
  $workflows['Materials Publication States']['Draft']['workflow_features_author_name'] = array(
    'grant_view' => 1,
    'grant_update' => 1,
    'grant_delete' => 1,
  );
  $workflows['Materials Publication States']['Draft']['Content Manager'] = array(
    'grant_view' => 1,
    'grant_update' => 1,
    'grant_delete' => 1,
  );
  $workflows['Materials Publication States']['Draft']['Instructor'] = array(
    'grant_view' => 1,
    'grant_update' => 1,
    'grant_delete' => 1,
  );
  $workflows['Materials Publication States']['Draft']['Site Administrator'] = array(
    'grant_view' => 1,
    'grant_update' => 1,
    'grant_delete' => 1,
  );
  $workflows['Materials Publication States']['Draft']['administrator'] = array(
    'grant_view' => 1,
    'grant_update' => 1,
    'grant_delete' => 1,
  );
  $workflows['Materials Publication States']['Ready for Annotation'] = array();
  $workflows['Materials Publication States']['Ready for Annotation']['workflow_features_author_name'] = array(
    'grant_view' => 1,
    'grant_update' => 0,
    'grant_delete' => 0,
  );
  $workflows['Materials Publication States']['Ready for Annotation']['Content Manager'] = array(
    'grant_view' => 1,
    'grant_update' => 1,
    'grant_delete' => 1,
  );
  $workflows['Materials Publication States']['Ready for Annotation']['Instructor'] = array(
    'grant_view' => 1,
    'grant_update' => 0,
    'grant_delete' => 0,
  );
  $workflows['Materials Publication States']['Ready for Annotation']['Site Administrator'] = array(
    'grant_view' => 1,
    'grant_update' => 1,
    'grant_delete' => 1,
  );
  $workflows['Materials Publication States']['Ready for Annotation']['administrator'] = array(
    'grant_view' => 1,
    'grant_update' => 0,
    'grant_delete' => 0,
  );

  return $workflows;
}
