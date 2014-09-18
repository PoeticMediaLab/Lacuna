<?php

function _views_graphapi_style_build_graph_data(&$vars) {
  $view = $vars["view"];
  $rows = $vars["rows"];
  $options = $vars["options"];

  $view->style_plugin->render_fields($view->result);

  $base = $view->base_table;
  if ($base == 'system') {
    // We cannot use system_rebuild_module_data as this calls build_dependencies
    // which adds transitive dependencies which we don't want.
    // @see system_rebuild_module_data()
    $modules = _system_rebuild_module_data();
    ksort($modules);
    system_get_files_database($modules, 'module');

    // Weird dry alert : some modules declare dependency on a theme
    $themes = system_rebuild_theme_data();
    foreach ($themes as $theme => $info) {
      $themes[$theme]->info['dependencies'] = array();
      if (isset($theme->info['base theme'])) {
        $themes[$theme]->info['dependencies'][] = $theme->info['base theme'];
      }
    }
    $modules += $themes;

    $graph = graphapi_new_graph();
    foreach ($view->result as $id => $row) {
      //if ($id > 20) break;
      $from_id = $row->system_name;
      $extra = $modules[$from_id];

      if ($extra->status) {
        $color = 'green';
      }
      else {
        $color = 'yellow';
      }
      if (!isset($extra->info['hidden']) || !$extra->info['hidden']) {
        graphapi_set_node_data($graph, $from_id, array('background-color' => $color));
        foreach ($extra->info['dependencies'] as $to_id) {
          // We need to cleanup the dependency. @see drupal_parse_dependency()
          $parts = explode('(', $to_id, 2);
          $to_id = trim($parts[0]);
          if (!isset($modules[$to_id])) {
            graphapi_set_node_data($graph, $to_id, array('background-color' => 'red'));
          }
          graphapi_add_link($graph, $from_id, $to_id);
        }
      }
    }
  }
  else {
    $view = $vars['view'];
    $options = $vars['options'];

    if (isset($view->build_info['substitutions']) && is_array($view->build_info['substitutions'])) {
      _views_graphapi_ugly_hack_replace_args($vars['settings'], $view->build_info['substitutions']);
    }

    $engine = $options['engine'];
    $fields = $options[$engine]['fields'];

    // Check for the existance of all fields
    $defined_fields = array_keys($view->field);
    $diff = array_diff(array_keys($fields), $defined_fields);
    if (count($diff)) {
      drupal_set_message(t("Some fields are removed from %view. Please check it's definition.", array('%view' => $view->human_name)), 'error');
      $vars['graph'] = array();
      $vars['graph-config'] = $vars['settings'];
      return;
    }

    $mapping = array_flip($fields);
    unset($mapping[0]);

    // Make sure we have required values like label
    if (!isset($mapping['from:label'])) {
      $mapping['from:label'] = $mapping['from:id'];
    }
    $mapping_from_id = $mapping['from:id'];
    $mapping_from_label = $mapping['from:label'];
    if (isset($mapping['from:URI'])) {
      $mapping_from_uri = $mapping['from:URI'];
    }
    if (isset($mapping['from:content'])) {
      $mapping_from_content = $mapping['from:content'];
    }
    unset($mapping['from:id']);
    unset($mapping['from:URI']);
    unset($mapping['from:label']);
    unset($mapping['from:content']);

    if (!isset($mapping['to:label'])) {
      $mapping['to:label'] = $mapping['to:id'];
    }
    $mapping_to_id = $mapping['to:id'];
    $mapping_to_label = $mapping['to:label'];
    if (isset($mapping['to:URI'])) {
      $mapping_to_uri = $mapping['to:URI'];
    }
    if (isset($mapping['to:content'])) {
      $mapping_to_content = $mapping['to:content'];
    }
    unset($mapping['to:id']);
    unset($mapping['to:URI']);
    unset($mapping['to:label']);
    unset($mapping['to:content']);

    // Split of remaining into from + to + link fragments
    $split = array(
      'from' => array(),
      'link' => array(),
      'to' => array(),
    );
    foreach ($mapping as $key => $value) {
      list($left, $rest) = preg_split('/:/', $key, 2);
      if (isset($left) && isset($rest)) {
        $split[$left][$rest] = $value;
      }
    }
    $mapping = $split;

    $graph = graphapi_new_graph();

    foreach ($view->result as $count => $row) {
      $view->row_index = $count;
      // Node values
      $from_id = $view->style_plugin->rendered_fields[$count][$mapping_from_id];
      graphapi_add_node($graph, $from_id);

      $from_title = $view->style_plugin->rendered_fields[$count][$mapping_from_label];
      graphapi_set_node_title($graph, $from_id, $from_title);

      $data = array();
      foreach ($mapping['from'] as $key => $value) {
        $data[$key] = $view->style_plugin->rendered_fields[$count][$value];
      }
      if (!empty($data)) {
        graphapi_set_node_data($graph, $from_id, $data);
      }

      if (!empty($mapping_from_uri)) {
        $value = $view->style_plugin->rendered_fields[$count][$mapping_from_uri];
        graphapi_set_node_uri($graph, $from_id, $value);
      }
      if (!empty($mapping_from_content)) {
        $value = $view->style_plugin->rendered_fields[$count][$mapping_from_content];
        graphapi_set_node_content($graph, $from_id, $value);
      }

      $to_id = $view->style_plugin->rendered_fields[$count][$mapping_to_id];
      // Make sure only add a link when exists
      // NOTE: a value of 0 or '0' is OK so cannot use empty
      if (!is_null($to_id) && $to_id != '') {
        graphapi_add_node($graph, $to_id);

        $to_title = $view->style_plugin->rendered_fields[$count][$mapping_to_label];
        graphapi_set_node_title($graph, $to_id, $to_title);
        if (!empty($mapping_to_uri)) {
          $value = $view->style_plugin->rendered_fields[$count][$mapping_to_uri];
          graphapi_set_node_uri($graph, $to_id, $value);
        }
        if (!empty($mapping_to_content)) {
          $to_content = $view->style_plugin->rendered_fields[$count][$mapping_to_content];
          graphapi_set_node_content($graph, $to_id, $to_content);
        }
        $data = array();
        foreach ($mapping['to'] as $key => $value) {
          $data[$key] = $view->style_plugin->rendered_fields[$count][$value];
        }
        if (!empty($data)) {
          graphapi_set_node_data($graph, $to_id, $data);
        }
        $data = array();
        foreach ($mapping['link'] as $key => $value) {
          $data[$key] = $view->style_plugin->rendered_fields[$count][$value];
        }
        if (!empty($data)) {
          if (isset($data['title'])) {
            graphapi_set_link_title($graph, $from_id, $to_id, $data['title']);
            unset($data['title']);
          }
          if (!empty($data)) {
            graphapi_set_link_data($graph, $from_id, $to_id, $data);
          }
        }
        else {
          graphapi_add_link($graph, $from_id, $to_id);
        }
      }
    }
  }
  $vars['graph'] = $graph;
  $vars['graph-config'] = $vars['settings'];
}

/**
 * Replace all views placeholders.
 *
 * This is a quick hack http://drupal.org/node/1597928 but very useful
 *
 * @param string $value
 * @param type $substitutions
 */
function _views_graphapi_ugly_hack_replace_args(&$value, &$substitutions) {
  if (is_array($value)) {
    foreach ($value as $key => $dummy) {
      _views_graphapi_ugly_hack_replace_args($value[$key], $substitutions);
    }
  }
  else {
    $value = str_replace(array_keys($substitutions), $substitutions, $value);
  }
}
