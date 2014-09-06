<?php

/**
 * Annotator ctools plugin
 */
class AuthAnnotatorPlugin extends AnnotatorPlugin {
  public function settingsForm() {
    $defaults = $this->settings();
    $form['tokenUrl'] = array(
      '#type' => 'textfield',
      '#title' => t('Token URL'),
      '#default_value' => $defaults['tokenUrl'],
    );
    $form['token'] = array(
      '#type' => 'textfield',
      '#title' => t('Token'),
      '#default_value' => $defaults['token'],
    );
    $form['autoFetch'] = array(
      '#type' => 'checkbox',
      '#title' => t('Token'),
      '#default_value' => $defaults['autoFetch'],
    );
    return $form;
  }

  public function settings($defaults = array()) {
    $defaults = array(
      'tokenUrl' => '/auth/token',
      'token' => NULL,
      'autoFetch' => TRUE,
    );
    return parent::settings($defaults);
  }

  public function setup() {
    $settings = $this->settings();
    drupal_add_js(array('annotator_auth' => (array) $settings), 'setting');
    drupal_add_js(drupal_get_path('module', 'annotator') . '/js/annotator_auth.js');
  }
}