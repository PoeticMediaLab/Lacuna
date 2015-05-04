<?php
/**
 * @file
 * D3 library info controller class.
 */

/**
 * Base handler for library info files.
 */
class D3LibraryInfoController {
  /**
   * Mapping class.
   *
   * @var D3DataMapping
   */
  public $mapping;

  /**
   * Processor class.
   *
   * @var D3LibraryInfoProcessor
   */
  public $processor;

  /**
   * Library fully loaded.
   *
   * @var array.
   */
  protected $library;

  public function __construct($args = array()) {
    if (!empty($args['mapping']) && class_exists($args['mapping'])) {
      $this->mapping = new $args['mapping']($this);
    }
    if (!empty($args['processor']) && class_exists($args['processor'])) {
      $this->processor = new $args['processor']($this);
    }
  }

  /**
   * Set the current library for this handler.
   */
  public function setLibrary(&$library) {
    $this->library = &$library;
  }

  public function machineName() {
    return !empty($this->library['machine name']) ? $this->library['machine name'] : FALSE;
  }

  /**
   * Helper function to get child elements.
   */
  protected function children($elements) {
    foreach ($elements as $key => &$value) {
      if (is_array($value)) {
        $this->children($value);
      }
      if ($key == '_info') {
        unset($elements[$key]);
      }
    }
    return $elements;
  }

  /**
   * Return a reference to the loaded library.
   */
  public function &value() {
    return $this->library;
  }
}
