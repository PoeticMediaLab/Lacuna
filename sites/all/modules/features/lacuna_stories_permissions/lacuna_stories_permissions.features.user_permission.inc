<?php
/**
 * @file
 * lacuna_stories_permissions.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function lacuna_stories_permissions_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'access administration menu'.
  $permissions['access administration menu'] = array(
    'name' => 'access administration menu',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
    ),
    'module' => 'admin_menu',
  );

  // Exported permission: 'access administration pages'.
  $permissions['access administration pages'] = array(
    'name' => 'access administration pages',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'system',
  );

  // Exported permission: 'access all views'.
  $permissions['access all views'] = array(
    'name' => 'access all views',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'views',
  );

  // Exported permission: 'access all webform results'.
  $permissions['access all webform results'] = array(
    'name' => 'access all webform results',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'webform',
  );

  // Exported permission: 'access any private annotation'.
  $permissions['access any private annotation'] = array(
    'name' => 'access any private annotation',
    'roles' => array(
      'ARC Member' => 'ARC Member',
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
    ),
    'module' => 'annotation',
  );

  // Exported permission: 'access backup and migrate'.
  $permissions['access backup and migrate'] = array(
    'name' => 'access backup and migrate',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'backup_migrate',
  );

  // Exported permission: 'access backup files'.
  $permissions['access backup files'] = array(
    'name' => 'access backup files',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'backup_migrate',
  );

  // Exported permission: 'access biblio content'.
  $permissions['access biblio content'] = array(
    'name' => 'access biblio content',
    'roles' => array(
      'ARC Collaborator' => 'ARC Collaborator',
      'ARC Member' => 'ARC Member',
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'biblio',
  );

  // Exported permission: 'access comments'.
  $permissions['access comments'] = array(
    'name' => 'access comments',
    'roles' => array(
      'ARC Collaborator' => 'ARC Collaborator',
      'ARC Member' => 'ARC Member',
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
    ),
    'module' => 'comment',
  );

  // Exported permission: 'access content'.
  $permissions['access content'] = array(
    'name' => 'access content',
    'roles' => array(
      'administrator' => 'administrator',
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: 'access content overview'.
  $permissions['access content overview'] = array(
    'name' => 'access content overview',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'access contextual links'.
  $permissions['access contextual links'] = array(
    'name' => 'access contextual links',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'contextual',
  );

  // Exported permission: 'access dashboard'.
  $permissions['access dashboard'] = array(
    'name' => 'access dashboard',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
    ),
    'module' => 'dashboard',
  );

  // Exported permission: 'access notify'.
  $permissions['access notify'] = array(
    'name' => 'access notify',
    'roles' => array(
      'ARC Collaborator' => 'ARC Collaborator',
      'ARC Member' => 'ARC Member',
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'notify',
  );

  // Exported permission: 'access own webform results'.
  $permissions['access own webform results'] = array(
    'name' => 'access own webform results',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'webform',
  );

  // Exported permission: 'access own webform submissions'.
  $permissions['access own webform submissions'] = array(
    'name' => 'access own webform submissions',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'webform',
  );

  // Exported permission: 'access private fields'.
  $permissions['access private fields'] = array(
    'name' => 'access private fields',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'access rules debug'.
  $permissions['access rules debug'] = array(
    'name' => 'access rules debug',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'rules',
  );

  // Exported permission: 'access site in maintenance mode'.
  $permissions['access site in maintenance mode'] = array(
    'name' => 'access site in maintenance mode',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'system',
  );

  // Exported permission: 'access site reports'.
  $permissions['access site reports'] = array(
    'name' => 'access site reports',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'system',
  );

  // Exported permission: 'access site-wide contact form'.
  $permissions['access site-wide contact form'] = array(
    'name' => 'access site-wide contact form',
    'roles' => array(
      'ARC Collaborator' => 'ARC Collaborator',
      'ARC Member' => 'ARC Member',
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
    ),
    'module' => 'contact',
  );

  // Exported permission: 'access statistics'.
  $permissions['access statistics'] = array(
    'name' => 'access statistics',
    'roles' => array(),
    'module' => 'statistics',
  );

  // Exported permission: 'access user contact forms'.
  $permissions['access user contact forms'] = array(
    'name' => 'access user contact forms',
    'roles' => array(
      'ARC Member' => 'ARC Member',
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
    ),
    'module' => 'contact',
  );

  // Exported permission: 'access user profiles'.
  $permissions['access user profiles'] = array(
    'name' => 'access user profiles',
    'roles' => array(
      'ARC Member' => 'ARC Member',
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
    ),
    'module' => 'user',
  );

  // Exported permission: 'access workflow summary views'.
  $permissions['access workflow summary views'] = array(
    'name' => 'access workflow summary views',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
    ),
    'module' => 'workflow_views',
  );

  // Exported permission: 'add media from remote sources'.
  $permissions['add media from remote sources'] = array(
    'name' => 'add media from remote sources',
    'roles' => array(
      'ARC Collaborator' => 'ARC Collaborator',
      'ARC Member' => 'ARC Member',
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
    ),
    'module' => 'media_internet',
  );

  // Exported permission: 'administer actions'.
  $permissions['administer actions'] = array(
    'name' => 'administer actions',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'system',
  );

  // Exported permission: 'administer annotations'.
  $permissions['administer annotations'] = array(
    'name' => 'administer annotations',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
    ),
    'module' => 'annotator',
  );

  // Exported permission: 'administer backup and migrate'.
  $permissions['administer backup and migrate'] = array(
    'name' => 'administer backup and migrate',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'backup_migrate',
  );

  // Exported permission: 'administer biblio'.
  $permissions['administer biblio'] = array(
    'name' => 'administer biblio',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'biblio',
  );

  // Exported permission: 'administer blocks'.
  $permissions['administer blocks'] = array(
    'name' => 'administer blocks',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'block',
  );

  // Exported permission: 'administer comments'.
  $permissions['administer comments'] = array(
    'name' => 'administer comments',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
    ),
    'module' => 'comment',
  );

  // Exported permission: 'administer contact forms'.
  $permissions['administer contact forms'] = array(
    'name' => 'administer contact forms',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'contact',
  );

  // Exported permission: 'administer content types'.
  $permissions['administer content types'] = array(
    'name' => 'administer content types',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'administer contexts'.
  $permissions['administer contexts'] = array(
    'name' => 'administer contexts',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'context_ui',
  );

  // Exported permission: 'administer features'.
  $permissions['administer features'] = array(
    'name' => 'administer features',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'features',
  );

  // Exported permission: 'administer field permissions'.
  $permissions['administer field permissions'] = array(
    'name' => 'administer field permissions',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'administer filters'.
  $permissions['administer filters'] = array(
    'name' => 'administer filters',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'filter',
  );

  // Exported permission: 'administer flags'.
  $permissions['administer flags'] = array(
    'name' => 'administer flags',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'flag',
  );

  // Exported permission: 'administer group'.
  $permissions['administer group'] = array(
    'name' => 'administer group',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'og',
  );

  // Exported permission: 'administer image styles'.
  $permissions['administer image styles'] = array(
    'name' => 'administer image styles',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'image',
  );

  // Exported permission: 'administer media'.
  $permissions['administer media'] = array(
    'name' => 'administer media',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
    ),
    'module' => 'media',
  );

  // Exported permission: 'administer menu'.
  $permissions['administer menu'] = array(
    'name' => 'administer menu',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'menu',
  );

  // Exported permission: 'administer module filter'.
  $permissions['administer module filter'] = array(
    'name' => 'administer module filter',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'module_filter',
  );

  // Exported permission: 'administer modules'.
  $permissions['administer modules'] = array(
    'name' => 'administer modules',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'system',
  );

  // Exported permission: 'administer nodes'.
  $permissions['administer nodes'] = array(
    'name' => 'administer nodes',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'administer notify'.
  $permissions['administer notify'] = array(
    'name' => 'administer notify',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
    ),
    'module' => 'notify',
  );

  // Exported permission: 'administer notify queue'.
  $permissions['administer notify queue'] = array(
    'name' => 'administer notify queue',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
    ),
    'module' => 'notify',
  );

  // Exported permission: 'administer pathauto'.
  $permissions['administer pathauto'] = array(
    'name' => 'administer pathauto',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'pathauto',
  );

  // Exported permission: 'administer permissions'.
  $permissions['administer permissions'] = array(
    'name' => 'administer permissions',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'user',
  );

  // Exported permission: 'administer popup elements'.
  $permissions['administer popup elements'] = array(
    'name' => 'administer popup elements',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'popup',
  );

  // Exported permission: 'administer realname'.
  $permissions['administer realname'] = array(
    'name' => 'administer realname',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'realname',
  );

  // Exported permission: 'administer rules'.
  $permissions['administer rules'] = array(
    'name' => 'administer rules',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'rules',
  );

  // Exported permission: 'administer search'.
  $permissions['administer search'] = array(
    'name' => 'administer search',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'search',
  );

  // Exported permission: 'administer shortcuts'.
  $permissions['administer shortcuts'] = array(
    'name' => 'administer shortcuts',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'shortcut',
  );

  // Exported permission: 'administer site configuration'.
  $permissions['administer site configuration'] = array(
    'name' => 'administer site configuration',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'system',
  );

  // Exported permission: 'administer software updates'.
  $permissions['administer software updates'] = array(
    'name' => 'administer software updates',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'system',
  );

  // Exported permission: 'administer statistics'.
  $permissions['administer statistics'] = array(
    'name' => 'administer statistics',
    'roles' => array(),
    'module' => 'statistics',
  );

  // Exported permission: 'administer superfish'.
  $permissions['administer superfish'] = array(
    'name' => 'administer superfish',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'superfish',
  );

  // Exported permission: 'administer taxonomy'.
  $permissions['administer taxonomy'] = array(
    'name' => 'administer taxonomy',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: 'administer themes'.
  $permissions['administer themes'] = array(
    'name' => 'administer themes',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'system',
  );

  // Exported permission: 'administer url aliases'.
  $permissions['administer url aliases'] = array(
    'name' => 'administer url aliases',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'path',
  );

  // Exported permission: 'administer users'.
  $permissions['administer users'] = array(
    'name' => 'administer users',
    'roles' => array(
      'ARC Member' => 'ARC Member',
      'administrator' => 'administrator',
    ),
    'module' => 'user',
  );

  // Exported permission: 'administer views'.
  $permissions['administer views'] = array(
    'name' => 'administer views',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'views',
  );

  // Exported permission: 'administer workflow'.
  $permissions['administer workflow'] = array(
    'name' => 'administer workflow',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'workflow_admin_ui',
  );

  // Exported permission: 'block IP addresses'.
  $permissions['block IP addresses'] = array(
    'name' => 'block IP addresses',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'system',
  );

  // Exported permission: 'bypass node access'.
  $permissions['bypass node access'] = array(
    'name' => 'bypass node access',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'bypass rules access'.
  $permissions['bypass rules access'] = array(
    'name' => 'bypass rules access',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'rules',
  );

  // Exported permission: 'cancel account'.
  $permissions['cancel account'] = array(
    'name' => 'cancel account',
    'roles' => array(
      'ARC Collaborator' => 'ARC Collaborator',
      'ARC Member' => 'ARC Member',
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
    ),
    'module' => 'user',
  );

  // Exported permission: 'change own username'.
  $permissions['change own username'] = array(
    'name' => 'change own username',
    'roles' => array(
      'ARC Collaborator' => 'ARC Collaborator',
      'ARC Member' => 'ARC Member',
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
    ),
    'module' => 'user',
  );

  // Exported permission: 'context ajax block access'.
  $permissions['context ajax block access'] = array(
    'name' => 'context ajax block access',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'context_ui',
  );

  // Exported permission: 'create annotation content'.
  $permissions['create annotation content'] = array(
    'name' => 'create annotation content',
    'roles' => array(
      'ARC Collaborator' => 'ARC Collaborator',
      'ARC Member' => 'ARC Member',
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create annotations'.
  $permissions['create annotations'] = array(
    'name' => 'create annotations',
    'roles' => array(
      'ARC Collaborator' => 'ARC Collaborator',
      'ARC Member' => 'ARC Member',
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
    ),
    'module' => 'annotator',
  );

  // Exported permission: 'create article content'.
  $permissions['create article content'] = array(
    'name' => 'create article content',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create biblio content'.
  $permissions['create biblio content'] = array(
    'name' => 'create biblio content',
    'roles' => array(
      'ARC Collaborator' => 'ARC Collaborator',
      'ARC Member' => 'ARC Member',
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create blog content'.
  $permissions['create blog content'] = array(
    'name' => 'create blog content',
    'roles' => array(
      'ARC Collaborator' => 'ARC Collaborator',
      'ARC Member' => 'ARC Member',
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create course content'.
  $permissions['create course content'] = array(
    'name' => 'create course content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'create document content'.
  $permissions['create document content'] = array(
    'name' => 'create document content',
    'roles' => array(
      'ARC Member' => 'ARC Member',
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create field_date_of_birth'.
  $permissions['create field_date_of_birth'] = array(
    'name' => 'create field_date_of_birth',
    'roles' => array(
      'ARC Collaborator' => 'ARC Collaborator',
      'ARC Member' => 'ARC Member',
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
      'anonymous user' => 'anonymous user',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'create field_education'.
  $permissions['create field_education'] = array(
    'name' => 'create field_education',
    'roles' => array(
      'ARC Collaborator' => 'ARC Collaborator',
      'ARC Member' => 'ARC Member',
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
      'anonymous user' => 'anonymous user',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'create field_gender'.
  $permissions['create field_gender'] = array(
    'name' => 'create field_gender',
    'roles' => array(
      'ARC Collaborator' => 'ARC Collaborator',
      'ARC Member' => 'ARC Member',
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
      'anonymous user' => 'anonymous user',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'create field_major_degree'.
  $permissions['create field_major_degree'] = array(
    'name' => 'create field_major_degree',
    'roles' => array(
      'ARC Collaborator' => 'ARC Collaborator',
      'ARC Member' => 'ARC Member',
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
      'anonymous user' => 'anonymous user',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'create field_media'.
  $permissions['create field_media'] = array(
    'name' => 'create field_media',
    'roles' => array(),
    'module' => 'field_permissions',
  );

  // Exported permission: 'create field_status'.
  $permissions['create field_status'] = array(
    'name' => 'create field_status',
    'roles' => array(
      'ARC Member' => 'ARC Member',
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'create field_year_in_program'.
  $permissions['create field_year_in_program'] = array(
    'name' => 'create field_year_in_program',
    'roles' => array(
      'ARC Collaborator' => 'ARC Collaborator',
      'ARC Member' => 'ARC Member',
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
      'anonymous user' => 'anonymous user',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'create og_user_node'.
  $permissions['create og_user_node'] = array(
    'name' => 'create og_user_node',
    'roles' => array(
      'ARC Collaborator' => 'ARC Collaborator',
      'ARC Member' => 'ARC Member',
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
      'anonymous user' => 'anonymous user',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'create page content'.
  $permissions['create page content'] = array(
    'name' => 'create page content',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create thread content'.
  $permissions['create thread content'] = array(
    'name' => 'create thread content',
    'roles' => array(
      'ARC Collaborator' => 'ARC Collaborator',
      'ARC Member' => 'ARC Member',
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create url aliases'.
  $permissions['create url aliases'] = array(
    'name' => 'create url aliases',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'path',
  );

  // Exported permission: 'create webform content'.
  $permissions['create webform content'] = array(
    'name' => 'create webform content',
    'roles' => array(
      'ARC Collaborator' => 'ARC Collaborator',
      'ARC Member' => 'ARC Member',
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'customize shortcut links'.
  $permissions['customize shortcut links'] = array(
    'name' => 'customize shortcut links',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'shortcut',
  );

  // Exported permission: 'delete all webform submissions'.
  $permissions['delete all webform submissions'] = array(
    'name' => 'delete all webform submissions',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'webform',
  );

  // Exported permission: 'delete any annotation content'.
  $permissions['delete any annotation content'] = array(
    'name' => 'delete any annotation content',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any article content'.
  $permissions['delete any article content'] = array(
    'name' => 'delete any article content',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any biblio content'.
  $permissions['delete any biblio content'] = array(
    'name' => 'delete any biblio content',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any blog content'.
  $permissions['delete any blog content'] = array(
    'name' => 'delete any blog content',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any course content'.
  $permissions['delete any course content'] = array(
    'name' => 'delete any course content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'delete any document content'.
  $permissions['delete any document content'] = array(
    'name' => 'delete any document content',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any page content'.
  $permissions['delete any page content'] = array(
    'name' => 'delete any page content',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any thread content'.
  $permissions['delete any thread content'] = array(
    'name' => 'delete any thread content',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any webform content'.
  $permissions['delete any webform content'] = array(
    'name' => 'delete any webform content',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete backup files'.
  $permissions['delete backup files'] = array(
    'name' => 'delete backup files',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'backup_migrate',
  );

  // Exported permission: 'delete own annotation content'.
  $permissions['delete own annotation content'] = array(
    'name' => 'delete own annotation content',
    'roles' => array(
      'ARC Collaborator' => 'ARC Collaborator',
      'ARC Member' => 'ARC Member',
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own article content'.
  $permissions['delete own article content'] = array(
    'name' => 'delete own article content',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own biblio content'.
  $permissions['delete own biblio content'] = array(
    'name' => 'delete own biblio content',
    'roles' => array(
      'ARC Collaborator' => 'ARC Collaborator',
      'ARC Member' => 'ARC Member',
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own blog content'.
  $permissions['delete own blog content'] = array(
    'name' => 'delete own blog content',
    'roles' => array(
      'ARC Collaborator' => 'ARC Collaborator',
      'ARC Member' => 'ARC Member',
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own course content'.
  $permissions['delete own course content'] = array(
    'name' => 'delete own course content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'delete own document content'.
  $permissions['delete own document content'] = array(
    'name' => 'delete own document content',
    'roles' => array(
      'ARC Member' => 'ARC Member',
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own page content'.
  $permissions['delete own page content'] = array(
    'name' => 'delete own page content',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own thread content'.
  $permissions['delete own thread content'] = array(
    'name' => 'delete own thread content',
    'roles' => array(
      'ARC Collaborator' => 'ARC Collaborator',
      'ARC Member' => 'ARC Member',
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own webform content'.
  $permissions['delete own webform content'] = array(
    'name' => 'delete own webform content',
    'roles' => array(
      'ARC Collaborator' => 'ARC Collaborator',
      'ARC Member' => 'ARC Member',
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own webform submissions'.
  $permissions['delete own webform submissions'] = array(
    'name' => 'delete own webform submissions',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'webform',
  );

  // Exported permission: 'delete revisions'.
  $permissions['delete revisions'] = array(
    'name' => 'delete revisions',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete terms in annotation_categories'.
  $permissions['delete terms in annotation_categories'] = array(
    'name' => 'delete terms in annotation_categories',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: 'delete terms in artifact_force_politics_power'.
  $permissions['delete terms in artifact_force_politics_power'] = array(
    'name' => 'delete terms in artifact_force_politics_power',
    'roles' => array(),
    'module' => 'taxonomy',
  );

  // Exported permission: 'delete terms in artifact_intercession'.
  $permissions['delete terms in artifact_intercession'] = array(
    'name' => 'delete terms in artifact_intercession',
    'roles' => array(),
    'module' => 'taxonomy',
  );

  // Exported permission: 'delete terms in artifact_mode'.
  $permissions['delete terms in artifact_mode'] = array(
    'name' => 'delete terms in artifact_mode',
    'roles' => array(),
    'module' => 'taxonomy',
  );

  // Exported permission: 'delete terms in artifact_participation_level'.
  $permissions['delete terms in artifact_participation_level'] = array(
    'name' => 'delete terms in artifact_participation_level',
    'roles' => array(),
    'module' => 'taxonomy',
  );

  // Exported permission: 'delete terms in artifact_privacy_levels'.
  $permissions['delete terms in artifact_privacy_levels'] = array(
    'name' => 'delete terms in artifact_privacy_levels',
    'roles' => array(),
    'module' => 'taxonomy',
  );

  // Exported permission: 'delete terms in artifact_projects'.
  $permissions['delete terms in artifact_projects'] = array(
    'name' => 'delete terms in artifact_projects',
    'roles' => array(),
    'module' => 'taxonomy',
  );

  // Exported permission: 'delete terms in artifact_theme'.
  $permissions['delete terms in artifact_theme'] = array(
    'name' => 'delete terms in artifact_theme',
    'roles' => array(),
    'module' => 'taxonomy',
  );

  // Exported permission: 'delete terms in genre_blog_post'.
  $permissions['delete terms in genre_blog_post'] = array(
    'name' => 'delete terms in genre_blog_post',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: 'delete terms in genre_doc'.
  $permissions['delete terms in genre_doc'] = array(
    'name' => 'delete terms in genre_doc',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: 'delete terms in genre_response'.
  $permissions['delete terms in genre_response'] = array(
    'name' => 'delete terms in genre_response',
    'roles' => array(),
    'module' => 'taxonomy',
  );

  // Exported permission: 'delete terms in media_types'.
  $permissions['delete terms in media_types'] = array(
    'name' => 'delete terms in media_types',
    'roles' => array(),
    'module' => 'taxonomy',
  );

  // Exported permission: 'delete terms in priority'.
  $permissions['delete terms in priority'] = array(
    'name' => 'delete terms in priority',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: 'delete terms in tags'.
  $permissions['delete terms in tags'] = array(
    'name' => 'delete terms in tags',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: 'delete terms in topics'.
  $permissions['delete terms in topics'] = array(
    'name' => 'delete terms in topics',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: 'delete terms in unit'.
  $permissions['delete terms in unit'] = array(
    'name' => 'delete terms in unit',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: 'display drupal links'.
  $permissions['display drupal links'] = array(
    'name' => 'display drupal links',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'admin_menu',
  );

  // Exported permission: 'edit all webform submissions'.
  $permissions['edit all webform submissions'] = array(
    'name' => 'edit all webform submissions',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'webform',
  );

  // Exported permission: 'edit any annotation content'.
  $permissions['edit any annotation content'] = array(
    'name' => 'edit any annotation content',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any annotations'.
  $permissions['edit any annotations'] = array(
    'name' => 'edit any annotations',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
    ),
    'module' => 'annotator',
  );

  // Exported permission: 'edit any article content'.
  $permissions['edit any article content'] = array(
    'name' => 'edit any article content',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any biblio content'.
  $permissions['edit any biblio content'] = array(
    'name' => 'edit any biblio content',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any blog content'.
  $permissions['edit any blog content'] = array(
    'name' => 'edit any blog content',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any course content'.
  $permissions['edit any course content'] = array(
    'name' => 'edit any course content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'edit any document content'.
  $permissions['edit any document content'] = array(
    'name' => 'edit any document content',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any page content'.
  $permissions['edit any page content'] = array(
    'name' => 'edit any page content',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any private annotation'.
  $permissions['edit any private annotation'] = array(
    'name' => 'edit any private annotation',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'annotation',
  );

  // Exported permission: 'edit any thread content'.
  $permissions['edit any thread content'] = array(
    'name' => 'edit any thread content',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any webform content'.
  $permissions['edit any webform content'] = array(
    'name' => 'edit any webform content',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit biblio authors'.
  $permissions['edit biblio authors'] = array(
    'name' => 'edit biblio authors',
    'roles' => array(
      'ARC Member' => 'ARC Member',
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
    ),
    'module' => 'biblio',
  );

  // Exported permission: 'edit by all biblio authors'.
  $permissions['edit by all biblio authors'] = array(
    'name' => 'edit by all biblio authors',
    'roles' => array(
      'ARC Member' => 'ARC Member',
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
    ),
    'module' => 'biblio',
  );

  // Exported permission: 'edit field_date_of_birth'.
  $permissions['edit field_date_of_birth'] = array(
    'name' => 'edit field_date_of_birth',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit field_education'.
  $permissions['edit field_education'] = array(
    'name' => 'edit field_education',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit field_gender'.
  $permissions['edit field_gender'] = array(
    'name' => 'edit field_gender',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit field_major_degree'.
  $permissions['edit field_major_degree'] = array(
    'name' => 'edit field_major_degree',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit field_media'.
  $permissions['edit field_media'] = array(
    'name' => 'edit field_media',
    'roles' => array(),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit field_status'.
  $permissions['edit field_status'] = array(
    'name' => 'edit field_status',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit field_year_in_program'.
  $permissions['edit field_year_in_program'] = array(
    'name' => 'edit field_year_in_program',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit media'.
  $permissions['edit media'] = array(
    'name' => 'edit media',
    'roles' => array(
      'ARC Member' => 'ARC Member',
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
    ),
    'module' => 'media',
  );

  // Exported permission: 'edit og_user_node'.
  $permissions['edit og_user_node'] = array(
    'name' => 'edit og_user_node',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit own annotation content'.
  $permissions['edit own annotation content'] = array(
    'name' => 'edit own annotation content',
    'roles' => array(
      'ARC Collaborator' => 'ARC Collaborator',
      'ARC Member' => 'ARC Member',
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own annotations'.
  $permissions['edit own annotations'] = array(
    'name' => 'edit own annotations',
    'roles' => array(
      'ARC Collaborator' => 'ARC Collaborator',
      'ARC Member' => 'ARC Member',
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
    ),
    'module' => 'annotator',
  );

  // Exported permission: 'edit own article content'.
  $permissions['edit own article content'] = array(
    'name' => 'edit own article content',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own biblio content'.
  $permissions['edit own biblio content'] = array(
    'name' => 'edit own biblio content',
    'roles' => array(
      'ARC Collaborator' => 'ARC Collaborator',
      'ARC Member' => 'ARC Member',
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own blog content'.
  $permissions['edit own blog content'] = array(
    'name' => 'edit own blog content',
    'roles' => array(
      'ARC Collaborator' => 'ARC Collaborator',
      'ARC Member' => 'ARC Member',
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own comments'.
  $permissions['edit own comments'] = array(
    'name' => 'edit own comments',
    'roles' => array(
      'ARC Collaborator' => 'ARC Collaborator',
      'ARC Member' => 'ARC Member',
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
    ),
    'module' => 'comment',
  );

  // Exported permission: 'edit own course content'.
  $permissions['edit own course content'] = array(
    'name' => 'edit own course content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'edit own document content'.
  $permissions['edit own document content'] = array(
    'name' => 'edit own document content',
    'roles' => array(
      'ARC Member' => 'ARC Member',
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own field_date_of_birth'.
  $permissions['edit own field_date_of_birth'] = array(
    'name' => 'edit own field_date_of_birth',
    'roles' => array(
      'ARC Collaborator' => 'ARC Collaborator',
      'ARC Member' => 'ARC Member',
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit own field_education'.
  $permissions['edit own field_education'] = array(
    'name' => 'edit own field_education',
    'roles' => array(
      'ARC Collaborator' => 'ARC Collaborator',
      'ARC Member' => 'ARC Member',
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit own field_gender'.
  $permissions['edit own field_gender'] = array(
    'name' => 'edit own field_gender',
    'roles' => array(
      'ARC Collaborator' => 'ARC Collaborator',
      'ARC Member' => 'ARC Member',
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit own field_major_degree'.
  $permissions['edit own field_major_degree'] = array(
    'name' => 'edit own field_major_degree',
    'roles' => array(
      'ARC Collaborator' => 'ARC Collaborator',
      'ARC Member' => 'ARC Member',
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit own field_media'.
  $permissions['edit own field_media'] = array(
    'name' => 'edit own field_media',
    'roles' => array(),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit own field_status'.
  $permissions['edit own field_status'] = array(
    'name' => 'edit own field_status',
    'roles' => array(
      'ARC Member' => 'ARC Member',
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit own field_year_in_program'.
  $permissions['edit own field_year_in_program'] = array(
    'name' => 'edit own field_year_in_program',
    'roles' => array(
      'ARC Collaborator' => 'ARC Collaborator',
      'ARC Member' => 'ARC Member',
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit own og_user_node'.
  $permissions['edit own og_user_node'] = array(
    'name' => 'edit own og_user_node',
    'roles' => array(
      'ARC Collaborator' => 'ARC Collaborator',
      'ARC Member' => 'ARC Member',
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit own page content'.
  $permissions['edit own page content'] = array(
    'name' => 'edit own page content',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own thread content'.
  $permissions['edit own thread content'] = array(
    'name' => 'edit own thread content',
    'roles' => array(
      'ARC Collaborator' => 'ARC Collaborator',
      'ARC Member' => 'ARC Member',
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own webform content'.
  $permissions['edit own webform content'] = array(
    'name' => 'edit own webform content',
    'roles' => array(
      'ARC Collaborator' => 'ARC Collaborator',
      'ARC Member' => 'ARC Member',
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own webform submissions'.
  $permissions['edit own webform submissions'] = array(
    'name' => 'edit own webform submissions',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'webform',
  );

  // Exported permission: 'edit terms in annotation_categories'.
  $permissions['edit terms in annotation_categories'] = array(
    'name' => 'edit terms in annotation_categories',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: 'edit terms in artifact_force_politics_power'.
  $permissions['edit terms in artifact_force_politics_power'] = array(
    'name' => 'edit terms in artifact_force_politics_power',
    'roles' => array(),
    'module' => 'taxonomy',
  );

  // Exported permission: 'edit terms in artifact_intercession'.
  $permissions['edit terms in artifact_intercession'] = array(
    'name' => 'edit terms in artifact_intercession',
    'roles' => array(),
    'module' => 'taxonomy',
  );

  // Exported permission: 'edit terms in artifact_mode'.
  $permissions['edit terms in artifact_mode'] = array(
    'name' => 'edit terms in artifact_mode',
    'roles' => array(),
    'module' => 'taxonomy',
  );

  // Exported permission: 'edit terms in artifact_participation_level'.
  $permissions['edit terms in artifact_participation_level'] = array(
    'name' => 'edit terms in artifact_participation_level',
    'roles' => array(),
    'module' => 'taxonomy',
  );

  // Exported permission: 'edit terms in artifact_privacy_levels'.
  $permissions['edit terms in artifact_privacy_levels'] = array(
    'name' => 'edit terms in artifact_privacy_levels',
    'roles' => array(),
    'module' => 'taxonomy',
  );

  // Exported permission: 'edit terms in artifact_projects'.
  $permissions['edit terms in artifact_projects'] = array(
    'name' => 'edit terms in artifact_projects',
    'roles' => array(),
    'module' => 'taxonomy',
  );

  // Exported permission: 'edit terms in artifact_theme'.
  $permissions['edit terms in artifact_theme'] = array(
    'name' => 'edit terms in artifact_theme',
    'roles' => array(),
    'module' => 'taxonomy',
  );

  // Exported permission: 'edit terms in genre_blog_post'.
  $permissions['edit terms in genre_blog_post'] = array(
    'name' => 'edit terms in genre_blog_post',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: 'edit terms in genre_doc'.
  $permissions['edit terms in genre_doc'] = array(
    'name' => 'edit terms in genre_doc',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: 'edit terms in genre_response'.
  $permissions['edit terms in genre_response'] = array(
    'name' => 'edit terms in genre_response',
    'roles' => array(),
    'module' => 'taxonomy',
  );

  // Exported permission: 'edit terms in media_types'.
  $permissions['edit terms in media_types'] = array(
    'name' => 'edit terms in media_types',
    'roles' => array(),
    'module' => 'taxonomy',
  );

  // Exported permission: 'edit terms in priority'.
  $permissions['edit terms in priority'] = array(
    'name' => 'edit terms in priority',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: 'edit terms in tags'.
  $permissions['edit terms in tags'] = array(
    'name' => 'edit terms in tags',
    'roles' => array(
      'ARC Collaborator' => 'ARC Collaborator',
      'ARC Member' => 'ARC Member',
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: 'edit terms in topics'.
  $permissions['edit terms in topics'] = array(
    'name' => 'edit terms in topics',
    'roles' => array(
      'ARC Member' => 'ARC Member',
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: 'edit terms in unit'.
  $permissions['edit terms in unit'] = array(
    'name' => 'edit terms in unit',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: 'edit workflow comment'.
  $permissions['edit workflow comment'] = array(
    'name' => 'edit workflow comment',
    'roles' => array(
      'ARC Member' => 'ARC Member',
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
    ),
    'module' => 'workflow',
  );

  // Exported permission: 'flag irb_form_completed'.
  $permissions['flag irb_form_completed'] = array(
    'name' => 'flag irb_form_completed',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'flag',
  );

  // Exported permission: 'flush caches'.
  $permissions['flush caches'] = array(
    'name' => 'flush caches',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
    ),
    'module' => 'admin_menu',
  );

  // Exported permission: 'generate features'.
  $permissions['generate features'] = array(
    'name' => 'generate features',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'features',
  );

  // Exported permission: 'grant content access'.
  $permissions['grant content access'] = array(
    'name' => 'grant content access',
    'roles' => array(),
    'module' => 'content_access',
  );

  // Exported permission: 'grant own content access'.
  $permissions['grant own content access'] = array(
    'name' => 'grant own content access',
    'roles' => array(),
    'module' => 'content_access',
  );

  // Exported permission: 'import from file'.
  $permissions['import from file'] = array(
    'name' => 'import from file',
    'roles' => array(
      'ARC Member' => 'ARC Member',
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
    ),
    'module' => 'biblio',
  );

  // Exported permission: 'import media'.
  $permissions['import media'] = array(
    'name' => 'import media',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
    ),
    'module' => 'media',
  );

  // Exported permission: 'manage features'.
  $permissions['manage features'] = array(
    'name' => 'manage features',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'features',
  );

  // Exported permission: 'notify of path changes'.
  $permissions['notify of path changes'] = array(
    'name' => 'notify of path changes',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'pathauto',
  );

  // Exported permission: 'participate in workflow'.
  $permissions['participate in workflow'] = array(
    'name' => 'participate in workflow',
    'roles' => array(
      'ARC Collaborator' => 'ARC Collaborator',
      'ARC Member' => 'ARC Member',
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
    ),
    'module' => 'workflow',
  );

  // Exported permission: 'perform backup'.
  $permissions['perform backup'] = array(
    'name' => 'perform backup',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'backup_migrate',
  );

  // Exported permission: 'post comments'.
  $permissions['post comments'] = array(
    'name' => 'post comments',
    'roles' => array(
      'ARC Collaborator' => 'ARC Collaborator',
      'ARC Member' => 'ARC Member',
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
    ),
    'module' => 'comment',
  );

  // Exported permission: 'publish any content'.
  $permissions['publish any content'] = array(
    'name' => 'publish any content',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
    ),
    'module' => 'publishcontent',
  );

  // Exported permission: 'publish editable content'.
  $permissions['publish editable content'] = array(
    'name' => 'publish editable content',
    'roles' => array(
      'ARC Collaborator' => 'ARC Collaborator',
      'ARC Member' => 'ARC Member',
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
    ),
    'module' => 'publishcontent',
  );

  // Exported permission: 'rename features'.
  $permissions['rename features'] = array(
    'name' => 'rename features',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'features',
  );

  // Exported permission: 'restore from backup'.
  $permissions['restore from backup'] = array(
    'name' => 'restore from backup',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'backup_migrate',
  );

  // Exported permission: 'revert revisions'.
  $permissions['revert revisions'] = array(
    'name' => 'revert revisions',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'schedule workflow transitions'.
  $permissions['schedule workflow transitions'] = array(
    'name' => 'schedule workflow transitions',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
    ),
    'module' => 'workflow',
  );

  // Exported permission: 'search content'.
  $permissions['search content'] = array(
    'name' => 'search content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'search',
  );

  // Exported permission: 'select account cancellation method'.
  $permissions['select account cancellation method'] = array(
    'name' => 'select account cancellation method',
    'roles' => array(
      'ARC Collaborator' => 'ARC Collaborator',
      'ARC Member' => 'ARC Member',
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
    ),
    'module' => 'user',
  );

  // Exported permission: 'show download links'.
  $permissions['show download links'] = array(
    'name' => 'show download links',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'biblio',
  );

  // Exported permission: 'show export links'.
  $permissions['show export links'] = array(
    'name' => 'show export links',
    'roles' => array(
      'ARC Collaborator' => 'ARC Collaborator',
      'ARC Member' => 'ARC Member',
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
    ),
    'module' => 'biblio',
  );

  // Exported permission: 'show filter tab'.
  $permissions['show filter tab'] = array(
    'name' => 'show filter tab',
    'roles' => array(
      'ARC Collaborator' => 'ARC Collaborator',
      'ARC Member' => 'ARC Member',
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
    ),
    'module' => 'biblio',
  );

  // Exported permission: 'show own download links'.
  $permissions['show own download links'] = array(
    'name' => 'show own download links',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'biblio',
  );

  // Exported permission: 'show sort links'.
  $permissions['show sort links'] = array(
    'name' => 'show sort links',
    'roles' => array(
      'ARC Collaborator' => 'ARC Collaborator',
      'ARC Member' => 'ARC Member',
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
    ),
    'module' => 'biblio',
  );

  // Exported permission: 'show workflow state form'.
  $permissions['show workflow state form'] = array(
    'name' => 'show workflow state form',
    'roles' => array(
      'ARC Member' => 'ARC Member',
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
    ),
    'module' => 'workflow',
  );

  // Exported permission: 'skip comment approval'.
  $permissions['skip comment approval'] = array(
    'name' => 'skip comment approval',
    'roles' => array(
      'ARC Collaborator' => 'ARC Collaborator',
      'ARC Member' => 'ARC Member',
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
    ),
    'module' => 'comment',
  );

  // Exported permission: 'switch shortcut sets'.
  $permissions['switch shortcut sets'] = array(
    'name' => 'switch shortcut sets',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'shortcut',
  );

  // Exported permission: 'unflag irb_form_completed'.
  $permissions['unflag irb_form_completed'] = array(
    'name' => 'unflag irb_form_completed',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'flag',
  );

  // Exported permission: 'unpublish any content'.
  $permissions['unpublish any content'] = array(
    'name' => 'unpublish any content',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
    ),
    'module' => 'publishcontent',
  );

  // Exported permission: 'unpublish editable content'.
  $permissions['unpublish editable content'] = array(
    'name' => 'unpublish editable content',
    'roles' => array(
      'ARC Collaborator' => 'ARC Collaborator',
      'ARC Member' => 'ARC Member',
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
    ),
    'module' => 'publishcontent',
  );

  // Exported permission: 'use PHP for settings'.
  $permissions['use PHP for settings'] = array(
    'name' => 'use PHP for settings',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'php',
  );

  // Exported permission: 'use advanced search'.
  $permissions['use advanced search'] = array(
    'name' => 'use advanced search',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'search',
  );

  // Exported permission: 'use flag import'.
  $permissions['use flag import'] = array(
    'name' => 'use flag import',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'flag',
  );

  // Exported permission: 'use text format filtered_html'.
  $permissions['use text format filtered_html'] = array(
    'name' => 'use text format filtered_html',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'filter',
  );

  // Exported permission: 'use text format full_html'.
  $permissions['use text format full_html'] = array(
    'name' => 'use text format full_html',
    'roles' => array(
      'ARC Collaborator' => 'ARC Collaborator',
      'ARC Member' => 'ARC Member',
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
    ),
    'module' => 'filter',
  );

  // Exported permission: 'use text format php_code'.
  $permissions['use text format php_code'] = array(
    'name' => 'use text format php_code',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'filter',
  );

  // Exported permission: 'view advanced help index'.
  $permissions['view advanced help index'] = array(
    'name' => 'view advanced help index',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'advanced_help',
  );

  // Exported permission: 'view advanced help popup'.
  $permissions['view advanced help popup'] = array(
    'name' => 'view advanced help popup',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'advanced_help',
  );

  // Exported permission: 'view advanced help topic'.
  $permissions['view advanced help topic'] = array(
    'name' => 'view advanced help topic',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'advanced_help',
  );

  // Exported permission: 'view annotations'.
  $permissions['view annotations'] = array(
    'name' => 'view annotations',
    'roles' => array(
      'ARC Collaborator' => 'ARC Collaborator',
      'ARC Member' => 'ARC Member',
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
    ),
    'module' => 'annotator',
  );

  // Exported permission: 'view field_date_of_birth'.
  $permissions['view field_date_of_birth'] = array(
    'name' => 'view field_date_of_birth',
    'roles' => array(
      'ARC Member' => 'ARC Member',
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view field_education'.
  $permissions['view field_education'] = array(
    'name' => 'view field_education',
    'roles' => array(
      'ARC Member' => 'ARC Member',
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view field_gender'.
  $permissions['view field_gender'] = array(
    'name' => 'view field_gender',
    'roles' => array(
      'ARC Member' => 'ARC Member',
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view field_major_degree'.
  $permissions['view field_major_degree'] = array(
    'name' => 'view field_major_degree',
    'roles' => array(
      'ARC Member' => 'ARC Member',
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view field_media'.
  $permissions['view field_media'] = array(
    'name' => 'view field_media',
    'roles' => array(),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view field_status'.
  $permissions['view field_status'] = array(
    'name' => 'view field_status',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view field_year_in_program'.
  $permissions['view field_year_in_program'] = array(
    'name' => 'view field_year_in_program',
    'roles' => array(
      'ARC Member' => 'ARC Member',
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view full text'.
  $permissions['view full text'] = array(
    'name' => 'view full text',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'biblio',
  );

  // Exported permission: 'view media'.
  $permissions['view media'] = array(
    'name' => 'view media',
    'roles' => array(
      'ARC Collaborator' => 'ARC Collaborator',
      'ARC Member' => 'ARC Member',
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'media',
  );

  // Exported permission: 'view og_user_node'.
  $permissions['view og_user_node'] = array(
    'name' => 'view og_user_node',
    'roles' => array(
      'ARC Member' => 'ARC Member',
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view own field_date_of_birth'.
  $permissions['view own field_date_of_birth'] = array(
    'name' => 'view own field_date_of_birth',
    'roles' => array(
      'ARC Collaborator' => 'ARC Collaborator',
      'ARC Member' => 'ARC Member',
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view own field_education'.
  $permissions['view own field_education'] = array(
    'name' => 'view own field_education',
    'roles' => array(
      'ARC Collaborator' => 'ARC Collaborator',
      'ARC Member' => 'ARC Member',
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view own field_gender'.
  $permissions['view own field_gender'] = array(
    'name' => 'view own field_gender',
    'roles' => array(
      'ARC Collaborator' => 'ARC Collaborator',
      'ARC Member' => 'ARC Member',
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view own field_major_degree'.
  $permissions['view own field_major_degree'] = array(
    'name' => 'view own field_major_degree',
    'roles' => array(
      'ARC Collaborator' => 'ARC Collaborator',
      'ARC Member' => 'ARC Member',
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view own field_media'.
  $permissions['view own field_media'] = array(
    'name' => 'view own field_media',
    'roles' => array(),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view own field_status'.
  $permissions['view own field_status'] = array(
    'name' => 'view own field_status',
    'roles' => array(
      'ARC Member' => 'ARC Member',
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view own field_year_in_program'.
  $permissions['view own field_year_in_program'] = array(
    'name' => 'view own field_year_in_program',
    'roles' => array(
      'ARC Collaborator' => 'ARC Collaborator',
      'ARC Member' => 'ARC Member',
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view own og_user_node'.
  $permissions['view own og_user_node'] = array(
    'name' => 'view own og_user_node',
    'roles' => array(
      'ARC Collaborator' => 'ARC Collaborator',
      'ARC Member' => 'ARC Member',
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view own unpublished content'.
  $permissions['view own unpublished content'] = array(
    'name' => 'view own unpublished content',
    'roles' => array(
      'ARC Collaborator' => 'ARC Collaborator',
      'ARC Member' => 'ARC Member',
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'view post access counter'.
  $permissions['view post access counter'] = array(
    'name' => 'view post access counter',
    'roles' => array(),
    'module' => 'statistics',
  );

  // Exported permission: 'view revisions'.
  $permissions['view revisions'] = array(
    'name' => 'view revisions',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'view the administration theme'.
  $permissions['view the administration theme'] = array(
    'name' => 'view the administration theme',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'system',
  );

  return $permissions;
}
