<?php

/**
 * Annotator ctools plugin
 */
class PrivacyAnnotatorPlugin extends AnnotatorPlugin {

  public function setup() {

    $user_groups = og_get_groups_by_user();
    $user_groups = array_keys($user_groups['node']);

    // If we are on a document node, pass the course(s) that the current document belongs to that also the user is a member of
    $course_groups = array();
    if (arg(0) == 'node' && is_numeric (arg(1))) {
      $current_node = node_load (arg(1));
      if ($current_node->type == 'document') {
        $document = entity_metadata_wrapper('node', $current_node);
        $doc_groups = $document->og_group_ref->value();
        if (count ($doc_groups)) {
          foreach ($doc_groups as $doc_group) { // Documents can belong to multiple courses
            if (in_array($doc_group->nid, $user_groups)) { // User must be in course
              $course_groups [$doc_group->nid] = $doc_group->title;
            }
          }
        }
      }
    }

    // Pass the user's peer groups
    $peer_groups = array();
    foreach($user_groups as $user_group) {
      $node = node_load($user_group);
      if ($node->type == 'peer_group') {
        $peer_groups[$user_group] = $node->title;
      }
    }

    $groups_total = array (
      'course_groups' => $course_groups,
      'peer_groups' => $peer_groups
    );
    #dpm ($groups_total, 'groups total');

    global $user;
    drupal_add_js(array('annotator_groups' => array ($user->uid => $groups_total)), 'setting');

    drupal_add_js(drupal_get_path('module', 'annotator') . '/js/annotator_privacy.js');
    drupal_add_js(drupal_get_path('module', 'annotator') . '/js/privacy.js');
    drupal_add_css(drupal_get_path('module', 'annotator') . '/css/privacy.css');
  }

}