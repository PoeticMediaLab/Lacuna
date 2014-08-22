<?php

/**
 * @file
 * Define MediaInternetFlickrHandler class.
 */

class MediaInternetFlickrHandler extends MediaInternetBaseHandler {
  public function parse($embedCode) {
    return media_flickr_media_parse($embedCode);
  }

  public function claim($embedCode) {
    if ($this->parse($embedCode)) {
      return TRUE;
    }
  }

  public function save() {
    $file = $this->getFileObject();
    // If a user enters a duplicate Flickr URL, the object will be saved again.
    // Set the timestamp to the current time, so that the media item shows up
    // at the top of the media library, where they would expect to see it.
    $file->timestamp = REQUEST_TIME;
    file_save($file);
    return $file;
  }

  public function getFileObject() {
    $uri = $this->parse($this->embedCode);
    return file_uri_to_object($uri, TRUE);
  }
}
