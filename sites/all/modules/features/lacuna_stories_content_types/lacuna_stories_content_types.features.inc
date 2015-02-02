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
    'name' => 'thumbnails_for_browsing',
    'label' => 'Thumbnails for Browsing',
    'effects' => array(
      1 => array(
        'label' => 'Resize',
        'help' => 'Resizing will make images an exact set of dimensions. This may cause images to be stretched or shrunk disproportionately.',
        'effect callback' => 'image_resize_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
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
    'audio' => array(
      'name' => t('Audio'),
      'base' => 'node_content',
      'description' => t('For audio files of any type.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'course_or_other_group' => array(
      'name' => t('Course or Other Group'),
      'base' => 'node_content',
      'description' => t('Any group of students, typically used to organized content by course'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'document' => array(
      'name' => t('Document'),
      'base' => 'node_content',
      'description' => t('Any primary or secondary text documents.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'image' => array(
      'name' => t('Image'),
      'base' => 'node_content',
      'description' => t('For any static images.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'music_video' => array(
      'name' => t('Music Video'),
      'base' => 'node_content',
      'description' => t('For music videos. Rock on.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'page' => array(
      'name' => t('Basic page'),
      'base' => 'node_content',
      'description' => t('Use <em>basic pages</em> for your static content, such as an \'About us\' page.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'thread' => array(
      'name' => t('Thread'),
      'base' => 'node_content',
      'description' => t('This content type stitches together items in a Sewing Kit.'),
      'has_title' => '1',
      'title_label' => t('Title of My Thread'),
      'help' => '',
    ),
    'video' => array(
      'name' => t('Video'),
      'base' => 'node_content',
      'description' => t('Any videos.'),
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
