<?php

/**
 * @file
 * Common pages for the Media module.
 */

/**
 * CTools modal callback for editing a file.
 */
function media_file_edit_modal($form, &$form_state, $file, $js) {
  ctools_include('modal');
  ctools_include('ajax');

  $form_state['ajax'] = $js;
  form_load_include($form_state, 'inc', 'file_entity', 'file_entity.pages');

  $output = ctools_modal_form_wrapper('file_entity_edit', $form_state);

  if ($js) {
    $commands = $output;

    if ($form_state['executed']) {
      $commands = array(ctools_modal_command_dismiss(t('File saved')));
      $preview = media_get_thumbnail_preview($file);
      $commands[] = ajax_command_replace('.media-item[data-fid=' . $file->fid . ']', render($preview));
    }

    print ajax_render($commands);
    exit();
  }

  // Otherwise, just return the output.
  return $output;
}
