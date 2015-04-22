<?php

/**
 * @file
 * Field integration for the MediaElement module.
 */

/**
 * Implements hook_field_formatter_info().
 */
function mediaelement_field_formatter_info() {
  $formatters = array();

  $formatters['mediaelement_video'] = array(
    'label' => t('MediaElement Video'),
    'field types' => array('file', 'link_field'),
    'settings' => array(
      'controls' => variable_get('mediaelement_video_default_controls', TRUE),
      'width' => variable_get('mediaelement_video_default_width', '640'),
      'height' => variable_get('mediaelement_video_default_height', '385'),
      'download_link' => variable_get('mediaelement_video_default_download_link', FALSE),
      'download_text' => variable_get('mediaelement_video_default_download_text', t('Download')),
    ),
  );

  $formatters['mediaelement_audio'] = array(
    'label' => t('MediaElement Audio'),
    'field types' => array('file', 'link_field'),
    'settings' => array(
      'controls' => variable_get('mediaelement_audio_default_controls', TRUE),
      'width' => variable_get('mediaelement_audio_default_width', '300'),
      'height' => variable_get('mediaelement_audio_default_height', '30'),
      'download_link' => variable_get('mediaelement_audio_default_download_link', FALSE),
      'download_text' => variable_get('mediaelement_audio_default_download_text', t('Download')),
    ),
  );

  return $formatters;
}

/**
 * Implements hook_field_formatter_settings_form().
 */
function mediaelement_field_formatter_settings_form($field, $instance, $view_mode, $form, &$form_state) {
  $display = $instance['display'][$view_mode];
  $settings = $display['settings'];
  $element = array();

  $element['controls'] = array(
    '#title' => t('Controls'),
    '#type' => 'checkbox',
    '#default_value' => $settings['controls'],
  );

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

  $element['download_link'] = array(
    '#title' => t('Download Link'),
    '#type' => 'checkbox',
    '#default_value' => $settings['download_link'],
  );

  $element['download_text'] = array(
    '#title' => t('Download Link Text'),
    '#type' => 'textfield',
    '#default_value' => $settings['download_text'],
  );

  return $element;
}

/**
 * Implements hook_field_formatter_settings_summary().
 */
function mediaelement_field_formatter_settings_summary($field, $instance, $view_mode) {
  $display = $instance['display'][$view_mode];
  $settings = $display['settings'];
  return t('Width: @width px, Height: @height px', array('@width' => $settings['width'], '@height' => $settings['height']));
}

/**
 * Implements hook_field_formatter_view().
 */
function mediaelement_field_formatter_view($entity_type, $entity, $field, $instance, $langcode, $items, $display) {
  // A unique caller per page for the JS specific settings to use. This may be
  // different for ever page view and should not be used for styling.
  static $id = 0;
  $element = array();
  $path = drupal_get_path('module', 'mediaelement');
  foreach ($items as $delta => $item) {
    // Support the link field type which stores it's data in 'url'.
    $src = ($field['type'] == 'link_field') ? $item['url'] : $item['uri'];

    $settings = $display['settings'];
    $js_settings = array();
    $js_settings['opts'] = array();
    $js_settings['controls'] = (bool)$settings['controls'];
    if ($display['type'] == 'mediaelement_video') {
      $js_settings['opts']['videoHeight'] = (int)$settings['height'];
      $js_settings['opts']['videoWidth'] = (int)$settings['width'];
    }
    elseif ($display['type'] == 'mediaelement_audio') {
      $js_settings['opts']['audioHeight'] = (int)$settings['height'];
      $js_settings['opts']['audioWidth'] = (int)$settings['width'];
    }

    $class = 'mediaelement-formatter-identifier-' . time() . '-' . $id++;
    $element[$delta] = array(
      '#attributes' => array(
        'src' => file_create_url($src),
        'class' => $class,
      ),
      '#settings' => $settings,
      '#attached' => array(
        'library' => array(array('mediaelement', 'mediaelement')),
        'js' => array(
          $path . '/mediaelement.js' => array(),
          0 => array('type' => 'setting', 'data' => array('mediaelement' => array('.' . $class => $js_settings))),
        ),
      ),
    );
    if ($settings['controls']) {
      $element[$delta]['#attributes']['controls'] = 'controls';
    }

    if ($display['type'] == 'mediaelement_video') {
      $element[$delta]['#theme'] = 'mediaelement_video';
      $element[$delta]['#attributes']['height'] = $display['settings']['height'];
      $element[$delta]['#attributes']['width'] = $display['settings']['width'];
    }
    elseif ($display['type'] == 'mediaelement_audio') {
      $element[$delta]['#theme'] = 'mediaelement_audio';
    }
  }
  return $element;
}
