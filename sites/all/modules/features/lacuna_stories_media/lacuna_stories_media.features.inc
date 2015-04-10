<?php
/**
 * @file
 * lacuna_stories_media.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function lacuna_stories_media_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "file_entity" && $api == "file_default_displays") {
    return array("version" => "1");
  }
}
