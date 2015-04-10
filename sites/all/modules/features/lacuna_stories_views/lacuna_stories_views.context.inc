<?php
/**
 * @file
 * lacuna_stories_views.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function lacuna_stories_views_context_default_contexts() {
  $export = array();

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'cite_as';
  $context->description = 'Show bibliographic citation for a document';
  $context->tag = '';
  $context->conditions = array(
    'node' => array(
      'values' => array(
        'document' => 'document',
      ),
      'options' => array(
        'node_form' => '0',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'views-cite_as-block' => array(
          'module' => 'views',
          'delta' => 'cite_as-block',
          'region' => 'content',
          'weight' => '10',
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Show bibliographic citation for a document');
  $export['cite_as'] = $context;

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'stitchings';
  $context->description = 'Show stitchings for a thread';
  $context->tag = 'thread';
  $context->conditions = array(
    'node' => array(
      'values' => array(
        'thread' => 'thread',
      ),
      'options' => array(
        'node_form' => '0',
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
          'weight' => '10',
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Show stitchings for a thread');
  t('thread');
  $export['stitchings'] = $context;

  return $export;
}
