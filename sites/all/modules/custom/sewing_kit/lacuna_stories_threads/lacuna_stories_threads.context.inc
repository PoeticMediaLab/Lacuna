<?php
/**
 * @file
 * lacuna_stories_threads.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function lacuna_stories_threads_context_default_contexts() {
  $export = array();

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'stitchings';
  $context->description = 'Show stitchings for a thread';
  $context->tag = 'Sewing Kit';
  $context->conditions = array(
    'node' => array(
      'values' => array(
        'thread' => 'thread',
      ),
      'options' => array(
        'node_form' => '1',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'views-stitchings-block' => array(
          'module' => 'views',
          'delta' => 'stitchings-block',
          'region' => 'content',
          'weight' => '-10',
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Sewing Kit');
  t('Show stitchings for a thread');
  $export['stitchings'] = $context;

  return $export;
}
