<?php

/**
 * @file
 * Extends the MediaInternetBaseHandler class to handle oEmbed resources.
 */

/**
 * Implementation of MediaInternetBaseHandler.
 *
 * @see hook_media_internet_providers().
 */
class MediaInternetOEmbedHandler extends MediaInternetBaseHandler {
  public function parse($embedCode) {
    if ($provider = media_oembed_get_provider($embedCode, $matches)) {
      return file_stream_wrapper_uri_normalize('oembed://' . drupal_encode_path($embedCode));
    }
  }

  public function claim($embedCode) {
    if ($this->parse($embedCode)) {
      return TRUE;
    }
  }

  public function getFileObject() {
    $uri = $this->parse($this->embedCode);
    $file = file_uri_to_object($uri, TRUE);

    // Generate a file name for the file.
    if (empty($file->fid) && $info = $this->getOEmbed()) {
      // Try to default the file name to the resource's title.
      if (!empty($info['title'])) {
        $filename = truncate_utf8($info['title'], 255);
      }
      // Otherwise rely on basic text containing the provider name and type.
      else {
        if (!empty($info['provider_name'])) {
          $filename = t('Embedded @type media on @provider_name', array('@type' => $info['type'], '@provider_name' => $info['provider_name']));
        }
        else {
          $filename = t('Embedded @type media', array('@type' => $info['type']));
        }
      }

      $file->filename = $filename;
    }

    return $file;
  }

  /**
   * Returns an array representation of the oEmbed data, or NULL on failure.
   *
   * An example project that calls this method is Media Browser Plus
   * (http://drupal.org/project/media_browser_plus). Other projects may do so
   * in the future.
   */
  public function getOEmbed() {
    $embed = media_oembed_get_data($this->embedCode);
    return $embed ? (array) $embed : NULL;
  }
}
