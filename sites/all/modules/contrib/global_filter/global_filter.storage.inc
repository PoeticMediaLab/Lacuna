<?php
/**
 * @file
 * global_filter.storage.inc
 *
 * Implements via Session Cache API several ways to store the user's current
 * global filter settings. For example:
 * o in a cookie, i.e. on the user's computer
 * o on the database, i.e. on the server (disk)
 * o on the HTTP session, i.e. in server memory (RAM) aka $_SESSION
 */

define('GLOBAL_FILTER_DB_VAR', 'global_filters');
// Legacy, can't change.
define('GLOBAL_FILTER_BLOCK_ID_PREFIX', 'global_filter_');
define('GLOBAL_FILTER_FILTER_KEY_PREFIX', 'global_filter_');

/**
 * Return value of a module configuration parameter, as set via the admin UI.
 *
 * Note that there is no global_filter_set_module_parameter() function. All
 * module parameters are set via the UI on admin/config/content/global_filter.
 *
 * @param string $name
 *   name of the parameter on the admin config page.
 * @param mixed $default
 *   value to return if the parameter hasn't been set yet
 *
 * @return mixed
 *   value, maybe a number, string or array.
 */
function global_filter_get_module_parameter($name, $default = NULL) {
  return variable_get('global_filter_' . $name, $default);
}

/**
 * Returns parameter value of the specified filter or all parameters if omitted.
 *
 * @param int $filter_key
 *   positive integer or NULL to retrieve all
 * @param string $name
 *   name of the filter parameter to retrieve, omit for all
 *
 * @return mixed
 *   a single value, array or two-dimensional array
 */
function global_filter_get_parameter($filter_key, $name = NULL) {
  // Take advantage of the cache inside global_filter_set_parameter() to
  // fetch all parameters. Then return the one requested or all if $name==null
  $parameters = global_filter_set_parameter(NULL, NULL, NULL);
  if (empty($filter_key) && empty($name)) {
    return $parameters;
  }
  if (empty($name)) {
    return isset($parameters[$filter_key]) ? $parameters[$filter_key] : NULL;
  }
  return isset($parameters[$filter_key][$name]) ? $parameters[$filter_key][$name] : NULL;
}

/**
 * Set a name/value pair on the filter by the key $key.
 *
 * Special cases:
 * o global_filter_set_parameter(NULL, NULL, NULL) simply returns
 *   all filter parameters keyed by filter key first and parameter name second.
 * o global_filter_set_parameter($filter_key, NULL, NULL) deletes the filter
 *
 * @param int $key
 *   a positive integer denoting the filter key
 * @param string $name
 *   name of parameter to set, use NULL to delete the filter
 * @param mixed $value
 *   the value
 * @param bool $reset
 *   whether to reset the cache
 *
 * @return array
 *   array of parameters
 */
function global_filter_set_parameter($key, $name, $value, $reset = FALSE) {
  // For multiple get's during the same request cache the values. The cache
  // lives in this function as it needs to be updated with every set operation.
  $parameters = &drupal_static(__FUNCTION__, NULL, $reset);

  if (!isset($parameters)) {
    $parameters = variable_get(GLOBAL_FILTER_DB_VAR, array());
    $legacy_parameters_set = variable_get('global_filter_legacy_parameters_set', FALSE);
    for ($j = 1; $j <= GLOBAL_FILTER_MAX_NUM_FILTERS; $j++) {

      if (empty($parameters[$j]['name'])) {
        if (!$legacy_parameters_set) {
          if (_global_filter_load_legacy_parameters($j, $parameters[$j])) {
            drupal_set_message(t('Global Filter settings from 7.x-1.8 version or older were successfully loaded and saved in the new format. Filters in the old format were kept also. If you want to revert to the older version of this module AND keep the old settings do NOT uninstall this module. Just copy the old version over the top of this new one.'), 'warning', FALSE);
            // Now that parameters have been set, we'll never get here again...
          }
          variable_set('global_filter_legacy_parameters_set', TRUE);
        }
        else {
          unset($parameters[$j]);
          continue;
        }
      }
      if (empty($parameters[$j]['block'])) {
        $parameters[$j]['block'] = GLOBAL_FILTER_BLOCK_ID_PREFIX . $j;
      }
      // Set remaining parameters to empty string to avoid NULLs.
      foreach (_global_filter_get_all_parameter_names() as $parameter_name) {
        if (!isset($parameters[$j][$parameter_name])) {
          $parameters[$j][$parameter_name] = '';
        }
      }
    }
  }
  if (isset($key)) {
    // Update cache and its db backup.
    if (isset($name)) {
      $parameters[$key][$name] = $value;
    }
    else {
      // Delete this filter.
      unset($parameters[$key]);
    }
  }
  if (isset($key) || (isset($legacy_parameters_set) && $legacy_parameters_set === FALSE)) {
    variable_set(GLOBAL_FILTER_DB_VAR, $parameters);
  }
  return $parameters;
}

/**
 * Load legacy parameters.
 */
function _global_filter_load_legacy_parameters($j, &$parametersj) {
  // Check for legacy data.
  $name = variable_get(GLOBAL_FILTER_BLOCK_ID_PREFIX . $j);
  if (empty($name)) {
    return FALSE;
  }
  $parametersj['name'] = $name;
  foreach (_global_filter_get_all_parameter_names() as $parameter_name) {
    if (!isset($parametersj[$parameter_name])) {
      $parametersj[$parameter_name] = variable_get(GLOBAL_FILTER_BLOCK_ID_PREFIX . $j . '_' . $parameter_name);
    }
  }
  if (!isset($parametersj['uses_view'])) {
    $parametersj['uses_view'] = (strpos($name, 'view_') === 0);
    if ($parametersj['uses_view']) {
      $parametersj['view'] = $name;
    }
    else {
      $parametersj['field'] = $name;
    }
  }
  return TRUE;
}

/**
 * Get a session value.
 */
function global_filter_get_session_value($name = NULL) {

  $filters = session_cache_get('global_filter');
  if (empty($filters) || !is_array($filters)) {
    // This is different from '', which means "all".
    return NULL;
  }
  return empty($name) ? $filters : (isset($filters[$name]) ? $filters[$name] : '');
}

/**
 * Sets the filter of the supplied name to the supplied value.
 *
 * @param string $name
 *   eg 'field_country', must not be empty
 * @param mixed $value
 *   to be set to filter of $name
 *
 * @return bool
 *   TRUE if $value was set, FALSE if it wasn't
 */
function global_filter_set_on_session($name, $value) {

  // Provide hook_global_filter_value_alter(), so $value can be altered by
  // other modules.
  drupal_alter('global_filter_value', $name, $value);

  if (empty($name)) {
    drupal_set_message(t('Global Filter: filter name empty. Cannot set value.'), 'warning');
    return FALSE;
  }
  if (is_array($value)) {
    // For e.g., hierarchical select.
    $value = global_filter_array_flatten($value);
    if (empty($value)) {
      $value = '';
    }
  }
  // Gets and caches all filters.
  $prev_value = global_filter_get_session_value($name);
  if ($prev_value == $value) {
    global_filter_debug(t('Global Filter @name: no change in value. No need to set.', array('@name' => $name)));
    return FALSE;
  }

  // May return '' or NULL.
  $filters = global_filter_get_session_value();
  if (empty($filters)) {
    $filters = array();
  }
  // Update the selected filter with the new value.
  $filters[$name] = $value;

  // For Context Session module, http://drupal.org/project/context_session
  // @todo refactor into its own ugly function.
  if (module_exists('context_session') && !empty($_SESSION)) {
    // context_session does not support session_cache, so use $_SESSION.
    // Note that context_session only offers boolean support: it sets a
    // context based on the fact whether a key is present or not. So we have
    // to fake name=value pairs. We start by clearing out old values.
    foreach ($_SESSION as $key => $v) {
      if (strpos($key, "global_filter:$name=") === 0) {
        unset($_SESSION[$key]);
      }
    }
    // Now set the new value. Support the AND operator. ORs are achieved by
    // the user adding multiple session conditions.
    $val = is_array($value) ? implode(',', array_filter($value)) : $value;
    $_SESSION["global_filter:$name=$val"] = TRUE;
    // If in the future Context Session accepts name|value pairs we can do this:
    // $_SESSION["global_filter:$name"] = $val;
  }

  $prev_value = !isset($prev_value) || $prev_value == '' ? t('all') : (is_array($prev_value) ? implode('+', $prev_value) : print_r($prev_value, TRUE));
  $value = !isset($value) || $value == '' ? t('all') : (is_array($value) ? implode('+', $value) : print_r($value, TRUE));
  global_filter_debug(t('Global Filter @name: changing from %prev_value to %value', array(
    '@name' => $name,
    '%prev_value' => $prev_value,
    '%value' => $value,
  )));

  if ($name != 'view_autocycle' && global_filter_get_module_parameter('mutex_mode', FALSE)) {
    global_filter_debug(t('Global Filter mutex mode is on, so setting other filters back to their global defaults...'));

    foreach (global_filter_get_parameter(NULL) as $filter) {
      $nm = $filter['name'];
      if ($nm && $nm != $name && $nm != 'view_autocycle') {
        $filters[$nm] = $val = global_filter_get_global_default($nm);
        $val = is_array($val) ? implode('+', array_filter($val)) : $val;
        if (module_exists('context_var')) {
          variable_set($nm, $val);
        }
        global_filter_debug(t('Global Filter %name: mutex reset to global default: "%value"', array(
          '%name' => $nm,
          '%value' => print_r($val, TRUE),
        )));
      }
    }
  }
  // Set all updated filters.
  session_cache_set('global_filter', $filters);

  // Invoke the Rules event: "A Views Global Filter has been set".
  if (module_exists('rules')) {
    rules_invoke_event('global_filter_set_filter_done', $name, $value);
  }

  return TRUE;
}

/**
 * Return an array of filter parameter names.
 *
 * @return array
 *   array of strings
 */
function _global_filter_get_all_parameter_names() {
  return array(
    'uses_view', 'view', 'field', 'widget', 'label', 'option_all_text',
    'convert_to_range', 'confirm_question', 'set_on_select',
    'global_php_default', 'global_field_or_view_default',
  );
}
