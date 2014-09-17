<?php
/**
 * @file
 * lacuna_stories_irb_form.features.inc
 */

/**
 * Implements hook_flag_default_flags().
 */
function lacuna_stories_irb_form_flag_default_flags() {
  $flags = array();
  // Exported flag: "IRB Form Completed".
  $flags['irb_form_completed'] = array(
    'entity_type' => 'user',
    'title' => 'IRB Form Completed',
    'global' => 1,
    'types' => array(),
    'flag_short' => 'Flag this user',
    'flag_long' => '',
    'flag_message' => '',
    'unflag_short' => 'Unflag this user',
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
    'access_uid' => 'others',
    'api_version' => 3,
    'module' => 'lacuna_stories_irb_form',
    'locked' => array(
      0 => 'name',
    ),
  );
  return $flags;

}
