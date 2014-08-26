<?php

/**
 * @file
 * Functions for rules integration.
 */

/**
 * Implements of hook_rules_event_info().
 * @ingroup rules
 */
function webform_rules_rules_event_info() {
  return array(
    'webform_rules_submit_as_draft' => array(
      'label' => t('After a webform has been saved as draft'),
      'group' => t('Webform'),
      'variables' => _webform_rules_event_variables(),
      'access callback' => 'rules_node_integration_access',
    ),
    'webform_rules_submit' => array(
      'label' => t('After a webform has been submitted'),
      'group' => t('Webform'),
      'variables' => _webform_rules_event_variables(),
      'access callback' => 'rules_node_integration_access',
    ),
    'webform_rules_insert' => array(
      'label' => t('After a submission draft has been submitted'),
      'group' => t('Webform'),
      'variables' => _webform_rules_event_variables(),
      'access callback' => 'rules_node_integration_access',
    ),
    'webform_rules_update' => array(
      'label' => t('After a webform submission has been updated'),
      'group' => t('Webform'),
      'variables' => _webform_rules_event_variables(),
      'access callback' => 'rules_node_integration_access',
    ),
    'webform_rules_delete' => array(
      'label' => t('After a webform submission has been deleted'),
      'group' => t('Webform'),
      'variables' => _webform_rules_event_variables(),
      'access callback' => 'rules_node_integration_access',
    ),
  );
}

/**
 * Implementation of hook_condition_info().
 */
function webform_rules_rules_condition_info() {
  return array(
    'webform_has_id' => array(
      'label' => t('Webform has name'),
      'parameter' => array(
        'form_id' => array(
          'type' => 'text',
          'label' => t('The form id of the submitted form'),
        ),
        'selected_webform' => array(
          'type' => 'list<text>',
          'label' => t('Webforms'),
          'options list' => 'webform_rules_get_webforms_as_options',
          'description' => t('The name of the webform to check for.'),
          'restriction' => 'input',
        ),
      ),
      'help' => t('This condition compares the id of the submitted form with the selected value(s).'),
      'group' => t('Webform'),
      'base' => 'webform_rules_condition_webform_has_id',
    ),
    'node_is_webform' => array(
      'label' => t('Content is webform-enabled'),
      'parameter' => array(
      'node' => array(
        'type' => 'node',
        'label' => t('Content'),
        'description' => t('The content to verify.'),
      ),
      ),
      'help' => t('This condition verifies a node contains a webform.'),
      'group' => t('Webform'),
      'base' => 'webform_rules_condition_node_is_webform',
    ),
  );
}

/**
 * Implements hook_rules_action_info().
 *
 */
function webform_rules_rules_action_info() {
  $defaults = array(
    'group' => t('Webform'),
    'access callback' => 'rules_node_admin_access',
    'parameter' => array(
      'entity' => array(
        'type' => 'node',
        'label' => t('Webform'),
        'description' => t('A webform-enabled node.'),
        'save' => TRUE,
        'optional' => TRUE,
      ),
      'selected_webform' => array(
        'type' => 'list<text>',
        'label' => t('Webforms'),
        'options list' => 'webform_rules_get_webforms_as_options',
        'description' => t('List of webforms to open.'),
        'restriction' => 'input',
        'optional' => TRUE,
      ),
    ),
    'callbacks' => array(
      'validate' => 'webform_rules_webform_statuschange_validate',
    ),
  );
  $actions = array(
    'webform_open' => $defaults + array(
      'label' => t('Open webforms'),
      'base' => 'webform_rules_webform_open',
    ),
    'webform_close' => $defaults + array(
      'label' => t('Close webforms'),
      'base' => 'webform_rules_webform_close',
    ),
    'webform_submissions_load' => array(
      'label' => t('Fetch webform submissions'),
      'base' => t('webform_rules_submissions_load'),
      'group' => t('Webform'),
      'access callback' => 'rules_node_admin_access',
      'parameter' => array(
        'nid' => array(
          'type' => 'integer',
          'label' => t('Node ID'),
          'description' => t('The ID of the webform node to load the submission for.'),
        ),
        'sid' => array(
          'type' => 'integer',
          'label' => t('Submission ID'),
          'description' => t('The ID of a webform submission. If omitted all submissions of the specified node ID will be fetched.'),
          'optional' => TRUE,
        ),
      ),
      'provides' => array(
        'submissions' => array(
          'label' => t('Fetched submissions'),
          'type' => 'list<list>',
        ),
      ),
    ),
  );

  // Modify description of closing action.
  $actions['webform_close']['parameter']['selected_webform']['description'] = t('The name of the webforms to close.');

  return $actions;
}

/**
 * Implements hook_rules_data_info().
 */
function webform_rules_data_info() {
  return array(
    'webform_data' => array(
      'label' => t('webform data'),
      'group' => t('Webform'),
      'token type' => 'webform',
      'property info' => array(),
    ),
  );
}

/**
 * Validation callback for actions 'webform_rules_webform_open' and
 * 'webform_rules_webform_close'.
 */
function webform_rules_webform_statuschange_validate($element) {
  if (empty($element->settings['entity:select']) && empty($element->settings['selected_webform'])) {
    throw new RulesIntegrityException(t('At least one parameter needs to be set.'), array($element, 'parameter', 'node'));
  }
}

/**
 * Function to compare the form id of the submitted webform with the selected
 * form.
 */
function webform_rules_condition_webform_has_id($form_id, $selected_webform) {
  if (is_array($selected_webform)) {
    return in_array($form_id, $selected_webform);
  }
  elseif (is_string($selected_webform)) {
    return $form_id == $selected_webform;
  }
  return FALSE;
}

/**
 * Condition callback to determine whether a node contains a webform.
 */
function webform_rules_condition_node_is_webform($node) {
  // Get a list of all nodes that are configured to use a webform.
  $query = db_select('node', 'n')
    ->fields('n', array('nid', 'title'))
    ->condition('n.nid', $node->nid);
  // Join to limit result list to node that really have a webform.
  $query->join('webform', 'w', 'n.nid = w.nid');
  // Join {webform_component} to prevent listing unconfigured webforms.
  $query->join('webform_component', 'c', 'n.nid = c.nid');
  // Get the result list.
  if ($query->execute()->rowCount() > 0) {
    return TRUE;
  }
  return FALSE;
}

/**
 * Rules action callback to open webforms.
 */
function webform_rules_webform_open($entity = FALSE, $selected_webforms = array()) {
  _webform_rules_webform_set_status($entity, $selected_webforms);
}

/**
 * Rules action callback to close webforms.
 */
function webform_rules_webform_close($entity = FALSE, $selected_webforms = array()) {
  _webform_rules_webform_set_status($entity, $selected_webforms, FALSE);
}

/**
 * Helper method to update the status of a webform.
 */
function _webform_rules_webform_set_status($entity = FALSE, $selected_webforms = array(), $open = TRUE) {
  if (!empty($entity->nid) && webform_rules_condition_node_is_webform($entity)) {
    // Set new status.
    $entity->webform['status'] = ($open == TRUE) ? 1 : 0;
  }
  module_load_include('inc', 'rules', 'modules/entity.eval');
  // Try to close all selected webforms.
  foreach ($selected_webforms as $form_id) {
    // Try to get node id from form_id.
    $nid = str_replace('webform-client-form-', '', $form_id);
    // Load the node object.
    $result = rules_action_entity_fetch('node', $nid, NULL);
    $webform = $result['entity_fetched'];
    if (!empty($webform->nid) && webform_rules_condition_node_is_webform($webform)) {
      // Set new status.
      $webform->webform['status'] = ($open == TRUE) ? 1 : 0;
      // Save the webform node. Maybe we can find a better way how to save?
      node_save($webform);
    }
  }
}

/**
 * Rules action to load a list of webform submissions.
 *
 * @param int $nid
 *   ID of node to load the submissions for.
 * @param int $sid
 *   (optional) Submission ID.
 *
 * @return array
 *   List of loaded webform submissions.
 */
function webform_rules_submissions_load($nid, $sid = NULL) {
  // Make sure the needed functions are available.
  module_load_include('inc', 'webform', 'includes/webform.submissions');
  $filters = array(
    'nid' => $nid,
  );
  if (!empty($sid)) {
    $filters['sid'] = $sid;
  }
  // Fetch submissions.
  $submissions = webform_get_submissions($filters);

  return array('submissions' => $submissions);
}

/**
 * Helper function for event variables.
 *
 * @return
 *   All available variables for the rules events provided by webform_rules.
 */
function _webform_rules_event_variables() {
  return array(
    'user' => array(
      'type' => 'user',
      'label' => t('User, who submitted the webform'),
    ),
    'node' => array(
      'type' => 'node',
      'label' => t('The webform node'),
    ),
    'data' => array(
      'type' => 'webform',
      'label' => t('The submitted webform data'),
    ),
    'form_id' => array(
      'type' => 'text',
      'label' => t('The form id of the submitted form'),
      'hidden' => TRUE,
    ),
    'selected_webform' => array(
      'type' => 'list<text>',
      'label' => t('Webforms'),
      'options list' => 'webform_rules_get_webforms_as_options',
      'description' => t('The name of the webform to check for.'),
      'restriction' => 'input',
      'hidden' => TRUE,
      'optional' => TRUE,
    ),
  );
}

