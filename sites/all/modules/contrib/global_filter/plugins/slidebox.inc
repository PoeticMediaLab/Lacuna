<?php
/**
 * @file
 * slidebox.inc, plugin for slidebox module
 */

/**
 * Implements hook_slidebox_data_alter().
 *
 * Relies on an auto-cycle view to return a list of node ids that will have
 * the slidebox feature enabled. The view may be filtered by vocabulary,
 * content type, modification date (e.g., only recently commented content) etc.
 * For each node the "next post" mentioned in the slidebox is the next node in
 * the view, so make sure your view results are in the order you want them.
 *
 * @see slidebox.module
 */
function global_filter_slidebox_data_alter(&$node_details, $view_mode) {
  if ($view_mode == 'full' && is_numeric(arg(1))) {
    // If there's no auto-cycle view, follow normal Slidebox behaviour.
    $view_id = drupal_substr(global_filter_get_module_parameter('view_autocycle'), 5);
    if (!views_get_view($view_id)) {
      return FALSE;
    }
    $nid = arg(1);
    $next_nid = global_filter_get_view_next_value($nid, $view_id);
    if ($next_nid && ($next_node = node_load($next_nid))) {
      $node_details['nid'] = $next_node->nid;
      $node_details['title'] = $next_node->title;
    }
    else {
      // Don't show slidebox.
      $node_details = FALSE;
    }
  }
}
