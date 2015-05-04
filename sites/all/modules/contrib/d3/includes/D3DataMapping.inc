<?php
/**
 * @file
 * D3 Data mapping class.
 */

/**
 * Maps information from a
 */
class D3DataMapping {
  /**
   * Current library to map.
   *
   * @var D3LibraryInfoController
   */
  protected $library;

  public function __construct(D3LibraryInfoController $library) {
    $this->library = $library;
  }

  public function map($rows = array()) { }
}
