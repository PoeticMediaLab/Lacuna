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
  $items['rules_log_new_comment_on_response'] = entity_import('rules_config', '{ "rules_log_new_comment_on_response" : {
      "LABEL" : "Log New Comment on Response",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules", "comment" ],
      "ON" : { "comment_insert--comment_node_response" : { "bundle" : "comment_node_response" } },
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
        }
      ]
    }
  }');
  $items['rules_log_new_comment_on_thread'] = entity_import('rules_config', '{ "rules_log_new_comment_on_thread" : {
      "LABEL" : "Log New Comment on Thread",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules", "comment" ],
      "ON" : { "comment_insert--comment_node_thread" : { "bundle" : "comment_node_thread" } },
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
  $items['rules_notification_of_annotation_on_response'] = entity_import('rules_config', '{ "rules_notification_of_annotation_on_response" : {
      "LABEL" : "Notification of Annotation on Response",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules" ],
      "ON" : { "node_insert--annotation" : { "bundle" : "annotation" } },
      "IF" : [
        { "data_is" : {
            "data" : [ "node:field-annotation-reference:type" ],
            "value" : "response"
          }
        },
        { "AND" : [] },
        { "NOT data_is" : {
            "data" : [ "node:author" ],
            "value" : [ "node:field-annotation-reference:author" ]
          }
        },
        { "AND" : [] },
        { "list_contains" : { "list" : [ "node:field-annotation-audience" ], "item" : "everyone" } }
      ],
      "DO" : [
        { "mail" : {
            "to" : [ "node:field-annotation-reference:author:mail" ],
            "subject" : "New Annotation on Your Response",
            "message" : "[node:author:field-display-name] made an annotation on your Response [node:field-annotation-reference:title]",
            "language" : [ "" ]
          }
        }
      ]
    }
  }');
  return $items;
}
