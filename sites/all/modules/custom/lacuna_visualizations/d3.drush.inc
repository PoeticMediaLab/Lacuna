<?php
/**
 * @file
 * Contains functionality needed for drush integration.
 */

/**
 * Implements hook_drush_command().
 */
function d3_drush_command() {
  $items = array();

  $items['d3'] = array(
    'description' => 'Create a new custom d3 library',
    'arguments' => array(
      'name' => 'The human readable name of your d3 library.',
      'machine_name' => 'The machine name of your d3 library.',
    ),
    'required-arguments' => 1,
    'options' => array(
      'name' => 'The human readable name of your d3 library.',
      'machine_name' => 'The machine name of your d3 library.',
      'description' => 'Library description for info file. (Shown in drush libraries-list)',
    ),
  );

  return $items;
}

/**
 * Create a d3 custom library from the template.
 */
function drush_d3($machine_name, $name = NULL) {
  if (!isset($name)) {
    $name = drush_get_option('name');
  }

  $description = drush_get_option('description');
  if (empty($description)) {
    $description = 'D3 visualization library';
  }

  $library_path = 'sites/all/libraries';
  if ($path = drush_get_option('path')) {
    $library_path = drush_trim_path($path);
  }

  $library_path = drush_normalize_path(drush_get_context('DRUSH_DRUPAL_ROOT') . '/' . $library_path . '/' . 'd3.' . $machine_name);

  $template_path = drush_normalize_path(drush_get_context('DRUSH_DRUPAL_ROOT') . '/' . drupal_get_path('module', 'd3') . '/libraries/template');

  drush_op('drush_copy_dir', $template_path, $library_path);
  $info_file = $library_path . '/d3.' . $machine_name . '.libraries.info';
  drush_op('rename', $library_path . '/template.libraries.info', $info_file);
  // Replace data in the .info file.
  drush_op('d3_file_str_replace', $info_file, array(
    '[library name]',
    '[library description]',
    '[machine name]',
  ), array($name, $description, $machine_name));
  // Replace the machine name in the main js file.
  drush_op('d3_file_str_replace', $library_path . '/template.js', array('[machine name]'), array($machine_name));
  drush_op('rename', $library_path . '/template.css', $library_path . '/' . $machine_name . '.css');
  drush_op('rename', $library_path . '/template.js', $library_path . '/' . $machine_name . '.js');
}

function d3_file_str_replace($file_path, $find, $replace) {
  $file_path = drush_normalize_path($file_path);
  $contents = file_get_contents($file_path);
  $contents = str_replace($find, $replace, $contents);
  file_put_contents($file_path, $contents);
}
