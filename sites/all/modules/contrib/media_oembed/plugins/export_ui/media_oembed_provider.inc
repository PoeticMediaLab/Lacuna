<?php

$plugin = array(
  'schema' => 'media_oembed_provider',
  'access' => 'administer media oembed',
  'menu' => array(
    'menu prefix' => 'admin/config/media',
    'menu item' => 'media-oembed',
    'menu title' => 'oEmbed Providers',
    'menu description' => 'Manage oEmbed providers and settings.',
  ),
  'handler' => array(
    'class' => 'media_oembed_provider_ui',
    'parent' => 'ctools_export_ui',
  ),
  'title singular' => t('provider'),
  'title singular proper' => t('Provider'),
  'title plural' => t('providers'),
  'title plural proper' => t('Providers'),
);
