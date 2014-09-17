<?php
/**
 * @file
 * lacuna_stories_content_types.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function lacuna_stories_content_types_context_default_contexts() {
  $export = array();

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'annotation_filters';
  $context->description = 'Annotation Filters';
  $context->tag = '';
  $context->conditions = array(
    'node' => array(
      'values' => array(
        'blog' => 'blog',
        'document' => 'document',
        'image' => 'image',
        'music_video' => 'music_video',
        'video' => 'video',
      ),
      'options' => array(
        'node_form' => '0',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'block-1' => array(
          'module' => 'block',
          'delta' => '1',
          'region' => 'sidebar_second',
          'weight' => '-10',
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Annotation Filters');
  $export['annotation_filters'] = $context;

  return $export;
}
