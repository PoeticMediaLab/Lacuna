<?php

/**
 * Annotator ctools plugin
 */
class StoreAnnotatorPlugin extends AnnotatorPlugin {
  public function settingsForm() {
    $defaults = $this->settings();
    $form['prefix'] = array(
      '#type' => 'textfield',
      '#title' => t('Prefix'),
      '#default_value' => $defaults['prefix'],
      '#description' => t('The store endpoint.'),
    );
    $form['urls'] = array(
      '#type' => 'fieldset',
      '#title' => t('URLs'),
      '#default_value' => '',
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );
    $form['urls']['create'] = array(
      '#type' => 'textfield',
      '#title' => t('Create'),
      '#default_value' => $defaults['urls']['create'],
    );
    $form['urls']['read'] = array(
      '#type' => 'textfield',
      '#title' => t('Read'),
      '#default_value' => $defaults['urls']['read'],
    );
    $form['urls']['update'] = array(
      '#type' => 'textfield',
      '#title' => t('Update'),
      '#default_value' => $defaults['urls']['update'],
    );
    $form['urls']['destroy'] = array(
      '#type' => 'textfield',
      '#title' => t('Destroy'),
      '#default_value' => $defaults['urls']['destroy'],
    );
    $form['urls']['search'] = array(
      '#type' => 'textfield',
      '#title' => t('Search'),
      '#default_value' => $defaults['urls']['search'],
    );
    return $form;
  }

  public function settings($defaults = array()) {
    $defaults = array(
      'prefix' => base_path() . 'annotation/api',
      'urls' => array(
        'create' => '/annotations',
        'read'   => '/annotations/:id',
        'update' => '/annotations/:id',
        'destroy' => '/annotations/:id',
        'search' => '/search',
      ),
    );
    return parent::settings($defaults);
  }

  public function setup() {
    $settings = $this->settings();
    drupal_add_js(array('annotator_store' => (array) $settings), 'setting');
    drupal_add_js(drupal_get_path('module', 'annotation') . '/js/annotator_store.js');
  }
}
