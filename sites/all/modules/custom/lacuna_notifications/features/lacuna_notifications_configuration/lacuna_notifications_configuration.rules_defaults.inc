<?php
/**
 * @file
 * lacuna_notifications_configuration.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function lacuna_notifications_configuration_default_rules_configuration() {
  $items = array();
  $items['lacuna_notifications_log_new_annotation_reply_comment_'] = entity_import('rules_config', '{ "lacuna_notifications_log_new_annotation_reply_comment_" : {
      "LABEL" : "Log New Annotation Reply (Comment)",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules", "flag", "comment" ],
      "ON" : { "comment_insert--comment_node_annotation" : { "bundle" : "comment_node_annotation" } },
      "IF" : [
        { "NOT data_is" : { "data" : [ "comment:author" ], "value" : [ "comment:node:author" ] } }
      ],
      "DO" : [
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
        }
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
  $items['rules_unflag_users_after_page_view'] = entity_import('rules_config', '{ "rules_unflag_users_after_page_view" : {
      "LABEL" : "Unflag Users After Page View",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "pathrules", "flag", "rules" ],
      "ON" : { "init" : [] },
      "IF" : [ { "pathrules_checkpath" : { "path" : "latest-conversations" } } ],
      "DO" : [
        { "flag_unflaguser" : {
            "flag" : "user_notifications_flag",
            "user" : [ "site:current-user" ],
            "flagging_user" : [ "site:current-user" ],
            "permission_check" : "1"
          }
        }
      ]
    }
  }');
  return $items;
}
