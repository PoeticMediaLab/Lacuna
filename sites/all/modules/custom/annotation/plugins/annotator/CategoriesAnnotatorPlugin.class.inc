<?php

/**
 * Annotator ctools plugin -- need to add default values
 */

//Get category to populate recursively. Right now, it just prints the first record.


// class CategoriesAnnotatorPlugin extends AnnotatorPlugin {

//   public function settingsForm() {
//     $result = db_query('SELECT * FROM annotation_categories');
//     // $count = 0;
//     foreach ($result as $record) {
//       $default = ucfirst($record->category_name);
//       // $count++
//       $form['category'] = array(
//       '#type' => 'fieldset',
//       '#title' => t('First Category'),
//       '#collapsible' => TRUE,
//       '#collapsed' => TRUE,
//     );
//     $form['category']['category_name'] = array(
//       '#type' => 'textfield',
//       '#title' => t('Category'),
//       //Need to add default values
//       '#default_value' => $default,
//     );
//     $form['category']['category_desc'] = array(
//       '#type' => 'textfield',
//       '#title' => t('Optional: One-line category description.'),
//       //Need to add default values
//       //'#default_value' => $defaults[''][''],
//     );
//     }


//     // $form['category1'] = array(
//     //   '#type' => 'fieldset',
//     //   '#title' => t('First Category'),
//     //   '#collapsible' => TRUE,
//     //   '#collapsed' => TRUE,
//     // );
//     // $form['category1']['category_name'] = array(
//     //   '#type' => 'textfield',
//     //   '#title' => t('Category'),
//     //   //Need to add default values
//     //   '#default_value' => 'test',
//     // );
//     // $form['category1']['category_desc'] = array(
//     //   '#type' => 'textfield',
//     //   '#title' => t('Optional: One-line category description.'),
//     //   //Need to add default values
//     //   //'#default_value' => $defaults[''][''],
//     // );
//     // $form['category2'] = array(
//     //   '#type' => 'fieldset',
//     //   '#title' => t('Second Category'),
//     //   '#collapsible' => TRUE,
//     //   '#collapsed' => TRUE,
//     // );
//     // $form['category2']['category_name'] = array(
//     //   '#type' => 'textfield',
//     //   '#title' => t('Category'),
//     //   //Need to add default values
//     //   //'#default_value' => $defaults[''][''],
//     // );
//     // $form['category2']['category_desc'] = array(
//     //   '#type' => 'textfield',
//     //   '#title' => t('Optional: One-line category description.'),
//     //   //Need to add default values
//     //   //'#default_value' => $defaults[''][''],
//     // );
//     // $form['category3'] = array(
//     //   '#type' => 'fieldset',
//     //   '#title' => t('Third Category'),
//     //   '#collapsible' => TRUE,
//     //   '#collapsed' => TRUE,
//     // );
//     // $form['category3']['category_name'] = array(
//     //   '#type' => 'textfield',
//     //   '#title' => t('Category'),
//     //   //Need to add default values
//     //   //'#default_value' => $defaults[''][''],
//     // );
//     // $form['category3']['category_desc'] = array(
//     //   '#type' => 'textfield',
//     //   '#title' => t('Optional: One-line category description.'),
//     //   //Need to add default values
//     //   //'#default_value' => $defaults[''][''],
//     // );
//     // $form['category4'] = array(
//     //   '#type' => 'fieldset',
//     //   '#title' => t('Fourth Category'),
//     //   '#collapsible' => TRUE,
//     //   '#collapsed' => TRUE,
//     // );
//     // $form['category4']['category_name'] = array(
//     //   '#type' => 'textfield',
//     //   '#title' => t('Category'),
//     //   //Need to add default values
//     //   //'#default_value' => $defaults[''][''],
//     // );
//     // $form['category4']['category_desc'] = array(
//     //   '#type' => 'textfield',
//     //   '#title' => t('Optional: One-line category description.'),
//     //   //Need to add default values
//     //   //'#default_value' => $defaults[''][''],
//     // );

//   return $form;
//   }


//   public function settings($defaults = array()) {
//     $defaults = array(
//       'category' => FALSE,
//     );
//         return parent::settings($defaults);
//   }


//   public function setup() {
//     //May need to add a CSS path here, like this:
//     // drupal_add_css(drupal_get_path('module', 'annotator') . '/css/annotorious.css');
//     drupal_add_js(drupal_get_path('module', 'annotator') . '/js/annotator_categories.js');
//   }
// }
