<?php
/**
 * @file
 * lacuna_stories_people.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function lacuna_stories_people_default_rules_configuration() {
  $items = array();
  $items['rules_automatically_assign_student_role'] = entity_import('rules_config', '{ "rules_automatically_assign_student_role" : {
      "LABEL" : "Automatically Assign Student Role",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules" ],
      "ON" : { "user_insert" : [] },
      "DO" : [
        { "user_add_role" : { "account" : [ "account" ], "roles" : { "value" : { "7" : "7" } } } }
      ]
    }
  }');
  return $items;
}
