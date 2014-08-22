<?php

/**
 * @file
 */

/**
 * Implements hook_file_formatter_info().
 */
function media_flickr_file_formatter_info() {
  $formatters['media_flickr_video'] = array(
    'label' => t('Flickr Photoset'),
    'file types' => array('video'),
    'default settings' => array(
      'width' => media_flickr_variable_get('width'),
      'height' => media_flickr_variable_get('height'),
      'autoplay' => media_flickr_variable_get('autoplay'),
    ),
    'view callback' => 'media_flickr_file_formatter_video_view',
    'settings callback' => 'media_flickr_file_formatter_video_settings',
  );
  $formatters['media_flickr_image'] = array(
    'label' => t('Flickr Preview Image'),
    'file types' => array('image', 'video'),
    'default settings' => array(
      'image_style' => '',
      'link_to_flickr' => FALSE,
    ),
    'view callback' => 'media_flickr_file_formatter_image_view',
    'settings callback' => 'media_flickr_file_formatter_image_settings',
  );
  return $formatters;
}

/**
 * Implements hook_file_formatter_FORMATTER_view().
 */
function media_flickr_file_formatter_video_view($file, $display, $langcode) {
  $scheme = file_uri_scheme($file->uri);
  // WYSIWYG does not yet support video inside a running editor instance.
  if ($scheme == 'flickr' && empty($file->override['wysiwyg'])) {
    $element = array(
      '#theme' => 'media_flickr_photoset',
      '#uri' => $file->uri,
    );
    foreach (array('width', 'height', 'autoplay') as $setting) {
      $element['#' . $setting] = isset($file->override[$setting]) ? $file->override[$setting] : $display['settings'][$setting];
    }
    return $element;
  }
}

/**
 * Implements hook_file_formatter_FORMATTER_settings().
 */
function media_flickr_file_formatter_video_settings($form, &$form_state, $settings) {
  $element = array();
  $element['width'] = array(
    '#title' => t('Width'),
    '#type' => 'textfield',
    '#default_value' => $settings['width'],
  );
  $element['height'] = array(
    '#title' => t('Height'),
    '#type' => 'textfield',
    '#default_value' => $settings['height'],
  );
  $element['autoplay'] = array(
    '#title' => t('Autoplay'),
    '#type' => 'checkbox',
    '#default_value' => $settings['autoplay'],
  );
  return $element;
}

/**
 * Implements hook_file_formatter_FORMATTER_view().
 */
function media_flickr_file_formatter_image_view($file, $display, $langcode) {
  $scheme = file_uri_scheme($file->uri);
  if ($scheme == 'flickr') {
    $wrapper = file_stream_wrapper_get_instance_by_uri($file->uri);
    $image_style = $display['settings']['image_style'];
    $valid_image_styles = image_style_options(FALSE);
    if (empty($image_style) || !isset($valid_image_styles[$image_style])) {
      $element = array(
        '#theme' => 'image',
        '#path' => $wrapper->getOriginalThumbnailPath(),
      );
    }
    else {
      $element = array(
        '#theme' => 'image_style',
        '#style_name' => $image_style,
        '#path' => $wrapper->getLocalThumbnailPath(),
      );
    }
    if ($display['settings']['link_to_flickr']) {
      $element = array(
        '#theme' => 'link',
        '#text' => drupal_render($element),
        '#path' => media_flickr_original_url($file->uri),
        '#options' => array(
          'attributes' => array(),
          'html' => TRUE,
        ),
      );
    }
    return $element;
  }
}

/**
 * Implements hook_file_formatter_FORMATTER_settings().
 */
function media_flickr_file_formatter_image_settings($form, &$form_state, $settings) {
  $element = array();
  $element['image_style'] = array(
    '#title' => t('Image style'),
    '#type' => 'select',
    '#options' => image_style_options(FALSE),
    '#default_value' => $settings['image_style'],
    '#empty_option' => t('None (original image)'),
  );
  $element['link_to_flickr'] = array(
    '#title' => t('Link to Flickr'),
    '#type' => 'checkbox',
    '#default_value' => $settings['link_to_flickr'],
  );
  return $element;
}

/**
 * Implements hook_file_default_displays().
 */
function media_flickr_file_default_displays() {
  $default_displays = array();

  // Default settings for displaying as a video.
  $default_video_settings = array(
    'media_large' => array(
      'width' => 480,
      'height' => 360,
      'autoplay' => FALSE,
    ),
    'media_original' => array(
      'width' => 640,
      'height' => 480,
      'autoplay' => media_flickr_variable_get('autoplay'),
    ),
  );
  foreach ($default_video_settings as $view_mode => $settings) {
    $display_name = 'video__' . $view_mode . '__media_flickr_video';
    $default_displays[$display_name] = (object) array(
      'api_version' => 1,
      'name' => $display_name,
      'status' => 1,
      'weight' => 1,
      'settings' => $settings,
    );
  }

  // Default settings for displaying a video preview image. We enable preview
  // images even for view modes that also play video, for use inside a running
  // WYSIWYG editor. The higher weight ensures that the video display is used
  // where possible.
  $default_image_styles = array(
    'media_preview' => 'square_thumbnail',
    'media_large' => 'large',
    'media_original' => ''
  );
  foreach ($default_image_styles as $view_mode => $image_style) {
    $display_name = 'video__' . $view_mode . '__media_flickr_image';
    $default_displays[$display_name] = (object) array(
      'api_version' => 1,
      'name' => $display_name,
      'status' => 1,
      'weight' => 2,
      'settings' => array('image_style' => $image_style),
    );
  }

  return $default_displays;
}

