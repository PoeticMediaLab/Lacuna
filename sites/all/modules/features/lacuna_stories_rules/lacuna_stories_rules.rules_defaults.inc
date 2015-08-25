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
  $items['lacuna_stories_rules_irb_form_complete_complete_profile'] = entity_import('rules_config', '{ "lacuna_stories_rules_irb_form_complete_complete_profile" : {
      "LABEL" : "After IRB Form Completed, Ask User to Complete Profile",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "webform_rules", "rules" ],
      "ON" : { "webform_rules_submit" : [] },
      "IF" : [
        { "webform_has_id" : {
            "form_id" : [ "form_id" ],
            "selected_webform" : { "value" : { "webform-client-form-1" : "webform-client-form-1" } }
          }
        }
      ],
      "DO" : [
        { "redirect" : { "url" : "[user:edit-url]" } },
        { "drupal_message" : { "message" : "Welcome to Lacuna Stories. Please tell us about yourself by completing your profile." } }
      ]
    }
  }');
  $items['rules_notice_about_annotations_on_responses'] = entity_import('rules_config', '{ "rules_notice_about_annotations_on_responses" : {
      "LABEL" : "Notice about Annotations on Responses",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules" ],
      "ON" : { "node_insert--response" : { "bundle" : "response" } },
      "DO" : [
        { "drupal_message" : {
            "message" : "Your response has been saved. Please note: if you make changes to your response, any annotations already made on this piece may disappear or be in the wrong location. To avoid this issue, you can set your response to \\u0022Unpublished\\u0022 until you are ready to share it with others. To do so, visit the \\u003Ca href=\\u0022\\/my-writing\\u0022\\u003EMy Writing\\u003C\\/a\\u003E page.",
            "type" : "warning"
          }
        }
      ]
    }
  }');
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
