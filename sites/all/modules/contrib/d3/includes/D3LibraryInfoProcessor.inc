<?php
/**
 * @file
 * D3 .info file processor class.
 */

/**
 * Parse additional information from library .info files.
 */
class D3LibraryInfoProcessor {
  /**
   * Current key being processed.
   *
   * @var array
   */
  private $key;

  /**
   * Specific keys to parse in the info file.
   *
   * e.x.
   * views[field] = value
   *
   * @var array
   */
	private $keys;

  /**
   * Current library to process.
   *
   * @var D3LibraryInfoController 
   */
  protected $library;

  public function __construct(D3LibraryInfoController $library) {
    $this->library = $library; 
  }

  /**
   * Set the current key being processed.
   */
  public function setKey($key, $depth = 0) {
    $this->key[$depth] = $key;
    foreach ($this->key as $index => $value) {
      if ($index == $depth) {
        $this->key[$index] = $key;
      }
      if ($index > $depth) {
        unset($this->key[$index]);
      }
    }
  }

  /**
   * Get the current key being processed.
   *
   * @return
   *   String separated by underscores.
   */
  public function getKey() {
    return join($this->key, '_');
  }

  /**
   * Set the info file keys to be processed.
   */
  public function setKeys($keys) {
    $this->keys = $keys;
  }

  /**
   * Main function to process the info file for the current keys.
   */
  public function process() {
    $library = &$this->library->value();
    foreach ($this->keys as $key) {
      $this->setKey($key);
      $this->processValues($library[$key]);
    }
  }

  /**
   * Sub function to start a recursive process.
   *
   * @param $values
   *   An array row that is being currently looped through.
   *
   * @see D3LibraryInfoController::process().
   */
  protected function processValues(&$values, $depth = 0) {
    // If this is a special string.
    if (!is_array($values) && (trim($values) != $this->trim($values))) {
      $values = $this->parseSpecialString($values);
      // Process meta keys once the special thing is parsed out.
      $this->processMeta($values);
    }
    elseif (is_string($values)) {
      // If this is a normal string, only check to see if it's a file name.
      $this->processFile($values);
    }
    elseif (is_array($values)) {
      // This is an array, process this recursively.
      foreach ($values as $index => &$data) {
        $this->setKey($index, $depth + 1);
        $this->processValues($data, $depth + 1);
      }
      // Process meta values.
      $this->processMeta($values);
    }
  }
  
  /**
   * Parse special strings into arrays.
   *
   * example: { key: value }
   * parses into: array('key' => 'value')
   *
   * @return
   *   Fully parsed array.
   */
  protected function parseSpecialString($str) {
    $ret = array();
    // Parse the line into array values separated by commas.
    $array = explode(',', $this->trim($str));
    foreach ($array as $string) {
      list($key, $values) = explode(':', $string);
      $ret[trim($key)] = trim($values, '\'\"');
    }
    return $ret;
  }

  /**
   * Load a file specified in an info file.
   *
   * If the library info file specifies a file name, then the information
   * for that library will reside in a file.
   * Load that file and see if it has the proper function.
   */
  protected function processFile(&$value) {
    $key = $this->getKey();
    $library = $this->library->value();
    // If they passed a filename for the field definition.
    $path = !empty($library['library path']) ? $library['library path'] : '';
    // TODO: find out if it's definitely a file and see if we can return an error.
    if (file_exists(DRUPAL_ROOT . '/' . $path . '/' . $value)) {
      require_once(DRUPAL_ROOT . '/' . $path . '/' . $value);
      $func = 'd3_library_' . str_replace('d3.', '', $library['machine name']) . '_' . $key;
      if (function_exists($func)) {
        $value = $func();
        $this->processMeta($value);
      }
    }
  }

  /**
   * Parse through magic meta keys.
   */
  protected function processMeta(&$values) {
    $info = array();
    foreach ($values as $key => $row) {
      if (is_array($row)) {
        // Recursive in case this is a file.
        $this->processMeta($values[$key]);
      }

      // Ensure the underscores are at the beginning.
      if (strpos($key, '__') === 0) {
        // Remove meta information.
        unset ($values[$key]);
        $count = 1;
        $key = str_replace('__', '', $key, $count);
        $info[$key] = is_string($row) ? trim($row) : $row;
      }
    }
    // Check to see if there were hidden values, otherwise this _info key
    // would show up everywhere blank.
    if (!empty($info)) {
      if (method_exists($this, 'postProcessMeta')) {
        $this->postProcessMeta($info);
      }
      $values['_info'] = $info;
    }
  }

  /**
   * Helper function to process info line with [] or {}.
   *
   * @see processValue().
   */
  protected function trim($str) {
    return trim($str, "\[\] \{\}\t\n\r\0\x0B");
  }

}
