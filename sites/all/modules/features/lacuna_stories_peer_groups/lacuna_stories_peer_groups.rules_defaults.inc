<?php
/**
 * @file
 * lacuna_stories_peer_groups.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function lacuna_stories_peer_groups_default_rules_configuration() {
  $items = array();
  $items['rules_add_user_to_peer_group_on_button_click'] = entity_import('rules_config', '{ "rules_add_user_to_peer_group_on_button_click" : {
      "LABEL" : "Add User to Peer Group on Button Click",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules", "button_field", "og" ],
      "ON" : { "button_field_clicked" : [] },
      "IF" : [
        { "entity_is_of_bundle" : {
            "entity" : [ "entity" ],
            "type" : "node",
            "bundle" : { "value" : { "peer_group" : "peer_group" } }
          }
        },
        { "button_field_compare_button" : {
            "clicked_field" : [ "field" ],
            "comparison_field_name" : "field_join_group"
          }
        }
      ],
      "DO" : [
        { "og_subcribe_user" : { "user" : [ "site:current-user" ], "group" : [ "entity" ] } },
        { "redirect" : { "url" : "peer-groups" } },
        { "drupal_message" : { "message" : "You have been added to this peer group." } }
      ]
    }
  }');
  $items['rules_remove_user_from_peer_group_on_button_click'] = entity_import('rules_config', '{ "rules_remove_user_from_peer_group_on_button_click" : {
      "LABEL" : "Remove User From Peer Group on Button Click",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules", "button_field", "og" ],
      "ON" : { "button_field_clicked" : [] },
      "IF" : [
        { "entity_has_field" : { "entity" : [ "entity" ], "field" : "field_leave_group" } },
        { "button_field_compare_button" : {
            "clicked_field" : [ "field" ],
            "comparison_field_name" : "field_leave_group"
          }
        },
        { "entity_is_of_bundle" : {
            "entity" : [ "entity" ],
            "type" : "node",
            "bundle" : { "value" : { "peer_group" : "peer_group" } }
          }
        }
      ],
      "DO" : [
        { "og_unsubscribe_user" : { "user" : [ "site:current-user" ], "group" : [ "entity" ] } },
        { "redirect" : { "url" : "peer-groups" } },
        { "drupal_message" : { "message" : "You have been removed from this peer group." } }
      ]
    }
  }');
  return $items;
}
