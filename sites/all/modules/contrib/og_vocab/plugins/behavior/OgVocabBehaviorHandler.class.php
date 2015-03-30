<?php

/**
 * OG vocab behavior handler.
 */
class OgVocabBehaviorHandler extends EntityReference_BehaviorHandler_Abstract {

  public function access($field, $instance) {
    return $field['settings']['target_type'] == 'taxonomy_term' && $instance['widget']['type'] == 'og_vocab_complex';
  }

  public function settingsForm($field, $instance) {
    $form = parent::settingsForm($field, $instance);

    $settings = !empty($field['settings']['handler_settings']['behaviors']['og_vocab']) ? $field['settings']['handler_settings']['behaviors']['og_vocab'] : array();
    $settings += array(
      'use_context' => 'yes',
    );

    $form['use_context'] = array(
      '#type' => 'select',
      '#title' => t('Use context'),
      '#required' => TRUE,
      '#options' => array(
        'force' => t('Hide widget if no context found'),
        'yes' => t('Use if possible'),
        'no' => t('Do not use'),
      ),
      '#description' => t('Should the OG vocabularies appear according to OG context. Depends on OG-context module.'),
      '#default_value' => $settings['use_context'],
    );
    return $form;
  }

  public function is_empty_alter(&$empty, $item, $field) {
    if (!empty($item['target_id']) && $item['target_id'] == 'autocreate') {
      $empty = FALSE;
    }
  }

  public function presave($entity_type, $entity, $field, $instance, $langcode, &$items) {
    foreach ($items as $delta => $item) {
      if ($item['target_id'] == 'autocreate') {
        $term = (object) $item;
        unset($term->tid);
        taxonomy_term_save($term);
        $items[$delta]['target_id'] = $term->tid;
      }
    }
  }
}
