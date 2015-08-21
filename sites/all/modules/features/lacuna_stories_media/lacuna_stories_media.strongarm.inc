<?php
/**
 * @file
 * lacuna_stories_media.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function lacuna_stories_media_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'mediaelement_sitewide';
  $strongarm->value = 1;
  $export['mediaelement_sitewide'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'media_icon_base_directory';
  $strongarm->value = 'public://media-icons';
  $export['media_icon_base_directory'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'media_wysiwyg_default_render';
  $strongarm->value = 'field_attach';
  $export['media_wysiwyg_default_render'] = $strongarm;

  return $export;
}
