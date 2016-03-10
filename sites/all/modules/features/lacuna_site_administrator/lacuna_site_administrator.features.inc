<?php
/**
 * @file
 * lacuna_site_administrator.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function lacuna_site_administrator_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}
