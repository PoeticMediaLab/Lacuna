<?php
/**
 * @file
 * lacuna_stories_materials.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function lacuna_stories_materials_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'documents';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Materials';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Materials';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'role';
  $handler->display->display_options['access']['role'] = array(
    3 => '3',
    4 => '4',
    5 => '5',
    6 => '6',
    7 => '7',
  );
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['reset_button'] = TRUE;
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = 'View All';
  $handler->display->display_options['exposed_form']['options']['autosubmit'] = TRUE;
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['style_options']['grouping'] = array(
    0 => array(
      'field' => 'field_unit',
      'rendered' => 1,
      'rendered_strip' => 0,
    ),
  );
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['inline'] = array(
    'views_bulk_operations' => 'views_bulk_operations',
    'field_image' => 'field_image',
  );
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = TRUE;
  $handler->display->display_options['empty']['area']['content'] = 'No results found for these limits. If you have materials you\'d like to suggest, please <a href="mailto:info@lacunastories.com">contact the Lacuna Stories team</a>.';
  $handler->display->display_options['empty']['area']['format'] = 'filtered_html';
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_bibliographic_entry_target_id']['id'] = 'field_bibliographic_entry_target_id';
  $handler->display->display_options['relationships']['field_bibliographic_entry_target_id']['table'] = 'field_data_field_bibliographic_entry';
  $handler->display->display_options['relationships']['field_bibliographic_entry_target_id']['field'] = 'field_bibliographic_entry_target_id';
  $handler->display->display_options['relationships']['field_bibliographic_entry_target_id']['label'] = 'Biblio';
  /* Relationship: Content: Taxonomy terms on node */
  $handler->display->display_options['relationships']['term_node_tid']['id'] = 'term_node_tid';
  $handler->display->display_options['relationships']['term_node_tid']['table'] = 'node';
  $handler->display->display_options['relationships']['term_node_tid']['field'] = 'term_node_tid';
  $handler->display->display_options['relationships']['term_node_tid']['label'] = 'units';
  $handler->display->display_options['relationships']['term_node_tid']['vocabularies'] = array(
    'units' => 'units',
    'copyright_status' => 0,
    'genre_doc' => 0,
    'genre_response' => 0,
    'medium' => 0,
    'priority' => 0,
    'tags' => 0,
    'annotation_categories' => 0,
    'annotation_tags' => 0,
  );
  /* Field: Content: Path */
  $handler->display->display_options['fields']['path']['id'] = 'path';
  $handler->display->display_options['fields']['path']['table'] = 'node';
  $handler->display->display_options['fields']['path']['field'] = 'path';
  $handler->display->display_options['fields']['path']['relationship'] = 'field_bibliographic_entry_target_id';
  $handler->display->display_options['fields']['path']['label'] = '';
  $handler->display->display_options['fields']['path']['exclude'] = TRUE;
  $handler->display->display_options['fields']['path']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['path']['absolute'] = TRUE;
  /* Field: Content: Path */
  $handler->display->display_options['fields']['path_1']['id'] = 'path_1';
  $handler->display->display_options['fields']['path_1']['table'] = 'node';
  $handler->display->display_options['fields']['path_1']['field'] = 'path';
  $handler->display->display_options['fields']['path_1']['label'] = '';
  $handler->display->display_options['fields']['path_1']['exclude'] = TRUE;
  $handler->display->display_options['fields']['path_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['path_1']['absolute'] = TRUE;
  /* Field: Content: Image */
  $handler->display->display_options['fields']['field_image']['id'] = 'field_image';
  $handler->display->display_options['fields']['field_image']['table'] = 'field_data_field_image';
  $handler->display->display_options['fields']['field_image']['field'] = 'field_image';
  $handler->display->display_options['fields']['field_image']['label'] = '';
  $handler->display->display_options['fields']['field_image']['alter']['path'] = '[path_1]';
  $handler->display->display_options['fields']['field_image']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_image']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['field_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_image']['settings'] = array(
    'image_style' => 'thumbnails_for_browsing',
    'image_link' => 'content',
  );
  $handler->display->display_options['fields']['field_image']['delta_offset'] = '0';
  /* Field: Content: Link */
  $handler->display->display_options['fields']['view_node']['id'] = 'view_node';
  $handler->display->display_options['fields']['view_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['view_node']['field'] = 'view_node';
  $handler->display->display_options['fields']['view_node']['label'] = '';
  $handler->display->display_options['fields']['view_node']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['view_node']['alter']['text'] = 'Read and Annotate';
  $handler->display->display_options['fields']['view_node']['element_type'] = 'div';
  $handler->display->display_options['fields']['view_node']['element_class'] = 'lacuna-button';
  $handler->display->display_options['fields']['view_node']['element_label_colon'] = FALSE;
  /* Field: Biblio: Abstract */
  $handler->display->display_options['fields']['biblio_abst_e']['id'] = 'biblio_abst_e';
  $handler->display->display_options['fields']['biblio_abst_e']['table'] = 'biblio';
  $handler->display->display_options['fields']['biblio_abst_e']['field'] = 'biblio_abst_e';
  $handler->display->display_options['fields']['biblio_abst_e']['relationship'] = 'field_bibliographic_entry_target_id';
  $handler->display->display_options['fields']['biblio_abst_e']['exclude'] = TRUE;
  $handler->display->display_options['fields']['biblio_abst_e']['alter']['max_length'] = '600';
  $handler->display->display_options['fields']['biblio_abst_e']['alter']['trim'] = TRUE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['exclude'] = TRUE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Field: Biblio: Short Title */
  $handler->display->display_options['fields']['biblio_short_title']['id'] = 'biblio_short_title';
  $handler->display->display_options['fields']['biblio_short_title']['table'] = 'biblio';
  $handler->display->display_options['fields']['biblio_short_title']['field'] = 'biblio_short_title';
  $handler->display->display_options['fields']['biblio_short_title']['relationship'] = 'field_bibliographic_entry_target_id';
  $handler->display->display_options['fields']['biblio_short_title']['label'] = '';
  $handler->display->display_options['fields']['biblio_short_title']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['biblio_short_title']['alter']['path'] = '[path_1]';
  $handler->display->display_options['fields']['biblio_short_title']['alter']['absolute'] = TRUE;
  $handler->display->display_options['fields']['biblio_short_title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['biblio_short_title']['empty'] = '<a href="[path_1]">[title]</a>';
  $handler->display->display_options['fields']['biblio_short_title']['biblio_label'] = 0;
  /* Field: Biblio: Year of Publication */
  $handler->display->display_options['fields']['biblio_year']['id'] = 'biblio_year';
  $handler->display->display_options['fields']['biblio_year']['table'] = 'biblio';
  $handler->display->display_options['fields']['biblio_year']['field'] = 'biblio_year';
  $handler->display->display_options['fields']['biblio_year']['relationship'] = 'field_bibliographic_entry_target_id';
  $handler->display->display_options['fields']['biblio_year']['label'] = '';
  $handler->display->display_options['fields']['biblio_year']['exclude'] = TRUE;
  $handler->display->display_options['fields']['biblio_year']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['biblio_year']['alter']['text'] = '([biblio_year])';
  $handler->display->display_options['fields']['biblio_year']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['biblio_year']['biblio_label'] = 0;
  /* Field: Biblio: Authors */
  $handler->display->display_options['fields']['biblio_authors']['id'] = 'biblio_authors';
  $handler->display->display_options['fields']['biblio_authors']['table'] = 'biblio';
  $handler->display->display_options['fields']['biblio_authors']['field'] = 'biblio_authors';
  $handler->display->display_options['fields']['biblio_authors']['relationship'] = 'field_bibliographic_entry_target_id';
  $handler->display->display_options['fields']['biblio_authors']['label'] = '';
  $handler->display->display_options['fields']['biblio_authors']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['biblio_authors']['alter']['text'] = '[biblio_authors] [biblio_year]';
  $handler->display->display_options['fields']['biblio_authors']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['biblio_authors']['biblio_label'] = 0;
  $handler->display->display_options['fields']['biblio_authors']['auth_category'] = '1';
  $handler->display->display_options['fields']['biblio_authors']['initialize'] = 0;
  /* Field: Content: Unit */
  $handler->display->display_options['fields']['field_unit']['id'] = 'field_unit';
  $handler->display->display_options['fields']['field_unit']['table'] = 'field_data_field_unit';
  $handler->display->display_options['fields']['field_unit']['field'] = 'field_unit';
  $handler->display->display_options['fields']['field_unit']['type'] = 'taxonomy_term_reference_plain';
  /* Field: Content: Priority */
  $handler->display->display_options['fields']['field_priority']['id'] = 'field_priority';
  $handler->display->display_options['fields']['field_priority']['table'] = 'field_data_field_priority';
  $handler->display->display_options['fields']['field_priority']['field'] = 'field_priority';
  $handler->display->display_options['fields']['field_priority']['type'] = 'taxonomy_term_reference_plain';
  /* Sort criterion: Global: Random */
  $handler->display->display_options['sorts']['random']['id'] = 'random';
  $handler->display->display_options['sorts']['random']['table'] = 'views';
  $handler->display->display_options['sorts']['random']['field'] = 'random';
  $handler->display->display_options['sorts']['random']['exposed'] = TRUE;
  $handler->display->display_options['sorts']['random']['expose']['label'] = 'Random';
  /* Sort criterion: Biblio: Year of Publication */
  $handler->display->display_options['sorts']['biblio_year']['id'] = 'biblio_year';
  $handler->display->display_options['sorts']['biblio_year']['table'] = 'biblio';
  $handler->display->display_options['sorts']['biblio_year']['field'] = 'biblio_year';
  $handler->display->display_options['sorts']['biblio_year']['relationship'] = 'field_bibliographic_entry_target_id';
  $handler->display->display_options['sorts']['biblio_year']['order'] = 'DESC';
  $handler->display->display_options['sorts']['biblio_year']['exposed'] = TRUE;
  $handler->display->display_options['sorts']['biblio_year']['expose']['label'] = 'Year of Publication';
  /* Sort criterion: Biblio: Sort Title */
  $handler->display->display_options['sorts']['biblio_sort_title']['id'] = 'biblio_sort_title';
  $handler->display->display_options['sorts']['biblio_sort_title']['table'] = 'biblio';
  $handler->display->display_options['sorts']['biblio_sort_title']['field'] = 'biblio_sort_title';
  $handler->display->display_options['sorts']['biblio_sort_title']['relationship'] = 'field_bibliographic_entry_target_id';
  $handler->display->display_options['sorts']['biblio_sort_title']['exposed'] = TRUE;
  $handler->display->display_options['sorts']['biblio_sort_title']['expose']['label'] = 'Title';
  $handler->display->display_options['filter_groups']['operator'] = 'OR';
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type_1']['id'] = 'type_1';
  $handler->display->display_options['filters']['type_1']['table'] = 'node';
  $handler->display->display_options['filters']['type_1']['field'] = 'type';
  $handler->display->display_options['filters']['type_1']['value'] = array(
    'audio' => 'audio',
    'document' => 'document',
    'image' => 'image',
    'music_video' => 'music_video',
    'video' => 'video',
  );
  $handler->display->display_options['filters']['type_1']['group'] = 1;
  $handler->display->display_options['filters']['type_1']['expose']['operator_id'] = 'type_1_op';
  $handler->display->display_options['filters']['type_1']['expose']['label'] = 'Type';
  $handler->display->display_options['filters']['type_1']['expose']['operator'] = 'type_1_op';
  $handler->display->display_options['filters']['type_1']['expose']['identifier'] = 'type_1';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Genre (field_doc_genre) */
  $handler->display->display_options['filters']['field_doc_genre_tid']['id'] = 'field_doc_genre_tid';
  $handler->display->display_options['filters']['field_doc_genre_tid']['table'] = 'field_data_field_doc_genre';
  $handler->display->display_options['filters']['field_doc_genre_tid']['field'] = 'field_doc_genre_tid';
  $handler->display->display_options['filters']['field_doc_genre_tid']['group'] = 1;
  $handler->display->display_options['filters']['field_doc_genre_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_doc_genre_tid']['expose']['operator_id'] = 'field_doc_genre_tid_op';
  $handler->display->display_options['filters']['field_doc_genre_tid']['expose']['label'] = 'Limit by Genre';
  $handler->display->display_options['filters']['field_doc_genre_tid']['expose']['operator'] = 'field_doc_genre_tid_op';
  $handler->display->display_options['filters']['field_doc_genre_tid']['expose']['identifier'] = 'field_doc_genre_tid';
  $handler->display->display_options['filters']['field_doc_genre_tid']['expose']['remember'] = TRUE;
  $handler->display->display_options['filters']['field_doc_genre_tid']['expose']['multiple'] = TRUE;
  $handler->display->display_options['filters']['field_doc_genre_tid']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
  );
  $handler->display->display_options['filters']['field_doc_genre_tid']['reduce_duplicates'] = TRUE;
  $handler->display->display_options['filters']['field_doc_genre_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_doc_genre_tid']['vocabulary'] = 'genre_doc';
  $handler->display->display_options['filters']['field_doc_genre_tid']['error_message'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'audio' => 'audio',
    'document' => 'document',
    'image' => 'image',
    'video' => 'video',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  $handler->display->display_options['filters']['type']['exposed'] = TRUE;
  $handler->display->display_options['filters']['type']['expose']['operator_id'] = 'type_op';
  $handler->display->display_options['filters']['type']['expose']['label'] = 'Limit by Medium';
  $handler->display->display_options['filters']['type']['expose']['operator'] = 'type_op';
  $handler->display->display_options['filters']['type']['expose']['identifier'] = 'type';
  $handler->display->display_options['filters']['type']['expose']['remember'] = TRUE;
  $handler->display->display_options['filters']['type']['expose']['multiple'] = TRUE;
  $handler->display->display_options['filters']['type']['expose']['remember_roles'] = array(
    2 => '2',
    1 => '1',
    3 => '3',
    4 => '4',
    5 => 0,
  );
  $handler->display->display_options['filters']['type']['expose']['reduce'] = TRUE;
  /* Filter criterion: Workflow current: New state name */
  $handler->display->display_options['filters']['sid']['id'] = 'sid';
  $handler->display->display_options['filters']['sid']['table'] = 'workflow_node_current';
  $handler->display->display_options['filters']['sid']['field'] = 'sid';
  $handler->display->display_options['filters']['sid']['value'] = array(
    3 => '3',
  );

  /* Display: Materials */
  $handler = $view->new_display('page', 'Materials', 'materials');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Materials';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Unit */
  $handler->display->display_options['fields']['field_unit']['id'] = 'field_unit';
  $handler->display->display_options['fields']['field_unit']['table'] = 'field_data_field_unit';
  $handler->display->display_options['fields']['field_unit']['field'] = 'field_unit';
  $handler->display->display_options['fields']['field_unit']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_unit']['type'] = 'taxonomy_term_reference_plain';
  /* Field: Content: Path */
  $handler->display->display_options['fields']['path_1']['id'] = 'path_1';
  $handler->display->display_options['fields']['path_1']['table'] = 'node';
  $handler->display->display_options['fields']['path_1']['field'] = 'path';
  $handler->display->display_options['fields']['path_1']['label'] = '';
  $handler->display->display_options['fields']['path_1']['exclude'] = TRUE;
  $handler->display->display_options['fields']['path_1']['alter']['path'] = '[path]';
  $handler->display->display_options['fields']['path_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['path_1']['absolute'] = TRUE;
  /* Field: Content: Image */
  $handler->display->display_options['fields']['field_image']['id'] = 'field_image';
  $handler->display->display_options['fields']['field_image']['table'] = 'field_data_field_image';
  $handler->display->display_options['fields']['field_image']['field'] = 'field_image';
  $handler->display->display_options['fields']['field_image']['label'] = '';
  $handler->display->display_options['fields']['field_image']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_image']['settings'] = array(
    'image_style' => 'thumbnails_for_browsing',
    'image_link' => 'content',
  );
  /* Field: Content: Link */
  $handler->display->display_options['fields']['view_node']['id'] = 'view_node';
  $handler->display->display_options['fields']['view_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['view_node']['field'] = 'view_node';
  $handler->display->display_options['fields']['view_node']['label'] = '';
  $handler->display->display_options['fields']['view_node']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['view_node']['alter']['text'] = 'Read and Annotate';
  $handler->display->display_options['fields']['view_node']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['view_node']['alter']['link_class'] = 'lacuna-button';
  $handler->display->display_options['fields']['view_node']['element_label_colon'] = FALSE;
  /* Field: Content: Priority */
  $handler->display->display_options['fields']['field_priority']['id'] = 'field_priority';
  $handler->display->display_options['fields']['field_priority']['table'] = 'field_data_field_priority';
  $handler->display->display_options['fields']['field_priority']['field'] = 'field_priority';
  $handler->display->display_options['fields']['field_priority']['label'] = '';
  $handler->display->display_options['fields']['field_priority']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_priority']['type'] = 'taxonomy_term_reference_plain';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['exclude'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['max_length'] = '50';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['trim'] = TRUE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Field: Biblio: Short Title */
  $handler->display->display_options['fields']['biblio_short_title']['id'] = 'biblio_short_title';
  $handler->display->display_options['fields']['biblio_short_title']['table'] = 'biblio';
  $handler->display->display_options['fields']['biblio_short_title']['field'] = 'biblio_short_title';
  $handler->display->display_options['fields']['biblio_short_title']['relationship'] = 'field_bibliographic_entry_target_id';
  $handler->display->display_options['fields']['biblio_short_title']['label'] = '';
  $handler->display->display_options['fields']['biblio_short_title']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['biblio_short_title']['alter']['path'] = '[path_1]';
  $handler->display->display_options['fields']['biblio_short_title']['alter']['absolute'] = TRUE;
  $handler->display->display_options['fields']['biblio_short_title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['biblio_short_title']['empty'] = '<a href="[path_1]">[title]</a>';
  $handler->display->display_options['fields']['biblio_short_title']['biblio_label'] = 0;
  /* Field: Biblio: Year of Publication */
  $handler->display->display_options['fields']['biblio_year']['id'] = 'biblio_year';
  $handler->display->display_options['fields']['biblio_year']['table'] = 'biblio';
  $handler->display->display_options['fields']['biblio_year']['field'] = 'biblio_year';
  $handler->display->display_options['fields']['biblio_year']['relationship'] = 'field_bibliographic_entry_target_id';
  $handler->display->display_options['fields']['biblio_year']['label'] = '';
  $handler->display->display_options['fields']['biblio_year']['exclude'] = TRUE;
  $handler->display->display_options['fields']['biblio_year']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['biblio_year']['alter']['text'] = '([biblio_year])';
  $handler->display->display_options['fields']['biblio_year']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['biblio_year']['biblio_label'] = 0;
  /* Field: Biblio: Authors */
  $handler->display->display_options['fields']['biblio_authors']['id'] = 'biblio_authors';
  $handler->display->display_options['fields']['biblio_authors']['table'] = 'biblio';
  $handler->display->display_options['fields']['biblio_authors']['field'] = 'biblio_authors';
  $handler->display->display_options['fields']['biblio_authors']['relationship'] = 'field_bibliographic_entry_target_id';
  $handler->display->display_options['fields']['biblio_authors']['label'] = '';
  $handler->display->display_options['fields']['biblio_authors']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['biblio_authors']['alter']['text'] = '[biblio_authors] [biblio_year]';
  $handler->display->display_options['fields']['biblio_authors']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['biblio_authors']['biblio_label'] = 0;
  $handler->display->display_options['fields']['biblio_authors']['auth_category'] = '1';
  $handler->display->display_options['fields']['biblio_authors']['initialize'] = 0;
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: Taxonomy term: Weight */
  $handler->display->display_options['sorts']['weight']['id'] = 'weight';
  $handler->display->display_options['sorts']['weight']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['sorts']['weight']['field'] = 'weight';
  $handler->display->display_options['sorts']['weight']['relationship'] = 'term_node_tid';
  /* Sort criterion: Content: Priority (field_priority) */
  $handler->display->display_options['sorts']['field_priority_tid']['id'] = 'field_priority_tid';
  $handler->display->display_options['sorts']['field_priority_tid']['table'] = 'field_data_field_priority';
  $handler->display->display_options['sorts']['field_priority_tid']['field'] = 'field_priority_tid';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['filter_groups']['operator'] = 'OR';
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type_1']['id'] = 'type_1';
  $handler->display->display_options['filters']['type_1']['table'] = 'node';
  $handler->display->display_options['filters']['type_1']['field'] = 'type';
  $handler->display->display_options['filters']['type_1']['value'] = array(
    'document' => 'document',
  );
  $handler->display->display_options['filters']['type_1']['group'] = 1;
  $handler->display->display_options['filters']['type_1']['expose']['operator_id'] = 'type_1_op';
  $handler->display->display_options['filters']['type_1']['expose']['label'] = 'Type';
  $handler->display->display_options['filters']['type_1']['expose']['operator'] = 'type_1_op';
  $handler->display->display_options['filters']['type_1']['expose']['identifier'] = 'type_1';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Workflow current: New state name */
  $handler->display->display_options['filters']['sid']['id'] = 'sid';
  $handler->display->display_options['filters']['sid']['table'] = 'workflow_node_current';
  $handler->display->display_options['filters']['sid']['field'] = 'sid';
  $handler->display->display_options['filters']['sid']['value'] = array(
    3 => '3',
  );
  $handler->display->display_options['filters']['sid']['group'] = 1;
  /* Filter criterion: Content: Unit (field_unit) */
  $handler->display->display_options['filters']['field_unit_tid']['id'] = 'field_unit_tid';
  $handler->display->display_options['filters']['field_unit_tid']['table'] = 'field_data_field_unit';
  $handler->display->display_options['filters']['field_unit_tid']['field'] = 'field_unit_tid';
  $handler->display->display_options['filters']['field_unit_tid']['group'] = 1;
  $handler->display->display_options['filters']['field_unit_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_unit_tid']['expose']['operator_id'] = 'field_unit_tid_op';
  $handler->display->display_options['filters']['field_unit_tid']['expose']['label'] = 'Limit by Unit';
  $handler->display->display_options['filters']['field_unit_tid']['expose']['operator'] = 'field_unit_tid_op';
  $handler->display->display_options['filters']['field_unit_tid']['expose']['identifier'] = 'field_unit_tid';
  $handler->display->display_options['filters']['field_unit_tid']['expose']['multiple'] = TRUE;
  $handler->display->display_options['filters']['field_unit_tid']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    5 => 0,
    3 => 0,
    4 => 0,
    6 => 0,
    7 => 0,
  );
  $handler->display->display_options['filters']['field_unit_tid']['reduce_duplicates'] = TRUE;
  $handler->display->display_options['filters']['field_unit_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_unit_tid']['vocabulary'] = 'units';
  $handler->display->display_options['filters']['field_unit_tid']['error_message'] = FALSE;
  /* Filter criterion: Content: Genre (field_doc_genre) */
  $handler->display->display_options['filters']['field_doc_genre_tid']['id'] = 'field_doc_genre_tid';
  $handler->display->display_options['filters']['field_doc_genre_tid']['table'] = 'field_data_field_doc_genre';
  $handler->display->display_options['filters']['field_doc_genre_tid']['field'] = 'field_doc_genre_tid';
  $handler->display->display_options['filters']['field_doc_genre_tid']['group'] = 1;
  $handler->display->display_options['filters']['field_doc_genre_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_doc_genre_tid']['expose']['operator_id'] = 'field_doc_genre_tid_op';
  $handler->display->display_options['filters']['field_doc_genre_tid']['expose']['label'] = 'Limit by Genre';
  $handler->display->display_options['filters']['field_doc_genre_tid']['expose']['operator'] = 'field_doc_genre_tid_op';
  $handler->display->display_options['filters']['field_doc_genre_tid']['expose']['identifier'] = 'field_doc_genre_tid';
  $handler->display->display_options['filters']['field_doc_genre_tid']['expose']['multiple'] = TRUE;
  $handler->display->display_options['filters']['field_doc_genre_tid']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
  );
  $handler->display->display_options['filters']['field_doc_genre_tid']['reduce_duplicates'] = TRUE;
  $handler->display->display_options['filters']['field_doc_genre_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_doc_genre_tid']['vocabulary'] = 'genre_doc';
  $handler->display->display_options['filters']['field_doc_genre_tid']['error_message'] = FALSE;
  /* Filter criterion: Content: Medium (field_medium) */
  $handler->display->display_options['filters']['field_medium_tid']['id'] = 'field_medium_tid';
  $handler->display->display_options['filters']['field_medium_tid']['table'] = 'field_data_field_medium';
  $handler->display->display_options['filters']['field_medium_tid']['field'] = 'field_medium_tid';
  $handler->display->display_options['filters']['field_medium_tid']['group'] = 1;
  $handler->display->display_options['filters']['field_medium_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_medium_tid']['expose']['operator_id'] = 'field_medium_tid_op';
  $handler->display->display_options['filters']['field_medium_tid']['expose']['label'] = 'Limit by Media';
  $handler->display->display_options['filters']['field_medium_tid']['expose']['operator'] = 'field_medium_tid_op';
  $handler->display->display_options['filters']['field_medium_tid']['expose']['identifier'] = 'field_medium_tid';
  $handler->display->display_options['filters']['field_medium_tid']['expose']['multiple'] = TRUE;
  $handler->display->display_options['filters']['field_medium_tid']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
  );
  $handler->display->display_options['filters']['field_medium_tid']['reduce_duplicates'] = TRUE;
  $handler->display->display_options['filters']['field_medium_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_medium_tid']['vocabulary'] = 'medium';
  $handler->display->display_options['filters']['field_medium_tid']['hierarchy'] = 1;
  $handler->display->display_options['filters']['field_medium_tid']['error_message'] = FALSE;
  /* Filter criterion: Biblio: Author last name */
  $handler->display->display_options['filters']['lastname']['id'] = 'lastname';
  $handler->display->display_options['filters']['lastname']['table'] = 'biblio_contributor_data';
  $handler->display->display_options['filters']['lastname']['field'] = 'lastname';
  $handler->display->display_options['filters']['lastname']['relationship'] = 'field_bibliographic_entry_target_id';
  $handler->display->display_options['filters']['lastname']['group'] = 1;
  $handler->display->display_options['filters']['lastname']['exposed'] = TRUE;
  $handler->display->display_options['filters']['lastname']['expose']['operator_id'] = 'lastname_op';
  $handler->display->display_options['filters']['lastname']['expose']['label'] = 'Limit by Author';
  $handler->display->display_options['filters']['lastname']['expose']['operator'] = 'lastname_op';
  $handler->display->display_options['filters']['lastname']['expose']['identifier'] = 'lastname';
  $handler->display->display_options['filters']['lastname']['expose']['multiple'] = TRUE;
  $handler->display->display_options['filters']['lastname']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    5 => 0,
    3 => 0,
    4 => 0,
    6 => 0,
    7 => 0,
  );
  $handler->display->display_options['filters']['lastname']['reduce_duplicates'] = TRUE;
  $handler->display->display_options['path'] = 'materials';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Materials';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'main-menu';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'course_block');
  $handler->display->display_options['defaults']['access'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['inline'] = array(
    'views_bulk_operations' => 'views_bulk_operations',
    'field_image' => 'field_image',
  );
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['empty'] = FALSE;
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = TRUE;
  $handler->display->display_options['empty']['area']['format'] = 'filtered_html';
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: Biblio: Sort Title */
  $handler->display->display_options['sorts']['biblio_sort_title']['id'] = 'biblio_sort_title';
  $handler->display->display_options['sorts']['biblio_sort_title']['table'] = 'biblio';
  $handler->display->display_options['sorts']['biblio_sort_title']['field'] = 'biblio_sort_title';
  $handler->display->display_options['sorts']['biblio_sort_title']['relationship'] = 'field_bibliographic_entry_target_id';
  $handler->display->display_options['sorts']['biblio_sort_title']['expose']['label'] = 'Title';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['filter_groups']['operator'] = 'OR';
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type_1']['id'] = 'type_1';
  $handler->display->display_options['filters']['type_1']['table'] = 'node';
  $handler->display->display_options['filters']['type_1']['field'] = 'type';
  $handler->display->display_options['filters']['type_1']['value'] = array(
    'audio' => 'audio',
    'document' => 'document',
    'image' => 'image',
    'music_video' => 'music_video',
    'video' => 'video',
  );
  $handler->display->display_options['filters']['type_1']['group'] = 1;
  $handler->display->display_options['filters']['type_1']['expose']['operator_id'] = 'type_1_op';
  $handler->display->display_options['filters']['type_1']['expose']['label'] = 'Type';
  $handler->display->display_options['filters']['type_1']['expose']['operator'] = 'type_1_op';
  $handler->display->display_options['filters']['type_1']['expose']['identifier'] = 'type_1';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  $handler->display->display_options['block_description'] = 'course materials block';
  $export['documents'] = $view;

  return $export;
}
