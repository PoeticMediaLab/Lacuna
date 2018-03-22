<?php

/*
* Enables annotations on PDF documents.
*/

class PDFAnnotatorPlugin extends AnnotatorPlugin {
  public function setup() {  
    $node = menu_get_object();
    $is_pdf = FALSE;
    if (isset($node->field_doc_type)) {
      $is_pdf = $node->field_doc_type[$node->language][0]['value'];
    }
    if ( $is_pdf ) {
      drupal_add_js(drupal_get_path('module', 'annotator') . '/js/annotator_pdf.js');
      drupal_add_js(drupal_get_path('module', 'annotator') . '/js/pdf.js');
    }
  }
}
