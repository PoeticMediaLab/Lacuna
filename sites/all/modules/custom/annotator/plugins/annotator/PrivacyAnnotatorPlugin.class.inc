<?php

/**
 * Annotator ctools plugin
 */
class PrivacyAnnotatorPlugin extends AnnotatorPlugin {

  public function setup() {

    $audience = array(
      'private' => 0,
      'instructor' => 0,
      'peer-groups' => 0,
      'everyone' => 1
    );
    $peer_groups = annotation_build_peer_groups();    

    $privacy_options = array(
      'audience' => $audience,
      'groups' => $peer_groups,
    );

    drupal_alter('annotator_privacy_options', $privacy_options);

    drupal_add_js(array('privacy_options' => $privacy_options), 'setting');
    drupal_add_js(drupal_get_path('module', 'annotator') . '/js/annotator_privacy.js');
    drupal_add_js(drupal_get_path('module', 'annotator') . '/js/privacy.js');
  }
}
