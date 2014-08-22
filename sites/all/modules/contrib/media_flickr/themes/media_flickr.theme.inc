<?php
/**
 * @file
 * Theme functions for the Media: Flickr module.
 */

function theme_media_flickr_preview_style($variables) {
  $variables['uri'] = media_flickr_variable_get('preview_uri');
  return theme('media_flickr_embed', $variables);
}

function theme_media_flickr_styles($variables) {
  $style = $variables['style'];
  $variables['file'] = $variables['object'];
  $variables['uri'] = $variables['object']->uri;
  $variables['style_name'] = $style['name'];
  return theme('media_flickr_embed', $variables);
}

function media_flickr_preprocess_media_flickr_photoset(&$variables) {
  // Build the URL for display.
  $uri = $variables['uri'];
  $wrapper = file_stream_wrapper_get_instance_by_uri($uri);
  $parts = $wrapper->get_parameters();
  if (isset($parts['search'])) {
    $variables['search'] = $parts['search'];
  }
  else {
    $variables['user_id'] = drupal_encode_path($parts['u']);
    $variables['set_id'] = drupal_encode_path($parts['s']);
  }
  $variables['width'] = isset($variables['width']) ? $variables['width'] : media_flickr_variable_get('width');
  $variables['height'] = isset($variables['height']) ? $variables['height'] : media_flickr_variable_get('height');
  if (isset($variables['search'])) {
    $variables['flashvars'] = "offsite=true&lang=en-us&page_show_url=%2Fsearch%2Fshow%2F%3Fq%3D{$variables['search']}&page_show_back_url=%2Fsearch%2F%3Fq%3D{$variables['search']}&method=flickr.photos.search&api_params_str=&api_text={$variables['search']}&api_tag_mode=bool&api_media=all&api_sort=relevance&jump_to=&start_index=0";
  }
  elseif ($variables['set_id'] == 'photostream') {
    $variables['flashvars'] = "offsite=true&lang=en-us&page_show_url=%2Fphotos%2F{$variables['user_id']}%2Fshow%2F&page_show_back_url=%2Fphotos%2F{$variables['user_id']}%2F&user_id={$variables['user_id']}&jump_to=";
  }
  else {
    $variables['flashvars'] = "offsite=true&lang=en-us&page_show_url=%2Fphotos%2F{$variables['user_id']}%2Fsets%2F{$variables['set_id']}%2Fshow%2F&page_show_back_url=%2Fphotos%2F{$variables['user_id']}%2Fsets%2F{$variables['set_id']}%2F&set_id={$variables['set_id']}&jump_to=";
  }
}

function theme_media_flickr_embed($variables) {
  if(isset($variables['preset']) && isset($variables['object'])){
    //get preset information from the variables object
    $preset_name = $variables[(string)'preset'];
    $all_presets = $variables[(string)'presets'];

    $preset = array(
      'effects' => $all_presets[(string)'presets'][(string)$preset_name],
    );

    // Build the URL for display.
    $uri = $variables['uri'];
    $wrapper = file_stream_wrapper_get_instance_by_uri($uri);
    $parts = $wrapper->get_parameters();

    $width = $height = 0;

    foreach ($preset['effects'] as $effect) {
      switch ($effect['name']) {
        case 'resize':
          $width = isset($effect['settings']['width']) ? $effect['settings']['width'] : NULL;
          $height = isset($effect['settings']['height']) ? $effect['settings']['height'] : NULL;
          break;
      }
    }
    if (isset($variables['object']->override)) {
      $override = $variables['object']->override;
      if (isset($override['width'])) {
        $width = $override['width'];
      }
      if (isset($override['height'])) {
        $height = $override['height'];
      }
      if (isset($override['thumbnail'])) {
        unset($variables['photoset']);
        unset($variables['search']);
      }
    }

    $attributes = array();
    if ($width) {
      $attributes['width'] = $width;
    }
    if ($height) {
      $attributes['height'] = $height;
    }

    // If this is a photoset, then return the flash object for that.
    if (!isset($parts['p'])) {
      if (isset($variables['search']) || (isset($variables['photoset']) && $variables['photoset'])) {
        $attributes['uri'] = $uri;
        return theme('media_flickr_photoset', $attributes);
      }
      else {
        $parts['p'] = media_flickr_photoset_photo_id($uri);
      }
    }

    $output = theme('image', array(
      'path' => media_flickr_image_url($parts['p'], $width, $height),
      'alt' => $variables['alt'],
      'title' => $variables['title'],
      'attributes' => $attributes,
      'getsize' => FALSE,
    ));
    return $output;
  }
}

function theme_media_flickr_field_formatter_styles($variables) {
  $element = $variables['element'];
  $style = $variables['style'];
  $variables['file'] = $element['#item'];
  $variables['uri'] = $variables['file']['uri'];
  $variables['style_name'] = $style['name'];
  return theme('media_flickr_embed', $variables);
}
