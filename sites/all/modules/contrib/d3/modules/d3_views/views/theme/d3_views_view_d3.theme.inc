<?php
/**
 * @file
 * Preprocessing for d3 views handler.
 */

/**
 * Template helper for theme_views_view_d3.
 */
function template_preprocess_d3_views_view_d3(&$vars) {
  $view    = $vars['view'];
  // Instance of d3_views_plugin_style_d3.
  $handler = $view->style_plugin;
  // All fields for this view.
  $fields  = &$view->field;

  // @see README.txt
  $row_labels = $handler->row_labels();
  $columns = $handler->columns();

  // Fields must be rendered in order as of Views 2.3, so we will pre-render
  // everything.
  // Taken from template_preprocess_views_view_table().
  $result = $handler->render_fields($vars['rows']);

  // Aggregate settings from $handler->options_form()
  $result = $handler->aggregate($result);

  // Rebuild view $rows.
  $vars['rows'] = array();

  // For the help table.
  $vars['header'] = array('');
  $vars['header_classes'] = array();

  foreach ($result as $row) {
    $data = array();
    // Loop through view labels because they'll need to be the first
    // element in each array.
    foreach ($row_labels as $field => $info) {
      $vars['header_classes'][$field] = '';
      if ($fields[$field]->options['element_default_classes']) {
        $vars['header_classes'][$field] .= "views-field views-field-" . drupal_clean_css_identifier($field);
      }
      if (isset($row[$field])) {
        $data[] = $row[$field];
      }
    }

    // The columns will follow.
    foreach ($columns as $field => $info) {
      $vars['header_classes'][$field] = '';
      if ($fields[$field]->options['element_default_classes']) {
        $vars['header_classes'][$field] .= "views-field views-field-" . drupal_clean_css_identifier($field);
      }
      // If this is not hidden in the field settings.
      if (empty($fields[$field]->options['exclude'])) {
        $label = check_plain(!empty($fields[$field]) ? $fields[$field]->label() : '');
        $data[] = ($info['display'] == 'display') ? $row[$field] : $label;
      }
    }

    $vars['rows'][] = $data;
  }

  $vars['visualization'] = $handler->draw($vars['rows']);
  foreach ($handler->columns() as $column => $info) {
    $vars['header'][] = $fields[$column]->label();
  }

  $vars['show_table'] = isset($handler->options['show_table']) ? $handler->options['show_table'] : FALSE;
}
