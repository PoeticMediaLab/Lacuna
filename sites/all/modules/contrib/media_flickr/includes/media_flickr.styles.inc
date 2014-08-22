<?php
// $Id:$

/**
 * @file media_flickr/includes/media_flickr.styles.inc
 * Styles definitions for Media: Flickr.
 */

/**
 * Implementation of Styles module hook_styles_default_containers().
 */
function media_flickr_styles_default_containers() {
 // We append Flickr to the file containers.
 return array(
   'file' => array(
     'containers' => array(
       'media_flickr' => array(
         'class' => 'MediaFlickrStyles',
         'name' => 'media_flickr',
         'label' => t('Flickr'),
         'preview' => 'media_flickr_preview_style',
       ),
     ),
   ),
 );
}

/**
 * Implementation of Styles module hook_styles_default_presets().
 */
function media_flickr_styles_default_presets() {
  $presets = array(
    'file' => array(
      'containers' => array(
        'media_flickr' => array(
          'default preset' => 'unlinked_thumbnail',
          'styles' => array(
            'original' => array(
              'default preset' => 'flickr_image',
            ),
            'thumbnail' => array(
              'default preset' => 'thumb_flickr_image',
            ),
            'square_thumbnail' => array(
              'default preset' => 'linked_square_thumbnail',
            ),
            'medium' => array(
              'default preset' => 'medium_flickr_image',
            ),
            'large' => array(
              'default preset' => 'large_flickr_image',
            ),
          ),
          'presets' => array(
            'flickr_image' => array(
              array(
                'name' => 'flickr_image',
                'settings' => array(),
              ),
            ),
            'thumb_flickr_image' => array(
              array(
                'name' => 'resize',
                'settings' => array(
                    'width' => 100,
                ),
              ),
              array(
                'name' => 'flickr_image',
                'settings' => array(),
              ),
            ),
            'medium_flickr_image' => array(
              array(
                'name' => 'resize',
                'settings' => array(
                  'width' => 220,
                ),
              ),
              array(
                'name' => 'flickr_image',
                'settings' => array(),
              ),
            ),
            'large_flickr_image' => array(
              array(
                'name' => 'resize',
                'settings' => array(
                  'width' => 640,
                ),
              ),
              array(
                'name' => 'flickr_image',
                'settings' => array(),
              ),
            ),
          ),
        ),
      ),
    ),
  );
  // Add optional photoset slideshow dipslay.
  foreach ($presets['file']['containers']['media_flickr']['presets'] as $preset_name => $preset) {
    $presets['file']['containers']['media_flickr']['presets'][$preset_name . '_photoset'] = $presets['file']['containers']['media_flickr']['presets'][$preset_name];
    array_pop($presets['file']['containers']['media_flickr']['presets'][$preset_name . '_photoset']);
    $presets['file']['containers']['media_flickr']['presets'][$preset_name . '_photoset'][] = array(
      'name' => 'flickr_photoset',
      'settings' => array(),
    );
  }
  // Allow any image style to be applied to the thumbnail.
  foreach (image_styles() as $style_name => $image_style) {
    $presets['file']['containers']['media_flickr']['presets']['linked_' . $style_name] = array(
      array(
        'name' => 'linkToMedia',
        'settings' => array(),
      ),
      array(
        'name' => 'imageStyle',
        'settings' => array(
          'image_style' => $style_name,
        ),
      ),
      array(
        'name' => 'thumbnail',
        'settings' => array(),
      ),
    );
    $presets['file']['containers']['media_flickr']['presets']['unlinked_' . $style_name] = $presets['file']['containers']['media_flickr']['presets']['linked_' . $style_name];
    array_shift($presets['file']['containers']['media_flickr']['presets']['unlinked_' . $style_name]);
      foreach ($image_style['effects'] as $effect) {
      if (in_array($effect['name'], array('image_scale', 'image_scale_and_crop', 'image_resize', 'image_crop'))) {
        $presets['file']['containers']['media_flickr']['presets']['photoset_' . $style_name] = array(
          array(
            'name' => 'resize',
            'settings' => $effect['data'],
          ),
          array(
            'name' => 'flickr_photoset',
            'settings' => array(),
          ),
        );
      }
    }
  }
  return $presets;
}
