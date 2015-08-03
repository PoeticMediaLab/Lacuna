<?php
/**
 * @file
 * global_filter_plugin_argument_default_global_filter_proximity.inc
 *
 * Contains a Global Filter default argument plugin (for proxomity argument).
 */

/**
 * Default argument plugin to extract the global View filter proximity value
 * set for this contextual filter.
 *
 * The value returned is a string of the format "lat,lon_dist", which is
 * accepted by the Location and Geofield contextual filters for proximity.
 */
class global_filter_plugin_argument_default_global_filter_proximity extends views_plugin_argument_default {

  /**
   * Option definition.
   */
  public function option_definition() {
    $options = parent::option_definition();
    $options['global_filter_proximity_distance'] = array('default' => '100');
    return $options;
  }

  /**
   * Build the options form.
   */
  public function options_form(&$form, &$form_state) {
    $form['global_filter_proximity_distance'] = array(
      '#type' => 'textfield',
      '#title' => t('Distance'),
      '#size' => 8,
      '#default_value' => $this->options['global_filter_proximity_distance'],
      '#description' => t('Enter a default distance to define the proximity area centered on the reference location supplied by the user in the Global Filter block form. For units etc. see the settings at the bottom of this panel.'),
    );
  }

  /**
   * Get argument.
   */
  public function get_argument() {
    $exception_value = $this->argument->options['exception']['value'];

    $proximity_field_name = isset($this->argument->definition['field_name']) ? $this->argument->definition['field_name'] : $this->argument->field;
    if (global_filter_key_by_name($proximity_field_name)) {

      $arg = global_filter_get_session_value($proximity_field_name);
      if (!empty($arg)) {
        if (is_object($arg)) {
          // Return in this format: lat,lon_dist
          $latlon = $arg->latitude . ',' . $arg->longitude;
          $distance = trim(empty($arg->distance) && $arg->distance != 0 ? $this->options['global_filter_proximity_distance'] : $arg->distance);
          return empty($distance) ? $latlon : $latlon . '_' . $distance;
        }
        if (is_array($arg)) {
          $arg = reset($arg);
        }
        $arg = trim($arg);
        if (!empty($arg)) {
          // Allow $arg to contain distance as second arg. If not specified
          // fall back on the admin default.
          // Allowed patterns: lat,lon_dist and postcode_dist
          // Instead of an underscore a space may be used.
          if (strpos($arg, '_')) {
            // This is the Location module native format.
            return $arg;
          }
          // Allow a space as a separator: "lat,lon dist" or "lat, lon dist"
          if (($pos_space = strrpos($arg, ' ')) && drupal_substr($arg, $pos_space - 1, 1) != ',') {
            $arg = drupal_substr($arg, 0, $pos_space) . '_' . drupal_substr($arg, $pos_space + 1);
          }
          else {
            // No distance specified, append the admin default.
            if ($distance = trim($this->options['global_filter_proximity_distance'])) {
              $arg .= '_' . $distance;
            }
          }
          return $arg;
        }
      }
      return $exception_value;
    }
    $view_name = empty($this->view->human_name) ? $this->view->name : $this->view->human_name;
    drupal_set_message(t('The view %view specifies a global filter location proximity field, %name, as its default contextual filter. However there is no associated <strong>Global Filter block</strong> for it. Please configure a global filter <a href="admin/structure/block">here</a> or remove this contextual filter default from the view.', array(
      '%view' => $view_name, '%name' => $proximity_field_name)), 'warning', FALSE);
    return $exception_value;
  }
}
