<?php
/**
 * @file
 * Preprocessing for d3 views handler.
 */

/**
 * Template helper for theme_views_view_d3.
 */
function template_preprocess_d3_views_view_d3(&$vars) {
  // Instance of the full view.
  $view    = $vars['view'];
  // Instance of d3_views_plugin_style_d3.
  $handler = $view->style_plugin;

  // Let the style handler map any values that the d3 library requires.
  $handler->map($vars['rows']);
  // Run any aggregation functions on the data in the $this->charts arary.
  $handler->aggregate();
  // Run additional hooks and convert arrays to numeric if selected.
  $handler->process();

  $vars['table'] = array();
  $header = array();

	if (!empty($handler->options['show_table'])) {
		$tr = array();
		foreach ($vars['rows'] as $id => $row) {
			$header = array();
			$td = array();
			foreach ($row as $name => $value) {
				$td[] = $value;
				$header[] = $name;
			}
			$tr[] = $td;
		}
		$vars['table'] = array(
			'#theme' => 'table',
			'#rows' => $tr,
			'#header' => $header,
	  );
	}
  $vars['visualization'] = $handler->draw();
}
