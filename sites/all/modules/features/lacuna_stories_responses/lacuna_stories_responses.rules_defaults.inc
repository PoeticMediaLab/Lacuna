<?php
/**
 * @file
 * lacuna_stories_responses.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function lacuna_stories_responses_default_rules_configuration() {
  $items = array();
  $items['rules_notice_about_annotations_on_responses'] = entity_import('rules_config', '{ "rules_notice_about_annotations_on_responses" : {
      "LABEL" : "Notice about Annotations on Responses",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules" ],
      "ON" : { "node_insert--response" : { "bundle" : "response" } },
      "DO" : [
        { "drupal_message" : {
            "message" : "Your response has been saved. Please note: if you make changes to your response, any annotations already made on this piece may disappear or be in the wrong location. To avoid this issue, you can set your response to \\u0022Unpublished\\u0022 until you are ready to share it with others. To do so, visit the \\u003Ca href=\\u0022[site:url]my-writing\\u0022\\u003EMy Writing\\u003C\\/a\\u003E page.",
            "type" : "warning"
          }
        }
      ]
    }
  }');
  return $items;
}
