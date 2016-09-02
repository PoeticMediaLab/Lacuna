<?php

/***
 * Provide a list of available resources to an LTI consumer.
 */
function lacuna_lti_resources() {
  ddl($_SESSION);
  $view = views_get_view('documents');
  $view->execute();
  print $view->render();
}