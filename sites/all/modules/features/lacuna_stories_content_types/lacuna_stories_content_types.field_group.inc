<?php
/**
 * @file
 * lacuna_stories_content_types.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function lacuna_stories_content_types_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_about|node|audio|default';
  $field_group->group_name = 'group_about';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'audio';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'About',
    'weight' => '3',
    'children' => array(
      0 => 'field_bibliographic_entry',
      1 => 'field_doc_genre',
      2 => 'field_topics',
      3 => 'field_tags',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-about field-group-fieldset',
      ),
    ),
  );
  $export['group_about|node|audio|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_about|node|audio|form';
  $field_group->group_name = 'group_about';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'audio';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'About',
    'weight' => '1',
    'children' => array(
      0 => 'field_bibliographic_entry',
      1 => 'field_doc_genre',
      2 => 'field_status',
      3 => 'field_topics',
      4 => 'field_tags',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-about field-group-fieldset',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_about|node|audio|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_about|node|document|default';
  $field_group->group_name = 'group_about';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'document';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'About',
    'weight' => '2',
    'children' => array(
      0 => 'field_bibliographic_entry',
      1 => 'field_doc_genre',
      2 => 'field_doc_pages',
      3 => 'field_topics',
      4 => 'field_tags',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'About',
      'instance_settings' => array(
        'classes' => 'group-about field-group-fieldset',
        'description' => '',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $export['group_about|node|document|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_about|node|document|form';
  $field_group->group_name = 'group_about';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'document';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'About',
    'weight' => '1',
    'children' => array(
      0 => 'field_bibliographic_entry',
      1 => 'field_doc_genre',
      2 => 'field_topics',
      3 => 'field_status',
      4 => 'field_tags',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-about field-group-fieldset',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_about|node|document|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_about|node|image|default';
  $field_group->group_name = 'group_about';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'image';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'About',
    'weight' => '1',
    'children' => array(
      0 => 'field_bibliographic_entry',
      1 => 'field_doc_genre',
      2 => 'field_topics',
      3 => 'field_tags',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-about field-group-fieldset',
      ),
    ),
  );
  $export['group_about|node|image|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_about|node|image|form';
  $field_group->group_name = 'group_about';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'image';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'About',
    'weight' => '2',
    'children' => array(
      0 => 'field_bibliographic_entry',
      1 => 'field_doc_genre',
      2 => 'field_topics',
      3 => 'field_status',
      4 => 'field_tags',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-about field-group-fieldset',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_about|node|image|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_about|node|music_video|default';
  $field_group->group_name = 'group_about';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'music_video';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'About',
    'weight' => '7',
    'children' => array(
      0 => 'field_bibliographic_entry',
      1 => 'field_doc_genre',
      2 => 'field_topics',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-about field-group-fieldset',
      ),
    ),
  );
  $export['group_about|node|music_video|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_about|node|music_video|form';
  $field_group->group_name = 'group_about';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'music_video';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'About',
    'weight' => '1',
    'children' => array(
      0 => 'field_bibliographic_entry',
      1 => 'field_doc_genre',
      2 => 'field_topics',
      3 => 'field_status',
      4 => 'field_tags',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-about field-group-fieldset',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_about|node|music_video|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_about|node|video|default';
  $field_group->group_name = 'group_about';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'video';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'About',
    'weight' => '10',
    'children' => array(
      0 => 'field_bibliographic_entry',
      1 => 'field_doc_genre',
      2 => 'field_topics',
      3 => 'field_tags',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'About',
      'instance_settings' => array(
        'classes' => 'group-about field-group-fieldset',
        'description' => '',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $export['group_about|node|video|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_about|node|video|form';
  $field_group->group_name = 'group_about';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'video';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'About',
    'weight' => '1',
    'children' => array(
      0 => 'field_bibliographic_entry',
      1 => 'field_doc_genre',
      2 => 'field_topics',
      3 => 'field_status',
      4 => 'field_tags',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-about field-group-fieldset',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_about|node|video|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_content|node|audio|form';
  $field_group->group_name = 'group_content';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'audio';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Content',
    'weight' => '0',
    'children' => array(
      0 => 'field_audio_audio',
      1 => 'field_audio_transcription',
      2 => 'field_image',
      3 => 'title',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-content field-group-fieldset',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_content|node|audio|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_content|node|document|form';
  $field_group->group_name = 'group_content';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'document';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Content',
    'weight' => '0',
    'children' => array(
      0 => 'field_doc_attachment',
      1 => 'field_doc_pages',
      2 => 'field_doc_text',
      3 => 'field_image',
      4 => 'title',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-content field-group-fieldset',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_content|node|document|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_content|node|music_video|form';
  $field_group->group_name = 'group_content';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'music_video';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Content',
    'weight' => '0',
    'children' => array(
      0 => 'field_video_transcription',
      1 => 'field_video_video',
      2 => 'title',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-content field-group-fieldset',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_content|node|music_video|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_content|node|video|form';
  $field_group->group_name = 'group_content';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'video';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Content',
    'weight' => '0',
    'children' => array(
      0 => 'field_image',
      1 => 'field_video_transcription',
      2 => 'field_video_video',
      3 => 'title',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-content field-group-fieldset',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_content|node|video|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_syllabus|node|audio|default';
  $field_group->group_name = 'group_syllabus';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'audio';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Syllabus',
    'weight' => '4',
    'children' => array(
      0 => 'field_unit',
      1 => 'field_priority',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-syllabus field-group-fieldset',
      ),
    ),
  );
  $export['group_syllabus|node|audio|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_syllabus|node|audio|form';
  $field_group->group_name = 'group_syllabus';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'audio';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Syllabus',
    'weight' => '2',
    'children' => array(
      0 => 'field_unit',
      1 => 'field_priority',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-syllabus field-group-fieldset',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_syllabus|node|audio|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_syllabus|node|document|default';
  $field_group->group_name = 'group_syllabus';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'document';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Syllabus',
    'weight' => '3',
    'children' => array(
      0 => 'field_priority',
      1 => 'field_unit',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Syllabus',
      'instance_settings' => array(
        'classes' => 'group-syllabus field-group-fieldset',
        'description' => '',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $export['group_syllabus|node|document|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_syllabus|node|document|form';
  $field_group->group_name = 'group_syllabus';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'document';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Syllabus',
    'weight' => '2',
    'children' => array(
      0 => 'field_priority',
      1 => 'field_unit',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-syllabus field-group-fieldset',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_syllabus|node|document|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_syllabus|node|image|default';
  $field_group->group_name = 'group_syllabus';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'image';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Syllabus',
    'weight' => '2',
    'children' => array(
      0 => 'field_priority',
      1 => 'field_unit',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-syllabus field-group-fieldset',
      ),
    ),
  );
  $export['group_syllabus|node|image|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_syllabus|node|image|form';
  $field_group->group_name = 'group_syllabus';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'image';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Syllabus',
    'weight' => '3',
    'children' => array(
      0 => 'field_priority',
      1 => 'field_unit',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-syllabus field-group-fieldset',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_syllabus|node|image|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_syllabus|node|music_video|default';
  $field_group->group_name = 'group_syllabus';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'music_video';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Syllabus',
    'weight' => '8',
    'children' => array(
      0 => 'field_unit',
      1 => 'field_priority',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-syllabus field-group-fieldset',
      ),
    ),
  );
  $export['group_syllabus|node|music_video|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_syllabus|node|music_video|form';
  $field_group->group_name = 'group_syllabus';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'music_video';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Syllabus',
    'weight' => '2',
    'children' => array(
      0 => 'field_unit',
      1 => 'field_priority',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-syllabus field-group-fieldset',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_syllabus|node|music_video|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_syllabus|node|video|default';
  $field_group->group_name = 'group_syllabus';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'video';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Syllabus',
    'weight' => '12',
    'children' => array(
      0 => 'field_priority',
      1 => 'field_unit',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Syllabus',
      'instance_settings' => array(
        'classes' => 'group-syllabus field-group-fieldset',
        'description' => '',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $export['group_syllabus|node|video|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_syllabus|node|video|form';
  $field_group->group_name = 'group_syllabus';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'video';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Syllabus',
    'weight' => '2',
    'children' => array(
      0 => 'field_priority',
      1 => 'field_unit',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-syllabus field-group-fieldset',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_syllabus|node|video|form'] = $field_group;

  return $export;
}
