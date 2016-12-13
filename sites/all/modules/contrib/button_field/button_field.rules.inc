<?php

/**
 * @file
 * Rules integration for the button_field module.
 */

/**
 * Implements hook_rules_action_info().
 *
 * @return array
 */
function button_field_rules_action_info() {
  return array(
    'button_field_action_reload' => array(
      'label' => t('Reload the current page'),
      'group' => t('Button Field'),
    ),
  );
} // end function button_field_rules_action_info()

/**
 * Implementation of hook_rules_condition_info().
 * 
 * @return array
 */
function button_field_rules_condition_info() {
  return array(
    'button_field_compare_button' => array(
      'label' => t('Clicked button comparison'),
      'parameter' => array(
        'clicked_field' => array(
          'label' => t('Clicked field'),
          'description' => t('The button field that was clicked.'),
          'type' => 'field',
        ),
        'comparison_field_name' => array(
          'label' => t('Comparison field'),
          'description' => t('The field to compare the clicked button to.'),
          'type' => 'text',
          'options list' => '_button_field_options_list',
        ),
      ),
      'group' => t('Button Field'),
      'callbacks' => array(
        'execute' => 'button_field_compare_button',
      ),
    ),
  );
} // end function button_field_rules_condision_info()

/**
 * Implements hook_rules_event_info().
 *
 * @return array
 */
function button_field_rules_event_info() {
  return array(
  	'button_field_clicked' => array(
      'label' => t('User clicks a button field'),
      'group' => t('Button Field'),
      'variables' => array(
        'field' => array(
          'type' => 'field',
          'label' => t('Button field'),
          'description' => t('Button field that was clicked.')
        ),
        'entity' => array(
          'type' => 'entity',
          'label' => t('Entity'),
          'description' => t('Entity from the button that was clicked.'),
        ),
      ),
    ),
  );
} // end function button_field_rules_event_info()

/**
 * Reloads the current page.
 */
function button_field_action_reload() {
  // redirect to the current page
  $_REQUEST['destination'] = $_SERVER['HTTP_REFERER'];
} // end function button_field_action_reload()

/**
 * Compares the button that was clicked to the field name that was specified.
 *
 * @param array $clicked_field
 *   Field that was clicked to trigger the current event.
 * @param string $comparison_field_name
 *   Name of the field to compate the clicked field to.
 * @return boolean
 *   Whether or not the fields are the same.
 */
function button_field_compare_button($clicked_field, $comparison_field_name) {
  return ($clicked_field['field_name'] == $comparison_field_name);
} // end function button_field_compare_button()

/**
 * Returns an array of button field names that can be used for the comparison
 * condition.
 *
 * @return array
 *   Names of all button fields.
 */
function _button_field_options_list() {
  $fields = array();
  foreach (field_read_fields(array('type' => 'button_field')) as $field) {
    $fields[$field['field_name']] = $field['field_name'];
  }

  return $fields;
} // end function _button_field_options_list()

/**
 * Implements hook_rules_action_base_upgrade_map_name().
 *
 * Returns the approproate name for the Drupal 7 version of the button_is
 * condition.
 */
function button_field_condition_button_is_upgrade_map_name($element) {
  return 'button_field_compare_button';
}

/**
 * Implements hook_rules_action_base_upgrade().
 *
 * Upgrade path for button_is conditions from Drupal 6 to 7.
 */
function button_field_condition_button_is_upgrade($element, RulesPlugin $target) {
  $target->settings['clicked_field:select'] = 'field';
  $target->settings['comparison_field_name'] = $element['#settings']['button_name'];
}
