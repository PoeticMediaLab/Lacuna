<?php

/**
 * @file
 * Drush integration for Superfish.
 */

/**
 * The Superfish plugin URI.
 */
define('SUPERFISH_DOWNLOAD_URI', 'https://github.com/mehrpadin/Superfish-for-Drupal/archive/1.x.zip');

/**
 * Implements hook_drush_command().
 */
function superfish_drush_command() {
  $items = array();

  // The key in the $items array is the name of the command.
  $items['superfish-plugin'] = array(
    'callback' => 'drush_superfish_plugin',
    'description' => dt("Downloads the Superfish plugin."),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH,
    'arguments' => array(
      'path' => dt('Optional. A path where to install the Superfish plugin. If omitted Drush will use the default location.'),
    ),
    'aliases' => array('superfishplugin'),
  );

  return $items;
}

/**
 * Implements hook_drush_help().
 */
function superfish_drush_help($section) {
  switch ($section) {
    case 'drush:superfish-plugin':
      return dt("Downloads the Superfish plugin, default location is sites/all/libraries.");
  }
}

/**
 * Command to download the Superfish plugin.
 */
function drush_superfish_plugin() {
  $args = func_get_args();
  if (!empty($args[0])) {
    $path = $args[0];
  }
  else {
    $path = 'sites/all/libraries';
  }

  // Create the path if it does not exist.
  if (!is_dir($path)) {
    drush_op('mkdir', $path);
    drush_log(dt('Directory @path was created', array('@path' => $path)), 'notice');
  }

  // Set the directory to the download location.
  $olddir = getcwd();
  chdir($path);

  // Download the zip archive.
  if ($filepath = drush_download_file(SUPERFISH_DOWNLOAD_URI)) {
    $filename = basename($filepath);
    $dirname = 'Superfish-for-Drupal-' . basename($filepath, '.zip');

    // Remove any existing Superfish plugin directory.
    if (is_dir($dirname) || is_dir('superfish')) {
      drush_delete_dir($dirname, TRUE);
      drush_delete_dir('superfish', TRUE);
      drush_log(dt('A existing Superfish plugin was deleted from @path', array('@path' => $path)), 'notice');
    }

    // Decompress the zip archive.
    drush_tarball_extract($filename);

    // Change the directory name to "superfish" if needed.
    if ($dirname != 'superfish') {
      drush_move_dir($dirname, 'superfish', TRUE);
      $dirname = 'superfish';
    }
  }

  if (is_dir($dirname)) {
    drush_log(dt('Superfish plugin has been uploaded to @path', array('@path' => $path)), 'success');
  }
  else {
    drush_log(dt('Drush was unable to upload the Superfish plugin to @path', array('@path' => $path)), 'error');
  }

  // Set working directory back to the previous working directory.
  chdir($olddir);
}