<?php

/**
 * @file
 * Progress bar example.
 */

/**
 * Implements hook_FORMID().
 *
 * Build a landing-page form for the progress bar example.
 *
 * @see https://api.drupal.org/api/drupal/developer%21topics%21forms_api_reference.html/7#ajax_progress
 */
function ajax_example_progressbar_form($form, &$form_state) {
  $form_state['time'] = REQUEST_TIME;

  // We make a DIV which the progress bar can occupy. You can see this in use
  // in ajax_example_progressbar_callback().
  $form['status'] = array(
    '#markup' => '<div id="progress-status"></div>',
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
    '#ajax' => array(
      // Here we set up our AJAX callback handler.
      'callback' => 'ajax_example_progressbar_callback',
      // Tell FormAPI about our progress bar.
      'progress' => array(
        'type' => 'bar',
        'message' => t('Execute..'),
        // Have the progress bar access this URL path.
        'url' => url('examples/ajax_example/progressbar/progress/' . $form_state['time']),
        // The time interval for the progress bar to check for updates.
        'interval' => 1000,
      ),
    ),
  );

  return $form;
}

/**
 * Get the progress bar execution status, as JSON.
 *
 * This is the menu handler for
 * examples/ajax_example/progressbar/progress/$time.
 *
 * This function is our wholly arbitrary job that we're checking the status for.
 * In this case, we're reading a system variable that is being updated by
 * ajax_example_progressbar_callback().
 *
 * We set up the AJAX progress bar to check the status every second, so this
 * will execute about once every second.
 *
 * The progress bar JavaScript accepts two values: message and percentage. We
 * set those in an array and in the end convert it JSON for sending back to the
 * client-side JavaScript.
 *
 * @param int $time
 *   Timestamp.
 *
 * @see ajax_example_progressbar_callback()
 */
function ajax_example_progressbar_progress($time) {
  $progress = array(
    'message' => t('Starting execute...'),
    'percentage' => -1,
  );

  $completed_percentage = variable_get('example_progressbar_' . $time, 0);

  if ($completed_percentage) {
    $progress['message'] = t('Executing...');
    $progress['percentage'] = $completed_percentage;
  }

  drupal_json_output($progress);
}

/**
 * Our submit handler.
 *
 * This handler spends some time changing a variable and sleeping, and then
 * finally returns a form element which marks the #progress-status DIV as
 * completed.
 *
 * While this is occurring, ajax_example_progressbar_progress() will be called
 * a number of times by the client-sid JavaScript, which will poll the variable
 * being set here.
 *
 * @see ajax_example_progressbar_progress()
 */
function ajax_example_progressbar_callback($form, &$form_state) {
  $variable_name = 'example_progressbar_' . $form_state['time'];
  $commands = array();

  variable_set($variable_name, 10);
  sleep(2);
  variable_set($variable_name, 40);
  sleep(2);
  variable_set($variable_name, 70);
  sleep(2);
  variable_set($variable_name, 90);
  sleep(2);
  variable_del($variable_name);

  $commands[] = ajax_command_html('#progress-status', t('Executed.'));

  return array(
    '#type' => 'ajax',
    '#commands' => $commands,
  );
}
