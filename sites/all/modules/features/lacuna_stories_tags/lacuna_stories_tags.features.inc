<?php
/**
 * @file
 * lacuna_stories_tags.features.inc
 */

/**
 * Implements hook_flag_default_flags().
 */
function lacuna_stories_tags_flag_default_flags() {
  $flags = array();
  // Exported flag: "Curated Tags".
  $flags['curated_tag'] = array(
    'entity_type' => 'taxonomy_term',
    'title' => 'Curated Tags',
    'global' => 1,
    'types' => array(
      0 => 'annotation_tags',
    ),
    'flag_short' => 'Add to "Curated Tags" list',
    'flag_long' => '',
    'flag_message' => '',
    'unflag_short' => 'Remove from "Curated Tags" list',
    'unflag_long' => '',
    'unflag_message' => '',
    'unflag_denied_text' => '',
    'link_type' => 'toggle',
    'weight' => 0,
    'show_in_links' => array(
      'full' => 'full',
      'diff_standard' => 0,
      'token' => 0,
    ),
    'show_as_field' => 0,
    'show_on_form' => 0,
    'access_author' => '',
    'show_contextual_link' => 0,
    'module' => 'lacuna_stories_tags',
    'locked' => array(
      0 => 'name',
    ),
    'api_version' => 3,
  );
  return $flags;

}
