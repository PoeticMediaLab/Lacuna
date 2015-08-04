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
  $authcode = variable_get('course_authcode', 's3kr3t');
  if ($authcode == $form['authcode']['#value']) {
    // save a token for a week to ensure the Auth Code was entered on subsequent pages
    // see course_access()
    global $user;
    $key = "Course_Auth_Code_User_" . $user->uid;
    $token = md5(uniqid(rand(), true));
    user_cookie_save(array($key => $token)); // their copy
    $expiration = time() + (7 * 24 * 60 * 60); // seven days from now
    cache_set($key, $token, 'cache', $expiration); // our copy

    drupal_set_message("Your Course Setup Code was recognized, please contact a Lacuna Stories team member if you have any issues creating your course.");
    drupal_goto('createcourse-2');
  }
  else {
    drupal_set_message("Unfortunately, we do not recognize your Course Setup Code.  Please try again or contact a Lacuna Stories team member.");
    drupal_goto('createcourse');
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

  $form['additional_settings']['#access'] = FALSE;
  $form['body'][LANGUAGE_NONE][0]['format']['#access'] = FALSE;
  $form['og_roles_permissions']['#access'] = FALSE;

  unset($form['actions']['preview']);
  $form['field_unregistered_students'][LANGUAGE_NONE][0]['value']['#value'] = 0;
  $form['actions']['submit']['#prefix'] = '<div>Send my information to the Lacuna Stories team to begin setting up my course!</div>';
  $path = drupal_get_path('module', 'course');
  $form['#attached']['css'] = array("$path/course.css");
  $form['#attached']['js'] = array("$path/course.js");

  return drupal_render($form);
}

function course_set_up_materials($nid) {
  $node = node_load($nid);
  $output = "Thank you for submitting your course information to the Lacuna Stories team. You can now continue by indicating the course materials you'd like to host on Lacuna Stories, and to assign them for specific weeks or units. To continue, click \"Set Up Materials for <i>{$node->title}</i>\"<br />";
  $output .= "<br />";
  $output .= drupal_render(drupal_get_form('course_set_up_materials_form', $nid));
  return $output;
}

function course_set_up_materials_form($form, &$form_state, $nid) {
  // current taxo terms, if any
  $number_of_weeks = course_numerical_vocab_term_max("number_of_weeks_$nid");
  $units_vocab = taxonomy_vocabulary_machine_name_load("units_$nid");
  $units = array();
  foreach (taxonomy_term_load_multiple(array(), array('vid' => $units_vocab->vid)) as $unit) {
    $units[] = "<div class='term'><span class='name'>" . $unit->name . "</span><span class='fa fa-minus'></span></div>";
  }
  asort($units);

  $form['course_nid'] = array(
    '#type' => 'hidden',
    '#value' => $nid
  );
  $form['number_of_weeks'] = array(
    '#type' => 'select',
    '#title' => 'Assign Materials to Individual Weeks',
    '#options' => drupal_map_assoc(range(1,25)),
    '#description' => "How many individual class weeks are there in your course?",
    '#default_value' => $number_of_weeks,
    '#required' => TRUE
  );
  $form['units_themes'] = array(
    '#type' => 'fieldset',
    '#title' => 'Assign Materials to Units/Themes',
  );
  $require_units = (count($units))? FALSE: TRUE; // only require if there are no existing terms
  $form['units_themes']['term'] = array(
    '#type' => 'textfield',
    '#description' => "Add as individual units or themes to your course.",
    '#size' => 60,
    '#required' => $require_units,
  );
  $form['units_themes']['ajax_button'] = array(
    '#markup' => "<button class='form-submit' id='ajax-units'>Add Unit/Theme</button>",
    '#suffix' => "<div class='terms'>" . implode('', $units) . "</div>",
  );
  $path = drupal_get_path('module', 'course');
  $form['#attached']['css'] = array("$path/course.css");
  $form['#attached']['js'] = array("$path/course.js");

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Set Up Materials'
  );

  return $form;
}

function course_set_up_materials_form_submit($form, &$form_state) {
  $nid = $form_state['values']['course_nid'];
  # add terms to vocabs

  # number of week tags
  $vocab = taxonomy_vocabulary_machine_name_load("number_of_weeks_$nid");
  $max = $form_state['values']['number_of_weeks'];
  $tree = taxonomy_get_tree($vocab->vid);

  # updating an existing vocab
  if (count($tree)) {
    foreach ($tree as $week) {
      if ($week->name > $max) {
        taxonomy_term_delete($week->tid);
      }
    }
  }
  for ($i=1; $i <= $max; $i++) {
    course_create_taxo($vocab, $i, $i);
  }

  # unit/theme tags
  $vocab = taxonomy_vocabulary_machine_name_load("units_$nid");
  foreach(explode(',', $form_state['values']['term']) as $unit) {
    course_create_taxo($vocab, $unit);
  }
  drupal_goto("createcourse-4/$nid");
}

function course_ajax_add_unit_term() {
  $term = check_plain($_POST['term']);
  $nid = check_plain($_POST['nid']);
  $vocab = taxonomy_vocabulary_machine_name_load("units_$nid");
  foreach(explode(',', $term) as $unit) {
    course_create_taxo($vocab, $unit);
  }
  ajax_deliver();
}


function course_ajax_delete_unit_term($nid, $term) {
  $term = check_plain($term);
  $nid = check_plain($nid);
  $term = array_pop(taxonomy_get_term_by_name($term, "units_$nid"));
  if ($term) {
    taxonomy_term_delete($term->tid);
  }
  ajax_deliver();
}

function course_create_taxo($vocab, $tag, $weight = 0) {
  // check for existing term
  $tag = trim($tag);
  if (0 == count(taxonomy_get_term_by_name($tag, $vocab->machine_name)) && !empty($tag)) {
    $term = new stdClass();
    $term->name = $tag;
    $term->vid = $vocab->vid;
    $term->weight = $weight;
    taxonomy_term_save($term);
  }
}

/**
 * Get the largest term for a numerical vocabulary
 *
 * return integer or FALSE
 */
function course_numerical_vocab_term_max($vocab_machine_name) {
  # simple guard to ensure numerical vocabularies
  if ('number_of_weeks' != substr($vocab_machine_name, 0, 15)) {
    return FALSE;
  }
  return db_query('SELECT t.name
  FROM {taxonomy_vocabulary} v INNER JOIN {taxonomy_term_data} t ON v.vid=t.vid
  WHERE v.machine_name = :machine_name
  ORDER BY CAST(t.name AS SIGNED) DESC
  LIMIT 1', array(':machine_name' => $vocab_machine_name))->fetchField();

}

function course_add_material($nid) {
  $output = "<p>Please find your materials using the methods below, in the order they are assigned. You, as the instructor, are responsible for determining if the online or e-access materials you are assigning your students are available at your home institution. If they are, your students will likely not have to pay for these materials. Otherwise, they will be charged. This is a cumbersome part of digital course setup, but an important one. It also allows the Lacuna Stories team to most efficiently assist you securing materials not available from your institutions digital resources. If you have any questions at any time, please send a quick email to info@lacunastories.com and someone from our team will assist you.</p><br /><div class='add-materials'>";

  $output .= "<div id='archived-materials'><div>Add Lacuna Stories Archived Materials. These materials may be free or available for a fee for your students. In either case, these are already digitized and using these materials will save you or the Lacuna Stories team time.</div><button class='form-submit'><a href='/archived-materials'>Search Lacuna Stories</a></button></div>";

  $output .= "<div id='e-access'><div>Add E-Access Material from my Institution. If your students have digital access to materials through your institution’s library, they may have free access to those same materials on Lacuna Stories. Save your students money!</div><button class='form-submit'>Confrim E-Access Material</button></div>";

  $output .= "<div id='studynet'><div>Request Copyright Permission. The Lacuna Stories team, in partnership with Study.Net, will obtain permission, directly from the publisher or an intermediary service, to use the material you identify.</div><button class='form-submit'>Request Copyright Permission</button></div></div>";

  global $user;
  module_load_include('inc', 'node', 'node.pages');
  $biblio = (object) array(
    'uid' => $user->uid,
    'name' => (isset($user->name) ? $user->name : ''),
    'type' => BIBLIO_NODE_TYPE,
    'language' => LANGUAGE_NONE,
  );
  $form = drupal_get_form(BIBLIO_NODE_TYPE . '_node_form', $biblio);

  $output .= "<div class='biblio-form'>" . drupal_render($form) . "</div>";
  $output .= views_embed_view('documents', 'course_block');
  return $output;
}

function course_switch_course($gid) {
  if ($group = node_load ($gid)) {
    if ($group->type == 'course') {
      if (og_is_member('node', $gid)) {
        _course_set_selected_course($gid);
        drupal_goto('materials'); // After setting the context, redirect user to the course materials page
      }
    }
  }
  drupal_access_denied();
}

// blank page
function course_blank_page() {
  return ' ';
}

// The about course callback, simply redirects to the user's currently selected course
function course_about_course() {
  if ($current_course = course_get_selected_course()) {
    drupal_goto('node/' . $current_course);
  }
}
