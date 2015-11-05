<?php
/**
 * @file
 * lacuna_stories_irb_form.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function lacuna_stories_irb_form_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

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
    'module' => 'lacuna_stories_irb_form',
    'locked' => array(
      0 => 'name',
    ),
    'api_version' => 3,
  );
  return $flags;

}

/**
 * Implements hook_node_info().
 */
function lacuna_stories_irb_form_node_info() {
  $items = array(
    'webform' => array(
      'name' => t('Webform'),
      'base' => 'node_content',
      'description' => t('Create a new form or questionnaire accessible to users. Submission results and statistics are recorded and accessible to privileged users.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
