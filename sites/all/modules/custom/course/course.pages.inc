<?php

/**
 * Course Creation Page; Menu callback.
 */
function course_create_authorize() {
  if (!variable_get('course_require_auth')) {
    drupal_goto('course-setup/add-course');
  }
  $output = "Thanks for your interest in setting up a Lacuna Stories course. Currently, courses are only being created after instructors have had a consultation with the Lacuna Stories team. To arrange a consultation, email <a href='info@lacunastories.com'>info@lacunastories.com</a>. If you have already been approved to create a course, please enter the Course Setup Code given to you by a Lacuna Stories team member.";

  $authcode_form = drupal_get_form('course_authcode_form');
  return $output . " " . drupal_render($authcode_form);
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
  $authcode = variable_get('course_authcode');
  if ($authcode == $form['authcode']['#value']) {
    // save a token for a week to ensure the Auth Code was entered on subsequent pages
    // see course_setup_access()
    global $user;
    $key = "Course_Auth_Code_User_" . $user->uid;
    $token = md5(uniqid(rand(), true));
    user_cookie_save(array($key => $token)); // their copy
    $expiration = time() + (7 * 24 * 60 * 60); // seven days from now
    cache_set($key, $token, 'cache', $expiration); // our copy

    drupal_set_message("Your Course Setup Code was recognized. Please contact a Lacuna Stories team member if you have any issues creating your course.");
    drupal_goto('course-setup/add-course');
  }
  else {
    drupal_set_message("Unfortunately, we do not recognize your Course Setup Code. Please try again or contact a Lacuna Stories team member.", 'warning');
    drupal_goto('course-setup');
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
		'status' => NODE_PUBLISHED,
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

/**
 * @return string
 *
 * A custom form so that instructors can easily add annotation tags to their course
 */
function course_annotation_tags_add() {
  $gid = course_get_selected_course();
  if ($gid == FALSE) {
    drupal_set_message(t('You are not associated with a course. Therefore, you cannot add tags for annotations.'), 'error');
    drupal_exit();
  }
  drupal_set_title('Add Tags for Annotations');
  $form = array(
    'term' => array(
      '#type' => 'textfield',
      '#title' => t('Tag name'),
      '#description' => t('Enter the tag for annotations as you would like it to appear to students. You may use spaces.'),
      '#size' => 36,
      '#required' => TRUE
    ),
    'submit' => array(
      '#type' => 'submit',
      '#value' => t('Submit'),
    )
  );

	return $form;
}

/**
 * Associate the annotation tag submitted with the appropriate course
 */
function course_annotation_tags_add_submit($form, &$form_state) {
  $gid = course_get_selected_course();
  if (!$gid) {
    drupal_set_message(t('You are not associated with any course. Therefore, we cannot create any tags for annotations.'), 'error');
    drupal_exit();
  }
  $vocab = taxonomy_vocabulary_machine_name_load('annotation_tags');
  $term = $form_state['values']['term'];
  course_create_taxonomy_term($vocab, $term);
  drupal_set_message(t('"' . $term . '" has been added to the list of tags for annotations.'));
}

/*
 * Pre-populate Units, Genre - Materials, and Genre - Responses
 * for a new course with some defaults
*/
function course_add_default_terms() {
	$default_prefix = 'course_default_';
	$taxonomies = ['units', 'genre_doc','genre_response'];
	foreach ($taxonomies as $taxonomy) {
		// Add only if this course doesn't already have terms for this vocabulary
		if (count(course_get_terms_for_current_course($taxonomy)) == 0) {
			$vocab = taxonomy_vocabulary_machine_name_load($taxonomy);
			if (!empty($vocab)) {
				foreach (explode(',', variable_get($default_prefix . $taxonomy)) as $term) {
					$term = trim($term);
					course_create_taxonomy_term($vocab, $term);
				}
			}
		}
	}
}

function course_organize() {
	// For JS access
	drupal_add_js(array(
		'course' => array(
			'current_course' => course_get_selected_course()
		)), 'setting');
	course_add_default_terms();
  $output = "Thank you for submitting your course information to the Lacuna Stories team. You can now continue by naming the units and genres by which you would like to organize course materials. A few defaults have been chosen for you already. You may remove these by clicking on the trash icon (<span class='fa fa-trash-o'></span>). To continue, click \"Continue\"<br />";
  $output .= "<br />";
	$form = drupal_get_form('course_organize_form');
  $output .= drupal_render($form);
  return $output;
}

// Update the form array for a course-specific list of taxonomy terms
function course_organize_form_set_defaults(&$form, $taxonomy_name) {
	$items = [];
	foreach (course_get_terms_for_current_course($taxonomy_name) as $term) {
		$items[] = "<div class='term'><span class='fa fa-trash-o'></span> <span class='name'>" . $term . "</span></div>";
	}
	$form[$taxonomy_name]['term']['#required'] = (count($items) == 0);
	$form[$taxonomy_name]['ajax_button'] = array(
		'#markup' => "<button class='form-submit ajax-add-term'>Add Item</button>",
		'#suffix' => "<div class='terms'>" . implode('', $items) . "</div>",
	);
}

function course_organize_form($form, &$form_state) {
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
	course_organize_form_set_defaults($form, 'units');

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
	course_organize_form_set_defaults($form, 'genre_doc');

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
	course_organize_form_set_defaults($form, 'genre_response');

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
function course_organize_form_submit($form, &$form_state) {
	// Don't need to do anything else; taxonomies handled in previous step
	// TODO: Skip taxonomy submission
  drupal_goto("course-setup/add-materials");
}

/*
 * Routines for per-course taxonomies
 */

// Returns results for query on course-based term in given vocabulary
function course_get_taxonomy_term_in_current_course($vocab_name, $term) {
	if (empty($vocab_name)) {
		return FALSE;
	}
	$gid = course_get_selected_course();
	if ($gid) {
		$query = new EntityFieldQuery();
		$result = $query->entityCondition('entity_type', 'taxonomy_term')
			->entityCondition('bundle', $vocab_name)
			->fieldCondition('field_term_course', 'target_id', $gid, '=')
			->propertyCondition('name', $term)
			->execute();
		if (isset($result['taxonomy_term'])) {
			return $result['taxonomy_term'];
		}
	}
	return FALSE;
}

function course_create_taxonomy_term($vocab, $tag, $weight = 0) {
	// first, check for existing term in per-course taxonomy
	$tag = trim($tag);
	if (course_get_taxonomy_term_in_current_course($vocab->machine_name, $tag) == FALSE) {
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
  // TODO: Load existing terms
  // TODO: Determine highest weight
  // TODO: Increment by one
  // TODO: Pass weight to course_create_taxonomy_term()
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

function course_add_material() {
  global $base_url;

  $output = "<p>You, as the instructor, are responsible for determining if the online or e-access materials you are assigning your students are available at your home institution. If you have any questions at any time, please email " .l('info@lacunastories.com', 'mailto:info@lacunastories.com', array('absolute' => TRUE)) . " and someone from our team will assist you.</p><br /><div class='add-materials'>";

//  $output .= "<div id='archived-materials' class='explanation'><div>Add Lacuna Stories Archived Materials. These materials may be free or available for a fee for your students. In either case, these are already digitized and using these materials will save you or the Lacuna Stories team time.</div><button class='form-submit'><a href='" . $base_url . "/archived-materials'>Search Lacuna Stories</a></button></div>";

//  $output .= "<div id='e-access'><div>Add E-Access Material from my Institution. If your students have digital access to materials through your institution’s library, they may have free access to those same materials on Lacuna Stories. Save your students money!</div><button class='form-submit'>Confirm E-Access Material</button></div>";

//  $output .= "<div id='studynet'><div>Request Copyright Permission. The Lacuna Stories team, in partnership with Study.Net, will obtain permission, directly from the publisher or an intermediary service, to use the material you identify.</div><button class='form-submit'>Request Copyright Permission</button></div></div>";

	  $output .= "<div id='add-documents' class='explanation'><div>Add materials to your course. Note: You are responsible for ensuring that you have permission to publish these materials for your course.</div><button class='form-submit'>Add Materials</button></div></div>";

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

// Autocomplete tags, but only for current course
// TODO: Add curated tags distinction
// TODO: Add comma-separated values for multiples
function course_tags_autocomplete($name, $match) {
	$matches = array();
	foreach (course_get_terms_for_current_course($name) as $tid => $term) {
		if (preg_match('/' . $match . '/i', $term)) {
			$matches[$term] = $term;
		}
	}
	drupal_json_output($matches);
}