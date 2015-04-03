<?php
/**
 * @file
 * lacuna_stories_content_types.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function lacuna_stories_content_types_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "context" && $api == "context") {
    return array("version" => "3");
  }
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_image_default_styles().
 */
function lacuna_stories_content_types_image_default_styles() {
  $styles = array();

  // Exported image style: thumbnails_for_browsing.
  $styles['thumbnails_for_browsing'] = array(
    'label' => 'Thumbnails for Browsing',
    'effects' => array(
      1 => array(
        'name' => 'image_resize',
        'data' => array(
          'width' => 220,
          'height' => 320,
        ),
        'weight' => 1,
      ),
    ),
  );

  return $styles;
}

/**
 * Implements hook_node_info().
 */
function lacuna_stories_content_types_node_info() {
  $items = array(
    'annotation' => array(
      'name' => t('Annotation'),
      'base' => 'node_content',
      'description' => t('An annotation of a piece of content.'),
      'has_title' => '0',
      'title_label' => '',
      'help' => '',
    ),
    'course' => array(
      'name' => t('Course'),
      'base' => 'node_content',
      'description' => t('A specific course, used to give a group of enrolled students access to materials.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'document' => array(
      'name' => t('Document'),
      'base' => 'node_content',
      'description' => t('Any primary or secondary documents.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'thread' => array(
      'name' => t('Thread'),
      'base' => 'node_content',
      'description' => t('Stitch annotations together into a thread.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
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
