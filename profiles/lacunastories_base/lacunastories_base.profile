<?php
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