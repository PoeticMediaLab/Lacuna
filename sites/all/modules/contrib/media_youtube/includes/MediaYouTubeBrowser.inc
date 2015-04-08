<?php

/**
 * @file media_youtube/includes/MediaYouTubeBrowser.inc
 *
 * Definition of MediaYouTubeBrowser.
 */

/**
 * Media browser plugin for displaying a specific view and display.
 */
class MediaYouTubeBrowser extends MediaBrowserPlugin {
  /**
   * Implements MediaBrowserPluginInterface::access().
   */
  public function access($account = NULL) {
    return media_internet_access($account);
  }

  /**
   * Implements MediaBrowserPlugin::view().
   */
  public function view() {
    $build = array();
    $params = $this->params;
    $build['form'] = drupal_get_form('media_youtube_add', $params);

    return $build;
  }
}
