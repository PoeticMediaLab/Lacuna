<?php
/**
 * @file
 * lacuna_stories_threads.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function lacuna_stories_threads_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'thread_description'.
  $field_bases['thread_description'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'thread_description',
    'indexes' => array(
      'format' => array(
        0 => 'format',
      ),
    ),
    'locked' => 1,
    'module' => 'text',
    'settings' => array(
      'max_length' => '',
    ),
    'translatable' => 0,
    'type' => 'text_long',
  );

  // Exported field_base: 'thread_reference'.
  $field_bases['thread_reference'] = array(
    'active' => 1,
    'cardinality' => -1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'thread_reference',
    'indexes' => array(
      'target_id' => array(
        0 => 'target_id',
      ),
    ),
    'locked' => 1,
    'module' => 'entityreference',
    'settings' => array(
      'handler' => 'base',
      'handler_settings' => array(
        'target_bundles' => array(
          0 => 'annotation',
        ),
      ),
      'target_type' => 'node',
    ),
    'translatable' => 0,
    'type' => 'entityreference',
  );

  return $field_bases;
}
