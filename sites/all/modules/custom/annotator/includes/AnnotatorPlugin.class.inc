<?php

class AnnotatorPlugin {

  public function __construct($plugin = array()) {
    foreach ($plugin as $name => $attribute) {
      if (is_string($attribute)) {
        $this->{$name} = $attribute;
      }
    }
  }

  public function settingsForm() {
    return NULL;
  }

  public function settings($defaults = array()) {
    $stored = variable_get('annotator_' . $this->name, array());
    return array_merge($defaults, $stored);
  }

  public function setup() {}

  public function alter(&$annotation, $op) {}
}