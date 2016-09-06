<?php

/***
 * Set up a course for instructors through LTI Consumer.
 * If course has already been created, then send them to manage the course.
 */
function lacuna_lti_setup() {
  // Check if course exists
  // If not, create it and populate fields with $_SESSION LTI values
  // check for required fields in course; if missing, go to edit it
  // need to modify course to alter the course form to hide certain fields in course_create()
  // If done, display options to manage taxonomies, add documents, or edit course information?
  // And a message that course already exists?
  // Maybe a page with the 3 different options, with icons and nice big boxes
  // That could be the "Manage" menu item
}