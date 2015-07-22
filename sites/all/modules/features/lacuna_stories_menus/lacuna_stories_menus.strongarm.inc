<?php
/**
 * @file
 * lacuna_stories_menus.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function lacuna_stories_menus_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'superfish_smallbp_1';
  $strongarm->value = '960';
  $export['superfish_smallbp_1'] = $strongarm;

  return $export;
}
