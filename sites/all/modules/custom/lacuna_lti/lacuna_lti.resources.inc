<?php

function lacuna_lti_resource_list() {
  if (array_key_exists('lti_tool_provider_context_info', $_SESSION)) {
    $lti_context = $_SESSION['lti_tool_provider_context_info'];
    variable_set(lacuna_lti_get_context_variable_name(), $lti_context); // Save the LMS's request info
    drupal_goto('lti_resource_list'); // now go to the view
  } else {
    drupal_set_message(t('Resource list must be requested from an LMS. No LTI data found!'), 'warning');
  }
}