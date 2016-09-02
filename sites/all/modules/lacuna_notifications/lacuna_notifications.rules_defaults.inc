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
  $items['rules_log_new_annotation_on_response'] = entity_import('rules_config', '{ "rules_log_new_annotation_on_response" : {
      "LABEL" : "Log New Annotation on Response",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules", "flag" ],
      "ON" : { "node_insert--annotation" : { "bundle" : "annotation" } },
      "IF" : [
        { "data_is" : {
            "data" : [ "node:field-annotation-reference:type" ],
            "value" : "response"
          }
        },
        { "list_contains" : { "list" : [ "node:field-annotation-audience" ], "item" : "everyone" } },
        { "NOT data_is" : {
            "data" : [ "node:field-annotation-reference:author" ],
            "value" : [ "node:author" ]
          }
        }
      ],
      "DO" : [
        { "flag_flaguser" : {
            "flag" : "user_notifications_flag",
            "user" : [ "node:field-annotation-reference:author" ],
            "flagging_user" : [ "node:author" ],
            "permission_check" : "1"
          }
        },
        { "drupal_message" : { "message" : "hey good job" } }
      ]
    }
  }');
  $items['rules_log_new_comment_on_response'] = entity_import('rules_config', '{ "rules_log_new_comment_on_response" : {
      "LABEL" : "Log New Comment on Response",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules", "flag", "comment" ],
      "ON" : { "comment_insert--comment_node_response" : { "bundle" : "comment_node_response" } },
      "IF" : [
        { "NOT data_is" : { "data" : [ "comment:author" ], "value" : [ "comment:node:author" ] } }
      ],
      "DO" : [
        { "entity_create" : {
            "USING" : {
              "type" : "message",
              "param_type" : "log_new_comment",
              "param_user" : [ "comment:author" ]
            },
            "PROVIDE" : { "entity_created" : { "entity_created" : "Created entity" } }
          }
        },
        { "data_set" : {
            "data" : [ "entity-created:field-message-comment" ],
            "value" : [ "comment" ]
          }
        },
        { "flag_flaguser" : {
            "flag" : "user_notifications_flag",
            "user" : [ "comment:node:author" ],
            "flagging_user" : [ "comment:author" ],
            "permission_check" : "1"
          }
        }
      ]
    }
  }');
  $items['rules_log_new_comment_on_thread'] = entity_import('rules_config', '{ "rules_log_new_comment_on_thread" : {
      "LABEL" : "Log New Comment on Thread",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules", "flag", "comment" ],
      "ON" : { "comment_insert--comment_node_thread" : { "bundle" : "comment_node_thread" } },
      "IF" : [
        { "NOT data_is" : { "data" : [ "comment:author" ], "value" : [ "comment:node:author" ] } }
      ],
      "DO" : [
        { "entity_create" : {
            "USING" : {
              "type" : "message",
              "param_type" : "log_new_comment",
              "param_user" : [ "comment:author" ]
            },
            "PROVIDE" : { "entity_created" : { "entity_created" : "Created entity" } }
          }
        },
        { "data_set" : {
            "data" : [ "entity-created:field-message-comment" ],
            "value" : [ "comment" ]
          }
        },
        { "flag_flaguser" : {
            "flag" : "user_notifications_flag",
            "user" : [ "comment:node:author" ],
            "flagging_user" : [ "comment:author" ],
            "permission_check" : "1"
          }
        }
      ]
    }
  }');
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
