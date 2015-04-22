<?php

/**
 *  @file
 *  Extends the MediaReadOnlyStreamWrapper class to handle oEmbed resources.
 */

/**
 *  Create an instance like this:
 *  $oembed = new MediaOEmbedStreamWrapper('oembed://[provider-url]');
 */
class MediaOEmbedStreamWrapper extends MediaReadOnlyStreamWrapper {
  static function getMimeType($uri, $mapping = NULL) {
    $url = rawurldecode(substr($uri, 9));
    $embed = media_oembed_get_data($url);

    // The mime type can be specified in hook_media_oembed_response_alter()
    // which is useful to map responses with type 'rich' and 'link' to more
    // appropriate Drupal file entity bundles.
    // See media_oembed_media_oembed_response_alter().
    if (isset($embed['mime_type'])) {
      return $embed['mime_type'];
    }

    if ($embed) {
      switch ($embed['type']) {
        case 'video':
          return 'video/oembed';
        case 'photo':
          return 'image/oembed';
        default:
          return 'text/oembed';
      }
    }
    else {
      // URIs for valid oEmbed responses may become invalid after they are saved
      // to the file_managed table. This might happen because the oEmbed
      // endpoint is down or the provider is misconfigured. The content may
      // have been deleted or become inaccessible. Some of these
      // situations are temporary, so the stream wrapper should try to return a
      // MIME type for URIs that are already saved as Drupal file entities.
      $type = db_select('file_managed', 'f')
        ->fields('f', array('type'))
        ->condition('uri', $uri)
        ->execute()
        ->fetchField();

      if (in_array($type, array('image', 'video', 'audio'))) {
        return $type .'/oembed';
      }
      else if ($type) {
        return 'text/oembed';
      }
    }

    return FALSE;
  }

  public function getExternalUrl() {
    return rawurldecode(substr($this->getUri(), 9));
  }

  function getOriginalThumbnailPath() {
    $uri = $this->getUri();
    $url = drupal_realpath($uri);

    $data = media_oembed_get_data($url);

    if (isset($data['thumbnail_url'])) {
      return $data['thumbnail_url'];
    }
    else {
      return FALSE;
    }
  }

  function getLocalThumbnailPath() {
    $uri = $this->getUri();
    $file = file_uri_to_object($uri);

    // The path to the file's local thumbnail is stored in metadata as it can't
    // be derived from the oEmbed URL.
    // Check if a local thumbnail is available and use it. Otherwise, create a
    // local copy of the original thumbnail.
    if (!isset($file->metadata['media_oembed_local_thumbnail_path']) || !file_exists($file->metadata['media_oembed_local_thumbnail_path'])) {
      // Attempt to get a URL to the file's original thumbnail.
      $url = $this->getOriginalThumbnailPath();

      if (isset($url)) {
        // Retrieve the original thumbnail.
        $result = drupal_http_request($url);

        // Using the redirect URL's basename might guarantee a path with an
        // appropriate file extension.
        if (isset($result->redirect_url)) {
          // If the redirect and original basenames are identical, do nothing.
          if (drupal_basename($result->redirect_url) != drupal_basename($url)) {
            $url .= '/'. drupal_basename($result->redirect_url);
          }
        }

        $parsed_url = parse_url($url);

        // Store local copies of images using hostname, path and filename of
        // source.
        $path = $parsed_url['host'];
        $path .= drupal_dirname($parsed_url['path']);

        if (substr($path, -1) != '/') {
          $path .= '/';
        }

        $filename = drupal_basename($parsed_url['path']);

        if (strpos($filename, '.') !== FALSE) {
          $filename = file_munge_filename($filename, 'jpg jpeg gif png', FALSE);
        }

        $path .= $filename;
        $local_uri = file_stream_wrapper_uri_normalize('public://media-oembed/'. $path);

        if (!file_exists($local_uri)) {
          /// Ensure filesystem has directories for new file.
          $dirname = drupal_dirname($local_uri);
          file_prepare_directory($dirname, FILE_CREATE_DIRECTORY | FILE_MODIFY_PERMISSIONS);

          // Save the file data to the local directory.
          file_unmanaged_save_data($result->data, $local_uri);
        }

        // Store the path to the local thumbnail in metadata.
        $file->metadata['media_oembed_local_thumbnail_path'] = $local_uri;

        // Save the file to update the metadata.
        file_save($file);
      }
    }

    if (isset($file->metadata['media_oembed_local_thumbnail_path'])) {
      $local_uri = $file->metadata['media_oembed_local_thumbnail_path'];

      return $local_uri;
    }
    else {
      return FALSE;
    }
  }
}
