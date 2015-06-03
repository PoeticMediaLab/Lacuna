<?php

/**
 * Annotator ctools plugin
 */
class PrivacyAnnotatorPlugin extends AnnotatorPlugin {

  public function setup() {
    $user_groups = og_get_groups_by_user();
    $user_groups = array_keys($user_groups['node']);
    global $user;
    drupal_add_js(array('annotator_groups' => array ($user->uid => $user_groups)), 'setting');
    drupal_add_js(drupal_get_path('module', 'annotator') . '/js/annotator_privacy.js');
    drupal_add_js(drupal_get_path('module', 'annotator') . '/js/privacy.js');
    drupal_add_css(drupal_get_path('module', 'annotator') . '/css/privacy.css');
  }

}