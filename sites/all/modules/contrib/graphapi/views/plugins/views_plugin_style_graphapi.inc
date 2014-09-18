<?php

/**
 * @file
 * Implements views_plugin_style for graphapi
 */

/**
 * Implements views_plugin_style
 */
class views_plugin_style_graphapi extends views_plugin_style {

  private $graph_fields = array(
    'from' => array(
      'id' => array(
        'title' => 'unique ID',
        'description' => 'Used as a unique identifier within the graph',
        'required' => true,
      ),
      'label' => array(
        'title' => 'Label to display',
      ),
      'uri' => array(
        'title' => '(tbd) Link to more info',
        'description' => 'Used for popup or link to the detailed information',
      ),
      'content' => array(
        'title' => '(tdb) Content',
        'description' => 'Displayed immediately.',
      ),
    ),
    'to' => array(
      'id' => array(
        'title' => 'unique ID',
        'description' => 'Used as a unique identifier within the graph',
        'required' => true,
      ),
      'label' => array(
        'title' => 'Label to display',
      ),
      'uri' => array(
        'title' => '(tdb) Link to more info',
        'description' => 'Used for popup or link to the detailed information',
      ),
      'content' => array(
        'title' => '(tdb) Content',
        'description' => 'Displayed immediately.',
      ),
    ),
  );

  /**
   * Implementation of views_plugin_style::option_definition
   */
  function option_definition() {
    $options = parent::option_definition();
    $options['engine'] = array('default' => 'graphapi');
    foreach ($this->graph_fields as $id => $data) {
      foreach ($data as $key => $value) {
        $options['mapping']['contains'][$id]['contains'][$key] = array('default' => NULL);
      }
    }

    // Add settings provided by plugin engines.
    $options += module_invoke_all('graphapi_default_settings');
    return $options;
  }

  function options_validate(&$form, &$form_state) {
    $values = $form_state['values']['style_options'];
    $engine = $values['engine'];
    $fields = $values[$engine]['fields'];
    $mapping = array_flip($fields);
    unset($mapping[0]);
    if (!isset($mapping['from:id'])) {
      form_error($form[$engine]['fields'], 'You must set an From ID value for ' . $engine);
    }
    if (!isset($mapping['to:id'])) {
      form_error($form[$engine]['fields'], 'You must set an To ID value for ' . $engine);
    }
  }

  /**
   * Provide a form for setting options.
   */
  function options_form(&$form, &$form_state) {
    $view = $form_state['view'];
    // We map system table ourself
    $is_system = $view->base_table == 'system';
    // TODO: next line gives grouping option
    // parent::options_form($form, $form_state);

    $options = $this->options;
    $handlers = $this->display->handler->get_handlers('field');
    if (!$is_system && (empty($handlers) || count($handlers) < 2)) {
      $form['error_markup'] = array(
        '#markup' => '<div class="error messages">' . t('You need at least two field before you can configure your graph settings') . '</div>',
      );
      return;
    }
    $engine = $options['engine'];
    $engines = graphapi_views_formats();
    if (!isset($engine) || !isset($engines[$engine])) {
      $engine = array_shift(array_keys($engines));
    }
    $opts = graphapi_views_formats();
    asort($opts);
    $form['engine'] = array(
      '#type' => 'radios',
      '#title' => t('Render type'),
      '#required' => TRUE,
      '#description' => t('The render engine to use. See the project page of !graphapi.', array('!graphapi' => l('Graph API', 'http://drupal.org/project/graphapi'))),
      '#options' => $opts,
      '#default_value' => $engine,
    );
    if (!isset($form_state['values'])) {
      $form_state['values'] = $options;
    }
    $form = graphapi_settings_form($form, $form_state);
    if ($is_system) {
      // We are done. No need for columns.
      return $form;
    }
    $field_names = $this->display->handler->get_field_labels();
    $fields = $this->display->handler->get_option('fields');

    $engines = graphapi_views_formats();
    asort($engines);
    $weight= 20;
    foreach ($engines as $engine => $dummy) {
      $form[$engine]['#collapsed'] = TRUE;
      $form[$engine]['#weight'] = $weight++;
      $form[$engine]['fields'] = array(
        '#type' => 'fieldset',
        '#title' => 'Map field destinations',
        '#description' => 'Map the views field to the correct Graph group and field.<br/>By reordering your views fields you can make this easier to follow.',
        '#collapsible' => TRUE,
        '#collapsed' => FALSE,
        '#weight' => -10,
      );
      $opts = _graphapi_mapping_options($engine);
      foreach ($field_names as $field => $label) {
        $form[$engine]['fields'][$field] = array(
          '#type' => 'select',
          '#title' => $label,
          '#description' => 'Uses ' . $field,
          '#options' => $opts,
          '#default_value' => isset($options[$engine]['fields'][$field]) ? $options[$engine]['fields'][$field] : 0,
        );
      }
    }
    return $form;
  }

  /**
   * Implementation of views_style_plugin::theme_functions().
   *
   * Returns an array of theme functions to use for the current style plugin.
   *
   * @return array
   */
  function theme_functions() {
    $hook = 'views_graphapi_style_graphapi';
    return views_theme_functions($hook, $this->view, $this->display);
  }

  /**
   * Implements views_style_plugin::additional_theme_functions(). Returns empty array.
   * @return array
   */
  function additional_theme_functions() {
    return array();
  }

  /**
   * Implementation of views_plugin_style::render().
   */
  function render() {
    $view = $this->view;
    $options = $this->options;
    $field = $view->field;
    $rows = array();
    $engine = $options['engine'];
    $settings = array();
    // Grab global settings
    if (isset($options['graphapi'])) {
      $settings = $options['graphapi'];
    }
    // Grab engine settings
    if (isset($options[$engine])) {
      $settings += $options[$engine];
    }
    $settings['engine'] = $engine;
    $vars = array(
      'view' => $view,
      'options' => $options,
      'rows' => $rows,
      'settings' => $settings
    );
    return theme($this->theme_functions(), $vars);
  }

}

