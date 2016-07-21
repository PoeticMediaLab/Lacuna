<?php
/**
 * @file
 * lacuna_notifications.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function lacuna_notifications_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_default_message_type().
 */
function lacuna_notifications_default_message_type() {
  $items = array();
  $items['log_new_content'] = entity_import('message_type', '{
    "name" : "log_new_content",
    "description" : "Log New Content",
    "argument_keys" : [],
    "argument" : [],
    "category" : "message_type",
    "data" : {
      "token options" : { "clear" : 0 },
      "purge" : { "override" : 0, "enabled" : 0, "quota" : "", "days" : "" }
    },
    "language" : "",
    "arguments" : null,
    "message_text" : { "und" : [
        {
          "value" : "\\u003Cp\\u003E{message:field-message-content:title] has been added by [message:user:name]\\u003C\\/p\\u003E",
          "format" : "filtered_html",
          "safe_value" : "\\u003Cp\\u003E{message:field-message-content:title] has been added by [message:user:name]\\u003C\\/p\\u003E\\n"
        }
      ]
    },
    "rdf_mapping" : []
  }');
  return $items;
}
