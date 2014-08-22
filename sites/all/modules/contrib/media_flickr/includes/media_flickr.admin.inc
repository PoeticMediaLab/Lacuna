<?php

/**
 *  @file
 *  Administrative page callbacks for Media: Flickr.
 */

/**
 * Callback for /admin/configure/media/media_flickr.
 */
function media_flickr_settings_form() {
  $form = array();
  $form['api'] = array(
    '#type' => 'fieldset',
    '#title' => t('Flickr API'),
    '#description' => t('You will first need to apply for an API Developer Key from the <a href="@flickr" target="_blank">Flickr Developer Profile page</a>.', array('@flickr' => MEDIA_FLICKR_API_APPLICATION_URL)),
    '#collapsible' => TRUE,
    '#collapsed' => (media_flickr_variable_name('api_key') != ''),
  );
  $form['api'][media_flickr_variable_name('api_key')] = array(
    '#type' => 'textfield',
    '#title' => t('Flickr API Key'),
    '#default_value' => media_flickr_variable_get('api_key'),
    '#description' => t('Please enter your Flickr Developer Key here.'),
  );
  $form['api'][media_flickr_variable_name('api_secret')] = array(
    '#type' => 'textfield',
    '#title' => t('Flickr API Secret'),
    '#default_value' => media_flickr_variable_get('api_secret'),
    '#description' => t('If you have a secret for the Flickr API, enter it here.'),
  );
  return system_settings_form($form);
}

/**
 *  Callback for /media/add/media_flickr and
 *  /admin/content/media/add/media_flickr.
 */
function media_flickr_add($form, &$form_state = array(), $redirect = NULL) {
  global $user;
  $form = array();
  $form['flickr'] = array(
    '#type' => 'vertical_tabs',
  );
  $form['flickr']['all'] = array(
    '#type' => 'fieldset',
    '#title' => t('My Flickr photos'),
  );

  // Get all flickr files for this user
  $results = db_query("SELECT fid FROM {file_managed} WHERE uid = :uid AND uri LIKE :uri", array(
    ':uid' => $user->uid,
    ':uri' => 'flickr%%'
  ))->fetchAll();

  module_load_include('inc', 'media_flickr', 'includes/media_flickr.utilities');

  foreach ($results as $result) {
    $file = file_load($result->fid);
    $url =  _media_flickr_photo_url(basename($file->uri));
    $output = theme('image', array(
      'path' => $url,
      'title' => 'title',
      'alt' => 'alt',
      'attributes' => array('width' => 200, 'hspace' => 10, 'vspace' => 10),
      'getsize' => FALSE,
    ));

    $form['flickr']['all'][$file->fid] = array(
      '#markup' => l($output, $url, array('html' => TRUE, 'attributes' => array('target' => '_blank'))),
    );
  }

  $form['flickr']['add_from_url'] = array(
    '#type' => 'fieldset',
    '#title' => t('Add from URL'),
  );

  $form['flickr']['add_from_url'] ['url'] = array(
    '#type' => 'textfield',
    '#title' => 'URL',
    '#description' => 'Input the URL of the desired Flickr photo page.',
  );

  $form['flickr']['add_from_url'] ['redirect'] = array(
    '#type' => 'value',
    '#value' => $redirect,
  );

  $form['flickr']['add_from_url'] ['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Submit',
  );

  return $form;
}

/**
 *  Validation for media_flickr_add().
 */
function media_flickr_add_validate($form, &$form_state) {
  if (!preg_match('@flickr\.com/photos/([^/]*)/(\d+)@i', $form_state['values']['url'], $matches)) {
    form_set_error('url', t('Please submit a valid Flickr photo URL.'));
  }
}

/**
 *  Submission for media_flickr_add().
 *
 *  This will create a file object for the Flickr video.
 */
function media_flickr_add_submit($form, &$form_state) {
  $uri = media_flickr_media_parse($form_state['values']['url']);

  $defaults = array (
    'display' => TRUE,
  );

  // @TODO: This won't work for Flickr and many other streams.
//   copy($url, $destination);

  $file = file_uri_to_object($uri);

  file_save($file);

  if ($file) {
    $form_state['redirect'] = 'media/' . $file->fid . '/edit';
    field_attach_submit('media', $file, $form, $form_state);
    // Make a copy of the file object to use as the media object
    // (file is a field of media and the base table). This is weird.
    $media = clone($file);
    $file->file = array();
    $file->file[LANGUAGE_NONE] = array();
    $file->file[LANGUAGE_NONE][0] = (array)$file + $defaults;
    $file->is_new = TRUE;
    field_attach_insert('media', $file);
  }
  else {
    drupal_set_message(t('An error occurred and no file was saved.'), 'error');
  }

  $form_state['redirect'] = !empty($form_state['values']['redirect']) ? $form_state['values']['redirect'] : 'media/' . $file->fid . '/edit';
}
