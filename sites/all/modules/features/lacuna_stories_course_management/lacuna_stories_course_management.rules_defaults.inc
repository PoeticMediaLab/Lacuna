<?php
/**
 * @file
 * lacuna_stories_course_management.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function lacuna_stories_course_management_default_rules_configuration() {
  $items = array();
  $items['og_notification_of_approved_enrollment'] = entity_import('rules_config', '{ "og_notification_of_approved_enrollment" : {
      "LABEL" : "Notification of Approved Enrollment",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules", "og" ],
      "ON" : { "og_user_insert" : [] },
      "IF" : [
        { "data_is" : { "data" : [ "og-membership:state" ], "value" : "1" } },
        { "entity_is_of_type" : { "entity" : [ "og-membership:group" ], "type" : "node" } }
      ],
      "DO" : [
        { "variable_add" : {
            "USING" : { "type" : "node", "value" : [ "og-membership:group" ] },
            "PROVIDE" : { "variable_added" : { "group" : "Added variable" } }
          }
        },
        { "mail" : {
            "to" : [ "account:mail" ],
            "subject" : "Your membership request was approved for \\u0027[group:title]\\u0027\\r\\n",
            "message" : "[account:name],\\r\\n\\r\\nYou are now a member in the group \\u0027[group:title]\\u0027 located at [group:url]"
          }
        },
        { "mail" : {
            "to" : [ "group:author:mail" ],
            "subject" : "[account:name] joined [group:title]",
            "message" : "[group:author:name],\\r\\n\\r\\n[account:name] joined [group:title] in [group:url]"
          }
        }
      ]
    }
  }');
  $items['og_notification_of_pending_enrollment'] = entity_import('rules_config', '{ "og_notification_of_pending_enrollment" : {
      "LABEL" : "Notification of Pending Enrollment",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules", "og" ],
      "ON" : { "og_user_insert" : [] },
      "IF" : [
        { "data_is" : { "data" : [ "og-membership:state" ], "value" : "2" } },
        { "entity_is_of_type" : { "entity" : [ "og-membership:group" ], "type" : "node" } }
      ],
      "DO" : [
        { "variable_add" : {
            "USING" : { "type" : "node", "value" : [ "og-membership:group" ] },
            "PROVIDE" : { "variable_added" : { "group" : "Added variable" } }
          }
        },
        { "mail" : {
            "to" : [ "account:mail" ],
            "subject" : "Your enrollment request for \\u0027[group:title]\\u0027",
            "message" : "Dear [account:name],\\r\\n\\r\\nYour enrollment in the course \\u0027[group:title]\\u0027 located at [group:url] is pending approval by the instructor. You will receive an email when it has been approved.\\r\\n\\r\\n\\r\\n\\r\\nSincerely,\\r\\nThe Lacuna Team",
            "language" : [ "" ]
          }
        },
        { "mail" : {
            "to" : [ "group:author:mail" ],
            "subject" : "[account:name] enrollment request [group:title]",
            "message" : "Dear [group:author:name],\\r\\n\\r\\n[account:name] requests enrollment in your course \\u0027[group:title]\\u0027 in [group:url]. You can add students to your course by accessing \\u0022Manage Students\\u0022 under the \\u0022Manage\\u0022 menu.\\r\\n\\r\\n[og_membership:og-membership-request]\\r\\n\\r\\n\\r\\n\\r\\nSincerely,\\r\\nThe Lacuna Team",
            "language" : [ "" ]
          }
        }
      ]
    }
  }');
  return $items;
}
