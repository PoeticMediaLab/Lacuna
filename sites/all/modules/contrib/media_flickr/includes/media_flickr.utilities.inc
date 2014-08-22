<?php

/**
 *  @file
 *  Utility functions for Media: Flickr.
 */

/**
 *  Based on the Photo ID of a Flickr image, this will return the URL to the
 *  image itself.
 *  @param $photo_id
 *    The Flickr photo code.
 *  @param $width
 *  @param $height
 *    We use this to guess the actual size provided by Flickr.
 *  @param $cached
 *    If TRUE, then we'll cache the remote URL if the attempt to save the file
 *    locally fails.
 */
function _media_flickr_photo_url($photo_id, $width = 0, $height = 0, $cached = TRUE) {
  if ($photo_id) {
    $size = _media_flickr_guess_size($width, $height);
    return _media_flickr_photo_url_from_size($photo_id, $size);
  }
}

/**
 *  This returns a cached photo stream from the Flickr farm servers.
 */
function _media_flickr_photo_remote_url($photo_id, $size) {
  $getsize = _media_flickr_sets_request('flickr.photos.getSizes', array('photo_id' => $photo_id));

  if ($getsize && ($getsize['@attributes']['stat'] != 'fail')) {
    // For small images, there may not be the sizes 0..4 that
    // media_flickr_guess_size assumes, so:
    $size = min($size, count($getsize['sizes']['size'])-1);

    return $getsize['sizes']['size'][$size]['@attributes']['source'];
  }
}

/**
 *  This is a wrapper for emfield_request_xml that includes flickr's api key.
 *  @param string $method
 *  @param array $args
 *  @param boolean $refresh
 *    Optional; if TRUE, then we'll force a new load of the XML. Otherwise,
 *    a cached version will be retrieved if possible.
 *  @return object
 *    A fully populated SimpleXML object.
 */
function _media_flickr_sets_request($method, $args = array(), $refresh = FALSE) {
  // Display an error if we don't have an API key yet.
  if (!_media_flickr_error_check()) {
    return array();
  }

  $args['api_key'] = trim(media_flickr_variable_get('api_key'));
  if ($secret = trim(media_flickr_variable_get('api_secret'))) {
    $args['secret'] = md5($secret);
  }
  $args['method'] = $method;

  $xml = media_retrieve_xml(MEDIA_FLICKR_RESTPOINT . '?' . drupal_http_build_query($args), user_access('administer site configuration'), $refresh);
  return $xml;
}

/**
 *  This will log an error if we don't have a key yet.
 *  In addition, if the user is an admin, we'll display an error.
 */
function _media_flickr_error_check() {
  static $checked;
  if (is_null($checked)) {
    if (media_flickr_variable_get('api_key') == '') {
      $error = 'You do not yet have a Flickr API key set. You will need to !apply and enter your key at the !settings before Flickr images may be displayed.';
      $arguments = array('!apply' => l(t('apply for a Flickr API key'), MEDIA_FLICKR_API_APPLICATION_URL), '!settings' => l(t('Flickr administration page'), 'admin/config/media/media_flickr'));
      if (user_access('administer site configuration')) {
        drupal_set_message(t($error, $arguments), 'error');
      }
      watchdog('media_flickr', $error, $arguments);
      $checked = FALSE;
    }
    else {
      $checked = TRUE;
    }
  }
  return $checked;
}

/**
 *  This will return the appropriate array key for the image size we wish.
 */
function _media_flickr_guess_size($width = 0, $height = 0) {
  $max = max($width, $height);

  if ($max) {
    foreach (array('0' => 75, '1' => 100, '2' => 240, '3' => 500, '4' => 1024) as $size => $value) {
      if ($max <= $value) {
        return $size;
      }
    }
  }

  // If we don't have width or height set, then get the original size.
  return '5';
}

function _media_flickr_photo_url_from_size($photo_id, $size = 5) {
  // Check to make sure we have a valid photo code.
  if (is_numeric($photo_id)) {
    $filepath = _media_flickr_photo_remote_url($photo_id, $size);
    // URLize that path...
    $filepath = url($filepath, array('absolute' => TRUE));
    return $filepath;
  }
}

function _media_flickr_photoset_photo_id($uri, $refresh = FALSE) {
  $wrapper = file_stream_wrapper_get_instance_by_uri($uri);
  $parts = $wrapper->get_parameters();
  if (isset($parts['search'])) {
    $photos = _media_flickr_sets_request('flickr.photos.search', array('text' => $parts['search'], 'per_page' => 1, 'media' => 'photos'));
    if ($photos && ($photos['@attributes']['stat'] != 'fail')) {
      return $photos['photos']['photo']['@attributes']['id'];
    }
  }
  elseif (isset($parts['s'])) {
    if ($parts['s'] == 'photostream') {
      if (isset($parts['u'])) {
        $photos = _media_flickr_sets_request('flickr.people.getPublicPhotos', array('user_id' => $parts['u'], 'per_page' => 1, 'media' => 'photos'));
        if ($photos && ($photos['@attributes']['stat'] != 'fail')) {
          return $photos['photos']['photo']['@attributes']['id'];
        }
      }
    }
    else {
      $photos = _media_flickr_sets_request('flickr.photosets.getPhotos', array('photoset_id' => $parts['s'], 'per_page' => 1, 'media' => 'photos'));
      if ($photos && ($photos['@attributes']['stat'] != 'fail')) {
        return $photos['photoset']['photo']['@attributes']['id'];
      }
    }
  }
}

function _media_flickr_photoset_image_url($uri, $width = 0, $height = 0, $refresh = FALSE) {
  $photo_id = media_flickr_photoset_photo_id($uri, $refresh);
  return media_flickr_image_url($photo_id, $width, $height, $refresh);
}

function _media_flickr_original_url($uri, $refresh = FALSE) {
  $wrapper = file_stream_wrapper_get_instance_by_uri($uri);
  return $wrapper->interpolateUrl();
}

function _media_flickr_photo_exists($photo_id) {
  $info = _media_flickr_sets_request('flickr.photos.getInfo', array('photo_id' => $photo_id));

  if ($info && ($info['@attributes']['stat'] != 'fail')) {
    return TRUE;
  }
}

function _media_flickr_photoset_exists($photoset_id) {
  $info = _media_flickr_sets_request('flickr.photosets.getInfo', array('photoset_id' => $photoset_id));
  if ($info && ($info['@attributes']['stat'] != 'fail')) {
    return TRUE;
  }
}

function _media_flickr_get_user_id($user_id) {
  $info = _media_flickr_sets_request('flickr.people.getInfo', array('user_id' => $user_id));

  if ($info && ($info['@attributes']['stat'] != 'fail')) {
    return $user_id;
  }
  elseif ($info['err']['@attributes']['code'] == 1) {
    // See if we were passed a username instead.
    $info = _media_flickr_sets_request('flickr.people.findByUsername', array('username' => $user_id));
    if ($info && $info['@attributes']['stat'] != 'fail') {
      return $info['user']['@attributes']['id'];
    }
  }
}

function _media_flickr_build_uri($parts) {
  if (isset($parts['u'])) {
     $user_id = _media_flickr_get_user_id($parts['u']);
     $parts['u'] = isset($user_id) ? $user_id : $parts['u'];
  }
  if (isset($parts['u'])) {
    if (isset($parts['p'])) {
      $uri = file_stream_wrapper_uri_normalize('flickr://u/' . $parts['u'] . "/p/" . $parts['p']);
      if (_media_flickr_photo_exists($parts['p'])) {
        return $uri;
      }
    }
    elseif (isset($parts['s'])) {
      $uri = file_stream_wrapper_uri_normalize('flickr://u/' . $parts['u'] . "/s/" . $parts['s']);
      if (($parts['s'] == 'photostream') || _media_flickr_photoset_exists($parts['s'])) {
        return $uri;
      }
    }
  }
  if (isset($parts['search'])) {
    return file_stream_wrapper_uri_normalize('flickr://search/' . $parts['search']);
  }
}

function _media_flickr_media_parse($url, $options = array()) {
  // The following are single images.
  $patterns = array(
    '@flickr\.com/photos/([0-9A-Za-z\@\&\$_-]+)/([0-9]+)/in/photostream@i',
    '@flickr\.com/photos/([0-9A-Za-z\@\&\$_-]+)/([0-9]+)/in/set-([0-9]+)@i',
    '@flickr\.com/photos/([0-9A-Za-z\@\&\$_-]+)/([0-9]+)/?$@i',
  );
  foreach ($patterns as $pattern) {
    preg_match($pattern, $url, $matches);
    if (isset($matches[1]) && isset($matches[2])) {
      return _media_flickr_build_uri(array('u' => $matches[1], 'p' => $matches[2]));
    }
  }
  // Next we look for photosets.
  $patterns = array(
    '@flickr\.com/photos/([0-9A-Za-z\@\&\$_-]+)/sets/([0-9]+)@i',
  );
  foreach ($patterns as $pattern) {
    preg_match($pattern, $url, $matches);
    if (isset($matches[1]) && isset($matches[2])) {
      return _media_flickr_build_uri(array('u' => $matches[1], 's' => $matches[2]));
    }
  }
  // Then we look for photostreams of the entire user.
  $patterns = array(
    '@flickr\.com/photos/([0-9A-Za-z\@\&\$_-]+)/?$@i',
    '@flickr\.com/photos/([0-9A-Za-z\@\&\$_-]+)/show/?$@i',
  );
  foreach ($patterns as $pattern) {
    preg_match($pattern, $url, $matches);
    if (isset($matches[1])) {
      return _media_flickr_build_uri(array('u' => $matches[1], 's' => 'photostream'));
    }
  }
  // Finally we look for searches.
  $patterns = array(
    '@flickr\.com/search/?\?q=([^& ]+)@i',
    '@flickr\.com/search/show/?\?q=([^& ]+)@i'
  );
  foreach ($patterns as $pattern) {
    preg_match($pattern, $url, $matches);
    if (isset($matches[1])) {
      return _media_flickr_build_uri(array('search' => $matches[1]));
    }
  }
}
