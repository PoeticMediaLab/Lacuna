<?php
/**
 * @file
 * This file contains no working PHP code; it exists to provide additional
 * documentation for doxygen as well as to document hooks in the standard
 * Drupal manner.
 */

/**
 * Alter the value passed to the Global Filter.
 *
 * This hook allows you to change the Global Filter value before it is set.
 *
 * @param string $name
 *   The name of the field used as a Global Filter.
 *
 * @param mixed $value
 *   The value of the Global Filter, passed by reference, so it can be changed.
 */
function hook_global_filter_value_alter($name, &$value) {
  // Global Filter for city using Smart IP.
  if ($name == 'field_city' && $value == '') {
    $value = $_SESSION['smart_ip']['location']['city'];
  }
}
