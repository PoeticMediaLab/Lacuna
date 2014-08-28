<?php
/**
 * @file
 * lacuna_stories.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function lacuna_stories_default_rules_configuration() {
  $items = array();
  $items['rules_flag_user_after_irb_consent_form_completed'] = entity_import('rules_config', '{ "rules_flag_user_after_irb_consent_form_completed" : {
      "LABEL" : "Flag User After IRB Consent Form Completed",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules", "webform_rules", "flag" ],
      "ON" : { "webform_rules_submit" : [] },
      "IF" : [
        { "webform_has_id" : {
            "form_id" : "[form-id:value]",
            "selected_webform" : { "value" : { "webform-client-form-52" : "webform-client-form-52" } }
          }
        }
      ],
      "DO" : [
        { "flag_flaguser" : {
            "flag" : "filled_out_irb_form",
            "user" : [ "site:current-user" ],
            "flagging_user" : [ "site:current-user" ],
            "permission_check" : 1
          }
        },
        { "redirect" : { "url" : "\\u003Cfront\\u003E" } }
      ]
    }
  }');
  $items['rules_redirect_document_content_to_bibliographic_entries'] = entity_import('rules_config', '{ "rules_redirect_document_content_to_bibliographic_entries" : {
      "LABEL" : "Redirect Document content to Bibliographic Entries",
      "PLUGIN" : "reaction rule",
      "ACTIVE" : false,
      "OWNER" : "rules",
      "REQUIRES" : [ "rules" ],
      "ON" : { "node_view--document" : { "bundle" : "document" } },
      "DO" : [ { "redirect" : { "url" : [ "node:field-bibliographic-entry:url" ] } } ]
    }
  }');
  $items['rules_require_irb_form_completion'] = entity_import('rules_config', '{ "rules_require_irb_form_completion" : {
      "LABEL" : "Require IRB Form Completion",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "flag", "rules" ],
      "ON" : { "user_login" : [] },
      "IF" : [
        { "NOT flag_flagged_user" : {
            "flag" : "filled_out_irb_form",
            "user" : [ "account" ],
            "flagging_user" : [ "account" ]
          }
        }
      ],
      "DO" : [ { "redirect" : { "url" : "content\\/digital-research-consent-form" } } ]
    }
  }');
  return $items;
}
