<?php

/**
 * @file
 * global_filter.linkswidget.inc
 */

/**
 * Create links widget.
 */
function global_filter_create_links_widget($filter_key, $options, &$form, &$form_state) {
  $post_it = global_filter_get_module_parameter('links_widget_via_post', TRUE);
  if ($post_it) {
    drupal_add_js(array('links_widget_via_post' => TRUE), 'setting');
  }
  $no_language = new stdClass();
  $no_language->language = FALSE;

  $name = $form_state['global_filters'][$filter_key]['name'];
  $selected_value = global_filter_get_session_value($name);
  $links = '';

  foreach ($options as $value => $link_text) {
    $active = is_array($selected_value) ? in_array($value, $selected_value) : $value == $selected_value;
    $link_options = array(
      'attributes' => array('title' => $link_text),
      // Hack to avoid every link being classed as 'active'.
      'language' => $active ? NULL : $no_language,
    );
    if (!isset($value)) {
      $value = '';
    }
    if ($post_it) {
      $link_options['attributes']['id'] = "$name:$value";
      if ($active) {
        $link_options['attributes']['class'] = drupal_html_class('active');
      }
    }
    else {
      $link_options['query'] = array($name => $value);
    }
    $link = $post_it ? '<a href="" ' . drupal_attributes($link_options['attributes']) . ">$link_text</a>" : l($link_text, $_GET['q'], $link_options);
    $links .= ($active ? '<li class="active">' : '<li>') . $link . '</li>';
  }
  $form[$name]['#markup'] = '<ul class="global-filter-links ' . drupal_html_class(GLOBAL_FILTER_FILTER_KEY_PREFIX . "$filter_key-$name") . '">' . $links . '</ul>';
  $form[$name]['#suffix'] = '<div class="suffix">' . t('Click link to filter') . '</div>';
}
