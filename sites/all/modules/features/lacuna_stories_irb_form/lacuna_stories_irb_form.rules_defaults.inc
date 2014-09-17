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
  $items['rules_require_irb_form_completion'] = entity_import('rules_config', '{ "rules_require_irb_form_completion" : {
      "LABEL" : "Require IRB Form Completion",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "flag", "rules" ],
      "ON" : { "user_login" : [] },
      "IF" : [
        { "NOT flag_flagged_user" : {
            "flag" : "irb_form_completed",
            "user" : [ "account" ],
            "flagging_user" : [ "account" ]
          }
        },
        { "NOT text_matches" : {
            "text" : [ "site:current-page:path" ],
            "match" : "^user\\/reset\\/",
            "operation" : "regex"
          }
        }
      ],
      "DO" : [ { "redirect" : { "url" : "content\\/digital-research-consent-form" } } ]
    }
  }');
  return $items;
}
