<?php

/**
 * @file
 * Contains Drupal\workflow\Entity\WorkflowInterface.
 */

// D8: namespace Drupal\workflow\Entity;

// D8: use Drupal\Core\Config\Entity\ConfigEntityBase;
// D8: use Drupal\Core\Session\AccountInterface;

/**
 * Defines a common interface for Workflow*Transition* objects.
 *
 * @see \Drupal\workflow\Entity\WorkflowConfigTransition
 * @see \Drupal\workflow\Entity\WorkflowTransition
 * @see \Drupal\workflow\Entity\WorkflowScheduledTransition
 */
interface WorkflowInterface {

  /**
   * Retrieves the entity manager service.
   *
   * @return \Drupal\workflow\Entity\WorkflowManagerInterface
   *   The entity manager service.
   */
//D8: public static function workflowManager();

  /**
   * Returns the workflow id.
   *
   * @return string
   *   $wid
   */
  public function getWorkflowId();

  /**
   * Validate the workflow. Generate a message if not correct.
   *
   * This function is used on the settings page of:
   * - Workflow field: WorkflowItem->settingsForm()
   *
   * @return bool
   *   $is_valid
   */
  public function isValid();

  /**
   * Returns if the Workflow may be deleted.
   *
   * @return bool $is_deletable
   *   TRUE if a Workflow may safely be deleted.
   */
  public function isDeletable();

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
   * @return \Drupal\workflow\Entity\WorkflowState
   *   The new state.
   */
  public function createState($sid, $save = TRUE);

  /**
   * Gets the initial state for a newly created entity.
   */
  public function getCreationState();

  /**
   * Gets the ID of the initial state for a newly created entity.
   */
  public function getCreationSid();

  /**
   * Gets the first valid state ID, after the creation state.
   *
   * Uses WorkflowState::getOptions(), because this does an access check.
   * The first State ID is user-dependent!
   */
  public function getFirstSid($entity_type, $entity, $field_name, $user, $force);

  /**
   * Returns the next state for the current state.
   * Is used in VBO Bulk actions.
   *
   * @param string $entity_type
   *   The type of the entity at hand.
   * @param object $entity
   *   The entity at hand. May be NULL (E.g., on a Field settings page).
   * @param $field_name
   * @param $user
   * @param bool $force
   *
   * @return array
   *   An array of sid=>label pairs.
   *   If $this->sid is set, returns the allowed transitions from this state.
   *   If $this->sid is 0 or FALSE, then labels of ALL states of the State's
   *   Workflow are returned.
   *
   */
  public function getNextSid($entity_type, $entity, $field_name, $user, $force = FALSE);

  /**
   * Gets all states for a given workflow.
   *
   * @param mixed $all
   *   Indicates to which states to return.
   *   - TRUE = all, including Creation and Inactive;
   *   - FALSE = only Active states, not Creation;
   *   - 'CREATION' = only Active states, including Creation.
   *
   * @return WorkflowState[]
   *   An array of WorkflowState objects.
   */
  public function getStates($all = FALSE, $reset = FALSE);

  /**
   * Gets a state for a given workflow.
   *
   * @param mixed $key
   *   A state ID or state Name.
   *
   * @return WorkflowState
   *   A WorkflowState object.
   */
  public function getState($sid);

  /**
   * Creates a Transition for this workflow.
   *
   * @param string $from_sid
   * @param string $to_sid
   * @param array $values
   *
   * @return mixed|null|static
   */
  public function createTransition($from_sid, $to_sid, $values = array());

  /**
   * Sorts all Transitions for this workflow, according to State weight.
   *
   * This is only needed for the Admin UI.
   */
  public function sortTransitions();

  /**
   * Loads all allowed ConfigTransitions for this workflow.
   *
   * @param array|bool $tids
   *   Array of Transitions IDs. If FALSE, show all transitions.
   * @param array $conditions
   *   $conditions['sid'] : if provided, a 'from' State ID.
   *   $conditions['target_sid'] : if provided, a 'to' state ID.
   *   $conditions['roles'] : if provided, an array of roles, or 'ALL'.
   * @param bool $reset
   *   Indicator to reset the cache.
   *
   * @return \Drupal\workflow\Entity\WorkflowConfigTransition[]
   */
  public function getTransitions($tids = FALSE, array $conditions = array(), $reset = FALSE);

  public function getTransitionsByTid($tid);

  /**
   *
   * Get a specific transition.
   *
   * @param string $from_sid
   * @param string $to_sid
   *
   * @return WorkflowConfigTransition[]
   */
//D8: public function getTransitionsByStateId($from_sid, $to_sid);

}
