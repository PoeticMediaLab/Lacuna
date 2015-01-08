<?php

$plugin = array(
  'name' => 'commentcount',
  'label' => t('CommentCount'),
  'module' => 'annotator',
  'handler' => array(
    'class' => 'CommentCountAnnotatorPlugin',
  ),
);
