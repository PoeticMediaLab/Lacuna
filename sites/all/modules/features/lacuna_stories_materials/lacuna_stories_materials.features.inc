<?php
/**
 * @file
 * lacuna_stories_materials.features.inc
 */

/**
 * Implements hook_default_Workflow().
 */
function lacuna_stories_materials_default_Workflow() {
  $workflows = array();

  // Exported workflow: 'Materials Publication States'
  $workflows['Materials Publication States'] = entity_import('Workflow', '{
    "name" : "Materials Publication States",
    "tab_roles" : [],
    "options" : [],
    "states" : {
      "1" : {"sid":"1","wid":"1","weight":"-50","sysid":"1","state":"(creation)","status":"1","name":"(creation)"},
      "2" : {"sid":"2","wid":"1","weight":"0","sysid":"0","state":"Draft","status":"1","name":"Draft"},
      "3" : {"sid":"3","wid":"1","weight":"0","sysid":"0","state":"Ready for Annotation","status":"1","name":"Ready for Annotation"}
    },
    "transitions" : {
      "1" : {"tid":"1","sid":"1","target_sid":"2","roles":[-1,5,3,4],"wid":"1","name":"1_2","label":"Draft","rdf_mapping":[]},
      "4" : {"tid":"4","sid":"1","target_sid":"3","roles":[5],"wid":"1","name":"1_3","label":"Ready for Annotation","rdf_mapping":[]},
      "2" : {"tid":"2","sid":"2","target_sid":"3","roles":[-1,5,3,4],"wid":"1","name":"2_3","label":"Ready for Annotation","rdf_mapping":[]},
      "3" : {"tid":"3","sid":"3","target_sid":"2","roles":[5,3],"wid":"1","name":"3_2","label":"Draft","rdf_mapping":[]}
    },
    "label" : "Materials Publication States",
    "typeMap" : [],
    "rdf_mapping" : [],
    "wid_original" : "1",
    "system_roles" : {
      "-1" : "(author)",
      "1" : "anonymous user",
      "2" : "authenticated user",
      "5" : "Site Administrator",
      "3" : "Content Manager",
      "4" : "Instructor",
      "6" : "Student",
      "7" : "administrator"
    }
  }');

  return $workflows;
}

/**
 * Implements hook_ctools_plugin_api().
 */
function lacuna_stories_materials_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function lacuna_stories_materials_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function lacuna_stories_materials_node_info() {
  $items = array(
    'document' => array(
      'name' => t('Document'),
      'base' => 'node_content',
      'description' => t('Any primary or secondary documents.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
