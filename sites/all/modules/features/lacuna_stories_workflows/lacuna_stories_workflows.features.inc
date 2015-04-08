<?php
/**
 * @file
 * lacuna_stories_workflows.features.inc
 */

/**
 * Implements hook_default_Workflow().
 */
function lacuna_stories_workflows_default_Workflow() {
  $workflows = array();

  // Exported workflow: 'materials_publication_states'
  $workflows['materials_publication_states'] = entity_import('Workflow', '{
    "name" : "materials_publication_states",
    "tab_roles" : [],
    "options" : [],
    "states" : {
      "4" : {"sid":"4","wid":"2","weight":"-50","sysid":"1","state":"(creation)","status":"1","name":"(creation)"},
      "5" : {"sid":"5","wid":"2","weight":"-20","sysid":"0","state":"Draft","status":"1","name":"draft"},
      "6" : {"sid":"6","wid":"2","weight":"-19","sysid":"0","state":"Ready for Annotation","status":"1","name":"ready_for_annotation"}
    },
    "transitions" : {
      "35" : {"tid":"35","sid":"4","target_sid":"5","roles":{"-1":-1,"3":3,"4":4,"5":5},"wid":"2","name":"4_5","label":"","rdf_mapping":[]},
      "36" : {"tid":"36","sid":"4","target_sid":"6","roles":{"3":3},"wid":"2","name":"4_6","label":"","rdf_mapping":[]},
      "37" : {"tid":"37","sid":"5","target_sid":"5","roles":{"-1":-1,"3":3,"4":4,"5":5,"6":6},"wid":"2","name":"5_5","label":"","rdf_mapping":[]},
      "38" : {"tid":"38","sid":"5","target_sid":"6","roles":{"-1":-1,"3":3,"4":4,"5":5},"wid":"2","name":"5_6","label":"","rdf_mapping":[]},
      "39" : {"tid":"39","sid":"6","target_sid":"5","roles":{"-1":-1,"3":3,"4":4},"wid":"2","name":"6_5","label":"","rdf_mapping":[]},
      "40" : {"tid":"40","sid":"6","target_sid":"6","roles":{"-1":-1,"3":3,"4":4,"5":5,"6":6},"wid":"2","name":"6_6","label":"","rdf_mapping":[]}
    },
    "label" : "Materials Publication States",
    "typeMap" : [],
    "rdf_mapping" : [],
    "wid_original" : "2",
    "system_roles" : {
      "-1" : "(author)",
      "1" : "anonymous user",
      "2" : "authenticated user",
      "3" : "administrator",
      "4" : "Content Manager",
      "5" : "Instructor",
      "6" : "Student"
    }
  }');

  return $workflows;
}
