Examples for Developers
=======================

http://drupal.org/project/examples

What Is This?
-------------

This set of modules is intended to provide working examples of Drupal's
features and APIs.  The modules strive to be simple, well documented and
modification friendly, in order to help developers quickly learn their inner
workings.

These examples are meant to teach you about code-level development for Drupal
7. Some solutions might be better served using a contributed module, so that
you don't end up having to re-invent the wheel in PHP.


How To Use The Examples
-----------------------

There are three main ways to interact with the examples in this project:

1. Enable the modules and use them within Drupal. Not all modules will have
obvious things to see within Drupal. For instance, while the Page and Form API
examples will show you forms, the Database API example will not show you much
within Drupal itself.

2. Read the code. Much effort has gone into making the example code readable,
not only in terms of the code itself, but also the extensive inline comments
and documentation blocks.

3. Browse the code and documentation on the web. There are two main places to
do this:

* https://api.drupal.org/api/examples is the main API site for all of Drupal.
It has all manner of cross-linked references between the example code and the
APIs being demonstrated.

* http://drupalcode.org/project/examples.git allows you to browse the git
repository for the Examples project.


How To Install The Modules
--------------------------

1. Install Examples for Developers (unpacking it to your Drupal
/sites/all/modules directory if you're installing by hand, for example).

2. Enable any Example modules in Admin menu > Site building > Modules.

3. Rebuild access permissions if you are prompted to.

4. Profit!  The examples will appear in your Navigation menu (on the left
sidebar by default; you'll need to reenable it if you removed it).

Now you can read the code and its comments and see the result, experiment with
it, and hopefully quickly grasp how things work.

If you find a problem, incorrect comment, obsolete or improper code or such,
please search for an issue about it at http://drupal.org/project/issues/examples
If there isn't already an issue for it, please create a new one.
