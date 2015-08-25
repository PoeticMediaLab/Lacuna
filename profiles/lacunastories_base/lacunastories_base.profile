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
 * Implementing hook_block_info
 * Adding neccessary blocks:
 * 1. a phoney empty block to activate second sidebar
 */
function lacunastories_base_block_info()
{
    $theme = "lacuna_stories";
    $blocks = array();
    $regions = system_region_list($theme, REGIONS_VISIBLE);
    if(array_key_exists('sidebar_second', $regions)){    
        $blocks['sidebar_second_empty'] = array(
            "info" => "Phony block to activate second sidebar",
            'region' => 'sidebar_second',
            'theme' => "lacuna_stories",
            'status' => 1,
            'weight' => 0,
            'pages' => 'document/*',
            'visibility' => BLOCK_VISIBILITY_LISTED,
        );
    }
    return $blocks;
}

/**
 * Implementing hook_block_view
 * Goes in pair with hook_block_info
 */
function lacunastories_base_block_view($delta)
{
    $block = array();
    if($delta == 'sidebar_second_empty'){
        $block['content'] = "<b></b>";
    }
    return $block;
}

/**
 * Implements hook_install_tasks().
 * Profile install tasks run after the main profile installation in lacunastories_base_install
 */
function lacunastories_base_install_tasks($install_state) {
  $tasks = array (
    'lacunastories_base_create_research_consent_webform' => array(),
    'lacunastories_base_create_basic_pages' => array(),
    'lacunastories_base_set_basic_pages_permissions' => array(),
    'lacunastories_base_manage_theme_settings' => array(), // hide main_menu(it belongs to superfish) and secondary_menu
    'lacunastories_base_set_jquery_default' => array(), // set JQuery version to 1.7
    'lacunastories_base_set_media_settings' => array(),
    'lacunastories_base_set_annotator_settings' => array(),
    'lacunastories_base_default_tax_terms' => array(),
    'lacunastories_base_create_publication_state_workflow' => array(),
    'lacunastories_base_late_feature_and_module_enabling' => array(),
    'lacunastories_base_revert_features_final' => array(),


  );
  return $tasks;
}

/*
  Creating Digital research consent webform.
 */
function lacunastories_base_create_research_consent_webform()
{
  $node = new stdClass();
  $node->type = 'webform';
  node_object_prepare($node);
  $node->title    = 'Digital Research Consent Form';
  $node->language = LANGUAGE_NONE; // Or other language.
  $node->body[$node->language][0]['value'] = file_get_contents(DRUPAL_ROOT . "/profiles/lacunastories_base/basic pages/consent_form.html");;
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
}


/*
  Creating basic pages like FAQ, "Instructor's Guide", etc.
 */
function lacunastories_base_create_basic_pages()
{

  $content[0]["title"] = "FAQ";
  $content[0]["body"] = file_get_contents(DRUPAL_ROOT . "/profiles/lacunastories_base/basic pages/faq.html");;

  $content[1]["title"] = "Instructor's Guide";
  $content[1]["body"] = file_get_contents(DRUPAL_ROOT . "/profiles/lacunastories_base/basic pages/instructors_guide.html");

  $content[2]["title"] = "Student User Guide";
  $content[2]["body"] = file_get_contents(DRUPAL_ROOT . "/profiles/lacunastories_base/basic pages/student_user_guide.html");;

  foreach($content as $page)
  {
    $node = new stdClass(); // We create a new node object
    $node->type = "page"; // Or any other content type you want
    $node->title = $page["title"];
    $node->language = LANGUAGE_NONE; // Or any language code if Locale module is enabled. More on this below *
    $node->body[$node->language][0]['format']  = 'full_html';
    $node->body[$node->language][0]['value'] = $page["body"];
    $node->menu['enabled'] = TRUE;
    $node->menu['link_title'] = $node->title;
    $node->menu['description'] = ''; // Needed even if empty to avoid notices.

    node_object_prepare($node); // Set some default values.
    $node->uid = 1; // Or any id you wish
    $node = node_submit($node); // Prepare node for a submit
    node_save($node); // After this call we'll get a nid
  }
}

/*
  Currently changes permissions for page "Instructor's Guide" only. But the same code can be used to change permissions for other pages too.
 */
function lacunastories_base_set_basic_pages_permissions()
{
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
function lacunastories_base_manage_theme_settings()
{
  $ts = variable_get("theme_settings");
  $ts["toggle_main_menu"] = 0;
  $ts["toggle_secondary_menu"] = 0;
  variable_set("theme_settings", $ts);
}

// set jquery version.
function lacunastories_base_set_jquery_default()
{
  variable_set('jquery_update_jquery_version', '1.7');
}

// set media settings
function lacunastories_base_set_media_settings(){
  variable_set("file_entity_file_upload_wizard_skip_scheme", 1); // this is actually a file entity setting but is available on the media form at admin/config/media/file-settings
}

// set annotator settings
function lacunastories_base_set_annotator_settings() {
  variable_set("annotator_element", 'article.node'); // TODO: check if this is necessary
  // enable some annotator plugins
  variable_set("annotator_plugins", array (
    'Store' => 'Store',
    'Unsupported' => 'Unsupported',
    'Touch' => 'Touch',
    'Categories' => 'Categories',
    'Richtext' => 'Richtext',
    'Filters' => 'Filters',
    'Comment' => 'Comment',
    'Tags' => 'Tags',
    'Privacy' => 'Privacy',
  ));
}

// set default taxonomy terms
function lacunastories_base_default_tax_terms () {
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
    // Add a default term to the vocabulary.
    $vocabulary = taxonomy_vocabulary_machine_name_load($vocabulary_name);
    foreach ($terms as $term) {
      taxonomy_term_save((object) array(
        'name' => $term,
        'vid' => $vocabulary->vid,
      ));
    }
  }
}


// Install task: create workflow states and transitions
function lacunastories_base_create_publication_state_workflow() {

  $system_roles = user_roles();
  $workflow = NULL;

  // Create a workflow.
  $workflow = workflow_create('Materials Publication States');
  $workflow->save();

  // Create States for the workflow.
  $s1 = $workflow->createState('(creation)');
  $s2 = $workflow->createState('Draft');
  $s3 = $workflow->createState('Ready for Annotation');

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
function lacunastories_base_late_feature_and_module_enabling () {
  $enable = array(
    'lacuna_stories_views', // this needs to happen late because it is dependent on lacuna_stories_workflows, which can only be enabled late
    'lacuna_stories_workflows', // this needs to happen after the workflow is created
  );
  module_enable($enable);
}

// ensure features are reverted since things have been done since the initial reversion in hook_install
function lacunastories_base_revert_features_final () {
  // Do it twice with a cache clear inbetween to make sure we get everything
  features_rebuild();
  features_revert();
  drupal_flush_all_caches();
  features_rebuild();
  features_revert();
}