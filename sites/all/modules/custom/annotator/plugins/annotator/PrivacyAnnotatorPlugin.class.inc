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
        $document = entity_metadata_wrapper('node', $current_node);

        // Main audience value
        $audience = array(
          'private' => 0,
          'instructor' => 0,
          'co-learners' => 1,
          'everyone' => 0
        );

        // Groups

        $user_groups = og_get_groups_by_user();
        $user_groups = array_keys($user_groups['node']);

        // Course groups - for the current document that user is a member of
        $course_groups = array();
        $doc_groups = $document->og_group_ref->value();
        if (count($doc_groups)) {
          foreach ($doc_groups as $doc_group) { // Documents can belong to multiple courses
            if (in_array($doc_group->nid, $user_groups)) { // User must be in course
              $course_groups [$doc_group->nid] = array(
                $doc_group->title,
                'selected' => 1
              );
            }
          }
        }
      }

      // Peer groups -- all user's peer groups
      $peer_groups = array();
      foreach ($user_groups as $user_group) {
        $node = node_load($user_group);
        if ($node->type == 'peer_group') {
          $peer_groups[$user_group] = array(
            $node->title,
            'selected' => 1
          );
        }
      }

      $groups_total = array(
        'course_groups' => $course_groups,
        'peer_groups' => $peer_groups
      );

      $privacy_options = array(
        'audience' => $audience,
        'groups' => $groups_total
      );

      drupal_add_js(array('privacy_options' => $privacy_options), 'setting');
    }

    drupal_add_js(drupal_get_path('module', 'annotator') . '/js/annotator_privacy.js');
    drupal_add_js(drupal_get_path('module', 'annotator') . '/js/privacy.js');
    drupal_add_css(drupal_get_path('module', 'annotator') . '/css/privacy.css');
  }

}
