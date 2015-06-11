<?php
/**
 * @file
 * lacuna_stories_peer_groups.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function lacuna_stories_peer_groups_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_anonymous_peer_group';
  $strongarm->value = 0;
  $export['comment_anonymous_peer_group'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_mode_peer_group';
  $strongarm->value = 1;
  $export['comment_default_mode_peer_group'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_per_page_peer_group';
  $strongarm->value = '50';
  $export['comment_default_per_page_peer_group'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_form_location_peer_group';
  $strongarm->value = 1;
  $export['comment_form_location_peer_group'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_peer_group';
  $strongarm->value = '2';
  $export['comment_peer_group'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_preview_peer_group';
  $strongarm->value = '1';
  $export['comment_preview_peer_group'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_subject_field_peer_group';
  $strongarm->value = 1;
  $export['comment_subject_field_peer_group'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_options_peer_group';
  $strongarm->value = array(
    0 => 'main-menu',
  );
  $export['menu_options_peer_group'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_parent_peer_group';
  $strongarm->value = 'main-menu:0';
  $export['menu_parent_peer_group'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_peer_group';
  $strongarm->value = array(
    0 => 'status',
    1 => 'promote',
  );
  $export['node_options_peer_group'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_preview_peer_group';
  $strongarm->value = '1';
  $export['node_preview_peer_group'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_submitted_peer_group';
  $strongarm->value = 1;
  $export['node_submitted_peer_group'] = $strongarm;

  return $export;
}
