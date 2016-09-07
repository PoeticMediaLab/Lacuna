<?php

/***
 * Set up a course for instructors through LTI Consumer.
 * If course has already been created, then send them to manage the course.
 */
function lacuna_lti_setup() {
  $nid = lacuna_lti_course_select();
  drupal_goto('node/' . $nid . '/edit');
  // check for required fields in course; if missing, go to edit it
  // If done, display options to manage taxonomies, add documents, or edit course information?
  // And a message that course already exists?
  // Maybe a page with the 3 different options, with icons and nice big boxes
  // That could be the "Manage" menu item
}