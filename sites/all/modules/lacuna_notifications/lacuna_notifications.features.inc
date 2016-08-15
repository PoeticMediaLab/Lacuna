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
