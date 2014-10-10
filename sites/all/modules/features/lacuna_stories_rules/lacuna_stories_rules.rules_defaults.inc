<?php
/**
 * @file
 * lacuna_stories_rules.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function lacuna_stories_rules_default_rules_configuration() {
  $items = array();
  $items['rules_notice_about_draft_status'] = entity_import('rules_config', '{ "rules_notice_about_draft_status" : {
      "LABEL" : "Notice about Draft Status",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules" ],
      "ON" : { "node_insert" : [] },
      "IF" : [
        { "node_is_of_type" : {
            "node" : [ "node" ],
            "type" : { "value" : {
                "audio" : "audio",
                "document" : "document",
                "image" : "image",
                "music_video" : "music_video",
                "video" : "video"
              }
            }
          }
        }
      ],
      "DO" : [
        { "drupal_message" : {
            "message" : "This content is currently saved as a Draft, so that you can make sure the formatting, images, font, and links are all polished and ready to go. Once you are sure the content is finalized and ready, click the \\u0022Workflow\\u0022 tab to change the status to \\u0022Ready for Annotation\\u0022. Once changed, this content can no longer be edited, as edits will \\u003Cb\\u003Eerase\\u003C\\/b\\u003E any existing annotations.\\r\\n",
            "type" : "warning"
          }
        }
      ]
    }
  }');
  return $items;
}
