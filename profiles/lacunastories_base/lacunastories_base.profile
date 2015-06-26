<?php

/**
 * Implements hook_install_tasks().
 * Profile install tasks run after the main profile installation in lacunastories_base_install
 */
function lacunastories_base_install_tasks($install_state) {
  $tasks = array (
    'lacunastories_base_create_publication_state_workflow' => array(),
  );
  return $tasks;
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
      'roles' => array(-1, 'Site Administrator', 'Content Manager', 'Instructor', 'Student'),
      'transitions' => array (
        array (
          'sid' => $s2,
          'target_sid' => $s2
        ),
        array (
          'sid' => $s3,
          'target_sid' => $s3
        ),
      ),
    ),
    array (
      'roles' => array(-1, 'Site Administrator', 'Content Manager'),
      'transitions' => array (
        array (
          'sid' => $s3,
          'target_sid' => $s3
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
      $transition_obj->label = '"' . $from->name . '" to "' . $to->name . '"';

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


/**
 * Implements hook_form_FORM_ID_alter().
 *
 * Allows the profile to alter the site configuration form.
 */
if (!function_exists("system_form_install_configure_form_alter")) {
  function system_form_install_configure_form_alter(&$form, $form_state) {
    $form['site_information']['site_name']['#default_value'] = 'Lacunastories Base';
  }
}

/**
 * Implements hook_form_alter().
 *
 * Select the current install profile by default.
 */
if (!function_exists("system_form_install_select_profile_form_alter")) {
  function system_form_install_select_profile_form_alter(&$form, $form_state) {
    foreach ($form['profile'] as $key => $element) {
      $form['profile'][$key]['#value'] = 'lacunastories_base';
    }
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
 * Implementing hook_block_info_alter
 * enabling superfish 1 block for main menu.
 */
function lacunastories_base_block_info_alter(&$blocks, $theme, $code_blocks){
    $regions = system_region_list($theme, REGIONS_VISIBLE);
    if(array_key_exists('header', $regions)){
        $blocks['superfish'][1]['status'] = 1;    
        $blocks['superfish'][1]['region'] = 'header';    
        $blocks['superfish'][1]['title'] = "<none>";
    }
}