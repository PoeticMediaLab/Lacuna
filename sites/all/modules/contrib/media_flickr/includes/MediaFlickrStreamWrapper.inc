<?php

/**
 *  @file
 *  Create a Flickr Stream Wrapper class for the Media/Resource module.
 */

/**
 *  Create an instance like this:
 *  $flickr = new MediaFlickrStreamWrapper('flickr://u/[user-code]/p/[photo-code]');
 */
class MediaFlickrStreamWrapper extends MediaReadOnlyStreamWrapper {
  protected $base_url = 'http://www.flickr.com/';
  protected $parameters = array('u' => NULL, 'p' => NULL, 's' => NULL, 'search' => NULL);

  function interpolateUrl() {
    if (isset($this->parameters['u']) && isset($this->parameters['p'])) {
      return $this->base_url . 'photos/' . check_plain($this->parameters['u']) . '/' . check_plain($this->parameters['p']);
    }
    if (isset($this->parameters['u']) && isset($this->parameters['s'])) {
      if ($this->parameters['s'] == 'photoset') {
        return $this->base_url . 'photos/' . check_plain($this->parameters['u']);
      }
      return $this->base_url . 'photos/' . check_plain($this->parameters['u']) . '/sets/' . check_plain($this->parameters['s']);
    }
    if (isset($this->parameters['search'])) {
      return $this->base_url . 'search/?q=' . check_plain($this->parameters['search']);
    }
  }

  function getTarget($f) {
    return FALSE;
  }

  /**
   * Get the url of the original image.
   */
  function getExternalUrl() {
    // Look for Photosets & searches.
    if (!isset($this->parameters['p'])) {
      if (isset($this->parameters['search']) || (isset($this->parameters['s']) && $this->parameters['s'])) {
        return media_flickr_image_url(media_flickr_photoset_photo_id($this->uri));
      }
      // Don't fall through.
      return;
    }

    // Return the direct image.
    $url =  media_flickr_image_url($this->parameters['p']);
    return $url;
  }
  function getOriginalThumbnailPath() {
    return $this->getExternalUrl();
  }

  function getLocalThumbnailPath() {
    $parts = $this->get_parameters();
    $local_path = str_replace('flickr://', 'public://media-flickr/', check_plain($this->uri)) . '.jpg';
    if (!file_exists($local_path)) {
      $dirname = drupal_dirname($local_path);
      file_prepare_directory($dirname, FILE_CREATE_DIRECTORY | FILE_MODIFY_PERMISSIONS);
      @copy($this->getOriginalThumbnailPath(), $local_path);
    }
    return $local_path;
  }
  static function getMimeType($uri, $mapping = NULL) {
    if (strpos($uri, '/s/') !== FALSE) {
      return 'video/flickr';
    }
    elseif (strpos($uri, '//search/') !== FALSE) {
      return 'video/flickr';
    }
    return 'image/jpeg';
  }
}
