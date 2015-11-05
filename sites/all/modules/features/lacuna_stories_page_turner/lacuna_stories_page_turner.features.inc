<?php
/**
 * @file
 * lacuna_stories_page_turner.features.inc
 */

/**
 * Implements hook_flag_default_flags().
 */
function lacuna_stories_page_turner_flag_default_flags() {
  $flags = array();
  // Exported flag: "Page Turner Bookmark".
  $flags['page_turner_bookmark'] = array(
    'entity_type' => 'node',
    'title' => 'Page Turner Bookmark',
    'global' => 0,
    'types' => array(),
    'flag_short' => 'Bookmark',
    'flag_long' => '',
    'flag_message' => '',
    'unflag_short' => 'Unbookmark',
    'unflag_long' => '',
    'unflag_message' => '',
    'unflag_denied_text' => '',
    'link_type' => 'toggle',
    'weight' => 0,
    'show_in_links' => array(),
    'show_as_field' => FALSE,
    'show_on_form' => FALSE,
    'access_author' => '',
    'show_contextual_link' => FALSE,
    'i18n' => 0,
    'module' => 'lacuna_stories_page_turner',
    'locked' => array(
      0 => 'name',
    ),
    'api_version' => 3,
  );
  return $flags;

}
