<?php

/**
 * @file
 * global_filter.proximitywidget.inc
 */

/**
 * Create the proximity widget.
 */
function global_filter_create_proximity_widget($filter_key, &$form, &$form_state) {

  $name = $form_state['global_filters'][$filter_key]['name'];

  $proximity = global_filter_get_session_value($name);
  if (!empty($proximity) && is_object($proximity)) {
    $location = $proximity->location;
    $distance = $proximity->distance;;
  }
  else {
    $location = $distance = '';
  }
  if (isset($form_state['input']['distance'])) {
    $distance = $form_state['input']['distance'];
  }
  if (isset($form_state['input']['location'])) {
    $location = $form_state['input']['location'];
  }

  $form[$name] = array(
    '#type' => 'fieldset',
    '#element_validate' => array('global_filter_proximity_widget_validate'),
  );
  $form[$name]['distance'] = array(
    '#title' => t('Within') . ' ',
    '#type' => 'textfield',
    '#size' => 6,
    '#maxlength' => 16,
    '#default_value' => $distance,
  );
  $form[$name]['location'] = array(
    '#title' => t('from'),
    '#type' => 'textfield',
    '#size' => 22,
    '#maxlength' => 127,
    '#default_value' => $location,
    '#description' => t('Enter city or partial address'),
  );
}

/**
 * Validate the proximity widget.
 */
function global_filter_proximity_widget_validate($form, &$form_state) {
  $distance = trim($form_state['values']['distance']);
  if (!empty($distance) && (!is_numeric($distance) || $distance <= 0)) {
    form_set_error('distance', t('Distance must be a positive number.'));
  }
}

/**
 * Convert the input (or lack thereof) to lat,lon coordinates and a distance.
 *
 * @todo use of visitor location and geocoding services is currently hardcoded.
 * Should perhaps be a hook?
 *
 * @param array $form_state
 *   the form state
 *
 * @return object
 *   containing entered values as well as calculated lat,lon
 */
function global_filter_extract_proximity($form_state) {
  $lat = $lon = 0.0;
  $location = trim($form_state['values']['location']);
  if (empty($location) || $location == 'me' || $location == t('me')) {
    if (module_exists('ip_geoloc')) {
      $visitor_location = ip_geoloc_get_visitor_location();
      if (isset($visitor_location['latitude'])) {
        $lat = $visitor_location['latitude'];
        $lon = $visitor_location['longitude'];
      }
    }
  }
  elseif (module_exists('geocoder')) {
    $geocoder_engines = array_keys(geocoder_handler_info('text'));
    $geocoder_engine = in_array('google', $geocoder_engines) ? 'google' : reset($geocoder_engines);
    if ($geocoded_data = geocoder($geocoder_engine, $location)) {
      $lat = $geocoded_data->getY();
      $lon = $geocoded_data->getX();
    }
  }
  $proximity = new stdClass();
  $proximity->location = $location;
  $proximity->distance = trim($form_state['values']['distance']);
  $proximity->latitude = $lat;
  $proximity->longitude = $lon;
  return $proximity;
}
