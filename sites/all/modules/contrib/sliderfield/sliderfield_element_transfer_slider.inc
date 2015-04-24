<?php

/**
 * Implements hook_theme().
 */
function _sliderfield_theme_transfer_slider() {
  $data['transfer_slider'] = array(
    'render element' => 'element',
    'file' => 'sliderfield_element_transfer_slider.inc',
  );
  return $data;
}

/**
 * Implements hook_element_info().
 */
function _sliderfield_element_info_transfer_slider() {
  $types['transfer_slider'] =  array(
    '#input'            => TRUE,
    '#process'          => array('sliderfield_transfer_slider_process'),
    '#element_validate' => array('sliderfield_transfer_slider_validate'),
    '#left'             => t('Left'),
    '#right'            => t('Right'),
    '#theme'            => array('sliderfield_transfer_slider'),
    '#left_value'       => 0,
    '#right_value'      => 100,
    '#size'             => 5,
  );
  return $types;
}

/**
 * Processes transfer slider: add textfields
 * @param unknown_type $element
 */
function sliderfield_transfer_slider_process($element) {
  $element['#tree'] = TRUE;

  // Generate left input for slider
  $element['left'] = array(
    '#prefix'           => '<div class="transfer-slider container-inline">',
    '#type'             => 'textfield',
    '#field_prefix'     => $element['#left'],
    '#default_value'    => $element['#left_value'],
    '#element_validate' => array('sliderfield_validate_integer'),
    '#size'             => $element['#size'],
    '#attributes'       => array('class' => array('transfer-slider-left-field')),
  );

  // Create markup for slider container
  $element['container']['#markup'] = '<div class="transfer-slider-container"></div>';
  $element['container']['#attached'] = array(
    'library' => array(
      array('system', 'ui.slider')
    ),
    'js' => array(
      drupal_get_path('module', 'sliderfield') . '/sliderfield_element_transfer_slider.js',
    ),
    'css' => array(
      array(
        'data' => drupal_get_path('module', 'sliderfield') . '/sliderfield_element_transfer_slider.css',
        'type' => 'file',
        //'group' => CSS_SYSTEM,
        'weight' => 2000,
      )
    ),
  );

  // Generate right input for slider
  $element['right'] = array(
    '#type'             => 'textfield',
    '#field_suffix'     => $element['#right'],
    '#default_value'    => $element['#right_value'],
    '#element_validate' => array('sliderfield_validate_integer'),
    '#size'             => $element['#size'],
    '#attributes'       => array('class' => array('transfer-slider-right-field')),
    '#suffix'           => '</div>',
  );

  return $element;
}

/**
 * Validates transfer_slider
 *
 * @param array $element
 * @param array $form_state
 */
function sliderfield_transfer_slider_validate($element, &$form_state) {
  $sum = $element['#left_value'] + $element['#right_value'];
  if (($element['#value']['left'] + $element['#value']['right']) != $sum) {
    form_error($element, t("The sum of left and right values doesn't check with original."));
  }
}