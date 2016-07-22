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
  $items['log_new_comment'] = entity_import('message_type', '{
    "name" : "log_new_comment",
    "description" : "Log New Comment",
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
          "value" : "\\u003Ctable\\u003E\\u003Ctbody\\u003E\\u003Ctr id=\\u0022token-message--field-message-comment--author--name\\u0022\\u003E\\u003Ctd\\u003E\\u003Ca href=\\u0022javascript:void(0);\\u0022 title=\\u0022Insert this token into your form\\u0022\\u003E[message:field-message-comment:author:name]\\u003C\\/a\\u003E\\u0026nbsp;made a comment on\\u0026nbsp;\\u003C\\/td\\u003E\\u003C\\/tr\\u003E\\u003C\\/tbody\\u003E\\u003C\\/table\\u003E\\u003Ctable\\u003E\\u003Ctbody\\u003E\\u003Ctr id=\\u0022token-message--field-message-comment--node--title\\u0022\\u003E\\u003Ctd\\u003E\\u003Ca href=\\u0022javascript:void(0);\\u0022 title=\\u0022Insert this token into your form\\u0022\\u003E[message:field-message-comment:node:title]\\u003C\\/a\\u003E\\u003C\\/td\\u003E\\u003C\\/tr\\u003E\\u003C\\/tbody\\u003E\\u003C\\/table\\u003E",
          "format" : "filtered_html",
          "safe_value" : "\\u003Cp\\u003E\\u003Ca href=\\u0022void(0);\\u0022 title=\\u0022Insert this token into your form\\u0022\\u003E[message:field-message-comment:author:name]\\u003C\\/a\\u003E\\u00a0made a comment on\\u00a0\\n\\u003Ca href=\\u0022void(0);\\u0022 title=\\u0022Insert this token into your form\\u0022\\u003E[message:field-message-comment:node:title]\\u003C\\/a\\u003E\\n\\u003C\\/p\\u003E"
        }
      ]
    },
    "rdf_mapping" : []
  }');
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
