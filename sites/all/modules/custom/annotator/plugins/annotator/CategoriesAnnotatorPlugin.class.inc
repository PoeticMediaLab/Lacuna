<?php

/*
  This code creates a form in Annotator settings for Categories, saves those selections to a global settings variable, and loads documents relevant to the plugin.
 */

class CategoriesAnnotatorPlugin extends AnnotatorPlugin {
  public function settingsForm() {
    $defaults = $this->settings();
    $count = 0;

    while ($count <= 3) {
      $name = $defaults['category'][$count]['category_name'];
      $form['category'][$count] = array(
        '#type' => 'fieldset',
        '#title' => t("{$name}"),
        '#collapsible' => TRUE,
        '#collapsed' => TRUE,
      );
      $form['category'][$count]['category_name'] = array(
        '#type' => 'textfield',
        '#title' => t('Change Name'),
        '#default_value' => $defaults['category'][$count]['category_name'],
      );
      // $form['category'][$count]['category_rank'] = array(
      // '#type' => 'textfield',
      // '#title' => t('Change the numeric rank of this category. 1 = highest.'),
      // '#default_value' => $defaults['category'][$count]['category_rank'],
      // );
      $form['category'][$count]['category_desc'] = array(
        '#type' => 'textfield',
        '#title' => t('Optional: One-line category description.'),
        '#default_value' => $defaults['category'][$count]['category_desc'],
      );
      $count++;
    }

    return $form;
  }


  /*  Values in $defaults are initial values used to populate the Categories settings form. These values are overridden if changed in the actual form. To access the form values, go to JS console and type Drupal.settings.category_list.
  */

  public function settings($defaults = array()) {
    $defaults = array(
      'category' => array(
        array(
          'category_name' => 'Comment',
          'category_desc' => '',
          ),
        array(
          'category_name' => 'Question',
          'category_desc' => '',
          ),
        array(
          'category_name' => 'Analyze',
          'category_desc' => '',
          ),
        array(
          'category_name' => 'Connect',
          'category_desc' => '',
        ),
      ),
    );
    return parent::settings($defaults);
  }

  public function setup() {
    $settings = $this->settings();
    // Sends the settings data to a global variable where JavaScript can access it. In JS console, type: Drupal.settings.category_list
    drupal_add_js(array('category_list' => (array) $settings), 'setting');

    //CSS file for Categories
    drupal_add_css(drupal_get_path('module', 'annotator') . '/css/categories.css');

    // Below: Creates the categories plugin for Annotator/Annotation.
    drupal_add_js(drupal_get_path('module', 'annotator') . '/js/annotator_categories.js');

    // Below: Extends the Annotator Class to include the Categories plugin.
    // drupal_add_js(drupal_get_path('module', 'annotator') . '/js/annotator-full-extension-categories.js');
    drupal_add_js(drupal_get_path('module', 'annotator') . '/js/categories_new.js');
    // drupal_add_js(drupal_get_path('module', 'annotator') . '/js/categories.js');
  }
}
