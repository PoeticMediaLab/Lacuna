<?php

/**
 * Annotation entity class.
 */
class AnnotationClassRevision extends Entity {
  public function __construct(array $values = array(), $entityType = NULL) {
    parent::__construct($values, 'annotation');
  }

  /**
   * Override buildContent() to add the username to the output.
   */
  public function buildContent($view_mode = 'full', $langcode = NULL) {
    $content = array();
    return entity_get_controller($this->entityType)->buildContent($this, $view_mode, $langcode, $content);
  }

  protected function defaultLabel() {
    $type = entity_test_get_types($this->name);
    return $type->label;
  }

  protected function defaultUri() {
    return array('path' => 'annotation/' . $this->identifier());
  }
}
