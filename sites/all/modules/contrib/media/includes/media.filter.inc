<?php

/**
 * @file
 * Functions related to the WYSIWYG editor and the media input filter.
 *
 * @TODO: Rename this file?
 */

define('MEDIA_TOKEN_REGEX', '/\[\[.*?\]\]/s');
define('MEDIA_TOKEN_REGEX_ALT', '/%7B.*?%7D/s');

/**
 * Implements hook_wysiwyg_include_directory().
 */
function media_wysiwyg_include_directory($type) {
  switch ($type) {
    case 'plugins':
      return 'wysiwyg_plugins';
        break;
    }
}

/**
 * Implements hook_field_attach_insert().
 *
 * Track file usage for media files included in formatted text. Note that this
 * is heavy-handed, and should be replaced when Drupal's filter system is
 * context-aware.
 */
function media_field_attach_insert($entity_type, $entity) {
  _media_filter_add_file_usage_from_fields($entity_type, $entity);
}

/**
 * Implements hook_field_attach_update().
 *
 * @see media_field_attach_insert().
 */
function media_field_attach_update($entity_type, $entity) {
  _media_filter_add_file_usage_from_fields($entity_type, $entity);
}

/**
 * Add file usage from file references in an entity's text fields.
 */
function _media_filter_add_file_usage_from_fields($entity_type, $entity) {
  // Track the total usage for files from all fields combined.
  $entity_files = media_entity_field_count_files($entity_type, $entity);

  list($entity_id, $entity_vid, $entity_bundle) = entity_extract_ids($entity_type, $entity);

  // When an entity has revisions and then is saved again NOT as new version the
  // previous revision of the entity has be loaded to get the last known good
  // count of files. The saved data is compared against the last version
  // so that a correct file count can be created for that (the current) version
  // id. This code may assume some things about entities that are only true for
  // node objects. This should be reviewed.
  // @TODO this conditional can probably be condensed
  if (empty($entity->revision) && empty($entity->old_vid) && empty($entity->is_new) && ! empty($entity->original)) {
    $old_files = media_entity_field_count_files($entity_type, $entity->original);
    foreach ($old_files as $fid => $old_file_count) {
      // Were there more files on the node just prior to saving?
      if (empty($entity_files[$fid])) {
        $entity_files[$fid] = 0;
      }
      if ($old_file_count > $entity_files[$fid]) {
        $deprecate = $old_file_count - $entity_files[$fid];
        // Now deprecate this usage
        if ($file = file_load($fid)) {
          file_usage_delete($file, 'media', $entity_type, $entity_id, $deprecate);
        }
        // Usage is deleted, nothing more to do with this file
        unset($entity_files[$fid]);
      }
      // There are the same number of files, nothing to do
      elseif ($entity_files[$fid] ==  $old_file_count) {
        unset($entity_files[$fid]);
      }
      // There are more files now, adjust the difference for the greater number.
      // file_usage incrementing will happen below.
      else {
        // We just need to adjust what the file count will account for the new
        // images that have been added since the increment process below will
        // just add these additional ones in
        $entity_files[$fid] = $entity_files[$fid] - $old_file_count;
      }
    }
  }

  // Each entity revision counts for file usage. If versions are not enabled
  // the file_usage table will have no entries for this because of the delete
  // query above.
  foreach ($entity_files as $fid => $entity_count) {
    if ($file = file_load($fid)) {
      file_usage_add($file, 'media', $entity_type, $entity_id, $entity_count);
    }
  }

}

/**
 * Parse file references from an entity's text fields and return them as an array.
 */
function media_filter_parse_from_fields($entity_type, $entity) {
  $file_references = array();

  foreach (_media_filter_fields_with_text_filtering($entity_type, $entity) as $field_name) {
    if ($field_items = field_get_items($entity_type, $entity, $field_name)) {
      foreach ($field_items as $field_item) {
        preg_match_all(MEDIA_TOKEN_REGEX, $field_item['value'], $matches);
        foreach ($matches[0] as $tag) {
          $tag = str_replace(array('[[', ']]'), '', $tag);
          $tag_info = drupal_json_decode($tag);
          if (isset($tag_info['fid']) && $tag_info['type'] == 'media') {
            $file_references[] = $tag_info;
          }
        }

        preg_match_all(MEDIA_TOKEN_REGEX_ALT, $field_item['value'], $matches_alt);
        foreach ($matches_alt[0] as $tag) {
          $tag = urldecode($tag);
          $tag_info = drupal_json_decode($tag);
          if (isset($tag_info['fid']) && $tag_info['type'] == 'media') {
            $file_references[] = $tag_info;
          }
        }
      }
    }
  }

  return $file_references;
}

/**
 * Returns an array containing the names of all fields that perform text filtering.
 */
function _media_filter_fields_with_text_filtering($entity_type, $entity) {
  list($entity_id, $revision_id, $bundle) = entity_extract_ids($entity_type, $entity);
  $fields = field_info_instances($entity_type, $bundle);

  // Get all of the fields on this entity that allow text filtering.
  $fields_with_text_filtering = array();
  foreach ($fields as $field_name => $field) {
    if (!empty($field['settings']['text_processing'])) {
      $fields_with_text_filtering[] = $field_name;
    }
  }

  return $fields_with_text_filtering;
}

/**
 * Utility function to get the file count in this entity
 *
 * @param type $entity
 * @param type $entity_type
 * @return int
 */
function media_entity_field_count_files($entity_type, $entity) {
  $entity_files = array();
  foreach (media_filter_parse_from_fields($entity_type, $entity) as $file_reference) {
    if (empty($entity_files[$file_reference['fid']])) {
      $entity_files[$file_reference['fid']] = 1;
    }
    else {
      $entity_files[$file_reference['fid']]++;
    }
  }
  return $entity_files;
}

/**
 * Implements hook_entity_delete().
 */
function media_entity_delete($entity, $type) {
  list($entity_id) = entity_extract_ids($type, $entity);

  db_delete('file_usage')
    ->condition('module', 'media')
    ->condition('type', $type)
    ->condition('id', $entity_id)
    ->execute();
}

/**
 * Implements hook_field_attach_delete_revision().
 *
 * @param type $entity_type
 * @param type $entity
 */
function media_field_attach_delete_revision($entity_type, $entity) {
  list($entity_id) = entity_extract_ids($entity_type, $entity);
  $files = media_entity_field_count_files($entity_type, $entity);
  foreach ($files as $fid => $count) {
    if ($file = file_load($fid)) {
      file_usage_delete($file, 'media', $entity_type , $entity_id, $count);
    }
  }
}

/**
 * Filter callback for media markup filter.
 *
 * @TODO check for security probably pass text through filter_xss
 * @return unknown_type
 */
function media_filter($text) {
  $text = ' ' . $text . ' ';
  $text = preg_replace_callback(MEDIA_TOKEN_REGEX, 'media_token_to_markup', $text);
  return $text;
}

/**
 * Filter callback for media url filter.
 * @TODO: There are currently problems with this. For instance, if a file is
 * to be loaded from a remote location here, it will be recreated multiple
 * times, each time this filter is called. If we want to continue supporting
 * this feature, we would need to probably create a new stream or other way
 * to lookup a remote file w/ its local version. Probably best as a contributed
 * module because of this difficulty. ~ aaron.
 *
 * @deprecated
 */
function media_url_filter($text, $filter) {
  $text = ' ' . $text . ' ';

  // Need to attach the variables to the callback after the regex.
  $callback = _media_url_curry('_media_url_parse_full_links', 1);

  // Match absolute URLs.
  $text = preg_replace_callback("`(<p>|<li>|<br\s*/?>|[ \n\r\t\(])((http://|https://)([a-zA-Z0-9@:%_+*~#?&=.,/;-]*[a-zA-Z0-9@:%_+*~#&=/;-]))([.,?!]*?)(?=(</p>|</li>|<br\s*/?>|[ \n\r\t\)]))`i", $callback, $text);

  return $text;
}

/**
 * If one of our allowed providers knows what to do with the url,
 * then let it embed the video.
 *
 * @param int $filter
 *  The filter id.
 * @param array $match
 *  The matched text from our regex.
 *
 * @return string
 *  The replacement text for the url.
 *
 * @deprecated
 */
function _media_url_parse_full_links($match) {
  // Get just the URL.
  $match[2] = check_url(decode_entities($match[2]));
  try {
    $file = media_parse_to_file($match[2]);
  }
  catch (Exception $e) {
    // Ignore errors; pass the original text for other filters to deal with.
    return $match[0];
  }

  if ($file->fid) {
    $file = file_load($file->fid);

    // Generate a preview of the file
    // @TODO: Allow user to change the formatter in the filter settings.
    $preview = file_view_file($file, 'media_large');
    $preview['#show_names'] = TRUE;

    return drupal_render($preview);
  }

  // Nothing was parsed; return the original text.
  return $match[0];
}

/**
 * @deprecated
 */
function _media_url_curry($func, $arity) {
  return create_function('', "
    \$args = func_get_args();
    if(count(\$args) >= $arity)
        return call_user_func_array('$func', \$args);
    \$args = var_export(\$args, 1);
    return create_function('','
        \$a = func_get_args();
        \$z = ' . \$args . ';
        \$a = array_merge(\$z,\$a);
        return call_user_func_array(\'$func\', \$a);
    ');
  ");
}

/**
 * Parses the contents of a CSS declaration block and returns a keyed array of property names and values.
 *
 * @param $declarations
 *   One or more CSS declarations delimited by a semicolon. The same as a CSS
 *   declaration block (see http://www.w3.org/TR/CSS21/syndata.html#rule-sets),
 *   but without the opening and closing curly braces. Also the same as the
 *   value of an inline HTML style attribute.
 *
 * @return
 *   A keyed array. The keys are CSS property names, and the values are CSS
 *   property values.
 */
function media_parse_css_declarations($declarations) {
  $properties = array();
  foreach (array_map('trim', explode(";", $declarations)) as $declaration) {
    if ($declaration != '') {
      list($name, $value) = array_map('trim', explode(':', $declaration, 2));
      $properties[strtolower($name)] = $value;
    }
  }
  return $properties;
}

/**
 * Replace callback to convert a media file tag into HTML markup.
 *
 * @param string $match
 *   Takes a match of tag code
 * @param boolean $wysiwyg
 *   Set to TRUE if called from within the WYSIWYG text area editor.
 * @return
 *   The HTML markup representation of the tag, or an empty string on failure.
 *
 * @see media_get_file_without_label()
 * @see hook_media_token_to_markup_alter()
 */
function media_token_to_markup($match, $wysiwyg = FALSE) {
  $settings = array();
  $match = str_replace("[[", "", $match);
  $match = str_replace("]]", "", $match);
  $tag = $match[0];

  try {
    if (!is_string($tag)) {
      throw new Exception('Unable to find matching tag');
    }

    $tag_info = drupal_json_decode($tag);

    if (!isset($tag_info['fid'])) {
      throw new Exception('No file Id');
    }
    if (!isset($tag_info['view_mode'])) {
      // Should we log or throw an exception here instead?
      // Do we need to validate the view mode for fields API?
      $tag_info['view_mode'] = media_variable_get('wysiwyg_default_view_mode');
    }

    $file = file_load($tag_info['fid']);
    if (!$file) {
      throw new Exception('Could not load media object');
    }
    $tag_info['file'] = $file;

    // The class attributes is a string, but drupal requires it to be
    // an array, so we fix it here.
    if (!empty($tag_info['attributes']['class'])) {
      $tag_info['attributes']['class'] = explode(" ", $tag_info['attributes']['class']);
    }

    // Track the fid of this file in the {media_filter_usage} table.
    media_filter_track_usage($file->fid);

    $attributes = is_array($tag_info['attributes']) ? $tag_info['attributes'] : array();
    $attribute_whitelist = media_variable_get('wysiwyg_allowed_attributes');
    $settings['attributes'] = array_intersect_key($attributes, array_flip($attribute_whitelist));

    // Many media formatters will want to apply width and height independently
    // of the style attribute or the corresponding HTML attributes, so pull
    // these two out into top-level settings. Different WYSIWYG editors have
    // different behavior with respect to whether they store user-specified
    // dimensions in the HTML attributes or the style attribute, so check both.
    // Per http://www.w3.org/TR/html5/the-map-element.html#attr-dim-width, the
    // HTML attributes are merely hints: CSS takes precedence.
    if (isset($settings['attributes']['style'])) {
      $css_properties = media_parse_css_declarations($settings['attributes']['style']);
      foreach (array('width', 'height') as $dimension) {
        if (isset($css_properties[$dimension]) && substr($css_properties[$dimension], -2) == 'px') {
          $settings[$dimension] = substr($css_properties[$dimension], 0, -2);
        }
        elseif (isset($settings['attributes'][$dimension])) {
          $settings[$dimension] = $settings['attributes'][$dimension];
        }
      }
    }

    if ($wysiwyg) {
      $settings['wysiwyg'] = $wysiwyg;
    }
  }
  catch (Exception $e) {
    watchdog('media', 'Unable to render media from %tag. Error: %error', array('%tag' => $tag, '%error' => $e->getMessage()));
    return '';
  }

  $element = media_get_file_without_label($file, $tag_info['view_mode'], $settings);
  drupal_alter('media_token_to_markup', $element, $tag_info, $settings);
  return drupal_render($element);
}

/**
 * Builds a map of media tags in the element being rendered to their rendered HTML.
 *
 * The map is stored in JS, so we can transform them when the editor is being displayed.
 *
 * @param array $element
 */
function media_pre_render_text_format($element) {
  // filter_process_format() copies properties to the expanded 'value' child
  // element.
  if (!isset($element['format'])) {
    return $element;
  }

  $field = &$element['value'];
  $settings = array(
    'field' => $field['#id'],
  );

  $tagmap = _media_generate_tagMap($field['#value']);

  if (isset($tagmap)) {
    drupal_add_js(array('tagmap' => $tagmap), 'setting');
  }
  return $element;
}

/**
 * Generates an array of [inline tags] => <html> to be used in filter
 * replacement and to add the mapping to JS.
 * @param
 * The String containing text and html markup of textarea
 * @return
 * An associative array with tag code as key and html markup as the value.
 *
 * @see media_process_form()
 * @see media_token_to_markup()
 */
function _media_generate_tagMap($text) {
  // Making $tagmap static as this function is called many times and
  // adds duplicate markup for each tag code in Drupal.settings JS,
  // so in media_process_form it adds something like tagCode:<markup>,
  // <markup> and when we replace in attach see two duplicate images
  // for one tagCode. Making static would make function remember value
  // between function calls. Since media_process_form is multiple times
  // with same form, this function is also called multiple times.
  static $tagmap = array();
  preg_match_all("/\[\[.*?\]\]/s", $text, $matches, PREG_SET_ORDER);
  foreach ($matches as $match) {
    // We see if tagContent is already in $tagMap, if not we add it
    // to $tagmap.  If we return an empty array, we break embeddings of the same
    // media multiple times.
    if (empty($tagmap[$match[0]])) {
      // @TODO: Total HACK, but better than nothing.
      // We should find a better way of cleaning this up.
      if ($markup_for_media = media_token_to_markup($match, TRUE)) {
        $tagmap[$match[0]] = $markup_for_media;
      }
      else {
        $missing = file_create_url(drupal_get_path('module', 'media') . '/images/icons/default/image-x-generic.png');
        $tagmap[$match[0]] = '<div><img src="' . $missing . '" width="100px" height="100px"/></div>';
      }
    }
  }
  return $tagmap;
}

/**
 * Return a list of view modes allowed for a file embedded in the WYSIWYG.
 *
 * @param object $file
 *   A file entity.
 *
 * @return array
 *   An array of view modes that can be used on the file when embedded in the
 *   WYSIWYG.
 */
function media_get_wysiwyg_allowed_view_modes($file) {
  $enabled_view_modes = &drupal_static(__FUNCTION__, array());

  // @todo Add more caching for this.
  if (!isset($enabled_view_modes[$file->type])) {
    $enabled_view_modes[$file->type] = array();

    // Add the default view mode by default.
    $enabled_view_modes[$file->type]['default'] = array('label' => t('Default'), 'custom settings' => TRUE);

    $entity_info = entity_get_info('file');
    $view_mode_settings = field_view_mode_settings('file', $file->type);
    foreach ($entity_info['view modes'] as $view_mode => $view_mode_info) {
      // Do not show view modes that don't have their own settings and will
      // only fall back to the default view mode.
      if (empty($view_mode_settings[$view_mode]['custom_settings'])) {
        continue;
      }

      // Don't present the user with an option to choose a view mode in which
      // the file is hidden.
      $extra_fields = field_extra_fields_get_display('file', $file->type, $view_mode);
      if (empty($extra_fields['file']['visible'])) {
        continue;
      }

      // Add the view mode to the list of enabled view modes.
      $enabled_view_modes[$file->type][$view_mode] = $view_mode_info;
    }
  }

  $view_modes = $enabled_view_modes[$file->type];
  drupal_alter('media_wysiwyg_allowed_view_modes', $view_modes, $file);
  return $view_modes;
}

/**
 * Form callback used when embedding media.
 *
 * Allows the user to pick a format for their media file.
 * Can also have additional params depending on the media type.
 */
function media_format_form($form, $form_state, $file) {
  $form = array();
  $form['#media'] = $file;

  $view_modes = media_get_wysiwyg_allowed_view_modes($file);
  $formats = $options = array();
  foreach ($view_modes as $view_mode => $view_mode_info) {
    //@TODO: Display more verbose information about which formatter and what it does.
    $options[$view_mode] = $view_mode_info['label'];
    $element = media_get_file_without_label($file, $view_mode, array('wysiwyg' => TRUE));

    // Make a pretty name out of this.
    $formats[$view_mode] = drupal_render($element);
  }

  // Add the previews back into the form array so they can be altered.
  $form['#formats'] = &$formats;

  if (!count($formats)) {
    throw new Exception('Unable to continue, no available formats for displaying media.');
    return;
  }

  $default_view_mode = media_variable_get('wysiwyg_default_view_mode');
  if (!isset($formats[$default_view_mode])) {
    $default_view_mode = key($formats);
  }

  // Add the previews by reference so that they can easily be altered by
  // changing $form['#formats'].
  $settings['media']['formatFormFormats'] = &$formats;
  $form['#attached']['js'][] = array('data' => $settings, 'type' => 'setting');

  // Add the required libraries, JavaScript and CSS for the form.
  $form['#attached']['library'][] = array('media', 'media_base');
  $form['#attached']['library'][] = array('system', 'form');
  $form['#attached']['js'][] = drupal_get_path('module', 'media') . '/js/media.format_form.js';
  $form['#attached']['css'][] = drupal_get_path('module', 'media') . '/css/media-format-form.css';

  $form['heading'] = array(
    '#type' => 'markup',
    '#prefix' => '<h1 class="title">',
    '#suffix' => '</h1>',
    '#markup' => t('Embedding %filename', array('%filename' => $file->filename)),
  );

  $preview = media_get_thumbnail_preview($file);

  $form['preview'] = array(
    '#type' => 'markup',
    '#title' => check_plain(basename($file->uri)),
    '#markup' => drupal_render($preview),
  );

  // These will get passed on to WYSIWYG
  $form['options'] = array(
    '#type' => 'fieldset',
    '#title' => t('options'),
  );

  $form['options']['format'] = array(
    '#type' => 'select',
    '#title' => t('Current format is'),
    '#options' => $options,
    '#default_value' => $default_view_mode
  );

  // Similar to a form_alter, but we want this to run first so that media.types.inc
  // can add the fields specific to a given type (like alt tags on media).
  // If implemented as an alter, this might not happen, making other alters not
  // be able to work on those fields.
  // @TODO: We need to pass in existing values for those attributes.
  drupal_alter('media_format_form_prepare', $form, $form_state, $file);

  if (!element_children($form['options'])) {
    $form['options']['#attributes'] = array('style' => 'display:none');
  }

  return $form;
}

/**
 * Returns a drupal_render() array for just the file portion of a file entity.
 *
 * Optional custom settings can override how the file is displayed.
 */
function media_get_file_without_label($file, $view_mode, $settings = array()) {
  $file->override = $settings;

  // Legacy support for Styles module plugins that expect overridden HTML
  // attributes in $file->override rather than $file->override['attributes'].
  if (isset($settings['attributes'])) {
    $file->override += $settings['attributes'];
  }

  $element = file_view_file($file, $view_mode);

  // The formatter invoked by file_view_file() can use $file->override to
  // customize the returned render array to match the requested settings. To
  // support simple formatters that don't do this, set the element attributes to
  // what was requested, but not if the formatter applied its own logic for
  // element attributes.
  if (!isset($element['#attributes']) && isset($settings['attributes'])) {
    $element['#attributes'] = $settings['attributes'];

    // While this function may be called for any file type, images are a common
    // use-case. theme_image() and theme_image_style() require the 'alt'
    // attribute to be passed separately from the 'attributes' array (see
    // http://drupal.org/node/999338). Until that's fixed, implement this
    // special-case logic. Image formatters using other theme functions are
    // responsible for their own 'alt' attribute handling. See
    // theme_media_formatter_large_icon() for an example.
    if (isset($settings['attributes']['alt']) && !isset($element['#alt']) && isset($element['#theme']) && in_array($element['#theme'], array('image', 'image_style'))) {
      $element['#alt'] = $settings['attributes']['alt'];
    }
  }

  return $element;
}

/**
 * Clears caches that may be affected by the media filter.
 *
 * The media filter calls file_load(). This means that if a file object
 * is updated, the check_markup() and field caches could return stale content.
 * There are several possible approaches to deal with this:
 *  - Disable filter caching in media_filter_info(), this was found to cause a
 *    30% performance hit from profiling four node teasers, due to both the
 *    media filter itself, and other filters that can't be cached.
 *  - Clear the filter and field caches whenever any media node is updated, this
 *    would ensure cache coherency but would reduce the effectiveness of those
 *    caches on high traffic sites with lots of media content updates.
 *  - The approach taken here: Record the fid of all media objects that are
 *    referenced by the media filter. Only clear the filter and field caches
 *    when one of these is updated, as opposed to all media objects.
 *  - @todo: consider an EntityFieldQuery to limit cache clearing to only those
 *    entities that use a text format with the media filter, possibly checking
 *    the contents of those fields to further limit this to fields referencing
 *    the media object being updated. This would need to be implemented
 *    carefully to avoid scalability issues with large result sets, and may
 *    not be worth the effort.
 *
 * @param $fid
 *   Optional media fid being updated. If not given, the cache will be cleared
 *   as long as any file is referenced.
 */
function media_filter_invalidate_caches($fid = FALSE) {
  // If fid is passed, confirm that it has previously been referenced by the
  // media filter. If not, clear the cache if the {media_filter_usage} has any
  // valid records.
  if (($fid && db_query('SELECT fid FROM {media_filter_usage} WHERE fid = :fid', array(':fid' => $fid))->fetchField()) || (!$fid && media_filter_usage_has_records())) {
    // @todo: support entity cache, either via a hook, or using module_exists().
    cache_clear_all('*', 'cache_filter', TRUE);
    cache_clear_all('*', 'cache_field', TRUE);
  }
}

/**
 * Determines if the {media_filter_usage} table has any entries.
 */
function media_filter_usage_has_records() {
  return  (bool) db_query_range('SELECT 1 FROM {media_filter_usage} WHERE fid > :fid', 0, 1, array(':fid' => 0))->fetchField();
}

/**
 * Tracks usage of media fids by the media filter.
 *
 * @param $fid
 *   The media fid.
 */
function media_filter_track_usage($fid) {
  // This function only tracks when fids are found by the media filter.
  // It would be impractical to check when formatted text is edited to remove
  // references to fids, however by keeping a timestamp, we can implement
  // rudimentary garbage collection in hook_flush_caches().
  // However we only need to track that an fid has ever been referenced,
  // not every time, so avoid updating this table more than once per month,
  // per fid.
  $timestamp = db_query('SELECT timestamp FROM {media_filter_usage} WHERE fid = :fid', array(':fid' => $fid))->fetchField();
  if (!$timestamp || $timestamp <= REQUEST_TIME - 86400 * 30) {
    db_merge('media_filter_usage')->key(array('fid' => $fid))->fields(array('fid' => $fid, 'timestamp' => REQUEST_TIME))->execute();
  }
}
