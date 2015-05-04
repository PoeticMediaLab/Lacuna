<?php
/**
 * @file
 * Contains the d3 style plugin.
 */

/**
 * TODO:
 *  - add library info alter to make "views_fields" an array by default so that we
 *    we don't have to check if it exists.
 *  - Add a default type as a string, and a default description so we don't have to check
 *    those in the UI form either.
 */

/**
 * Style plugin to render a d3 visualization
 *
 * @ingroup views_style_plugins
 */
class d3_views_plugin_style_d3 extends views_plugin_style {
  /**
   * Statically store all library info.
   *
   * @var array
   */
  protected $libraries = array();
 
  /**
   * Statically store the current visualization.
   *
   * @var array
   */
  protected $vis = array();

  /**
   * Local instance of D3ViewsLibraryInfoController
   *
   * @var D3ViewsLibraryInfoController
   */
  protected $controller;

  /**
   * Override views_object::construct().
   */
  function construct() {
    parent::construct();
  }

  function init(&$view, &$display, $options = NULL) {
    parent::init($view, $display, $options);
    $this->controller = d3_get_library_info_handler('views');
    $this->controller->mapping->setPlugin($this);
  }

  /**
   * Set default options.
   */
  function option_definition() {
    $options = parent::option_definition();

    $options['library'] = array('default' => FALSE);
		$options['fields'] = array('default' => array());
    $options['show_table'] = array('default' => FALSE);

    return $options;
  }

  /**
   * Options form for the given style.
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    // We temporarily disable grouping on all libraries.
    // @TODO In future releases there should be an option to group
    // if the visualization's data requires it.
    $form['grouping']['#access'] = FALSE;

    $handlers = $this->display->handler->get_handlers('field');

    // Reload the library from $form_state if called by ajax.
    $library = $this->getLibrary($form_state);
    // Reset the library controller.
    $this->controller->setLibrary($library);

    $form['library'] = array(
      '#title' => 'Library',
      '#description' => t('Select which d3 library you would like to use with this view. Note: For instructions on how to incorporate your custom library with views, see the README.txt.'),
      '#type' => 'select',
      '#options' => $this->getLibraryOptions(),
      '#default_value' => $this->controller->machineName(),
      '#ajax' => array(
        'path' => views_ui_build_form_url($form_state),
      ),
    );
  
    $this->controller->mapping->form($form, $form_state);

    // Additional settings.
    $form['settings'] = array(
      '#type' => 'container',
      '#tree' => TRUE,
    );
    // Can eventually separate these out into different functions.
    foreach ($this->controller->getSettings() as $key => $data) {
      $form_element = !empty($data['_info']['form_element']) ? $data['_info']['form_element'] : array();
      $form['settings'][$key] = $form_element + array(
        '#type' => 'textfield',
        '#default_value' => NULL,
        '#title' => '',
        '#description' => ''
      );
      if (!empty($this->options['settings'][$key])) {
        $form['settings'][$key]['#default_value'] = $this->options['settings'][$key];
      }
    }

    $form['show_table'] = array(
      '#title' => 'Show table',
      '#type' => 'checkbox',
      '#default_value' => $this->options['show_table'],
    );

    if (empty($handlers)) {
      $form['error_markup'] = array(
        '#markup' => '<div class="error messages">' . t('You need at least one field before you can configure your table settings') . '</div>',
      );
      return;
    }

    // Note: views UI registers this theme handler on our behalf. Your module
    // will have to register your theme handlers if you do stuff like this.
    $form['#theme'] = 'views_ui_style_d3_options_form';
  }

  /**
   * Get the current field mapping's aggregation setting.
   *
   * @param string $key1
   *   The base view field key.
   * @param string $key2
   *   For view fields that have sub-fields, this is the sub-field key.
   *
   * @return string
   *   Setting for the particular aggregation, or FALSE.
   */
  function getAggregation($key1, $key2 = FALSE) {
    if ($key2) {
      return !empty($this->options['fields'][$key1][$key2]['aggregation'])
        ? $this->options['fields'][$key1][$key2]['aggregation']
        : FALSE;
    }
    return !empty($this->options['fields'][$key1]['aggregation'])
      ? $this->options['fields'][$key1]['aggregation']
      : FALSE;
  }

  /**
   * Default value for a field mapping.
   *
   * @param string $key1
   *   The base view field key.
   * @param string $key2
   *   For view fields that have sub-fields, this is the sub-field key.
   *
   * @return object
   *   Object with field, and aggregation properties.
   */
  function getDefaultValues($key1, $key2 = NULL, $form_state = NULL) {
    $default = new StdClass();
    $default->field = FALSE;
    $default->aggregation = FALSE;

    $options = $this->getFieldOptions($form_state);
    if (!is_null($key2)) {
      return !empty($options[$key1][$key2]) ? (object) $options[$key1][$key2] : $default;
    }
    return !empty($options[$key1]) ? (object) $options[$key1] : $default;
  }

  /**
   * Get data saved to views, or from form state for options.
   */
  function getFieldOptions($form_state = NULL) {
    $options = ($form_state && !empty($form_state['input']['style_options']))
      ? $form_state['input']['style_options']
      : $this->options;
    return $options['fields'];
  }

  /**
   * Wrapper function to determine the methods to use, and execute it.
   */
  function aggregate() {
    $vis = &$this->getVis();
    $map = $this->controller->mapping->getMapping();
    $fields = $this->controller->getFields();
    // Loop through mapping to get aggregation settings.
    foreach ($map as $key => $values) {
      // Has subfields.
      if (is_array($values)) {
        // Convert the settings to numeric to match the already numeric array.
        $numeric = !empty($fields[$key]['_info']['data_type'])
          && $fields[$key]['_info']['data_type'] == '2dnnv';
        
        $index = 0;
        foreach ($values as $k => $v) {
          // We have to pas the field name to the getAggregation function, whereas
          // we need to pass the index to the aggregation function.
          // Only if it's a numeric array.
          if (($aggregation = $this->getAggregation($key, $k))
            && method_exists($this, $aggregation . 'Multiple')) {
            $k = ($numeric) ? $index : $k;
            $vis[$key] = $this->{$aggregation . 'Multiple'}($vis[$key], $k);
          }
          $index++;
        }
      }
      else {
        if (($aggregation = $this->getAggregation($key))
          && method_exists($this, $aggregation)) {
          $vis[$key] = $this->{$aggregation}($vis[$key]);
        }
      }
    }
  }

  /**
   * Aggregation function for simple arrays.
   */
  function unique($data) {
    return array_values(array_unique($data));
  }

  /**
   * Aggregation function for multidimensional arrays.
   */
  function uniqueMultiple($data, $field_name) {
    // TODO
  }

  /**
   * Aggregation function for simple arrays.
   */
  function count($data) {
    return array_count_values($data);
  }

  /**
   * Aggregation function for multidimensional arrays.
   */
  function countMultiple($data, $field_name) {
    $counted = array();
    // Restructure to group by given $field_name.
    foreach ($data as $datum) {
      $counted[$datum[$field_name]][] = $datum;
    }
    // Loop through, count each subarray.
    foreach ($counted as $field_id => &$items) {
      $count = count($items);
      // Grab the first item of each subarray with original values.
      $items = reset($items);
      $items[$field_name] = $count;
    }

    return array_values($counted);
  }

  function map($rows) {
    $this->controller->mapping->map($rows);
  }

  /**
   * Additional functionality on data before it is passed to d3_draw.
   *
   * TODO: there is some chance this code could actually be put in
   *       the D3LibraryInfoProcessor class itselfa s this functionality
   *       wolud be the same for all libraries.
   */
  function process() {
    $vis = &$this->getVis();

    // Add settings to visualization.
    if (!empty($this->options['settings'])) {
      foreach ($this->controller->getSettings() as $key => $setting)  {
        if (isset($this->options['settings'][$key])) {
          $vis[$key] = $this->options['settings'][$key];
        }
      }
    }
  }

  /**
   * Render the display in this style.
   *
   * @see template_preprocess_d3_views_view_d3().
   */
  function render() {
    if ($this->uses_row_plugin() && empty($this->row_plugin)) {
      debug('views_plugin_style_default: Missing row plugin');
      return;
    }

    $library = $this->getLibrary();
    $this->controller->setLibrary($library);
    // This is views theming, send this over to views preprocess.
    return theme($this->theme_functions(), array(
      'view' => $this->view,
      'options' => $this->options,
      'rows' => $this->render_fields($this->view->result),
    ));
  }

  /**
   * Send the vis to d3's theme handlers.
   *
   * @see template_preprocess_d3_views_view_d3().
   */
  function draw() {
    return d3_draw($this->getVis());
  }

  /**
   * Get the current visualization by reference.
   */
  public function &getVis() {
    if (!$this->vis) {
      $libraries = $this->getLibraries();
      $this->vis = array(
        'id' => 'view-d3-vis-' . $this->view->dom_id,
        'type' => $libraries[$this->options['library']]['js callback'],
      );
    }
    return $this->vis;
  }

  /**
   * Get the fully loaded from the form, or current library.
   *
   * @param Array $form_state
   *   Form API $form_state array.
   */
  function getLibrary($form_state = NULL) {
		if (!empty($form_state['values']['style_options']['library'])) {
      $library = $form_state['values']['style_options']['library'];
    }
    else {
      $library = $this->options['library'];
    }
    return !empty($library) ? libraries_load($library) : FALSE;
  }

  /**
   * Local function to get all libraries that are compatible with views.
   *
   * @return array
   *   Array of library info keyed by library machine name.
   */
  function getLibraryOptions() {
    $options = array();
    foreach ($this->getLibraries() as $library) {
      // We can match compatibility based on the views API version.
      $library_name = $library['machine name'];
      $options[$library_name] = $library['name'];
    }
    return $options;
  }

  /**
   * Get d3 libraries basic info.
   *
   * WARNING: This does not return field / settings info. For that info
   * a full libraries_load is needed.
   */
  function getLibraries() {
    if (!empty($this->libraries)) {
      return $this->libraries;
    }

    $views_api_version = views_api_version();
    // List all d3 libraries.
    $libraries = d3_get_libraries();

    $this->libraries = array();
    foreach ($libraries as $library) {
      // Skip if no views integration.
      if (empty($library['views'])) {
        continue;
      }
      // Assume library is compatible with any version if it is not specified.
      if (empty($library['views']['version'])) {
        $library['views']['version'] = $views_api_version;
      }
      if (empty($library['views']['fields'])) {
        $library['views']['fields'] = array();
      }
      // Only add to the list if the version is compatible.
      if ($library['views']['version'] <= $views_api_version) {
        $this->libraries[$library['machine name']] = $library;
      }
    }
    return $this->libraries;
  }

  /**
   * Check user field mapping matches library requirements.
   */
  function checkFieldType($handler, $field_type) {
    $message = '';
    switch ($field_type) {
      case 'integer':
        // If it's a numeric field handler, this passes.
        if ($handler->definition['handler'] == 'views_handler_field_numeric') {
          break;
        }
        // If it's a field API handler, and a number field type, this passes.
        if ($handler->definition['handler'] == 'views_handler_field_field'
          && $handler->field_info['type'] == 'number_integer') {
          break;
        }
        // All other cases should fail.
        $message = 'Error: numeric field required for integer type.';
      break;
    }
    return '<span class="error">' . $message . '</span>';
  }
}
