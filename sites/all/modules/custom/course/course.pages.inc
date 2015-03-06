<?php

/**
 * Course Creation Page; Menu callback.
 */
function course_create() {
  if (!user_is_logged_in()) {
    drupal_set_message("You will need to login to continue", 'error');
  }
  $output = "Thanks for your interest in setting up a Lacuna Stories course. Currently, courses are only being created after instructors have had a consultation with the Lacuna Stories team. To arrange a consultation, email <a href='info@lacunastories.com'>info@lacunastories.com</a>. If you have already been approved to create a course, please enter the Course Setup Code given to you by a Lacuna Stories team member.";

  $authcode_form = drupal_render(drupal_get_form('course_authcode_form'));
  return $output . " " . $authcode_form;
}

function course_authcode_form($form, &$form_state) {
  $form['authcode'] = array(
    '#type' => 'textfield',
    '#title' => 'Course Setup Code',
    '#size' => 10,
    '#required' => TRUE
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Authorize'
  );

  return $form;
}

function course_authcode_form_submit($form, &$form_state) {
  if ('s3kr3t' == $form['authcode']['#value']) {
    drupal_set_message("Your Course Setup Code was recognized, please contact a Lacuna Stories team member if you have any issues creating your course.");
    drupal_goto('node/add/course-or-other-group');
  }
  else {
    drupal_set_message("Unfortunately, we do not recognize your Course Setup Code.  Please try again or contact a Lacuna Stories team member.");
    drupal_goto('createcourse');
  }
}
