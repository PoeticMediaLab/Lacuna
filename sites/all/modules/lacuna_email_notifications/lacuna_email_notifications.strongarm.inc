<?php
/**
 * @file
 * lacuna_email_notifications.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function lacuna_email_notifications_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'mail_system';
  $strongarm->value = array(
    'default-system' => 'MimeMailSystem',
    'rules' => 'MaillogMailSystem',
    'maillog' => 'MaillogMailSystem',
    'mimemail' => 'MimeMailSystem',
    'mimemail_example' => 'MimeMailSystem',
  );
  $export['mail_system'] = $strongarm;

  return $export;
}
