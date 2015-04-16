<?php
/**
 * @file
 * lacuna_stories_views.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function lacuna_stories_views_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'node-document-field_artifact_intercession'
  $field_instances['node-document-field_artifact_intercession'] = array(
    'bundle' => 'document',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Which of the following best describe your artifact?',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'taxonomy',
        'settings' => array(),
        'type' => 'taxonomy_term_reference_link',
        'weight' => 12,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_artifact_intercession',
    'label' => 'Intercession: Lepsis, Metalepsis, or Syndialepsis?',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_buttons',
      'weight' => 26,
    ),
  );

  // Exported field_instance: 'node-document-field_artifact_mode'
  $field_instances['node-document-field_artifact_mode'] = array(
    'bundle' => 'document',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Indicate the form and tone of the artifact.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'taxonomy',
        'settings' => array(),
        'type' => 'taxonomy_term_reference_link',
        'weight' => 13,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_artifact_mode',
    'label' => 'Mode: Tragedy | Irony | Comedy | Pathos ',
    'required' => 1,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_buttons',
      'weight' => 27,
    ),
  );

  // Exported field_instance: 'node-document-field_artifact_theme'
  $field_instances['node-document-field_artifact_theme'] = array(
    'bundle' => 'document',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'taxonomy',
        'settings' => array(),
        'type' => 'taxonomy_term_reference_link',
        'weight' => 10,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_artifact_theme',
    'label' => 'Your artifact principally primes which of the following?',
    'required' => 1,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_buttons',
      'weight' => 23,
    ),
  );

  // Exported field_instance: 'node-document-field_excess_mean_or_deficiency'
  $field_instances['node-document-field_excess_mean_or_deficiency'] = array(
    'bundle' => 'document',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Where would you locate your artifact in the series Excess, Mean, or Deficiency? (Number 5 being "Mean")',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'list',
        'settings' => array(),
        'type' => 'list_default',
        'weight' => 14,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_excess_mean_or_deficiency',
    'label' => 'Excess, Mean, or Deficiency?',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_buttons',
      'weight' => 28,
    ),
  );

  // Exported field_instance: 'node-document-field_explanation'
  $field_instances['node-document-field_explanation'] = array(
    'bundle' => 'document',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Provide a basic explanation for why you categorized this artifact as you did.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 20,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_explanation',
    'label' => 'Explanation',
    'required' => 1,
    'settings' => array(
      'text_processing' => 1,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'rows' => 5,
      ),
      'type' => 'text_textarea',
      'weight' => 24,
    ),
  );

  // Exported field_instance: 'node-document-field_force'
  $field_instances['node-document-field_force'] = array(
    'bundle' => 'document',
    'default_value' => array(
      0 => array(
        'value' => 0,
        'container' => array(
          'max_value' => 100,
          'min_value' => 0,
        ),
        'ignore' => FALSE,
      ),
    ),
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'number',
        'settings' => array(
          'decimal_separator' => '.',
          'prefix_suffix' => TRUE,
          'scale' => 0,
          'thousand_separator' => ' ',
        ),
        'type' => 'number_integer',
        'weight' => 17,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_force',
    'label' => 'Force',
    'required' => 0,
    'settings' => array(
      'max' => 100,
      'min' => 0,
      'prefix' => '',
      'suffix' => '',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'number',
      'settings' => array(
        'sliderfield_settings' => array(
          'adjust_field_max' => 'field_power',
          'adjust_field_min' => 'field_power',
          'animate' => 1,
          'display_bubble' => 0,
          'display_bubble_format' => '%{value}%',
          'display_ignore_button' => 1,
          'display_values' => 1,
          'display_values_format' => '%{value}%',
          'hide_inputs' => 1,
          'hide_slider_handle_when_no_value' => 0,
          'multi_value' => 0,
          'orientation' => 'horizontal',
          'range' => 0,
          'slider_length' => '',
          'slider_style' => 'red',
          'step' => 1,
        ),
      ),
      'type' => 'number',
      'weight' => 19,
    ),
  );

  // Exported field_instance: 'node-document-field_media_types'
  $field_instances['node-document-field_media_types'] = array(
    'bundle' => 'document',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'taxonomy',
        'settings' => array(),
        'type' => 'taxonomy_term_reference_link',
        'weight' => 7,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_media_types',
    'label' => 'What are the media of your artifact?',
    'required' => 1,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_buttons',
      'weight' => 7,
    ),
  );

  // Exported field_instance: 'node-document-field_participation_level'
  $field_instances['node-document-field_participation_level'] = array(
    'bundle' => 'document',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'In terms of primary orientation of the artifact under consideration, check those which apply.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'taxonomy',
        'settings' => array(),
        'type' => 'taxonomy_term_reference_link',
        'weight' => 11,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_participation_level',
    'label' => 'Participant Observation: Betrachtung',
    'required' => 1,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_buttons',
      'weight' => 25,
    ),
  );

  // Exported field_instance: 'node-document-field_politics'
  $field_instances['node-document-field_politics'] = array(
    'bundle' => 'document',
    'default_value' => array(
      0 => array(
        'value' => 0,
        'container' => array(
          'max_value' => 0,
          'min_value' => 100,
        ),
        'ignore' => FALSE,
      ),
    ),
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'number',
        'settings' => array(
          'decimal_separator' => '.',
          'prefix_suffix' => TRUE,
          'scale' => 0,
          'thousand_separator' => ' ',
        ),
        'type' => 'number_integer',
        'weight' => 19,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_politics',
    'label' => 'Politics',
    'required' => 0,
    'settings' => array(
      'max' => 100,
      'min' => 0,
      'prefix' => '',
      'suffix' => '',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'number',
      'settings' => array(
        'sliderfield_settings' => array(
          'adjust_field_max' => 'field_power',
          'adjust_field_min' => 'field_power',
          'animate' => 1,
          'display_bubble' => 0,
          'display_bubble_format' => '%{value}%',
          'display_ignore_button' => 1,
          'display_values' => 1,
          'display_values_format' => '%{value}%',
          'hide_inputs' => 1,
          'hide_slider_handle_when_no_value' => 0,
          'multi_value' => 0,
          'orientation' => 'horizontal',
          'range' => 0,
          'slider_length' => '',
          'slider_style' => 'green',
          'step' => 1,
        ),
      ),
      'type' => 'number',
      'weight' => 21,
    ),
  );

  // Exported field_instance: 'node-document-field_power'
  $field_instances['node-document-field_power'] = array(
    'bundle' => 'document',
    'default_value' => array(
      0 => array(
        'value' => 0,
        'container' => array(
          'max_value' => 0,
          'min_value' => 100,
        ),
        'ignore' => FALSE,
      ),
    ),
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'number',
        'settings' => array(
          'decimal_separator' => '.',
          'prefix_suffix' => TRUE,
          'scale' => 0,
          'thousand_separator' => ' ',
        ),
        'type' => 'number_integer',
        'weight' => 18,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_power',
    'label' => 'Power',
    'required' => 0,
    'settings' => array(
      'max' => 100,
      'min' => 0,
      'prefix' => '',
      'suffix' => '',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'number',
      'settings' => array(
        'sliderfield_settings' => array(
          'adjust_field_max' => 'field_force',
          'adjust_field_min' => 'field_force',
          'animate' => 1,
          'display_bubble' => 0,
          'display_bubble_format' => '%{value}%',
          'display_ignore_button' => 1,
          'display_values' => 1,
          'display_values_format' => '%{value}%',
          'hide_inputs' => 1,
          'hide_slider_handle_when_no_value' => 0,
          'multi_value' => 0,
          'orientation' => 'horizontal',
          'range' => 0,
          'slider_length' => '',
          'slider_style' => 'green',
          'step' => 1,
        ),
      ),
      'type' => 'number',
      'weight' => 20,
    ),
  );

  // Exported field_instance: 'node-document-field_privacy_level'
  $field_instances['node-document-field_privacy_level'] = array(
    'bundle' => 'document',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'taxonomy',
        'settings' => array(),
        'type' => 'taxonomy_term_reference_link',
        'weight' => 9,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_privacy_level',
    'label' => 'I would like this artifact to be viewable by:',
    'required' => 1,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_buttons',
      'weight' => 11,
    ),
  );

  // Exported field_instance: 'node-document-field_topics'
  $field_instances['node-document-field_topics'] = array(
    'bundle' => 'document',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'The case(s) with which this artifact engages.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'taxonomy',
        'settings' => array(),
        'type' => 'taxonomy_term_reference_plain',
        'weight' => 3,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_topics',
    'label' => 'Case',
    'required' => 1,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_buttons',
      'weight' => 4,
    ),
  );

  // Exported field_instance: 'taxonomy_term-topics-field_image'
  $field_instances['taxonomy_term-topics-field_image'] = array(
    'bundle' => 'topics',
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'image',
        'settings' => array(
          'image_link' => '',
          'image_style' => 'medium',
        ),
        'type' => 'image',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'taxonomy_term',
    'field_name' => 'field_image',
    'label' => 'Image',
    'required' => 0,
    'settings' => array(
      'alt_field' => 0,
      'default_image' => 0,
      'file_directory' => '',
      'file_extensions' => 'png gif jpg jpeg',
      'max_filesize' => '',
      'max_resolution' => '',
      'media_library_include_in_library' => FALSE,
      'min_resolution' => '',
      'title_field' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'image',
      'settings' => array(
        'preview_image_style' => 'thumbnail',
        'progress_indicator' => 'throbber',
      ),
      'type' => 'image_image',
      'weight' => 2,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Case');
  t('Excess, Mean, or Deficiency?');
  t('Explanation');
  t('Force');
  t('I would like this artifact to be viewable by:');
  t('Image');
  t('In terms of primary orientation of the artifact under consideration, check those which apply.');
  t('Indicate the form and tone of the artifact.');
  t('Intercession: Lepsis, Metalepsis, or Syndialepsis?');
  t('Mode: Tragedy | Irony | Comedy | Pathos ');
  t('Participant Observation: Betrachtung');
  t('Politics');
  t('Power');
  t('Provide a basic explanation for why you categorized this artifact as you did.');
  t('The case(s) with which this artifact engages.');
  t('What are the media of your artifact?');
  t('Where would you locate your artifact in the series Excess, Mean, or Deficiency? (Number 5 being "Mean")');
  t('Which of the following best describe your artifact?');
  t('Your artifact principally primes which of the following?');

  return $field_instances;
}
