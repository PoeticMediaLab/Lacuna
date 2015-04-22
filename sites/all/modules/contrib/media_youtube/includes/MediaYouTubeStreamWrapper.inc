<?php

/**
 *  @file
 *  Extends the MediaReadOnlyStreamWrapper class to handle YouTube videos.
 */

/**
 *  Create an instance like this:
 *  $youtube = new MediaYouTubeStreamWrapper('youtube://v/[video-code]');
 */
class MediaYouTubeStreamWrapper extends MediaReadOnlyStreamWrapper {
  protected $base_url = 'http://www.youtube.com/watch';

  static function getMimeType($uri, $mapping = NULL) {
    return 'video/youtube';
  }

  function getOriginalThumbnailPath() {
    $parts = $this->get_parameters();
    $v = check_plain($parts['v']);
    //  Attempt to pull a HD thumbnail from YouTube. If it exists pass it on
    //  otherwise pass on the smaller one.
    $thumbname = drupal_tempnam('temporary://', 'youtube');
    $response = drupal_http_request('http://img.youtube.com/vi/' . $v . '/maxresdefault.jpg');
    if (!isset($response->error)) {
      file_unmanaged_save_data($response->data, $thumbname, $replace = FILE_EXISTS_REPLACE);
    }
    if ((filesize($thumbname)) == 0) {
      return 'http://img.youtube.com/vi/' . $v . '/0.jpg';
    }
    else {
      return 'http://img.youtube.com/vi/' . $v . '/maxresdefault.jpg';
    }
  }

  function getLocalThumbnailPath() {
    $parts = $this->get_parameters();
    // There's no need to hide thumbnails, always use the public system rather
    // than file_default_scheme().
    $local_path = 'public://media-youtube/' . check_plain($parts['v']) . '.jpg';

    if (!file_exists($local_path)) {
      $dirname = drupal_dirname($local_path);
      file_prepare_directory($dirname, FILE_CREATE_DIRECTORY | FILE_MODIFY_PERMISSIONS);
      $response = drupal_http_request($this->getOriginalThumbnailPath());

      if (!isset($response->error)) {
        file_unmanaged_save_data($response->data, $local_path, TRUE);
      }
      else {
        @copy($this->getOriginalThumbnailPath(), $local_path);
      }
    }

    return $local_path;
  }
}
