<?php
/**
 * @file
 * D3 admin file
 */

/**
 * D3 configuration form
 */
function d3_config_form($form, &$form_state) {
  $form['d3_library_source'] = array(
    '#title' => 'D3 library source',
    '#description' => 'Get the d3 source library from CDN, or from the libraries module',
    '#type' => 'select',
    '#options' => array('lib' => 'Libraries', 'cdn' => 'CDN'),
    '#default_value' => variable_get('d3_library_source', 'lib'),
  );

  $form['#submit'][] = 'd3_config_form_submit';
  return system_settings_form($form);
}

function d3_config_form_submit(&$form, &$form_state) {
  foreach (array('libraries_get_path', 'libraries_info') as $name) {
    drupal_static_reset($name);
  }
  cache_clear_all('*', 'cache_libraries', TRUE);
}
