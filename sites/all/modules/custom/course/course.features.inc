<?php
/**
 * @file
 * course.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function course_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "context" && $api == "context") {
    return array("version" => "3");
  }
  if ($module == "ds" && $api == "ds") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function course_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_image_default_styles().
 */
function course_image_default_styles() {
  $styles = array();

  // Exported image style: course_views_style.
  $styles['course_views_style'] = array(
    'label' => 'Course Views Style',
    'effects' => array(
      3 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 450,
          'height' => 275,
        ),
        'weight' => -10,
      ),
      2 => array(
        'name' => 'image_crop',
        'data' => array(
          'width' => 275,
          'height' => 150,
          'anchor' => 'center-bottom',
        ),
        'weight' => -9,
      ),
    ),
  );

  return $styles;
}

/**
 * Implements hook_node_info().
 */
function course_node_info() {
  $items = array(
    'course' => array(
      'name' => t('Course'),
      'base' => 'node_content',
      'description' => t('A specific course, used to give a group of enrolled students access to materials.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
