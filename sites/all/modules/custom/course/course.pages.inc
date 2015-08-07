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

/*
 * Pre-populate Units, Genre - Materials, and Genre - Responses
 * for a new course with some defaults
*/
function course_add_default_terms() {
	$default_prefix = 'course_default_';
	$taxonomies = ['units', 'genre_doc','genre_response'];
	foreach ($taxonomies as $taxonomy) {
		$vocab = taxonomy_vocabulary_machine_name_load($taxonomy);
		if (!empty($vocab)) {
			foreach (explode(',', variable_get($default_prefix . $taxonomy)) as $term) {
				$term = trim($term);
				course_create_taxonomy_term($vocab, $term);
			}
		}
	}
}

function course_set_up_materials($nid) {
	_course_set_selected_course($nid);
	course_add_default_terms();
  $output = "Thank you for submitting your course information to the Lacuna Stories team. You can now continue by indicating the course materials you'd like to host on Lacuna Stories, and to assign them for specific weeks or units. To continue, click \"Continue\"<br />";
  $output .= "<br />";
  $output .= drupal_render(drupal_get_form('course_set_up_materials_form', $nid));
  return $output;
}

// Update the form array for a course-specific list of taxonomy terms
function course_custom_taxonomy_form_setup(&$form, $taxonomy_name) {
	$items = [];
	foreach (course_get_terms_for_current_course($taxonomy_name) as $term) {
		$items[] = "<div class='term'><span class='fa fa-trash-o'></span><span class='name'>" . $term . "</span></div>";
	}
	$form[$taxonomy_name]['term']['#required'] = (count($items) == 0);
	$form[$taxonomy_name]['ajax_button'] = array(
		'#markup' => "<button class='form-submit ajax-add-term'>Add Item</button>",
		'#suffix' => "<div class='terms'>" . implode('', $items) . "</div>",
	);
}

function course_set_up_materials_form($form, &$form_state, $nid) {
  // Current Units terms for this course, if any
  $form['units'] = array(
    '#type' => 'fieldset',
    '#title' => 'Create units by which your course will be organized.',
		'#attributes' => array(
			'id' => 'units'
		)
  );
  $form['units']['term'] = array(
    '#type' => 'textfield',
    '#description' => 'Examples: "Week One," "Travel"',
    '#size' => 60,
  );
	course_custom_taxonomy_form_setup($form, 'units');

	// Current Genre terms for this courajax-se, if any
	$form['genre_doc'] = array(
		'#type' => 'fieldset',
		'#title' => 'Create genres to categorize course readings.',
		'#attributes' => array(
			'id' => 'genre_doc',
		),
	);
	$form['genre_doc']['term'] = array(
		'#type' => 'textfield',
		'#description' => 'Examples: "Scholarship," "Fiction"',
		'#size' => 60,
	);
	course_custom_taxonomy_form_setup($form, 'genre_doc');

	// Current Response genre terms for this course, if any
	$form['genre_response'] = array(
		'#type' => 'fieldset',
		'#title' => 'Create genres to categorize student responses.',
		'#attributes' => array(
			'id' => 'genre_response',
		),
	);
	$form['genre_response']['term'] = array(
		'#type' => 'textfield',
		'#description' => 'Examples: "Essay," "Reflection"',
		'#size' => 60,
	);
	course_custom_taxonomy_form_setup($form, 'genre_response');

	$path = drupal_get_path('module', 'course');
  $form['#attached']['css'] = array("$path/course.css");
	// TODO: refactor to include only the JS we need
	$form['#attached']['js'] = array("$path/course.js");

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Continue',
		'#attributes' => array(
			'CLASS' => 'lacuna-button',
		),
  );
  return $form;
}

// AJAX adds the taxonomy terms, so form submit doesn't need to handle it
function course_set_up_materials_form_submit($form, &$form_state) {
  $gid = course_get_selected_course();
	// TODO: uncomment next line to progress
	// TODO: remove need to pass $gid to each step
	// May not need to do anything else; taxonomies handled in previous step!
  drupal_goto("createcourse-4/$gid");
}

/*
 * Routines for per-course taxonomies
 */

// Returns results for query on course-based term in given vocabulary
function course_get_taxonomy_term_in_current_course($vocab_name, $term) {
	if (empty($vocab)) {
		return FALSE;
	}
	$gid = course_get_selected_course();
	$query = new EntityFieldQuery();
	$result = $query->entityCondition('entity_type', 'taxonomy_term')
		->entityCondition('bundle', $vocab_name)
		->fieldCondition('field_term_course', 'target_id', $gid, '=')
		->propertyCondition('name', $term)
		->execute();
	if (isset($result['taxonomy_term'])) {
		return $result['taxonomy_term'];
	}
	return FALSE;
}

function course_create_taxonomy_term($vocab, $tag, $weight = 0) {
	// first, check for existing term in per-course taxonomy
	$tag = trim($tag);
	if (!course_get_taxonomy_term_in_current_course($vocab->machine_name, $tag)) {
		// none found, create a new one
		$term = new stdClass();
		$term->name = $tag;
		$term->vid = $vocab->vid;
		$term->weight = $weight;
		$term->field_term_course[LANGUAGE_NONE][0]['target_id'] = course_get_selected_course();
		taxonomy_term_save($term);
	}
}

function course_ajax_add_term($vocab_name) {
	$terms = check_plain($_POST['terms']);
	$vocab = taxonomy_vocabulary_machine_name_load($vocab_name);
	foreach(explode(',', $terms) as $term) {
		course_create_taxonomy_term($vocab, $term);
	}
	ajax_deliver(NULL);
}

function course_ajax_delete_term($vocab_name, $term) {
	$terms = course_get_taxonomy_term_in_current_course($vocab_name, $term);
	if (!empty($term)) {
		foreach(array_keys($terms) as $tid) {
			// Should be only one, but this is easier
			taxonomy_term_delete($tid);
		}
	}
	ajax_deliver(NULL);
}

/**
 * Get the largest term for a numerical vocabulary
 *
 * return integer or FALSE
 */
//function course_numerical_vocab_term_max($vocab_machine_name) {
//  # simple guard to ensure numerical vocabularies
//  if ('number_of_weeks' != substr($vocab_machine_name, 0, 15)) {
//    return FALSE;
//  }
//  return db_query('SELECT t.name
//  FROM {taxonomy_vocabulary} v INNER JOIN {taxonomy_term_data} t ON v.vid=t.vid
//  WHERE v.machine_name = :machine_name
//  ORDER BY CAST(t.name AS SIGNED) DESC
//  LIMIT 1', array(':machine_name' => $vocab_machine_name))->fetchField();
//
//}

function course_add_material($nid) {
  global $base_url;

  $output = "<p>Please find your materials using the methods below, in the order they are assigned. You, as the instructor, are responsible for determining if the online or e-access materials you are assigning your students are available at your home institution. If they are, your students will likely not have to pay for these materials. Otherwise, they will be charged. This is a cumbersome part of digital course setup, but an important one. It also allows the Lacuna Stories team to most efficiently assist you securing materials not available from your institutions digital resources. If you have any questions at any time, please send a quick email to info@lacunastories.com and someone from our team will assist you.</p><br /><div class='add-materials'>";

  $output .= "<div id='archived-materials'><div>Add Lacuna Stories Archived Materials. These materials may be free or available for a fee for your students. In either case, these are already digitized and using these materials will save you or the Lacuna Stories team time.</div><button class='form-submit'><a href='" . $base_url . "/archived-materials'>Search Lacuna Stories</a></button></div>";

  $output .= "<div id='e-access'><div>Add E-Access Material from my Institution. If your students have digital access to materials through your institution’s library, they may have free access to those same materials on Lacuna Stories. Save your students money!</div><button class='form-submit'>Confirm E-Access Material</button></div>";

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
  if ($group = node_load($gid)) {
    if ($group->type == 'course') {
      if (og_is_member('node', $gid) || user_access('administer group')) {
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
    drupal_goto(drupal_get_path_alias('node/' . $current_course));
  }
}
