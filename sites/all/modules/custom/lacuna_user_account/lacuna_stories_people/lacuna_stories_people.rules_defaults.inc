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
      "REQUIRES" : [ "rules", "logintoboggan_rules" ],
      "ON" : { "logintoboggan_validated" : [] },
      "DO" : [
        { "user_remove_role" : { "account" : [ "account" ], "roles" : { "value" : { "9" : "9" } } } },
        { "user_add_role" : { "account" : [ "account" ], "roles" : { "value" : { "6" : "6" } } } }
      ]
    }
  }');
  return $items;
}
