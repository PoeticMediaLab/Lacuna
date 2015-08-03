<?php

/**
 * @file
 * global_filter.datewidget.inc
 */

/**
 * Implements hook_field_widget_properties_alter().
 *
 * Called from field_default_form() this alters the widget properties of a
 * field instance before it gets displayed.
 * Used here to make sure that the Date module doesn't impose its defaults on
 * the widget, as we already do that based on the session when
 * 'set_date_from_session' is set on the form_state.
 * @see global_filter_field_widget_form_alter()
 */
function global_filter_field_widget_properties_alter(&$widget, $context) {
  // Do nothing if this isn't a widget ear-marked by Global Filter.
  if (empty($widget['is_global_filter'])) {
    return;
  }
  switch ($widget['module']) {
    case 'date':
      $widget['is_new'] = FALSE;
      break;
  }
}

/**
 * Implements hook_date_combo_process_alter().
 *
 * Remove the 'Show End Date' checkbox and line up the start and end date boxes.
 */
function global_filter_date_combo_process_alter(&$element, &$form_state, &$context) {
  if (!empty($context['form']['#id']) && strpos($context['form']['#id'], 'global-filter') === 0) {
    // Remove 'Show End Date' checkbox.
    unset($element['show_todate']);
    if (empty($element['value']['#title'])) {
      // Remove 'to:' from end box so it lines up vertically with start box.
      unset($element['value2']['#title']);
    }
  }
}

/**
 * Implements hook_field_widget_form_alter().
 *
 * Responds to 'set_date_from_session' being set on the $form_state.
 */
function global_filter_field_date_widget_form_alter(&$element, &$form_state, $context) {

  if (!empty($form_state['set_date_from_session'])) {

    $session_value = global_filter_get_session_value($element['#field_name']);

    if (class_exists('date_sql_handler')) {
      // Date module.
      $date_range = new date_sql_handler();
      $parts = $date_range->arg_parts($session_value);
    }
    else {
      // @todo Format needs to be parts[0][date][year,month,day]
      // Use explode('--', $session_value); ?
      $parts = array();
    }
    if (!empty($parts[0]['date'])) {
      $field = $context['field'];
      $instance = $context['instance'];
      $lang = $context['langcode'];
      $instance['settings']['default_value'] = 'strtotime';
      $instance['settings']['default_value_code']  = implode('-', $parts[0]['date']);
      if (!empty($parts[1]['date'])) {
        $instance['settings']['default_value2'] = 'strtotime';
        $instance['settings']['default_value_code2'] = implode('-', $parts[1]['date']);
      }
      // Date module.
      $default_date_range = date_default_value($field, $instance, $lang);
      $element['#default_value'] = reset($default_date_range);
    }
  }
}

/**
 * Convert the date range received on the form to the standard string.
 *
 * @param array $form_state
 *   the form state
 * @param int $filter_key
 *   the filter key
 *
 * @return string
 *   date range in the format YYYY-MM-DD--YYYY-MM-DD
 */
function global_filter_extract_date_range($form_state, $filter_key) {
  $name = $form_state['global_filters'][$filter_key]['name'];
  $lang = $form_state['language'];
  if (empty($form_state['input'][$name][$lang][0]) || !is_array($form_state['input'][$name][$lang][0])) {
    // Not a date.
    return FALSE;
  }
  $values = $form_state['input'][$name][$lang][0];
  if (isset($values['value']['date'])) {
    // From date_popup.
    $date_string = $values['value']['date'];
    if (!empty($date_string)) {
      // @todo Add support for hours and minutes
      $timestamp = strtotime($date_string);
      $value = format_date($timestamp, 'custom', 'Y-m-d');
      if (!empty($values['value2']['date'])) {
        $timestamp2 = strtotime($values['value2']['date']);
        $value .= '--' . format_date($timestamp2, 'custom', 'Y-m-d');
      }
    }
  }
  elseif (!empty($values['value']['day'])) {
    // From date_select.
    $value = $form_state['input'][$name][$lang][0]['value'];
    $day = drupal_strlen($value['day']) == 1 ? ('0' . $value['day']) : $value['day'];
    $month = drupal_strlen($value['month']) == 1 ? ('0' . $value['month']) : $value['month'];
    $value = $value['year'] . '-' . $month . '-' . $day;
    if (!empty($form_state['input'][$name][$lang][0]['value2']['day'])) {
      $value2 = $form_state['input'][$name][$lang][0]['value2'];
      $day = drupal_strlen($value2['day']) == 1 ? ('0' . $value2['day']) : $value2['day'];
      $month = drupal_strlen($value2['month']) == 1 ? ('0' . $value2['month']) : $value2['month'];
      $value .= '--' . $value2['year'] . '-' . $month . '-' . $day;
    }
  }
  // Check for corrupt date and return.
  return (empty($value) || drupal_strlen($value) < 10) ? '' : $value;
}

/**
 * Set instance date widget value.
 */
function global_filter_set_instance_date_widget_value(&$field, $instance, &$form_state) {

  $name = $field['field_name'];
  $lang = $form_state['language'];

  if (empty($form_state['input'][$name][$lang])) {
    // If this is the first time the form is presented, tell
    // global_filter_field_date_widget_form_alter() to take the date range
    // from the session and convert it into a widget-compatible format.
    $form_state['set_date_from_session'] = TRUE;
    $items = array();
  }
  else {
    $items = $form_state['input'][$name][$lang];
  }
  $form_state['field'][$name][$lang] = array(
    'field' => $field,
    'instance' => $instance,
    'items_count' => 1,
  );
  // Make sure that a Date global filter always appears with an end date.
  // For date_combo_element_process().
  $form_state['field'][$name][$lang]['field']['settings']['todate'] = TRUE;
  // For date_default_value().
  $field['settings']['todate'] = TRUE;

  return $items;
}
