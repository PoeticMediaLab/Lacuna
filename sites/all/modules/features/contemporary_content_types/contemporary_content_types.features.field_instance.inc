<?php
/**
 * @file
 * contemporary_content_types.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function contemporary_content_types_field_default_field_instances() {
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
      'weight' => 12,
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
      'weight' => 13,
    ),
  );

  // Exported field_instance: 'node-document-field_artifact_projects'
  $field_instances['node-document-field_artifact_projects'] = array(
    'bundle' => 'document',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '(Upon selecting, you will have a text box that asks you to explain your choice)',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'taxonomy',
        'settings' => array(),
        'type' => 'taxonomy_term_reference_link',
        'weight' => 8,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_artifact_projects',
    'label' => 'To which projects/case(s) could your artifact pertain? ',
    'required' => 1,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_buttons',
      'weight' => 8,
    ),
  );

  // Exported field_instance: 'node-document-field_artifact_theme'
  $field_instances['node-document-field_artifact_theme'] = array(
    'bundle' => 'document',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '[required comment/text box for a basic explanation]',
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
      'weight' => 10,
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
      'weight' => 14,
    ),
  );

  // Exported field_instance: 'node-document-field_force_politics_power'
  $field_instances['node-document-field_force_politics_power'] = array(
    'bundle' => 'document',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Please select the proportion appropriate to your artifact. [configure below to a 100% ratio]',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'taxonomy',
        'settings' => array(),
        'type' => 'taxonomy_term_reference_link',
        'weight' => 15,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_force_politics_power',
    'label' => 'How Are Force, Politics, Power configured in your artifact',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_buttons',
      'weight' => 15,
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
    'label' => 'What are the media of your upload?',
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
      'weight' => 11,
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
      'weight' => 9,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('(Upon selecting, you will have a text box that asks you to explain your choice)');
  t('Excess, Mean, or Deficiency?');
  t('How Are Force, Politics, Power configured in your artifact');
  t('I would like this artifact to be viewable by:');
  t('In terms of primary orientation of the artifact under consideration, check those which apply.');
  t('Indicate the form and tone of the artifact.');
  t('Intercession: Lepsis, Metalepsis, or Syndialepsis?');
  t('Mode: Tragedy | Irony | Comedy | Pathos ');
  t('Participant Observation: Betrachtung');
  t('Please select the proportion appropriate to your artifact. [configure below to a 100% ratio]');
  t('To which projects/case(s) could your artifact pertain? ');
  t('What are the media of your upload?');
  t('Where would you locate your artifact in the series Excess, Mean, or Deficiency? (Number 5 being "Mean")');
  t('Which of the following best describe your artifact?');
  t('Your artifact principally primes which of the following?');
  t('[required comment/text box for a basic explanation]');

  return $field_instances;
}
