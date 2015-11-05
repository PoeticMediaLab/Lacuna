<?php

$plugin = array(
  'name' => 'histogram',
  'label' => t('Histogram'),
  'module' => 'annotator',
  'handler' => array(
    'class' => 'HistogramAnnotatorPlugin',
  ),
);
