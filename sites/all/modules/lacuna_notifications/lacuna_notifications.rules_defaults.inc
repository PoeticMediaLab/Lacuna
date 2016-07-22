<?php
/**
 * @file
 * lacuna_notifications.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function lacuna_notifications_default_rules_configuration() {
  $items = array();
  $items['rules_log_new_group_content'] = entity_import('rules_config', '{ "rules_log_new_group_content" : {
      "LABEL" : "Log New Group Content",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules" ],
      "ON" : { "node_insert" : [] },
      "IF" : [
        { "entity_is_of_bundle" : {
            "entity" : [ "node" ],
            "type" : "node",
            "bundle" : { "value" : {
                "annotation" : "annotation",
                "response" : "response",
                "thread" : "thread"
              }
            }
          }
        }
      ],
      "DO" : [
        { "entity_create" : {
            "USING" : {
              "type" : "message",
              "param_type" : "log_new_content",
              "param_user" : [ "node:author" ]
            },
            "PROVIDE" : { "entity_created" : { "entity_created" : "Created entity" } }
          }
        },
        { "data_set" : {
            "data" : [ "entity-created:field-message-content" ],
            "value" : [ "node" ]
          }
        }
      ]
    }
  }');
  return $items;
}
