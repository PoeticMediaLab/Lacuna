<?php

// Provide a landing page from within the LMS
function lacuna_lti_landing() {
  // Links and titles; Hate that these are hard-coded, but see no other way
  $links = array(
    'Materials' => '/materials',
    'Responses' => '/responses',
    'Sewing Kit' => '/sewing-kit',
    'Threads' => '/threads',
    'Profile' => '/user',
    'Dashboard' => '/visualization/dashboard',
  );

  $markup = "<div class='lacuna-lti-landing-page'>";
  foreach ($links as $title => $href) {
    $markup .= "<div class='lacuna-lti-landing-item'>";
    $markup .= "<a href='" . $href . "' target='_blank'>";
    $markup .= $title;
    $markup .= "</a></div>";
  }
  $markup .= "</div>";

  $content['raw_markup'] = array(
    '#type' => 'markup',
    '#markup' => $markup,
  );

  return $content;
}