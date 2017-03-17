<?php

/**
 * @file
 * Provides Views integration for the button_field field.
 */

/**
 * Implements hook_field_views_data().
 */
function button_field_field_views_data($field) {
  $data = field_views_field_default_views_data($field);
  $field_name = $field['field_name'];

  // Iterate over the data and set the field handler for the button field.
  foreach ($data as $table_name => $table_data) {
    $data[$table_name][$field_name]['field']['handler'] =
      'button_field_handler_field';
  } // end for each data

  return $data;
}
