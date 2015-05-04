<?php

class D3ViewsDataMapping extends D3DataMapping {
  /**
   * Not sure about this particular property.
   *
   * TODO: this needs work defining this in the abstract.
   */
  protected $plugin;

  public function setPlugin(d3_views_plugin_style_d3 $plugin) {
    $this->plugin = $plugin;
  }

  public function form(&$form, &$form_state) {
    $data_key = $this->library->getDataKey();
    $form['fields'] = array(
      '#type' => 'container',
      '#tree' => TRUE,
    );

    foreach ($this->library->getFields() as $key => $data) {
      if ($key == '_info') {
        continue;
      }
      $element = &$form['fields'][$key];
      $element['#caption'] = t('Data required for settings.!key.', array('!key' => $key));

      if ($data_key == $key) {
        $element['#caption'] .= t(' This is the main data array that will be used in the visualization.');
        $data['_info']['data_type'] = '2dnav';
      }
        // Set to "2dnav" by default.
      if ($key == '_info' || empty($data['_info']['data_type'])) {
        continue;
      }

      $data_type = strtoupper($data['_info']['data_type']);
      if (method_exists($this, 'form' . $data_type)) {
        $this->{'form' . $data_type}($form, $form_state, $data, $key);
      }
    }

  
    $this->formRepeated($form, $form_state);
  }

  protected function formSV(&$form, &$form_state, $data, $key) {
    $this->formS($form, $form_state, $data, $key);
  }

  protected function formS(&$form, &$form_state, $data, $key) {
    $element = &$form['fields'][$key];
    $default_values = $this->plugin->getDefaultValues($key, NULL, $form_state);
    $this->formRow($element, $data, $form_state, $default_values);
  }

  /**
   * 1-dimensional numeric array of fields / labels.
   */
  protected function form1DN(&$form, &$form_state, $data, $key) {
    $element = &$form['fields'][$key];
    $cardinality = $data['_info']['cardinality'];
    $k = 0;
    do {
      $default_values = $this->plugin->getDefaultValues($key, $k, $form_state);
      $this->formRow($element[$k], $data, $form_state, $default_values);
      $k++;
      if (!empty($cardinality) && $k >= $cardinality) {
        break;
      }
    }
    while (!empty($default_values->field) && $default_values->field != '__none');
    
  }

  /**
   * 1-dimensional numeric array of row values.
   */
  protected function form1DNV(&$form, &$form_state, $data, $key) {
  }

  /**
   * 1-dimensional associative array of fields / labels.
   */
  protected function form1DA(&$form, &$form_state, $data, $key) {
    
  }

  /**
   * 2-dimensional numeric array of numeric array of row values.
   */
  protected function form2DNNV(&$form, &$form_state, $data, $key) {
    // We change this to numeric in mapping, no need for a different configuration.
    $this->form2DNAV($form, $form_state, $data, $key); 
  }

  /**
   * 2-dimensional numeric array of associative array of row values.
   *
   * Used for default data keys.
   */
  protected function form2DNAV(&$form, &$form_state, $data, $key) {
    $element = &$form['fields'][$key];
    foreach ($data as $k => $datum) {
      // TODO: same as todo before this.
      if ($k == '_info') {
        continue;
      }
      $default_values = $this->plugin->getDefaultValues($key, $k, $form_state);
      $this->formRow($element[$k], $datum, $form_state, $default_values);
    }
  }

  /**
   * Helper function to isolate each row.
   *
   * @see options_form().
   */
  protected function formRow(&$field, $field_info, &$form_state, StdClass $default_values) {
    $field_names = $this->plugin->display->handler->get_field_labels();
    $handlers = $this->plugin->display->handler->get_handlers('field');

    $field['name'] = array(
      '#title' => t('Lib data field'),
      '#markup' => $field_info['label'],
    );
    $field['type'] = array(
      '#title' => t('Variable type'),
      '#markup' => $field_info['type'],
    );
    $field['description'] = array(
      '#title' => 'Description',
      '#markup' => !empty($field_info['description']) ? $field_info['description'] : NULL,
    );
    $field['field'] = array(
      '#title' => t('View field'),
      '#type' => 'select',
      '#options' => array('__none' => '-- No mapping --') + $field_names,
      '#default_value' => $default_values->field,
      '#ajax' => array(
        'path' => views_ui_build_form_url($form_state),
      ),
    );
    $field['aggregation'] = array(
      '#title' => t('Aggregation'),
      '#type' => 'select',
      '#options' => array(
        '_none' => t('None'),
        'unique' => t('Unique'),
        'count' => t('Count'),
      ),
      '#default_value' => $default_values->aggregation,
    );

    // Run a check on the field type if it's been selected, compare to the
    // field type in the libraries info.
    if ($default_values->field && $default_values->field != '__none') {
      $field['field']['#suffix'] = $this->plugin->checkFieldType($handlers[$default_values->field], $field_info['type']);
    }
      // We can't use aggregation on data that isn't in the main data array.
  }

  protected function formRepeated(&$form, &$form_state) {
    $options = $this->plugin->getFieldOptions($form_state);
    $fields = &$form['fields'];
    foreach ($this->library->getFields() as $key => $field) {
      if ($key == '_info') {
        continue;
      }
      if ($key == $this->library->getDataKey()) {
        foreach ($field as $k => $f) {
          if (isset($f['_info']['repeated']) && $f['_info']['repeated']) {
            // TODO: handle cardinality if it is not zero, really we would just
            // inerate through the amount.
            $this->formRepeatedSubRow($form, $form_state, $key, $k);
          }
        }
      }
      else {
        if (isset($field['_info']['repeated']) && $field['_info']['repeated']) {
          $this->formRepeatedRow($form, $form_state, $key);
        }
      }
    }
  }

  protected function formRepeatedRow(&$form, $form_state, $key, $k = NULL) {
    $library = $this->library->value();
    $fields = &$form['fields'];
    $f = ($k) ? $library['views']['fields'][$key][$k] : $library['views']['fields'][$key];
    $options = $this->plugin->getFieldOptions($form_state);
    $x = 0;
    // Loop through the values set in options.
    do  {
      $default_values = $this->plugin->getDefaultValues($key . $x, $k, $form_state);
      $this->formRow($fields[$key . $x], $f, $form_state, $default_values);
      $x++;
    } while (isset($options[$key . $x]));

    // Delete the original row that hasn't been concatenated with a integer.
    unset($fields[$key]);
    // If there is only one value and it is empty, that means they haven't set anything yet.
    if ($x == 1 && (empty($default_values->field) || $default_values->field == '_none')) {
      return;
    }
    // Add an additional row if the previous row is true.
    if ($default_values->field && $default_values->field != '__none') {
      // Should always return a blank value.
      $default_values = $this->plugin->getDefaultValues($key . $x, $k, $form_state);
      $this->formRow($fields[$key . $x], $f, $form_state, $default_values);
    }
    else {
      // If the previous row is false, find any other straggelers.
      $count = 0;
      $x--;
      while (empty($options[$key . $x]['field']) || $options[$key . $x]['field'] == '__none') {
        // If they just initiated it, break out.
        if ($count > 0) {
          unset($fields[$key . ($x + 1)]);
        }
        $count++;
        $x--;
      }
    }
  }

  protected function formRepeatedSubRow(&$form, $form_state, $key, $k = NULL) {
    $library = $this->library->value();
    $fields = &$form['fields'];
    $f = ($k) ? $library['views']['fields'][$key][$k] : $library['views']['fields'][$key];
    $options = $this->plugin->getFieldOptions($form_state);
    $x = 0;
    // Loop through the values set in options.
    do  {
      $default_values = $this->plugin->getDefaultValues($key, $k . $x, $form_state);
      $this->formRow($fields[$key][$k . $x], $f, $form_state, $default_values);
      $x++;
    } while (isset($options[$key][$k . $x]));

    // Delete the original row that hasn't been concatenated with a integer.
    unset($fields[$key][$k]);
    // If there is only one value and it is empty, that means they haven't set anything yet.
    if ($x == 1 && (empty($default_values->field) || $default_values->field == '__none')) {
      return;
    }
    // Add an additional row if the previous row is true.
    if ($default_values->field && $default_values->field != '__none') {
      // Should always return a blank value.
      $default_values = $this->plugin->getDefaultValues($key, $k . $x, $form_state);
      $this->formRow($fields[$key][$k . $x], $f, $form_state, $default_values);
    }
    else {
      // If the previous row is false, find any other straggelers.
      $count = 0;
      $x--;
      while (empty($options[$key][$k . $x]['field']) || $options[$key][$k . $x]['field'] == '__none') {
        if ($count > 0) {
          // Unset the previous one.
          unset($fields[$key][$k . ($x + 1)]);
        }
        $count++;
        $x--;
      }
    }
  }

  /**
   * Map views fields to library info specified field names.
   *
   * @see template_preprocess_d3_views_view_d3().
   */
  public function map($rows = array()) {
    $vis = &$this->plugin->getVis();
    $map = $this->getMapping();
    $fields = $this->library->getFields();

    // If there are no mapping setings, just add the rows as is.
    if (empty($map)) {
      $vis['rows'] =  $rows;
      return;
    }

    // Loop through data rows.
    foreach ($rows as $index => $row) {
      // If there are no mappings, map the default views behavior.
      // Loop through mapping rows.
      foreach ($map as $key => $value) {
        if (empty($vis[$key])) {
          $vis[$key] = NULL;
        }
        $type = FALSE;
        if ($this->library->isDataKey($key)) {
          $type = '2DNAV';
        }
        if (!empty($fields[$key]['_info']['data_type'])) {
          $type = $fields[$key]['_info']['data_type'];
        }

        if ($type && method_exists($this, 'map' . $type)) {
          $this->{'map' . $type}($value, $row, $vis[$key], $index);
        }
        else {
          $vis['rows'][$index] = $row;
        }
      }
    }
  }

  /**
   * Get the current mapping configuration.
   */
  public function getMapping() {
    if (empty($this->plugin->options['fields'])) {
      return array();
    }
    $map = array();
    foreach ($this->plugin->options['fields'] as $key => $values) {
      // If it's a single field.
      if (!empty($values['field'])) {
        $map[$key] = $values['field'];
      }
      else {
        // If it has multiple subfields.
        foreach ($values as $k => $v) {
          if (!empty($v['field'])) {
            $map[$key][$k] = $v['field'];
          }
        }
      }
    }
    return $map;
  }

  protected function mapS($mapping, $row, &$output, $index) {
    // Only populate once.
    if (empty($output)) {
      $output = $this->plugin->view->field[$mapping]->label();
    }
  }

  protected function mapSV($mapping, $row, &$output, $index) {
    // Only populate once.
    if (empty($output)) {
      $output = $row[$mapping];
    }
  }

  protected function map1DN($mapping, $row, &$output, $index) {
    // Only populate once.
    if (empty($output)) {
      foreach ($mapping as $index => $value) {
        if (!empty($value) && $value != '__none') {
          $output[$index] = $this->plugin->view->field[$value]->label();
        }
      }
    }
  }

  protected function map1DNV($row) {

  }

  protected function map1DA($row) {

  }

  protected function map2DNNV($mapping, $row, &$output, $index) {
    $this->map2DNAV($mapping, $row, $output, $index); 
    $output[$index] = array_values($output[$index]);
  }

  protected function map2DNAV($mapping, $row, &$output, $index) {
    $output[$index] = array();
    foreach ($mapping as $destination => $source) {
      if (!empty($source) && $source != '__none') {
        $output[$index][$destination] = $row[$source];
      }
    }
  }
}
