<?php
/**
 * @file
 * lacuna_stories_annotations.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function lacuna_stories_annotations_default_rules_configuration() {
  $items = array();
  $items['rules_notification_about_new_annotation'] = entity_import('rules_config', '{ "rules_notification_about_new_annotation" : {
      "LABEL" : "Notification about new Annotation",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules" ],
      "ON" : { "node_insert--annotation" : { "bundle" : "annotation" } },
      "IF" : [
        { "node_is_of_type" : {
            "node" : [ "node:field-annotation-reference" ],
            "type" : { "value" : { "response" : "response", "thread" : "thread" } }
          }
        },
        { "NOT data_is" : {
            "data" : [ "node:author" ],
            "value" : [ "node:field-annotation-reference:author" ]
          }
        },
        { "data_is" : {
            "data" : [ "node:field-annotation-audience" ],
            "value" : { "value" : { "everyone" : "everyone" } }
          }
        }
      ],
      "DO" : [
        { "mail" : {
            "to" : [ "node:field-annotation-reference:author:mail" ],
            "subject" : "New annotation of [node:field-annotation-reference:title] on Lacuna Stories: [site:name]",
            "message" : "Dear [node:field-annotation-reference:author:field-display-name],\\r\\n\\r\\nYour post on Lacuna Stories: [site:name], \\u0022[node:field-annotation-reference:title]\\u0022 has been annotated by [node:author:field-display-name]:\\r\\n\\r\\n[node:text]\\r\\n\\r\\nTo view this annotation, visit the following link:\\r\\n\\r\\n[node:field-annotation-reference:url]?id=[node:nid]\\r\\n\\r\\nSincerely,\\r\\n\\r\\nThe Lacuna Stories Team",
            "language" : [ "" ]
          }
        }
      ]
    }
  }');
  return $items;
}
