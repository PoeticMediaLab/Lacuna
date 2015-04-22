<?php

/**
 * @file
 * Theme and preprocess functions for Media: oEmbed.
 */

/**
 * Preprocess function for theme('media_oembed').
 */
function media_oembed_preprocess_media_oembed(&$variables) {
  $uri = $variables['uri'];

  // Make the file object available.
  $file_object = file_uri_to_object($uri);
  $variables['filename'] = check_plain($file_object->filename);

  $parameters = array();

  if ($variables['options']['height']) {
    $parameters['maxheight'] = $variables['options']['height'];
  }

  if ($variables['options']['width']) {
    $parameters['maxwidth'] = $variables['options']['width'];
  }

  // Get the oEmbed resource.
  $url = drupal_realpath($uri);
  $data = media_oembed_get_data($url, $parameters);

  // Response parameters
  foreach (array('type', 'version', 'title', 'author_name', 'author_url', 'provider_name', 'provider_url', 'cache_age', 'thumbnail_url', 'thumbnail_width', 'thumbnail_height') as $themevar) {
    $variables[$themevar] = isset($data[$themevar]) ? $data[$themevar] : NULL;
  }

  $content = '';

  switch ($variables['type']) {
    case 'photo':
      $variables['url'] = $data['url'];
      $variables['width'] = $data['width'];
      $variables['height'] = $data['height'];

      $image = array(
        'path' => $variables['url'],
        'width' => $variables['width'],
        'height' => $variables['height'],
      );

      if (!empty($file_object->alt)) {
        $image['alt'] = $file_object->alt;
      }
      else {
        $image['alt'] = $file_object->filename;
      }

      if (!empty($file_object->title)) {
        $image['title'] = $file_object->title;
      }
      else {
        $image['title'] = '';
      }

      $content = theme('image', $image);
      break;
    case 'video':
      $variables['html'] = $data['html'];
      $variables['width'] = $data['width'];
      $variables['height'] = $data['height'];

      $content = $variables['html'];
      break;
    case 'link':
      break;
    case 'rich':
      $variables['html'] = $data['html'];
      $variables['width'] = $data['width'];
      $variables['height'] = $data['height'];

      $content = $variables['html'];
      break;
  }

  $variables['content'] = $content;
}
