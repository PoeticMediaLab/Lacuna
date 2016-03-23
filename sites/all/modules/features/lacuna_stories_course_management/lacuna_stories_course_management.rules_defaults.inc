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
            "subject" : "Your enrollment request was approved for \\u0027[group:title]\\u0027\\r\\n",
            "message" : "Dear [account:name],\\r\\n\\r\\nYou are now enrolled in \\u0022[group:title]\\u0022 located at [group:url]\\r\\n\\r\\nSincerely,\\r\\n\\r\\nThe Lacuna Team",
            "language" : [ "" ]
          }
        }
      ]
    }
  }');
  $items['og_notification_of_pending_enrollment'] = entity_import('rules_config', '{ "og_notification_of_pending_enrollment" : {
      "LABEL" : "Notification of Pending Enrollment",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules", "course_registration", "og" ],
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
        { "og_get_members_from_group" : {
            "USING" : {
              "group" : [ "group" ],
              "states" : { "value" : [] },
              "roles" : { "value" : { "administrator member" : "administrator member" } }
            },
            "PROVIDE" : { "group_members" : { "group_admins" : "List of group admins" } }
          }
        },
        { "LOOP" : {
            "USING" : { "list" : [ "group-admins" ] },
            "ITEM" : { "group_admin" : "Current group admin" },
            "DO" : [
              { "mail" : {
                  "to" : [ "group-admin:mail" ],
                  "subject" : "[account:name] requests enrollment in \\u0022[group:title]\\u0022",
                  "message" : "Dear [group-admin:name],\\r\\n\\r\\n[account:name] has requested enrollment in your course \\u0022[group:title]\\u0022 ([group:url]). To approve this request, please visit the \\u0022Manage Students\\u0022 page on Lacuna at: [site:url]\\/manage-students\\r\\n\\r\\nSincerely,\\r\\n\\r\\nThe Lacuna Team",
                  "language" : [ "" ]
                }
              }
            ]
          }
        }
      ]
    }
  }');
  return $items;
}
