<?php

/**
 * D3 Views custom Library info processor.
 *
 * Should be overridden with a hook.
 */
class D3ViewsLibraryInfoProcessor extends D3LibraryInfoProcessor {
  public function process() {
    parent::process();
    $library = &$this->library->value();
    if (is_array($library['views']['fields'])) {
      // Set default for the data key.
      if (!empty($library['views']['fields']['rows']) && empty($library['views']['fields']['rows']['_info']['data_key'])) {
        $library['views']['fields']['_info']['data_key'] = 'rows';
      }
    }
  }

  public function postProcessMeta(&$values) {
    if (!empty($values['form_element'])) {
      $values['form_element'] = $this->hash($values['form_element']);
    }
    // TODO: Add functionality for the rows data type.
    if (!isset($values['cardinality'])) {
      $values['cardinality'] = 1;
    }
  }

  /**
   * Ensure there are hashes in form_element arrays.
   *
   * Could potentially go in parent class.
   */
  protected function hash($element) {
    foreach ($element as $key => $value) {
      if (strpos($key, '#') === FALSE) {
        $element['#' . $key] = $value; unset($element[$key]);
      }
    }
    return $element;
  }
}
