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

  return $export;
}
