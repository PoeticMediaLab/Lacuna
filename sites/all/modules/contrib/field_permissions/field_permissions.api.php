<?php

/**
 * @file
 * Hooks provided by the Field Permission module.
 */

/**
 * Defines the owner of an entity.
 *
 * Because not all entities have uids, this hook allows other modules to specify
 * one.
 *
 * @param int $uid
 *   The userid that will be checked against the current user's account->uid.
 * @param object $entity
 *   The entity this field belongs to.
 */
// @codingStandardsIgnoreStart
function hook_field_permissions_userid_ENTITY_TYPE_alter(&$uid, $entity) {
  // This example always assigns user 15 as the owner of an entity.
  $uid = 15;
}
// @codingStandardsIgnoreEnd

/**
 * Alter the permissions handled by field_permissions module.
 *
 * @param array $permissions
 *   The $permissions array created by the Field permissions module.
 * @param string $field_label
 *   The field name.
 */
function hook_field_permissions_list_alter(&$permissions, $field_label) {
  $permissions += array(
    'view own node preview' => array(
      'label' => t('View own field on node preview'),
      'title' => t('View own value for field %field on node preview', array('%field' => $field_label)),
    ),
    'view node preview' => array(
      'label' => t('View field on node preview'),
      'title' => t("View anyone's value for field %field on node preview", array('%field' => $field_label)),
    ),
  );
}

/**
 * Hook invoked with custom field permissions.
 *
 * This hook can be used to revoke access to the field. If access is not
 * revoked, default access of the Field permissions module will apply.
 *
 * @param string $op
 *   The operation to be performed. Possible values: 'edit', 'view'.
 * @param array $field
 *   The field on which the operation is to be performed.
 * @param string $entity_type
 *   The type of $entity; for example, 'node' or 'user'.
 * @param object $entity
 *   (optional) The entity for the operation.
 * @param object $account
 *   (optional) The account to check; if not given use currently logged in user.
 *
 * @return bool
 *   FALSE if the operation is not allowed.
 *
 * @see field_permissions_field_access()
 * @see field_access()
 */
function hook_field_permissions_custom_field_access($op, $field, $entity_type, $entity, $account) {
  if ($op == 'view' && $entity_type == 'node' && !empty($entity)) {
    // Check if user has access to view this field in any entity.
    if (!user_access('view node preview ' . $field['field_name'], $account)) {
      return FALSE;
    }

    // If the user has permission to view entities that they own, return TRUE if
    // they own this entity or FALSE if they don't.
    if (user_access('view own node preview ' . $field['field_name'], $account)) {
      return _field_permissions_entity_is_owned_by_account($entity, $account);
    }
  }

  return TRUE;
}
