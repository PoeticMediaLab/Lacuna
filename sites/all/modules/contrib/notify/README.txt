NOTIFY README.txt
=================


CONTENTS OF THIS FILE
---------------------

* Introduction
* Requirements
* Installation
* Configuration
  - Administration form
  - User's settings
* Testing
* Maintainers


INTRODUCTION
------------

Notify is a simple, lightweight notification module. It provides
e-mail notifications to subscribers about updates and changes to the
Drupal web site.

* For a full description of the module, visit the project page:
  https://drupal.org/project/notify

* To submit bug reports and feature suggestions, or to track changes:
  https://drupal.org/project/issues/notify

If you enable node revisions (http://drupal.org/node/320614), the
notification e-mail will also mention the name of the last person to
edit the node.


REQUIREMENTS
------------

This module requires a supported version of Drupal and cron to be
running.


INSTALLATION
------------

1. Extract the notify project directory into the directory where you
   keep contributed modules (e.g. sites/all/modules/).

2. Enable the notify module on the Modules list page.  The database
   tables will be created automagically for you at this point.

3. Run the update script if you're upgrading from 7.x-1.0-alpha1.

4. Modify permissions on the People » Permissions page.

   To adminster the notify main settings and user notfification
   settings, grant the permission "administer notify".

   To adminster the notificaton queue (flush and truncate), grant the
   permission "administer notify queue".

   To set the notification checkbox default on new user registration
   form, or let new users opt in for notifications during
   registration, you must grant the anonymous user the right to
   "access notify".  To allow users to control their own notification
   settings (recommended) you must also grant authenticated users the
   right to "access notify".

5. Configure the other general notification settings.

   See the "Administration form" section below for details.

Notify will not automatically subscribe anyone to notifications upon
installation.  Before anyone is subscribed, no notifications will be
sent.


CONFIGURATION
-------------

Administration form
-------------------

The administrative interface is at: Administer » Configuration »
People » Notification settings.

There are four tabs:

1. Settings: All the main options for this module.
2. Defaults: Default settings for new users.
3. Queue: Process and inspect the notification queue.
4. Users: Review and alter per-user settings.


Settings

The Settings tab allow you to configure how the module shall work.

You can specify how often notifications are sent, the hour to send
them (if the frequency is one day or greater), the number of failed
sends after which notifications are disabled, and the maximum number
of notifications to send out per cron run.

When setting how often notifications are sent, note that e-mail
updates can only happen as frequently as the cron is set to run.

To reset the count of failed sends to zero, look at the notification
settings in the user's profile and save it press "Save settings"
(there is no need to change anything).

If you check "Include updated posts in notifications", any change to a
node or content will cause it to be included in the next notification.
Note that even minor changes, such as correcting a trivial typo or
setting or unsetting the "sticky" attribute for the node will flag it
as updated, so use this option with caution in order to avoid excess
notificatons.

If you check "Exclude contents from unverified authors from user
notifications", notify will not notify about postings from unverified
(i.e. anonymous) authors.  You need only care about this setting if
you you permit postings from anonymous authors.  Even if you have spam
protection in the shape of CAPTCHA or other measures, you may
experience that some spammers still manage to post contents on your
site.  By checking this setting, you will at least save your
subscribers from being notified about spam.  As with most of these
settings, it doesn't apply to administrators. Even when checked
administrators will be notified, in order to intervene and delete the
spam before it gets much exposure.  Note that if you check this
settings, there is currently no keeping track of the content that is
excluded due this setting.  If you use it, your users will never
receive any notification email about new content from unverified
authors.  That's not a bug, it is a feature.

If you check "Administrators shall be notified about unpublished
content", users belonging to roles with the "administer nodes" and
"administer comments" permissions granted will receive notifications
about unpublished content.  This is mainly to make the module useful
to manage moderation queues.  Note that notifications about
unpublished content are only sent once.

If you've set up a multilingual site, there should also be three radio
buttons that allow you to filter notifications about new nodes against
the user's language setting (may be set by editing the user profile).
The first setting ("All contents") will notify a user about all new
content on the site. If a piece of contents exists in more than one
language, all versions will be notified about.  The setting "Contents
in the user's preferred language + contents not yet translated" will
notify about content in the user's preferred language and also about
content that is in some other language if no translation of it
exists. The last setting, "Only contents in the user's preferred
language ", will only notify about new contents in the user's
preferred language.  However, please note that new contents that are
marked as "language neutral" will always be included in notifications.
The multilingual settings do not apply to administrators.
Administrators will always be notified about all new contents.  Note
that if you use the second setting, contents that is not in the user's
preferred language will be excluded from the notification if some
translation of exists, even if that translation is not to the user's
preferred language.

The "Watchdog log level" setting lets you specify how much to log.
The setting "All" will make a log record of every notification mail
sent.  The setting "Failures+Summary" will only log failed
notification attempts. It will also insert a summary of how many sent
and how many failures at the end of each batch.  The "Failures"
setting will omit the summary.  The "Nothing" setting will turn of
logging for Notify.


Queue

The Queue tab is to process and inspect the notification queue.

The radio buttons below the heading "Process notification queue" has
the following meanings:

 - Send batch now: Force sending a notification batch without waiting
   for the next cron run.  Note that if the number of notifications
   queue exceeds the maximum number of notifications to send out per
   cron run, only the maximum number is sent.  The rest will be queued
   for the next cron run or the next manual send batch (whatever
   happens first).

 - Truncate queue: Truncate the queue of pending notifications without
   sending out any notifications.

The status panel gives the administrator a rough overview of the
current state of the notification queue.


Defaults

The checkbox under "Notification default for new users" is used as the
default value for the notification master switch on the new user
registration.  Note that this setting has no effect unless you grant
the anonymous user the right to access notify.

The "Initial settings panel" let you set up the initial settings that
will apply to new users registering, and to users that are enrolled in
notifications with batch subscription. These settings have no effect
on users that already have the master switch set to "Enabled".

The final panel under the Settings tab let you set up notification
subscriptions by node type.  Having nothing checked defaults to making
all content types available for subscription.


Users

The Users tab is to review and alter per-user settings for those users
that have the master switch for notifications set to "Enabled".

If you tick the box "Bulk subscribe all users", all non-blocked users
that do not already subscribe to notifications will be subscribed with
the initial settings set under the deafult tab.


User's settings
---------------

To manage your own notification preferences, click on the
"Notification settings" tab on your "My account" page.

The "Master switch" overrides all other settings for Notify. You can
use it to suspend notifications without having to disturb any of your
settings under "Detailed settings" and "Subscriptions".

The "Detailed settings" determine what is included in each
notification.  You can turn on or off notification of new content and
new comments, and specify how much of the original content to include
in the notification email.

The "Subscriptions" panel allow each user to manage individual
notifications by content type.

Note that for users with the permission "administer notify queue", it
is possible to subscribe to content types that is not generally
available for subscription.  This allows administrators to monitor all
new content on the site, without making it subscribable for
non-administrators.


TESTING
-------

The file notify.test contains a test suite for Notify that make use of
the core Testing module.  See comments inside the file for details
about the individual tests.


MAINTAINERS
-----------

Kjartan Mannes <kjartan@drop.org> is the original author.

Rob Barreca <rob@electronicinsight.com> was a previous maintainer.

Matt Chapman <matt@ninjitsuweb.com> is the current maintainer.

Marton Bodonyi (http://www.interactivejunky.com/),
Mark Lindsey,
John Oltman <john.oltman@sitebasin.com>,
Ward Poelmans <wpoely86@gmail.com>,
Ishmael Sanchez (http://ishmaelsanchez.com),
Ajit Shinde (https://www.facebook.com/shinde.ajit), and 
Gisle Hannemyr <gisle@hannemyr.no> contributed to the Drupal 7 port.
