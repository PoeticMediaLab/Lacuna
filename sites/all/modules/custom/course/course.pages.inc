<?php

/**
 * Course Creation Page; Menu callback.
 */
function course_create_authorize() {
  $output = "Thanks for your interest in setting up a Lacuna Stories course. Currently, courses are only being created after instructors have had a consultation with the Lacuna Stories team. To arrange a consultation, email <a href='info@lacunastories.com'>info@lacunastories.com</a>. If you have already been approved to create a course, please enter the Course Setup Code given to you by a Lacuna Stories team member.";

  $authcode_form = drupal_render(drupal_get_form('course_authcode_form'));
  return $output . " " . $authcode_form;
}

function course_authcode_form($form, &$form_state) {
  $form['authcode'] = array(
    '#type' => 'textfield',
    '#title' => 'Course Setup Code',
    '#size' => 10,
    '#required' => TRUE
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Authorize'
  );

  return $form;
}

function course_authcode_form_submit($form, &$form_state) {
  if ('s3kr3t' == $form['authcode']['#value']) {
    drupal_set_message("Your Course Setup Code was recognized, please contact a Lacuna Stories team member if you have any issues creating your course.");
    drupal_goto('createcourse-2');
  }
  else {
    drupal_set_message("Unfortunately, we do not recognize your Course Setup Code.  Please try again or contact a Lacuna Stories team member.");
    drupal_goto('createcourse');
  }
}


function course_form_alter(&$form, &$form_state, $form_id) {
  if ("course_node_form" == $form_id ) {
    $form['#submit'] = array('course_create_form_submit');
  }
}

function course_create() {
  global $user;
  module_load_include('inc', 'node', 'node.pages');
  $node = (object) array(
    'uid' => $user->uid,
    'name' => (isset($user->name) ? $user->name : ''),
    'type' => COURSE_NODE_TYPE,
    'language' => LANGUAGE_NONE,
  );
  $form = drupal_get_form(COURSE_NODE_TYPE . '_node_form', $node);
  
  $form['group_access']['#access'] = FALSE;
  $form['additional_settings']['#access'] = FALSE;
  unset($form['body'][LANGUAGE_NONE][0]['format']);
  unset($form['actions']['preview']);
  $form['field_unregistered_students'][LANGUAGE_NONE][0]['value']['#value'] = 0;
  $form['actions']['submit']['#prefix'] = '<div>Send my information to the Lacuna Stories team to begin setting up my course!</div>';
  $path = drupal_get_path('module', 'course'); 
  $form['#attached']['css'] = array("$path/course.css");
  $form['#attached']['js'] = array("$path/course.js");

  return drupal_render($form);
}

function course_create_form_submit($form, &$form_state) {
  # prevent the form from caching, which breaks our submit handler
  cache_clear_all('form_'. $_POST['form_build_id'], 'cache_form');

  $node = new stdClass();
  $node->type = COURSE_NODE_TYPE;
  foreach($form_state['values'] as $k => $v) {
    $node->$k = $v;
  }
  node_object_prepare($node);
  node_save($node);

  if ($node->nid) {
    drupal_goto("createcourse-3/" . $node->nid);
  }
  else {
    drupal_set_message("There was an error creating your course.  Please try again and/or contact the Lacuna Stories team for assistance, <a href='info@lacunastories.com'>info@lacunastories.com</a>.", 'error');
    drupal_goto("createcourse-2");
  }
}

function course_set_up_materials($nid) {
  $node = node_load($nid);
  $output = "Thank you for submitting your course information to the Lacuna Stories team. You can now continue by indicating the course materials you'd like to host on Lacuna Stories, and to assign them for specific classes, weeks, or units. To continue, click \"Set Up Materials for <i>{$node->title}</i>\"<br />";
  $output .= "<br />";
  $output .= drupal_render(drupal_get_form('course_set_up_materials_form'));
  $output .= "<br /><br />";
  $output .= "<button>Add Material<span class='fa fa-plus'></span></button><br /><br />";
  $output .= "<button>Done Adding Course Materials<span class='fa fa-check'></span></button><p><em>You can add more materials at any time</em></p><br /><br /><br />";
  $output .= "VIEW OF COURSE MATERIALS";
  return $output;
}

function course_set_up_materials_form($form, &$form_state) {
  $form['number_of_classes'] = array(
    '#type' => 'select',
    '#title' => 'Assign Materials to Individual Class Numbers',
    '#options' => drupal_map_assoc(range(1,50)),
    '#description' => "How many individual class sessions are there in your course?", 
    '#required' => TRUE
  );
  $form['number_of_weeks'] = array(
    '#type' => 'select',
    '#title' => 'Assign Materials to Individual Weeks',
    '#options' => drupal_map_assoc(range(1,25)),
    '#description' => "How many individual class weeks are there in your course?", 
    '#required' => TRUE
  );
  $form['units_themes'] = array(
    '#type' => 'textfield',
    '#title' => 'Assign Materials to Units/Themes',
    '#description' => "Add as individual units or themes to your course.", 
    '#size' => 60,
    '#required' => TRUE
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Save'
  );

  return $form;
}

function course_set_up_materials_form_submit($form, &$form_state) {
  # add terms to vocabs

  # numeric tags
  $voc_names = array('number_of_classes', 'number_of_weeks', 'units_themes');
  foreach(array('number_of_classes', 'number_of_weeks') as $voc_name) {
    $vocab = taxonomy_vocabulary_machine_name_load($voc_name);
    $max = $form_state['values'][$voc_name];
    for ($i=1; $i <= $max; $i++) {
      course_create_taxo($vocab, $i);
    }
  }

  # unit/theme tags
  $vocab = taxonomy_vocabulary_machine_name_load('units_themes');
  foreach(explode(',', $form_state['values']['units_themes']) as $unit) {
    course_create_taxo($vocab, $unit);
  }
}

function course_create_taxo($vocab, $tag) {
  // check for existing term
  if (0 == count(taxonomy_get_term_by_name($tag, $vocab->machine_name))) {
    $term = new stdClass();
    $term->name = $tag;
    $term->vid = $vocab->vid;
    taxonomy_term_save($term);
  }
}
