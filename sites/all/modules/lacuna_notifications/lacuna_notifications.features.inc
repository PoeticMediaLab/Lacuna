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
 * Implements hook_views_api().
 */
function lacuna_notifications_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
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
          "value" : "\\u003Ctable class=\\u0022token-tree token-click-insert sticky-enabled tableheader-processed sticky-table token-tree-processed treeTable\\u0022\\u003E\\u003Ctbody\\u003E\\u003Ctr class=\\u0022child-of-token-message even initialized parent collapsed\\u0022 id=\\u0022token-message--field-message-comment\\u0022 style=\\u0022\\u0022\\u003E\\u003Ctd style=\\u0022padding-left: 29px;\\u0022\\u003E\\u0026nbsp;\\u003C\\/td\\u003E\\u003Ctd class=\\u0022token-key token-click-insert-processed\\u0022\\u003E[message:field-message-comment] was added by\\u003Ctable class=\\u0022token-tree token-click-insert sticky-enabled tableheader-processed sticky-table token-tree-processed treeTable\\u0022\\u003E\\u003Ctbody\\u003E\\u003Ctr class=\\u0022child-of-token-message--field-message-comment odd initialized parent collapsed\\u0022 id=\\u0022token-message--field-message-comment--author\\u0022 style=\\u0022\\u0022\\u003E\\u003Ctd style=\\u0022padding-left: 48px;\\u0022\\u003E\\u0026nbsp;\\u003C\\/td\\u003E\\u003Ctd class=\\u0022token-key token-click-insert-processed\\u0022\\u003E[message:field-message-comment:author]\\u003C\\/td\\u003E\\u003C\\/tr\\u003E\\u003C\\/tbody\\u003E\\u003C\\/table\\u003E\\u003C\\/td\\u003E\\u003C\\/tr\\u003E\\u003C\\/tbody\\u003E\\u003C\\/table\\u003E",
          "format" : "filtered_html",
          "safe_value" : "\\u003Cp\\u003E\\u00a0\\n[message:field-message-comment] was added by\\u003Cbr \\/\\u003E\\u00a0\\n[message:field-message-comment:author]\\u003C\\/p\\u003E\\n\\n"
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
          "value" : "\\u003Ctable class=\\u0022token-tree token-click-insert sticky-enabled tableheader-processed sticky-table token-tree-processed treeTable\\u0022 height=\\u002248\\u0022 width=\\u0022505\\u0022\\u003E\\u003Ctbody\\u003E\\u003Ctr class=\\u0022child-of-token-message--field-message-content odd initialized parent collapsed\\u0022 id=\\u0022token-message--field-message-content--author\\u0022 style=\\u0022\\u0022\\u003E\\u003Ctd style=\\u0022padding-left: 48px;\\u0022\\u003E\\u0026nbsp;\\u003C\\/td\\u003E\\u003Ctd class=\\u0022token-key token-click-insert-processed\\u0022\\u003E[message:field-message-content:author]\\u003C\\/td\\u003E\\u003C\\/tr\\u003E\\u003C\\/tbody\\u003E\\u003C\\/table\\u003E\\u003Cp\\u003E[message:field-message-content]\\u003C\\/p\\u003E",
          "format" : "filtered_html",
          "safe_value" : "\\u003Cp\\u003E\\u00a0\\n[message:field-message-content:author]\\n\\u003C\\/p\\u003E\\n\\n\\u003Cp\\u003E[message:field-message-content]\\u003C\\/p\\u003E\\n"
        }
      ]
    },
    "rdf_mapping" : []
  }');
  return $items;
}
