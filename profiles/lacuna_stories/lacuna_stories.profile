<?php

/**
 * Implements hook_form_FORM_ID_alter().
 *
 * Allows the profile to alter the site configuration form.
 */
if (!function_exists("system_form_install_configure_form_alter")) {
  function system_form_install_configure_form_alter(&$form, $form_state) {
    $form['site_information']['site_name']['#default_value'] = 'Lacuna Stories';
  }
}

/**
 * Implements hook_install_tasks().
 * Profile install tasks run after the main profile installation in lacuna_stories_install
 */
function lacuna_stories_install_tasks($install_state) {
  $tasks = array (
    'lacuna_stories_create_research_consent_webform' => array(
//      'display_name' => st('Create research consent form')
    ),
    'lacuna_stories_create_basic_page_type' => array(),
    'lacuna_stories_create_default_content' => array(
//      'display_name' => st('Create static pages')
    ),
    'lacuna_stories_set_basic_pages_permissions' => array(
//      'display_name' => st('Set page permissions')
    ),
    // hide main_menu(it belongs to superfish) and secondary_menu
    'lacuna_stories_manage_theme_settings' => array(
//      'display_name' => st('Tweak theme settings')
    ),
    // set JQuery version to 1.7
    'lacuna_stories_set_jquery_default' => array(
//      'display_name' => st('Set default jQuery version')
    ),
    'lacuna_stories_set_media_settings' => array(
//      'display_name' => st('Media settings')
    ),
    'lacuna_stories_set_annotator_settings' => array(
//      'display_name' => st('Enable Annotator.js plugins')
    ),
    'lacuna_stories_create_publication_state_workflow' => array(
//      'display_name' => st('Create publication workflow')
    ),
    'lacuna_stories_late_feature_and_module_enabling' => array(
//      'display_name' => st('Finish enabling modules')
    ),
		'lacuna_stories_revert_features_final' => array(
//      'display_name' => st('Revert features')
    ),
		// Must come after feature enable to ensure taxonomies for default terms exist
		'lacuna_stories_default_tax_terms' => array(
//      'display_name' => st('Create default taxonomy terms')
    ),
  );
  return $tasks;
}

function lacuna_stories_create_basic_page_type() {
  // Add the "Basic Page" type that appears in a standard install
  $types = array(
    array(
      'type' => 'page',
      'name' => st('Basic page'),
      'base' => 'node_content',
      'description' => st("Use <em>basic pages</em> for your static content, such as an 'About us' page."),
      'custom' => 1,
      'modified' => 1,
      'locked' => 0,
    ),
  );

  foreach ($types as $type) {
    $type = node_type_set_defaults($type);
    node_type_save($type);
    node_add_body_field($type);
  }
  // disable comments and author info on basic pages
  variable_set('node_submitted_page', 0);
  variable_set('comment_page', COMMENT_NODE_CLOSED);
}

// Return the plid for a parent menu item in main-menu with given title
function lacuna_stores_get_main_menu_plid($title) {
  $main_menu = menu_load_links('main-menu');
  foreach ($main_menu as $menu_link) {
    if ($menu_link['link_title'] == $title) {
      return $menu_link['mlid'];
    }
  }
}

/*
  Creating Digital research consent webform.
 */
function lacuna_stories_create_research_consent_webform() {
  $node = new stdClass();
  $node->type = 'webform';
  node_object_prepare($node);
  $node->title    = 'Digital Research Consent Form';
  $node->language = LANGUAGE_NONE; // Or other language.
  $node->body[$node->language][0]['value'] = file_get_contents(DRUPAL_ROOT . "/profiles/lacuna_stories/content/consent_form.html");;
  $node->body[$node->language][0]['format']  = 'full_html';
  $node->uid = 1;     // Set admin as author
  $node->promote = 0; // Do not put this node to front page.
  $node->comment = 1; // Closed the comment.

  // Create the webform components.
  $components = array(
    0 => array(
      'name' => 'By checking the “agree” box below, you agree to allowing your anonymized user data reflecting site usage and/or survey responses to be used for research purposes.',
      'form_key' => 'agree',
      'type' => 'select',
      'mandatory' => 0,
      'weight' => 0,
      'pid' => 0,
      'extra' => array (
        'items' => "yes|Agree\nno|Disagree",
        'multiple' => 0,
        'title_display' => 'before',
        'private' => 0,
        'aslist' => 0,
        'optrand' => 0,
        'conditional_operator' => '=',
      ),
    ),
    1 => array(
      'name' => 'I am at least 18 years old',
      'form_key' => 'over_18',
      'type' => 'select',
      'mandatory' => 1,
      'weight' => 1,
      'pid' => 0,
      'extra' => array (
        'items' => "no|No\nyes|Yes",
        'multiple' => 0,
        'title_display' => 'before',
        'private' => 0,
        'aslist' => 0,
        'optrand' => 0,
        'conditional_operator' => '=',
      ),
    ),
  );

  // Setup notification email.
  $emails = array(
    //  0 => array(
    // 'email' => 'abc@def.com',
    // 'subject' => 'default',
    // 'from_name' => 'default',
    // 'from_address' => 'default',
    // 'template' => 'default',
    // 'excluded_components' => array(),
    //  ),
  );

  // Attach the webform to the node.
  $node->webform = array(
    'confirmation' => '',
    'confirmation_format' => NULL,
    'redirect_url' => '<confirmation>',
    'status' => '1',
    'block' => '0',
    'teaser' => '0',
    'allow_draft' => '0',
    'auto_save' => '0',
    'submit_notice' => '1',
    'submit_text' => '',
    'submit_limit' => '-1', // User can submit more than once.
    'submit_interval' => '-1',
    'total_submit_limit' => '-1',
    'total_submit_interval' => '-1',
    'record_exists' => TRUE,
    'roles' => array(
      0 => '1', // Anonymous user can submit this webform.
      1 => '2', // Authenticated user can submit this webform.
    ),
    'emails' => $emails,
    'components' => $components,
  );
  
  $node = node_submit($node); // Prepare node for a submit
  node_save($node);

  // Node ids change, so we must add the menu item after the webform is created
  $menu_item = array(
    'link_path' => 'node/' . $node->nid,
    'link_title' => 'Digital Research Consent Form',
    'menu_name' => 'main-menu',
    'weight' => 10,
    'language' => $node->language,
    'module' => 'menu',
    'plid' => lacuna_stores_get_main_menu_plid('Account'),
  );
  menu_link_save($menu_item);
}

function lacuna_stories_block_info() {
  $blocks = array();
  $blocks['front_page_banner'] = array(
    'info' => t('Front Page Banner'),
  );
  return $blocks;
}

function lacuna_stories_block_view($delta = '') {
  $block = array();
  switch ($delta) {
    case 'front_page_banner':
      $block['subject'] = '';
      $block['content'] = file_get_contents(DRUPAL_ROOT . "/profiles/lacuna_stories/content/banner.html");
      break;
  }
  return $block;
}

/*
  Creating default content like FAQ, "Instructor's Guide", etc.
 */
function lacuna_stories_create_default_content() {

  $content[0]["title"] = "FAQ";
  $content[0]["body"] = file_get_contents(DRUPAL_ROOT . "/profiles/lacuna_stories/content/faq.html");;

  $content[1]["title"] = "Instructor's Guide";
  $content[1]["body"] = file_get_contents(DRUPAL_ROOT . "/profiles/lacuna_stories/content/instructors_guide.html");

  $content[2]["title"] = "Student User Guide";
  $content[2]["body"] = file_get_contents(DRUPAL_ROOT . "/profiles/lacuna_stories/content/student_user_guide.html");;

  foreach ($content as $page) {
    $node = new stdClass(); // We create a new node object
    $node->type = "page"; // Or any other content type you want
    $node->title = $page["title"];
    $node->language = LANGUAGE_NONE; // Or any language code if Locale module is enabled. More on this below *
    $node->body[$node->language][0]['format']  = 'full_html';
    $node->body[$node->language][0]['value'] = $page["body"];

    node_object_prepare($node); // Set some default values.
    $node->uid = 1; // Or any id you wish
    $node = node_submit($node); // Prepare node for a submit
    node_save($node); // After this call we'll get a nid
    // Node ids change, so we must add the menu item after the webform is created
    $plid = lacuna_stores_get_main_menu_plid('Help');
    $menu_item = array(
      'link_path' => 'node/' . $node->nid,
      'link_title' => $node->title,
      'menu_name' => 'main-menu',
      'weight' => 10,
      'language' => $node->language,
      'module' => 'menu',
      'plid' => $plid,
    );
    menu_link_save($menu_item);
  }
}

/*
  Currently changes permissions for page "Instructor's Guide" only. But the same code can be used to change permissions for other pages too.
 */
function lacuna_stories_set_basic_pages_permissions()
{
  if (!function_exists('content_access_set_settings')) {
    // this module should already be enabled
    // but sometimes it isn't. why?
    module_enable(array('content_access'));
  }
  content_access_set_settings(array("per_node" => 1), "page");    // turn per_node content_access 1, for basic pages
  $instructor = user_role_load_by_name("Instructor")->rid;

  $settings = array(
    'view' => array($instructor),
    'view_own' => array(),
    'update' => array(),
    'update_own' => array(),
    'delete' => array(),
    'delete_own' => array()
  );

  $query = new EntityFieldQuery();
  $entities = $query->entityCondition('entity_type', 'node')
    ->propertyCondition('type', 'page')
    ->propertyCondition('title', "Instructor's Guide")
    ->propertyCondition('status', 1)
    ->range(0,1)
    ->execute();

  $nid = array_keys($entities['node'])[0];
  $node = node_load($nid);

  content_access_save_per_node_settings($node, $settings);
  // Apply new settings.
  node_access_acquire_grants($node);

  module_invoke_all('per_node', $settings);
  node_access_rebuild();  // rebuild for changes to make effect
}

//  toggle off main_menu and secondary_menu
function lacuna_stories_manage_theme_settings()
{
  $ts = variable_get("theme_settings");
  $ts["toggle_main_menu"] = 0;
  $ts["toggle_secondary_menu"] = 0;
  variable_set("theme_settings", $ts);
}

// set jquery version.
function lacuna_stories_set_jquery_default()
{
  variable_set('jquery_update_jquery_version', '1.7');
}

// set media settings
function lacuna_stories_set_media_settings(){
  variable_set("file_entity_file_upload_wizard_skip_scheme", 1); // this is actually a file entity setting but is available on the media form at admin/config/media/file-settings
}

// set annotator settings
function lacuna_stories_set_annotator_settings() {
  variable_set("annotator_element", 'article.node'); // TODO: check if this is necessary
  // enable some annotator plugins
  variable_set("annotator_plugins", array (
    'Store' => 'Store',
    'Unsupported' => 'Unsupported',
    'Touch' => 'Touch',
    'Categories' => 'Categories',
    'Richtext' => 'Richtext',
    'Filters' => 'Filters',
//    'Comment' => 'Comment', // Disabled until fixed
    'Tags' => 'Tags',
    'Privacy' => 'Privacy',
		'Histogram' => 'Histogram',
		'Author' => 'Author',
    'Controls' => 'Controls',
    'Loading' => 'Loading',
  ));
}

// set default taxonomy terms
function lacuna_stories_default_tax_terms () {
  $taxonomy = array(
    'priority' => array(
      'Required',
      'Suggested',
      'Supplementary',
    ),
    'medium' => array(
      'Document',
      'Video',
      'Audio',
      'Image',
    ),
    'annotation_categories' => array(
      'Comment',
      'Question',
      'Analyze',
      'Compare'
    ),
  );
  foreach ($taxonomy as $vocabulary_name => $terms) {
    // Add a default term to each vocabulary.
		// Vocabularies are created in a feature
    $vocabulary = taxonomy_vocabulary_machine_name_load($vocabulary_name);
    if (isset($vocabulary->vid)) {
      $weight = 0;  // weight them as ordered in their arrays
      foreach ($terms as $name) {
        $term = new stdClass();
        $term->name = $name;
        $term->vid = $vocabulary->vid;
        $term->weight = $weight;
        taxonomy_term_save($term);
        ++$weight;
      }
    }
  }
}


// Install task: create workflow states and transitions
function lacuna_stories_create_publication_state_workflow() {
  $system_roles = user_roles();
  $workflow = NULL;

  // Create a workflow.
  $workflow = workflow_create('Materials Publication States');
  $workflow->save();

  // Create States for the workflow.
  $s1 = $workflow->createState('(creation)');
  $s2 = $workflow->createState('Draft');
  $s3 = $workflow->createState('Ready for Annotation');
  $s1->save();
  $s2->save();
  $s3->save();

  // Define the transitions per role set in $transition_chunks
  $transition_chunks = array (
    array (
      'roles' => array(-1, 'Site Administrator', 'Content Manager', 'Instructor'),
      'transitions' => array (
        array (
          'sid' => $s1,
          'target_sid' => $s2
        ),
        array (
          'sid' => $s2,
          'target_sid' => $s3
        ),
      ),
    ),
    array (
      'roles' => array('Site Administrator', 'Content Manager'),
      'transitions' => array (
        array (
          'sid' => $s3,
          'target_sid' => $s2
        ),
      ),
    ),
    array (
      'roles' => array('Site Administrator'),
      'transitions' => array (
        array (
          'sid' => $s1,
          'target_sid' => $s3
        ),
      ),
    ),
  );

  // Create Transitions for the workflow
  foreach ($transition_chunks as $transition_chunk) {
    foreach ($transition_chunk['transitions'] as $transition) {

      // Create transition
      $from = $transition['sid'];
      $to = $transition['target_sid'];
      $transition_obj = $workflow->createTransition($from->sid, $to->sid);
      //$transition_obj->label = '"' . $from->name . '" to "' . $to->name . '"';
      $transition_obj->label = $to->name;

      // Assign roles for the transition
      $rids_to_assign = array();
      foreach ($transition_chunk['roles'] as $transition_role) {
        if (is_numeric($transition_role)) {
          $rids_to_assign[] = $transition_role;
        }
        else {
          if ($rid = array_search($transition_role, $system_roles)) {
            $rids_to_assign[] = $rid;
          }
          else {
            drupal_set_message ('Could not find a role ID for "' . $transition_role . '" when creating workflow transitions.');
            continue 2;
          }

        }
      }
      $transition_obj->roles = $rids_to_assign;
      $transition_obj->save();
    }
  }

}

// Enable any modules or features that need to be enabled after other installation tasks are done
function lacuna_stories_late_feature_and_module_enabling () {
  $module_list = array(
		'lacuna_stories_materials',	// Depends on the Workflow for Materials Publications
		'lacuna_stories_threads',	// Depends on Materials
		'lacuna_stories_responses',	// Depends on Materials
		'lacuna_stories_irb_form', // Webform is created on install
    'lacuna_stories_visualizations', // Visualizations require responses to be active
  );
  module_enable($module_list);
}

// ensure features are reverted since things have been done since the initial reversion in hook_install
function lacuna_stories_revert_features_final () {
  // Do it twice with a cache clear in-between to make sure we get everything
  features_rebuild();
  features_revert();
  drupal_flush_all_caches();
  features_rebuild();
  features_revert();
}