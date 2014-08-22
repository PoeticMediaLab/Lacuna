<?php

/**
 * @file
 * Dummy placeholder; moved to /includes.
 * This is here to avert a WSOD on update prior to 7001.
 */

/**
 *  Create an instance like this:
 *  $youtube = new ResourceYouTubeStreamWrapper('flickr://u/[user-code]/p/[photo-code]');
 */
class MediaFlickrStreamWrapper extends MediaReadOnlyStreamWrapper {
  protected $base_url = 'http://www.flickr.com/';

  function interpolateUrl() {
    if (isset($this->parameters['p'])) {
      return $this->base_url . 'photos/' . check_plain($this->parameters['u']) . '/' . check_plain($this->parameters['p']);
    }
  }

  function getTarget($f) {
    return FALSE;
  }

  static function getMimeType($uri, $mapping = NULL) {
    return 'image/jpeg';
  }
}
