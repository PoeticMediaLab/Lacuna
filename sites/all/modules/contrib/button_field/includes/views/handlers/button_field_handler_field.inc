<?php

/**
 * Button field views handler
 */
class button_field_handler_field extends views_handler_field_field {
  /**
   * Return an array of items for the field.
   */
  function set_items($values, $row_id) {
    $display = array(
      'type' => $this->options['type'],
      'settings' => $this->options['settings'],
      'label' => 'hidden',
      // Pass the View object in the display so that fields can act on it.
      'views_view' => $this->view,
      'views_field' => $this,
      'views_row_id' => $row_id,
    ); // end $display

    // Get the entity and type that we will render the field about.
    $entity_type = $values->_field_data[$this->field_alias]['entity_type'];
    $entity = $this->get_value($values, 'entity');
    if (!$entity) {
      return array();
    } // end if we do not have an entity

    $langcode = $this->field_language($entity_type, $entity);
    $render_array = field_view_field($entity_type, $entity,
      $this->definition['field_name'], $display, $langcode);

    // Check to see if we should return the field already rendered.
    if ($this->options['field_api_classes']) {
      // Make a copy.
      $array = $render_array;
      return array(array('rendered' => drupal_render($render_array)));
    } // end if we should return the field already rendered

    return array(array('rendered' => $render_array));
  } // end function set_items()
} // end class button_field_handler_field
