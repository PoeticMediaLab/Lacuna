<?php
/**
 * @file
 * lacuna_stories_peer_groups.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function lacuna_stories_peer_groups_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'node-peer_group-group_access'
  $field_instances['node-peer_group-group_access'] = array(
    'bundle' => 'peer_group',
    'default_value' => array(
      0 => array(
        'value' => 0,
      ),
    ),
    'deleted' => 0,
    'description' => '<br>
Public Peer Groups show in the Peer Groups listing, where people can request to join. Non-members can see who the group members are.<br>
Private Peer Groups cannot be seen by non-members in any way. You need to invite people into the group.<br>
<br>
This setting can be changed at any time.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'list',
        'settings' => array(),
        'type' => 'list_default',
        'weight' => 1,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'group_access',
    'label' => 'Group Visibility',
    'required' => 1,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'view modes' => array(
      'full' => array(
        'label' => 'above',
        'type' => 'options_onoff',
      ),
      'teaser' => array(
        'label' => 'above',
        'type' => 'options_onoff',
      ),
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_buttons',
      'weight' => 1,
    ),
    'widget_type' => 'options_select',
  );

  // Exported field_instance: 'node-peer_group-group_group'
  $field_instances['node-peer_group-group_group'] = array(
    'bundle' => 'peer_group',
    'default_value' => array(
      0 => array(
        'value' => 1,
      ),
    ),
    'deleted' => 0,
    'description' => 'Determine if this is an OG group.',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'og_ui',
        'settings' => array(
          'field_name' => FALSE,
        ),
        'type' => 'og_group_subscribe',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'display_label' => 1,
    'entity_type' => 'node',
    'field_name' => 'group_group',
    'label' => 'Group',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'view modes' => array(
      'full' => array(
        'custom settings' => FALSE,
        'label' => 'Full',
        'type' => 'og_group_subscribe',
      ),
      'teaser' => array(
        'custom settings' => FALSE,
        'label' => 'Teaser',
        'type' => 'og_group_subscribe',
      ),
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(
        'display_label' => 0,
        'og_hide' => 1,
      ),
      'type' => 'options_onoff',
      'weight' => 2,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('<br>
Public Peer Groups show in the Peer Groups listing, where people can request to join. Non-members can see who the group members are.<br>
Private Peer Groups cannot be seen by non-members in any way. You need to invite people into the group.<br>
<br>
This setting can be changed at any time.');
  t('Determine if this is an OG group.');
  t('Group');
  t('Group Visibility');

  return $field_instances;
}
