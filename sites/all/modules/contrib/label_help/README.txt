Label Help
=========
The Label Help module provides a way of adding help text to Drupal form fields
which appears below the form label but above the form field itself.

Installation
============
1. Install & enable the module.

2. When editing a form field using Drupal's Field UI user interface for the Field API,
   you'll see an option named 'Label help message' that lets you enter help text which will
   appear below the label for that field.

3. This module does _not_ affect the placement of the 'Help text' field that normally
   goes _below_ the form field. You could therefore have separate help text appearing
   in both places. Most people will probably want to leave put text in one place and
   leave the other option blank.

Using Label Help to create form fields programmatically
=======================================================

The Label Help field defines a theme option named 'description at top' which can be used
to insert label help text in form fields that are defined programmatically. The following
function would therefore define a form with label help text at the top of field 'example':

function mymodule_form($form, &$form_state) {
  $form['example'] = array(
    '#type' => 'textfield',
    '#title' => t('Example'),
    '#theme_options' => array(
      'description at top' => t('Label help text for the example field.'),
    ),
  );
  return $form;
}

Modifying form fields using hook_form_alter()
=============================================

Drupal's hook_form_alter() functions can be used either inside a custom module or in
the template.php file in your site theme to add Label Help text to existing form fields.
For example, the following function uses hook_form_user_login_alter() to change Drupal's
user login form so that it displays label text top of field 'example':

function mymodule_form_user_login_alter(&$form, &$form_state, $form_id) {
  $form['name']['#theme_options'] = array(
    'description at top' => t('Enter your @s username.', array('@s' => variable_get('site_name', 'Drupal'))),
  );
  unset($form['name']['#description']);
  $form['pass']['#theme_options'] = array(
    'description at top' => t('Enter the password that accompanies your username.'),
  );
  unset($form['pass']['#description']);
}

