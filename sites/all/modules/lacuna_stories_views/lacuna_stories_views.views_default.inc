<?php
/**
 * @file
 * lacuna_stories_views.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function lacuna_stories_views_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'documents';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Materials, Sewing Kit, Syllabus';
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
    2 => '2',
    6 => '6',
    7 => '7',
    5 => '5',
    4 => '4',
  );
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'better_exposed_filters';
  $handler->display->display_options['exposed_form']['options']['reset_button'] = TRUE;
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = 'View All';
  $handler->display->display_options['exposed_form']['options']['autosubmit'] = TRUE;
  $handler->display->display_options['exposed_form']['options']['bef'] = array(
    'general' => array(
      'allow_secondary' => 0,
      'secondary_label' => 'Advanced options',
    ),
    'field_unit_tid' => array(
      'bef_format' => 'bef',
      'more_options' => array(
        'bef_select_all_none' => 0,
        'bef_collapsible' => 0,
        'is_secondary' => 0,
        'any_label' => '',
        'bef_filter_description' => '',
        'tokens' => array(
          'available' => array(
            0 => 'global_types',
          ),
        ),
        'rewrite' => array(
          'filter_rewrite_values' => '',
        ),
      ),
    ),
  );
  $handler->display->display_options['exposed_form']['options']['input_required'] = 0;
  $handler->display->display_options['exposed_form']['options']['text_input_required_format'] = 'filtered_html';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '100';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
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
  /* Field: Field: Image */
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
  /* Field: Content: Video */
  $handler->display->display_options['fields']['field_video_video']['id'] = 'field_video_video';
  $handler->display->display_options['fields']['field_video_video']['table'] = 'field_data_field_video_video';
  $handler->display->display_options['fields']['field_video_video']['field'] = 'field_video_video';
  $handler->display->display_options['fields']['field_video_video']['label'] = '';
  $handler->display->display_options['fields']['field_video_video']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_video_video']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['field_video_video']['alter']['path'] = '[path_1] ';
  $handler->display->display_options['fields']['field_video_video']['alter']['absolute'] = TRUE;
  $handler->display->display_options['fields']['field_video_video']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_video_video']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_video_video']['type'] = 'file_rendered';
  $handler->display->display_options['fields']['field_video_video']['settings'] = array(
    'file_view_mode' => 'media_preview',
  );
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
  /* Field: Content: Hover Abstract */
  $handler->display->display_options['fields']['field_biblio_hover_abstract']['id'] = 'field_biblio_hover_abstract';
  $handler->display->display_options['fields']['field_biblio_hover_abstract']['table'] = 'field_data_field_biblio_hover_abstract';
  $handler->display->display_options['fields']['field_biblio_hover_abstract']['field'] = 'field_biblio_hover_abstract';
  $handler->display->display_options['fields']['field_biblio_hover_abstract']['relationship'] = 'field_bibliographic_entry_target_id';
  $handler->display->display_options['fields']['field_biblio_hover_abstract']['label'] = '';
  $handler->display->display_options['fields']['field_biblio_hover_abstract']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_biblio_hover_abstract']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_biblio_hover_abstract']['empty'] = '[biblio_abst_e]';
  $handler->display->display_options['fields']['field_biblio_hover_abstract']['hide_alter_empty'] = FALSE;
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
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Topics (field_topics) */
  $handler->display->display_options['filters']['field_topics_tid']['id'] = 'field_topics_tid';
  $handler->display->display_options['filters']['field_topics_tid']['table'] = 'field_data_field_topics';
  $handler->display->display_options['filters']['field_topics_tid']['field'] = 'field_topics_tid';
  $handler->display->display_options['filters']['field_topics_tid']['group'] = 1;
  $handler->display->display_options['filters']['field_topics_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_topics_tid']['expose']['operator_id'] = 'field_topics_tid_op';
  $handler->display->display_options['filters']['field_topics_tid']['expose']['label'] = 'Limit by Topic';
  $handler->display->display_options['filters']['field_topics_tid']['expose']['operator'] = 'field_topics_tid_op';
  $handler->display->display_options['filters']['field_topics_tid']['expose']['identifier'] = 'field_topics_tid';
  $handler->display->display_options['filters']['field_topics_tid']['expose']['remember'] = TRUE;
  $handler->display->display_options['filters']['field_topics_tid']['expose']['multiple'] = TRUE;
  $handler->display->display_options['filters']['field_topics_tid']['expose']['remember_roles'] = array(
    2 => '2',
    1 => '1',
    3 => '3',
    4 => '4',
  );
  $handler->display->display_options['filters']['field_topics_tid']['reduce_duplicates'] = TRUE;
  $handler->display->display_options['filters']['field_topics_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_topics_tid']['vocabulary'] = 'topics';
  $handler->display->display_options['filters']['field_topics_tid']['error_message'] = FALSE;
  /* Filter criterion: Content: Genre (field_doc_genre) */
  $handler->display->display_options['filters']['field_doc_genre_tid']['id'] = 'field_doc_genre_tid';
  $handler->display->display_options['filters']['field_doc_genre_tid']['table'] = 'field_data_field_doc_genre';
  $handler->display->display_options['filters']['field_doc_genre_tid']['field'] = 'field_doc_genre_tid';
  $handler->display->display_options['filters']['field_doc_genre_tid']['value'] = array(
    20 => '20',
    12 => '12',
    10 => '10',
    19 => '19',
    9 => '9',
    21 => '21',
    7 => '7',
    22 => '22',
    23 => '23',
    13 => '13',
    11 => '11',
    24 => '24',
    8 => '8',
  );
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
    1 => '1',
    3 => '3',
    4 => '4',
    5 => 0,
  );
  $handler->display->display_options['filters']['field_doc_genre_tid']['expose']['reduce'] = TRUE;
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
  /* Filter criterion: Workflow current: Current state */
  $handler->display->display_options['filters']['sid']['id'] = 'sid';
  $handler->display->display_options['filters']['sid']['table'] = 'workflow_node_current';
  $handler->display->display_options['filters']['sid']['field'] = 'sid';
  $handler->display->display_options['filters']['sid']['value'] = array(
    3 => '3',
  );

  /* Display: Materials */
  $handler = $view->new_display('page', 'Materials', 'page');
  $handler->display->display_options['defaults']['exposed_form'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'better_exposed_filters';
  $handler->display->display_options['exposed_form']['options']['reset_button'] = TRUE;
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = 'View All';
  $handler->display->display_options['exposed_form']['options']['autosubmit'] = TRUE;
  $handler->display->display_options['exposed_form']['options']['bef'] = array(
    'general' => array(
      'allow_secondary' => 0,
      'secondary_label' => 'Advanced options',
    ),
    'sort' => array(
      'bef_format' => 'bef_links',
      'advanced' => array(
        'collapsible' => 0,
        'collapsible_label' => 'Sort options',
        'combine' => 0,
        'combine_rewrite' => '',
        'reset' => 0,
        'reset_label' => '',
        'is_secondary' => 0,
      ),
    ),
    'field_topics_tid' => array(
      'bef_format' => 'bef',
      'more_options' => array(
        'bef_select_all_none' => 0,
        'bef_collapsible' => 0,
        'is_secondary' => 0,
        'bef_filter_description' => '',
        'tokens' => array(
          'available' => array(
            0 => 'global_types',
          ),
        ),
      ),
    ),
    'field_doc_genre_tid' => array(
      'bef_format' => 'bef',
      'more_options' => array(
        'bef_select_all_none' => 0,
        'bef_collapsible' => 0,
        'is_secondary' => 0,
        'bef_filter_description' => '',
        'tokens' => array(
          'available' => array(
            0 => 'global_types',
          ),
        ),
      ),
    ),
    'type' => array(
      'bef_format' => 'bef',
      'more_options' => array(
        'bef_select_all_none' => 0,
        'bef_collapsible' => 0,
        'is_secondary' => 0,
        'bef_filter_description' => '',
        'tokens' => array(
          'available' => array(
            0 => 'global_types',
          ),
        ),
      ),
    ),
  );
  $handler->display->display_options['defaults']['fields'] = FALSE;
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
  /* Field: Field: Image */
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
  /* Field: Content: Video */
  $handler->display->display_options['fields']['field_video_video']['id'] = 'field_video_video';
  $handler->display->display_options['fields']['field_video_video']['table'] = 'field_data_field_video_video';
  $handler->display->display_options['fields']['field_video_video']['field'] = 'field_video_video';
  $handler->display->display_options['fields']['field_video_video']['label'] = '';
  $handler->display->display_options['fields']['field_video_video']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_video_video']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['field_video_video']['alter']['path'] = '[path_1] ';
  $handler->display->display_options['fields']['field_video_video']['alter']['absolute'] = TRUE;
  $handler->display->display_options['fields']['field_video_video']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_video_video']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_video_video']['type'] = 'file_rendered';
  $handler->display->display_options['fields']['field_video_video']['settings'] = array(
    'file_view_mode' => 'media_preview',
  );
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
  /* Field: Content: Hover Abstract */
  $handler->display->display_options['fields']['field_biblio_hover_abstract']['id'] = 'field_biblio_hover_abstract';
  $handler->display->display_options['fields']['field_biblio_hover_abstract']['table'] = 'field_data_field_biblio_hover_abstract';
  $handler->display->display_options['fields']['field_biblio_hover_abstract']['field'] = 'field_biblio_hover_abstract';
  $handler->display->display_options['fields']['field_biblio_hover_abstract']['relationship'] = 'field_bibliographic_entry_target_id';
  $handler->display->display_options['fields']['field_biblio_hover_abstract']['label'] = '';
  $handler->display->display_options['fields']['field_biblio_hover_abstract']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_biblio_hover_abstract']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_biblio_hover_abstract']['empty'] = '[biblio_abst_e]';
  $handler->display->display_options['fields']['field_biblio_hover_abstract']['hide_alter_empty'] = FALSE;
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
  $handler->display->display_options['path'] = 'materials';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Materials';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'main-menu';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;

  /* Display: Sewing Kit */
  $handler = $view->new_display('page', 'Sewing Kit', 'page_2');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Sewing Kit';
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '50';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['inline'] = array(
    'views_bulk_operations' => 'views_bulk_operations',
    'biblio_short_title' => 'biblio_short_title',
  );
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
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
  /* Field: Field: Image */
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
  /* Field: Content: Video */
  $handler->display->display_options['fields']['field_video_video']['id'] = 'field_video_video';
  $handler->display->display_options['fields']['field_video_video']['table'] = 'field_data_field_video_video';
  $handler->display->display_options['fields']['field_video_video']['field'] = 'field_video_video';
  $handler->display->display_options['fields']['field_video_video']['label'] = '';
  $handler->display->display_options['fields']['field_video_video']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_video_video']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['field_video_video']['alter']['path'] = '[path_1] ';
  $handler->display->display_options['fields']['field_video_video']['alter']['absolute'] = TRUE;
  $handler->display->display_options['fields']['field_video_video']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_video_video']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_video_video']['type'] = 'file_rendered';
  $handler->display->display_options['fields']['field_video_video']['settings'] = array(
    'file_view_mode' => 'media_preview',
  );
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['exclude'] = TRUE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Field: Biblio: URL */
  $handler->display->display_options['fields']['biblio_url']['id'] = 'biblio_url';
  $handler->display->display_options['fields']['biblio_url']['table'] = 'biblio';
  $handler->display->display_options['fields']['biblio_url']['field'] = 'biblio_url';
  $handler->display->display_options['fields']['biblio_url']['relationship'] = 'field_bibliographic_entry_target_id';
  $handler->display->display_options['fields']['biblio_url']['label'] = '';
  $handler->display->display_options['fields']['biblio_url']['exclude'] = TRUE;
  $handler->display->display_options['fields']['biblio_url']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['biblio_url']['alter']['text'] = 'Read and Annotate';
  $handler->display->display_options['fields']['biblio_url']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['biblio_url']['alter']['path'] = '[biblio_url]';
  $handler->display->display_options['fields']['biblio_url']['alter']['link_class'] = 'lacuna-button';
  $handler->display->display_options['fields']['biblio_url']['alter']['target'] = '_blank';
  $handler->display->display_options['fields']['biblio_url']['element_type'] = 'div';
  $handler->display->display_options['fields']['biblio_url']['element_class'] = 'grid-link';
  $handler->display->display_options['fields']['biblio_url']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['biblio_url']['biblio_label'] = 0;
  /* Field: Biblio: Abstract */
  $handler->display->display_options['fields']['biblio_abst_e']['id'] = 'biblio_abst_e';
  $handler->display->display_options['fields']['biblio_abst_e']['table'] = 'biblio';
  $handler->display->display_options['fields']['biblio_abst_e']['field'] = 'biblio_abst_e';
  $handler->display->display_options['fields']['biblio_abst_e']['relationship'] = 'field_bibliographic_entry_target_id';
  $handler->display->display_options['fields']['biblio_abst_e']['exclude'] = TRUE;
  $handler->display->display_options['fields']['biblio_abst_e']['alter']['max_length'] = '600';
  $handler->display->display_options['fields']['biblio_abst_e']['alter']['trim'] = TRUE;
  /* Field: Content: Hover Abstract */
  $handler->display->display_options['fields']['field_biblio_hover_abstract']['id'] = 'field_biblio_hover_abstract';
  $handler->display->display_options['fields']['field_biblio_hover_abstract']['table'] = 'field_data_field_biblio_hover_abstract';
  $handler->display->display_options['fields']['field_biblio_hover_abstract']['field'] = 'field_biblio_hover_abstract';
  $handler->display->display_options['fields']['field_biblio_hover_abstract']['relationship'] = 'field_bibliographic_entry_target_id';
  $handler->display->display_options['fields']['field_biblio_hover_abstract']['label'] = '';
  $handler->display->display_options['fields']['field_biblio_hover_abstract']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_biblio_hover_abstract']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_biblio_hover_abstract']['empty'] = '[biblio_abst_e]';
  $handler->display->display_options['fields']['field_biblio_hover_abstract']['hide_alter_empty'] = FALSE;
  /* Field: Bulk operations: Content */
  $handler->display->display_options['fields']['views_bulk_operations']['id'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['table'] = 'node';
  $handler->display->display_options['fields']['views_bulk_operations']['field'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['label'] = '';
  $handler->display->display_options['fields']['views_bulk_operations']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['display_type'] = '1';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['enable_select_all_pages'] = 1;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['force_single'] = 0;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['entity_load_capacity'] = '1';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_operations'] = array(
    'action::sewing_kit_stitch' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 1,
      'override_label' => 0,
      'label' => '',
    ),
    'action::node_assign_owner_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::views_bulk_operations_delete_item' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::views_bulk_operations_delete_revision' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::views_bulk_operations_script_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::flag_node_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::node_make_sticky_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::node_make_unsticky_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::views_bulk_operations_modify_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
      'settings' => array(
        'show_all_tokens' => 1,
        'display_values' => array(
          '_all_' => '_all_',
        ),
      ),
    ),
    'action::views_bulk_operations_argument_selector_action' => array(
      'selected' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
      'settings' => array(
        'url' => '',
      ),
    ),
    'action::node_promote_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::node_publish_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::node_unpromote_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::node_save_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::system_send_email_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::node_unpublish_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::node_unpublish_by_keyword_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::pathauto_node_update_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
  );
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
  $handler->display->display_options['path'] = 'sewing-kit';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Sewing Kit';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'main-menu';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;

  /* Display: Syllabus */
  $handler = $view->new_display('page', 'Syllabus', 'page_1');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Syllabus';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Unit */
  $handler->display->display_options['fields']['field_unit']['id'] = 'field_unit';
  $handler->display->display_options['fields']['field_unit']['table'] = 'field_data_field_unit';
  $handler->display->display_options['fields']['field_unit']['field'] = 'field_unit';
  $handler->display->display_options['fields']['field_unit']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_unit']['type'] = 'taxonomy_term_reference_plain';
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
  /* Field: Field: Image */
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
  /* Field: Content: Video */
  $handler->display->display_options['fields']['field_video_video']['id'] = 'field_video_video';
  $handler->display->display_options['fields']['field_video_video']['table'] = 'field_data_field_video_video';
  $handler->display->display_options['fields']['field_video_video']['field'] = 'field_video_video';
  $handler->display->display_options['fields']['field_video_video']['label'] = '';
  $handler->display->display_options['fields']['field_video_video']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_video_video']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['field_video_video']['alter']['path'] = '[path_1] ';
  $handler->display->display_options['fields']['field_video_video']['alter']['absolute'] = TRUE;
  $handler->display->display_options['fields']['field_video_video']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_video_video']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_video_video']['type'] = 'file_rendered';
  $handler->display->display_options['fields']['field_video_video']['settings'] = array(
    'file_view_mode' => 'media_preview',
  );
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
  /* Field: Content: Hover Abstract */
  $handler->display->display_options['fields']['field_biblio_hover_abstract']['id'] = 'field_biblio_hover_abstract';
  $handler->display->display_options['fields']['field_biblio_hover_abstract']['table'] = 'field_data_field_biblio_hover_abstract';
  $handler->display->display_options['fields']['field_biblio_hover_abstract']['field'] = 'field_biblio_hover_abstract';
  $handler->display->display_options['fields']['field_biblio_hover_abstract']['relationship'] = 'field_bibliographic_entry_target_id';
  $handler->display->display_options['fields']['field_biblio_hover_abstract']['label'] = '';
  $handler->display->display_options['fields']['field_biblio_hover_abstract']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_biblio_hover_abstract']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_biblio_hover_abstract']['empty'] = '[biblio_abst_e]';
  $handler->display->display_options['fields']['field_biblio_hover_abstract']['hide_alter_empty'] = FALSE;
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
  /* Sort criterion: Content: Priority (field_priority) */
  $handler->display->display_options['sorts']['field_priority_tid']['id'] = 'field_priority_tid';
  $handler->display->display_options['sorts']['field_priority_tid']['table'] = 'field_data_field_priority';
  $handler->display->display_options['sorts']['field_priority_tid']['field'] = 'field_priority_tid';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['filter_groups']['operator'] = 'OR';
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Workflow current: Current state */
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
  $handler->display->display_options['filters']['field_unit_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_unit_tid']['expose']['operator_id'] = 'field_unit_tid_op';
  $handler->display->display_options['filters']['field_unit_tid']['expose']['label'] = 'Limit by Unit';
  $handler->display->display_options['filters']['field_unit_tid']['expose']['operator'] = 'field_unit_tid_op';
  $handler->display->display_options['filters']['field_unit_tid']['expose']['identifier'] = 'field_unit_tid';
  $handler->display->display_options['filters']['field_unit_tid']['expose']['remember'] = TRUE;
  $handler->display->display_options['filters']['field_unit_tid']['expose']['multiple'] = TRUE;
  $handler->display->display_options['filters']['field_unit_tid']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
  );
  $handler->display->display_options['filters']['field_unit_tid']['reduce_duplicates'] = TRUE;
  $handler->display->display_options['filters']['field_unit_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_unit_tid']['vocabulary'] = 'unit';
  $handler->display->display_options['filters']['field_unit_tid']['error_message'] = FALSE;
  $handler->display->display_options['path'] = 'syllabus';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Syllabus';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'main-menu';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $export['documents'] = $view;

  $view = new view();
  $view->name = 'my_annotations';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'My Annotations';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'My Annotations';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'create annotation content';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'views_bulk_operations' => 'views_bulk_operations',
    'title' => 'title',
    'text' => 'text',
    'category' => 'category',
    'annotation_tags' => 'annotation_tags',
    'quote' => 'quote',
    'title_1' => 'title_1',
    'created' => 'created',
    'edit_node' => 'edit_node',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'views_bulk_operations' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'title' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'text' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'category' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'annotation_tags' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'quote' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'title_1' => array(
      'sortable' => 1,
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
    'edit_node' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['annotation_reference_target_id']['id'] = 'annotation_reference_target_id';
  $handler->display->display_options['relationships']['annotation_reference_target_id']['table'] = 'field_data_annotation_reference';
  $handler->display->display_options['relationships']['annotation_reference_target_id']['field'] = 'annotation_reference_target_id';
  /* Field: Bulk operations: Content */
  $handler->display->display_options['fields']['views_bulk_operations']['id'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['table'] = 'node';
  $handler->display->display_options['fields']['views_bulk_operations']['field'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['label'] = 'Select for Thread';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['display_type'] = '1';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['enable_select_all_pages'] = 1;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['force_single'] = 0;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['entity_load_capacity'] = '10';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_operations'] = array(
    'action::sewing_kit_stitch' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 1,
      'override_label' => 0,
      'label' => '',
    ),
    'action::node_assign_owner_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::views_bulk_operations_delete_item' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::views_bulk_operations_delete_revision' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::views_bulk_operations_script_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::flag_node_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::node_make_sticky_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::node_make_unsticky_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::views_bulk_operations_modify_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
      'settings' => array(
        'show_all_tokens' => 1,
        'display_values' => array(
          '_all_' => '_all_',
        ),
      ),
    ),
    'action::views_bulk_operations_argument_selector_action' => array(
      'selected' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
      'settings' => array(
        'url' => '',
      ),
    ),
    'action::node_promote_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::node_publish_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::node_unpromote_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::node_save_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::system_send_email_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::node_unpublish_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::node_unpublish_by_keyword_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::pathauto_node_update_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
  );
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['exclude'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  /* Field: Content: Annotation Text */
  $handler->display->display_options['fields']['text']['id'] = 'text';
  $handler->display->display_options['fields']['text']['table'] = 'field_data_text';
  $handler->display->display_options['fields']['text']['field'] = 'text';
  $handler->display->display_options['fields']['text']['label'] = 'My Annotation';
  /* Field: Content: Category */
  $handler->display->display_options['fields']['category']['id'] = 'category';
  $handler->display->display_options['fields']['category']['table'] = 'field_data_category';
  $handler->display->display_options['fields']['category']['field'] = 'category';
  $handler->display->display_options['fields']['category']['empty'] = 'Highlight';
  $handler->display->display_options['fields']['category']['type'] = 'taxonomy_term_reference_plain';
  /* Field: Content: Tags */
  $handler->display->display_options['fields']['annotation_tags']['id'] = 'annotation_tags';
  $handler->display->display_options['fields']['annotation_tags']['table'] = 'field_data_annotation_tags';
  $handler->display->display_options['fields']['annotation_tags']['field'] = 'annotation_tags';
  $handler->display->display_options['fields']['annotation_tags']['delta_offset'] = '0';
  /* Field: Content: Quote */
  $handler->display->display_options['fields']['quote']['id'] = 'quote';
  $handler->display->display_options['fields']['quote']['table'] = 'field_data_quote';
  $handler->display->display_options['fields']['quote']['field'] = 'quote';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title_1']['id'] = 'title_1';
  $handler->display->display_options['fields']['title_1']['table'] = 'node';
  $handler->display->display_options['fields']['title_1']['field'] = 'title';
  $handler->display->display_options['fields']['title_1']['relationship'] = 'annotation_reference_target_id';
  $handler->display->display_options['fields']['title_1']['label'] = 'Document Annotated';
  /* Field: Content: Post date */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'node';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['date_format'] = 'short';
  $handler->display->display_options['fields']['created']['second_date_format'] = 'long';
  /* Field: Content: Edit link */
  $handler->display->display_options['fields']['edit_node']['id'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['edit_node']['field'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['label'] = 'Edit';
  $handler->display->display_options['fields']['edit_node']['text'] = 'Edit annotation';
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Contextual filter: Content: Author uid */
  $handler->display->display_options['arguments']['uid']['id'] = 'uid';
  $handler->display->display_options['arguments']['uid']['table'] = 'node';
  $handler->display->display_options['arguments']['uid']['field'] = 'uid';
  $handler->display->display_options['arguments']['uid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['uid']['default_argument_type'] = 'current_user';
  $handler->display->display_options['arguments']['uid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['uid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['uid']['summary_options']['items_per_page'] = '25';
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

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'my-annotations';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'My Annotations';
  $handler->display->display_options['menu']['name'] = 'main-menu';
  $export['my_annotations'] = $view;

  $view = new view();
  $view->name = 'my_content';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'My Writing';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'My Writing';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'role';
  $handler->display->display_options['access']['role'] = array(
    2 => '2',
  );
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['disable_sql_rewrite'] = TRUE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '25';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['row_class'] = 'my_writing';
  $handler->display->display_options['style_options']['columns'] = array(
    'title' => 'title',
    'type' => 'type',
    'created' => 'created',
    'publishcontent' => 'publishcontent',
  );
  $handler->display->display_options['style_options']['default'] = 'created';
  $handler->display->display_options['style_options']['info'] = array(
    'title' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => 'views-align-left',
      'separator' => '',
      'empty_column' => 0,
    ),
    'type' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => 'views-align-left',
      'separator' => '',
      'empty_column' => 0,
    ),
    'created' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => 'views-align-center',
      'separator' => '',
      'empty_column' => 0,
    ),
    'publishcontent' => array(
      'align' => 'views-align-center',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = TRUE;
  $handler->display->display_options['empty']['area']['content'] = 'You haven\'t written anything yet for this course.';
  $handler->display->display_options['empty']['area']['format'] = 'full_html';
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
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  /* Field: Content: Type */
  $handler->display->display_options['fields']['type']['id'] = 'type';
  $handler->display->display_options['fields']['type']['table'] = 'node';
  $handler->display->display_options['fields']['type']['field'] = 'type';
  /* Field: Content: Post date */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'node';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['date_format'] = 'custom';
  $handler->display->display_options['fields']['created']['custom_date_format'] = 'M j, Y';
  $handler->display->display_options['fields']['created']['second_date_format'] = 'long';
  /* Field: Content: Publish link */
  $handler->display->display_options['fields']['publishcontent']['id'] = 'publishcontent';
  $handler->display->display_options['fields']['publishcontent']['table'] = 'node';
  $handler->display->display_options['fields']['publishcontent']['field'] = 'publishcontent';
  $handler->display->display_options['fields']['publishcontent']['label'] = 'Publish/Unpublish';
  $handler->display->display_options['fields']['publishcontent']['element_type'] = 'div';
  $handler->display->display_options['fields']['publishcontent']['element_class'] = 'lacuna-button publish-button';
  $handler->display->display_options['fields']['publishcontent']['unpublish'] = 'Unpublish';
  $handler->display->display_options['fields']['publishcontent']['publish'] = 'Publish';
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Contextual filter: User: Uid */
  $handler->display->display_options['arguments']['uid']['id'] = 'uid';
  $handler->display->display_options['arguments']['uid']['table'] = 'users';
  $handler->display->display_options['arguments']['uid']['field'] = 'uid';
  $handler->display->display_options['arguments']['uid']['relationship'] = 'uid';
  $handler->display->display_options['arguments']['uid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['uid']['default_argument_type'] = 'current_user';
  $handler->display->display_options['arguments']['uid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['uid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['uid']['summary_options']['items_per_page'] = '25';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'my-writing';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'My Writing';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'main-menu';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $export['my_content'] = $view;

  $view = new view();
  $view->name = 'my_threads';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'My Threads';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'My Threads';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'create thread content';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'better_exposed_filters';
  $handler->display->display_options['exposed_form']['options']['autosubmit'] = TRUE;
  $handler->display->display_options['exposed_form']['options']['bef'] = array(
    'general' => array(
      'allow_secondary' => 0,
      'secondary_label' => 'Advanced options',
    ),
    'sort' => array(
      'bef_format' => 'bef_links',
      'advanced' => array(
        'collapsible' => 0,
        'collapsible_label' => 'Sort options',
        'combine' => 0,
        'combine_rewrite' => '',
        'reset' => 0,
        'reset_label' => '',
        'is_secondary' => 0,
      ),
    ),
    'field_tags_tid' => array(
      'bef_format' => 'bef',
      'more_options' => array(
        'bef_select_all_none' => 0,
        'bef_collapsible' => 0,
        'is_secondary' => 0,
        'any_label' => '',
        'bef_filter_description' => '',
        'tokens' => array(
          'available' => array(
            0 => 'global_types',
          ),
        ),
        'rewrite' => array(
          'filter_rewrite_values' => '',
        ),
      ),
    ),
  );
  $handler->display->display_options['exposed_form']['options']['input_required'] = 0;
  $handler->display->display_options['exposed_form']['options']['text_input_required_format'] = 'filtered_html';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['thread_reference_target_id']['id'] = 'thread_reference_target_id';
  $handler->display->display_options['relationships']['thread_reference_target_id']['table'] = 'field_data_thread_reference';
  $handler->display->display_options['relationships']['thread_reference_target_id']['field'] = 'thread_reference_target_id';
  /* Field: Field: Image */
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
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title_1']['id'] = 'title_1';
  $handler->display->display_options['fields']['title_1']['table'] = 'node';
  $handler->display->display_options['fields']['title_1']['field'] = 'title';
  $handler->display->display_options['fields']['title_1']['relationship'] = 'thread_reference_target_id';
  $handler->display->display_options['fields']['title_1']['group_type'] = 'count_distinct';
  $handler->display->display_options['fields']['title_1']['label'] = 'Total Connections';
  $handler->display->display_options['fields']['title_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title_1']['link_to_node'] = FALSE;
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  $handler->display->display_options['sorts']['created']['exposed'] = TRUE;
  $handler->display->display_options['sorts']['created']['expose']['label'] = 'Date created';
  /* Sort criterion: Content: Updated date */
  $handler->display->display_options['sorts']['changed']['id'] = 'changed';
  $handler->display->display_options['sorts']['changed']['table'] = 'node';
  $handler->display->display_options['sorts']['changed']['field'] = 'changed';
  $handler->display->display_options['sorts']['changed']['exposed'] = TRUE;
  $handler->display->display_options['sorts']['changed']['expose']['label'] = 'Date modified';
  /* Sort criterion: Content: Title */
  $handler->display->display_options['sorts']['title']['id'] = 'title';
  $handler->display->display_options['sorts']['title']['table'] = 'node';
  $handler->display->display_options['sorts']['title']['field'] = 'title';
  $handler->display->display_options['sorts']['title']['exposed'] = TRUE;
  $handler->display->display_options['sorts']['title']['expose']['label'] = 'Title';
  /* Contextual filter: Content: Author uid */
  $handler->display->display_options['arguments']['uid']['id'] = 'uid';
  $handler->display->display_options['arguments']['uid']['table'] = 'node';
  $handler->display->display_options['arguments']['uid']['field'] = 'uid';
  $handler->display->display_options['arguments']['uid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['uid']['default_argument_type'] = 'current_user';
  $handler->display->display_options['arguments']['uid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['uid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['uid']['summary_options']['items_per_page'] = '25';
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
  /* Filter criterion: Content: Tags (field_tags) */
  $handler->display->display_options['filters']['field_tags_tid']['id'] = 'field_tags_tid';
  $handler->display->display_options['filters']['field_tags_tid']['table'] = 'field_data_field_tags';
  $handler->display->display_options['filters']['field_tags_tid']['field'] = 'field_tags_tid';
  $handler->display->display_options['filters']['field_tags_tid']['group'] = 1;
  $handler->display->display_options['filters']['field_tags_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_tags_tid']['expose']['operator_id'] = 'field_tags_tid_op';
  $handler->display->display_options['filters']['field_tags_tid']['expose']['label'] = 'Limit by Tags';
  $handler->display->display_options['filters']['field_tags_tid']['expose']['operator'] = 'field_tags_tid_op';
  $handler->display->display_options['filters']['field_tags_tid']['expose']['identifier'] = 'field_tags_tid';
  $handler->display->display_options['filters']['field_tags_tid']['expose']['remember'] = TRUE;
  $handler->display->display_options['filters']['field_tags_tid']['expose']['multiple'] = TRUE;
  $handler->display->display_options['filters']['field_tags_tid']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
  );
  $handler->display->display_options['filters']['field_tags_tid']['reduce_duplicates'] = TRUE;
  $handler->display->display_options['filters']['field_tags_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_tags_tid']['vocabulary'] = 'tags';
  $handler->display->display_options['filters']['field_tags_tid']['error_message'] = FALSE;

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'my-threads';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'My Threads';
  $handler->display->display_options['menu']['name'] = 'main-menu';
  $export['my_threads'] = $view;

  $view = new view();
  $view->name = 'responses';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Responses';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Responses';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'better_exposed_filters';
  $handler->display->display_options['exposed_form']['options']['reset_button'] = TRUE;
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = 'View All';
  $handler->display->display_options['exposed_form']['options']['expose_sort_order'] = FALSE;
  $handler->display->display_options['exposed_form']['options']['autosubmit'] = TRUE;
  $handler->display->display_options['exposed_form']['options']['bef'] = array(
    'general' => array(
      'allow_secondary' => 0,
      'secondary_label' => 'Advanced options',
    ),
    'field_genre_tid' => array(
      'bef_format' => 'bef',
      'more_options' => array(
        'bef_select_all_none' => 0,
        'bef_collapsible' => 0,
        'is_secondary' => 0,
        'any_label' => '',
        'bef_filter_description' => '',
        'tokens' => array(
          'available' => array(
            0 => 'global_types',
          ),
        ),
        'rewrite' => array(
          'filter_rewrite_values' => '',
        ),
      ),
    ),
    'field_topics_tid' => array(
      'bef_format' => 'bef',
      'more_options' => array(
        'bef_select_all_none' => 0,
        'bef_collapsible' => 0,
        'is_secondary' => 0,
        'any_label' => '',
        'bef_filter_description' => '',
        'tokens' => array(
          'available' => array(
            0 => 'global_types',
          ),
        ),
        'rewrite' => array(
          'filter_rewrite_values' => '',
        ),
      ),
    ),
  );
  $handler->display->display_options['exposed_form']['options']['input_required'] = 0;
  $handler->display->display_options['exposed_form']['options']['text_input_required_format'] = 'filtered_html';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '25';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Relationship: Content: Author */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'node';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  /* Field: Field: Image */
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
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: User: Display Name */
  $handler->display->display_options['fields']['field_display_name']['id'] = 'field_display_name';
  $handler->display->display_options['fields']['field_display_name']['table'] = 'field_data_field_display_name';
  $handler->display->display_options['fields']['field_display_name']['field'] = 'field_display_name';
  $handler->display->display_options['fields']['field_display_name']['relationship'] = 'uid';
  $handler->display->display_options['fields']['field_display_name']['label'] = '';
  $handler->display->display_options['fields']['field_display_name']['element_label_colon'] = FALSE;
  /* Field: Content: Post date */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'node';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['label'] = 'Written on';
  $handler->display->display_options['fields']['created']['date_format'] = 'custom';
  $handler->display->display_options['fields']['created']['custom_date_format'] = 'M j, Y';
  $handler->display->display_options['fields']['created']['second_date_format'] = 'long';
  /* Field: Content: Comment count */
  $handler->display->display_options['fields']['comment_count']['id'] = 'comment_count';
  $handler->display->display_options['fields']['comment_count']['table'] = 'node_comment_statistics';
  $handler->display->display_options['fields']['comment_count']['field'] = 'comment_count';
  $handler->display->display_options['fields']['comment_count']['label'] = 'Comment(s)';
  $handler->display->display_options['fields']['comment_count']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['comment_count']['empty_zero'] = TRUE;
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
    'blog' => 'blog',
  );
  /* Filter criterion: Content: Genre (field_genre) */
  $handler->display->display_options['filters']['field_genre_tid']['id'] = 'field_genre_tid';
  $handler->display->display_options['filters']['field_genre_tid']['table'] = 'field_data_field_genre';
  $handler->display->display_options['filters']['field_genre_tid']['field'] = 'field_genre_tid';
  $handler->display->display_options['filters']['field_genre_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_genre_tid']['expose']['operator_id'] = 'field_genre_tid_op';
  $handler->display->display_options['filters']['field_genre_tid']['expose']['label'] = 'Genre';
  $handler->display->display_options['filters']['field_genre_tid']['expose']['operator'] = 'field_genre_tid_op';
  $handler->display->display_options['filters']['field_genre_tid']['expose']['identifier'] = 'field_genre_tid';
  $handler->display->display_options['filters']['field_genre_tid']['expose']['remember'] = TRUE;
  $handler->display->display_options['filters']['field_genre_tid']['expose']['multiple'] = TRUE;
  $handler->display->display_options['filters']['field_genre_tid']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
  );
  $handler->display->display_options['filters']['field_genre_tid']['reduce_duplicates'] = TRUE;
  $handler->display->display_options['filters']['field_genre_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_genre_tid']['vocabulary'] = 'genre_blog_post';
  $handler->display->display_options['filters']['field_genre_tid']['error_message'] = FALSE;
  /* Filter criterion: Content: Topics (field_topics) */
  $handler->display->display_options['filters']['field_topics_tid']['id'] = 'field_topics_tid';
  $handler->display->display_options['filters']['field_topics_tid']['table'] = 'field_data_field_topics';
  $handler->display->display_options['filters']['field_topics_tid']['field'] = 'field_topics_tid';
  $handler->display->display_options['filters']['field_topics_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_topics_tid']['expose']['operator_id'] = 'field_topics_tid_op';
  $handler->display->display_options['filters']['field_topics_tid']['expose']['label'] = 'Topics';
  $handler->display->display_options['filters']['field_topics_tid']['expose']['operator'] = 'field_topics_tid_op';
  $handler->display->display_options['filters']['field_topics_tid']['expose']['identifier'] = 'field_topics_tid';
  $handler->display->display_options['filters']['field_topics_tid']['expose']['remember'] = TRUE;
  $handler->display->display_options['filters']['field_topics_tid']['expose']['multiple'] = TRUE;
  $handler->display->display_options['filters']['field_topics_tid']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
  );
  $handler->display->display_options['filters']['field_topics_tid']['reduce_duplicates'] = TRUE;
  $handler->display->display_options['filters']['field_topics_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_topics_tid']['vocabulary'] = 'topics';
  $handler->display->display_options['filters']['field_topics_tid']['error_message'] = FALSE;

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'responses';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Responses';
  $handler->display->display_options['menu']['name'] = 'main-menu';
  $export['responses'] = $view;

  $view = new view();
  $view->name = 'topics';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'taxonomy_term_data';
  $view->human_name = 'Topics';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Topics';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['style_options']['default_row_class'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['inline'] = array(
    'field_image' => 'field_image',
    'description' => 'description',
  );
  /* Header: Global: Text area */
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  $handler->display->display_options['header']['area']['content'] = '<h2>Click on the images below to browse materials by topic.</h2>';
  $handler->display->display_options['header']['area']['format'] = 'full_html';
  /* Field: Taxonomy term: Term ID */
  $handler->display->display_options['fields']['tid']['id'] = 'tid';
  $handler->display->display_options['fields']['tid']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['fields']['tid']['field'] = 'tid';
  $handler->display->display_options['fields']['tid']['label'] = '';
  $handler->display->display_options['fields']['tid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['tid']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['tid']['separator'] = '';
  /* Field: Field: Image */
  $handler->display->display_options['fields']['field_image']['id'] = 'field_image';
  $handler->display->display_options['fields']['field_image']['table'] = 'field_data_field_image';
  $handler->display->display_options['fields']['field_image']['field'] = 'field_image';
  $handler->display->display_options['fields']['field_image']['label'] = '';
  $handler->display->display_options['fields']['field_image']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['field_image']['alter']['path'] = 'materials?field_themes_tid[]=[tid]';
  $handler->display->display_options['fields']['field_image']['element_type'] = 'div';
  $handler->display->display_options['fields']['field_image']['element_class'] = 'topic_image';
  $handler->display->display_options['fields']['field_image']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_image']['settings'] = array(
    'image_style' => 'square_thumbnail',
    'image_link' => '',
  );
  /* Field: Taxonomy term: Term description */
  $handler->display->display_options['fields']['description']['id'] = 'description';
  $handler->display->display_options['fields']['description']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['fields']['description']['field'] = 'description';
  $handler->display->display_options['fields']['description']['label'] = '';
  $handler->display->display_options['fields']['description']['element_type'] = 'div';
  $handler->display->display_options['fields']['description']['element_class'] = 'topic_description';
  $handler->display->display_options['fields']['description']['element_label_colon'] = FALSE;
  /* Sort criterion: Taxonomy vocabulary: Weight */
  $handler->display->display_options['sorts']['weight']['id'] = 'weight';
  $handler->display->display_options['sorts']['weight']['table'] = 'taxonomy_vocabulary';
  $handler->display->display_options['sorts']['weight']['field'] = 'weight';
  /* Filter criterion: Taxonomy vocabulary: Machine name */
  $handler->display->display_options['filters']['machine_name']['id'] = 'machine_name';
  $handler->display->display_options['filters']['machine_name']['table'] = 'taxonomy_vocabulary';
  $handler->display->display_options['filters']['machine_name']['field'] = 'machine_name';
  $handler->display->display_options['filters']['machine_name']['value'] = array(
    'topics' => 'topics',
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'topics';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Topics';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'main-menu';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $export['topics'] = $view;

  return $export;
}
