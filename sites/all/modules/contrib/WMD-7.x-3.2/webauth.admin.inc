<?php
/**
 * @file
 * Admin menus for webauth module
 *
 */

/**
 * Base webauth settings form
 */
function webauth_admin_settings($form, &$form_state) {

  $result = db_query('SELECT rid, name FROM {role} WHERE rid > :rid', array(':rid' => 2));
  $roles = array();
  while ($role = $result->fetchObject()) {
    $roles[$role->rid] = $role->name;
  }

  $form['webauth_allow_local'] = array(
    '#type' => 'radios',
    '#title' => t('Stanford WebAuth options'),
    '#default_value' => variable_get('webauth_allow_local', 1),
    '#options' => array(
      0 => t('Hide Local Drupal Login Block'),
      1 => t('Show Local Drupal Login Block'),
    ),
    '#description' => t('Hide the Local Drupal Login Block if it&rsquo;s not needed by local accounts to prevent users from entering their SUNet ID and password there by mistake. This does not affect the <em>user/login</em> form which can still be used to log in as <em>user 1</em> when needed.'),
  );
  $form['webauth_link_text'] = array(
    '#type' => 'textfield',
    '#title' => t('WebAuth Link Text'),
    '#size' => 80,
    '#maxlength' => 255,
    '#default_value' => variable_get('webauth_link_text', 'Log in with WebAuth'),
    '#description' => t('The text for the WebAuth link. It&rsquo;s what users will click on to log in using WebAuth. (E.g.: "Log in with WebAuth")'),
  );
  $form['webauth_destination'] = array(
    '#type' => 'textfield',
    '#title' => t('Post-Login Destination'),
    '#size' => 80,
    '#maxlength' => 255,
    '#default_value' => variable_get('webauth_destination', ''),
    '#description' => t('Drupal node to which the browser redirects after successful weblogin. (E.g.: \'node/add/page\' will automatically redirect user to a new content page.) If unsure, just leave blank to keep Drupal\'s default behavior.'),
  );

  $form['webauth_restrict_message'] = array(
    '#type' => 'textarea',
    '#title' => t('Restricted Access Message'),
    '#cols' => 80,
    '#rows' => 5,
    '#default_value' => variable_get('webauth_restrict_message', 'This content has been restricted by the author or by the site administrator.'),
    '#description' => t('Message to be displayed to user when access to content is restricted.'),
  );

  return system_settings_form($form);
}

/**
 * The webauth groups/mapping form
 */
function webauth_admin_groups($form, &$form_state) {
  $table = array();
  $submitted = !empty($form_state['post']);

  $result = db_query('SELECT rid, name FROM {role} WHERE rid > 2');
  while ($role = $result->fetchObject()) {
    $roles[$role->rid] = $role->name;
  }

  $form['new_rid'] = array(
    '#name' => 'new_rid',
    '#type' => 'select',
    '#options' => $roles,
  );

  $form['new_group'] = array(
    '#name' => 'new_group',
    '#type' => 'textfield',
    '#default_value' => '',
  );

  $form['new_submit'] = array(
    '#name' => 'new_submit',
    '#type' => 'submit',
    '#value' => t('Add Mapping'),
  );

  if (!$submitted) {
    $table[] = array(drupal_render($form['new_rid']), drupal_render($form['new_group']), drupal_render($form['new_submit']));
  }
  else {
    // Keep the UI consistent.
    $form['new_rid']['#prefix'] = '<table><tr class="odd"><td>';
    $form['new_rid']['#suffix'] = '</td><td>';
    $form['new_group']['#suffix'] = '</td><td>';
    $form['new_submit']['#suffix'] = '</td><td>';
    $form['cancel'] = array(
      '#type' => 'markup',
      '#value' => l(t('Cancel'), 'admin/config/webauth/mappings'),
      '#suffix' => '</td></tr></table>',
    );
  }

  $result = db_query("SELECT wr.warid, r.name, wr.wa_group as `group` FROM {webauth_roles} wr INNER JOIN {role} r ON wr.rid = r.rid WHERE r.rid > 2");
  while ($group = $result->fetchObject()) {
    $button_id = 'remove_warid_' . $group->warid;
    $form[$button_id] = array(
      '#name' => $button_id,
      '#type' => 'submit',
      '#value' => t('Remove Mapping'),
    );
    $row = array($group->name, $group->group, drupal_render($form[$button_id]));
    $table[] = $row;
  }
  $header = array(
    t('Drupal Role'),
    t('Workgroup (e.g. stanford:staff)'),
    t('Action')
  );
  $form['output'] = array(
    '#markup' => theme('table', array(
      'header' => $header,
      'rows' => $table,
    )),
  );

  return $form;
}

/**
 * Validates the webauth_admin_groups form
 */
function webauth_admin_groups_validate($form, &$form_state) {
  if ($form_state['clicked_button']['#value'] == t('Add Mapping')) {
    if (preg_match("/^[-_\w\d\~]+:[\w\d-_]+$/", $form_state['values']['new_group']) == 0) {
      form_set_error('new_group', t('There was an error in your workgroup name.  Please make sure you entered it correctly.'));
    }
    $query = db_query("SELECT * FROM {webauth_roles} WHERE rid = :rid AND wa_group = :wa_group",
      array(':rid' => $form_state['values']['new_rid'], ':wa_group' => $form_state['values']['new_group']));
    if ($query->fetchField()) {
      form_set_error('new_group', t('This workgroup is already mapped to this Drupal role!'));
    }
  }
}

/**
 * The submit function for the webauth_admin_groups form
 */
function webauth_admin_groups_submit($form, &$form_state) {
  if ($form_state['clicked_button']['#value'] == t('Add Mapping')) {
    // Add mapping
    $id = db_insert('webauth_roles')
      ->fields(array(
        'rid' => $form_state['values']['new_rid'],
        'wa_group' => $form_state['values']['new_group'],
      ))
      ->execute();
    $role_name = db_query("SELECT name FROM {role} WHERE rid = :rid", array(':rid' => $form_state['values']['new_rid']))->fetchField();
    drupal_set_message(t('Added new WebAuth mapping: @role_name => @new_group', array('@role_name' => $role_name, '@new_group' => $form_state['values']['new_group'])));
  }
  elseif ($form_state['clicked_button']['#value'] == t('Remove Mapping')) {
    // Remove mapping
    $warid = drupal_substr($form_state['clicked_button']['#name'], 13);
    db_delete('webauth_roles')
      ->condition('warid', $warid)
      ->execute();
    drupal_set_message(t('Removed WebAuth mapping from table. [ID: @warid]', array('@warid' => $warid)));
    // Clear out any roles that were granted as a result.
    $result = db_query("SELECT * FROM {webauth_roles_history} WHERE warid = :warid", array(':warid' => $warid));
    while ($history = $result->fetchObject()) {
      // See if there's another mapping for this role.
      if (!db_query("SELECT * FROM {webauth_roles_history} WHERE uid = :uid AND rid = :rid AND warid <> :warid", array(':uid' => $history->uid, ':rid' => $history->rid, ':warid' => $warid))->fetchField()) {
        // If not, nix the users_roles value so they lose privileges immediately.
        db_delete('users_roles')
          ->condition('uid', $history->uid)
          ->condition('rid', $history->rid)
          ->execute();
      }
    }
    db_delete('webauth_roles_history')
      ->condition('warid', $warid)
      ->execute();
  }

  // Need to update the .htaccess file.
  webauth_write_htaccess();
}

/**
 * WebAuth user specific functionality form.
 */
function webauth_admin_users($form, &$form_state) {

  $form['webauth_require_valid_user'] = array(
    '#type' => 'checkbox',
    '#title' => t('Require ANY valid user'),
    '#description' => t('If checked, anyone with a valid SUNet ID will be allowed to log in. This overrides whatever users or groups are entered below. Default is on.'),
    '#default_value' => variable_get('webauth_require_valid_user', 1),
  );

  $form['webauth_require_users'] = array(
    '#type' => 'textarea',
    '#title' => t('SUNet IDs of users permitted access'),
    '#description' => t('Enter one SUNet ID per line.'),
    '#default_value' => variable_get('webauth_require_users', ''),
  );

  $form['webauth_require_privgroups'] = array(
    '#type' => 'textarea',
    '#title' => t('Workgroups permitted access'),
    '#description' => t('Enter one workgroup (e.g."stanford:staff") per line. You can create and maintain workgroups using <a href="https://workgroup.stanford.edu">workgroup manager</a>.'),
    '#default_value' => variable_get('webauth_require_privgroups', ''),
  );

  $form = system_settings_form($form);

  $form['#validata'][] = 'webauth_admin_users_validate';
  $form['#submit'][] = 'webauth_admin_users_submit';

  return $form;
}

/**
 * Validate that we're getting valid input in our .htaccess file.
 */
function webauth_admin_users_validate($form, &$form_state) {
  $userlines = explode("\n", chop($form_state['values']['webauth_require_users']));
  $grouplines = explode("\n", chop($form_state['values']['webauth_require_privgroups']));

  foreach ($userlines as $line) {
    $line = chop($line);
    if ($line != '' && preg_match("/^[\w\d-_]+$/", $line) != 1) {
      form_set_error('webauth_require_users', t('@line is not a valid user format. Please enter one username per line.', array('@line' => $line)));
    }
  }
  foreach ($grouplines as $line) {
    $line = chop($line);
    if ($line != '' && preg_match("/^[-_\w\d\~]+:[\w\d-_]+$/", $line) != 1) {
      form_set_error('webauth_require_privgroups', t('@line is not a valid user format. Please enter one username per line.', array('@line' => $line)));
    }
  }

  if (trim($form_state['values']['webauth_require_users']) == '' && trim($form_state['values']['webauth_require_privgroups']) == '' && $form_state['values']['webauth_require_valid_user'] == FALSE) {
    form_set_error('webauth_require_valid_user', t('You must specify some valid means for accessing the site.'));
  }

}

/**
 * Submit function for webauth_admin_users form
 */
function webauth_admin_users_submit($form, &$form_state) {
  // Need to update the .htaccess file.
  webauth_write_htaccess();
}

/**
 * Migrate old-style {webauth} and {webauth_force} data to {node_access}.
 *
 * This is here so it can be called from the install file or at a later date.
 */
function webauth_migrate_to_content_access() {
  // make sure content_access is loaded in case this is during an update hook
  require_once DRUPAL_ROOT . '/' . drupal_get_path('module', 'content_access') . "/content_access.module";
  require_once DRUPAL_ROOT . '/' . drupal_get_path('module', 'content_access') . "/content_access.admin.inc";

  $types = array(); // we will need to track node types touched so they're enabled.
  $default_role = variable_get('webauth_default_role', 0);
  // The webauth table contains specific mappings, which we should respect.
  $result = db_query("SELECT * FROM {webauth}");
  while ($webauth_access = $result->fetchObject()) {
    $node = node_load($webauth_access->nid);
    $webauth_roles = unserialize($webauth_access->roles);

    if (trim($webauth_access->sugroups) != '') {
      $sugroups = explode(',', $webauth_access->sugroups);
      foreach ($sugroups as $sugroup) {
        $sugroup = trim($sugroup);
        $wa_mapped_role = db_query("SELECT * FROM {webauth_roles} WHERE wa_group = :wa_group", array(':wa_group' => $sugroup))->fetchObject();
        if ($wa_mapped_role->rid) {
          $webauth_roles[$wa_mapped_role->rid] = $wa_mapped_role->rid;
        }
        else {
          $role_exists = (bool) db_query("SELECT COUNT(*) FROM {role} WHERE name = :name", array(':name' => $sugroup))->fetchField();
          if (!$role_exists) {
            $id = db_insert('role')
              ->fields(array(
                'name' => $sugroup,
              ))
              ->execute();
            drupal_set_message(t('Added Role: @sugroup', array('@sugroup' => $sugroup)));
          }
          $rid = db_query("SELECT rid FROM {role} WHERE name = :name", array(':name' => $sugroup))->fetchField();
          if ($rid) {
            $id = db_insert('webauth_roles')
              ->fields(array(
                'rid' => $rid,
                'wa_group' => $sugroup,
              ))
              ->execute();
            drupal_set_message(t('Added group mapping for @sugroup => @sugroup2', array('@sugroup' => $sugroup, '@sugroup' => $sugroup)));
            $webauth_roles[$rid] = $rid;
          }
        }
      }
    }

    $settings = array(
      'view' => array_keys($webauth_roles),
      'view_own' => array(),
      'update' => array(),
      'update_own' => array(),
      'delete' => array(),
      'delete_own' => array(),
    );
    content_access_save_per_node_settings($node, $settings);
    $types[$node->type] = 1;
  }

  // Force maps to the default role, so only proceed if we have one set.
  if ($default_role > 0) {
    $result = db_query("SELECT * FROM {webauth_force}");
    $settings = array(
      'view' => array($default_role),
      'view_own' => array(),
      'update' => array(),
      'update_own' => array(),
      'delete' => array(),
      'delete_own' => array(),
    );
    while ($webauth_force = $result->fetchObject()) {
      $node = node_load($webauth_force->nid);
      content_access_save_per_node_settings($node, $settings);
      $types[$node->type] = 1;
    }
  }

  // Ensure that all types are set to per-node control.
  $content_access_settings = array('per_node' => $types);
  content_access_set_settings($content_access_settings);
  // Rebuild content_access settings.
  content_access_mass_update($types);
  $link = l(t('here'), 'admin/content/node-settings');
  drupal_set_message(t("You need to rebuild the node access settings now. You can do that !link.", array('!link' => $link)), 'error');
  node_access_needs_rebuild(TRUE);
}
