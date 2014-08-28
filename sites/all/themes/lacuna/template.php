<?php

function lacuna_preprocess_html(&$variables,$hook) {
  // $path = drupal_get_destination();
  // $path_cur = current_path();
  // $request_path = request_path();
  // $path_components_array = explode('/', $path_cur);
  // $path_comp_0 = !empty($path_components_array[0]) ? $path_components_array[0] : NULL;
  // $path_comp_1 = !empty($path_components_array[1]) ? $path_components_array[1] : NULL;
  // $path_comp_2 = !empty($path_components_array[2]) ? $path_components_array[2] : NULL;
  // $path_comp_3 = !empty($path_components_array[3]) ? $path_components_array[3] : NULL;
	drupal_add_css('http://fonts.googleapis.com/css?family=Noto+Sans|Open+Sans:400italic,700italic,400,700', array('group' => CSS_THEME));
	drupal_add_css('//netdna.bootstrapcdn.com/font-awesome/4.0.3/css/font-awesome.css', array('group' => CSS_THEME, 'type' => 'external'));
}
