<?php

/**
 * @file
 * Functions that are only called on the admin pages.
 */

/**
 * Generate the default path for the Superfish library.
 */
function superfish_library_path() {
  // Ensure the Libraries API module is installed and working.
  if (module_exists('libraries') && function_exists('libraries_get_path')) {
    $directory = libraries_get_path('superfish');
  }
  // Otherwise use the default directory.
  elseif (file_exists('profiles/' . drupal_get_profile() . '/libraries/superfish')) {
    $directory = 'profiles/' . drupal_get_profile() . '/libraries/superfish';
  }
  else {
    $directory = 'sites/all/libraries/superfish';
  }
  if (file_exists($directory)) {
    $output = $directory . "/jquery.hoverIntent.minified.js\n" .
      $directory . "/jquery.bgiframe.min.js\n" .
      $directory . "/superfish.js\n" .
      $directory . "/supersubs.js\n" .
      $directory . "/supposition.js\n" .
      $directory . "/sftouchscreen.js\n" .
      $directory . "/sfsmallscreen.js\n" .
      $directory . "/sfautomaticwidth.js";
  }
  else {
    $output = '';
  }
  return $output;
}

/**
 * Overriding system settings form.
 */
function superfish_system_settings_form($form, $automatic_defaults = TRUE) {
  $form['actions']['#type'] = 'container';
  $form['actions']['#attributes']['class'][] = 'form-actions';
  $form['actions']['#weight'] = 100;
  $form['actions']['submit'] = array('#type' => 'submit', '#value' => t('Save configuration'));

  if ($automatic_defaults) {
    $form = _system_settings_form_automatic_defaults($form);
  }

  if (!empty($_POST) && form_get_errors()) {
    drupal_set_message(t('The settings have not been saved because of the errors.'), 'error');
  }

  // Adding our custom submission handler.
  $form['#submit'][] = 'superfish_admin_settings_submit';

  $form['#submit'][] = 'system_settings_form_submit';
  // By default, render the form using theme_system_settings_form().
  if (!isset($form['#theme'])) {
    $form['#theme'] = 'system_settings_form';
  }
  return $form;
}

/**
 * Module settings form.
 */
function superfish_admin_settings() {
  $form['superfish_number'] = array(
    '#type' => 'select',
    '#title' => t('Number of blocks'),
    '#multiple' => FALSE,
    '#options' => drupal_map_assoc(range(1, 50)),
    '#description' => t('The number of Superfish menu blocks.') . ' (' . t('Default') . ': 4' . ')' . '<br />' . t('Please note decreasing this number leads to permanent deletion of blocks.'),
    '#default_value' => variable_get('superfish_number', 4),
  );
  $form['superfish_slp'] = array(
    '#type' => 'textarea',
    '#title' => t('Path to Superfish library'),
    '#description' => t('Edit only if you are sure of what you are doing.'),
    '#default_value' => variable_get('superfish_slp', superfish_library_path()),
    '#rows' => 7,
  );
  return superfish_system_settings_form($form, FALSE);
}

/**
 * Implements hook_validate().
 */
function superfish_admin_settings_validate($form, &$form_state) {
  $error = array();
  // Removing blank lines and white spaces.
  $sf_library = preg_replace("/(^[\r\n]*|[\r\n]+)[\s\t]*[\r\n]+/", "\n", trim($form_state['values']['superfish_slp']));
  if (empty($sf_library)) {
    form_set_error('superfish_slp', t('<strong>Path to Superfish library</strong> field cannot be empty. Please try the below list:') . '<br /><pre>' . superfish_library_path() . '</pre>');
  }
  else {
    // Trimming blank lines and such.
    $sf_library = explode("\n", $sf_library);
    // Crystal clear.
    foreach ($sf_library as $s) {
      if (!file_exists($s)) {
        $error[] = $s;
      }
    }
    if (!empty($error)) {
      $error_message = '';
      if (count($error) > 1) {
        foreach ($error as $e) {
          $error_message .= '<li>' . check_plain($e) . '</li>';
        }
        $error_message = t('Files not found') . ': <ul>' . $error_message . '</ul>';
      }
      else {
        $error_message = t('File not found') . ': ' . check_plain($error[0]);
      }
      form_set_error('superfish_slp', $error_message);
    }
  }
}

/**
 * Custom submission handler for the settings form.
 */
function superfish_admin_settings_submit($form, &$form_state) {
  $values = &$form_state['values'];
  $before = variable_get('superfish_number', 4);
  $after = $values['superfish_number'];
  // If the number of blocks has been decreased.
  if ($before > $after) {
    // How many blocks should be removed?
    $reduce = $before - $after;
    // Remove each block with all its variables.
    $delta = $after;
    for ($i = 0; $i < $reduce; $i++) {
      $delta++;
      db_delete('variable')->condition('name', 'superfish_%%_' . $delta, 'LIKE')->execute();
      db_delete('block')->condition('module', 'superfish')->condition('delta', $delta)->execute();
      db_delete('block_role')->condition('module', 'superfish')->condition('delta', $delta)->execute();
    }
    drupal_set_message(t('Successfully removed @number Superfish block(s).', array('@number' => $reduce)));
  }
}