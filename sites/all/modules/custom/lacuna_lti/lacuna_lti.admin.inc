<?php

/***
 * Set up a course for instructors through LTI Consumer.
 * If course has already been created, then send them to manage the course.
 */
function lacuna_lti_setup() {
  global $base_url;
  $nid = lacuna_lti_course_select();
  $wrapper = entity_metadata_wrapper('node', $nid);
  $field_info = field_info_instances('node', 'course');
  $form_complete = TRUE;
  // Check if all required fields have been completed
  // Exception for fields with default values
  foreach ($field_info as $field => $settings) {
    if (($settings['required'] == TRUE) &&
      !$wrapper->$field->value() &&
      !isset($settings['default_value'])) // OG fields
    {
        $form_complete = FALSE;
    }
  }
  if ($form_complete == FALSE) {
    drupal_set_title('Complete Course Information');
    drupal_goto($base_url . '/node/' . $nid . '/edit');
  } else {
    // Form complete, provide a landing page instead with the links under 'Manage'
    $markup = "<div class='lacuna-lti-landing-page'>";
    $markup .= '<h1>Manage Your Lacuna Course</h1>';
    $markup .= "<div class='lacuna-lti-landing-item'>";
    $markup .= "<a href='" . $base_url . "/node/" . $nid . "/edit' target='_blank'>";
    $markup .= "Edit Course Information";
    $markup .= "</a></div>";

    $tree = menu_tree_all_data('main-menu');
    foreach ($tree as $branch) {
      if ($branch['link']['title'] == 'Manage') {
        foreach ($branch['below'] as $leaf) {
          $markup .= "<div class='lacuna-lti-landing-item' id='lacuna-lti-" . strtolower(str_replace(' ', '-', $leaf['link']['title'])) . "''>";
          $markup .= "<a href='/" . $leaf['link']['href']. "' target='_blank'>" . $leaf['link']['title'] . "</a>";
          $markup .= "</div>";
        }
      }
    }
    $markup .= "</div>";

    $content['raw_markup'] = array(
      '#type' => 'markup',
      '#markup' => $markup,
    );

    return $content;
  }
}
