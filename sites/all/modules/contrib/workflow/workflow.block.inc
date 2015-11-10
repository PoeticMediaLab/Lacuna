<?php
/**
 * @file
 * Provide block with Workflow form.
 *
 * Credits to workflow_extensions module.
 */

/**
 * Implements hook_block_info().
 *
 * Re-implements the block from workflow_extensions module.
 */
function workflow_block_info() {
  $blocks['workflow_transition'] = array(
    'info' => t('Workflow transition form'),
    'cache' => DRUPAL_NO_CACHE, // DRUPAL_CACHE_PER_ROLE will be assumed.
  );

  return $blocks;
}

/**
 * Implements hook_block_view().
 */
function workflow_block_view($delta) {
  $block = array();
  $form = array();

  // @todo: how to make this work for non-nodes, like terms?
  $entity = NULL;
  if ((arg(0) == 'node') && (arg(1) !== NULL) ) {
    $entity_type = arg(0);
    $entity_id = arg(1);
    $entity = entity_load_single($entity_type, $entity_id);
  }

  if ($entity) {
    list($entity_id, , $entity_bundle) = entity_extract_ids($entity_type, $entity);

    if (is_null($field_name = workflow_get_field_name($entity, $entity_type, NULL, $entity_id))) {
      return $block;
    }

    // Get the current sid.
    $current_sid = workflow_node_current_state($entity, $entity_type, $field_name);
    $current_state = ($current_sid) ? workflow_state_load_single($current_sid) : NULL;
    $workflow = ($current_state) ? $current_state->getWorkflow() : NULL;
    if (!$workflow) {
      return $block;
    }

    // Show the current state and the Workflow form to allow state changing.
    // N.B. This part is replicated in hook_node_view, workflow_tab_page, workflow_vbo, transition_edit.
    // @todo: support multiple workflows per entity.
    // For workflow_tab_page with multiple workflows, use a separate view. See [#2217291].
    $field = _workflow_info_field($field_name, $workflow);
    $field_id = $field['id'];
    $instance = field_info_instance($entity_type, $field_name, $entity_bundle);
    if (!$field_id) {
      // This is a Workflow Node workflow. Set widget options as in v7.x-1.2
      $field['settings']['widget']['comment'] = isset($workflow->options['comment_log_tab']) ? $workflow->options['comment_log_tab'] : 1; // vs. ['comment_log_node'];
      $field['settings']['widget']['current_status'] = TRUE;
    }

    $form_id = implode('_', array('workflow_transition_form', $entity_type, $entity_id, $field_id));
    $form += drupal_get_form($form_id, $field, $instance, $entity_type, $entity);

    $block['content'] = $form;
    if ($block['content']) {
      $block['subject'] = t('Current state: @state', array('@state' => $current_state->label()));
    }
  }
  return $block;
}
