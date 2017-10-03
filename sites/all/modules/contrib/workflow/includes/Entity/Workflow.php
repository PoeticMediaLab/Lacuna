<?php

/**
 * @file
 * Contains workflow\includes\Entity\Workflow.
 * Contains workflow\includes\Entity\WorkflowController.
 */

// Include file to avoid drush upgrade errors.
include_once('WorkflowInterface.php');

class Workflow extends Entity implements WorkflowInterface {
  public $wid = 0;
  public $name = '';
  public $tab_roles = array();
  public $options = array();
  protected $creation_sid = 0;

  // Attached States.
  public $states = NULL;
  public $transitions = NULL;

  /**
   * CRUD functions.
   */

  // public function __construct(array $values = array(), $entityType = NULL) {
  //   return parent::__construct($values, $entityType);
  // }

  public function __clone() {
    // Clone the arrays of States and Transitions.
    foreach ($this->states as &$state) {
      $state = clone $state;
    }
    foreach ($this->transitions as &$transition) {
      $transition = clone $transition;
    }
  }

  /**
   * Given information, update or insert a new workflow.
   *
   * This also handles importing, rebuilding, reverting from Features,
   * as defined in workflow.features.inc.
   *
   * When changing this function, test with the following situations:
   * - maintain Workflow in Admin UI;
   * - clone Workflow in Admin UI;
   * - create/revert/rebuild Workflow with Features; @see workflow.features.inc
   * - save Workflow programmatically;
   */
  public function save($create_creation_state = TRUE) {
    // Are we saving a new Workflow?
    $is_new = !empty($this->is_new);
    // Are we rebuilding, reverting a new Workflow? @see workflow.features.inc
    $is_rebuild = !empty($this->is_rebuild) || !empty($this->is_reverted);

    if ($is_rebuild) {
      $this->is_rebuild = TRUE;
      $this->preRebuild();
    }

    $return = parent::save();

    // On either clone or rebuild from features.
    if ($is_new || $is_rebuild) {
      $this->rebuildInternals();
      if ($is_rebuild) {
        // The above may have marked us overridden!
        $this->status = ENTITY_IN_CODE;
        parent::save();
      }
    }

    // Make sure a Creation state exists.
    if ($is_new) {
      $state = $this->getCreationState();
    }

    workflow_reset_cache($this->wid);

    return $return;
  }

  /**
   * Rebuild things that get saved with this entity.
   */
  protected function preRebuild() {
    // Remap roles. They can come from another system with shifted role IDs.
    // See also https://drupal.org/node/1702626 .
    $this->rebuildRoles($this->tab_roles);

    // After update.php or import feature, label might be empty. @todo: remove in D8.
    if (empty($this->label)) {
      $this->label = $this->name;
    }
  }

  /**
   * Rebuild internals that get saved separately.
   */
  protected function rebuildInternals() {
    // Insert the type_map when building from Features.
    if (isset($this->typeMap)) {
      foreach ($this->typeMap as $node_type) {
        workflow_insert_workflow_type_map($node_type, $this->wid);
      }
    }

    // Index the existing states and transitions by name.
    $db_name_map = WorkflowState::getStates($this->wid, TRUE); // sid -> state.
    $db_states = array(); // name -> state.
    foreach ($db_name_map as $state) {
      $db_states[$state->getName()] = $state;
    }
    $db_transitions = array();
    foreach (entity_load('WorkflowConfigTransition') as $transition) {
      if ($transition->wid == $this->wid) {
        $start_name = $db_name_map[$transition->sid]->getName();
        $end_name = $db_name_map[$transition->target_sid]->getName();
        $name = WorkflowConfigTransition::machineName($start_name, $end_name);
        $db_transitions[$name] = $transition;
      }
    }

    // Update/create states.
    $states = isset($this->states) ? $this->states : array();
    $saved_states = array(); // Saved states: key -> sid.
    $saved_state_names = array();
    foreach ($states as $key => $data) {
      $data = (array)$data;

      $name = $data['name'];
      if (isset($db_states[$name])) {
        $state = $db_states[$name];
      }
      else {
        $state = $this->createState($name, FALSE);
      }

      $state->wid = $this->wid;
      $state->state = $data['state'];
      $state->weight = $data['weight'];
      $state->sysid = $data['sysid'];
      if (!$data['status']) {
        $this->rebuildStateInactive($state);
      }
      $state->status = $data['status'];
      $state->save();

      unset($db_states[$name]);
      $saved_states[$key] = $state;
      $saved_state_names[$state->sid] = $key;
    }

    // Update/create transitions.
    $transitions = isset($this->transitions) ? $this->transitions : array();
    foreach ($transitions as $name => $data) {
      $data = (array)$data;

      if (is_numeric($name)) {
        $start_state = $saved_states[$saved_state_names[$data['sid']]];
        $end_state = $saved_states[$saved_state_names[$data['target_sid']]];
        $name = WorkflowConfigTransition::machineName($start_state->getName(),
          $end_state->getName());
      }
      else {
        $start_state = $saved_states[$data['start_state']];
        $end_state = $saved_states[$data['end_state']];
      }

      if (isset($db_transitions[$name])) {
        $transition = $db_transitions[$name];
      }
      else {
        $transition = $this->createTransition($start_state->sid,
          $end_state->sid);
      }

      $transition->wid = $this->wid;
      $transition->sid = $start_state->sid;
      $transition->target_sid = $end_state->sid;
      $transition->label = $data['label'];
      $transition->roles = $data['roles'];
      $this->rebuildRoles($transition->roles);
      $transition->save();

      unset($db_transitions[$name]);
    }

    // Any states/transitions left in $db_states/transitions need deletion.
    foreach ($db_states as $state) {
      $this->rebuildStateInactive($state);
      $state->delete();
    }
    foreach ($db_transitions as $transition) {
      $transition->delete();
    }

    // Clear the caches, and set $this->states and $this->transitions.
    $this->states = $this->transitions = NULL;
    $this->getStates(TRUE, TRUE);
    $this->getTransitions(FALSE, array(), TRUE);
  }

  /**
   * Handle a state becoming inactive during a rebuild.
   */
  protected function rebuildStateInactive($state) {
    if (!$state->isActive()) {
      return;
    }

    // TODO: What should we do in this case? Is this safe?
    $state->deactivate(NULL);
  }

  /**
   * Given a wid, delete the workflow and its data.
   *
   * @deprecated: workflow_delete_workflows_by_wid() --> Workflow::delete().
   */
  public function delete() {
    $wid = $this->wid;

    // Notify any interested modules before we delete the workflow.
    // E.g., Workflow Node deletes the {workflow_type_map} record.
    module_invoke_all('workflow', 'workflow delete', $wid, NULL, NULL, FALSE);

    // Delete associated state (also deletes any associated transitions).
    foreach ($this->getStates($all = TRUE) as $state) {
      $state->deactivate(0);
      $state->delete();
    }

    // Delete the workflow.
    db_delete('workflows')->condition('wid', $wid)->execute();
  }

  /**
   * Validate the workflow. Generate a message if not correct.
   *
   * This function is used on the settings page of:
   * - Workflow node: workflow_admin_ui_type_map_form()
   * - Workflow field: WorkflowItem->settingsForm()
   *
   * @return bool
   *   $is_valid
   */
  public function isValid() {
    $is_valid = TRUE;

    // Don't allow workflows with no states. There should always be a creation state.
    $states = $this->getStates($all = FALSE);
    if (count($states) < 1) {
      // That's all, so let's remind them to create some states.
      $message = t('Workflow %workflow has no states defined, so it cannot be assigned to content yet.',
        array('%workflow' => $this->getName()));
      drupal_set_message($message, 'warning');

      // Skip allowing this workflow.
      $is_valid = FALSE;
    }

    // Also check for transitions, at least out of the creation state. Use 'ALL' role.
    $transitions = $this->getTransitionsBySid($this->getCreationSid(), $roles = 'ALL');
    if (count($transitions) < 1) {
      // That's all, so let's remind them to create some transitions.
      $message = t('Workflow %workflow has no transitions defined, so it cannot be assigned to content yet.',
        array('%workflow' => $this->getName()));
      drupal_set_message($message, 'warning');

      // Skip allowing this workflow.
      $is_valid = FALSE;
    }

    // If the Workflow is mapped to a node type, check if workflow->options is set.
    if ($this->getTypeMap() && !count($this->options)) {
      // That's all, so let's remind them to create some transitions.
      $message = t('Please maintain Workflow %workflow on its <a href="@url">settings</a> page.',
        array(
          '%workflow' => $this->getName(),
          '@url' => url('admin/config/workflow/workflow/manage/' . $this->wid),
        )
      );
      drupal_set_message($message, 'warning');

      // Skip allowing this workflow.
      // $is_valid = FALSE;
    }

    return $is_valid;
  }

  /**
   * Returns if the Workflow may be deleted.
   *
   * @return bool $is_deletable
   *   TRUE if a Workflow may safely be deleted.
   */
  public function isDeletable() {
    $is_deletable = FALSE;

    // May not be deleted if a TypeMap exists.
    if ($this->getTypeMap()) {
      return $is_deletable;
    }

    // May not be deleted if assigned to a Field.
    foreach (_workflow_info_fields() as $field) {
      if ($field['settings']['wid'] == $this->wid) {
        return $is_deletable;
      }
    }

    // May not be deleted if a State is assigned to a state.
    foreach ($this->getStates(TRUE) as $state) {
      if ($state->count()) {
        return $is_deletable;
      }
    }
    $is_deletable = TRUE;
    return $is_deletable;
  }

  /**
   * Property functions.
   */

  /**
   * Returns the workflow id.
   *
   * @return int
   *   $wid
   */
  public function getWorkflowId() {
    return $this->wid;
  }

  /**
   * Create a new state for this workflow.
   *
   * @param string $name
   *   The untranslated human readable label of the state.
   * @param bool $save
   *   Indicator if the new state must be saved. Normally, the new State is
   *   saved directly in the database. This is because you can use States only
   *   with Transitions, and they rely on State IDs which are generated
   *   magically when saving the State. But you may need a temporary state.
   *
   * @return WorkflowState
   */
  public function createState($name, $save = TRUE) {
    $wid = $this->wid;
    $state = workflow_state_load_by_name($name, $wid);
    if (!$state) {
      $state = entity_create('WorkflowState', array('name' => $name, 'state' => $name, 'wid' => $wid));
      if ($save) {
        $state->save();
      }
    }
    $state->setWorkflow($this);
    // Maintain the new object in the workflow.
    $this->states[$state->sid] = $state;

    return $state;
  }

  /**
   * Gets the initial state for a newly created entity.
   */
  public function getCreationState() {
    $sid = $this->getCreationSid();
    return ($sid) ? $this->getState($sid) : $this->createState(WORKFLOW_CREATION_STATE_NAME);
  }

  /**
   * Gets the ID of the initial state for a newly created entity.
   */
  public function getCreationSid() {
    if (!$this->creation_sid) {
      foreach ($this->getStates($all = TRUE) as $state) {
        if ($state->isCreationState()) {
          $this->creation_sid = $state->sid;
        }
      }
    }
    return $this->creation_sid;
  }

  /**
   * Gets the first valid state ID, after the creation state.
   *
   * Uses WorkflowState::getOptions(), because this does a access check.
   * The first State ID is user-dependent!
   */
  public function getFirstSid($entity_type, $entity, $field_name, $user, $force) {
    $creation_state = $this->getCreationState();
    $options = $creation_state->getOptions($entity_type, $entity, $field_name, $user, $force);
    if ($options) {
      $keys = array_keys($options);
      $sid = $keys[0];
    }
    else {
      // This should never happen, but it did during testing.
      drupal_set_message(t('There are no workflow states available. Please notify your site administrator.'), 'error');
      $sid = 0;
    }
    return $sid;
  }

  /**
   * Returns the next state for the current state.
   *
   * @param string $entity_type
   *   The type of the entity at hand.
   * @param object $entity
   *   The entity at hand. May be NULL (E.g., on a Field settings page).
   * @param $field_name
   * @param $user
   * @param bool $force
   *
   * @return int $sid
   *   A state ID.
   */
  public function getNextSid($entity_type, $entity, $field_name, $user, $force = FALSE) {
    $new_sid = workflow_node_current_state($entity, $entity_type, $field_name);

    if ($new_sid && $new_state = workflow_state_load_single($new_sid)) {
      /* @var $current_state WorkflowState */
      $options = $new_state->getOptions($entity_type, $entity, $field_name, $user, $force);
      // Loop over every option. To find the next one.
      $flag = $new_state->isCreationState();
      foreach ($options as $sid => $name) {
        if ($flag) {
          $new_sid = $sid;
          break;
        }
        if ($sid == $new_state->sid) {
          $flag = TRUE;
        }
      }
    }

    return $new_sid;
  }

  /**
   * Gets all states for a given workflow.
   *
   * @param mixed $all
   *   Indicates to which states to return.
   *   - TRUE = all, including Creation and Inactive;
   *   - FALSE = only Active states, not Creation;
   *   - 'CREATION' = only Active states, including Creation.
   *
   * @return array
   *   An array of WorkflowState objects.
   */
  public function getStates($all = FALSE, $reset = FALSE) {
    if ($this->states === NULL || $reset) {
      $this->states = $this->wid ? WorkflowState::getStates($this->wid, $reset) : array();
    }
    // Do not unset, but add to array - you'll remove global objects otherwise.
    $states = array();
    foreach ($this->states as $state) {
      if ($all === TRUE) {
        $states[$state->sid] = $state;
      }
      elseif (($all === FALSE) && ($state->isActive() && !$state->isCreationState())) {
        $states[$state->sid] = $state;
      }
      elseif (($all == 'CREATION') && ($state->isActive() || $state->isCreationState())) {
        $states[$state->sid] = $state;
      }
    }
    return $states;
  }

  /**
   * Gets a state for a given workflow.
   *
   * @param mixed $key
   *   A state ID or state Name.
   *
   * @return WorkflowState
   *   A WorkflowState object.
   */
  public function getState($key) {
    if (is_numeric($key)) {
      return workflow_state_load_single($key, $this->wid);
    }
    else {
      return workflow_state_load_by_name($key, $this->wid);
    }
  }

  /**
   * Creates a Transition for this workflow.
   */
  public function createTransition($sid, $target_sid, $values = array()) {
    $workflow = $this;
    if (is_numeric($sid) && is_numeric($target_sid)) {
      $values['sid'] = $sid;
      $values['target_sid'] = $target_sid;
    }
    else {
      $state = $workflow->getState($sid);
      $target_state = $workflow->getState($target_sid);
      $values['sid'] = $state->sid;
      $values['target_sid'] = $target_state->sid;
    }

    // First check if this transition already exists.
    if ($transitions = entity_load('WorkflowConfigTransition', FALSE, $values)) {
      $transition = reset($transitions);
    }
    else {
      $values['wid'] = $workflow->wid;
      $transition = entity_create('WorkflowConfigTransition', $values);
      $transition->save();
    }
    $transition->setWorkflow($this);
    // Maintain the new object in the workflow.
    $this->transitions[$transition->tid] = $transition;

    return $transition;
  }

  /**
   * Sorts all Transitions for this workflow, according to State weight.
   *
   * This is only needed for the Admin UI.
   */
  public function sortTransitions() {
    // Sort the transitions on state weight.
    usort($this->transitions, '_workflow_transitions_sort_by_weight');
  }

  /**
   * Loads all allowed ConfigTransitions for this workflow.
   *
   * @param mixed $tids
   *   Array of Transitions IDs. If FALSE, show all transitions.
   * @param array $conditions
   *   $conditions['sid'] : if provided, a 'from' State ID.
   *   $conditions['target_sid'] : if provided, a 'to' state ID.
   *   $conditions['roles'] : if provided, an array of roles, or 'ALL'.
   * @param bool $reset
   *   Indicator to reset the cache.
   *
   * @return array
   *   An array of keyed transitions.
   */
  public function getTransitions($tids = FALSE, array $conditions = array(), $reset = FALSE) {
    $config_transitions = array();

    // Get valid + creation states.
    $states = $this->getStates('CREATION');

    // Get filters on 'from' states, 'to' states, roles.
    $sid = isset($conditions['sid']) ? $conditions['sid'] : FALSE;
    $target_sid = isset($conditions['target_sid']) ? $conditions['target_sid'] : FALSE;
    $roles = isset($conditions['roles']) ? $conditions['roles'] : 'ALL';

    // Cache all transitions in the workflow.
    // We may have 0 transitions....
    if ($this->transitions === NULL) {
      $this->transitions = array();
      // Get all transitions. (Even from other workflows. :-( )
      $config_transitions = entity_load('WorkflowConfigTransition', $tids, array(), $reset);
      foreach ($config_transitions as &$config_transition) {
        if (isset($states[$config_transition->sid])) {
          $config_transition->setWorkflow($this);
          $this->transitions[$config_transition->tid] = $config_transition;
        }
      }
      $this->sortTransitions();
    }

    $config_transitions = array();
    foreach ($this->transitions as &$config_transition) {
      if (!isset($states[$config_transition->sid])) {
        // Not a valid transition for this workflow.
      }
      elseif ($sid && $sid != $config_transition->sid) {
        // Not the requested 'from' state.
      }
      elseif ($target_sid && $target_sid != $config_transition->target_sid) {
        // Not the requested 'to' state.
      }
      elseif ($roles == 'ALL' || $config_transition->isAllowed($roles)) {
        // Transition is allowed, permitted. Add to list.
        $config_transition->setWorkflow($this);
        $config_transitions[$config_transition->tid] = $config_transition;
      }
      else {
        // Transition is otherwise not allowed.
      }
    }

    return $config_transitions;
  }

  public function getTransitionsByTid($tid, $roles = '', $reset = FALSE) {
    $conditions = array(
      'roles' => $roles,
    );
    return $this->getTransitions(array($tid), $conditions, $reset);
  }

  public function getTransitionsBySid($sid, $roles = '', $reset = FALSE) {
    $conditions = array(
      'sid' => $sid,
      'roles' => $roles,
    );
    return $this->getTransitions(FALSE, $conditions, $reset);
  }

  public function getTransitionsByTargetSid($target_sid, $roles = '', $reset = FALSE) {
    $conditions = array(
      'target_sid' => $target_sid,
      'roles' => $roles,
    );
    return $this->getTransitions(FALSE, $conditions, $reset);
  }

  /**
   * Get a specific transition. Therefore, use $roles = 'ALL'.
   */
  public function getTransitionsBySidTargetSid($sid, $target_sid, $roles = 'ALL', $reset = FALSE) {
    $conditions = array(
      'sid' => $sid,
      'target_sid' => $target_sid,
      'roles' => $roles,
    );
    return $this->getTransitions(FALSE, $conditions, $reset);
  }

  /**
   * Gets a the type map for a given workflow.
   *
   * @param int $sid
   *   A state ID.
   *
   * @return array
   *   An array of typemaps.
   */
  public function getTypeMap() {
    $result = array();

    $type_maps = module_exists('workflownode') ? workflow_get_workflow_type_map_by_wid($this->wid) : array();
    foreach ($type_maps as $map) {
      $result[] = $map->type;
    }

    return $result;
  }

  /**
   * Gets a setting from the state object.
   */
  public function getSetting($key, array $field = array()) {
    switch ($key) {
      case 'watchdog_log':
        if (isset($this->options['watchdog_log'])) {
          // This is set via Node API.
          return $this->options['watchdog_log'];
        }
        elseif ($field) {
          if (isset($field['settings']['watchdog_log'])) {
            // This is set via Field API.
            return $field['settings']['watchdog_log'];
          }
        }
        drupal_set_message('Setting Workflow::getSetting(' . $key . ') does not exist', 'error');
        break;

      default:
        drupal_set_message('Setting Workflow::getSetting(' . $key . ') does not exist', 'error');
    }
  }

  /**
   * Mimics Entity API functions.
   */
  public function getName() {
    return $this->name;
  }

  protected function defaultLabel() {
    return isset($this->label) ? $this->label : '';
  }

  protected function defaultUri() {
    return array('path' => 'admin/config/workflow/workflow/manage/' . $this->wid);
  }

  protected function rebuildRoles(array &$roles) {
    $role_map = isset($this->system_roles) ? $this->system_roles : array();
    if (!$role_map) {
      return;
    }

    // See also https://drupal.org/node/1702626 .
    $new_roles = array();
    foreach ($roles as $key => $rid) {
      if ($rid == WORKFLOW_ROLE_AUTHOR_RID) {
        $new_roles[$rid] = $rid;
      }
      else {
        if ($role = user_role_load_by_name($role_map[$rid])) {
          $new_roles[$role->rid] = (int)($role->rid);
        }
      }
    }
    $roles = $new_roles;
  }

}

/**
 * Helper function to sort the transitions.
 *
 * @param WorkflowConfigTransition $a
 * @param WorkflowConfigTransition $b
 *
 * @return int
 */
function _workflow_transitions_sort_by_weight($a, $b) {
  // First sort on From-State.
  $old_state_a = $a->getOldState();
  $old_state_b = $b->getOldState();
  if ($old_state_a->weight < $old_state_b->weight) return -1;
  if ($old_state_a->weight > $old_state_b->weight) return +1;

  // Then sort on To-State.
  $new_state_a = $a->getNewState();
  $new_state_b = $b->getNewState();
  if ($new_state_a->weight < $new_state_b->weight) return -1;
  if ($new_state_a->weight > $new_state_b->weight) return +1;
  return 0;
}


/**
 * Implements a controller class for Workflow.
 */
class WorkflowController extends EntityAPIControllerExportable {

  // public function create(array $values = array()) {    return parent::create($values);  }
  // public function load($ids = array(), $conditions = array()) { }

  public function delete($ids, DatabaseTransaction $transaction = NULL) {
    // @todo: replace WorkflowController::delete() with parent.
    // @todo: throw error if not workflow->isDeletable().
    foreach ($ids as $wid) {
      if ($workflow = workflow_load($wid)) {
        $workflow->delete();
      }
    }
    $this->resetCache();
  }

  /**
   * Overrides DrupalDefaultEntityController::cacheGet().
   *
   * Override default function, due to Core issue #1572466.
   */
  protected function cacheGet($ids, $conditions = array()) {
    // Load any available entities from the internal cache.
    if ($ids === FALSE && !$conditions) {
      return $this->entityCache;
    }
    return parent::cacheGet($ids, $conditions);
  }

  /**
   * Overrides DrupalDefaultEntityController::cacheSet().
   */
  /*
    // protected function cacheSet($entities) { }
    //   return parent::cacheSet($entities);
    // }
   */

  /**
   * Overrides DrupalDefaultEntityController::resetCache().
   *
   * Called by workflow_reset_cache, to
   * Reset the Workflow when States, Transitions have been changed.
   */
  // public function resetCache(array $ids = NULL) {
  //   parent::resetCache($ids);
  // }

  /**
   * Overrides DrupalDefaultEntityController::attachLoad().
   */
  protected function attachLoad(&$queried_entities, $revision_id = FALSE) {
    foreach ($queried_entities as $entity) {
      // Load the states, so they are already present on the next (cached) load.
      $entity->states = $entity->getStates($all = TRUE);
      $entity->transitions = $entity->getTransitions(FALSE);
      $entity->typeMap = $entity->getTypeMap();
    }

    parent::attachLoad($queried_entities, $revision_id);
  }
}
