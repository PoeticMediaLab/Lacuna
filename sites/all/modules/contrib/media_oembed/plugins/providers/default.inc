<?php

$plugin = array(
  'title' => 'Remote endpoint',
  'description' => 'oEmbed provider for remote endpoints',
  'callback' => 'media_oembed_default_callback',
  'get child' => 'media_oembed_default_provider_get_child',
  'scheme callback' => 'media_oembed_default_provider_scheme',
  'consumer' => TRUE,
);

/**
 * Child plugins are oembed_provider objects that describe remote oEmbed endpoints.
 */
function media_oembed_default_provider_get_child($plugin, $parent, $child) {
  ctools_include('export');
  $provider = ctools_export_crud_load('media_oembed_provider', $child);
  $plugin['admin_title'] = $provider->admin_title;
  $plugin['admin_description'] = $provider->admin_description;
  $plugin['endpoint'] = $provider->endpoint;
  $plugin['scheme'] = $provider->scheme;
  $plugin['name'] = $parent . ':' . $provider->name;

  // Force the plugin to be processed again because it will persist in the static cache
  // of ctools_get_plugins(). Therefore, strip out the features of the child plugin
  // that make it look like the parent.
  unset($plugin['scheme callback']);
  unset($plugin['scheme map']);
  unset($plugin['weight']);

  $info = ctools_plugin_get_info('media_oembed', 'providers');
  $function = ctools_plugin_get_function($info, 'process');
  $function($plugin, $info);

  return $plugin;
}

/**
 *
 */
function media_oembed_default_provider_scheme() {
  // oEmbed provider definitions are remote web services.
  ctools_include('export');
  $providers = ctools_export_load_object('media_oembed_provider');
  $schemes = array();

  foreach ($providers as $provider) {
    if (empty($provider->disabled) && !empty($provider->scheme)) {
      $schemes['default:'. $provider->name] = $provider->scheme;
    }
  }

  return $schemes;
}

/**
 * Default provider callback makes HTTP requests using drupal_http_request().
 */
function media_oembed_default_callback($plugin, $url, $matches, $parameters) {
  $embed = FALSE;

  // Remote oEmbed endpoint request.
  $parameters['url'] = $url;
  $query = http_build_query($parameters, NULL, '&');
  $fetch_url = $plugin['endpoint'] . '?' . $query;

  //TODO: Add alternative ways of fetching the content - like http client?
  $response = drupal_http_request($fetch_url);
  if (!isset($response->error)) {
    // JSON or XML data might be returned, so be agnostic about decoding it.
    $embed = json_decode($response->data, TRUE);

    if (!is_array($embed)) {
      try {
        $xml = @new SimpleXMLElement($response->data);
        $embed = array();
        foreach ($xml as $key => $value) {
          $embed[$key] = (string) $value;
        }
      }
      catch (Exception $e) {
        watchdog('media_oembed', 'Could not parse response from %url.', array('%url' => $fetch_url), WATCHDOG_ERROR);
      }
    }

    if (empty($embed['version']) || empty($embed['type']) || intval($embed['version']) != 1) {
      $embed = FALSE;
    }

    if ($embed && !isset($embed['title'])) {
      $embed['title'] = '';
    }

    if (!$embed) {
      watchdog('media_oembed', 'Response from %url not a valid oEmbed response.', array('%url' => $fetch_url), WATCHDOG_ERROR);
    }
  }
  else {
    watchdog('media_oembed', 'Error fetching data from %url.', array('%url' => $fetch_url), WATCHDOG_ERROR);
  }

  return $embed;
}
