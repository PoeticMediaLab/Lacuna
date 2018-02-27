<?php

/**
 * @file
 * Provides Features integration for Workflow using the CRUD API.
 *
 * As you will notice this file will only handle the <export> of Worflows,
 * including states and transitions. The <import> is handeled magically,
 * and all modifications are done in function Workflow::save().
 */

define('WORKFLOW_FEATURES_AUTHOR_NAME', 'workflow_features_author_name');

// Even if workflow Node is not enabled, Features may use Node API's type_maps.
require_once dirname(__FILE__) . '/workflow.node.type_map.inc';

/**
 * Default controller handling features integration.
 */
class WorkflowFeaturesController extends EntityDefaultFeaturesController {

  /**
   * Generates the result for hook_features_export().
   */
  public function export($data, &$export, $module_name = '') {
    $pipe = parent::export($data, $export, $module_name);

    foreach ($data as $workflow_name) {
      if ($workflow = workflow_load_by_name($workflow_name)) {
        // Add dependency on workflow_node.
        if (count($workflow->getTypeMap())) {
          $export['dependencies']['workflownode'] = 'workflownode';
        }
      }
    }

    return $pipe;
  }

  /**
   * Generates the result for hook_features_export_render().
   *
   * This is a copy of the parent, adding 'system_roles'.
   * The workflow is imported in the target system with Workflow::save().
   */
  public function export_render($module, $data, $export = NULL) {
    $translatables = $code = array();
    $code[] = '  $workflows = array();';
    $code[] = '';

    foreach ($data as $identifier) {
      // Clone workflow to make sure changes are not propagated to original.
      if ($workflow = entity_load_single($this->type, $identifier)) {
        $this->export_render_workflow($workflow, $identifier, $code);
      }
    }

    $code[] = '  return $workflows;';
    $code = implode("\n", $code);

    $hook = isset($this->info['export']['default hook']) ? $this->info['export']['default hook'] : 'default_' . $this->type;

    return array($hook => $code);
  }

  /**
   * Renders the provided workflow into export code.
   *
   * @param Workflow $workflow
   *   The workflow to export.
   * @param string $identifier
   *   The unique machine name for the workflow in the export.
   * @param array $code
   *   A reference to the export code array that will receive the output.
   */
  protected function export_render_workflow(Workflow $workflow, $identifier, array &$code) {
    // Make sure data is not copied to the database.
    $workflow = clone $workflow;

    $this->sanitize_workflow_for_export($workflow);

    // Make sure to escape the characters \ and '.
    // The following method has the advantage, that you can export with
    // features,
    // and later import without enabling Features in the target system.
    $workflow_export = addcslashes(entity_export($this->type, $workflow, '  '), '\\\'');
    $workflow_identifier = features_var_export($identifier);

    $code[] = "  // Exported workflow: {$workflow_identifier}";
    $code[] = "  \$workflows[{$workflow_identifier}] = entity_import('{$this->type}', '" . $workflow_export . "');";
    $code[] = ''; // Blank line
  }

  /**
   * Prepares the provided workflow for export.
   *
   * Removes serial IDs and replaces them with machine names.
   *
   * @param Workflow $workflow
   *   The workflow to sanitize. The contents of this object are modified directly.
   */
  protected function sanitize_workflow_for_export(Workflow $workflow) {
    // Eliminate serial IDs in exports to prevent "Overridden" status.
    // We use machine names instead.
    unset($workflow->wid);

    // Add roles to translate role IDs on target system.
    $permission = NULL;

    // Get system roles.
    $workflow->system_roles = workflow_get_roles($permission);
    // Only export system roles for roles used by this workflow.
    $roles = array();
    foreach ($workflow->transitions as $id => $transition) {
      foreach ($transition->roles as $rid) {
        $roles[] = $rid;
      }
    }
    $roles = array_unique($roles);
    foreach ($workflow->system_roles as $id => $system_role) {
      if (!in_array($id, $roles)) {
        unset($workflow->system_roles[$id]);
      }
    }

    $sid_to_name_map = $this->pack_states($workflow);
    $this->pack_transitions($workflow, $sid_to_name_map);
  }

  /**
   * "Packs" the states in the provided workflow into an export-friendly format.
   *
   * @param Workflow $workflow
   *   The workflow to pack. The contents of this object are modified directly.
   *
   * @return array
   *   A map of the old state IDs to their new machine names.
   */
  protected function pack_states(Workflow $workflow) {
    $named_states    = array();
    $sid_to_name_map = array();

    foreach ($workflow->states as $state) {
      /* @var WorkflowState $state */
      $name = $state->getName();

      $sid_to_name_map[$state->sid] = $name;

      // Eliminate serial IDs in exports to prevent "Overridden" status.
      // We use machine names instead.
      unset($state->sid);
      unset($state->wid);

      $named_states[$name] = $state;
    }
    ksort($named_states);

    // Identify states by machine name.
    $workflow->states = $named_states;

    return $sid_to_name_map;
  }

  /**
   * "Packs" the transitions in the provided workflow into an export-friendly format.
   *
   * @param Workflow $workflow
   *   The workflow to pack. The contents of this object are modified directly.
   *
   * @param array $sid_to_name_map
   *   The map of numeric state IDs to their machine names, for remapping sid
   *   references.
   */
  protected function pack_transitions(Workflow $workflow, array $sid_to_name_map) {
    $named_transitions = array();

    foreach ($workflow->transitions as $transition) {
      /* @var WorkflowTransition $transition */
      $start_name = $sid_to_name_map[$transition->sid];
      $end_name   = $sid_to_name_map[$transition->target_sid];
      $new_name = WorkflowConfigTransition::machineName($start_name, $end_name);

      $transition->name        = $new_name;
      $transition->start_state = $start_name;
      $transition->end_state   = $end_name;

      // Eliminate serial IDs in exports to prevent "Overridden" status.
      // We use machine names instead.
      unset($transition->wid);
      unset($transition->tid);
      unset($transition->sid);
      unset($transition->target_sid);

      $named_transitions[$new_name] = $transition;
    }
    ksort($named_transitions);

    // Identify transitions by new machine name.
    $workflow->transitions = $named_transitions;
  }

  /**
   * Revert this workflow, either creating the workflow new (if one with the
   * same machine name is not present), or updating the existing workflow.
   *
   * @param string $module
   *   The name of the feature module whose components should be reverted.
   */
  function revert($module = NULL) {
    // Loads defaults from feature code.
    $defaults = workflow_get_defaults($module);

    if (!empty($defaults)) {
      foreach ($defaults as $machine_name => $entity) {
        workflow_revert($defaults, $machine_name);
      }
    }
  }
}

/**
 * Implements hook_features_COMPONENT_alter().
 *
 * Adds the corresponding Workflow to the WorkflowField.
 */
function workflow_features_pipe_field_base_alter(&$pipe, $data, $export) {
  if (!empty($data)) {
    foreach ($data as $field_name) {
      // $info = field_info_field($field_name);
      $field = _workflow_info_field($field_name);

      if ($field['type'] == 'workflow') {
        // $field['settings']['wid'] can be numeric or named.
        $workflow = workflow_load_single($field['settings']['wid']);

        // Fields might reference missing workflows.
        if (!empty($workflow)) {
          $pipe['Workflow'][] = $workflow->name;
        }
      }
    }
  }
}

/**
 * Implements hook_features_api_alter().
 *
 * Ensures Workflow always fires last during rebuild, to ensure that roles
 * referenced by workflows to be loaded-in when features contain roles.
 */
function workflow_features_api_alter(array &$components) {
  // FIXME: Why is Workflow the only features provider with an uppercase component name?
  $component_name = 'Workflow';

  if (isset($components[$component_name])) {
    $setting = $components[$component_name];
    unset($components[$component_name]);
    $components[$component_name] = $setting;
  }
}
