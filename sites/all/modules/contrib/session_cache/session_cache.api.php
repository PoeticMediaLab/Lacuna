<?php

/**
 * @file
 * API documentation for Session Cache API module.
 *
 * Cookies and database session caches created through this API expire after a
 * UI-configurable number of hours or days. $_SESSIONs expire according to the
 * global configuration -- see the comments in
 * sites/default/files/default.settings.php.
 */

/**
 * Write data to the user session, whatever the storage mechanism may be.
 *
 * @param string $bin
 *   Unique id, eg a string prefixed by the module name.
 * @param mixed $data
 *   A number or string, an object, a multi-dimensional array etc.
 *   $bin is the identifier you choose for the data you want to store. To
 *   guarante uniqueness, you could prefix it with the name of the module that
 *   you use this API with.
 *   Use NULL to erase the bin; it may be auto-recreated and refilled at any
 *   time by calling the function again with a non-NULL data argument.
 */
function session_cache_set($bin, $data) {
  // See the following modules for examples:
  // o IP Geolocation Views & Maps.
  // o Views Global Filter.
}

/**
 * Read data from the user session, given its bin id.
 *
 * @param string $bin
 *   unique id eg a string prefixed by the module name
 *
 * @return mixed
 *   the cache data
 */
function session_cache_get($bin) {
  // See the following modules for examples:
  // o IP Geolocation Views & Maps.
  // o Views Global Filter.
}

/**
 * @addtogroup hooks
 * @{
 */

/**
 * Implement this set-hook to complete your own storage mechanism.
 *
 * @param int $storage_method
 *   the storage method
 * @param string $bin
 *   the name of the bin under which to store $data
 * @param mixed $data
 *   the data to store
 */
function hook_session_cache_set($storage_method, $bin, $data) {
  if ($storage_method != MYMODULE_SESSION_STORAGE) {
    return;
  }
  // Store $data in $bin, using your module's mechanism.
  // For an example see the submodule: session_cache_file.module
}

/**
 * Implement this get-hook to complete your own storage mechanism.
 *
 * @param int $storage_method
 *   the storage methd
 * @param string $bin
 *   the name of the bin to retrieve cached data from
 *
 * @return mixed
 *   the cached data
 */
function hook_session_cache_get($storage_method, $bin) {
  if ($storage_method != MYMODULE_SESSION_STORAGE) {
    return NULL;
  }
  // ... your retrieval mechanism goes here.
  $data = "your data based on $bin";
  return $data;
}

/**
 * Implement this hook to make your storage mechanism selectable in the UI.
 */
function hook_form_session_cache_admin_config_alter(&$form, &$form_state) {
  $form['session_cache_storage_method']['#options'][MYMODULE_SESSION_STORAGE]
    = t('my great storage method');
}

/**
 * @} End of "addtogroup hooks".
 */
