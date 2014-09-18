<?php

/**
 * @file
 * This file contains no working PHP code; it exists to provide additional
 * documentation for doxygen as well as to document hooks in the standard
 * Drupal manner.
 */

/**
 * @defgroup graphapi Graph API module integrations.
 *
 * Module integrations with the graphapi module.
 *
 * ENGINE is similar to MODULE
 * FORMAT is provided by an ENGINE
 *
 * Each engine can provide multiple formats.
 * Ie a textual and a visual representation of it's structure
 */

/**
 * Defines Graph display formats.
 *
 * @return
 *   An array with key (format) value (label) pair defining the callback and display name.
 *
 * @see theme_graphapi_dispatch
 * @see theme_FORMAT_graphapi
 */
function hook_graphapi_formats() {
  return array(
    'graphapi_graphviz_filter' => 'Graphviz Filter',
  );
}

/**
 * Format specific theme function
 *
 * The $vars contains at least
 * - $graph : the graph structure
 * - $settings : the format specific settings
 *
 * @param array $vars
 */
function theme_FORMAT_graphapi(array $vars) {

}

/**
 * Provides the engine settings form.
 *
 * The settings form is used by the views display format but also by the
 * engines config pages or other unforseen places.
 *
 * @return
 *   A Drupal sub-form.
 *
 * @see graphapi_global_settings_form()
 * @see graphapi_settings_form()
 * @see _graphapi_engine_form()
 * @see graph_phyz_graphapi_settings_form()
 */
function hook_graphapi_settings_form() {
  // tbd
}

/**
 * Declares settings that should be exportable in Views.
 *
 * TODO: rewrite this views specific structure to normal.
 * - that is remove default
 *
 * The settings declared here will be included in the option_definition()
 * method, as implemented in the Graph API style plugin.
 *
 * @return array
 *   A views_plugin_style::option_definition() compatible structure.
 *
 * @see hook_graphapi_settings_form()
 * @see views_plugin_style::option_definition()
 */
function hook_graphapi_default_settings() {
  // Settings used by the first graph engine.
  $settings['my_first_engine']['contains'] = array(
    'setting 1' => array('default' => NULL),
    'setting 2' => array('default' => 1),
    'setting 3' => array('default' => t('Some string')),
  );
  // Settings used by the second graph engine.
  $settings['my_second_engine']['contains']['setting 1']['default'] = 1;
  return $settings;
}

/**
 * Example function: creates a graph of user logins by day.
 */
function user_last_login_by_day($n = 40) {
  $query = db_select('users');
  $query->addField('users', 'name');
  $query->addField('users', 'uid');
  $query->addField('users', 'created');
  $query->condition('uid', 0, '>');
  $query->orderBy('created', 'DESC');
  $query->range(0, $n);
  $result = $query->execute();
  $g = graphapi_new_graph();
  $now = time();
  $days = array();
  foreach ($result as $user) {
    $uid = $user->uid;
    $user_id = 'user_' . $uid;

    $day = intval(($now - $user->created) / (24 * 60 * 60));
    $day_id = 'data_' . $day;
    graphapi_set_node_title($g, $user_id, l($user->name, "user/" . $uid));
    graphapi_set_node_title($g, $day_id, "Day " . $day);
    graphapi_set_link_data($g, $user_id, $day_id, array('color' => '#F0F'));
  }
  $options = array(
    'width' => 400,
    'height' => 400,
    'item-width' => 50,
    'engine' => 'graph_phyz'
  );
  return theme('graphapi_dispatch', array('graph' => $g, 'config' => $options));
}

/**
 * Theme functions to implement
 *
 * @see graphapi_theme().
 * @see theme_graphapi_dispatch().
 */
function ENGINE_theme() {
  return array(
    // This is required as graphapi dispatched to the engine.
    // See theme_graphapi_dispatch()
    'engine_graphapi' => array(
      'variables' => array(
        'graph' => NULL,
        'config' => NULL,
      ),
    ),
    // To make everything themable it is likely to dispatch the engine_graphapi
    // to it's own overridable implementation
    'engine_container' => array(
      'variables' => array(
        'graph' => NULL,
        'config' => NULL,
      ),
    ),
    // This gives themers the oportunity to override the links
    'engine_links' => array(
      'variables' => array(
        'graph' => NULL,
        'config' => NULL,
      ),
    ),
    // This gives themers the oportunity to override the links
    'engine_node' => array(
      'variables' => array(
        'dom_id' => NULL,
        'data' => NULL,
        'config' => NULL,
      ),
    ),
  );
}

/**
 * Provides the engine node properties.
 *
 * @return
 *   Array of node properties.
 *
 * @see _graphapi_mapping_options()
 * @see graphapi_node_properties()
 */
function hook_graphapi_node_properties() {
  return array(
    'id' => 'ID',
    'label' => 'Label',
    'URI' => 'URI',
    'content' => 'Content',
  );
}

/**
 * Provides the engine link properties.
 *
 * @return
 *   Array of link properties.
 *
 * @see _graphapi_mapping_options()
 * @see graphapi_link_properties()
 */
function hook_graphapi_link_properties() {
  return array(
    'color' => 'Color',
  );
}
