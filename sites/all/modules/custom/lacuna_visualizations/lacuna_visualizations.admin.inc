<?php
/**
 * Routines for the administration form
 */
function lacuna_visualizations_admin_form() {
  $form = array();

  $form['lacuna_visualizations_cache_threshold'] = array(
    '#type' => 'textfield',
    '#title' => t('Cache threshold'),
    '#description' => t('Set the minimum number of annotations in a course before the dashboard is cached.'),
    '#default_value' => variable_get('lacuna_visualizations_cache_threshold', 1000),
    '#required' => TRUE,
  );

  $form['lacuna_visualizations_cache_ttl'] = array(
    '#type' => 'textfield',
    '#title' => t('Cache duration'),
    '#description' => t('Set the time in hours after which the cache should expire.'),
    '#default_value' => variable_get('lacuna_visualizations_cache_ttl', 24),
    '#required' => TRUE,
  );

  return system_settings_form($form);
}
