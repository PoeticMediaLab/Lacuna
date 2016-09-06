<?php

function lacuna_lti_resource_list() {
  $lti_context = lacuna_lti_context();
  if ($lti_context) {
    drupal_goto('lti_resource_list'); // now go to the view
  } else {
    drupal_set_message(t('Resource list must be requested from an LMS. No LTI data found!'), 'warning');
    drupal_exit();
  }
}