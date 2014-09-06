<?php

/**
 * Admin page; Menu callback.
 */
function annotator_admin() {
  $form = $plugin_options = array();
  $form['annotator_element'] = array(
    '#type' => 'textfield',
    '#title' => t('Annotator element'),
    '#description' => 'Use jQuery to select the element that you would like to annotate. ' . l('Read more', 'http://docs.annotatorjs.org/en/latest/getting-started.html#setting-up-annotator'),
    '#default_value' => variable_get('annotator_element','.node'),
  );
  $form['plugins'] = array(
    '#type' => 'fieldset',
    '#title' => t('Plugins'),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
  );
  ctools_include('plugins');
  $plugins = ctools_get_plugins('annotator', 'annotator');
  foreach ($plugins as $plugin) {
    $class = ctools_plugin_get_class($plugin, 'handler');
    $instance = new $class($plugin);
    if ($instance_settings = $instance->settingsForm()) {
      $settings['annotator_' . $plugin['name']] = array(
        '#tree' => TRUE,
        '#type' => 'fieldset',
        '#title' => $plugin['label'],
        '#collapsible' => TRUE,
        '#collapsed' => TRUE,
      );
      $settings['annotator_' . $plugin['name']] += (array) $instance->settingsForm();
    }
    $plugin_options[ucfirst($plugin['name'])] = $plugin['label'];
  }

  $annotator_plugins = variable_get('annotator_plugins', array());
  $form['plugins']['annotator_plugins'] = array(
    '#type' => 'checkboxes',
    '#description' => t('Enable the desired annotator plugins'),
    '#options' => $plugin_options,
    '#default_value' => $annotator_plugins,
  );
  $form['settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Plugin settings'),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
  );
  $form['settings'] += (array) $settings;
  return system_settings_form($form);
}
