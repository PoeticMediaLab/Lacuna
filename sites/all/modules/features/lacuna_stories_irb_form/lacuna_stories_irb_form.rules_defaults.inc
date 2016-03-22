<?php
/**
 * @file
 * lacuna_stories_irb_form.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function lacuna_stories_irb_form_default_rules_configuration() {
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
  $items['rules_flag_user_after_irb_consent_form_completed'] = entity_import('rules_config', '{ "rules_flag_user_after_irb_consent_form_completed" : {
      "LABEL" : "Flag User After IRB Consent Form Completed",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "webform_rules", "flag" ],
      "ON" : { "webform_rules_submit" : [] },
      "IF" : [
        { "webform_has_id" : {
            "form_id" : [ "form_id" ],
            "selected_webform" : { "value" : { "webform-client-form-1" : "webform-client-form-1" } }
          }
        }
      ],
      "DO" : [
        { "flag_flaguser" : {
            "flag" : "irb_form_completed",
            "user" : [ "user" ],
            "flagging_user" : [ "user" ],
            "permission_check" : 1
          }
        }
      ]
    }
  }');
  $items['rules_require_irb_form_completion'] = entity_import('rules_config', '{ "rules_require_irb_form_completion" : {
      "LABEL" : "Require IRB Form Completion",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules", "flag" ],
      "ON" : { "user_login" : [] },
      "IF" : [
        { "NOT text_matches" : {
            "text" : [ "site:current-page:path" ],
            "match" : "^user\\/reset\\/",
            "operation" : "regex"
          }
        },
        { "NOT flag_flagged_user" : {
            "flag" : "irb_form_completed",
            "user" : [ "account" ],
            "flagging_user" : [ "account" ]
          }
        }
      ],
      "DO" : [ { "redirect" : { "url" : "webform\\/digital-research-consent-form" } } ]
    }
  }');
  return $items;
}
