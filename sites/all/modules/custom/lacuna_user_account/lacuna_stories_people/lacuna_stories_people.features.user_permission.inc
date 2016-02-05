<?php
/**
 * @file
 * lacuna_stories_people.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function lacuna_stories_people_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'access notify'.
  $permissions['access notify'] = array(
    'name' => 'access notify',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'Instructor' => 'Instructor',
      'Site Administrator' => 'Site Administrator',
      'Student' => 'Student',
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'notify',
  );

  // Exported permission: 'access site-wide contact form'.
  $permissions['access site-wide contact form'] = array(
    'name' => 'access site-wide contact form',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'Site Administrator' => 'Site Administrator',
      'Student' => 'Student',
    ),
    'module' => 'contact',
  );

  // Exported permission: 'access user contact forms'.
  $permissions['access user contact forms'] = array(
    'name' => 'access user contact forms',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'Instructor' => 'Instructor',
      'Site Administrator' => 'Site Administrator',
    ),
    'module' => 'contact',
  );

  // Exported permission: 'access user profiles'.
  $permissions['access user profiles'] = array(
    'name' => 'access user profiles',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'Instructor' => 'Instructor',
      'Site Administrator' => 'Site Administrator',
      'Student' => 'Student',
    ),
    'module' => 'user',
  );

  // Exported permission: 'administer contact forms'.
  $permissions['administer contact forms'] = array(
    'name' => 'administer contact forms',
    'roles' => array(
      'Site Administrator' => 'Site Administrator',
    ),
    'module' => 'contact',
  );

  // Exported permission: 'administer notify'.
  $permissions['administer notify'] = array(
    'name' => 'administer notify',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'Site Administrator' => 'Site Administrator',
    ),
    'module' => 'notify',
  );

  // Exported permission: 'administer notify queue'.
  $permissions['administer notify queue'] = array(
    'name' => 'administer notify queue',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'Site Administrator' => 'Site Administrator',
    ),
    'module' => 'notify',
  );

  // Exported permission: 'administer permissions'.
  $permissions['administer permissions'] = array(
    'name' => 'administer permissions',
    'roles' => array(
      'Site Administrator' => 'Site Administrator',
    ),
    'module' => 'user',
  );

  // Exported permission: 'administer realname'.
  $permissions['administer realname'] = array(
    'name' => 'administer realname',
    'roles' => array(
      'Site Administrator' => 'Site Administrator',
    ),
    'module' => 'realname',
  );

  // Exported permission: 'administer users'.
  $permissions['administer users'] = array(
    'name' => 'administer users',
    'roles' => array(
      'Site Administrator' => 'Site Administrator',
    ),
    'module' => 'user',
  );

  // Exported permission: 'cancel account'.
  $permissions['cancel account'] = array(
    'name' => 'cancel account',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'Instructor' => 'Instructor',
      'Site Administrator' => 'Site Administrator',
      'Student' => 'Student',
    ),
    'module' => 'user',
  );

  // Exported permission: 'change own username'.
  $permissions['change own username'] = array(
    'name' => 'change own username',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'Instructor' => 'Instructor',
      'Site Administrator' => 'Site Administrator',
      'Student' => 'Student',
    ),
    'module' => 'user',
  );

  // Exported permission: 'create field_about_me'.
  $permissions['create field_about_me'] = array(
    'name' => 'create field_about_me',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'create field_date_of_birth'.
  $permissions['create field_date_of_birth'] = array(
    'name' => 'create field_date_of_birth',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'Instructor' => 'Instructor',
      'Site Administrator' => 'Site Administrator',
      'Student' => 'Student',
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'create field_education'.
  $permissions['create field_education'] = array(
    'name' => 'create field_education',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'Instructor' => 'Instructor',
      'Site Administrator' => 'Site Administrator',
      'Student' => 'Student',
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'create field_gender'.
  $permissions['create field_gender'] = array(
    'name' => 'create field_gender',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'Instructor' => 'Instructor',
      'Site Administrator' => 'Site Administrator',
      'Student' => 'Student',
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'create field_how_i_learn'.
  $permissions['create field_how_i_learn'] = array(
    'name' => 'create field_how_i_learn',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'create field_learning_goals'.
  $permissions['create field_learning_goals'] = array(
    'name' => 'create field_learning_goals',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'create field_major_degree'.
  $permissions['create field_major_degree'] = array(
    'name' => 'create field_major_degree',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'Instructor' => 'Instructor',
      'Site Administrator' => 'Site Administrator',
      'Student' => 'Student',
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'create field_year_in_program'.
  $permissions['create field_year_in_program'] = array(
    'name' => 'create field_year_in_program',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'Instructor' => 'Instructor',
      'Site Administrator' => 'Site Administrator',
      'Student' => 'Student',
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit field_about_me'.
  $permissions['edit field_about_me'] = array(
    'name' => 'edit field_about_me',
    'roles' => array(
      'Site Administrator' => 'Site Administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit field_date_of_birth'.
  $permissions['edit field_date_of_birth'] = array(
    'name' => 'edit field_date_of_birth',
    'roles' => array(
      'Site Administrator' => 'Site Administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit field_education'.
  $permissions['edit field_education'] = array(
    'name' => 'edit field_education',
    'roles' => array(
      'Site Administrator' => 'Site Administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit field_gender'.
  $permissions['edit field_gender'] = array(
    'name' => 'edit field_gender',
    'roles' => array(
      'Site Administrator' => 'Site Administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit field_how_i_learn'.
  $permissions['edit field_how_i_learn'] = array(
    'name' => 'edit field_how_i_learn',
    'roles' => array(
      'Site Administrator' => 'Site Administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit field_learning_goals'.
  $permissions['edit field_learning_goals'] = array(
    'name' => 'edit field_learning_goals',
    'roles' => array(
      'Site Administrator' => 'Site Administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit field_major_degree'.
  $permissions['edit field_major_degree'] = array(
    'name' => 'edit field_major_degree',
    'roles' => array(
      'Site Administrator' => 'Site Administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit field_year_in_program'.
  $permissions['edit field_year_in_program'] = array(
    'name' => 'edit field_year_in_program',
    'roles' => array(
      'Site Administrator' => 'Site Administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit own field_about_me'.
  $permissions['edit own field_about_me'] = array(
    'name' => 'edit own field_about_me',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit own field_date_of_birth'.
  $permissions['edit own field_date_of_birth'] = array(
    'name' => 'edit own field_date_of_birth',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'Instructor' => 'Instructor',
      'Site Administrator' => 'Site Administrator',
      'Student' => 'Student',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit own field_education'.
  $permissions['edit own field_education'] = array(
    'name' => 'edit own field_education',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'Instructor' => 'Instructor',
      'Site Administrator' => 'Site Administrator',
      'Student' => 'Student',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit own field_gender'.
  $permissions['edit own field_gender'] = array(
    'name' => 'edit own field_gender',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'Instructor' => 'Instructor',
      'Site Administrator' => 'Site Administrator',
      'Student' => 'Student',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit own field_how_i_learn'.
  $permissions['edit own field_how_i_learn'] = array(
    'name' => 'edit own field_how_i_learn',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit own field_learning_goals'.
  $permissions['edit own field_learning_goals'] = array(
    'name' => 'edit own field_learning_goals',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit own field_major_degree'.
  $permissions['edit own field_major_degree'] = array(
    'name' => 'edit own field_major_degree',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'Instructor' => 'Instructor',
      'Site Administrator' => 'Site Administrator',
      'Student' => 'Student',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit own field_year_in_program'.
  $permissions['edit own field_year_in_program'] = array(
    'name' => 'edit own field_year_in_program',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'Instructor' => 'Instructor',
      'Site Administrator' => 'Site Administrator',
      'Student' => 'Student',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'select account cancellation method'.
  $permissions['select account cancellation method'] = array(
    'name' => 'select account cancellation method',
    'roles' => array(
      'Site Administrator' => 'Site Administrator',
    ),
    'module' => 'user',
  );

  // Exported permission: 'view field_about_me'.
  $permissions['view field_about_me'] = array(
    'name' => 'view field_about_me',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view field_date_of_birth'.
  $permissions['view field_date_of_birth'] = array(
    'name' => 'view field_date_of_birth',
    'roles' => array(
      'Instructor' => 'Instructor',
      'Site Administrator' => 'Site Administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view field_education'.
  $permissions['view field_education'] = array(
    'name' => 'view field_education',
    'roles' => array(
      'Instructor' => 'Instructor',
      'Site Administrator' => 'Site Administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view field_gender'.
  $permissions['view field_gender'] = array(
    'name' => 'view field_gender',
    'roles' => array(
      'Instructor' => 'Instructor',
      'Site Administrator' => 'Site Administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view field_how_i_learn'.
  $permissions['view field_how_i_learn'] = array(
    'name' => 'view field_how_i_learn',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'Instructor' => 'Instructor',
      'Site Administrator' => 'Site Administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view field_learning_goals'.
  $permissions['view field_learning_goals'] = array(
    'name' => 'view field_learning_goals',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'Instructor' => 'Instructor',
      'Site Administrator' => 'Site Administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view field_major_degree'.
  $permissions['view field_major_degree'] = array(
    'name' => 'view field_major_degree',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'Instructor' => 'Instructor',
      'Site Administrator' => 'Site Administrator',
      'Student' => 'Student',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view field_year_in_program'.
  $permissions['view field_year_in_program'] = array(
    'name' => 'view field_year_in_program',
    'roles' => array(
      'Instructor' => 'Instructor',
      'Site Administrator' => 'Site Administrator',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view own field_about_me'.
  $permissions['view own field_about_me'] = array(
    'name' => 'view own field_about_me',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view own field_date_of_birth'.
  $permissions['view own field_date_of_birth'] = array(
    'name' => 'view own field_date_of_birth',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'Instructor' => 'Instructor',
      'Site Administrator' => 'Site Administrator',
      'Student' => 'Student',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view own field_education'.
  $permissions['view own field_education'] = array(
    'name' => 'view own field_education',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'Instructor' => 'Instructor',
      'Site Administrator' => 'Site Administrator',
      'Student' => 'Student',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view own field_gender'.
  $permissions['view own field_gender'] = array(
    'name' => 'view own field_gender',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'Instructor' => 'Instructor',
      'Site Administrator' => 'Site Administrator',
      'Student' => 'Student',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view own field_how_i_learn'.
  $permissions['view own field_how_i_learn'] = array(
    'name' => 'view own field_how_i_learn',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view own field_learning_goals'.
  $permissions['view own field_learning_goals'] = array(
    'name' => 'view own field_learning_goals',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view own field_major_degree'.
  $permissions['view own field_major_degree'] = array(
    'name' => 'view own field_major_degree',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'Instructor' => 'Instructor',
      'Site Administrator' => 'Site Administrator',
      'Student' => 'Student',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'view own field_year_in_program'.
  $permissions['view own field_year_in_program'] = array(
    'name' => 'view own field_year_in_program',
    'roles' => array(
      'Content Manager' => 'Content Manager',
      'Instructor' => 'Instructor',
      'Site Administrator' => 'Site Administrator',
      'Student' => 'Student',
    ),
    'module' => 'field_permissions',
  );

  return $permissions;
}
