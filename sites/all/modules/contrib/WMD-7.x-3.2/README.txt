WMD - WebAuth Module for Drupal 7.x

-- SUMMARY --

Authors: Ken Sharp, Steve Rude, Josh Koenig, Marco Wise, Brad Erickson

The WebAuth Module for Drupal (also known as WMD) implements external logins
using Stanford's WebAuth. It automatically creates new users accounts and
assigns them Drupal roles based on mappings between Workgroups and Roles as
specified by the administrator.

For a full description of the module, visit the project page:
  https://github.com/mistermarco/WMD/

To submit bug reports and feature suggestions, or to track changes:
  https://github.com/mistermarco/WMD/issues

-- LICENSE --

See the LICENSE file.

-- REQUIREMENTS --

The WebAuth module for Drupal will only work properly on a server that has the
WebAuth module for Apache and the WebAuth LDAP module for Apache installed and
properly configured. This includes Stanford's central Web infrastructure
(www.stanford.edu) and most of IT Services-maintained web servers.
If you are hosting a Drupal site on www.stanford.edu, you are set.

If you are installing the Apached module on your own server see
http://webauth.stanford.edu/ for more information. The developers of the
Drupal module don't have access to help you install the Apache module.

We strongly suggest you also install and enable the Content Access module
(http://drupal.org/project/content_access)


-- INSTALLATION --

Download and extract the module's package in your sites/all/modules directory.
As an admin, go to Administer > Site building > Modules to enable the module.
More detailed information on installing modules here: http://drupal.org/node/70151

At install time, WebAuth will do the following for you:
* create a webauth directory for its files under /sites/default/webauth
  or under /sites/<name-of-site>/webauth for multi-site installs.
  You might need to create this directory manually if the web server can't
  write to /sites/default or sites/<name-of-site>
* create roles for SUNet User, Student, Staff and Faculty
* create mappings from the appropriate workgroups to the roles it created
* add a login link to the login block
* allow any valid user with a SUNet ID to login to your site using WebAuth

-- CONFIGURATION --

Configure the module's behavior at Administer > Site Configuration > WebAuth.

WebAuth Settings is where you can enable or disable local Drupal accounts,
change the text of the Login link, or set a post-login destination.

Role Mappings is where you can assign workgroups to specific roles. The
Student, Faculty and Staff roles and mappings are automatically created at
install time.

Authorizations is where you can decide who can login to your site using
WebAuth. By default it's anyone with a SUNet ID (valid-user) but you can
restrict that further if you want.

-- KNOWN ISSUES --

Because the WebAuth module for Drupal attempts to log people in automatically
if they reach a restricted resource, removing "View Published Content" permissions
from anonymous users may result in users not being able to log out. That's because
upon log out, users are redirected to the home page. If the home page is restricted,
the module will log the users back in again. The current workaround is to quit
the browser to destroy the WebAuth cookie.

-- TROUBLESHOOTING --

If you encounter any issues while using this module at Stanford,
please send a message to:

drupallers@lists.stanford.edu
