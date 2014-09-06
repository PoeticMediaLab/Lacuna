<?php

/**
 * Annotator ctools plugin
 */
class UnsupportedAnnotatorPlugin extends AnnotatorPlugin {
  public function settingsForm() {
    $defaults = $this->settings();
    $form['message'] = array(
      '#type' => 'textfield',
      '#title' => t('Message'),
      '#default_value' => $defaults['message'],
      '#description' => t('The message that you wish to display to users.'),
    );
    return $form;
  }

  public function settings($defaults = array()) {
    $defaults = array(
      'message' => t("We're sorry the Annotator is not supported by this browser"),
    );
    return parent::settings($defaults);
  }

  public function setup() {
    drupal_add_js(drupal_get_path('module', 'annotator') . '/js/annotator_unsupported.js');
  }
}
