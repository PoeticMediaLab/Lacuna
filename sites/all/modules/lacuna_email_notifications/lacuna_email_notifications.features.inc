<?php
/**
 * @file
 * lacuna_email_notifications.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function lacuna_email_notifications_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}
