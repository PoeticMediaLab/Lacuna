<?php

/**
 * @file
 * Admin page callbacks for the Media: oEmbed module.
 */

/**
 * Form builder; The Media: oEmbed configuration form.
 *
 * @ingroup forms
 * @see system_settings_form()
 */
function media_oembed_settings() {
  $period = drupal_map_assoc(array(3600, 10800, 21600, 32400, 43200, 86400, 172800, 259200, 604800, 1209600, 2419200, 4838400, 9676800), 'format_interval');
  $period[CACHE_PERMANENT] = t('Indefinite');

  $form['oembed_cache_lifetime'] = array(
    '#type' => 'select',
    '#title' => t('Minimum oEmbed cache lifetime'),
    '#options' => $period,
    '#default_value' => variable_get('media_oembed_cache_lifetime', 3600),
    '#description' => t('Cached oEmbed output will not be re-requested until at least this much time has elapsed.'),
  );

  return system_settings_form($form);
}
