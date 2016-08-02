<?php
/**
 * Custom filter handler so that we can have author as an exposed filter select list (which then gets 'chosen-ed')
 * taken from: http://stackoverflow.com/questions/3881718/drupal-views-exposed-filter-of-author-name-as-a-drop-down
 */
class views_lacuna_stories_views_handler_filter_author_select extends views_handler_filter_in_operator {

	/**
	 * Override parent get_value_options() function.
	 *
	 * @return
	 *   Return the stored values in $this->value_options if someone expects it.
	 */
	function get_value_options() {
    $cid = 'views_lacuna_stories_users_list';
    $users = array();
    if ($cached = cache_get($cid)) {
      $users = $cached->data;
    }

    if (empty($users)) {
      $users_list = entity_load('user');

      foreach ($users_list as $user) {
        $users[$user->uid] = $user->name;
      }

      // We don't need Guest user here, so remove it.
      unset($users[0]);
      // Also remove super user
      unset($users[1]);

      // Sort by username.
      natsort($users);

      cache_set($cid, $users, 'cache', time() + 24 * 60 * 60);
    }
    $this->value_options = $users;
    return $users;
	}
}