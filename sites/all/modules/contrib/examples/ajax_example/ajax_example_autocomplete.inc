<?php
/**
 * @file
 * ajax_example_autocomplete.inc
 *
 * Demonstrates usage of the Form API's autocomplete features.
 *
 * This file provides three examples in increasing complexity:
 * - A simple username autocomplete (usernames are unique, so little effort is
 *   required)
 * - A node title autocomplete (titles are not unique, so we have to find the
 *   nid and stash it in the field)
 * - A username autocomplete that updates a node title autocomplete with a
 *   changed #autocomplete_path so that the #autocomplete_path can have
 *   context (the username to use in the search).
 */

/**
 * A simple autocomplete form which just looks up usernames in the user table.
 *
 * @param array $form
 *   Form API form.
 * @param array $form_state
 *   Form API form.
 *
 * @return array
 *   Form array.
 */
function ajax_example_simple_autocomplete($form, &$form_state) {

  $form['info'] = array(
    '#markup' => '<div>' . t("This example does a simplest possible autocomplete by username. You'll need a few users on your system for it to make sense.") . '</div>',
  );

  $form['user'] = array(
    '#type' => 'textfield',
    '#title' => t('Choose a user (or a people, depending on your usage preference)'),
    // The autocomplete path is provided in hook_menu in ajax_example.module.
    '#autocomplete_path' => 'examples/ajax_example/simple_user_autocomplete_callback',
  );

  return $form;
}

/**
 * This is just a copy of user_autocomplete().
 *
 * It works simply by searching usernames (and of course in Drupal usernames
 * are unique, so can be used for identifying a record.)
 *
 * The returned $matches array has
 * * key: string which will be displayed once the autocomplete is selected
 * * value: the value which will is displayed in the autocomplete pulldown.
 *
 * In the simplest cases (see user_autocomplete()) these are the same, and
 * nothing needs to be done. However, more more complicated autocompletes
 * require more work. Here we demonstrate the difference by displaying the UID
 * along with the username in the dropdown.
 *
 * In the end, though, we'll be doing something with the value that ends up in
 * the textfield, so it needs to uniquely identify the record we want to access.
 * This is demonstrated in ajax_example_unique_autocomplete().
 *
 * @param string $string
 *   The string that will be searched.
 */
function ajax_example_simple_user_autocomplete_callback($string = "") {
  $matches = array();
  if ($string) {
    $result = db_select('users')
      ->fields('users', array('name', 'uid'))
      ->condition('name', db_like($string) . '%', 'LIKE')
      ->range(0, 10)
      ->execute();
    foreach ($result as $user) {
      // In the simplest case (see user_autocomplete), the key and the value are
      // the same. Here we'll display the uid along with the username in the
      // dropdown.
      $matches[$user->name] = check_plain($user->name) . " (uid=$user->uid)";
    }
  }

  drupal_json_output($matches);
}

/**
 * An autocomplete form to look up nodes by title.
 *
 * An autocomplete form which looks up nodes by title in the node table,
 * but must keep track of the nid, because titles are certainly not guaranteed
 * to be unique.
 *
 * @param array $form
 *   Form API form.
 * @param array $form_state
 *   Form API form state.
 *
 *  * @return array
 *   Form array.
 */
function ajax_example_unique_autocomplete($form, &$form_state) {

  $form['info'] = array(
    '#markup' => '<div>' . t("This example does a node autocomplete by title. The difference between this and a username autocomplete is that the node title may not be unique, so we have to use the nid for uniqueness, placing it in a parseable location in the textfield.") . '</div>',
  );

  $form['node'] = array(
    '#type' => 'textfield',
    '#title' => t('Choose a node by title'),
    // The autocomplete path is provided in hook_menu in ajax_example.module.
    '#autocomplete_path' => 'examples/ajax_example/unique_node_autocomplete_callback',
  );

  $form['actions'] = array(
    '#type' => 'actions',
  );

  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
  );

  return $form;
}

/**
 * Node title validation handler.
 *
 * Validate handler to convert our string like "Some node title [3325]" into a
 * nid.
 *
 * In case the user did not actually use the autocomplete or have a valid string
 * there, we'll try to look up a result anyway giving it our best guess.
 *
 * Since the user chose a unique node, we must now use the same one in our
 * submit handler, which means we need to look in the string for the nid.
 *
 * @param array $form
 *   Form API form.
 * @param array $form_state
 *   Form API form state.
 */
function ajax_example_unique_autocomplete_validate($form, &$form_state) {
  $title = $form_state['values']['node'];
  $matches = array();
  $nid = 0;

  // This preg_match() looks for the last pattern like [33334] and if found
  // extracts the numeric portion.
  $result = preg_match('/\[([0-9]+)\]$/', $title, $matches);
  if ($result > 0) {
    // If $result is nonzero, we found a match and can use it as the index into
    // $matches.
    $nid = $matches[$result];
    // Verify that it's a valid nid.
    $node = node_load($nid);
    if (empty($node)) {
      form_error($form['node'], t('Sorry, no node with nid %nid can be found', array('%nid' => $nid)));
      return;
    }
  }
  // BUT: Not everybody will have javascript turned on, or they might hit ESC
  // and not use the autocomplete values offered. In that case, we can attempt
  // to come up with a useful value. This is not absolutely necessary, and we
  // *could* just emit a form_error() as below.
  else {
    $nid = db_select('node')
      ->fields('node', array('nid'))
      ->condition('title', db_like($title) . '%', 'LIKE')
      ->range(0, 1)
      ->execute()
      ->fetchField();
  }

  // Now, if we somehow found a nid, assign it to the node. If we failed, emit
  // an error.
  if (!empty($nid)) {
    $form_state['values']['node'] = $nid;
  }
  else {
    form_error($form['node'], t('Sorry, no node starting with %title can be found', array('%title' => $title)));
  }
}

/**
 * Submit handler for node lookup unique autocomplete example.
 *
 * Here the nid has already been placed in $form_state['values']['node'] by the
 * validation handler.
 *
 * @param array $form
 *   Form API form.
 * @param array $form_state
 *   Form API form state.
 */
function ajax_example_unique_autocomplete_submit($form, &$form_state) {
  $node = node_load($form_state['values']['node']);
  drupal_set_message(t('You found node %nid with title %title', array('%nid' => $node->nid, '%title' => $node->title)));
}

/**
 * Autocomplete callback for nodes by title.
 *
 * Searches for a node by title, but then identifies it by nid, so the actual
 * returned value can be used later by the form.
 *
 * The returned $matches array has
 * - key: The title, with the identifying nid in brackets, like "Some node
 *   title [3325]"
 * - value: the title which will is displayed in the autocomplete pulldown.
 *
 * Note that we must use a key style that can be parsed successfully and
 * unambiguously. For example, if we might have node titles that could have
 * [3325] in them, then we'd have to use a more restrictive token.
 *
 * @param string $string
 *   The string that will be searched.
 */
function ajax_example_unique_node_autocomplete_callback($string = "") {
  $matches = array();
  if ($string) {
    $result = db_select('node')
      ->fields('node', array('nid', 'title'))
      ->condition('title', db_like($string) . '%', 'LIKE')
      ->range(0, 10)
      ->execute();
    foreach ($result as $node) {
      $matches[$node->title . " [$node->nid]"] = check_plain($node->title);
    }
  }

  drupal_json_output($matches);
}

/**
 * Search by title and author.
 *
 * In this example, we'll look up nodes by title, but we want only nodes that
 * have been authored by a particular user. That means that we'll have to make
 * an autocomplete function which takes a username as an argument, and use
 * #ajax to change the #autocomplete_path based on the selected user.
 *
 * Although the implementation of the validate handler may look complex, it's
 * just ambitious. The idea here is:
 * 1. Autcomplete to get a valid username.
 * 2. Use #ajax to update the node element with a #autocomplete_callback that
 *    gives the context for the username.
 * 3. Do an autcomplete on the node field that is limited by the username.
 *
 * @param array $form
 *   Form API form.
 * @param array $form_state
 *   Form API form state.
 *
 * @return array
 *   Form API array.
 */
function ajax_example_node_by_author_autocomplete($form, &$form_state) {

  $form['intro'] = array(
    '#markup' => '<div>' . t("This example uses a user autocomplete to dynamically change a node title autocomplete using #ajax.
      This is a way to get past the fact that we have no other way to provide context to the autocomplete function.
      It won't work very well unless you have a few users who have created some content that you can search for.") . '</div>',
  );

  $form['author'] = array(
    '#type' => 'textfield',
    '#title' => t('Choose the username that authored nodes you are interested in'),
    // Since we just need simple user lookup, we can use the simplest function
    // of them all, user_autocomplete().
    '#autocomplete_path' => 'user/autocomplete',
    '#ajax' => array(
      'callback' => 'ajax_example_node_by_author_ajax_callback',
      'wrapper' => 'autocomplete-by-node-ajax-replace',
    ),
  );

  // This form element with autocomplete will be replaced by #ajax whenever the
  // author changes, allowing the search to be limited by user.
  $form['node'] = array(
    '#type' => 'textfield',
    '#title' => t('Choose a node by title'),
    '#prefix' => '<div id="autocomplete-by-node-ajax-replace">',
    '#suffix' => '</div>',
    '#disabled' => TRUE,
  );

  // When the author changes in the author field, we'll change the
  // autocomplete_path to match.
  if (!empty($form_state['values']['author'])) {
    $author = user_load_by_name($form_state['values']['author']);
    if (!empty($author)) {
      $autocomplete_path = 'examples/ajax_example/node_by_author_autocomplete/' . $author->uid;
      $form['node']['#autocomplete_path'] = $autocomplete_path;
      $form['node']['#title'] = t('Choose a node title authored by %author', array('%author' => $author->name));
      $form['node']['#disabled'] = FALSE;
    }
  }

  $form['actions'] = array(
    '#type' => 'actions',
  );

  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
  );

  return $form;
}

/**
 * AJAX callback for author form element.
 *
 * @param array $form
 *   Form API form.
 * @param array $form_state
 *   Form API form state.
 *
 * @return array
 *   Form API array.
 */
function ajax_example_node_by_author_ajax_callback($form, $form_state) {
  return $form['node'];
}

/**
 * Validate handler to convert our title string into a nid.
 *
 * In case the user did not actually use the autocomplete or have a valid string
 * there, we'll try to look up a result anyway giving it our best guess.
 *
 * Since the user chose a unique node, we must now use the same one in our
 * submit handler, which means we need to look in the string for the nid.
 *
 * This handler looks complex because it's ambitious (and tries to punt and
 * find a node if they've entered a valid username and part of a title), but
 * you *could* just do a form_error() if nothing were found, forcing people to
 * use the autocomplete to look up the relevant items.
 *
 * @param array $form
 *   Form API form.
 * @param array $form_state
 *   Form API form state.
 *
 * @return array
 *   Form API array.
 */
function ajax_example_node_by_author_autocomplete_validate($form, &$form_state) {
  $title = $form_state['values']['node'];
  $author = $form_state['values']['author'];
  $matches = array();
  $nid = 0;

  // We must have a valid user.
  $account = user_load_by_name($author);
  if (empty($account)) {
    form_error($form['author'], t('You must choose a valid author username'));
    return;
  }
  // This preg_match() looks for the last pattern like [33334] and if found
  // extracts the numeric portion.
  $result = preg_match('/\[([0-9]+)\]$/', $title, $matches);
  if ($result > 0) {
    // If $result is nonzero, we found a match and can use it as the index into
    // $matches.
    $nid = $matches[$result];
    // Verify that it's a valid nid.
    $node = node_load($nid);
    if (empty($node)) {
      form_error($form['node'], t('Sorry, no node with nid %nid can be found', array('%nid' => $nid)));
      return;
    }
  }
  // BUT: Not everybody will have javascript turned on, or they might hit ESC
  // and not use the autocomplete values offered. In that case, we can attempt
  // to come up with a useful value. This is not absolutely necessary, and we
  // *could* just emit a form_error() as below. Here we'll find the *first*
  // matching title and assume that is adequate.
  else {
    $nid = db_select('node')
      ->fields('node', array('nid'))
      ->condition('uid', $account->uid)
      ->condition('title', db_like($title) . '%', 'LIKE')
      ->range(0, 1)
      ->execute()
      ->fetchField();
  }

  // Now, if we somehow found a nid, assign it to the node. If we failed, emit
  // an error.
  if (!empty($nid)) {
    $form_state['values']['node'] = $nid;
  }
  else {
    form_error($form['node'], t('Sorry, no node starting with %title can be found', array('%title' => $title)));
  }
}

/**
 * Submit handler for node lookup unique autocomplete example.
 *
 * Here the nid has already been placed in $form_state['values']['node'] by the
 * validation handler.
 *
 * @param array $form
 *   Form API form.
 * @param array $form_state
 *   Form API form state.
 *
 * @return array
 *   Form API array.
 */
function ajax_example_node_by_author_autocomplete_submit($form, &$form_state) {
  $node = node_load($form_state['values']['node']);
  $account = user_load($node->uid);
  drupal_set_message(t('You found node %nid with title !title_link, authored by !user_link',
    array(
      '%nid' => $node->nid,
      '!title_link' => l($node->title, 'node/' . $node->nid),
      '!user_link' => theme('username', array('account' => $account)),
    )
  ));
}

/**
 * Autocomplete callback for nodes by title but limited by author.
 *
 * Searches for a node by title given the passed-in author username.
 *
 * The returned $matches array has
 * - key: The title, with the identifying nid in brackets, like "Some node
 *   title [3325]"
 * - value: the title which will is displayed in the autocomplete pulldown.
 *
 * Note that we must use a key style that can be parsed successfully and
 * unambiguously. For example, if we might have node titles that could have
 * [3325] in them, then we'd have to use a more restrictive token.
 *
 * @param int $author_uid
 *   The author username to limit the search.
 * @param string $string
 *   The string that will be searched.
 */
function ajax_example_node_by_author_node_autocomplete_callback($author_uid, $string = "") {
  $matches = array();
  if ($author_uid > 0 && trim($string)) {
    $result = db_select('node')
      ->fields('node', array('nid', 'title'))
      ->condition('uid', $author_uid)
      ->condition('title', db_like($string) . '%', 'LIKE')
      ->range(0, 10)
      ->execute();
    foreach ($result as $node) {
      $matches[$node->title . " [$node->nid]"] = check_plain($node->title);
    }
  }

  drupal_json_output($matches);
}
