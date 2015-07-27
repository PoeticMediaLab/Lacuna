<?php
/**
 * @file
 * global_filter_views.inc
 *
 * Defines the Global Filter default argument plugins.
 */

/**
 * Implements hook_views_plugins().
 *
 * Note that while contextual filters are assigned to fields, contextual filter
 * 'argument default' plugins are global and as far as I can see, unconditional.
 * To suppress 'global_filter_proximity' filtr in contexts where it does not
 * apply we implement hook_form_FORMID_alter().
 */
function global_filter_views_plugins() {
  $plugins = array(
    'argument default' => array(
      'global_filter_field' => array(
        'title' => t('Global filter (field or search term)'),
        'handler' => 'global_filter_plugin_argument_default_global_filter_field',
      ),
      'global_filter_view' => array(
        'title' => t('Global filter (View)'),
        'handler' => 'global_filter_plugin_argument_default_global_filter_view',
      ),
      'global_filter_proximity' => array(
        'title' => t('Global filter (proximity)'),
        'handler' => 'global_filter_plugin_argument_default_global_filter_proximity',
      ),
    ),
  );
  return $plugins;
}
