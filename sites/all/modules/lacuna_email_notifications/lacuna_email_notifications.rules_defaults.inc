<?php
/**
 * @file
 * lacuna_email_notifications.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function lacuna_email_notifications_default_rules_configuration() {
  $items = array();
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
        { "drupal_message" : { "message" : "Well done man" } },
        { "mail" : {
            "to" : [ "node:field-annotation-reference:author:mail" ],
            "subject" : "New Annotation on Your Response",
            "message" : "[node:field-annotation-reference:author:mail] has made an \\u003Ca href=\\u0022lacunastories\\/resposne\\/re-cone\\/[nid]\\u0022\\u003Eannotation\\u003C\\/a\\u003E on your Response \\u0022[node:field-annotation-reference:title]\\u0022",
            "language" : [ "" ]
          }
        }
      ]
    }
  }');
  return $items;
}
