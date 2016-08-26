<?php

/**
 * @file
 * Administrative page callbacks for the avatar_selection module.
 */


/**
 * Scan the directory for new files.
 *
 * @param $name
 *   The name of the avatar(s).
 * @param $access
 *   The permission - the value determines which user roles have rights to see
 *   the avatar.
 * @param $og
 *   Organic group (optional).
 * @param $weight
 *   Avatar weight to assign.
 * @return
 *   Number of images found.
 */
function _avatar_selection_scan_images($name, $access, $og = array(), $weight = 0) {
  $avatars = array();
  $add_count = 0;
  $delete_count = 0;

  $dir = file_build_uri('avatar_selection');
  file_prepare_directory($dir, FILE_CREATE_DIRECTORY);
  $mask = '/.*\.(gif|GIF|Gif|jpg|JPG|Jpg|jpeg|JPEG|Jpeg|png|PNG|Png)/';
  $listings = file_scan_directory($dir, $mask);

  $result = db_select('avatar_selection', 'avs')
    ->fields('avs', array('avatar'))
    ->execute();
  foreach ($result as $avatar) {
    $avatars[$avatar->avatar] = $avatar->avatar;
  }

  // Search for new files.  Remove matching records from avatars array.
  foreach ($listings as $listing) {
    $filename = str_replace("$dir/", '', $listing->filename);
    if (in_array($filename, $avatars)) {
      unset($avatars[$filename]);
    }
    else {
      // Manage the file and add it to the avatar table.
      $file = file_save(_avatar_selection_uri_to_object($dir . '/' . $listing->filename));
      _avatar_selection_save_avatar_info(0, $filename, (empty($name) ? $filename : $name), $access, $og, $weight, $file->fid);
      $add_count++;
    }
  }

  // Remove records from database where we have an avatar entry but no
  // corresponding file.
  foreach ($avatars as $avatar) {
    $file = _avatar_selection_uri_to_object($dir . '/' . $avatar, TRUE);
    avatar_selection_image_delete($file->fid);
    $delete_count++;
  }

  $count['add'] = $add_count;
  $count['delete'] = $delete_count;

  return $count;
}

/**
 * Create a file object from a file uri.
 *
 * @param $uri
 *   A file uri of an existing unmanaged file.
 * @param $use_existing
 *   Find existing file if possible.
 * @return
 *   A file object.
 */
function _avatar_selection_uri_to_object($uri, $use_existing = FALSE) {
  if ($use_existing) {
    $query = db_select('file_managed', 'f')
      ->fields('f', array('fid'))
      ->condition('uri', $uri)
      ->execute()
      ->fetchCol();
    if (!empty($query)) {
      $file = file_load(array_shift($query));
    }
  }
  if (!isset($file)) {
    global $user;
    $uri = file_stream_wrapper_uri_normalize($uri);
    $wrapper = file_stream_wrapper_get_instance_by_uri($uri);
    $file = new stdClass;
    $file->uid = $user->uid;
    $file->filename = basename($uri);
    $file->uri = $uri;
    $file->filemime = file_get_mimetype($uri);
    // This is gagged because some uris will not support it.
    $file->filesize = @filesize($uri);
    $file->timestamp = REQUEST_TIME;
    $file->status = FILE_STATUS_PERMANENT;
    $file->is_new = TRUE;
  }
  return $file;
}

/**
 * Select which form will be shown to the user, according to the permissions.
 *
 * @param $op
 *   Default NULL; the action the user wants to do after the function checks
 *   the permission.
 * @return
 *   Return the structure of the form.
 */
function avatar_selection_settings_page($op = NULL) {

  switch ($op) {
    case 'edit':
      $output = drupal_get_form('avatar_selection_config_form');
      break;
    case 'upload':
      $output = drupal_get_form('avatar_selection_upload_form');
      break;
    case 'list':
      $output = drupal_get_form('avatar_selection_edit_form');
      break;
    default:
      $form[] = array(
        '#type' => 'fieldset',
        '#title' => t('Add another'),
      );
      $output = drupal_get_form('avatar_selection_config_form');
      break;
  }
  return $output;
}


/**
 * Create the form structure for configuring the avatar module settings; seen
 * in the 'Configure' tab under the Avatar Selection administration page.
 *
 * @return
 *   Return the structure of the form.
 */
function avatar_selection_config_form($form) {
  if (!variable_get('user_pictures', 0)) {
    drupal_set_message(t('User Pictures option is disabled.  You will need to enable this option before you can use the Avatar Selection module.  You may configure this setting on the <a href="@url">User settings</a> page.', array('@url' => url('admin/config/people/accounts'))));
  }

  // To store how many avatars per page are displayed.
  $form['update']['avatar_per_page'] = array(
    '#type' => 'textfield',
    '#title' => t('How many avatars per page'),
    '#description' => t('The number of avatars to show per page.'),
    '#default_value' => variable_get('avatar_selection_avatar_per_page', 30),
    '#size' => 3,
  );

  $form['update']['disable_user_upload'] = array(
    '#type' => 'checkbox',
    '#title' => t('Disable users uploading pictures to profile'),
    '#description' => t('Allow users to pick their avatar from the selection but prevent them from uploading new avatars when editing their account.'),
    '#default_value' => variable_get('avatar_selection_disable_user_upload', FALSE),
  );
  $form['update']['force_set_image_reg'] = array(
    '#type' => 'checkbox',
    '#title' => t('Force users to select an avatar image on user registration.'),
    '#description' => t('This only applies on the user registration screen.'),
    '#default_value' => variable_get('avatar_selection_force_user_avatar_reg', FALSE),
  );
  $form['update']['force_set_image'] = array(
    '#type' => 'checkbox',
    '#title' => t('Force users to select an avatar image when editing their account'),
    '#description' => t('This only applies when the user is editing their account details and image uploads are disabled.'),
    '#default_value' => variable_get('avatar_selection_force_user_avatar', FALSE),
  );
  $form['update']['set_random_default'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable random default avatar image'),
    '#description' => t("Automatically set a random avatar image to be used when the user doesn't set one for their account."),
    '#default_value' => variable_get('avatar_selection_set_random_default', FALSE),
  );
  $form['update']['distinctive_avatars'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable unique avatars'),
    '#description' => t("Only allow users to pick an avatar that isn't already in use by another user.  If there are no available avatars left, the default avatar image will be used."),
    '#default_value' => variable_get('avatar_selection_distinctive_avatars', FALSE),
  );

  if (module_exists('image')) {
    $form['update']['imagecache_preset'] = array(
      '#type' => 'select',
      '#title' => t('Picture display style'),
      '#options' => image_style_options(TRUE),
      '#default_value' => variable_get('avatar_selection_imagecache_preset', ''),
      '#description' => t('Choose an display style for avatars in the selection list. Styles may be configured in the <a href="@config">Image styles</a> administration area. The <a href="@profiles">ImageCache Profiles</a> module can be used to format the avatars in other locations.', array('@config' => url('admin/config/media/image-styles'), '@profiles' => url('http://drupal.org/project/imagecache_profiles'))),
    );
  }

  $form['update']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Update'),
  );

  return $form;
}

/**
 * Create the form structure for uploading an avatar.
 *
 * @return
 *   Return the structure of the form.
 */
function avatar_selection_upload_form($form) {
  if (!variable_get('user_pictures', 0)) {
    drupal_set_message(t('User Pictures option is disabled.  You will need to enable this option before you can use the Avatar Selection module.  You may configure this setting on the <a href="@url">User settings</a> page.', array('@url' => url('admin/config/people/accounts'))));
  }

  $form['#attributes']['enctype'] = 'multipart/form-data';

  $dir = file_build_uri('avatar_selection');
  file_prepare_directory($dir, FILE_CREATE_DIRECTORY);
  $form['bulk_upload'] = array(
    '#type' => 'fieldset',
    '#title' => t('Bulk Upload / Delete'),
    '#description' => t("To upload a large number of avatars, first copy the images manually to the %dir folder, using ftp for example.  To make these new avatar images available, check the 'Scan for new avatars' option. All new images will then be added to the list.  By removing files from this directory and checking the box, you can also perform a bulk delete.", array('%dir' => $dir)),
    '#collapsed' => TRUE,
    '#collapsible' => TRUE,
  );
  $form['bulk_upload']['scan_avatars'] = array(
    '#type' => 'checkbox',
    '#title' => t('Scan avatars'),
    '#description' => t('All new avatar images found will be added to the list of available avatars with the name, weight and permissions defined below.  Scanning for new avatars may be slow depending on the number of files.  All avatar entries which no longer have a corresponding file will be be removed.'),
    '#default_value' => 0,
  );


  $form['picture_upload'] = array(
    '#type' => 'file',
    '#title' => t('Upload image'),
    '#size' => 48,
    '#description' => t('A new avatar image.  Maximum dimensions are %dimensions and the maximum size is %size kB.  Images must have one of the following extensions (case sensitive): png, jpg, jpeg, gif, PNG, JPG, JPEG, GIF.', array('%dimensions' => variable_get('user_picture_dimensions', '85x85'), '%size' => variable_get('user_picture_file_size', 30))) . ' ' .  variable_get('user_picture_guidelines', ''),
  );

  $form['avatar_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Name'),
    '#description' => t("Image name or title which will be displayed when hovering over the image.  It's also used in conjunction with the weight setting for sorting the avatars."),
    '#size' => 48,
  );
  $form['avatar_weight'] = array(
    '#type' => 'weight',
    '#title' => t('Weight'),
    '#delta' => 100,
    '#description' => t('Avatars with a lower weight appear before higher weighted avatars in lists.'),
  );
  $form['permissions'] = array(
    '#type' => 'fieldset',
    '#title' => t('Permissions'),
    '#weight' => 2,
  );
  $form['permissions']['access'] = array(
    '#type' => 'checkboxes',
    '#title' => t('User Roles'),
    '#options' => avatar_selection_handler_filter_role(),
    '#description' => t('Only the checked roles will be able to see this avatar icon; if no roles are checked, access will not be restricted.'),
  );
  if (module_exists('og')) {
    $form['permissions']['og_access'] = array(
      '#type' => 'checkboxes',
      '#title' => t('Organic Groups'),
      '#options' => avatar_selection_og_options(),
      '#description' => t('Only users in the checked organic groups will be able to see this avatar icon; if no groups are checked, access will not be restricted.'),
    );
  }

  $form['upload'] = array(
    '#type' => 'submit',
    '#value' => t('Upload'),
    '#weight' => 10,
  );

  return $form;
}

/**
 * Returns appropriate avatar set by role or og for configuration.
 */
function avatar_selection_roles_page($op = NULL) {
  $output = '';

  // Display the form where appropriate.
  if (isset($op) && ($op == 'role' || $op == 'og')) {
    $output = array();
    $output['avatar_selection_edit_form'] = drupal_get_form('avatar_selection_edit_form');
  }

  // Display the number of avatars per role / group.
  else {
    $avs_access = array();
    $og_access = array();
    $avs_access[0] = 0;
    $og_access[0] = 0;

    // Get the list of access roles and initialise the count to 0.
    $roles = avatar_selection_handler_filter_role();
    foreach ($roles as $rid => $role_name) {
      $avs_access[$rid] = 0;
    }

    // Get the list of organic groups and initialise the count to 0.
    if (module_exists('og')) {
      $ogroups = avatar_selection_og_options();
      foreach ($ogroups as $ogid => $ogroup_name) {
        $og_access[$ogid] = 0;
      }
    }

    // Get the total number of avatars available on the system.
    $total_count = 0;
    $total_count = db_select('avatar_selection', 'avs')
      ->fields('avs', array('fid'))
      ->countQuery()
      ->execute()
      ->fetchField();
    $output .= '<p>' . t('There is a total of %count avatars configured.', array('%count' => $total_count)) . '</p>';


    // Get the count of avatars per role.
    $result = db_query("SELECT avsr.rid, count(*) AS count FROM {avatar_selection} avs LEFT JOIN {avatar_selection_roles} avsr ON avs.aid = avsr.aid GROUP BY avsr.rid");
    foreach ($result as $avatar) {
      if (empty($avatar->rid)) {
        $avs_access[0] += $avatar->count;
      }
      else {
        $avs_access[$avatar->rid] += $avatar->count;
      }
    }

    // Get the count of avatars per organic group.
    $result = db_query("SELECT avso.ogid, count(*) AS count FROM {avatar_selection} avs LEFT JOIN {avatar_selection_og} avso ON avs.aid = avso.aid GROUP BY avso.ogid");
    foreach ($result as $avatar) {
      if (empty($avatar->ogid)) {
        $og_access[0] += $avatar->count;
      }
      else {
        $og_access[$avatar->ogid] += $avatar->count;
      }
    }

    // Format the user roles table.
    $avs_rows = array();
    $header = array(t('User Role'), t('Number of Avatars'), t('Operations'));
    $edit = l(t('edit'), 'admin/config/people/avatar_selection/edit/role/0');
    $avs_rows[] = array(t('Available to all roles'), $avs_access[0], $edit);
    foreach ($roles as $rid => $role_name) {
      $edit = l(t('edit'), 'admin/config/people/avatar_selection/edit/role/' . $rid);
      $avs_rows[] = array($role_name, $avs_access[$rid], $edit);
    }
    $output .= theme('table', array('header' => $header, 'rows' => $avs_rows));


    // Format the organic groups table.
    if (module_exists('og')) {
      $og_rows = array();
      $header = array(t('Organic Group'), t('Number of Avatars'), t('Operations'));
      $edit = l(t('edit'), 'admin/config/people/avatar_selection/edit/og/0');
      $og_rows[] = array(t('Available to all groups'), $og_access[0], $edit);
      foreach ($ogroups as $ogid => $ogroup_name) {
        $edit = l(t('edit'), 'admin/config/people/avatar_selection/edit/og/' . $ogid);
        $og_rows[] = array($ogroup_name, $og_access[$ogid], $edit);
      }
      $output .= theme('table', array('header' => $header, 'rows' => $og_rows));
    }
  }

  return $output;
}


/**
 * Create the form structure for listing the avatars and managing them in the
 * 'Manage Avatars' tab under the Avatar Selection administration page.
 *
 * @param $form_state
 *   General variable, used to control the processing of the form.
 * @return
 *   Return the structure of the form.
 */
function avatar_selection_edit_form($form, $form_state) {
  $form = array();

  if (!variable_get('user_pictures', 0)) {
    drupal_set_message(t('User Pictures option is disabled.  You will need to enable this option before you can use the Avatar Selection module.  You may configure this setting on the <a href="@url">User settings</a> page.', array('@url' => url('admin/config/people/accounts'))));
  }

  drupal_add_css(drupal_get_path('module', 'avatar_selection') . '/avatar_selection.css');

  $set_type = arg(5);
  $set_id = arg(6);

  // We find out the current page number.
  $page = 0;
  if (isset($_GET['page']) && is_numeric($_GET['page'])) {
    $page = $_GET['page'];
  }

  $avatars_per_page = variable_get('avatar_selection_avatar_per_page', 30);
  $selects = _avatar_selection_image_list('', $set_type, $set_id, $page * $avatars_per_page, $avatars_per_page);
  if (!count($selects['avatars'])) {
    drupal_set_message(t('There are no avatars configured.'));
  }

  else {
    if (!isset($form_state['values'])) {
      $step = 'list';
    }
    else {
      $step = 'edit';
    }
    $form['step'] = array(
      '#type' => 'value',
      '#value' => $step,
    );


    if ($step == 'list') {

      if ($set_type == 'role') {
        $sets = avatar_selection_handler_filter_role();
      }
      elseif ($set_type == 'og' && module_exists('og')) {
        $sets = avatar_selection_og_options();
      }
      $sets[0] = t('All roles');
      drupal_set_title(t('Manage Avatars - %name', array('%name' => $sets[$set_id])), PASS_THROUGH);
      drupal_add_js(drupal_get_path('module', 'avatar_selection') . '/js/avatar_selection_pager.js');
      $js_file = drupal_get_path('module', 'avatar_selection') . '/js/avatar_selection.js';

      $form['select_avatar'] = array(
        '#type' => 'radios',
        '#title' => t('Select an avatar to edit'),
        '#options' => $selects['avatars'],
        '#required' => TRUE,
        '#attributes' => array('class' => array('user-avatar-select')),
        '#suffix' => theme('avatar_selection_pager', array('total' => $selects['total'], 'limit' => $avatars_per_page, 'js_file' => '/' . $js_file)),
      );

      $form['search'] = array(
        '#type' => 'submit',
        '#value' => t('Edit'),
        '#submit' => array('avatar_selection_edit_list_form_submit'),
      );

      drupal_add_js($js_file);
    }

    elseif ($step == 'edit') {
      drupal_set_title(t('Manage Avatars'));
      $form_state['#redirect'] = array('admin/config/people/avatar_selection/edit');
      $roles = avatar_selection_handler_filter_role();
      $aid = 0;
      $avs_access = $og_access = array();
      $weight = 0;
      $name = '';

      $query = db_select('avatar_selection', 'avs')
        ->fields('avs', array('aid', 'avatar', 'name', 'weight'))
        ->condition('avs.fid', $form_state['values']['select_avatar']);
      $query->leftJoin('avatar_selection_roles', 'avsr', 'avs.aid = avsr.aid');
      $query->addField('avsr', 'rid');
      $query->leftJoin('avatar_selection_og', 'avso', 'avs.aid = avso.aid');
      $query->addField('avso', 'ogid');
      $result = $query->orderBy('weight', 'ASC')
        ->orderBy('name', 'ASC')
        ->orderBy('avatar', 'ASC')
        ->execute();
      foreach ($result as $avatar) {
        $aid = $avatar->aid;
        $name = $avatar->name;
        $weight = $avatar->weight;
        if ($avatar->rid) {
          array_push($avs_access, $avatar->rid);
        }
        if ($avatar->ogid) {
          array_push($og_access, $avatar->ogid);
        }
      }

      $image_path = file_build_uri('avatar_selection');
      file_prepare_directory($image_path, FILE_CREATE_DIRECTORY);
      $selected_avatar = $avatar->avatar;
      $image = theme('image', array('path' => $image_path . '/' . $selected_avatar));
      $form['avatar_image'] = array(
        '#type' => 'item',
        '#title' => t('Image'),
        '#markup' => $image,
      );
      $form['aid'] = array(
        '#type' => 'value',
        '#value' => $aid,
      );

      $form['select_avatar'] = array(
        '#type' => 'value',
        '#value' => $form_state['values']['select_avatar'],
      );

      $form['avatar_name'] = array(
        '#type' => 'textfield',
        '#title' => t('Name'),
        '#description' => t("Image name or title which will be displayed when hovering over the image.  It's also used in conjunction with the weight setting for sorting the avatars."),
        '#size' => 48,
        '#default_value' => $name,
      );
      $form['avatar_weight'] = array(
        '#type' => 'weight',
        '#title' => t('Weight'),
        '#delta' => 100,
        '#description' => t('Avatars with a lower weight appear before higher weighted avatars in lists.'),
        '#default_value' => $weight,
      );
      $form['permissions'] = array(
        '#type' => 'fieldset',
        '#title' => t('Permissions'),
        '#weight' => 1,
      );
      $form['permissions']['access'] = array(
        '#type' => 'checkboxes',
        '#title' => t('User Roles'),
        '#default_value' => $avs_access,
        '#options' => $roles,
        '#description' => t('Only the checked roles will be able to see this avatar icon; if no roles are checked, access will not be restricted.'),
      );

      if (module_exists('og')) {
        $form['permissions']['og_access'] = array(
          '#type' => 'checkboxes',
          '#title' => t('Organic Groups'),
          '#default_value' => $og_access,
          '#options' => avatar_selection_og_options(),
          '#description' => t('Only users in the checked organic groups will be able to see this avatar icon; if no groups are checked, access will not be restricted.'),
        );
      }

      $form['update'] = array(
        '#type' => 'submit',
        '#value' => t('Update'),
        '#weight' => 9,
        '#submit' => array('avatar_selection_edit_update_form_submit'),
      );
      $form['delete'] = array(
        '#type' => 'submit',
        '#value' => t('Delete'),
        '#weight' => 10,
        '#submit' => array('avatar_selection_edit_delete_form_submit'),
      );
    }

  }

  return $form;
}


/**
 * Validate the submission.
 *
 * Ensure the number of avatars page setting is numeric.
 *
 * @param $form
 *   General variable used in drupal, defining the structure & the fields of a
 *   form.
 * @param &$form_state
 *   General reference, used to control the processing of the form.
 */
function avatar_selection_config_form_validate($form, &$form_state) {
  $error = FALSE;

  if ($form_state['values']['op'] == t('Update')) {
    if (!is_numeric($form_state['values']['avatar_per_page'])) {
      form_set_error('avatar_per_page', t('Must be a number.'));
      $error = TRUE;
    }
  }
}



/**
 * Validate the submission.
 *
 * Check if Delete has been chosen AND a checkbox has been selected.
 *
 * @param $form
 *   General variable used in drupal, defining the structure & the fields of a
 *   form.
 * @param &$form_state
 *   General reference, used to control the processing of the form.
 */
function avatar_selection_delete_form_validate($form, &$form_state) {
  if ($form_state['values']['op'] == t('Delete')) {
    if (count(array_filter($form_state['values']['images'])) == 0) {
      form_set_error('images', t('Please select images to delete.'));
    }
  }
}

/**
 * Submit the settings form in the Avatar Selection administration page.
 *
 * @param $form
 *   General variable used in drupal, defining the structure & the fields of a
 *   form.
 * @param &$form_state
 *   General reference, used to control the processing of the form.
 */
function avatar_selection_config_form_submit($form, &$form_state) {
  $op = $form_state['values']['op'];

  if ($op == t('Update')) {
    // Save system variables.
    variable_set('avatar_selection_disable_user_upload', $form_state['values']['disable_user_upload']);
    variable_set('avatar_selection_force_user_avatar_reg', $form_state['values']['force_set_image_reg']);
    variable_set('avatar_selection_force_user_avatar', $form_state['values']['force_set_image']);
    variable_set('avatar_selection_avatar_per_page', $form_state['values']['avatar_per_page']);
    variable_set('avatar_selection_set_random_default', $form_state['values']['set_random_default']);
    variable_set('avatar_selection_distinctive_avatars', $form_state['values']['distinctive_avatars']);
    if (module_exists('image')) {
      variable_set('avatar_selection_imagecache_preset', $form_state['values']['imagecache_preset']);
    }
    drupal_set_message(t('Configuration has been updated.'));
  }
}

/**
 * Submit the image upload form in the Avatar Selection administration page.
 *
 * @param $form
 *   General variable used in drupal, defining the structure & the fields of a
 *   form.
 * @param &$form_state
 *   General reference, used to control the processing of the form.
 */
function avatar_selection_upload_form_submit($form, &$form_state) {
  $op = $form_state['values']['op'];

  if ($op == t('Upload')) {
    // Get access settings.
    $access = array_keys(array_filter($form_state['values']['access']));
    $og = array();
    if (module_exists('og')) {
      $og = array_keys(array_filter($form_state['values']['og_access']));
    }
    $name = $form_state['values']['avatar_name'];
    $weight = $form_state['values']['avatar_weight'];

    // Scan for new files.
    if ($form_state['values']['scan_avatars'] == 1) {
      $count = _avatar_selection_scan_images($name, $access, $og, $weight);
      drupal_set_message(t('Scan complete: %added new avatars found. %deleted avatars removed.', array('%added' => $count['add'], '%deleted' => $count['delete'])));
    }

    // Save uploaded files.
    $dir = file_build_uri('avatar_selection');
    $is_writable = file_prepare_directory($dir, FILE_CREATE_DIRECTORY);

    if ($is_writable) {
      // If required, validate the uploaded picture.
      $validators = array(
        'file_validate_is_image' => array(),
        'file_validate_image_resolution' => array(variable_get('user_picture_dimensions', '85x85')),
        'file_validate_size' => array(variable_get('user_picture_file_size', 30) * 1024),
      );

      if ($file = file_save_upload('picture_upload', $validators, $dir, FILE_EXISTS_RENAME)) {

        if (image_get_info($file->uri)) {
          $file->status = FILE_STATUS_PERMANENT;
          $file = file_save($file);
          _avatar_selection_save_avatar_info(0, $file->filename, $name, $access, $og, $weight, $file->fid);
          drupal_set_message(t('New image saved.'));
        }
        else {
          file_delete($file);
          drupal_set_message(t('Uploaded file does not appear to be a valid image file. Please try again.'));
        }
      }
    }
    else {
      form_set_error('picture_upload', t('Directory not writable: !dir', array('!dir' => $dir)));
    }
  }
}

/**
 * Submit the image list form in the Avatar Selection - 'Manage Avatars' page.
 *
 * Function called when the Edit button is pressed.
 * Practically it sets the $form_state['rebuild'] value to true, which will
 * determine the rebuilding of the page.
 *
 * @param $form
 *   General variable used in drupal, defining the structure & the fields of a
 *   form.
 * @param &$form_state
 *   General reference, used to control the processing of the form.
 */
function avatar_selection_edit_list_form_submit($form, &$form_state) {
  $form_state['rebuild'] = TRUE;
}

/**
 * Submit the image list  form in the Avatar Selection - 'Manage Avatars' page.
 *
 * Function called when the Update button is pressed.
 *
 * @param $form
 *   General variable used in drupal, defining the structure & the fields of a
 *   form.
 * @param &$form_state
 *   General reference, used to control the processing of the form.
 */
function avatar_selection_edit_update_form_submit($form, &$form_state) {
  $og = array();
  $access = array_keys(array_filter($form_state['values']['access']));
  if (module_exists('og')) {
    $og = array_keys(array_filter($form_state['values']['og_access']));
  }
  $file = $form_state['values']['select_avatar'];
  $name = $form_state['values']['avatar_name'];
  $weight = $form_state['values']['avatar_weight'];
  $aid = $form_state['values']['aid'];
  _avatar_selection_save_avatar_info($aid, $file, $name, $access, $og, $weight);
  drupal_set_message(t('Image updated.'));
}

/**
 * Submit the image list form in the Avatar Selection - 'Manage Avatars' page.
 *
 * Function called when the Delete button is pressed, and deletes the selected
 * avatar(s).
 *
 * @param $form
 *   General variable used in drupal, defining the structure & the fields of a
 *   form.
 * @param &$form_state
 *   General reference, used to control the processing of the form.
 */
function avatar_selection_edit_delete_form_submit($form, &$form_state) {
  $fid = $form_state['values']['select_avatar'];
  $deleted = avatar_selection_image_delete($fid);
  if ($deleted) {
    drupal_set_message(t('Image deleted.'));
  }
}

/**
 * Delete the specified avatar image.
 *
 * @param $fid
 *   The image file id to be deleted.
 */
function avatar_selection_image_delete($fid) {
  file_delete(file_load($fid));

  $aid = db_query("SELECT aid FROM {avatar_selection} WHERE fid = :avatar", array(':avatar' => $fid))->fetchField();
  if ($aid) {
    $result = db_delete('avatar_selection')
      ->condition('aid', $aid)
      ->execute();
    $result = db_delete('avatar_selection_roles')
      ->condition('aid', $aid)
      ->execute();
    $result = db_delete('avatar_selection_og')
      ->condition('aid', $aid)
      ->execute();
  }

  return TRUE;
}

/**
 * Create the SQL queries in order to save the avatar path and data into the
 * database, and perform them according to the SQL server type.
 *
 * @param $aid
 *   The avatar identifier.
 * @param $image
 *   The avatar image.
 * @param $name
 *   The avatar name, used as the image alternative text on the forms.
 * @param $access
 *   Array of roles - the value determines which user roles have rights to see
 *   the avatar.
 * @param $og
 *   Array of organic groups (optional).
 * @param $weight
 *   The weight of the avatar.  Lower weighted avatars appear before higher
 *   weighted avatars in the list.
 * @param $fid
 *   The managed file id
 */
function _avatar_selection_save_avatar_info($aid, $image, $name, $access, $og = array(), $weight = 0, $fid = NULL) {

  // Add or update avatar_selection table.
  if ($aid) {
    $result = db_update('avatar_selection')
      ->fields(array(
          'name' => $name,
          'weight' => $weight,
        ))
      ->condition('aid', $aid)
      ->execute();
    $result = db_delete('avatar_selection_roles')
      ->condition('aid', $aid)
      ->execute();
    $result = db_delete('avatar_selection_og')
      ->condition('aid', $aid)
      ->execute();
  }
  else {
    $aid = db_insert('avatar_selection')
      ->fields(array(
        'avatar' => $image,
        'name' => $name,
        'weight' => $weight,
        'fid' => $fid,
      ))
      ->execute();
  }

  // Add access settings.
  if (is_array($access) && count($access)) {
    foreach ($access as $rid) {
      $id = db_insert('avatar_selection_roles')
        ->fields(array(
          'aid' => $aid,
          'rid' => $rid,
        ))
        ->execute();
    }
  }
  if (is_array($og) && count($og)) {
    foreach ($og as $ogid) {
      $id = db_insert('avatar_selection_og')
        ->fields(array(
          'aid' => $aid,
          'ogid' => $ogid,
        ))
        ->execute();
    }
  }
}

/**
 * Return a list of the existing roles.
 *
 * @return
 *   Return the role id(s).
 */
function avatar_selection_handler_filter_role() {
  $rids = array();
  $result = db_select('role', 'r')
    ->fields('r', array('rid', 'name'))
    ->orderBy('r.name', 'ASC')
    ->execute();
  foreach ($result as $obj) {
    $rids[$obj->rid] = $obj->name;
  }
  return $rids;
}

/**
 * Get og options.
 */
function avatar_selection_og_options() {
  $options = array();
  foreach (node_load_multiple(og_get_all_group()) as $node) {
    $options[$node->nid] = $node->title;
  }
  return $options;
}
