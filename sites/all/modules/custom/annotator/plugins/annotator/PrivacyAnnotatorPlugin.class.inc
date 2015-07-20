<?php

/**
 * Annotator ctools plugin
 */
class PrivacyAnnotatorPlugin extends AnnotatorPlugin {

  public function setup() {

    // Build annotator.js privacy options

    // Check that we are on a document
    if (arg(0) == 'node' && is_numeric (arg(1))) {
      $current_node = node_load(arg(1));
      if ($current_node->type == 'document') {


        // Check for default privacy options for this user for this document
        global $user;
        if (isset ($user->data['annotation_privacy_defaults'][$current_node->nid])) {
          $privacy_options = $user->data['annotation_privacy_defaults'][$current_node->nid];
        }

        // No default privacy options default for this user for this document, so use general default
        else {
          // Main audience value
          $audience = array(
            'private' => 0,
            'instructor' => 0,
            'co-learners' => 1,
            'everyone' => 0
          );

          $groups = annotation_get_possible_groups_for_document($current_node);
          $instructor_groups = $groups['course_groups'];

          $privacy_options = array(
            'audience' => $audience,
            'groups' => $groups,
            'instructor_groups' => $instructor_groups
          );
        }

        drupal_add_js(array('privacy_options' => $privacy_options), 'setting');
      }
    }

    drupal_add_js(drupal_get_path('module', 'annotator') . '/js/annotator_privacy.js');
    drupal_add_js(drupal_get_path('module', 'annotator') . '/js/privacy.js');
  }

}
