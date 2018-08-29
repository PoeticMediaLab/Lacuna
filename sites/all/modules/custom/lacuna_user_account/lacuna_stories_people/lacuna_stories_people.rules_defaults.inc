<?php
/**
 * @file
 * lacuna_stories_people.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function lacuna_stories_people_default_rules_configuration() {
  $items = array();
  $items['rules_browser_warning'] = entity_import('rules_config', '{ "rules_browser_warning" : {
      "LABEL" : "Browser Warning",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "php", "rules" ],
      "ON" : { "user_login" : [] },
      "IF" : [
        { "php_eval" : { "code" : "if(strpos($_SERVER[\\u0027HTTP_USER_AGENT\\u0027], \\u0027MSIE\\u0027) !== FALSE)\\r\\n   return true;\\r\\n elseif(strpos($_SERVER[\\u0027HTTP_USER_AGENT\\u0027], \\u0027Trident\\u0027) !== FALSE) \\/\\/For Supporting IE 11\\r\\n    return true;\\r\\n else\\r\\n   return false;" } }
      ],
      "DO" : [
        { "drupal_message" : {
            "message" : "Lacuna does not support annotation on Internet Explorer. Please switch to Firefox, Safari, or Chrome if you wish to annotate.",
            "type" : "warning"
          }
        }
      ]
    }
  }');
  return $items;
}
