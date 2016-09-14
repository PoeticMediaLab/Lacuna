<?php
/**
 * @file
 * lacuna_notifications_configuration.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function lacuna_notifications_configuration_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "context" && $api == "context") {
    return array("version" => "3");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function lacuna_notifications_configuration_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_flag_default_flags().
 */
function lacuna_notifications_configuration_flag_default_flags() {
  $flags = array();
  // Exported flag: "User Notifications Flag".
  $flags['user_notifications_flag'] = array(
    'entity_type' => 'user',
    'title' => 'User Notifications Flag',
    'global' => 1,
    'types' => array(),
    'flag_short' => 'Flag this item',
    'flag_long' => '',
    'flag_message' => '',
    'unflag_short' => 'Unflag this item',
    'unflag_long' => '',
    'unflag_message' => '',
    'unflag_denied_text' => '',
    'link_type' => 'toggle',
    'weight' => 0,
    'show_in_links' => array(
      'full' => 0,
      'token' => 0,
    ),
    'show_as_field' => 0,
    'show_on_form' => 0,
    'access_author' => '',
    'show_contextual_link' => 0,
    'show_on_profile' => 0,
    'access_uid' => '',
    'module' => 'lacuna_notifications_configuration',
    'locked' => array(
      0 => 'name',
    ),
    'api_version' => 3,
  );
  return $flags;

}

/**
 * Implements hook_default_message_type().
 */
function lacuna_notifications_configuration_default_message_type() {
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
          "safe_value" : "\\u003Ctable class=\\u0022token-tree token-click-insert sticky-enabled tableheader-processed sticky-table token-tree-processed treeTable\\u0022\\u003E\\u003Ctbody\\u003E\\u003Ctr class=\\u0022child-of-token-message even initialized parent collapsed\\u0022 id=\\u0022token-message--field-message-comment\\u0022 style=\\u0022\\u0022\\u003E\\u003Ctd style=\\u0022padding-left: 29px;\\u0022\\u003E\\u00a0\\u003C\\/td\\u003E\\n\\u003Ctd class=\\u0022token-key token-click-insert-processed\\u0022\\u003E[message:field-message-comment] was added by\\u003Cbr \\/\\u003E\\u003Ctable class=\\u0022token-tree token-click-insert sticky-enabled tableheader-processed sticky-table token-tree-processed treeTable\\u0022\\u003E\\u003Ctbody\\u003E\\u003Ctr class=\\u0022child-of-token-message--field-message-comment odd initialized parent collapsed\\u0022 id=\\u0022token-message--field-message-comment--author\\u0022 style=\\u0022\\u0022\\u003E\\u003Ctd style=\\u0022padding-left: 48px;\\u0022\\u003E\\u00a0\\u003C\\/td\\u003E\\n\\u003Ctd class=\\u0022token-key token-click-insert-processed\\u0022\\u003E[message:field-message-comment:author]\\u003C\\/td\\u003E\\n\\u003C\\/tr\\u003E\\u003C\\/tbody\\u003E\\u003C\\/table\\u003E\\u003C\\/td\\u003E\\n\\u003C\\/tr\\u003E\\u003C\\/tbody\\u003E\\u003C\\/table\\u003E"
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
          "safe_value" : "\\u003Ctable class=\\u0022token-tree token-click-insert sticky-enabled tableheader-processed sticky-table token-tree-processed treeTable\\u0022 height=\\u002248\\u0022 width=\\u0022505\\u0022\\u003E\\u003Ctbody\\u003E\\u003Ctr class=\\u0022child-of-token-message--field-message-content odd initialized parent collapsed\\u0022 id=\\u0022token-message--field-message-content--author\\u0022 style=\\u0022\\u0022\\u003E\\u003Ctd style=\\u0022padding-left: 48px;\\u0022\\u003E\\u00a0\\u003C\\/td\\u003E\\n\\u003Ctd class=\\u0022token-key token-click-insert-processed\\u0022\\u003E[message:field-message-content:author]\\u003C\\/td\\u003E\\n\\u003C\\/tr\\u003E\\u003C\\/tbody\\u003E\\u003C\\/table\\u003E\\u003Cp\\u003E[message:field-message-content]\\u003C\\/p\\u003E\\n"
        }
      ]
    },
    "rdf_mapping" : []
  }');
  return $items;
}
