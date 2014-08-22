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
 * Implements hook_fontyourface_features_default_font().
 */
function lacuna_stories_fontyourface_features_default_font() {
  return array(
    'Noto Sans 700 (latin-ext)' => array(
      'name' => 'Noto Sans 700 (latin-ext)',
      'enabled' => 1,
      'url' => 'http://www.google.com/webfonts/family?family=Noto Sans&subset=latin-ext#700',
      'provider' => 'google_fonts_api',
      'css_selector' => 'h1, h2, h3, h4, h5, h6',
      'css_family' => 'Noto Sans',
      'css_style' => 'normal',
      'css_weight' => 700,
      'css_fallbacks' => '',
      'foundry' => '',
      'foundry_url' => '',
      'license' => '',
      'license_url' => '',
      'designer' => '',
      'designer_url' => '',
      'metadata' => 'a:2:{s:4:"path";s:13:"Noto Sans:700";s:6:"subset";s:9:"latin-ext";}',
    ),
    'Open Sans regular (latin)' => array(
      'name' => 'Open Sans regular (latin)',
      'enabled' => 1,
      'url' => 'http://www.google.com/webfonts/family?family=Open Sans&subset=latin#regular',
      'provider' => 'google_fonts_api',
      'css_selector' => 'body, p, div',
      'css_family' => 'Open Sans',
      'css_style' => 'normal',
      'css_weight' => 'normal',
      'css_fallbacks' => '',
      'foundry' => '',
      'foundry_url' => '',
      'license' => '',
      'license_url' => '',
      'designer' => '',
      'designer_url' => '',
      'metadata' => 'a:2:{s:4:"path";s:17:"Open Sans:regular";s:6:"subset";s:5:"latin";}',
    ),
  );
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
