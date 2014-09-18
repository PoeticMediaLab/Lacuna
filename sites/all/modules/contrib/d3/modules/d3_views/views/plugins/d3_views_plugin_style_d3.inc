<?php
/**
 * @file
 * Contains the d3 style plugin.
 */

/**
 * Style plugin to render a d3 visualization
 *
 * @ingroup views_style_plugins
 */
class d3_views_plugin_style_d3 extends views_plugin_style {

  protected $libraries = array();

  /**
   * Set default options.
   */
  function option_definition() {
    $options = parent::option_definition();

    $options['library'] = array('default' => FALSE);
    $options['columns'] = array('default' => array());

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

    $form['library'] = array(
      '#title' => 'Library',
      '#description' => t('Select which d3 library you would like to use with this view. Note: For instructions on how to incorporate your custom library with views, see the README.txt.'),
      '#type' => 'select',
      '#options' => $this->get_libraries(),
      '#default_value' => $this->options['library'],
    );

    $form['show_table'] = array(
      '#title' => 'Show Debug Table',
      '#type' => 'checkbox',
      '#default_value' => $this->options['show_table'],
    );

    $handlers = $this->display->handler->get_handlers('field');
    if (empty($handlers)) {
      $form['error_markup'] = array(
        '#markup' => '<div class="error messages">' . t('You need at least one field before you can configure your table settings') . '</div>',
      );
      return;
    }

    // Note: views UI registers this theme handler on our behalf. Your module
    // will have to register your theme handlers if you do stuff like this.
    $form['#theme'] = 'views_ui_style_d3_options_form';

    // Create an array of allowed columns from the data we know:
    $field_names = $this->display->handler->get_field_labels();

    $form['columns'] = array(
      '#tree' => TRUE,
    );

    foreach ($field_names as $field => $display) {

      // Markup for the field name.
      $form['columns'][$field]['name'] = array(
        '#markup' => $field_names[$field],
      );

      $form['columns'][$field]['display'] = array(
        '#type' => 'select',
        '#options' => array(
          'label' => t('Label'),
          'display' => t('Display Value'),
        ),
        '#default_value' => isset($this->options['columns'][$field]['display']) ? $this->options['columns'][$field]['display'] : '',
      );

      $form['columns'][$field]['aggregate'] = array(
        '#type' => 'select',
        '#options' => array(
          '_none' => t('None'),
          'count' => t('Count'),
          'count_dist' => t('Count DISTINCT'),
          'sum' => t('Sum'),
          'avg' => t('Average'),
          'min' => t('Minimum'),
          'max' => t('Maximum'),
        ),
        '#default_value' => isset($this->options['columns'][$field]['aggregate']) ? $this->options['columns'][$field]['aggregate'] : '',
      );

      $form['columns'][$field]['type'] = array(
        '#type' => 'select',
        '#options' => array(
          '_none' => t('None'),
          'column' => t('Column'),
          'row' => t('Row label'),
        ),
        '#default_value' => isset($this->options['columns'][$field]['type']) ? $this->options['columns'][$field]['type'] : '',
      );

    }

    // @TODO: It would be nice if this was triggered by ajax.
    $form['demo'] = array(
      '#type' => 'markup',
      '#prefix' => '<div id="demo">',
      '#markup' => '',
      '#suffix' => '</div>',
    );

  }

  /**
   * Normalize a list of columns and row labels to use for the visualization.
   *
   * In the example of a column chart, the column will be the
   * name in the legend, and represent the meaning of the value of
   * each bar. The row label will represent the X-Axis labels.
   *
   * @return object
   *   ->columns = array()
   *     An array of column keys
   *   ->labels = array()
   *     An array of label keys
   */
  function columns() {
    // We want to cross reference with the fields associated with the view
    // and maintain that order as well.
    $columns = array();
    foreach ($this->options['columns'] as $column => $info) {
      if ($info['type'] == 'column') {
        $columns[$column] = $info;
      }
    }
    return $columns;
  }

  /**
   * Cross reference with fields associated with the view and maintain order.
   */
  function row_labels() {
    $row_labels = array();
    foreach ($this->options['columns'] as $column => $info) {
      if ($info['type'] == 'row') {
        $row_labels[$column] = $info;
      }
    }
    return $row_labels;
  }

  /**
   * Helper function to return a count for each result row.
   */
  function count(&$data, $field) {
    $counted = array();

    foreach ($data as $row) {
      $counted[$row[$field]][] = $row;
    }

    $data = array();
    foreach ($counted as $row) {
      $values = $row[0];
      $values[$field] = count($row);

      $data[] = $values;
    }
  }

  /**
   * Wrapper function to determine the method to use, and execute it.
   */
  function aggregate($data) {
    foreach ($this->columns() as $column => $info) {
      if (isset($info['aggregate']) && $info['aggregate'] != '_none') {
        if (method_exists($this, $info['aggregate'])) {
        $this->{$info['aggregate']}($data, $column);
        }
        else {
          drupal_set_message(t('!method aggregation currently not supported', array('!method' => ucwords($info['aggregate']))), 'error');
        }
      }
    }
    return $data;
  }

  function sum(&$data, $field) {
   dsm($data); 
   dsm($field);
  }

  /**
   * Render the display in this style.
   */
  function render() {
    if ($this->uses_row_plugin() && empty($this->row_plugin)) {
      debug('views_plugin_style_default: Missing row plugin');
      return;
    }

    // Group the rows according to the grouping instructions, if specified.
    $sets = $this->render_grouping(
      $this->view->result,
      $this->options['grouping'],
      TRUE
    );

    // @TODO:
    // - get rid of grouping
    // - pass over to theme function, and preprocess
    // - render the fields according to the options
    $output = '';
    foreach ($sets as $set) {
      $output .= theme($this->theme_functions(),
          array(
            'view' => $this->view,
            'options' => $this->options,
            'rows' => $set['rows'],
            'title' => $set['group'])
          );
    }
    unset($this->view->row_index);
    return $output;
  }

  /**
   * Get the raw field value.
   *
   * @param int $index
   *   The index count of the row.
   * @param string $field
   *   The id of the field.
   */
  function get_field_value($index, $field) {
    $this->view->row_index = $index;
    $value = $this->view->field[$field]->get_value($this->view->result[$index]);
    unset($this->view->row_index);
    return $value;
  }

  /**
   * Prepare raw view result for d3.
   *
   * @return array()
   *   Multi-dimensional array of rows and fields.
   */
  function preprocess($rows) {
    $data = array();
    // An array for the grouped fields displays to show on the visualization
    // for each of the fields associated with this view.
    foreach ($rows as $index => $row) {
      // Get the display name for the row label fields that were
      // chosen on the options page.
      $labels = array();
      foreach ($this->columns()->labels as $label => $name) {
        $labels[] = $this->get_field_label($index, $label);
      }

      // Create a new array for this data row, and start with the labels
      // joined by a ' ' if necessary.
      $data_row = array(implode(' ', $labels));
      $data[] = array_values($data_row);
    }

    return $data;
  }

  /**
   * Prepare library and d3_draw array.
   *
   * @param array $rows
   *   Result array.
   *
   * @see preprocess()
   * @see render()
   */
  function draw($rows) {
    $columns = $this->columns();

    $legend = array();
    foreach ($columns as $column => $info) {
      $legend[] = $this->view->field[$column]->label();
    }
    $this->get_libraries();
    $type = $this->libraries[$this->options['library']]['js callback'];
    $chart = array(
      'id' => 'view-d3-vis-' . $this->view->dom_id,
      'type' => $type,
      'legend' => $legend,
      'rows' => $rows,
    );

    return d3_draw($chart);
  }

  /**
   * Get the rendered label for a particular field / row.
   *
   * @param int $index
   *   Row index, defined by view result.
   * @param string $field
   *   Field name.
   *
   * @return string
   *   Safe label.
   */
  function get_field_label($index, $field) {
    $group_content = '';

    if (isset($this->view->field[$field])) {
      $group_content = $this->get_field($index, $field);
      if ($this->view->field[$field]->options['label']) {
        $group_content = $this->view->field[$field]->options['label'] . ': ' . $group_content;
      }
    }

    return $group_content;
  }

  /**
   * Group records as needed for rendering.
   *
   * @param array $records
   *   An array of records from the view to group.
   * @param array $groupings
   *   An array of grouping instructions on which fields to group. If empty, the
   *   result set will be given a single group with an empty string as a label.
   * @param bool $group_rendered
   *   Boolean value whether to use the rendered or the raw field value for
   *   grouping. If set to NULL the return is structured as before
   *   Views 7.x-3.0-rc2. After Views 7.x-3.0 this boolean is only used if
   *   $groupings is an old-style string or if the rendered option is missing
   *   for a grouping instruction.
   *
   * @return array
   *   The grouped record set.
   *   A nested set structure is generated if multiple grouping fields are used.
   *
   * @code
   * array(
   *   'grouping_field_1:grouping_1' => array(
   *     'group' => 'grouping_field_1:content_1',
   *     'rows' => array(
   *       'grouping_field_2:grouping_a' => array(
   *         'group' => 'grouping_field_2:content_a',
   *         'rows' => array(
   *           $row_index_1 => $row_1,
   *           $row_index_2 => $row_2,
   *           // ...
   *         )
   *       ),
   *     ),
   *   ),
   *   'grouping_field_1:grouping_2' => array(
   *     // ...
   *   ),
   * )
   * @endcode
   */
  function render_grouping($records, $groupings = array(), $group_rendered = NULL) {
    // This is for backward compability, when $groupings was a string containing
    // the ID of a single field.
    if (is_string($groupings)) {
      $rendered = $group_rendered === NULL ? TRUE : $group_rendered;
      $groupings = array(array('field' => $groupings, 'rendered' => $rendered));
    }

    // Make sure fields are rendered.
    $this->render_fields($this->view->result);
    $sets = array();
    if ($groupings) {
      foreach ($records as $index => $row) {
        // Iterate through configured grouping fields to determine the
        // hierarchically positioned set where the current row belongs to.
        // While iterating, parent groups, that do not exist yet, are added.
        $set = &$sets;
        foreach ($groupings as $info) {
          $field = $info['field'];
          $rendered = isset($info['rendered']) ? $info['rendered'] : $group_rendered;
          $rendered_strip = isset($info['rendered_strip']) ? $info['rendered_strip'] : FALSE;
          $grouping = '';
          $group_content = '';
          // Group on the rendered version of the field, not the raw.  That way,
          // we can control any special formatting of the grouping field through
          // the admin or theme layer or anywhere else we'd like.
          if (isset($this->view->field[$field])) {
            $group_content = $this->get_field($index, $field);
            if ($this->view->field[$field]->options['label']) {
              $group_content = $this->view->field[$field]->options['label'] . ': ' . $group_content;
            }
            if ($rendered) {
              $grouping = $group_content;
              if ($rendered_strip) {
                $group_content = $grouping = strip_tags(htmlspecialchars_decode($group_content));
              }
            }
            else {
              $grouping = $this->get_field_value($index, $field);
              // Not all field handlers return a scalar value,
              // for example: views_handler_field_field.
              if (!is_scalar($grouping)) {
                $grouping = md5(serialize($grouping));
              }
            }
          }

          // Create the group if it does not exist yet.
          if (empty($set[$grouping])) {
            $set[$grouping]['group'] = $group_content;
            $set[$grouping]['rows'] = array();
          }

          // Move the set reference into the row set of the
          // group we just determined.
          $set = &$set[$grouping]['rows'];
        }
        // Add the row to the hierarchically positioned
        // row set we just determined.
        $set[$index] = $row;
      }
    }
    else {
      // Create a single group with an empty grouping field.
      $sets[''] = array(
        'group' => '',
        'rows' => $records,
      );
    }

    // If this parameter isn't explicitely set modify the output to be fully
    // backward compatible to code before Views 7.x-3.0-rc2.
    // @TODO Remove this as soon as possible e.g. October 2020
    if ($group_rendered === NULL) {
      $old_style_sets = array();
      foreach ($sets as $group) {
        $old_style_sets[$group['group']] = $group['rows'];
      }
      $sets = $old_style_sets;
    }

    return $sets;
  }

  /**
   * Local function to get all libraries that are compatible with views.
   *
   * @return array
   *   Array of library info keyed by library machine name.
   */
  function get_libraries() {
    $views_api_version = views_api_version();
    // List all d3 libraries.
    $libraries = d3_get_libraries();
    $views_libraries = array();

    foreach ($libraries as $library) {
      // We can match compatibility based on the views API version.
      if (isset($library['views']) && $library['views'] <= $views_api_version) {
        $library_name = $library['machine name'];
        $views_libraries[$library_name] = $library['name'];
        $this->libraries[$library_name] = $library;
      }
    }

    return $views_libraries;
  }
}
