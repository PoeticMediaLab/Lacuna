<?php
/**
 * @file
 * Administration pages for the 'jQuery UI filter' module.
 */

////////////////////////////////////////////////////////////////////////////////
// General settings form
////////////////////////////////////////////////////////////////////////////////

/**
 * Form builder; General settings page for the 'jQuery UI filter' module.
 *
 * @ingroup forms
 */
function jquery_ui_filter_general_settings() {
  // General
  $form['general'] = array(
    '#type' => 'fieldset',
    '#title' => 'General settings',
  );

  $form['general']['jquery_ui_filter_disabled_pages'] = array(
    '#type' => 'textarea',
    '#title' => t('Disable jQuery UI widgets on specific pages'),
    '#description' => t("Enter one page per line as Drupal paths. The '*' character is a wildcard. Example paths are '@example'", array('@example' => 'print*')),
    '#default_value' => variable_get('jquery_ui_filter_disabled_pages', 'print*'),
  );

  return system_settings_form($form);
}

/**
 * Demo settings form
 */
function jquery_ui_filter_demo_settings($form_state) {
  if (isset($form_state['post']['op']) && $form_state['post']['op'] == t('Reset')) {
    drupal_goto($_GET['q']);
  }

  $form = array('#redirect' => FALSE);

  // Demos
  foreach (array('accordion', 'dialog', 'tabs') as $type) {
    if (module_exists("jquery_ui_filter_$type")) {
      module_load_include('admin.inc', "jquery_ui_filter_$type");
      $func = "_jquery_ui_filter_${type}_demo";
      $form += $func ($form_state);
    }
  }

  // Submit
  $form['html']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Update'),
  );
  $form['html']['reset'] = array(
    '#type' => 'submit',
    '#value' => t('Reset'),
  );

  return $form;
}

/**
 * jQuery UI filter demo container html.
 */
function _jquery_ui_filter_demo_get_container_html() {
  return '<p>Pellentesque habitant morbi tristique senectus et netus et malesuada fames ac turpis egestas. Vestibulum tortor quam, feugiat vitae, ultricies eget, tempor sit amet, ante. Donec eu libero sit amet quam egestas semper. Aenean ultricies mi vitae est. Mauris placerat eleifend leo.</p>
<ul>
<li>Lorem ipsum dolor sit amet, consectetuer adipiscing elit.</li>
<li>Aliquam tincidunt mauris eu risus.</li>
<li>Vestibulum auctor dapibus neque.</li>
</ul>';
}
/**
 * jQuery UI filter demo check markup.
 */
function _jquery_ui_filter_demo_check_markup($type, $text) {
  $prepare_callback = "_jquery_ui_filter_${type}_prepare_callback";
  if (function_exists($prepare_callback)) {
    $text = $prepare_callback($text);
  }

  $text = _filter_htmlcorrector($text);
  $allowed_tags = preg_split('/\s+|<|>/', '<a> <p> <div> <script> <ul> <li> <h1> <h2> <h3> <h4> <h5> <h6>', -1, PREG_SPLIT_NO_EMPTY);
  $text = filter_xss($text, $allowed_tags);

  $process_callback = "_jquery_ui_filter_${type}_process_callback";
  $text = $process_callback($text);

  return $text;
}

////////////////////////////////////////////////////////////////////////////////
// Form helper functions
////////////////////////////////////////////////////////////////////////////////

/**
 * Add default buttons to a jQuery UI widget form and set its submit handler.
 */
function _jquery_ui_filter_widget_settings_form($form, $type) {
  $form['type'] = array('#type' => 'value', '#value' => $type);

  $form['buttons']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save configuration'),
  );

  $form['#submit'][] = '_jquery_ui_filter_widget_settings_form_submit';
  return $form;
}

/**
 * Submit handler; Setting form for the 'jQuery UI filter' module.
 *
 * @ingroup forms
 */
function _jquery_ui_filter_widget_settings_form_submit($form, &$form_state) {
  $values = $form_state['values'];
  $type = $values['type'];

  foreach ($values as $key => $value) {
    if (strpos($key, "jquery_ui_filter_${type}") === FALSE) {
      continue;
    }

    if ($key == "jquery_ui_filter_${type}_options") {
      $value = _jquery_ui_filter_set_options($value);
    }

    variable_set($key, $value);
  }
  drupal_set_message(t('The configuration options have been saved.'));

  // DEBUG:
  // dpm(variable_get("jquery_ui_filter_${type}_options", array()));
}

/**
 * Get Fx hide or show options.
 */
function _jquery_ui_filter_admin_settings_fx_options($default_values = array()) {
  $fx_options = array();
  $fx_options['opacity'] = array(
    '#title' => t('opacity'),
    '#type' => 'checkbox',
    // Usually the best tab effect is just to use opacity (aka fade in/out)
    '#default_value' => !empty($default_values['opacity']),
    '#return_value' => 'toggle'
  );
  $fx_options['height'] = array(
    '#title' => t('height'),
    '#type' => 'checkbox',
    '#default_value' => !empty($default_values['height']),
    '#return_value' => 'toggle'
  );
  // width: [SKIPPED]
  // Adjusting the width cause unpredictable results so don't include it.
  $fx_options['duration'] = array(
    '#title' => t('duration'),
    '#type' => 'select',
    '#default_value' => (!empty($default_values['duration'])) ? $default_values['duration'] : 'normal',
    '#options' => array('normal' => 'normal', 'slow' => 'slow', 'medium' => 'medium', 'fast' => 'fast'),
  );
  return $fx_options;
}

/**
 * Set jQuery UI tabs or accordion options objects.
 */
function _jquery_ui_filter_set_options($options) {
  _jquery_ui_filter_set_options_types_recursive($options);

  // Clean up fx options by removing toggle options that are set to 0.
  if (isset($options['fx_options'])) {
    $options['fx_options'][0] = array_filter($options['fx_options'][0]);
    $options['fx_options'][1] = array_filter($options['fx_options'][1]);
  }

  // Set options object for enabled options (ie fx, cookie, etc...);
  foreach ($options as $name => $value) {
    if (isset($options[$name . '_options'])) {
      if ($value) {
        $options[$name] = $options[$name . '_options'];
      }
      unset($options[$name . '_options']);
    }
  }

  return $options;
}

/**
 * Convert jQuery UI tabs or accordion options numeric strings to integers.
 */
function _jquery_ui_filter_set_options_types_recursive(&$options) {
  foreach ($options as $name => $value) {
    if (is_numeric($value)) {
      $options[$name] = (int) $value;
    }
    elseif (is_array($value)) {
      _jquery_ui_filter_set_options_types_recursive($options[$name]);
    }
  }
}
