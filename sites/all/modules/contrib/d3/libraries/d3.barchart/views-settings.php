<?php
function d3_library_barchart_views_settings() {
  return array(
    'height' => array(
      '__form_element' => array(
        'title' => 'Height',
        'description' => 'The height of the entire visualization',
        'default_value' => 400,
      ),
    ),
    'width' => array(
      '__form_element' => array(
        'title' => 'Width',
        'description' => 'Width of the entire visualization.',
        'default_value' => 900,
      ),
    ),
  );
}
