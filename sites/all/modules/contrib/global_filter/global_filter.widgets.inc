<?php

/**
 * @file
 * global_filter.widgets.inc
 */

define('GLOBAL_FILTER_DEF_OPTION_ALL_TEXT', t('All'));
// Does not require Location module.
define('GLOBAL_FILTER_VIEWS_COUNTRY_FIELD', 'country');
// Requires Location module.
define('GLOBAL_FILTER_VIEWS_PROXIMITY_FIELD', 'distance');
// Core Search module.
define('GLOBAL_FILTER_VIEWS_SEARCH_TERMS_FIELD', 'keys');
// Requires Search API module.
define('GLOBAL_FILTER_VIEWS_SEARCH_API_FULLTEXT', 'search_api_views_fulltext');

define('GLOBAL_FILTER_VIEWS_TID', 'tid');
define('GLOBAL_FILTER_VIEWS_TID_DEPTH', 'term_node_tid_depth');

$path = DRUPAL_ROOT . '/' . drupal_get_path('module', 'global_filter');
include_once $path . '/widgets/global_filter.datewidget.inc';
include_once $path . '/widgets/global_filter.linkswidget.inc';
include_once $path . '/widgets/global_filter.proximitywidget.inc';
include_once $path . '/widgets/global_filter.rangewidget.inc';
include_once $path . '/widgets/global_filter.simplewidget.inc';

/**
 * Implements hook_forms().
 *
 * Called as a result of the fact that there are no hard-coded handlers for the
 * unique form_id's ('global_filter_block_1', 'global_filter_block_2'...),
 * generated in global_filter_block_info().
 * Here we map these form_id's back to the same 'global_filter_submission_form'.
 */
function global_filter_forms($form_id, $args) {
  if (strpos($form_id, GLOBAL_FILTER_BLOCK_ID_PREFIX) === 0) {
    // Convert $form_id to block#
    $block_number = _global_filter_number($form_id);
    $form = array(
      $form_id => array(
        'callback' => 'global_filter_submission_form',
        'callback arguments' => array($block_number),
      ),
    );
    return $form;
  }
}

/**
 * Creates the global selector widgets, e.g., drop-down, radio-boxes, links...
 *
 * @ingroup forms
 */
function global_filter_submission_form($form, &$form_state, $block_number) {

  if (!isset($form_state['language'])) {
    $form_state['language'] = LANGUAGE_NONE;
  }
  foreach (global_filter_get_filters_for_block($block_number) as $key => $filter) {

    $form_state['global_filters'][$key]['name'] = $filter['name'];
    $form_state['global_filters'][$key]['widget'] = $filter['widget'];
    $form_state['global_filters'][$key]['label'] = $filter['label'];

    global_filter_create_widget($key, $form, $form_state);
  }
  // Complete form with markup and visible or invisible submit button (unless
  // the form contains link widgets only).
  global_filter_finalise_form($form, $block_number);

  $path = drupal_get_path('module', 'global_filter');
  $form['#attached']['css'][] = $path . '/global_filter.css';
  $form['#attributes']['class'][] = drupal_html_class('global-filter');

  return $form;
}

/**
 * Based on the requested or field-implied widget.
 *
 * There are three main cases:
 * o global filter driven by a view: user may request any list widget
 * o global filter driven by a node property, search term: textfield
 * o global filter driven by a field: widget default may be overriden by user
 *
 * @param int $filter_key
 *   1, 2, 3..
 * @param array $form
 *   the form that will be added to, cannot be NULL
 * @param array $form_state
 *   the form state
 */
function global_filter_create_widget($filter_key, &$form, &$form_state) {

  $name = $form_state['global_filters'][$filter_key]['name'];
  $widget_label = $form_state['global_filters'][$filter_key]['label'];

  $option_all_text = global_filter_get_parameter($filter_key, 'option_all_text');
  $options = empty($option_all_text) ? array('' => GLOBAL_FILTER_DEF_OPTION_ALL_TEXT) : ($option_all_text == '<none>' ? array() : array('' => $option_all_text));

  // Establish the widget type and create widget form accordingly.
  $exceptions = array(
    GLOBAL_FILTER_VIEWS_PROXIMITY_FIELD,
    GLOBAL_FILTER_VIEWS_SEARCH_TERMS_FIELD,
    GLOBAL_FILTER_VIEWS_SEARCH_API_FULLTEXT,
    GLOBAL_FILTER_VIEWS_TID,
    GLOBAL_FILTER_VIEWS_TID_DEPTH,
  );
  if (strpos($name, 'view') === 0) {

    $requested_widget = $form_state['global_filters'][$filter_key]['widget'];
    if (empty($requested_widget) || $requested_widget == 'default') {
      $requested_widget = 'select';
    }
    $view_name = drupal_substr($name, 5);
    global_filter_add_view_results($options, $view_name);
  }
  elseif (in_array($name, $exceptions) || in_array($name, array_keys(global_filter_get_node_properties()))) {
    $requested_widget = $form_state['global_filters'][$filter_key]['widget'];
    if ($requested_widget != 'proximity' && $requested_widget != 'range') {
      $requested_widget = 'textfield';
    }
  }
  else {
    // Probably a field widget.
    if ($name == GLOBAL_FILTER_VIEWS_COUNTRY_FIELD) {

      $requested_widget = 'select';
      if (global_filter_get_module_parameter('global_filter_take_countries_from_location_module', TRUE) && module_exists('location')) {
        // Assemble country list based on the 2-letter country codes in the
        // {location} table.
        $countries = array();
        $result = db_query('SELECT DISTINCT country FROM {location}');
        foreach ($result as $country) {
          $countries[$country->country] = location_country_name($country->country);
        }
      }
      else {
        // Use core's list. Note: country codes will be in uppercase.
        include_once DRUPAL_ROOT . '/includes/locale.inc';
        $countries = country_get_list();
      }
      natcasesort($countries);
      $options = array_merge($options, $countries);
    }
    else {
      // Field-based widget.
      $field = field_info_field($name);
      if (!$field) {
        if ($name) {
          drupal_set_message(t('The field %name used for filter #@filter does not exist. Please re-configure the associated Global Filter block.',
            array('%name' => $name, '@filter' => $filter_key)), 'error');
        }
        return;
      }
      $instances = global_filter_get_field_instances($name);
      if (empty($instances)) {
        global_filter_debug(t('Global filter: no instances found of field %name', array('%name' => $name)));
        return;
      }
      if (!($requested_widget = $form_state['global_filters'][$filter_key]['widget'])) {
        $requested_widget = 'default';
      }
      foreach ($instances as $instance) {
        // If there are multiple widget instances, pick the one requested.
        if ('default_' . $instance['widget']['type'] == $requested_widget) {
          break;
        }
      }
      // Starts with 'default' or 'default_'.
      if (strpos($requested_widget, 'default') === 0 ||
        (strpos($instance['widget']['type'], 'date') === 0) && $requested_widget != 'textfield') {

        // Inherit native widget and set back on form.
        $form_state['global_filters'][$filter_key]['widget'] = $instance['widget']['type'];

        global_filter_debug(t('Global Filter @name (on %bundle) uses %widget widget', array(
          '%bundle' => $instance['bundle'], '@name' => $name, '%widget' => $instance['widget']['type'])));

        if (!empty($widget_label)) {
          // Also field_default_form() does check_plain().
          $instance['label'] = ($widget_label == '<none>') ? NULL : $widget_label;
        }
        global_filter_create_field_instance_widget($option_all_text, $field, $instance, $form, $form_state);

        $lang = $form_state['language'];

        // Don't want to see asterisk in filter.
        $form[$name][$lang]['#required'] = FALSE;
        if (empty($form[$name][$lang]['#title'])) {
          // Remove empty title so that it won't take up any screen space.
          unset($form[$name][$lang]['#title']);
        }
        // Repeat the above for children and grand-children, if any.
        foreach (element_children($form[$name][$lang]) as $key0) {
          $form[$name][$lang][$key0]['#required'] = FALSE;
          if (empty($form[$name][$lang][$key0]['#title'])) {
            unset($form[$name][$lang][$key0]['#title']);
          }
          foreach (element_children($form[$name][$lang][$key0]) as $key) {
            $form[$name][$lang][$key0][$key]['#required'] = FALSE;
            if (empty($form[$name][$lang][$key0][$key]['#title'])) {
              unset($form[$name][$lang][$key0][$key]['#title']);
            }
          }
        }
        return;
      }

      // Simple or links widget, load up the $options.
      if ($field['type'] == 'taxonomy_term_reference') {
        $vocabulary_name = $field['settings']['allowed_values'][0]['vocabulary'];
        // Only show hierarchy depth indicators for select and multi-select.
        $show_depth = drupal_substr($requested_widget, -6) == 'select';
        _global_filter_add_terms($options, $vocabulary_name, $show_depth);
      }
      elseif (!empty($field['settings']['allowed_values'])) {
        foreach (list_allowed_values($field) as $value => $label) {
          $options[$value] = $label;
        }
      }
    }
  }

  global_filter_debug(t('Global Filter @name uses %widget widget', array(
    '@name' => $name, '%widget' => $requested_widget)));

  $form_state['global_filters'][$filter_key]['widget'] = $requested_widget;

  switch ($requested_widget) {
    case 'links':
      global_filter_create_links_widget($filter_key, $options, $form, $form_state);
      break;

    case 'range':
      global_filter_create_range_widget($filter_key, $form, $form_state);
      break;

    case 'proximity':
      global_filter_create_proximity_widget($filter_key, $form, $form_state);
      break;

    default:
      global_filter_create_simple_widget($filter_key, $options, $form, $form_state);
  }

  if (!empty($widget_label) && $widget_label != '<none>') {
    $form[$name]['#title'] = check_plain($widget_label);
  }
}

/**
 * Cast widget in the mould of the widget configured for the supplied's field.
 *
 * @param string $option_all_text
 *   Currently not used. See global_filter_options_none().
 * @param object $field
 *   the field
 * @param array $instance
 *   the instance
 * @param array $form
 *   the form
 * @param array $form_state
 *   the form state
 */
function global_filter_create_field_instance_widget($option_all_text, $field, $instance, &$form, &$form_state) {

  if (!isset($form['#parents'])) {
    // Must be set for most widgets before creation.
    $form['#parents'] = array();
  }
  // Add some context to the widget. This allows us for instance to make sure
  // that the Date widget doesn't impose its defaults.
  $instance['widget']['is_global_filter'] = TRUE;

  // $items is used to set the default value on the widget.
  if ($instance['widget']['module'] == 'date') {
    $items = global_filter_set_instance_date_widget_value($field, $instance, $form_state);
  }
  else {
    // Any widget other than the Date widgets.
    $session_value = global_filter_get_session_value($field['field_name']);
    $items = global_filter_set_instance_widget_value($session_value, $field, $form_state);
  }

  // Uncomment next two lines to obtain control over the option list, with the
  // exception of the first 'none' option. See global_filter_options_list().
  // $field['real_module'] = $field['module'];
  // $field['module'] = 'global_filter';
  // Trying to add/suppress 'All' option. The statement below doesn't have the
  // desired effect.
  // $instance['required'] = ($option_all_text == '<none>');
  $lang = $form_state['language'];
  // Note last argument, $delta=0, in this call. We don't want multiple
  // occurrences of a widget, except for Date, which is handled above.
  $form += field_default_form($instance['entity_type'], NULL, $field, $instance, $lang, $items, $form, $form_state, 0);
}

/**
 * Complete the form.
 *
 * @param array $form
 *   the form to complete
 * @param int $block_number
 *   the block number
 */
function global_filter_finalise_form(&$form, $block_number) {
  // Preserve filter order as selected on the block configuration page.
  $num_filters = 0;
  foreach ($form as $key => &$filter_element) {
    if (drupal_substr($key, 0, 1) != '#') {
      $filter_element['#weight'] = ++$num_filters;
    }
  }
  $submit_required = $button_required = FALSE;
  foreach (global_filter_get_filters_for_block($block_number) as $key => $filter) {

    $name = $filter['name'];
    $filter_delta = GLOBAL_FILTER_FILTER_KEY_PREFIX . $key;

    // We're adding a class rather than an id as it needs to be attached to all
    // of the <input>'s of each sequence of check boxes or radio buttons.
    $form[$name]['#attributes']['class'][] = drupal_html_class("$filter_delta-$name");

    $confirm_question = global_filter_get_parameter($key, 'confirm_question');
    $autosubmit = global_filter_get_parameter($key, 'set_on_select');

    if ($filter['widget'] != 'links') {
      $submit_required = TRUE;
      if (!$autosubmit) {
        $button_required = TRUE;
      }
    }

    if ($confirm_question || $autosubmit) {
      drupal_add_js(array(
        $filter_delta => array(
          drupal_html_class("$filter_delta-$name"),
          $confirm_question,
          $autosubmit,
        ),
      ), 'setting');
      $form[$name]['#attached']['js'][] = drupal_get_path('module', 'global_filter') . '/js/global_filter_all.js';
    }
  }
  if ($submit_required) {
    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Set'),
      '#submit' => array('global_filter_set_form_on_session'),
      '#attributes' => array(
        'class' => array(
          drupal_html_class('global-filter-set-' . ($num_filters > 1 ? 'all' : $filter['widget'])),
        ),
      ),
      '#weight' => ++$num_filters,
    );
    if (!$button_required) {
      // Suppress the 'Set' submit button defined above.
      $form['submit']['#attributes']['style'][] = 'display:none';
    }
  }
}

/**
 * Implements hook_field_widget_form_alter().
 *
 * Called from field_default_form().
 */
function global_filter_field_widget_form_alter(&$element, &$form_state, $context) {

  if (!isset($context['instance']['widget']['is_global_filter'])) {
    return;
  }
  switch ($context['instance']['widget']['module']) {

    case 'date':
      global_filter_field_date_widget_form_alter($element, $form_state, $context);
      break;

    case 'slide_with_style':
      global_filter_field_slider_widget_form_alter($element, $form_state, $context);
      break;
  }
}

/**
 * Add the view results. In particular load up the selection options.
 */
function global_filter_add_view_results(&$options, $view_id) {
  $view = views_get_view($view_id);
  if (!is_object($view)) {
    drupal_set_message(t('Global Filter: could not find view: %view.', array(
      '%view' => empty($view_id) ? t('no name specified') : $view_id)), 'error');
    return FALSE;
  }
  $view->init_display();
  $view->pre_execute();
  $view->execute();
  // Pick the first non-id field of each returned row as the next value for
  // the filter.
  foreach ($view->result as $row) {
    $row_as_array = (array) $row;
    foreach ($row_as_array as $fid => $value) {
      if ($fid != $view->base_field) {
        // E.g. 'nid', 'uid', 'cid', 'tid', 'aid' {accesslog}.
        // At this point can we fetch the translated value?
        // The patch from [#2110573], #3 does not always work so wasn't applied.
        break;
      }
    }
    $key = isset($row_as_array[$view->base_field]) ? $row_as_array[$view->base_field] : NULL;
    $options[empty($key) ? $value : $key] = $value;
  }
}

/**
 * Get field instances.
 */
function global_filter_get_field_instances($field_name) {
  $instances = array();
  foreach (field_info_instances() as $type_bundles) {
    // Example: $entity_type == 'file', 'node', 'taxonomy_term' or 'user'
    // $bundle == 'article' or 'user'
    foreach ($type_bundles as $bundle_instances) {
      // Fields of node, user.
      foreach ($bundle_instances as $f_name => $instance) {
        if ($f_name == $field_name) {
          $instances[] = $instance;
        }
      }
    }
  }
  // If the field has instances with different widgets, prefer 'node' over
  // 'taxonomy_term' or 'user' and with 'node' prefer field names that come
  // earlier in the alphabet.
  return array_reverse($instances);
}

/**
 * Set widget instale value.
 */
function global_filter_set_instance_widget_value($session_value, $field, $form_state) {
  $name = $field['field_name'];
  $lang = $form_state['language'];

  $form_input = isset($form_state['input'][$name][$lang]) ? $form_state['input'][$name][$lang] : NULL;
  $form_values = isset($form_state['values'][$name][$lang]) ? $form_state['values'][$name][$lang] : NULL;

  if (is_array($form_input)) {
    $value = $form_input;
  }
  if (is_array($form_values)) {
    // Usually this means an autocomplete taxonomy, retrieve the term id.
    $form_values = reset($form_values);
    $value = empty($form_values['tid']) ? $form_values['name'] : $form_values['tid'];
  }

  if (empty($value)) {
    $value = $session_value;
  }
  // $items is used to set defaults. Must use this format (multi-valued):
  // $items[0][$key] = 4
  // $items[1][$key] = 23
  // where $key tends to equal 'value' or 'tid'
  $items = array();
  $key = key($field['columns']);
  if (!empty($value) && is_array($value)) {
    foreach (global_filter_array_flatten($value) as $value) {
      $items[] = array($key => $value);
    }
  }
  else {
    $items[0][$key] = $value;
  }
  // If nothing set, return something that represents 'All'. Otherwise the
  // field widget will set the instance default.
  return empty($items) ? array(0 => array()) : $items;
}

/**
 * Stashes the selected global filter value(s) in the user's session.
 *
 * @param array $form
 *   the form
 * @param array $form_state
 *   the form state
 */
function global_filter_set_form_on_session($form, &$form_state) {

  foreach ($form_state['global_filters'] as $filter_key => $info) {

    $name = $info['name'];
    $widget = $info['widget'];

    if (strpos($widget, 'date') === 0) {
      // If successful this function returns a date range in the format
      // YYYY-MM-DD--YYYY-MM-DD, which is what Views' contextual filters need.
      $form_value = global_filter_extract_date_range($form_state, $filter_key);
    }
    elseif ($widget == 'range') {
      // Extract from 2 form fields an alphabetical or numeric range string, eg.
      // 'a--kz' or '1.5--3.5'
      // Only meaningful when used with the contextual_range_filter module.
      $form_value = global_filter_extract_alphanumeric_range($form_state, $name);
    }
    elseif ($widget == 'proximity') {
      $form_value = global_filter_extract_proximity($form_state);
      // Returns object with 'location', 'distance', 'latitude' and 'longitude'.
    }
    elseif (isset($form_state['values'][$name])) {
      // The rest of the widgets, both single and multi-choice (i.e array).
      $lang = isset($form_state['language']) ? $form_state['language'] : LANGUAGE_NONE;
      $form_value = global_filter_extract_values($form_state['values'][$name], $lang);
    }
    else {
      continue;
    }
    global_filter_set_on_session($name, $form_value);
  }
  // If rebuild==FALSE there will be an unnecessary drupal_goto(), so need to
  // force it not to redirect.
  // @see drupal_redirect_form()
  $form_state['rebuild'] = FALSE;
  $form_state['no_redirect'] = TRUE;
}

/**
 * Extract values entered on the form.
 *
 * @param array $form_values
 *   normally form_state['values']['global_filter_#']
 * @param string $language
 *   language code
 *
 * @return mixed
 *   single value or array of values (multi-select)
 */
function global_filter_extract_values($form_values, $language = NULL) {
  if (!is_array($form_values)) {
    return $form_values;
  }
  if (!isset($language)) {
    // If present, expect language to be first element of $form_values
    $language = array_keys($form_values);
    $language = reset($language);
    if (is_numeric($language)) {
      return array_values($form_values);
    }
  }
  // $language level won't be there for simple widgets.
  if (empty($form_values[$language])) {
    return array_values($form_values);
  }
  $values = array();
  foreach ($form_values[$language] as $v) {
    if (is_array($v)) {
      $keys = array_keys($v);
      $values[] = array_keys($keys) === $keys ? reset($v) : $v;
    }
    else {
      $values[] = $v;
    }
  }
  return $values;
}

/**
 * Add terms to global filter.
 */
function _global_filter_add_terms(&$options, $vocabulary_machine_name, $show_depth = TRUE) {
  if (!module_exists('taxonomy')) {
    drupal_set_message(t('Global Filter: using vocabulary %vocabulary, but Taxonomy module is not enabled.', array('%vocabulary' => $vocabulary_machine_name)), 'error');
    return;
  }
  if (!empty($vocabulary_machine_name)) {
    foreach (taxonomy_get_vocabularies() as $vid => $vocabulary) {
      $found = ($vocabulary->machine_name == $vocabulary_machine_name);
      if ($found) {
        break;
      }
    }
  }
  if (empty($found)) {
    drupal_set_message(t('Global Filter: the vocabulary %vocabulary does not exist.', array('%vocabulary' => $vocabulary_machine_name)), 'error');
  }
  else {
    foreach (taxonomy_get_tree($vid) as $term) {
      $term_name = module_exists('i18n_taxonomy') ? i18n_taxonomy_term_name($term) : $term->name;
      // If $show_depth is set, we follow core's way and append one hyphen for
      // each hierarchy level.
      $options[$term->tid] = $show_depth ? (str_repeat('-', $term->depth) . $term_name) : $term_name;
    }
  }
}

/**
 * Quick and dirty way to flatten an array.
 *
 * @param array $array
 *   the array to enflattenate
 *
 * @return array
 *   the flattened array
 */
function global_filter_array_flatten($array) {
  foreach ($array as $key => $value) {
    $array[$key] = (array) $value;
  }
  return call_user_func_array('array_merge', $array);
}

/**
 * Implements hook_theme_registry_alter().
 *
 * Override theme_options_none (options.module) to make the '- None -' text
 * configurable for buttons and select lists, but only for Global Filter
 * widgets, see function global_filter_options_none() below.
 */
function global_filter_theme_registry_alter(&$theme_registry) {
  $theme_registry['options_none']['function'] = 'global_filter_options_none';
  $theme_registry['options_none']['theme_path'] = drupal_get_path('module', 'global_filter');
}

/**
 * Override of the theme_options_none() function.
 *
 * In addition to the regular options as returned by hook_options_list, the
 * Options module will always prepend a 'none' for non-required fields, whether
 * appearing as a single or multiple-select. We can't intercept this process.
 * We could make the select mandatory and then prepend a 'none' option
 * ourselves, but then we end up with a red asterisk for a select that isn't
 * really mandatory...
 *
 * Until I can find a way to determine if this is a global filter context,
 * I'll switch this feature off for global filters driven by field widgets.
 */
function global_filter_options_none($variables) {
  if (!empty($variables['global_filter_context'])) {
    // See comment above.
    $filter_key = global_filter_key_by_name($variables['instance']['field_name']);
    $option_all_text = global_filter_get_parameter($filter_key, 'option_all_text');
    if (!empty($option_all_text)) {
      return $option_all_text == t('<none>') ? '' : check_plain($option_all_text);
    }
  }
  // Not used in a global filter context or no 'All' text specified, so return
  // the widget default.
  // @todo: change to theme('options_none', $variables)
  return theme_options_none($variables);
}

/**
 * List filter options.
 */
function global_filter_options_list($field, $instance) {
  $options = (array) module_invoke($field['real_module'], 'options_list', $field, $instance);
  // ...
  return $options;
}
