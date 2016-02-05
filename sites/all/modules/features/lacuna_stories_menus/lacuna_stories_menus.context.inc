<?php
/**
 * @file
 * lacuna_stories_menus.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function lacuna_stories_menus_context_default_contexts() {
  $export = array();

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'course_context';
  $context->description = '';
  $context->tag = '';
  $context->conditions = array(
    'context' => array(
      'values' => array(
        '~institutional_context' => '~institutional_context',
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
  $context->condition_mode = 0;
  $export['course_context'] = $context;

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'institutional_context';
  $context->description = '';
  $context->tag = '';
  $context->conditions = array(
    'path' => array(
      'values' => array(
        '<front>' => '<front>',
      ),
    ),
    'php' => array(
      'values' => array(
        0 => TRUE,
      ),
      'options' => array(
        'phpcode' => '$current_node = menu_get_object();
$current_course_id = course_get_selected_course();

// Enrolled in a course, but on a view
// Return here to avoid warnings about trying to get properties from a NULL value
if (($current_node == NULL) && ($current_course_id != FALSE)) {
  return FALSE;
}

// Enrolled in a course, but viewing a course node that isn\'t the currently enrolled course
if (($current_node->type == \'course\') && 
  ($current_course_id != (int) $current_node->nid))
{
  return TRUE;
}',
      ),
    ),
    'user' => array(
      'values' => array(
        'Pre-authorized User' => 'Pre-authorized User',
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
