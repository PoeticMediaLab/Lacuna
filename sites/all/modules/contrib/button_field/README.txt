Adds a button field type for use with any fieldable entity type and Rules.
Provides two different widgets: HTML Button and Image Button. Adds a new button
click event, clicked button comparison, and reload page action for use with
rules. When the button is clicked, an AJAX call is used to run the event. Using
rules you could display a message to the user, alter some data on the entity (or
another entity) and reload the current (or any other) page.

Differences from Drupal 6 version
=================================
- Works with any fieldable entity
- Entity parameter provided with the rules event will contain any form values
from the edit form
- Makes much better use of Drupal's Forms API (FAPI)
- Utilizes Drupal's Ajax Framework

Upgrading from Druapl 6
=======================
This module provides no update path of its own from Drupal 6 to Drupal 7. To
migrate your existing fields, take a look at http://drupal.org/node/1144136. To
update your rules, read the "Upgrade from Rules 6.x-1.x to Rules 7.x-2.x"
section of the README included in the Rules module. Any button fields previously
added to views will need to be re-attached to those views.

Installation
============
Simply enable the module at /admin/modules.

Usage
=====
You can add a button field to any fieldable entity type. For example, to
add one to the default page content type, go to
/admin/structure/types/manage/page/fields and use the same manage fields
interface you would use for any other field type.

To add rules to trigger when a button is clicked, you will need to add a rule
at /admin/config/workflow/rules. Choose the "User clicks a button field" event
and add any conditions or actions that you require. Any rules that would modify
the current page (such as changing entity field values or displaying a message
to the user) will require a page reload before they will be visible to the user.
You can accomplish this by adding a "Reload the current page" action. It is
recommended that you add a "Clicked button comparison" condition to ensure that
your rule only executes when the desired button is clicked. Due to the ajax
nature of button fields and the rules event, not all conditions or actions may
work as desired.

Support
=======
If you have any questions or run into any issues, please use the issue queue
found on the project page at http://drupal.org/project/button_field.
