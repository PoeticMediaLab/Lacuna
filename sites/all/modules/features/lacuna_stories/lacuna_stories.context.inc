<?php
/**
 * @file
 * lacuna_stories.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function lacuna_stories_context_default_contexts() {
  $export = array();

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'annotate_button';
  $context->description = 'Add "Annotate" button to bibliographic entries';
  $context->tag = '';
  $context->conditions = array(
    'node' => array(
      'values' => array(
        'biblio' => 'biblio',
      ),
      'options' => array(
        'node_form' => '0',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'views-annotate_links-block_1' => array(
          'module' => 'views',
          'delta' => 'annotate_links-block_1',
          'region' => 'content',
          'weight' => '0',
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Add "Annotate" button to bibliographic entries');
  $export['annotate_button'] = $context;

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'annotations_dashboard';
  $context->description = 'Show annotations dashboard';
  $context->tag = '';
  $context->conditions = array(
    'path' => array(
      'values' => array(
        'content/annotations-dashboard' => 'content/annotations-dashboard',
        'node/62' => 'node/62',
        'node/61' => 'node/61',
      ),
    ),
  );
  $context->reactions = array(
    'breadcrumb' => '<front>',
    'region' => array(
      'bartik' => array(
        'disable' => array(
          'header' => 0,
          'help' => 0,
          'page_top' => 0,
          'page_bottom' => 0,
          'highlighted' => 0,
          'featured' => 0,
          'content' => 0,
          'sidebar_first' => 0,
          'sidebar_second' => 0,
          'triptych_first' => 0,
          'triptych_middle' => 0,
          'triptych_last' => 0,
          'footer_firstcolumn' => 0,
          'footer_secondcolumn' => 0,
          'footer_thirdcolumn' => 0,
          'footer_fourthcolumn' => 0,
          'footer' => 0,
          'dashboard_main' => 0,
          'dashboard_sidebar' => 0,
          'dashboard_inactive' => 0,
        ),
      ),
      'lacuna' => array(
        'disable' => array(
          'sidebar_first' => 'sidebar_first',
          'sidebar_second' => 'sidebar_second',
          'content' => 0,
          'header' => 0,
          'footer' => 0,
          'highlighted' => 0,
          'help' => 0,
          'page_top' => 0,
          'page_bottom' => 0,
          'dashboard_main' => 0,
          'dashboard_sidebar' => 0,
          'dashboard_inactive' => 0,
        ),
      ),
      'seven' => array(
        'disable' => array(
          'content' => 0,
          'help' => 0,
          'page_top' => 0,
          'page_bottom' => 0,
          'sidebar_first' => 0,
          'dashboard_main' => 0,
          'dashboard_sidebar' => 0,
          'dashboard_inactive' => 0,
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Show annotations dashboard');
  $export['annotations_dashboard'] = $context;

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'audiovisual_links';
  $context->description = 'Add "Annotate" button to nodes';
  $context->tag = '';
  $context->conditions = array(
    'node' => array(
      'values' => array(
        'audio' => 'audio',
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
        'views-annotate_links-block' => array(
          'module' => 'views',
          'delta' => 'annotate_links-block',
          'region' => 'content',
          'weight' => '-1',
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Add "Annotate" button to nodes');
  $export['audiovisual_links'] = $context;

  return $export;
}
