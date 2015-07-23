<?php

/**
 * Annotator ctools plugin
 */
class PrivacyAnnotatorPlugin extends AnnotatorPlugin {

  public function setup() {

    // Build annotator.js privacy options

    $annotatable_node = annotator_check_annotatable_node();

    // Check for default privacy options for this user for this node
    global $user;
    if (isset ($user->data['annotation_privacy_defaults'][$annotatable_node->nid])) {
      $privacy_options = $user->data['annotation_privacy_defaults'][$annotatable_node->nid];
    }

    // No default privacy options default for this user for this node, so use general default
    else {
      // Main audience value
      $audience = array(
        'private' => 0,
        'instructor' => 0,
        'co-learners' => 1,
        'everyone' => 0
      );

      $groups = annotation_get_possible_groups_for_node($annotatable_node);
      $instructor_groups = $groups['course_groups'];

      $privacy_options = array(
        'audience' => $audience,
        'groups' => $groups,
        'instructor_groups' => $instructor_groups
      );
    }

    drupal_add_js(array('privacy_options' => $privacy_options), 'setting');
    drupal_add_js(drupal_get_path('module', 'annotator') . '/js/annotator_privacy.js');
    drupal_add_js(drupal_get_path('module', 'annotator') . '/js/privacy.js');
    drupal_add_css(drupal_get_path('module', 'annotator') . '/css/privacy.css');
  }
}
