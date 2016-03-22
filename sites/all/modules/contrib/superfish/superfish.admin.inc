<?php

/**
 * @file
 * Functions that are only called on the admin pages.
 */

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
    '#type' => 'textfield',
    '#title' => t('Number of blocks'),
    '#multiple' => FALSE,
    '#description' => t('The number of Superfish menu blocks.') . ' (' . t('Default') . ': 4' . ')' . '<br />' . t('Please note decreasing this number leads to permanent deletion of blocks.'),
    '#default_value' => variable_get('superfish_number', 4),
  );
  return superfish_system_settings_form($form, FALSE);
}

/**
 * Implements hook_validate().
 */
function superfish_admin_settings_validate($form, &$form_state) {
  if (!is_numeric($form_state['values']['superfish_number'])) {
    form_set_error('superfish_number', t('Please enter a number.'));
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