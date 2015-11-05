<?php

/**
 * @file
 * Contains workflow\includes\Field\WorkflowDefaultWidget.
 */

/**
 * Plugin implementation of the 'workflow_default' widget.
 */
class WorkflowDefaultWidget extends WorkflowD7Base { // D8: extends WidgetBase {

  /**
   * Returns the settings.
   *
   * @todo d8: Replace by the 'annotations' in D8 (See comments above this class).
   */
  public static function settings() {
    return array(
      'workflow_default' => array(
        'label' => t('Workflow'),
        'field types' => array('workflow'),
        'settings' => array(
          'name_as_title' => 1,
          'fieldset' => 0,
          'comment' => 1,
        ),
      ),
    );
  }

  /**
   * Implements hook_field_widget_settings_form() --> WidgetInterface::settingsForm().
   *
   * {@inheritdoc}
   *
   * The Widget Instance has no settings. To have a uniform UX, all settings are done on the Field level.
   */
  public function settingsForm(array $form, array &$form_state, $has_data) {
    $element = array();
    return $element;
  }

  /**
   * Implements hook_field_widget_form --> WidgetInterface::formElement().
   *
   * {@inheritdoc}
   *
   * Be careful: Widget may be shown in very different places. Test carefully!!
   *  - On a entity add/edit page
   *  - On a entity preview page
   *  - On a entity view page
   *  - On a entity 'workflow history' tab
   *  - On a comment display, in the comment history
   *  - On a comment form, below the comment history
   *
   * @todo D8: change "array $items" to "FieldInterface $items"
   */
  public function formElement(array $items, $delta, array $element, array &$form, array &$form_state) {
    $field = $this->field;
    $instance = $this->instance;
    $entity = $this->entity;
    $entity_type = $this->entity_type;

    // Add the element. Do not use drupal_get_form, or you will have a form in a form.
    workflow_transition_form($form, $form_state, $field, $instance, $entity_type, $entity);
  }

  /**
   * Implements workflow_transition() -> WorkflowDefaultWidget::submit().
   *
   * Overrides submit(array $form, array &$form_state).
   * Contains 2 extra parameters for D7
   *
   * @param array $form
   * @param array $form_state
   * @param array $items
   *   The value of the field.
   * @param bool $force
   *   TRUE if all access must be overridden, e.g., for Rules.
   *
   * @return int
   *   If update succeeded, the new State Id. Else, the old Id is returned.
   *
   * This is called from function _workflowfield_form_submit($form, &$form_state)
   * It is a replacement of function workflow_transition($node, $new_sid, $force, $field)
   * It performs the following actions;
   * - save a scheduled action
   * - update history
   * - restore the normal $items for the field.
   * @todo: remove update of {node_form} table. (separate task, because it has features, too)
   */
  public function submit(array $form, array &$form_state, array &$items, $force = FALSE) {
    return workflow_transition_form_submit($form, $form_state);
  }

  /**
   * Implements hook_field_widget_error --> WidgetInterface::errorElement().
   */
  // public function errorElement(array $element, ConstraintViolationInterface $violation, array $form, array &$form_state) {
  // }
  // public function settingsSummary() {
  // }
  // public function massageFormValues(array $values, array $form, array &$form_state) {
  // }

}
