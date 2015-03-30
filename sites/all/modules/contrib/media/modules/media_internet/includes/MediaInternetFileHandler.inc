<?php

/**
 * @file
 * Definition of MediaInternetFileHandler.
 */

/**
 * A class for managing the addition of Internet files.
 */
class MediaInternetFileHandler extends MediaInternetBaseHandler {

  public $fileObject;

  public function preSave(&$file_obj) {
    // Coppies the remote file locally.
    $remote_uri = $file_obj->uri;
    //@TODO: we should follow redirection here an save the final filename, not just the basename.
    $local_filename = basename($remote_uri);
    $local_filename = file_munge_filename($local_filename, media_variable_get('file_extensions'), FALSE);
    $local_uri = file_stream_wrapper_uri_normalize('temporary://' . $local_filename);
    if (!@copy($remote_uri, $local_uri)) {
      throw new Exception('Unable to add file ' . $remote_uri);
      return;
    }
    // Make the current fileObject point to the local_uri, not the remote one.
    $file_obj = file_uri_to_object($local_uri);
  }

  public function postSave(&$file_obj) {
    $scheme = variable_get('file_default_scheme', 'public') . '://';
    $uri = file_stream_wrapper_uri_normalize($scheme . $file_obj->filename);
    // Now to its new home.
    $file_obj = file_move($file_obj, $uri, FILE_EXISTS_RENAME);
  }

  public function getFileObject() {
    if (!$this->fileObject) {
      $this->fileObject = file_uri_to_object($this->embedCode);
    }
    return $this->fileObject;
  }

  public function claim($embedCode) {
    // Claim only valid URLs using a supported scheme.
    if (!valid_url($embedCode, TRUE) || !in_array(file_uri_scheme($embedCode), media_variable_get('fromurl_supported_schemes'))) {
      return FALSE;
    }

    // This handler is intended for regular files, so don't claim URLs
    // containing query strings or fragments.
    if (preg_match('/[\?\#]/', $embedCode)) {
      return FALSE;
    }

    // Since this handler copies the remote file to the local web server, do not
    // claim a URL with an extension disallowed for media uploads.
    $regex = '/\.(' . preg_replace('/ +/', '|', preg_quote(media_variable_get('file_extensions'))) . ')$/i';
    if (!preg_match($regex, basename($embedCode))) {
      return FALSE;
    }

    return TRUE;
  }
}
