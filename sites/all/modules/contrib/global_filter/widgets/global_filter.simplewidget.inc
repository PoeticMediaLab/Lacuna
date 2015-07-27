<?php

/**
 * @file
 * global_filter.simplewidget.inc
 */

/**
 * Create simple widget.
 */
function global_filter_create_simple_widget($filter_key, $options, &$form, &$form_state) {
  $name   = $form_state['global_filters'][$filter_key]['name'];
  $widget = $form_state['global_filters'][$filter_key]['widget'];

  $default_value = isset($form_state['input'][$name]) ? $form_state['input'][$name] : global_filter_get_session_value($name);

  if (is_array($default_value)) {
    if ($widget == 'radios' || $widget == 'textfield') {
      $default_value = reset($default_value);
    }
  }
  else {
    if ($widget == 'checkboxes') {
      $default_value = array($default_value);
    }
  }

  $form[$name] = array(
    '#type' => ($widget == 'multiselect') ? 'select' : $widget,
    '#default_value' => $default_value,
    // @todo: add description.
    '#description' => NULL,
  );
  if ($widget == 'textfield') {
    $form[$name]['#size'] = 20;
  }
  elseif (!empty($options)) {
    $form[$name]['#options'] = $options;
    $form[$name]['#multiple'] = in_array($widget, array('multiselect', 'checkboxes'));
  }
}
