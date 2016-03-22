<?php
/**
 * @file
 * course.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function course_context_default_contexts() {
  $export = array();

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'course_context';
  $context->description = '';
  $context->tag = '';
  $context->conditions = array(
    'path' => array(
      'values' => array(
        '~<front>' => '~<front>',
      ),
    ),
    'php' => array(
      'values' => array(
        0 => TRUE,
      ),
      'options' => array(
        'phpcode' => '$current_node = menu_get_object();
$current_course_id = course_get_selected_course();
$admin = user_access(\'administer nodes\');
// Not approved for any course yet
if (($current_course_id === FALSE) && !$admin) {
  return FALSE;
}

// Enrolled in a course, but on a view
// Return here to avoid warnings about trying to get properties from a NULL value
if ($current_node == NULL) {
  return TRUE;
}

// Enrolled in a course, but viewing a course node that isn\'t the currently selected course
if ($current_node->type == \'course\') {
  // See if we can set it
  course_set_selected_course($current_node->nid);
  if (course_get_selected_course() === $current_node->nid) {
    return TRUE;
  }
}

// Course content; try to switch context
$new_course = $current_node->og_group_ref[LANGUAGE_NONE][0][\'target_id\'];
course_set_selected_course($new_course);
if (course_get_selected_course()== $new_course) {
  return TRUE;
}
return FALSE;',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'superfish-1' => array(
          'module' => 'superfish',
          'delta' => '1',
          'region' => 'header',
          'weight' => '-10',
        ),
      ),
    ),
  );
  $context->condition_mode = 1;
  $export['course_context'] = $context;

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'frontpage';
  $context->description = '';
  $context->tag = '';
  $context->conditions = array(
    'path' => array(
      'values' => array(
        '<front>' => '<front>',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'block-1' => array(
          'module' => 'block',
          'delta' => '1',
          'region' => 'highlighted',
          'weight' => '-10',
        ),
        'global_filter-global_filter_1' => array(
          'module' => 'global_filter',
          'delta' => 'global_filter_1',
          'region' => 'content',
          'weight' => '-10',
        ),
        'views-courses-enrolled' => array(
          'module' => 'views',
          'delta' => 'courses-enrolled',
          'region' => 'content',
          'weight' => '-9',
        ),
        'views-courses-not_enrolled' => array(
          'module' => 'views',
          'delta' => 'courses-not_enrolled',
          'region' => 'content',
          'weight' => '-8',
        ),
      ),
    ),
  );
  $context->condition_mode = 0;
  $export['frontpage'] = $context;

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'institutional_context';
  $context->description = '';
  $context->tag = '';
  $context->conditions = array(
    'context' => array(
      'values' => array(
        '~course_context' => '~course_context',
      ),
    ),
    'path' => array(
      'values' => array(
        '<front>' => '<front>',
      ),
    ),
    'user' => array(
      'values' => array(
        'anonymous user' => 'anonymous user',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'superfish-2' => array(
          'module' => 'superfish',
          'delta' => '2',
          'region' => 'header',
          'weight' => '-10',
        ),
      ),
    ),
  );
  $context->condition_mode = 0;
  $export['institutional_context'] = $context;

  return $export;
}
