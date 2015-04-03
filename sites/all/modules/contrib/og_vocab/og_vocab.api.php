<?php


/**
 * @file
 * Hooks provided by the Organic groups vocabulary module.
 */

/**
 * @addtogroup hooks
 * @{
 */


/**
 * Allow modules to return TRUE if we are insiede an OG vocab admin
 * context.
 *
 * @return
 *   If countext found array keyed by the group-type and the group ID.
 */
function hook_og_vocab_is_admin_context() {
  $item = menu_get_item();
  if (strpos($item['path'], 'foo/admin') === 0){
    return array('group_type' => 'node', 'gid' => 1);
  }
}

/**
 * @} End of "addtogroup hooks".
 */
