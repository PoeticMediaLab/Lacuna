<html>
  <head>
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
  </head>
  <body>
  <?php
  if ($view->name == 'stitchings') {
    // This value is same for all results, so just load the first one
    $wrapper = entity_metadata_wrapper('node', $view->result[0]->thread_reference_node_nid);
    print '<h2>' . $wrapper->title->value() . '</h2>';
    print '<h4>Created by ' . $wrapper->author->label() . ' on ';
    print format_date($wrapper->created->value(),
      $type = 'medium',
      $format = 'F jS, Y',
      $timezone = NULL,
      $langcode = NULL);
    print '<p>' . $wrapper->thread_description->value->value() . '</p>';
  }
  ?>
    <table>
    <?php print $header_row; ?>
    <tbody>