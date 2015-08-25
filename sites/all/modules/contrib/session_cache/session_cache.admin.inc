<?php

/**
 * @file
 * session_cache.admin.inc
 */

/**
 * Menu callback for admin settings.
 *
 * Contrib modules can add more options by implementing hook_form_alter().
 */
function session_cache_admin_config() {
  $form['session_cache_storage_method'] = array(
    '#type' => 'radios',
    '#title' => t('Where should user session data be stored?'),
    '#default_value' => variable_get('session_cache_storage_method', SESSION_CACHE_STORAGE_SESSION),
    '#options' => array(
      SESSION_CACHE_STORAGE_COOKIE  => t("on the user's computer, in a cookie"),
      SESSION_CACHE_STORAGE_DB_CORE => t("on the server, on core's cache database"),
      SESSION_CACHE_STORAGE_SESSION => t('on the server, in $_SESSION memory'),
    ),
    '#description' => t('When using Varnish or similar page caching engine for anonymous users, do not use $_SESSION and have a page exclusion strategy in place.'),
  );

  $options = array(
    SESSION_CACHE_COOKIE_FOR_SID => t('via their cookie'),
    SESSION_CACHE_UID_FOR_SID => t('via their login id, via cookie for anonymous users (works cross-browser for authenticated users)'),
    SESSION_CACHE_IP_ADDRESS_FOR_SID => t('via their IP address')
  );
  $form['session_cache_sid_source'] = array(
    '#type' => 'radios',
    '#title' => t('Method for identifying the user in database and file-based storage methods'),
    '#options' => $options,
    '#default_value' => variable_get('session_cache_sid_source', SESSION_CACHE_COOKIE_FOR_SID),
    '#description' => t('None of the above apply to the $_SESSION and cookie storage mechanisms.'),
  );

  $expire_period = (float) variable_get('session_cache_expire_period');
  if ($expire_period <= 0.0) {
    $expire_period = SESSION_CACHE_DEFAULT_EXPIRATION_DAYS;
  }
  $form['session_cache_expire_period'] = array(
    '#type' => 'textfield',
    '#size' => 4,
    '#title' => t('Expiration time for the database cache and cookies created via this module'),
    '#field_suffix' => t('days'),
    '#default_value' => $expire_period,
    '#description' => t('You may use decimals, eg 0.25 equates to 6 hours.<br/>$_SESSION expiration is set via the server configuration. See the <em>sites/default/settings.php</em> file for details.'),
  );

  return system_settings_form($form);
}
