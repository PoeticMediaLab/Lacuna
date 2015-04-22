<?php

/**
 * @file
 * Administrative pages callbacks for the Notify module.
 */

/**
 * Menu callback, show admin notification settings form.
 */
function notify_admin_settings($form, &$form_state) {
  $period = array(
    0 => t('Cron'),
    3600 => format_interval(3600),
    10800 => format_interval(10800),
    21600 => format_interval(21600),
    32400 => format_interval(32400),
    43200 => format_interval(43200),
    86400 => format_interval(86400),
    172800 => format_interval(172800),
    259200 => format_interval(259200),
    604800 => format_interval(604800),
    1209600 => format_interval(1209600),
    2419200 => format_interval(2419200),
    -1 => t('Never'),
  );

  $attempts = array(
    0 => t('Disabled'),
    1 => 1,
    2 => 2,
    3 => 3,
    4 => 4,
    5 => 5,
    6 => 6,
    7 => 7,
    8 => 8,
    9 => 9,
    10 => 10,
    15 => 15,
    20 => 20,
  );

  $batch = array(
    2 => 2,
    3 => 3,
    10 => 10,
    20 => 20,
    50 => 50,
    100 => 100,
    200 => 200,
    400 => 400,
  );

  $form = array();

  $form['notify_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('E-mail notification settings'),
    '#collapsible' => TRUE,
  );

  $form['notify_settings']['notify_period'] = array(
    '#type' => 'select',
    '#title' => t('Send notifications every'),
    '#default_value' => variable_get('notify_period', array(86400)),
    '#options' => $period,
    '#description' => t('How often should new content notifications be sent? Requires cron to be running at least this often.'),
  );

  $form['notify_settings']['notify_send_hour'] = array(
    '#type' => 'select',
    '#title' => t('Hour to send notifications'),
    '#description' => t('Specify the hour (24-hour clock) in which notifications should be sent, if the frequency is one day or greater.'),
    '#default_value' => variable_get('notify_send_hour', 9),
    '#options' => array(
      0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
      10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
      20, 21, 22, 23,
    ),
  );

  $form['notify_settings']['notify_attempts'] = array(
    '#type' => 'select',
    '#title' => t('Number of failed sends after which notifications are disabled'),
    '#description' => t('The maximum number of failed attempts to send e-mail to tolerate before notification is suspended.'),
    '#default_value' => variable_get('notify_attempts', 5),
    '#options' => $attempts,
  );

  $form['notify_settings']['notify_batchsize'] = array(
    '#type' => 'select',
    '#title' => t('Maximum number of notifications to send out per cron run'),
    '#description' => t('The maximum number of notification e-mails to send in each pass of  a <a href="@cron">cron maintenance task</a>. If necessary, reduce the number of items to prevent resource limit conflicts.', array('@cron' => url('admin/reports/status'))),
    '#default_value' => variable_get('notify_batchsize', 100),
    '#options' => $batch,
  );

  $form['notify_settings']['notify_include_updates'] = array(
    '#type' => 'checkbox',
    '#title' => t('Include updated posts in notifications.'),
    '#return_value' => 1,
    '#default_value' => variable_get('notify_include_updates', 0),
  );

  $form['notify_settings']['notify_unverified'] = array(
    '#type' => 'checkbox',
    '#title' => t('Exclude contents from unverified authors from user notifications.'),
    '#return_value' => 1,
    '#default_value' => variable_get('notify_unverified', 0),
  );

  $form['notify_settings']['notify_unpublished'] = array(
    '#type' => 'checkbox',
    '#title' => t('Administrators shall be notified about unpublished content of tracked types.'),
    '#return_value' => 1,
    '#default_value' => variable_get('notify_unpublished', 1),
  );

  if (drupal_multilingual()) {
    $form['notify_settings']['notify_multilingual'] = array(
      '#type' => 'radios',
      '#title' => t('Multilingual setting &ndash; new contents to include:'),
      '#default_value' => variable_get('notify_multilingual', 1),
      '#options' => array(t('All contents'), t("Contents in the user's preferred language + contents not yet translated"), t("Only contents in the user's preferred language")),
      '#description' => t('This setting lets you specfy what to include in user notifications on a multilingual site.  (Please note that new contents that are marked as "language neutral" will always be included, and that administrators will always be notified about all new contents.)'),
    );
  }

  $form['notify_settings']['notify_watchdog'] = array(
    '#type' => 'radios',
    '#title' => t('Watchdog log level'),
    '#default_value' => variable_get('notify_watchdog', 1),
    '#options' => array(t('All'), t('Failures+Summary'), t('Failures'), t('Nothing')),
    '#description' => t('This setting lets you specify how much to log.'),
  );

  $form['notify_settings']['notify_weightur'] = array(
    '#type' => 'textfield',
    '#title' => t('Weight of notification field in user registration form'),
    '#default_value' => variable_get('notify_weightur', 0),
    '#size' => 3,
    '#maxlength' => 5,
    '#description' => t('The weight you set here will determine the position of the notification field when it appears in the user registration form.'),
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save settings'),
  );

  return ($form);
}

/**
 * Submit for the notify_admin_settings form.
 */
function notify_admin_settings_submit($form, &$form_state) {
  variable_set('notify_period', $form_state['values']['notify_period']);
  variable_set('notify_batchsize', $form_state['values']['notify_batchsize']);
  variable_set('notify_send_hour', $form_state['values']['notify_send_hour']);
  variable_set('notify_attempts', $form_state['values']['notify_attempts']);
  variable_set('notify_include_updates', $form_state['values']['notify_include_updates']);
  variable_set('notify_unverified', $form_state['values']['notify_unverified']);
  variable_set('notify_unpublished', $form_state['values']['notify_unpublished']);
  if (isset($form_state['values']['notify_multilingual'])) {
    variable_set('notify_multilingual', $form_state['values']['notify_multilingual']);
  }
  variable_set('notify_watchdog', $form_state['values']['notify_watchdog']);
  variable_set('notify_weightur', $form_state['values']['notify_weightur']);

  variable_set('notify_cron_next', 0); // Force reset.
  drupal_set_message(t('Notify admin settings saved.'));
}

/**
 * Menu callback, show admin list of queue status.
 */
function notify_admin_queue($form, &$form_state) {
  $period = variable_get('notify_period', 86400);
  $since = variable_get('notify_send_last', REQUEST_TIME - $period);
  $lastdate = format_date($since, 'short');
  $start = variable_get('notify_send_start', 0);
  $startdate = format_date($start, 'short');
  $notify_send_last  = variable_get('notify_send_last', 0);
  $next_last = _notify_next_notificaton($notify_send_last);

  if ($next_last == -1) {
    $batch_msg = t('No more notifications scheduled');
  } elseif ($next_last == 0) {
    $batch_msg = t('The next notification is scheduled for the next cron run');
  }
  else {
    $next = format_date($next_last, 'short');
    $batch_msg = t('The next notification is scheduled for the first cron run after ') . $next;
  }

  $form = array();

  $form['process'] = array(
    '#type' => 'radios',
    '#title' => t('Notification queue operations'),
    '#default_value' => 0,
    '#options' => array(t('Send batch now'), t('Truncate queue'), t('Override timestamp')),
    '#description' => t('Select &#8220;Send batch now&#8220; to send next batch of e-mails queued for notifications. Select &#8220;Truncate queue&#8220; to empty queue of pending notification <em>without</em> sending e-mails. Select &#8220;Override timestamp&#8220; to override the last notification timestamp. Press &#8220;Submit&#8220; to execute.'),
  );

  $send_last = format_date($notify_send_last, 'custom', 'Y-m-d H:i:s');
  
  $form['lastdate'] = array(
    '#type' => 'textfield',
    '#title' => t('Last notification timestamp'),
    '#default_value' => $send_last,
    '#size' => 19,
    '#maxlength' => 19,
    '#description' => t('To explicitly set the last notification timestamp, change the value of this field and select the &#8220;Override timestamp&#8220; option above, then press &#8220;Submit&#8220; to execute.'),
  ); 

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
  );

  $form['batch'] = array(
    '#type' => 'fieldset',
    '#title' => t('Status'),
    '#collapsible' => TRUE,
  );

  list ($np, $cp, $nn, $cn, $nu, $cu) = _notify_count();

  $npcp = $np + $cp;
  if ($npcp) {
    $queue_msg = t('Notifications about at least !item queued', array(
      '!item' => format_plural($npcp, '1 item is', '@count items are'),
    ));
  } else {
    $queue_msg = t('No notifications queued');
  }
  $flagcnt = count(variable_get('notify_skip_nodes', array())) + count(variable_get('notify_skip_comments', array()));
  if ($flagcnt) {
    $skip_msg = t('!item flagged for skipping', array(
      '!item' => format_plural($flagcnt, '1 item is', '@count items are'),
    ));
  } else {
    $skip_msg = t('No item is flagged for skipping');
  }

  if (($np && $nu) || ($cp && $cu)) {
    $nonew_msg = '';
  }
  else {
    $nonew_msg = t(', no notification about unpublished items are queued');
  }
  if ($nu + $cu) {
    $unpub_msg = t('Unpublished: !nodeup and !commup', array(
      '!nodeup' => format_plural($nu, '1 node', '@count nodes'),
      '!commup' => format_plural($cu, '1 comment', '@count comments'),
    )) . $nonew_msg;
  }
  else {
    $unpub_msg = t('No unpublished items');
  }

  $sent = variable_get('notify_num_sent', 0);
  $fail = variable_get('notify_num_failed', 0);
  $batch_remain = count(variable_get('notify_users', array()));

  $creat_msg = t('There are !nodes and !comms created', array(
    '!nodes' => format_plural($np, '1 node', '@count nodes'),
    '!comms' => format_plural($cp, '1 comment', '@count comments'),
  ));
  if ($nn + $cn) {
    $publ_msg = t(', and in addition !noderp and !commrp published,', array(
      '!noderp' => format_plural($nn, '1 node', '@count nodes'),
      '!commrp' => format_plural($cn, '1 comment', '@count comments'),
    ));
  }
  else {
    $publ_msg = '';
  }
  if ($batch_remain) {
    $intrv_msg = t('between !last and !start', array(
       '!last' => $lastdate,
       '!start' => $startdate,
    ));
    $sent_msg = t('Batch not yet complete.  So far !sent has been sent (!fail, !remain to go)', array(
      '!sent' => format_plural($sent, '1 e-mail', '@count e-mails'),
      '!fail' => format_plural($fail, '1 failure', '@count failures'),
      '!remain' => format_plural($batch_remain, '1 user', '@count users'),
    ));
  }
  else {
    $intrv_msg = t('since !last', array(
      '!last' => $lastdate,
    ));
    $sent_msg = t('Last batch:') . ' ';
    if ($sent == 0) {
      $sent_msg = t('No e-mails were sent');
    }
    else {
      $sent_msg .= t('sent !sent', array(
        '!sent' => format_plural($sent, '1 e-mail', '@count e-mails'),
      ));
    }
    if ($fail > 0) {
      $sent_msg .= ', ' . t('!fail', array(
        '!fail' => format_plural($fail, '1 failure', '@count failures'),
      ));
    }
    elseif ($sent) {
      $sent_msg .= ', ' . t('no failures');
    }
  }
  $mailsystem = variable_get('mail_system', NULL);
  $ms = isset($mailsystem['default-system']) ? $mailsystem['default-system'] : t('system default');
  $form['batch']['schedule'] = array(
    '#markup' => $creat_msg . $publ_msg . ' ' . $intrv_msg . '.<br>'
    . $unpub_msg . '.<br>'
    . $queue_msg . '.<br>'
    . $skip_msg . '.<br>'
    . $sent_msg . '.<br>'
    . $batch_msg . '.<br>'
    . t('Default MailSystem: ') . $ms . '.'
  );
  return $form;
}

/**
 * Submit for the notify_admin_queue form.
 */
function notify_admin_queue_submit($form, &$form_state) {
  unset($form);

  $process= $form_state['values']['process'];
  $notify_send_last = variable_get('notify_send_last', 0);
  $frform_send_last = strtotime($form_state['values']['lastdate']);
  if (FALSE ===  $frform_send_last) {
    form_set_error('notify_admin_queue', t('This does not look like a valid date format.'));
    return;
  }
  $frform_string = format_date($frform_send_last. 'short');
  if ($process < 2) {
    if ($notify_send_last != $frform_send_last) {
      form_set_error('notify_admin_queue', t('You must select &#8220;Override timestamp&#8221; to override the timestamp.'));
      return;
    }
  }
  elseif ($process == 2) {
    if ($notify_send_last == $frform_send_last) {
      form_set_error('notify_admin_queue', t('You selected &#8220;Override timestamp&#8221;, but the timestamp is not altered.'));
      return;
    }
  }

  $watchdog_level = variable_get('notify_watchdog', 0);
  if (0 == $form_state['values']['process']) { // flush
    list($num_sent, $num_fail) = _notify_send();

    if ($num_fail > 0) {
      drupal_set_message(t('!sent notification !emsent sent successfully, !fail !emfail could not be sent.',
        array(
          '!sent' => $num_sent, '!emsent' =>  format_plural($num_sent, 'e-mail', 'e-mails'),
          '!fail' => $num_fail, '!emfail' =>  format_plural($num_fail, 'notification', 'notifications'),
        )
      ), 'error');
      $watchdog_status = WATCHDOG_ERROR;
    }
    elseif ($num_sent > 0) {
      drupal_set_message(t('!count pending notification !emails have been sent in this pass.', array('!count' => $num_sent, '!emails' =>  format_plural($num_sent, 'e-mail', 'e-mails'))));
      $watchdog_status = WATCHDOG_INFO;
    }
    if (0 == ($num_sent + $num_fail)) {
      drupal_set_message(t('No notifications needed to be sent in this pass.'));
    }
    else {
      if ($watchdog_level <= 1) {
        watchdog('notify', 'Notifications sent: !sent, failures: !fail.', array('!sent' => $num_sent, '!fail' => $num_fail), $watchdog_status);
      }
    }
    $num_sent += variable_get('notify_num_sent', 0);
    $num_fail += variable_get('notify_num_failed', 0);
    variable_set('notify_num_sent', $num_sent);
    variable_set('notify_num_failed', $num_fail);
  }
  elseif (1 == $form_state['values']['process']) { // truncate
    list ($res_nodes, $res_comms, $res_nopub, $res_copub, $res_nounp, $res_counp) = _notify_select_content();
    foreach ($res_nopub as $row) {
      db_query('DELETE FROM {notify_unpublished_queue} WHERE cid = :cid AND nid = :nid', array(':cid' => 0, ':nid' => $row->nid));
    }
    foreach ($res_copub as $row) {
      db_query('DELETE FROM {notify_unpublished_queue} WHERE cid = :cid AND nid = :nid', array(':cid' => $row->cid, ':nid' => $row->nid));
    }
    variable_set('notify_send_start', REQUEST_TIME);
    variable_set('notify_send_last', REQUEST_TIME);
    variable_set('notify_cron_next', 0); // Force reset
    variable_set('notify_users', array());
    drupal_set_message(t('The notification queue has been truncated. No e-mail were sent.'));
    if ($watchdog_level <= 1) {
      watchdog('notify', 'Notification queue truncated.', NULL, WATCHDOG_INFO);
    }
    return;
  }
  elseif (2 == $form_state['values']['process']) { // override
    $date = strtotime($form_state['values']['lastdate']);
    variable_set('notify_send_last', $date);
  }
  variable_del('notify_skip_nodes');
  variable_del('notify_skip_comments');
}

/**
 * Menu callback, show admin list of queued notification settings.
 */
function notify_admin_skip($form, &$form_state) {
  // Fetch list of nodes and comments scheduled for notification
  list ($res_nodes, $res_comms, $res_nopub, $res_copub, $res_nounp, $res_counp) = _notify_select_content();

  // Get the nodes and comments queued.
  $count = 0;
  $nodes = $comments = array();
  // Ordinary nodes
  foreach ($res_nodes as $row) {
    $nodes[$row->nid] = node_load($row->nid);
    $count++;
  }
  // Ordinary comments
  if ($res_comms) {
    foreach ($res_nopub as $row) {
      if (!isset($nodes[$row->nid])) {
        $nodes[$row->nid] = node_load($row->nid);
        $count++;
      }
    }
    foreach ($res_comms as $row) {
      $comment = comment_load($row->cid);
      $comments[$comment->nid][$row->cid] = $comment;
      $count++;
    }
    foreach ($res_copub as $row) {
      if (!isset($comments[$row->nid][$row->cid])) {
        $comments[$row->nid][$row->cid] = comment_load($row->cid);
        $count++;
      }
    }
  }
  // Published nodes in unpublished queue
  foreach ($res_nopub as $row) {
    if (!isset($nodes[$row->nid])) {
      $nodes[$row->nid] = node_load($row->nid);
      $count++;
    }
  }
  // Unpublished nodes in unpublished queue
  foreach ($res_nounp as $row) {
    if (!isset($nodes[$row->nid])) {
      $nodes[$row->nid] = node_load($row->nid);
      $count++;
    }
  }
  $form = array();

  $form['#tree'] = TRUE;
  $form['info'] = array(
    '#markup' => '<p>' . t('The following table shows all messages that are candidates for bulk notifications:' . '</p>'),
  );

  $skpnodes = variable_get('notify_skip_nodes', array());
  $skpcomts = variable_get('notify_skip_comments', array());
  $ii = 0;
  $entities = array();
  foreach ($nodes as $node) {
    $ii++;
    $entities[$ii] = array();
    $entities[$ii]['nid'] = array(
      '#markup' => $node->nid,
    );
    $entities[$ii]['cid'] = array(
      '#markup' => '-',
    );
    $entities[$ii]['created'] = array(
      '#markup' => format_date($node->created, 'short'),
    );
    $entities[$ii]['updated'] = array(
      '#markup' => ($node->changed != $node->created) ? format_date($node->changed, 'short') : '-',
    );
    $entities[$ii]['title'] = array(
      '#markup' => $node->title,
    );
    $flag = in_array($node->nid, $skpnodes) ? 1 : 0;
    $entities[$ii]['dist'] = array(
      '#type' => 'checkbox',
      '#default_value' => $flag,
    );
  }
  foreach ($comments as $thread) {
    foreach ($thread as $comment) {
      $ii++;
      $entities[$ii] = array();
      $entities[$ii]['nid'] = array(
        '#markup' => $comment->nid,
      );
      $entities[$ii]['cid'] = array(
        '#markup' => $comment->cid,
      );
      $entities[$ii]['created'] = array(
        '#markup' => format_date($comment->created, 'short'),
      );
      $entities[$ii]['updated'] = array(
        '#markup' => ($comment->changed != $comment->created) ? format_date($comment->changed, 'short') : '-',
      );
      $entities[$ii]['title'] = array(
        '#markup' => $comment->subject,
      );
      $flag = in_array($comment->cid, $skpcomts) ? 1 : 0;
      $entities[$ii]['dist'] = array(
        '#type' => 'checkbox',
        '#default_value' => $flag,
      );
    }
  }
  $form['entities'] = $entities;
  $batch_remain = count(variable_get('notify_users', array()));
  if ($batch_remain) {
    $form['info2'] = array(
      '#markup' => '<p>' . t('Please note that the list above may be out of sync.  Saving an altered list of skip flags is disabled as long as notifications are being processed.') . '</p> ',
    );
  }
  else {
    $form['info2'] = array(
      '#markup' => '<p>' . t('To flag that <em>no</em> notification about a particular message should be sent, check the checkbox in the &#8220;Skip&#8220; column. Press &#8220;Save skip flags&#8220; to save the flags.') . '</p> ',
    );
  }
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save skip flags'),
    '#disabled' => $batch_remain,
  );
  return $form;
}

/**
 * Submit for the notify_admin_skip form.
 */
function notify_admin_skip_submit($form, &$form_state) {
  unset($form);
  $nodes = array();
  $comts = array();
  if (isset($form_state['values']['entities']) && $form_state['values']['entities']) {
    foreach ($form_state['values']['entities'] as $dist => $ii) {
      if ($ii['dist']) {
        $nid = $form_state['complete form']['entities'][$dist]['nid']['#markup'];
        $cid = $form_state['complete form']['entities'][$dist]['cid']['#markup'];
	if ('-' == $cid) {
          array_push($nodes, (int)$nid);
	}
	else {
          array_push($comts, (int)$cid);
	}
      }
    }
    variable_set('notify_skip_nodes', $nodes);
    variable_set('notify_skip_comments', $comts);
  }

  drupal_set_message(t('Skip flags saved.'));
  // notify_skip_nodes
}

/**
 * Theme function to theme the admin skip flag settings form in a table format.
 */
function theme_notify_admin_skip($variables) {
  $form = $variables['form'];
  $output = drupal_render($form['info']);
  $header = array(
    t('Nid'),
    t('Cid'),
    t('Created'),
    t('Updated'),
    t('Title'),
    t('Skip'),
  );

  $rows = array();
  foreach (element_children($form['entities']) as $uid) {
    $row = array();
    foreach (element_children($form['entities'][$uid]) as $entry_key) {
      unset($form['entities'][$uid][$entry_key]['#title']);

      $row[] = drupal_render($form['entities'][$uid][$entry_key]);
    }
    $rows[] = $row;
  }

  if (!$rows) {
    $rows[] = array(array(
        'data' => t('No notifications are scheduled.'),
        'colspan' => 5,
      ));
  }
  $output .= theme('table', array('header' => $header, 'rows' => $rows));

  $output .= drupal_render_children($form);
  return $output;
}


/**
 * Menu callback, show admin list of user default settings.
 */
function notify_admin_defaults($form, &$form_state) {
  $form = array();

  $defnu = variable_get('notify_reg_default', 1);
  $perms = user_role_permissions(array(DRUPAL_ANONYMOUS_RID => 'anon'));
  $anonp = array_key_exists('access notify', $perms[1]);
  if ($defnu && !$anonp) {
    drupal_set_message(t('If you want notification enabled by default for new users, you must grant the anonymous user role the permission to access notify.'), 'warning');
  }

  $set = 'defaults';
  $form['notify_defaults'] = array(
    '#type' => 'fieldset',
    '#title' => t('Notification default for new users'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#description' => t('The default master switch for new users (check for enabled, uncheck for disabled).'),
  );

  $form['notify_defaults']['notify_reg_default'] = array(
    '#type' => 'checkbox',
    '#title' => t('Receive e-mail notifications'),
    '#return_value' => 1,
    '#default_value' => variable_get('notify_reg_default', 1),
  );

  $form['notify_defs'] = array(
    '#type' => 'fieldset',
    '#title' => t('Initial settings'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#description' => t('These are the initial settings that will apply to new users registering, and to users that are enrolled in notifications with batch subscription.'),
  );
  $form['notify_defs']['node'] = array(
    '#type' => 'radios',
    '#title' => t('Notify new content'),
    '#default_value' => variable_get('notify_def_node', 1),
    '#options' => array(t('Disabled'), t('Enabled')),
    '#description' => t('Include new posts in the notification mail.'),
  );
  $form['notify_defs']['comment'] = array(
    '#type' => 'radios',
    '#access' => module_exists('comment'),
    '#title' => t('Notify new comments'),
    '#default_value' => variable_get('notify_def_comment', 0),
    '#options' => array(t('Disabled'), t('Enabled')),
    '#description' => t('Include new comments in the notification mail.'),
  );
  $form['notify_defs']['teasers'] = array(
    '#type' => 'radios',
    '#title' => t('How much to include?'),
    '#default_value' => variable_get('notify_def_teasers', 0),
    '#options' => array(
      t('Title only'),
      t('Title + Teaser/Excerpt'),
      t('Title + Body'),
      t('Title + Body + Fields'),
    ),
    '#description' => t('Select the amount of each item to include in the notification e-mail.'),
  );

  $set = 'ntype';
  $form[$set] = array(
    '#type' => 'fieldset',
    '#title' => t('Notification subscription by node type'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#description' => t('Tick content types to make available for subscription. Having nothing checked defaults to making all content types available.'),
  );

  foreach (node_type_get_types() as $type => $object) {
    $form[$set][NOTIFY_NODE_TYPE . $type] = array(
      '#type' => 'checkbox',
      '#title' => $object->name,
      '#return_value' => 1,
      '#default_value' => variable_get(NOTIFY_NODE_TYPE . $type, 0),
    );
  }

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save settings'),
  );

  //return system_settings_form($form);
  return ($form);
}

/**
 * Submit for the notify_admin_defaults form.
 */
function notify_admin_defaults_submit($form, &$form_state) {
  variable_set('notify_reg_default', $form_state['values']['notify_reg_default']);
  variable_set('notify_def_node',    $form_state['values']['node']);
  variable_set('notify_def_comment', $form_state['values']['comment']);
  variable_set('notify_def_teasers', $form_state['values']['teasers']);

  foreach (node_type_get_types() as $type => $object) {
    $ntype = NOTIFY_NODE_TYPE . $type;
    variable_set($ntype, $form_state['values'][$ntype]);
  }

  drupal_set_message(t('Notify default settings saved.'));
}

/**
 * Menu callback, show admin list of user notification settings.
 */
function notify_admin_users($form, &$form_state) {
  $form = array();

  $form['#tree'] = TRUE;
  $form['info'] = array(
    '#markup' => '<p>' . t('The following table shows all users that have notifications enabled:' . '</p>'),
  );

  $form['users'] = array();

  // Fetch users with notify enabled.
  $q = db_select('notify', 'n');
  $q->join('users', 'u', 'n.uid = u.uid');
  $q->fields('u', array('uid', 'name', 'mail', 'language'));
  $q->fields('n', array('status', 'node', 'comment', 'attempts', 'teasers'));
  $q->condition('n.status', 1);
  $q->condition('u.status', 1);
  $q->orderBy('u.name');
  $uresult = $q->execute();

  foreach ($uresult as $user) {
    $form['users'][$user->uid] = array();
    $form['users'][$user->uid]['name'] = array(
      '#markup' => theme('username', array('account' => $user)),
    );
    $form['users'][$user->uid]['mail'] = array(
      '#markup' => $user->mail,
    );
    $form['users'][$user->uid]['node'] = array(
      '#type' => 'checkbox',
      '#default_value' => $user->node,
    );
    $form['users'][$user->uid]['comment'] = array(
      '#type' => 'checkbox',
      '#default_value' => $user->comment,
    );
    $form['users'][$user->uid]['teasers'] = array(
      '#type' => 'select',
      '#default_value' => $user->teasers,
      '#options' => array(
        t('Title only'),
        t('Title + Teaser'),
        t('Title + Body'),
        t('Title + Body + Fields'),
      ),
    );
    $form['users'][$user->uid]['attempts'] = array(
      '#markup' => $user->attempts ? intval($user->attempts) : 0,
    );
  }

  $form['info2'] = array(
    '#markup' => '<p>' . t('You may check/uncheck the checkboxes and the &#8220;How much&#8220;-selection to change the users\' subscription. Press &#8220;Save settings&#8220; to save the settings.' . '</p>'),
  );

  $form['bulk'] = array(
    '#title' => t('Bulk subscribe all users'),
    '#type' => 'checkbox',
    '#default_value' => FALSE,
    '#description' => t('Subscribe all non-blocked users that do not already subscribe to notifications.'),
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save settings'),
  );
  return $form;
}

/**
 * Submit for the notify_admin_users form.
 */
function notify_admin_users_submit($form, &$form_state) {
  unset($form);

  if (isset($form_state['values']['bulk']) && 1 == $form_state['values']['bulk']) {
    $node = variable_get('notify_def_node', 1);
    $comment = variable_get('notify_def_comment', 0);
    $teasers = variable_get('notify_def_teasers', 0);
    $result = db_query('SELECT u.uid, u.name FROM {users} u WHERE u.uid > 0 AND status = 1 AND u.uid NOT IN (SELECT n.uid FROM {notify} n)');

    foreach ($result as $record) {
      db_insert('notify')
      ->fields(array(
        'uid' => $record->uid,
        'status' => 1,
        'node' => $node,
        'comment' => $comment,
        'teasers' => $teasers,
        'attempts' => 0,
      ))
      ->execute();
    }
  }
  elseif (!array_key_exists('users', $form_state['values'])) {
    drupal_set_message(t('No users have notifications enabled.'), 'warning');
    return;
  }
  if (isset($form_state['values']['users']) && $form_state['values']['users']) {
    foreach ($form_state['values']['users'] as $uid => $settings) {
      db_update('notify')
      ->fields(array(
        'node' => $settings['node'],
        'teasers' => $settings['teasers'],
        'comment' => $settings['comment'],
        // 'attempts' => $settings['attempts'],
      ))
      ->condition('uid', $uid)
      ->execute();
    }
  }

  drupal_set_message(t('Notify settings saved.'));
}

/**
 * Theme function to theme the admin user settings form in a table format.
 */
function theme_notify_admin_users($variables) {
  $form = $variables['form'];
  $output = drupal_render($form['info']);
  $header = array(
    t('Username'),
    t('E-mail address'),
    t('Content'),
    t('Comment'),
    t('How much'),
    t('Failed attempts'),
  );

  $rows = array();
  foreach (element_children($form['users']) as $uid) {
    $row = array();
    foreach (element_children($form['users'][$uid]) as $entry_key) {
      unset($form['users'][$uid][$entry_key]['#title']);

      $row[] = drupal_render($form['users'][$uid][$entry_key]);
    }
    $rows[] = $row;
  }

  if (!$rows) {
    $rows[] = array(array(
        'data' => t('No users have notifications enabled.'),
        'colspan' => 6,
      ));
  }
  $output .= theme('table', array('header' => $header, 'rows' => $rows));

  $output .= drupal_render_children($form);
  return $output;
}

/**
 * Menu callback; show user notification options.
 */
function notify_user_settings_form($form, &$form_state, $arg) {
  global $user;

  if ($user->uid != $arg->uid && !user_access('administer notify')) {
    drupal_access_denied();
    return;
  }

  $account = user_load($arg->uid);
  if (!is_object($account)) {
    drupal_not_found();
    return;
  }

  $result = db_query('SELECT u.uid, u.name, u.mail, n.status, n.node, n.teasers, n.comment FROM {users} u LEFT JOIN {notify} n ON u.uid = n.uid WHERE u.uid = :uid', array(':uid' => $account->uid));
  if (0==$result->rowCount())
    $notify = NULL; // Internal error.
  else
    $notify = $result->fetchObject();

  $form = array();
  if (!$notify->mail) {
    drupal_set_message(t('Your e-mail address must be specified on your <a href="@url">my account</a> page.', array('@url' => url('user/' . $account->uid . '/edit'))), 'error');
  }


  $form['notify_page_master'] = array(
    '#type' => 'fieldset',
    '#title' => t('Master switch'),
  );
  // If user existed before notify was enabled, these are not set in db.
  if (!isset($notify->status)) {
    $notify->status = 0;
    $notify->node = 0;
    $notify->teasers = 0;
    $notify->comment = 0;
  }
  if (module_exists('advanced_help')) {
    $output = theme('advanced_help_topic', array(
      'module' => 'notify',
      'topic' => 'users',
    ));
  }
  else {
    $output = '';
  }

  $form['notify_page_master']['status'] = array(
    '#type' => 'radios',
    '#title' => t('Notify status'),
    '#default_value' => $notify->status,
    '#options' => array(t('Disabled'), t('Enabled')),
    '#description' => $output . '&nbsp;' . t('The master switch overrides all other settings for Notify.  You can use it to suspend notifications without having to disturb any of your settings under &#8220;Detailed settings&#8221; and &#8220;Subscriptions&#8221;.'),
  );

  $form['notify_page_detailed'] = array(
    '#type' => 'fieldset',
    '#title' => t('Detailed settings'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#description' => t('These settings will only be effective if the master switch is set to &#8220;Enabled&#8221;.'),
  );
  $form['notify_page_detailed']['node'] = array(
    '#type' => 'radios',
    '#title' => t('Notify new content'),
    '#default_value' => $notify->node,
    '#options' => array(t('Disabled'), t('Enabled')),
    '#description' => t('Include new posts in the notification mail.'),
  );
  $form['notify_page_detailed']['comment'] = array(
    '#type' => 'radios',
    '#access' => module_exists('comment'),
    '#title' => t('Notify new comments'),
    '#default_value' => $notify->comment,
    '#options' => array(t('Disabled'), t('Enabled')),
    '#description' => t('Include new comments in the notification mail.'),
  );
  $form['notify_page_detailed']['teasers'] = array(
    '#type' => 'radios',
    '#title' => t('How much to include?'),
    '#default_value' => $notify->teasers,
    '#options' => array(
      t('Title only'),
      t('Title + Teaser/Excerpt'),
      t('Title + Body'),
      t('Title + Body + Fields'),
    ),
    '#description' => t('Select the amount of each item to include in the notification e-mail.'),
  );

  $set = 'notify_page_nodetype';
  $form[$set] = array(
    '#type' => 'fieldset',
    '#title' => t('Subscriptions'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#description' => t('Tick the content types you want to subscribe to.'),
  );
  $alltypes = node_type_get_types();
  $enatypes = array();

  foreach (node_type_get_types() as $type => $object) {
    if (variable_get(NOTIFY_NODE_TYPE . $type, 0)) {
      $enatypes[] = array($type, $object->name);
    }
  }
  if (user_access('administer notify queue', $account) || empty($enatypes )) {
    $enatypes = array();
    foreach ($alltypes as $obj) {
      $enatypes[] = array($obj->type, $obj->name);
    }
  }

  $exists = _notify_user_has_subscriptions($account->uid);
  if ($exists) {
    // Custom subscriptions exists, use those.
    foreach ($enatypes as $type) {
      $field = db_query('SELECT uid FROM {notify_subscriptions} WHERE (uid = :uid) AND (type = :type)', array(':uid' => $account->uid, ':type' => $type[0]))->fetchObject();
      $default = $field ? TRUE : FALSE;
      $form[$set][NOTIFY_NODE_TYPE . $type[0]] = array(
        '#type' => 'checkbox',
        '#title' => $type[1],
        '#return_value' => 1,
        '#default_value' => $default,
      );
    }
  }
  else {
    // No custom subscriptions, so inherit default.
    foreach ($enatypes as $type) {
      $form[$set][NOTIFY_NODE_TYPE . $type[0]] = array(
        '#type' => 'checkbox',
        '#title' => $type[1],
        '#return_value' => 1,
        '#default_value' => TRUE,
      );
    }
  }


  $form['uid'] = array(
    '#type' => 'value',
    '#value' => $account->uid,
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save settings'),
  );

  return $form;
}


/**
 * Submit for the notify_user_settings form.
 */
function notify_user_settings_form_submit($form, &$form_state) {
  unset($form);
  $uid = $form_state['values']['uid'];
  db_delete('notify')
    ->condition('uid', $uid)
    ->execute();

  $id = db_insert('notify')
    ->fields(array(
    'uid' => $uid,
    'status' => $form_state['values']['status'],
    'node' => $form_state['values']['node'],
    'teasers' => $form_state['values']['teasers'],
    'comment' => $form_state['values']['comment'],
  ))
    ->execute();
  $subscriptions = array();
  // Remember that this is a custom subscriber.
  $subscriber = _notify_user_has_subscriptions($uid);
  if (!$subscriber) {
    db_insert('notify_subscriptions')
    ->fields(array(
      'uid' => $uid,
      'type' => 'magic custom subscription',
    ))
    ->execute();
  }

  foreach ($form_state['values'] as $key => $value) {
    if (preg_match("/^" . NOTIFY_NODE_TYPE . "/", $key)) {
      $key = substr($key, 17);
      $id = db_query('SELECT id FROM {notify_subscriptions} WHERE (uid = :uid) AND (type = :key)', array(':uid' => $uid, ':key' => $key))->fetchObject();
      if ($id) {
        $id = $id->id;
	if (!$value) {
          db_delete('notify_subscriptions')
            ->condition('id', $id)
            ->execute();
        }
      }
      else {
         if ($value) {
	   db_insert('notify_subscriptions')
             ->fields(array(
               'uid' => $uid,
               'type' => $key,
             ))
             ->execute();
         }
      }
    }
  }

  drupal_set_message(t('Notify settings saved.'));
}
