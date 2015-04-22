<?php

/**
 * @file
 * File formatters for oEmbed resources.
 */

/**
 * Implements hook_file_formatter_info().
 */
function media_oembed_file_formatter_info() {
  $formatters['media_oembed'] = array(
    'label' => t('oEmbed'),
    'description' => t('All-purpose oEmbed formatter.'),
    'file types' => array('audio', 'document', 'image', 'video'),
    'mime types' => array('audio/oembed', 'image/oembed', 'text/oembed', 'video/oembed'),
    'default settings' => array(
      'width' => '640',
      'height' => '360',
    ),
    'view callback' => 'media_oembed_file_formatter_oembed_view',
    'settings callback' => 'media_oembed_file_formatter_oembed_settings',
  );
  $formatters['media_oembed_thumbnail'] = array(
    'label' => t('oEmbed thumbnail'),
    'description' => t('oEmbed thumbnail media.'),
    'file types' => array('audio', 'document', 'image', 'video'),
    'mime types' => array('audio/oembed', 'image/oembed', 'text/oembed', 'video/oembed'),
    'default settings' => array(
      'image_style' => '',
    ),
    'view callback' => 'media_oembed_file_formatter_oembed_thumbnail_view',
    'settings callback' => 'media_oembed_file_formatter_oembed_thumbnail_settings',
  );

  return $formatters;
}

/**
 * Implements hook_file_formatter_FORMATTER_settings().
 */
function media_oembed_file_formatter_oembed_settings($form, &$form_state, $settings) {
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

  return $element;
}

/**
 * Implements hook_file_formatter_FORMATTER_view().
 */
function media_oembed_file_formatter_oembed_view($file, $display, $langcode) {
  $scheme = file_uri_scheme($file->uri);

  if ($scheme == 'oembed') {
    $element = array(
      '#theme' => 'media_oembed',
      '#uri' => $file->uri,
      '#options' => array(),
    );

    // Fake a default for attributes so the ternary doesn't choke.
    $display['settings']['attributes'] = array();

    foreach (array('width', 'height') as $setting) {
      $element['#options'][$setting] = isset($file->override[$setting]) ? $file->override[$setting] : $display['settings'][$setting];
    }

    return $element;
  }
}

/**
 * Implements hook_file_formatter_FORMATTER_settings().
 */
function media_oembed_file_formatter_oembed_thumbnail_settings($form, &$form_state, $settings) {
  $element = array();

  $element['image_style'] = array(
    '#title' => t('Image style'),
    '#type' => 'select',
    '#options' => image_style_options(FALSE),
    '#default_value' => $settings['image_style'],
    '#empty_option' => t('None (original image)'),
  );

  return $element;
}

/**
 * Implements hook_file_formatter_FORMATTER_view().
 */
function media_oembed_file_formatter_oembed_thumbnail_view($file, $display, $langcode) {
  $scheme = file_uri_scheme($file->uri);

  if ($scheme == 'oembed') {
    $wrapper = file_stream_wrapper_get_instance_by_uri($file->uri);
    $image_style = $display['settings']['image_style'];
    $valid_image_styles = image_style_options(FALSE);

    $element = array();

    if (!empty($file->alt)) {
      $alt = $file->alt;
    }
    else {
      $alt = $file->filename;
    }

    if (!empty($file->title)) {
      $title = $file->title;
    }
    else {
      $title = '';
    }

    if (empty($image_style) || !isset($valid_image_styles[$image_style])) {
      if ($path = $wrapper->getOriginalThumbnailPath()) {
        $element = array(
          '#theme' => 'image',
          '#path' => $path,
          '#alt' => isset($file->override['attributes']['alt']) ? $file->override['attributes']['alt'] : $alt,
          '#title' => isset($file->override['attributes']['title']) ? $file->override['attributes']['title'] : $title,
        );
      }
    }
    else {
      if ($path = $wrapper->getLocalThumbnailPath()) {
        $element = array(
          '#theme' => 'image_style',
          '#style_name' => $image_style,
          '#path' => $path,
          '#alt' => isset($file->override['attributes']['alt']) ? $file->override['attributes']['alt'] : $alt,
          '#title' => isset($file->override['attributes']['title']) ? $file->override['attributes']['title'] : $title,
        );
      }
    }

    if (!empty($element)) {
      return $element;
    }
  }
}
