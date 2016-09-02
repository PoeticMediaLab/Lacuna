<?php
/**
 * @file
 * lacuna_notifications.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function lacuna_notifications_context_default_contexts() {
  $export = array();

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'recent_interactions_page';
  $context->description = '';
  $context->tag = '';
  $context->conditions = array(
    'path' => array(
      'values' => array(
        'recent-interactions' => 'recent-interactions',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'views-comments_on_threads_view-block' => array(
          'module' => 'views',
          'delta' => 'comments_on_threads_view-block',
          'region' => 'content',
          'weight' => '-10',
        ),
        'views-220158f4a69df629932c5cc73344defd' => array(
          'module' => 'views',
          'delta' => '220158f4a69df629932c5cc73344defd',
          'region' => 'content',
          'weight' => '-9',
        ),
        'views-b12c389f8fc7310c5e95d7ae0209ba2a' => array(
          'module' => 'views',
          'delta' => 'b12c389f8fc7310c5e95d7ae0209ba2a',
          'region' => 'content',
          'weight' => '-8',
        ),
      ),
    ),
  );
  $context->condition_mode = 0;
  $export['recent_interactions_page'] = $context;

  return $export;
}
