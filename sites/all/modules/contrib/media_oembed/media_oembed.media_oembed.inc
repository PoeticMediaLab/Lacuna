<?php

/**
 * @file
 * Media: oEmbed module integration for the Media:oEmbed module.
 */

/**
 * Implements hook_media_oembed_request_alter().
 */
function media_oembed_media_oembed_request_alter(&$parameters, &$provider, $url) {
  // Instagram doesn't support requesting the maxheight parameter.
  // @see http://instagram.com/developer/embedding/#oembed
  if ($provider['name'] == 'default:instagram') {
    unset($parameters['maxheight']);
  }
}

/**
 * Implement hook_media_oembed_response_alter().
 */
function media_oembed_media_oembed_response_alter(&$response) {
  // SoundCloud rich responses are audio players that should be re-cast as audio
  // files.
  if ($response['type'] == 'rich' && $response['provider'] == 'default:soundcloud') {
    $response['mime_type'] = 'audio/oembed';

    // SoundCloud responses also mistake the thumbnail url property name.
    foreach ($response as $key => $value) {
      if (strpos($key, '-')) {
        $new_key = strtr($key, array('-' => '_'));
        if (!isset($response[$new_key])) {
          $response[$new_key] = $value;
        }
      }
    }
  }

  // SlideShare sets uses the property to store the thumbnail URL.
  if ($response['provider'] == 'default:slideshare' && empty($response['thumbnail_url']) && !empty($response['thumbnail'])) {
    $response['thumbnail_url'] = $response['thumbnail'];
  }

  // If a photo provider doesn't include a thumbnail URL fall back to the full
  // image URL instead.
  if ($response['type'] == 'photo' && empty($response['thumbnail_url'])) {
    $response['thumbnail_url'] = $response['url'];
  }
}

/**
 * Process callback for oEmbed provider plugins.
 */
function media_oembed_provider_process(&$plugin, $info) {
  // For plugins which provide children based on the URL, a scheme callback
  // allows a map to be used to generate a regular expression for the whole
  // plugin and each child. Probably the plugin properties 'scheme callback' and
  // 'scheme' are mutually exclusive.
  $function = ctools_plugin_get_function($plugin, 'scheme callback');

  if ($function) {
    $schemes = array();
    $plugin['scheme map'] = $function();

    foreach ($plugin['scheme map'] as $id => $scheme) {
      if (is_array($scheme)) {
        $scheme = implode("\n", $scheme);
      }

      $schemes[] = $scheme;
      $plugin['scheme map'][$id] = _media_oembed_scheme_to_regex($scheme, $plugin['capture subpatterns']);
    }

    uasort($plugin['scheme map'], '_media_oembed_specificity_compare');
  }
  else if (is_array($plugin['scheme'])) {
    $schemes = $plugin['scheme'];
  }
  else {
    $schemes = array($plugin['scheme']);
  }

  if (!empty($schemes)) {
    $plugin['scheme'] = implode("\n", $schemes);
    $plugin['scheme'] = _media_oembed_scheme_to_regex($plugin['scheme'], $plugin['capture subpatterns']);

    if (empty($plugin['weight'])) {
      $plugin['weight'] = strlen($plugin['scheme']);
    }
  }
}

/**
 * Helper function that compares the length of match expressions.
 */
function _media_oembed_specificity_compare($a, $b) {
  return strlen($a) - strlen($b);
}

/**
 * Helper function that changes oEmbed schemes to regular expressions.
 */
function _media_oembed_scheme_to_regex($scheme, $capture_subpatterns = FALSE) {
  $patterns = array();
  $schemes = array_filter(preg_split("/(\r\n?|\n)/", $scheme));

  foreach ($schemes as $scheme) {
    $patterns[] = str_replace('\*', $capture_subpatterns ? '(.*)' : '.*', preg_quote($scheme, '#'));
  }

  return '#'. implode('|', $patterns) .'#i';
}
