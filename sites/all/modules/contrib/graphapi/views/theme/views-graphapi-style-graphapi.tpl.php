<?php

// TODO Decide on json callbacks 
if (isset($view->override_path)) {       // inside live preview
  print htmlspecialchars($xml);
}
elseif (isset($options['using_views_api_mode']) && $options['using_views_api_mode']) {
  // We're in Views API mode.
  print $xml;
}
else {
  // TODO: this could be a json callback
  //drupal_add_http_header("Content-Type", "$content_type; charset=utf-8");
  print $xml;
  //exit;
}
