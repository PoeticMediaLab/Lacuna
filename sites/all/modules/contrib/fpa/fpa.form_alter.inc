<?php

/**
 * @file
 * Contains form alter hooks to inject FPA functionality.
 */


/**
 * Implements hook_form_FORM_ID_alter().
 */
function fpa_form_node_type_form_alter(&$form, &$form_state) {
  if (!empty($form['type']['#default_value']) && user_access('administer permissions')) {
    fpa_fieldset($form['#node_type']->type . ' content', $form, array('#group' => 'additional_settings'));
  }
}

/**
 * Implements hook_form_FORM_ID_alter().
 */
function fpa_form_user_admin_permissions_alter(&$form, &$form_state) {
  
  // Prevent duplication of memory limit warning.
  if (module_exists('filter_perms') && empty($form_state['input'])) {
    
    $memory_limit = ini_get('memory_limit');
    
    if (!drupal_check_memory_limit(_fpa_memory_required() . 'b', $memory_limit)) {
      drupal_set_message(t('If you attempt to display all roles and permissions on this page at the same time, you will most likely exceed your PHP memory limit of %memory_limit.', array('%memory_limit' => $memory_limit)), 'warning');
    }
  }
    
  $form['#theme'] = array('fpa_user_admin_permissions');
  
  $fpa_module_path = drupal_get_path('module', 'fpa');
  
  $form['#attached']['library'][] = array('system', 'jquery.cookie');

  $form['#attached']['css'][] = $fpa_module_path . '/css/fpa.css';
  $form['#attached']['js'][] = $fpa_module_path . '/js/fpa.min.js';
  $form['#attached']['js'][] = array(
    'type' => 'setting',
    'data' => array(
      'fpa' => array(
        'attr' => array(
          'permission' =>  FPA_ATTR_PERMISSION,
          'module' =>      FPA_ATTR_MODULE,
          'role' =>        FPA_ATTR_ROLE,
          
          'checked' =>     FPA_ATTR_CHECKED,
          'not_checked' => FPA_ATTR_NOT_CHECKED,

          'system_name' => FPA_ATTR_SYSTEM_NAME,
        ),
      ),
    ),
  );
}

/**
 * Implements hook_form_FORM_ID_alter().
 */
function fpa_form_filter_perms_admin_perm_filter_alter(&$form, &$form_state) {
  
  $form['#submit'][] = '_fpa_reset_filter_defaults';
}
