<?php
/**
 * @file
 * lacuna_site_administrator.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function lacuna_site_administrator_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'admin_theme';
  $strongarm->value = 'seven';
  $export['admin_theme'] = $strongarm;

  return $export;
}
