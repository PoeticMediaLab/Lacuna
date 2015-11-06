<?php
/**
 * @file
 * global_filter.block.inc
 *
 * Block hooks and pieces for global_filter.module blocks.
 *
 * Each global filter block may have one or more global filters in it.
 */

/**
 * Implements hook_block_info().
 */
function global_filter_block_info() {

  $num_filter_blocks = global_filter_get_module_parameter('num_filters', GLOBAL_FILTER_DEF_NUM_FILTERS);

  for ($block_number = 1; $block_number <= $num_filter_blocks; $block_number++) {
    $filter_names = array();
    foreach ($filters = global_filter_get_filters_for_block($block_number) as $filter) {
      if (!empty($filter['name'])) {
        $filter_names[] = $filter['name'];
      }
    }
    if (empty($filter_names)) {
      $info = t('Global filter block @i (not configured)', array('@i' => $block_number < 10 ? " $block_number" : $block_number));
    }
    else {
      $info = format_plural(count($filter_names), 'Global filter @filters', 'Global filters: @filters', array(
        '@filters' => implode(' + ', $filter_names)));
    }
    $blocks[GLOBAL_FILTER_BLOCK_ID_PREFIX . $block_number] = array(
      'info' => $info,
      'cache' => DRUPAL_NO_CACHE,
    );
  }
  // For the case that the number of blocks is reduced, remove the filters as
  // without a block they have no home.
  while ($block_number <= GLOBAL_FILTER_MAX_NUM_FILTERS) {
    foreach (global_filter_get_filters_for_block($block_number) as $key => $filter) {
      if (!empty($filter['name'])) {
        global_filter_remove_default_filter_from_views($filter['name']);
      }
      // Delete the filter.
      global_filter_set_parameter($key, NULL, NULL);
    }
    $block_number++;
  }
  return $blocks;
}

/**
 * Implements hook_block_configure().
 *
 * Note that this hook cannot easily be used with dynamic forms adding
 * additional fields at the press of a button, because form_state is not passed
 * as its argument. See drupal.org/node/690828.
 * Therefore the actions of adding or removing a fieldset (filter) is not easily
 * communicated back to this function.
 *
 * $param string $delta
 *   Example: 'global_filter_2'
 */
function global_filter_block_configure($delta) {

  // Container for the table, its id is used in the AJAX callback.
  $form['all-filters'] = array(
    '#title' => t('Global filters in this block'),
    '#type' => 'fieldset',
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
    '#prefix' => '<div id="all-filters">',
    '#suffix' => '</div>',
  );
  $block_number = empty($delta) ? 1 : _global_filter_number($delta);
  $filter_parameters = global_filter_get_parameter(NULL);
  // Generate forms for existing filters.
  $fieldset = 0;
  $keys = array();
  for ($key = 1; $key <= GLOBAL_FILTER_MAX_NUM_FILTERS; $key++) {
    if (empty($filter_parameters[$key])) {
      if (!isset($first_free_key)) {
        $first_free_key = $key;
      }
    }
    elseif (_global_filter_number($filter_parameters[$key]['block']) == $block_number) {
      $form['all-filters'][$key] = _global_filter_configure_form($block_number, $key, $fieldset);
      $keys[] = $key;
      $fieldset++;
    }
  }
  // Generate empty form for optional extra filter.
  if (isset($first_free_key)) {
    $form['all-filters'][$first_free_key] = _global_filter_configure_form($block_number, $first_free_key, $fieldset);
    $keys[] = $first_free_key;
  }
  return $form;
}

/**
 * Generates the filter configuration form for filters in a block.
 *
 * @param int $block_number
 *   the block number
 * @param int $filter_key
 *   the filter key
 * @param bool $expand_fieldset
 *   whetor to expand or collapse the fieldset holding the form
 *
 * @return array
 *   the $form array
 */
function _global_filter_configure_form($block_number, $filter_key, $expand_fieldset) {

  $num_filters = count(global_filter_get_filters_for_block($block_number));
  $name = ($num_filters == 0) ? '' : global_filter_get_parameter($filter_key, 'name');

  $form = array();
  $delta = GLOBAL_FILTER_FILTER_KEY_PREFIX . $filter_key;
  $form[$delta] = array(
    '#title' => isset($name) ? t('Settings for global filter %name', array('%name' => $name)) : t('Optional additional global filter (currently not configured)'),
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => $expand_fieldset,
  );

  $form[$delta]['driver'] = array(
    '#title' => t('Filter driver'),
    '#type' => 'fieldset',
    '#collapsible' => FALSE,
    '#attributes' => array('id' => drupal_html_class('global-filter-driver-' . $filter_key)),
  );

  $radios_name = $delta . '_uses_view';
  $form[$delta]['driver'][$radios_name] = array(
    '#title' => t('Select whether this global filter is to be populated by a field or by a view'),
    '#type' => 'radios',
    '#options' => array(
      0 => module_exists('location') ? t('field, node property, location proximity or search term(s)') : t('field, node property or search term(s)'),
      1 => t('view'),
    ),
    '#default_value' => (int) global_filter_get_parameter($filter_key, 'uses_view'),
  );
  // Same name for both buttons.
  $selector_radios = ':input[name="' . $radios_name . '"]';

  $note = t('If you have enabled the <a target="url_project" href="@url_project">Context Session</a> module, then you may use "global_filter:%machine_name=VALUE" as the session name to switch contexts on.', array(
    '@url_project' => url('http://drupal.org/project/context_session'),
    '%machine_name' => $name,
  ));

  $field_options = global_filter_get_usable_fields();
  $form[$delta]['driver'][$delta . '_field'] = array(
    '#title' => t('Choose the field to be used as a global filter'),
    '#type' => 'select',
    '#default_value' => global_filter_get_parameter($filter_key, 'field'),
    '#options' => $field_options,
    '#description' => t('The field or node property employed to populate the widget used to filter one or more views.') . ' ' . $note,
    '#states' => array('visible' => array($selector_radios => array('value' => 0))),
  );

  $view_options = array_merge(
    array('' => t('- None -')),
    global_filter_get_view_names()
  );
  asort($view_options);
  $form[$delta]['driver'][$delta . '_view'] = array(
    '#title' => t('Choose the view to be used as a global filter'),
    '#type' => 'select',
    '#default_value' => global_filter_get_parameter($filter_key, 'view'),
    '#options' => $view_options,
    '#description' => t('The view employed to populate the widget used to filter one or more other views.') . ' ' . $note,
    '#states' => array('visible' => array($selector_radios => array('value' => 1))),
  );

  $widget_default = global_filter_get_parameter($filter_key, 'widget');

  if (global_filter_get_parameter($filter_key, 'uses_view')) {
    if (empty($widget_default) || strpos($widget_default, 'default_') === 0) {
      $widget_default = 'default';
    }
    $widget_options = array('default' => 'Default');
  }
  else {
    $instances = global_filter_get_field_instances($name);
    if (empty($instances)) {
      $widget_options = array('default' => t('Default, i.e. inherit from field, if field-driven'));
    }
    else {
      foreach ($instances as $instance) {
        $widget_type = $instance['widget']['type'];
        $widget_options['default_' . $widget_type] = t('Inherit %widget widget from field @label (on %bundle)', array(
          '%widget' => $widget_type, '@label' => $instance['label'], '%bundle' => $instance['bundle'],
        ));
      }
      if (empty($widget_default) || $widget_default == 'default') {
        // If not set inherit widget from last field instance.
        $widget_default = 'default_' . $widget_type;
      }
    }
  }
  $range_option = module_exists('contextual_range_filter') ? t('Range') : t('Range (requires <a href="!url">Contextual Range Filter</a>)', array(
    '!url' => url('http://drupal.org/project/contextual_range_filter'),
  ));
  $widget_options += array(
    'select' => t('Single choice drop-down'),
    'radios' => t('Single choice radio buttons'),
    'multiselect' => t('Multi choice select box'),
    'checkboxes' => t('Multi choice check boxes'),
    'links' => t('List of hyperlinks'),
    'textfield' => t('Text field'),
    'range' => $range_option,
    'proximity' => t('Proximity (reference location and distance)'),
  );
  $form[$delta]['widget'] = array(
    '#title' => 'Widget to render the global filter',
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#description' => t('Not all options apply to all cases, e.g., when the field is natively rendered as a textfield or date picker widget.'),
  );
  $form[$delta]['widget'][$delta . '_widget'] = array(
    '#title' => t('Widget'),
    '#type' => 'radios',
    '#default_value' => $widget_default,
    '#options' => $widget_options,
    '#description' => t("If you tick one of the multi choice widgets, make sure to tick the <strong>Allow multiple values</strong> box in the <strong>More</strong> section of the view's contextual filter. <br/>Note: Views does not support multi choice widgets that have non-numeric keys."),
  );

  $description = t('Should be ticked for inherited slider widgets of type float. Optional for slider widgets of type integer and list. Has no effect on any other widget.');
  $note1 = module_exists('slide_with_style') ? '' : t('Requires <a href="!url">Slide with Style</a> or similar.', array(
    '!url' => url('http://drupal.org/project/select_with_style'))) . ' ';
  $note2 = module_exists('contextual_range_filter') ? '' : t('Requires <a href="!url">Contextual Range Filter</a>.', array(
    '!url' => url('http://drupal.org/project/contextual_range_filter'))
  );
  $form[$delta]['widget'][$delta . '_convert_to_range'] = array(
    '#title' => t('Convert slider to range slider'),
    '#type' => 'checkbox',
    '#default_value' => global_filter_get_parameter($filter_key, 'convert_to_range'),
    '#description' => $description . '<br/>' . $note1 . $note2,
  );
  $form[$delta]['widget'][$delta . '_label'] = array(
    '#title' => t('Widget label override'),
    '#type' => 'textfield',
    '#default_value' => global_filter_get_parameter($filter_key, 'label'),
    '#description' => t("If omitted the widget's native label will be used, which may be blank. Use <em>&ltnone&gt;</em> if you want to suppress the label."),
  );
  $option_all_text = global_filter_get_parameter($filter_key, 'option_all_text');
  $form[$delta]['widget'][$delta . '_option_all_text'] = array(
    '#title' => t('Text to appear as the "all" option, where applicable'),
    '#type' => 'textfield',
    '#default_value' => $option_all_text,
    '#description' => t('Does NOT apply to inherited field widgets. Inherited field widgets always use core defaults. Remaining widgets default to <strong>@all</strong>, if left blank.<br/>Enter <em>&lt;none&gt;</em> to omit the "all" option from the widget. <em>&lt;none&gt;</em> is recommended for multi choice widgets.',
      array('@all' => GLOBAL_FILTER_DEF_OPTION_ALL_TEXT)),
  );
  $form[$delta]['widget'][$delta . '_confirm_question'] = array(
    '#title' => t('Prompt the user to confirm their selection'),
    '#type' => 'textfield',
    '#size' => 120,
    '#default_value' => global_filter_get_parameter($filter_key, 'confirm_question'),
    '#description' => t('The text you enter here will pop up as an alert box with Cancel and OK buttons, for example: <em>Are you sure you want to change this filter ?</em> If you leave this field blank, there will be no prompt.'),
  );
  $form[$delta]['widget'][$delta . '_set_on_select'] = array(
    '#title' => t('Autosubmit: invoke widget immediately upon select'),
    '#type' => 'checkbox',
    '#default_value' => global_filter_get_parameter($filter_key, 'set_on_select'),
    '#description' => t('When ticked this does away with the Set button next to the widget. May not work on certain inherited widgets. When using the "List of hyperlinks" this option is ticked intrinsically.'),
  );
  $form[$delta]['global_defaults'] = array(
    '#title' => 'Global filter defaults',
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
  );
  $field_or_view_options = array('' => ' - ' . t('No default ("all")') . ' - ');
  if (global_filter_get_parameter($filter_key, 'uses_view')) {
    // Execute View to present possible default values.
    $view_name = drupal_substr(global_filter_get_parameter($filter_key, 'view'), 5);
    global_filter_add_view_results($field_or_view_options, $view_name);
  }
  else {
    // Retrieve field values.
    $field_name = global_filter_get_parameter($filter_key, 'field');
    $field = field_info_field($field_name);
    if ($field['type'] == 'taxonomy_term_reference') {
      $vocabulary_name = $field['settings']['allowed_values'][0]['vocabulary'];
      _global_filter_add_terms($field_or_view_options, $vocabulary_name);
    }
    elseif (!empty($field['settings']['allowed_values'])) {
      foreach (list_allowed_values($field) as $key => $value) {
        $field_or_view_options[$key] = $value;
      }
    }
    else {
      // Handle Location:Country.
      // Final case: free text field?
    }
  }
  $global_default = global_filter_get_parameter($filter_key, 'global_field_or_view_default');
  if (empty($global_default)) {
    $keys = array_keys($field_or_view_options);
    $first_option = next($keys);
    $global_default = $option_all_text == '<none>' ? $first_option : NULL;
  }
  $multi_choices = array('multiselect', 'checkboxes', 'default');
  $form[$delta]['global_defaults'][$delta . '_global_field_or_view_default'] = array(
    '#title' => t('Default value for the field or view selected above'),
    '#type' => 'select',
    '#multiple' => in_array(global_filter_get_parameter($filter_key, 'widget'), $multi_choices),
    '#options' => $field_or_view_options,
    '#size' => 1,
    '#description' => t('Optionally select default value(s) for the field or view above. These values will be active until the user selects another global filter value. If your widget does not have an "all" option, then you probably don\'t want to set "all" as the default.'),
    '#default_value' => $global_default,
  );

  $description = t("Enclose in PHP 'brackets'. Examples:<br/><code>&lt;?php return 'Beatles'; ?&gt;</code><br/><code>&lt;?php return '2013-01-01--2013-12-31'; ?&gt;</code> (date range, note the double hyphen)<br/>If the selected widget allows multiple choices, then return either an array or a string with choices delimited by plus signs.");
  if (!module_exists('php')) {
    $description .= t('<br/>Enable the core <strong>PHP filter</strong> module for this setting to take effect.');
  }
  $form[$delta]['global_defaults'][$delta . '_global_php_default'] = array(
    '#title' => t('Alternatively specify a default through PHP code'),
    '#type' => 'textarea',
    '#default_value' => global_filter_get_parameter($filter_key, 'global_php_default'),
    '#description' => $description,
  );
  return $form;
}

/**
 * Implements hook_block_view().
 *
 * $param $delta, index into the array $blocks defined in
 *   global_filter_block_info)(), e.g., 'global_filter_2'
 */
function global_filter_block_view($delta) {
  // In order to make sure that that the filter settings submitted via this
  // little block are received by the depending views before they're executed
  // this block may end up being requested twice: once in global_filter_init()
  // and once whenever core feels like it. Hence the caching.
  $blocks = &drupal_static(__FUNCTION__, array());

  if (empty($blocks[$delta])) {

    $usable_views = global_filter_get_view_names();
    $usable_fields = global_filter_get_usable_fields();

    $block_number = empty($delta) ? 1 : _global_filter_number($delta);

    // Set the block title, aka 'subject'.
    $blocks[$delta]['subject'] = '';
    foreach (global_filter_get_filters_for_block($block_number) as $filter) {
      $filter_name = $filter['name'];
      if ($filter['uses_view'] && isset($usable_views[$filter_name])) {
        $blocks[$delta]['subject'] .= drupal_substr($usable_views[$filter_name], 6);
      }
      elseif (isset($usable_fields[$filter_name])) {
        $label = $usable_fields[$filter_name];
        $pos_colon = strpos($label, ':');
        $pos_bracket = strrpos($label, '(');
        if ($pos_bracket) {
          $blocks[$delta]['subject'] .= drupal_substr($label, $pos_colon + 2, $pos_bracket > $pos_colon ? $pos_bracket - $pos_colon - 3 : NULL);
        }
        else {
          $blocks[$delta]['subject'] .= drupal_substr($label, $pos_colon ? $pos_colon + 2 : 0);
        }
      }
      $blocks[$delta]['subject'] .= ' ';
    }
    // With the block title set, now add all the filters for this block.
    $blocks[$delta]['content'] = drupal_get_form($delta);
  }
  return $blocks[$delta];
}

/**
 * Implements hook_block_save().
 *
 * Notes: $delta may be something like 'global_filter_2'.
 * $edit holds the contents of the block form
 */
function global_filter_block_save($delta, $edit = array()) {

  foreach (_global_filter_extract_filters_from_form($edit) as $key => $filter) {

    $old_name = global_filter_get_parameter($key, 'name');
    $new_name = $filter['uses_view'] ? $filter['view'] : $filter['field'];
    global_filter_set_parameter($key, 'name', $new_name);

    global_filter_set_parameter($key, 'block', empty($new_name) ? NULL : $delta);

    if (empty($old_name) || $old_name != $new_name) {
      if (!empty($old_name)) {
        global_filter_remove_default_filter_from_views($old_name);
      }
      if (!empty($new_name)) {
        drupal_set_message(t('As you changed the global filter driver to %new, please check that the <strong>Global Filter defaults</strong> are correct. If not, make a selection and press <em>Save block</em>.',
          array('%new' => $new_name)));
        $reload_page = TRUE;
      }
    }
    if ($filter['widget'] == 'links') {
      $filter['set_on_select'] = TRUE;
    }
    foreach ($filter as $parameter_name => $value) {
      global_filter_set_parameter($key, $parameter_name, empty($new_name) ? NULL : $value);
    }
  }
  if (isset($reload_page)) {
    drupal_goto($_GET['q']);
  }
}

/**
 * Extracts parameter values for all filters on the block when saved.
 *
 * @param array $form
 *   a one-dimensional array containg filter parameters with
 *   keys formatted like "global_filter_#_name"
 *
 * @return array
 *   2-dimenional array indexed by filter key and parameter name
 */
function _global_filter_extract_filters_from_form($form) {
  $filter_parameters = array();
  foreach ($form as $form_key => $value) {
    // Consider reg_split.
    if (strpos($form_key, GLOBAL_FILTER_FILTER_KEY_PREFIX) === 0) {
      $l = drupal_strlen(GLOBAL_FILTER_FILTER_KEY_PREFIX);
      $key = strstr(drupal_substr($form_key, $l), '_', TRUE);
      if (is_numeric($key)) {
        $parameter_name = drupal_substr($form_key, $l + strlen($key) + 1);
        $filter_parameters[$key][$parameter_name] = $value;
      }
    }
  }
  return $filter_parameters;
}

/**
 * Get a list of labels of fields of supplied type, or all fields if omitted.
 *
 * @param string $field_type
 *   e.g., 'text'; for all lists use 'list'.
 *
 * @return array
 *   array of labels indexed by field machine names
 */
function global_filter_get_field_labels($field_type = NULL) {
  $field_names = &drupal_static(__FUNCTION__, array());
  if (empty($field_names)) {
    $content_prefix = t('Content');
    $field_prefix = t('Field');
    foreach ($field_info_instances = field_info_instances() as $entity_type => $type_bundles) {
      foreach ($type_bundles as $key => $bundle_instances) {
        if ($entity_type == 'taxonomy_term') {
          // Two special pseudo-fields to cover all taxonomy terms.
          $field_names[GLOBAL_FILTER_VIEWS_TID] = $content_prefix . ': ' . t('Has taxonomy term ID');
          $field_names[GLOBAL_FILTER_VIEWS_TID_DEPTH] = $content_prefix . ': ' . t('Has taxonomy term ID with depth');
        }
        foreach ($bundle_instances as $field_name => $instance) {
          $field = field_info_field($field_name);
          if (empty($field_type) || $field_type == $field['type'] || ($field_type == 'list' && strpos($field['type'], 'list') === 0)) {
            $field_names[$field_name] = $field_prefix . ': ' . $instance['label'] . " ($field_name)";
          }
        }
      }
    }
  }
  return $field_names;
}

/**
 * Retunrs a list of all field filters, indexed by their machine_name.
 */
function global_filter_get_usable_fields() {
  $special_fields = array('' => t('- None -'));
  $special_fields[GLOBAL_FILTER_VIEWS_COUNTRY_FIELD] = t('Country name');
  if (module_exists('location')) {
    $special_fields[GLOBAL_FILTER_VIEWS_PROXIMITY_FIELD] = t('Location module: Proximity/Distance');
    // Note: for Geofield the associated real field needs to be selected.
  }
  $special_fields[GLOBAL_FILTER_VIEWS_SEARCH_TERMS_FIELD] = t('Search: Search terms');
  // As in Views.
  if (module_exists('search_api')) {
    $special_fields[GLOBAL_FILTER_VIEWS_SEARCH_API_FULLTEXT] = t('Search API: Fulltext Search');
  }

  $fields = array_merge(global_filter_get_node_properties(), global_filter_get_field_labels());
  asort($fields);
  return array_merge($special_fields, $fields);
}

/**
 * Return an array of names of the filters inside the block by the given id.
 *
 * @param int $block_number
 *   a positive integer: 1, 2, 3...
 *
 * @return array
 *   array of filter names
 */
function global_filter_get_filters_for_block($block_number) {
  $filter_parameters = global_filter_get_parameter(NULL);
  foreach ($filter_parameters as $key => $filter) {
    if (_global_filter_number($filter['block']) != $block_number) {
      unset($filter_parameters[$key]);
    }
  }
  return $filter_parameters;
}

/**
 * Extracts the number part from a global filter identification string.
 *
 * @param string $string
 * @return string
 */
function _global_filter_number($string) {
  $from_underscore = strrchr($string, '_');
  return $from_underscore ? drupal_substr($from_underscore, 1) : FALSE;
}