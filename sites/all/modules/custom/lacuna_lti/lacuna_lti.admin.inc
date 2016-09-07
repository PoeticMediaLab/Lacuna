<?php

/***
 * Set up a course for instructors through LTI Consumer.
 * If course has already been created, then send them to manage the course.
 */
function lacuna_lti_setup() {
  $lti_context = lacuna_lti_get_context();
  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'course')
    ->fieldCondition('field_lms_id', 'value', $lti_context['context_id'], '=');
  $result = $query->execute();
  if (!isset($result['node'])) {
    // LTI Tool Provider module should have created it already
    drupal_set_message(t('Something went wrong creating your course. Please contact the site administrator'), 'error');
    drupal_goto('/');
  }
  $nid = array_keys($result['node']); // Avoid PHP strict warning
  $nid = array_shift($nid);
  drupal_goto('node/' . $nid . '/edit');
  // check for required fields in course; if missing, go to edit it
  // If done, display options to manage taxonomies, add documents, or edit course information?
  // And a message that course already exists?
  // Maybe a page with the 3 different options, with icons and nice big boxes
  // That could be the "Manage" menu item
}