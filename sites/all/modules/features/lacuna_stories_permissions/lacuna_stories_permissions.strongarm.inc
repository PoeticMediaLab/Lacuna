<?php
/**
 * @file
 * lacuna_stories_permissions.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function lacuna_stories_permissions_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'content_access_annotation';
  $strongarm->value = array(
    'view_own' => array(
      0 => 2,
      1 => 3,
      2 => 4,
    ),
    'view' => array(
      0 => 2,
      1 => 5,
      2 => 6,
      3 => 3,
      4 => 4,
    ),
    'priority' => '-1',
  );
  $export['content_access_annotation'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'content_access_audio';
  $strongarm->value = array(
    'view_own' => array(
      0 => 2,
      1 => 3,
      2 => 4,
    ),
    'view' => array(
      0 => 2,
      1 => 3,
      2 => 4,
    ),
  );
  $export['content_access_audio'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'content_access_blog';
  $strongarm->value = array(
    'view_own' => array(
      0 => 2,
      1 => 3,
      2 => 4,
    ),
    'view' => array(
      0 => 5,
      1 => 6,
      2 => 3,
      3 => 4,
    ),
  );
  $export['content_access_blog'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'content_access_course_or_other_group';
  $strongarm->value = array(
    'view_own' => array(
      0 => 2,
      1 => 3,
      2 => 4,
    ),
    'view' => array(
      0 => 2,
      1 => 3,
      2 => 4,
    ),
  );
  $export['content_access_course_or_other_group'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'content_access_document';
  $strongarm->value = array(
    'view_own' => array(
      0 => 2,
      1 => 3,
      2 => 4,
    ),
    'view' => array(
      0 => 5,
      1 => 6,
      2 => 3,
      3 => 4,
    ),
  );
  $export['content_access_document'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'content_access_image';
  $strongarm->value = array(
    'view_own' => array(
      0 => 2,
      1 => 3,
      2 => 4,
    ),
    'view' => array(
      0 => 2,
      1 => 3,
      2 => 4,
    ),
  );
  $export['content_access_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'content_access_music_video';
  $strongarm->value = array(
    'view_own' => array(
      0 => 2,
      1 => 3,
      2 => 4,
    ),
    'view' => array(
      0 => 2,
      1 => 3,
      2 => 4,
    ),
  );
  $export['content_access_music_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'content_access_video';
  $strongarm->value = array(
    'view_own' => array(
      0 => 2,
      1 => 3,
      2 => 4,
    ),
    'view' => array(
      0 => 5,
      1 => 6,
      2 => 3,
      3 => 4,
    ),
  );
  $export['content_access_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'content_access_webform';
  $strongarm->value = array(
    'view_own' => array(
      0 => 2,
      1 => 3,
      2 => 4,
    ),
    'view' => array(
      0 => 2,
      1 => 3,
      2 => 4,
    ),
  );
  $export['content_access_webform'] = $strongarm;

  return $export;
}
