<?php
/**
 * @file
 * lacuna_stories_threads.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function lacuna_stories_threads_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'sewing-kit';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Sewing Kit';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Sewing Kit';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'create thread content';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['reset_button'] = TRUE;
  $handler->display->display_options['exposed_form']['options']['autosubmit'] = TRUE;
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '25';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'views_bulk_operations' => 'views_bulk_operations',
    'field_annotation_reference' => 'field_annotation_reference',
    'field_annotation_quote' => 'field_annotation_quote',
    'field_annotation_text' => 'field_annotation_text',
    'field_display_name' => 'field_display_name',
    'field_annotation_tags' => 'field_annotation_tags',
    'field_annotation_category' => 'field_annotation_category',
    'field_annotation_audience' => 'field_annotation_audience',
    'og_group_ref' => 'og_group_ref',
    'php' => 'php',
    'path' => 'path',
    'nid' => 'nid',
    'nothing' => 'nothing',
  );
  $handler->display->display_options['style_options']['default'] = 'field_display_name';
  $handler->display->display_options['style_options']['info'] = array(
    'views_bulk_operations' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_annotation_reference' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_annotation_quote' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_annotation_text' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_display_name' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_annotation_tags' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
    ),
    'field_annotation_category' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
    ),
    'field_annotation_audience' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'og_group_ref' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'php' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'path' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'nid' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'nothing' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = TRUE;
  $handler->display->display_options['empty']['area']['content'] = 'There are no annotations that match the selected limits.';
  $handler->display->display_options['empty']['area']['format'] = 'filtered_html';
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_annotation_reference_target_id']['id'] = 'field_annotation_reference_target_id';
  $handler->display->display_options['relationships']['field_annotation_reference_target_id']['table'] = 'field_data_field_annotation_reference';
  $handler->display->display_options['relationships']['field_annotation_reference_target_id']['field'] = 'field_annotation_reference_target_id';
  $handler->display->display_options['relationships']['field_annotation_reference_target_id']['label'] = 'Annotated Content';
  /* Relationship: Content: Author */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'node';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  /* Field: Bulk operations: Content */
  $handler->display->display_options['fields']['views_bulk_operations']['id'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['table'] = 'node';
  $handler->display->display_options['fields']['views_bulk_operations']['field'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['label'] = 'Select for Thread';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['display_type'] = '1';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['enable_select_all_pages'] = 1;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['row_clickable'] = 1;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['force_single'] = 0;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['entity_load_capacity'] = '10';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_operations'] = array(
    'action::sewing_kit_stitch' => array(
      'selected' => 1,
      'skip_confirmation' => 1,
      'override_label' => 0,
      'label' => '',
    ),
    'action::views_data_export_action_csv_export' => array(
      'selected' => 1,
      'skip_confirmation' => 1,
      'override_label' => 1,
      'label' => 'Export',
    ),
  );
  /* Field: Content: Annotated Content */
  $handler->display->display_options['fields']['field_annotation_reference']['id'] = 'field_annotation_reference';
  $handler->display->display_options['fields']['field_annotation_reference']['table'] = 'field_data_field_annotation_reference';
  $handler->display->display_options['fields']['field_annotation_reference']['field'] = 'field_annotation_reference';
  $handler->display->display_options['fields']['field_annotation_reference']['settings'] = array(
    'link' => 1,
  );
  /* Field: Content: Excerpt */
  $handler->display->display_options['fields']['field_annotation_quote']['id'] = 'field_annotation_quote';
  $handler->display->display_options['fields']['field_annotation_quote']['table'] = 'field_data_field_annotation_quote';
  $handler->display->display_options['fields']['field_annotation_quote']['field'] = 'field_annotation_quote';
  $handler->display->display_options['fields']['field_annotation_quote']['alter']['max_length'] = '150';
  $handler->display->display_options['fields']['field_annotation_quote']['alter']['trim'] = TRUE;
  $handler->display->display_options['fields']['field_annotation_quote']['element_class'] = 'fix-width-15';
  /* Field: Content: Annotation Text */
  $handler->display->display_options['fields']['field_annotation_text']['id'] = 'field_annotation_text';
  $handler->display->display_options['fields']['field_annotation_text']['table'] = 'field_data_field_annotation_text';
  $handler->display->display_options['fields']['field_annotation_text']['field'] = 'field_annotation_text';
  $handler->display->display_options['fields']['field_annotation_text']['alter']['max_length'] = '150';
  $handler->display->display_options['fields']['field_annotation_text']['alter']['trim'] = TRUE;
  $handler->display->display_options['fields']['field_annotation_text']['element_class'] = 'fix-width-15';
  $handler->display->display_options['fields']['field_annotation_text']['type'] = 'text_plain';
  /* Field: User: Display Name */
  $handler->display->display_options['fields']['field_display_name']['id'] = 'field_display_name';
  $handler->display->display_options['fields']['field_display_name']['table'] = 'field_data_field_display_name';
  $handler->display->display_options['fields']['field_display_name']['field'] = 'field_display_name';
  $handler->display->display_options['fields']['field_display_name']['relationship'] = 'uid';
  $handler->display->display_options['fields']['field_display_name']['label'] = 'Annotator';
  /* Field: Content: Tags */
  $handler->display->display_options['fields']['field_annotation_tags']['id'] = 'field_annotation_tags';
  $handler->display->display_options['fields']['field_annotation_tags']['table'] = 'field_data_field_annotation_tags';
  $handler->display->display_options['fields']['field_annotation_tags']['field'] = 'field_annotation_tags';
  $handler->display->display_options['fields']['field_annotation_tags']['type'] = 'taxonomy_term_reference_plain';
  $handler->display->display_options['fields']['field_annotation_tags']['delta_offset'] = '0';
  /* Field: Content: Category */
  $handler->display->display_options['fields']['field_annotation_category']['id'] = 'field_annotation_category';
  $handler->display->display_options['fields']['field_annotation_category']['table'] = 'field_data_field_annotation_category';
  $handler->display->display_options['fields']['field_annotation_category']['field'] = 'field_annotation_category';
  $handler->display->display_options['fields']['field_annotation_category']['type'] = 'taxonomy_term_reference_plain';
  /* Field: Content: Audience */
  $handler->display->display_options['fields']['field_annotation_audience']['id'] = 'field_annotation_audience';
  $handler->display->display_options['fields']['field_annotation_audience']['table'] = 'field_data_field_annotation_audience';
  $handler->display->display_options['fields']['field_annotation_audience']['field'] = 'field_annotation_audience';
  $handler->display->display_options['fields']['field_annotation_audience']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_annotation_audience']['delta_offset'] = '0';
  /* Field: Content: Groups audience */
  $handler->display->display_options['fields']['og_group_ref']['id'] = 'og_group_ref';
  $handler->display->display_options['fields']['og_group_ref']['table'] = 'og_membership';
  $handler->display->display_options['fields']['og_group_ref']['field'] = 'og_group_ref';
  $handler->display->display_options['fields']['og_group_ref']['exclude'] = TRUE;
  $handler->display->display_options['fields']['og_group_ref']['settings'] = array(
    'link' => 0,
  );
  $handler->display->display_options['fields']['og_group_ref']['delta_offset'] = '0';
  /* Field: Global: PHP */
  $handler->display->display_options['fields']['php']['id'] = 'php';
  $handler->display->display_options['fields']['php']['table'] = 'views';
  $handler->display->display_options['fields']['php']['field'] = 'php';
  $handler->display->display_options['fields']['php']['label'] = 'Shared With';
  $handler->display->display_options['fields']['php']['use_php_setup'] = 0;
  $handler->display->display_options['fields']['php']['php_output'] = '<?php 
if (module_exists(\'course\')) {
  print course_sewing_kit_shared_with($data);
}
?>';
  $handler->display->display_options['fields']['php']['use_php_click_sortable'] = '0';
  $handler->display->display_options['fields']['php']['php_click_sortable'] = '';
  /* Field: Content: Path */
  $handler->display->display_options['fields']['path']['id'] = 'path';
  $handler->display->display_options['fields']['path']['table'] = 'node';
  $handler->display->display_options['fields']['path']['field'] = 'path';
  $handler->display->display_options['fields']['path']['relationship'] = 'field_annotation_reference_target_id';
  $handler->display->display_options['fields']['path']['exclude'] = TRUE;
  $handler->display->display_options['fields']['path']['absolute'] = TRUE;
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['label'] = '';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = '<span class="fa fa-eye"></span>';
  $handler->display->display_options['fields']['nothing']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['nothing']['alter']['path'] = '[path]?id=[nid]';
  $handler->display->display_options['fields']['nothing']['alter']['absolute'] = TRUE;
  $handler->display->display_options['fields']['nothing']['alter']['target'] = '_blank';
  $handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'annotation' => 'annotation',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  /* Filter criterion: Content: Author (select list) */
  $handler->display->display_options['filters']['author_select']['id'] = 'author_select';
  $handler->display->display_options['filters']['author_select']['table'] = 'node';
  $handler->display->display_options['filters']['author_select']['field'] = 'author_select';
  $handler->display->display_options['filters']['author_select']['group'] = 1;
  $handler->display->display_options['filters']['author_select']['exposed'] = TRUE;
  $handler->display->display_options['filters']['author_select']['expose']['operator_id'] = 'author_select_op';
  $handler->display->display_options['filters']['author_select']['expose']['label'] = 'Limit by Annotator';
  $handler->display->display_options['filters']['author_select']['expose']['operator'] = 'author_select_op';
  $handler->display->display_options['filters']['author_select']['expose']['identifier'] = 'author_select';
  $handler->display->display_options['filters']['author_select']['expose']['multiple'] = TRUE;
  $handler->display->display_options['filters']['author_select']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    5 => 0,
    3 => 0,
    4 => 0,
    6 => 0,
    7 => 0,
    8 => 0,
  );
  /* Filter criterion: Content: Annotated Content (field_annotation_reference) */
  $handler->display->display_options['filters']['field_annotation_reference_target_id']['id'] = 'field_annotation_reference_target_id';
  $handler->display->display_options['filters']['field_annotation_reference_target_id']['table'] = 'field_data_field_annotation_reference';
  $handler->display->display_options['filters']['field_annotation_reference_target_id']['field'] = 'field_annotation_reference_target_id';
  $handler->display->display_options['filters']['field_annotation_reference_target_id']['group'] = 1;
  $handler->display->display_options['filters']['field_annotation_reference_target_id']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_annotation_reference_target_id']['expose']['operator_id'] = 'field_annotation_reference_target_id_op';
  $handler->display->display_options['filters']['field_annotation_reference_target_id']['expose']['label'] = 'Limit by Material';
  $handler->display->display_options['filters']['field_annotation_reference_target_id']['expose']['operator'] = 'field_annotation_reference_target_id_op';
  $handler->display->display_options['filters']['field_annotation_reference_target_id']['expose']['identifier'] = 'document';
  $handler->display->display_options['filters']['field_annotation_reference_target_id']['expose']['multiple'] = TRUE;
  $handler->display->display_options['filters']['field_annotation_reference_target_id']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    5 => 0,
    3 => 0,
    4 => 0,
    6 => 0,
    7 => 0,
    8 => 0,
  );
  /* Filter criterion: Content: Tags (field_annotation_tags) */
  $handler->display->display_options['filters']['field_annotation_tags_tid']['id'] = 'field_annotation_tags_tid';
  $handler->display->display_options['filters']['field_annotation_tags_tid']['table'] = 'field_data_field_annotation_tags';
  $handler->display->display_options['filters']['field_annotation_tags_tid']['field'] = 'field_annotation_tags_tid';
  $handler->display->display_options['filters']['field_annotation_tags_tid']['group'] = 1;
  $handler->display->display_options['filters']['field_annotation_tags_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_annotation_tags_tid']['expose']['operator_id'] = 'field_annotation_tags_tid_op';
  $handler->display->display_options['filters']['field_annotation_tags_tid']['expose']['label'] = 'Limit by Tags';
  $handler->display->display_options['filters']['field_annotation_tags_tid']['expose']['operator'] = 'field_annotation_tags_tid_op';
  $handler->display->display_options['filters']['field_annotation_tags_tid']['expose']['identifier'] = 'field_annotation_tags_tid';
  $handler->display->display_options['filters']['field_annotation_tags_tid']['expose']['multiple'] = TRUE;
  $handler->display->display_options['filters']['field_annotation_tags_tid']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    5 => 0,
    3 => 0,
    4 => 0,
    6 => 0,
    7 => 0,
    8 => 0,
  );
  $handler->display->display_options['filters']['field_annotation_tags_tid']['reduce_duplicates'] = TRUE;
  $handler->display->display_options['filters']['field_annotation_tags_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_annotation_tags_tid']['vocabulary'] = 'annotation_tags';
  $handler->display->display_options['filters']['field_annotation_tags_tid']['error_message'] = FALSE;
  /* Filter criterion: Content: Category (field_annotation_category) */
  $handler->display->display_options['filters']['field_annotation_category_tid']['id'] = 'field_annotation_category_tid';
  $handler->display->display_options['filters']['field_annotation_category_tid']['table'] = 'field_data_field_annotation_category';
  $handler->display->display_options['filters']['field_annotation_category_tid']['field'] = 'field_annotation_category_tid';
  $handler->display->display_options['filters']['field_annotation_category_tid']['group'] = 1;
  $handler->display->display_options['filters']['field_annotation_category_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_annotation_category_tid']['expose']['operator_id'] = 'field_annotation_category_tid_op';
  $handler->display->display_options['filters']['field_annotation_category_tid']['expose']['label'] = 'Limit by Category';
  $handler->display->display_options['filters']['field_annotation_category_tid']['expose']['operator'] = 'field_annotation_category_tid_op';
  $handler->display->display_options['filters']['field_annotation_category_tid']['expose']['identifier'] = 'field_annotation_category_tid';
  $handler->display->display_options['filters']['field_annotation_category_tid']['expose']['multiple'] = TRUE;
  $handler->display->display_options['filters']['field_annotation_category_tid']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    5 => 0,
    3 => 0,
    4 => 0,
    6 => 0,
    7 => 0,
    8 => 0,
  );
  $handler->display->display_options['filters']['field_annotation_category_tid']['reduce_duplicates'] = TRUE;
  $handler->display->display_options['filters']['field_annotation_category_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_annotation_category_tid']['vocabulary'] = 'annotation_categories';
  /* Filter criterion: Content: Audience (field_annotation_audience) */
  $handler->display->display_options['filters']['field_annotation_audience_value']['id'] = 'field_annotation_audience_value';
  $handler->display->display_options['filters']['field_annotation_audience_value']['table'] = 'field_data_field_annotation_audience';
  $handler->display->display_options['filters']['field_annotation_audience_value']['field'] = 'field_annotation_audience_value';
  $handler->display->display_options['filters']['field_annotation_audience_value']['group'] = 1;
  $handler->display->display_options['filters']['field_annotation_audience_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_annotation_audience_value']['expose']['operator_id'] = 'field_annotation_audience_value_op';
  $handler->display->display_options['filters']['field_annotation_audience_value']['expose']['label'] = 'Limit by Sharing';
  $handler->display->display_options['filters']['field_annotation_audience_value']['expose']['operator'] = 'field_annotation_audience_value_op';
  $handler->display->display_options['filters']['field_annotation_audience_value']['expose']['identifier'] = 'field_annotation_audience_value';
  $handler->display->display_options['filters']['field_annotation_audience_value']['expose']['multiple'] = TRUE;
  $handler->display->display_options['filters']['field_annotation_audience_value']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    5 => 0,
    3 => 0,
    4 => 0,
    6 => 0,
    7 => 0,
    8 => 0,
  );
  /* Filter criterion: After */
  $handler->display->display_options['filters']['created']['id'] = 'created';
  $handler->display->display_options['filters']['created']['table'] = 'node';
  $handler->display->display_options['filters']['created']['field'] = 'created';
  $handler->display->display_options['filters']['created']['ui_name'] = 'After';
  $handler->display->display_options['filters']['created']['operator'] = '>=';
  $handler->display->display_options['filters']['created']['group'] = 1;
  $handler->display->display_options['filters']['created']['exposed'] = TRUE;
  $handler->display->display_options['filters']['created']['expose']['operator_id'] = 'created_op';
  $handler->display->display_options['filters']['created']['expose']['label'] = 'After';
  $handler->display->display_options['filters']['created']['expose']['operator'] = 'created_op';
  $handler->display->display_options['filters']['created']['expose']['identifier'] = 'posted_after';
  $handler->display->display_options['filters']['created']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    5 => 0,
    3 => 0,
    4 => 0,
    6 => 0,
    7 => 0,
    8 => 0,
  );
  /* Filter criterion: Before */
  $handler->display->display_options['filters']['created_1']['id'] = 'created_1';
  $handler->display->display_options['filters']['created_1']['table'] = 'node';
  $handler->display->display_options['filters']['created_1']['field'] = 'created';
  $handler->display->display_options['filters']['created_1']['ui_name'] = 'Before';
  $handler->display->display_options['filters']['created_1']['operator'] = '<=';
  $handler->display->display_options['filters']['created_1']['exposed'] = TRUE;
  $handler->display->display_options['filters']['created_1']['expose']['operator_id'] = 'created_1_op';
  $handler->display->display_options['filters']['created_1']['expose']['label'] = 'Before';
  $handler->display->display_options['filters']['created_1']['expose']['operator'] = 'created_1_op';
  $handler->display->display_options['filters']['created_1']['expose']['identifier'] = 'posted_before';
  $handler->display->display_options['filters']['created_1']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    5 => 0,
    3 => 0,
    4 => 0,
    6 => 0,
    7 => 0,
    8 => 0,
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'sewing-kit';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Sewing Kit';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'main-menu';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;

  /* Display: Data export */
  $handler = $view->new_display('views_data_export', 'Data export', 'views_data_export_1');
  $handler->display->display_options['defaults']['group_by'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'views_data_export_txt';
  $handler->display->display_options['style_options']['provide_file'] = 1;
  $handler->display->display_options['style_options']['filename'] = '%view%timestamp-full.txt';
  $handler->display->display_options['style_options']['parent_sort'] = 0;
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_annotation_reference_target_id']['id'] = 'field_annotation_reference_target_id';
  $handler->display->display_options['relationships']['field_annotation_reference_target_id']['table'] = 'field_data_field_annotation_reference';
  $handler->display->display_options['relationships']['field_annotation_reference_target_id']['field'] = 'field_annotation_reference_target_id';
  $handler->display->display_options['relationships']['field_annotation_reference_target_id']['label'] = 'Annotated Content';
  /* Relationship: Content: Author */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'node';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_bibliographic_item_target_id']['id'] = 'field_bibliographic_item_target_id';
  $handler->display->display_options['relationships']['field_bibliographic_item_target_id']['table'] = 'field_data_field_bibliographic_item';
  $handler->display->display_options['relationships']['field_bibliographic_item_target_id']['field'] = 'field_bibliographic_item_target_id';
  $handler->display->display_options['relationships']['field_bibliographic_item_target_id']['relationship'] = 'field_annotation_reference_target_id';
  $handler->display->display_options['relationships']['field_bibliographic_item_target_id']['label'] = 'Biblio - Response';
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_bibliographic_entry_target_id']['id'] = 'field_bibliographic_entry_target_id';
  $handler->display->display_options['relationships']['field_bibliographic_entry_target_id']['table'] = 'field_data_field_bibliographic_entry';
  $handler->display->display_options['relationships']['field_bibliographic_entry_target_id']['field'] = 'field_bibliographic_entry_target_id';
  $handler->display->display_options['relationships']['field_bibliographic_entry_target_id']['relationship'] = 'field_annotation_reference_target_id';
  $handler->display->display_options['relationships']['field_bibliographic_entry_target_id']['label'] = 'Biblio - Document';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Biblio: Biblio Citation */
  $handler->display->display_options['fields']['citation']['id'] = 'citation';
  $handler->display->display_options['fields']['citation']['table'] = 'biblio';
  $handler->display->display_options['fields']['citation']['field'] = 'citation';
  $handler->display->display_options['fields']['citation']['relationship'] = 'field_bibliographic_item_target_id';
  $handler->display->display_options['fields']['citation']['label'] = 'Bibliographic Citation';
  $handler->display->display_options['fields']['citation']['exclude'] = TRUE;
  $handler->display->display_options['fields']['citation']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['citation']['style_name'] = 'chicago';
  $handler->display->display_options['fields']['citation']['export_links'] = 0;
  $handler->display->display_options['fields']['citation']['file_attachments'] = 0;
  $handler->display->display_options['fields']['citation']['open_url_link'] = 0;
  /* Field: Biblio: Biblio Citation */
  $handler->display->display_options['fields']['citation_1']['id'] = 'citation_1';
  $handler->display->display_options['fields']['citation_1']['table'] = 'biblio';
  $handler->display->display_options['fields']['citation_1']['field'] = 'citation';
  $handler->display->display_options['fields']['citation_1']['relationship'] = 'field_bibliographic_entry_target_id';
  $handler->display->display_options['fields']['citation_1']['label'] = 'Bibliographic Citation';
  $handler->display->display_options['fields']['citation_1']['empty'] = '[citation]';
  $handler->display->display_options['fields']['citation_1']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['citation_1']['style_name'] = 'chicago';
  $handler->display->display_options['fields']['citation_1']['export_links'] = 0;
  $handler->display->display_options['fields']['citation_1']['file_attachments'] = 0;
  $handler->display->display_options['fields']['citation_1']['open_url_link'] = 0;
  /* Field: Content: Excerpt */
  $handler->display->display_options['fields']['field_annotation_quote']['id'] = 'field_annotation_quote';
  $handler->display->display_options['fields']['field_annotation_quote']['table'] = 'field_data_field_annotation_quote';
  $handler->display->display_options['fields']['field_annotation_quote']['field'] = 'field_annotation_quote';
  $handler->display->display_options['fields']['field_annotation_quote']['alter']['max_length'] = '150';
  $handler->display->display_options['fields']['field_annotation_quote']['element_class'] = 'fix-width-15';
  /* Field: Content: Annotation Text */
  $handler->display->display_options['fields']['field_annotation_text']['id'] = 'field_annotation_text';
  $handler->display->display_options['fields']['field_annotation_text']['table'] = 'field_data_field_annotation_text';
  $handler->display->display_options['fields']['field_annotation_text']['field'] = 'field_annotation_text';
  $handler->display->display_options['fields']['field_annotation_text']['alter']['max_length'] = '150';
  $handler->display->display_options['fields']['field_annotation_text']['element_class'] = 'fix-width-15';
  $handler->display->display_options['fields']['field_annotation_text']['type'] = 'text_plain';
  /* Field: User: Display Name */
  $handler->display->display_options['fields']['field_display_name']['id'] = 'field_display_name';
  $handler->display->display_options['fields']['field_display_name']['table'] = 'field_data_field_display_name';
  $handler->display->display_options['fields']['field_display_name']['field'] = 'field_display_name';
  $handler->display->display_options['fields']['field_display_name']['relationship'] = 'uid';
  $handler->display->display_options['fields']['field_display_name']['label'] = 'Annotator';
  /* Field: Content: Tags */
  $handler->display->display_options['fields']['field_annotation_tags']['id'] = 'field_annotation_tags';
  $handler->display->display_options['fields']['field_annotation_tags']['table'] = 'field_data_field_annotation_tags';
  $handler->display->display_options['fields']['field_annotation_tags']['field'] = 'field_annotation_tags';
  $handler->display->display_options['fields']['field_annotation_tags']['type'] = 'taxonomy_term_reference_plain';
  $handler->display->display_options['fields']['field_annotation_tags']['delta_offset'] = '0';
  /* Field: Content: Category */
  $handler->display->display_options['fields']['field_annotation_category']['id'] = 'field_annotation_category';
  $handler->display->display_options['fields']['field_annotation_category']['table'] = 'field_data_field_annotation_category';
  $handler->display->display_options['fields']['field_annotation_category']['field'] = 'field_annotation_category';
  $handler->display->display_options['fields']['field_annotation_category']['type'] = 'taxonomy_term_reference_plain';
  $handler->display->display_options['path'] = 'export/annotations';
  $export['sewing-kit'] = $view;

  $view = new view();
  $view->name = 'stitchings';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Stitchings';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Stitchings';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'draggableviews' => 'draggableviews',
    'name' => 'name',
    'field_annotation_reference' => 'field_annotation_reference',
    'field_annotation_quote' => 'field_annotation_quote',
    'field_annotation_text' => 'field_annotation_text',
    'field_annotation_category' => 'field_annotation_category',
    'field_annotation_tags' => 'field_annotation_tags',
    'nid' => 'nid',
    'path' => 'path',
    'nothing' => 'nothing',
  );
  $handler->display->display_options['style_options']['default'] = 'field_annotation_reference';
  $handler->display->display_options['style_options']['info'] = array(
    'draggableviews' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'name' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_annotation_reference' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_annotation_quote' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_annotation_text' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_annotation_category' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_annotation_tags' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'nid' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'path' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'nothing' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Relationship: Thread */
  $handler->display->display_options['relationships']['reverse_thread_reference_node']['id'] = 'reverse_thread_reference_node';
  $handler->display->display_options['relationships']['reverse_thread_reference_node']['table'] = 'node';
  $handler->display->display_options['relationships']['reverse_thread_reference_node']['field'] = 'reverse_thread_reference_node';
  $handler->display->display_options['relationships']['reverse_thread_reference_node']['ui_name'] = 'Thread';
  $handler->display->display_options['relationships']['reverse_thread_reference_node']['label'] = 'Thread';
  /* Relationship: Annotated Content */
  $handler->display->display_options['relationships']['field_annotation_reference_target_id']['id'] = 'field_annotation_reference_target_id';
  $handler->display->display_options['relationships']['field_annotation_reference_target_id']['table'] = 'field_data_field_annotation_reference';
  $handler->display->display_options['relationships']['field_annotation_reference_target_id']['field'] = 'field_annotation_reference_target_id';
  $handler->display->display_options['relationships']['field_annotation_reference_target_id']['ui_name'] = 'Annotated Content';
  $handler->display->display_options['relationships']['field_annotation_reference_target_id']['label'] = 'Annotated Content';
  /* Relationship: Content: Author */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'node';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  /* Field: Draggableviews: Content */
  $handler->display->display_options['fields']['draggableviews']['id'] = 'draggableviews';
  $handler->display->display_options['fields']['draggableviews']['table'] = 'node';
  $handler->display->display_options['fields']['draggableviews']['field'] = 'draggableviews';
  $handler->display->display_options['fields']['draggableviews']['label'] = '';
  $handler->display->display_options['fields']['draggableviews']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['draggableviews']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['draggableviews']['hide_alter_empty'] = FALSE;
  $handler->display->display_options['fields']['draggableviews']['draggableviews']['ajax'] = 1;
  /* Field: User: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'uid';
  $handler->display->display_options['fields']['name']['label'] = 'Annotator';
  /* Field: Content: Annotated Content */
  $handler->display->display_options['fields']['field_annotation_reference']['id'] = 'field_annotation_reference';
  $handler->display->display_options['fields']['field_annotation_reference']['table'] = 'field_data_field_annotation_reference';
  $handler->display->display_options['fields']['field_annotation_reference']['field'] = 'field_annotation_reference';
  $handler->display->display_options['fields']['field_annotation_reference']['settings'] = array(
    'link' => 1,
  );
  /* Field: Content: Excerpt */
  $handler->display->display_options['fields']['field_annotation_quote']['id'] = 'field_annotation_quote';
  $handler->display->display_options['fields']['field_annotation_quote']['table'] = 'field_data_field_annotation_quote';
  $handler->display->display_options['fields']['field_annotation_quote']['field'] = 'field_annotation_quote';
  $handler->display->display_options['fields']['field_annotation_quote']['alter']['max_length'] = '200';
  $handler->display->display_options['fields']['field_annotation_quote']['alter']['trim'] = TRUE;
  $handler->display->display_options['fields']['field_annotation_quote']['element_class'] = 'fix-width-15';
  $handler->display->display_options['fields']['field_annotation_quote']['type'] = 'text_plain';
  $handler->display->display_options['fields']['field_annotation_quote']['settings'] = array(
    'trim_length' => '600',
  );
  /* Field: Content: Annotation Text */
  $handler->display->display_options['fields']['field_annotation_text']['id'] = 'field_annotation_text';
  $handler->display->display_options['fields']['field_annotation_text']['table'] = 'field_data_field_annotation_text';
  $handler->display->display_options['fields']['field_annotation_text']['field'] = 'field_annotation_text';
  $handler->display->display_options['fields']['field_annotation_text']['element_class'] = 'fix-width-15';
  $handler->display->display_options['fields']['field_annotation_text']['type'] = 'text_plain';
  /* Field: Content: Category */
  $handler->display->display_options['fields']['field_annotation_category']['id'] = 'field_annotation_category';
  $handler->display->display_options['fields']['field_annotation_category']['table'] = 'field_data_field_annotation_category';
  $handler->display->display_options['fields']['field_annotation_category']['field'] = 'field_annotation_category';
  $handler->display->display_options['fields']['field_annotation_category']['type'] = 'taxonomy_term_reference_plain';
  /* Field: Content: Tags */
  $handler->display->display_options['fields']['field_annotation_tags']['id'] = 'field_annotation_tags';
  $handler->display->display_options['fields']['field_annotation_tags']['table'] = 'field_data_field_annotation_tags';
  $handler->display->display_options['fields']['field_annotation_tags']['field'] = 'field_annotation_tags';
  $handler->display->display_options['fields']['field_annotation_tags']['type'] = 'taxonomy_term_reference_plain';
  $handler->display->display_options['fields']['field_annotation_tags']['delta_offset'] = '0';
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  /* Field: Content: Path */
  $handler->display->display_options['fields']['path']['id'] = 'path';
  $handler->display->display_options['fields']['path']['table'] = 'node';
  $handler->display->display_options['fields']['path']['field'] = 'path';
  $handler->display->display_options['fields']['path']['relationship'] = 'field_annotation_reference_target_id';
  $handler->display->display_options['fields']['path']['exclude'] = TRUE;
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['label'] = '';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = '<a class="fa fa-eye" href="[path]?id=[nid]" target="_blank"></a>';
  $handler->display->display_options['fields']['nothing']['alter']['absolute'] = TRUE;
  $handler->display->display_options['fields']['nothing']['alter']['target'] = '_blank';
  $handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
  /* Sort criterion: Draggableviews: Weight */
  $handler->display->display_options['sorts']['weight']['id'] = 'weight';
  $handler->display->display_options['sorts']['weight']['table'] = 'draggableviews_structure';
  $handler->display->display_options['sorts']['weight']['field'] = 'weight';
  $handler->display->display_options['sorts']['weight']['draggableviews_setting_view'] = 'stitchings:block';
  $handler->display->display_options['sorts']['weight']['draggableviews_setting_new_items_bottom_list'] = 1;
  /* Contextual filter: Content: Nid */
  $handler->display->display_options['arguments']['nid']['id'] = 'nid';
  $handler->display->display_options['arguments']['nid']['table'] = 'node';
  $handler->display->display_options['arguments']['nid']['field'] = 'nid';
  $handler->display->display_options['arguments']['nid']['relationship'] = 'reverse_thread_reference_node';
  $handler->display->display_options['arguments']['nid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['nid']['default_argument_type'] = 'node';
  $handler->display->display_options['arguments']['nid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['nid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['nid']['summary_options']['items_per_page'] = '25';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'annotation' => 'annotation',
  );

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block');
  $export['stitchings'] = $view;

  $view = new view();
  $view->name = 'threads';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Threads';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Threads';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['group_by'] = TRUE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'create thread content';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['reset_button'] = TRUE;
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = 'View All';
  $handler->display->display_options['exposed_form']['options']['autosubmit'] = TRUE;
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '25';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'title' => 'title',
    'name' => 'name',
    'nid' => 'nid',
    'thread_description' => 'thread_description',
    'created' => 'created',
  );
  $handler->display->display_options['style_options']['default'] = 'created';
  $handler->display->display_options['style_options']['info'] = array(
    'title' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'name' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'nid' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'thread_description' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'created' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = TRUE;
  $handler->display->display_options['empty']['area']['content'] = 'No threads have been created for this course yet. How sad. Why don\'t you create one?';
  $handler->display->display_options['empty']['area']['format'] = 'filtered_html';
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['thread_reference_target_id']['id'] = 'thread_reference_target_id';
  $handler->display->display_options['relationships']['thread_reference_target_id']['table'] = 'field_data_thread_reference';
  $handler->display->display_options['relationships']['thread_reference_target_id']['field'] = 'thread_reference_target_id';
  $handler->display->display_options['relationships']['thread_reference_target_id']['label'] = 'Stitching';
  /* Relationship: Content: Author */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'node';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: User: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'uid';
  $handler->display->display_options['fields']['name']['label'] = 'Author';
  /* Field: COUNT(DISTINCT Content: Nid) */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['relationship'] = 'thread_reference_target_id';
  $handler->display->display_options['fields']['nid']['group_type'] = 'count_distinct';
  $handler->display->display_options['fields']['nid']['label'] = 'Stitchings';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  /* Field: Content: Description */
  $handler->display->display_options['fields']['thread_description']['id'] = 'thread_description';
  $handler->display->display_options['fields']['thread_description']['table'] = 'field_data_thread_description';
  $handler->display->display_options['fields']['thread_description']['field'] = 'thread_description';
  $handler->display->display_options['fields']['thread_description']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['thread_description']['alter']['text'] = '[thread_description] ([nid] stitchings)';
  $handler->display->display_options['fields']['thread_description']['alter']['max_length'] = '300';
  $handler->display->display_options['fields']['thread_description']['alter']['trim'] = TRUE;
  $handler->display->display_options['fields']['thread_description']['type'] = 'text_plain';
  /* Field: Content: Post date */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'node';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['date_format'] = 'short';
  $handler->display->display_options['fields']['created']['second_date_format'] = 'long';
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'thread' => 'thread',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  /* Filter criterion: Content: Author (select list) */
  $handler->display->display_options['filters']['author_select']['id'] = 'author_select';
  $handler->display->display_options['filters']['author_select']['table'] = 'node';
  $handler->display->display_options['filters']['author_select']['field'] = 'author_select';
  $handler->display->display_options['filters']['author_select']['exposed'] = TRUE;
  $handler->display->display_options['filters']['author_select']['expose']['operator_id'] = 'author_select_op';
  $handler->display->display_options['filters']['author_select']['expose']['label'] = 'Limit by Author';
  $handler->display->display_options['filters']['author_select']['expose']['operator'] = 'author_select_op';
  $handler->display->display_options['filters']['author_select']['expose']['identifier'] = 'author_select';
  $handler->display->display_options['filters']['author_select']['expose']['multiple'] = TRUE;
  $handler->display->display_options['filters']['author_select']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    5 => 0,
    3 => 0,
    4 => 0,
    6 => 0,
    7 => 0,
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'threads';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Threads';
  $handler->display->display_options['menu']['name'] = 'main-menu';
  $export['threads'] = $view;

  return $export;
}
