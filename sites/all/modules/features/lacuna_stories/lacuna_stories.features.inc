<?php
/**
 * @file
 * lacuna_stories.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function lacuna_stories_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "context" && $api == "context") {
    return array("version" => "3");
  }
  if ($module == "file_entity" && $api == "file_default_displays") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function lacuna_stories_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_flag_default_flags().
 */
function lacuna_stories_flag_default_flags() {
  $flags = array();
  // Exported flag: "Filled out IRB form".
  $flags['filled_out_irb_form'] = array(
    'entity_type' => 'user',
    'title' => 'Filled out IRB form',
    'global' => 1,
    'types' => array(),
    'flag_short' => 'Filled out IRB form',
    'flag_long' => '',
    'flag_message' => '',
    'unflag_short' => 'Did not fill out IRB form',
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
    'module' => 'lacuna_stories',
    'locked' => array(
      0 => 'name',
    ),
  );
  return $flags;

}

/**
 * Implements hook_image_default_styles().
 */
function lacuna_stories_image_default_styles() {
  $styles = array();

  // Exported image style: medium__220x320__no_scaling.
  $styles['medium__220x320__no_scaling'] = array(
    'name' => 'medium__220x320__no_scaling',
    'label' => 'Medium (220x320) no resize',
    'effects' => array(
      4 => array(
        'label' => 'Scale',
        'help' => 'Scaling will maintain the aspect-ratio of the original image. If only a single dimension is specified, the other dimension will be calculated.',
        'effect callback' => 'image_scale_effect',
        'dimensions callback' => 'image_scale_dimensions',
        'form callback' => 'image_scale_form',
        'summary theme' => 'image_scale_summary',
        'module' => 'image',
        'name' => 'image_scale',
        'data' => array(
          'width' => 220,
          'height' => 320,
          'upscale' => 1,
        ),
        'weight' => 2,
      ),
    ),
  );

  // Exported image style: thumbnails_for_browsing.
  $styles['thumbnails_for_browsing'] = array(
    'name' => 'thumbnails_for_browsing',
    'label' => 'Thumbnails for Browsing',
    'effects' => array(
      1 => array(
        'label' => 'Scale',
        'help' => 'Scaling will maintain the aspect-ratio of the original image. If only a single dimension is specified, the other dimension will be calculated.',
        'effect callback' => 'image_scale_effect',
        'dimensions callback' => 'image_scale_dimensions',
        'form callback' => 'image_scale_form',
        'summary theme' => 'image_scale_summary',
        'module' => 'image',
        'name' => 'image_scale',
        'data' => array(
          'width' => 220,
          'height' => 320,
          'upscale' => 1,
        ),
        'weight' => 1,
      ),
      2 => array(
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
        'weight' => 2,
      ),
    ),
  );

  return $styles;
}

/**
 * Implements hook_node_info().
 */
function lacuna_stories_node_info() {
  $items = array(
    'audio' => array(
      'name' => t('Audio'),
      'base' => 'node_content',
      'description' => t('For audio files of any type.'),
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
    'group' => array(
      'name' => t('Group'),
      'base' => 'node_content',
      'description' => t('A group to determine levels of access to content'),
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
    'video' => array(
      'name' => t('Video'),
      'base' => 'node_content',
      'description' => t('Any videos.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}

/**
 * Implements hook_popupformat_defaults().
 */
function lacuna_stories_popupformat_defaults() {
  return array(
    'Default click' => array(
      'label' => 'Default click',
      'origin' => 'bottom-left',
      'expand' => 'bottom-right',
      'effect' => 'default',
      'style' => 0,
      'opacity' => '1.0',
      'width' => 150,
      'activate' => 'click',
      'close' => 1,
      'ajax' => 0,
      'teaser' => 0,
      'inline' => 0,
      'flat' => 0,
      'submenu-origin' => 'top-right',
      'submenu-expand' => 'bottom-right',
    ),
    'Default hover' => array(
      'label' => 'Default hover',
      'origin' => 'bottom-right',
      'expand' => 'bottom-right',
      'effect' => 'default',
      'style' => 0,
      'opacity' => '1.0',
      'width' => 150,
      'activate' => 'hover',
      'close' => 1,
      'ajax' => 1,
      'teaser' => 0,
      'inline' => 0,
      'flat' => 0,
      'submenu-origin' => 'top-right',
      'submenu-expand' => 'bottom-right',
    ),
    'Default node' => array(
      'label' => 'Default node',
      'origin' => 'bottom-left',
      'expand' => 'bottom-right',
      'effect' => 'default',
      'style' => 0,
      'opacity' => '1.0',
      'width' => 150,
      'activate' => 'hover',
      'close' => 0,
      'ajax' => 0,
      'teaser' => 1,
      'inline' => 0,
      'flat' => 0,
      'submenu-origin' => 'top-right',
      'submenu-expand' => 'bottom-right',
    ),
    'Flat popup menu' => array(
      'label' => 'Flat popup menu',
      'origin' => 'top-right',
      'expand' => 'bottom-right',
      'effect' => 'default',
      'style' => 0,
      'opacity' => '1.0',
      'width' => 200,
      'activate' => 'hover',
      'close' => 0,
      'ajax' => 0,
      'teaser' => 0,
      'inline' => 0,
      'flat' => 1,
      'submenu-origin' => 'top-right',
      'submenu-expand' => 'bottom-right',
    ),
    'Left block' => array(
      'label' => 'Left block',
      'origin' => 'top-right',
      'expand' => 'bottom-right',
      'effect' => 'default',
      'style' => 0,
      'opacity' => '1.0',
      'width' => 150,
      'activate' => 'hover',
      'close' => 0,
      'ajax' => 0,
      'teaser' => 0,
      'inline' => 0,
      'flat' => 0,
      'submenu-origin' => 'top-right',
      'submenu-expand' => 'bottom-right',
    ),
    'Popup menu' => array(
      'label' => 'Popup menu',
      'origin' => 'top-right',
      'expand' => 'bottom-right',
      'effect' => 'default',
      'style' => 0,
      'opacity' => '1.0',
      'width' => 200,
      'activate' => 'hover',
      'close' => 0,
      'ajax' => 0,
      'teaser' => 0,
      'inline' => 0,
      'flat' => 0,
      'submenu-origin' => 'top-right',
      'submenu-expand' => 'bottom-right',
    ),
    'Right block' => array(
      'label' => 'Right block',
      'origin' => 'top-left',
      'expand' => 'bottom-left',
      'effect' => 'default',
      'style' => 0,
      'opacity' => '1.0',
      'width' => 150,
      'activate' => 'hover',
      'close' => 0,
      'ajax' => 0,
      'teaser' => 0,
      'inline' => 0,
      'flat' => 0,
      'submenu-origin' => 'top-right',
      'submenu-expand' => 'bottom-right',
    ),
  );
}
