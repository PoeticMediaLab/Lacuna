<?php
/**
 * @file
 * Views style plugins to render nodes in the XML data format.
 *
 * @see views_plugin_style_xml.inc
 * @ingroup views_plugins
 */

/**
 * Implements hook_views_plugins().
 */
function d3_views_plugins() {

  $path = drupal_get_path('module', 'd3_views') . '/views';
  return array(
    'module' => 'd3_views',
    'style' => array(
      'd3_style' => array(
        'title'           => t('D3 Visualization'),
        'path'            => $path . '/plugins',
        'help'            => t('Display view as a D3 visualization'),
        'handler'         => 'd3_views_plugin_style_d3',
        'theme'           => 'd3_views_view_d3',
        'theme path'      => $path . '/theme',
        'theme file'      => 'd3_views_view_d3.theme.inc',
        'uses row plugin' => FALSE,
        'uses fields'     => TRUE,
        'uses options'    => TRUE,
        'type'            => 'normal',
        'help_topic'      => 'style-xml',
        'even empty'      => TRUE,
      ),
    ),
  );
}
