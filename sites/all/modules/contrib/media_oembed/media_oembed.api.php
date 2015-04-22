<?php

/**
 * @file
 * Hooks provided by the Media: oEmbed module.
 */

/**
 * Alters an oEmbed request parameters and provider.
 *
 * @param array $parameters
 *   oEmbed request parameters.
 * @param object $provider
 *   oEmbed provider info.
 * @param string $url
 *   The original URL or embed code to parse.
 */
function hook_media_oembed_request_alter(&$parameters, &$provider, $url) {
  // Example provider only supports a max height of 500px.
  if ($provider['name'] == 'default:example') {
    if (isset($parameters['maxheight'])) {
      $parameters['maxheight'] = min($parameters['maxheight'], 500);
    }
  }
}

/**
 * Alters an oEmbed response.
 *
 * @param array $response
 *   oEmbed response data.
 */
function hook_media_oembed_response_alter(&$response) {
  // Example provider uses a proprietary property for storing the thumbnail URL.
  if ($response['provider'] == 'default:example' && empty($response['thumbnail_url']) && !empty($response['preview_image_url'])) {
    $response['thumbnail_url'] = $response['preview_image_url'];
  }
}
