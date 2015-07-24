<?php

/**
 * Annotator ctools plugin
 */
class PrivacyAnnotatorPlugin extends AnnotatorPlugin {

  public function setup() {

    // Build annotator.js privacy options

    $annotatable_node =  annotator_check_annotatable_node();

    // Check for default privacy options for this user for this node
    global $user;
    if (isset ($user->data['annotation_privacy_defaults'][$annotatable_node->nid])) {
      $privacy_options = $user->data['annotation_privacy_defaults'][$annotatable_node->nid];
      $audience = $privacy_options['audience'];
      $default_groups = $privacy_options['groups'];
      $possible_groups = annotation_build_peer_groups();
      $peer_groups = array_merge ($default_groups, $possible_groups);
    }

    // No default privacy options default for this user for this node, so use general default
    else {
      // Main audience value
      $audience = array(
        'private' => 0,
        'instructor' => 0,
        'peer-groups' => 0,
        'everyone' => 1
      );
      $peer_groups = annotation_build_peer_groups();

    }
    $privacy_options = array(
      'audience' => $audience,
      'groups' => $peer_groups,
    );

    drupal_add_js(array('privacy_options' => $privacy_options), 'setting');
    drupal_add_js(drupal_get_path('module', 'annotator') . '/js/annotator_privacy.js');
    drupal_add_js(drupal_get_path('module', 'annotator') . '/js/privacy.js');
  }
}
