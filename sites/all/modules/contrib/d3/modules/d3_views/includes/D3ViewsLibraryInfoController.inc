<?php

class D3ViewsLibraryInfoController extends D3LibraryInfoController {

  public function isDataKey($key) {
    return $key == $this->getDataKey();
  }

  public function getDataKey() {
    if (!$library = $this->value()) {
      return NULL;
    }
    $info = $library['views']['fields'];
    return !empty($info['_info']['data_key']) ? $info['_info']['data_key'] : 'rows';
  }

  public function getFields() {
    if (!$library = $this->value()) {
      return array();
    }
    return !empty($library['views']['fields'])
      ? $library['views']['fields']
      : array();
  }

  public function getSettings() {
    if (!$library = $this->value()) {
      return array();
    }
    return !empty($library['views']['settings']) && is_array($library['views']['settings'])
      ? $library['views']['settings']
      : array();
  }
}
