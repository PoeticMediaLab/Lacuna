CONTENTS OF THIS FILE
---------------------

 * Introduction
 * Usage
 * Features
 * Requirements
 * Installation
 * Customization
 * Similar Modules
 * Todo

INTRODUCTION
------------

The jQueryUI filter converts static HTML to a jQuery UI accordian or tabs widget
and opens links inside a jQuery UI dialog.

For example, this module converts the below HTML code into a
collapsed jQueryUI accordion widget.

<p>[accordion collapsed]</p>

  <h3>Section I</h3>
  <p>Pellentesque habitant morbi tristique senectus et netus et malesuada fames ac turpis egestas.</p>

  <h3>Section II</h3>
  <p>Pellentesque habitant morbi tristique senectus et netus et malesuada fames ac turpis egestas.</p>

  <h3>Section III</h3>
  <p>Pellentesque habitant morbi tristique senectus et netus et malesuada fames ac turpis egestas.</p>

<p>[/accordion]</p>

Learn more about jQueryUI's accordion, dialog, and tabs widget.
- http://jqueryui.com/demos/accordion/
- http://jqueryui.com/demos/dialog/
- http://jqueryui.com/demos/tabs/

Roll your own custom jQueryUI theme
- http://jqueryui.com/themeroller/


USAGE
-----

Use [accordion] and [/accordion] or [tabs] and [/tabs] to create a jQuery UI
Accordian or tabs. Using [accordion collapsed] will start with the accordion
closed.

To open a link inside a jQuery UI dialog set the link\'s the target attribute
to [dialog] or [modal] with optional JSON data with single quotes.

<p><a href="/contact" target="[modal {'width': 400, 'height': 600}]">Contact Us</a></p>


FEATURES
--------

- Full UI for customizing most jQuery UI accordion, dialog, and tabs options.

- Adds option to include paging buttons below tabs.

- Adds history and bookmark support to accordions and tabs.

- Gracefully degrades when JavaScript is disabled.


REQUIREMENTS
------------

- jQuery plugins: An API and home for miscellaneous jQuery plugins.
  http://drupal.org/project/jquery_plugin
  (Optional: Used to store jQuery UI tabs state in a cookie.)


INSTALLATION
------------

IMPORTANT:
Make sure your text formats are configured to support <h3> tags.
The default filter, included with Drupal, removes <H3> tags from filtered text.

1. Copy/upload the jquery_ui_filter.module to the sites/all/modules directory
   of your Drupal installation.

2. Enable the 'jQueryUI filter' modules in 'Modules', (admin/modules)

3. Visit the 'Configuration > [Content authoring] Text formats'
   (admin/config/content/formats). Click "configure" next to the input format you want
   to enable the jQueryUI filter.

4. Enable (check) the jQueryUI filter under the list of filters and save
   the configuration.

5. (optional) Visit the 'Configuration > [Content authoring] jQuery UI filter'
   (admin/config/content/jquery_ui_filter). 


CUSTOMIZATION
-------------

- Besides using the UI for customizing your jQuery UI widget you can define 
  default options by adding the the below JavaScript snippets to your 
  theme's script.js file.

(function ($) {

// Set Jquery UI Filter default options
Drupal.jQueryUiFilter = Drupal.jQueryUiFilter || {}

// Set Jquery UI accordion options: http://jqueryui.com/demos/accordion/
Drupal.jQueryUiFilter.accordionOptions = {
  autoHeight: false
}

// Set Jquery UI dialog options: http://jqueryui.com/demos/dialog/
Drupal.jQueryUiFilter.dialogOptions = {
  modal: true
}

// Set Jquery UI tabs options: http://jqueryui.com/demos/tabs/
Drupal.jQueryUiFilter.tabsOptions = {
  event: 'click',
  fx: {opacity: 'toggle'},
  paging: true
}

})(jQuery);


SIMILAR MODULES
---------------

[Dialog]
- Automodal: Automatically convert certain classed links to modal popups
  and provides an API to add custom modals quickly and easily.
  http://drupal.org/project/automodal

- Automodal URL: Loads a modal frame automatically based on URL parameters.
  http://drupal.org/project/automodal_url

- Dialog API: The module provides an API for creating and updating javascript
  dialog windows using the jQuery UI Dialog widget and the CTools ajax framework.
  http://drupal.org/project/dialog

- Modal Frame API: Provides an API to render an iframe within a modal dialog
  based on the jQuery UI Dialog plugin.
  http://drupal.org/project/modalframe

- Simple Dialog: Provides an API to create simple modal dialogs. Leverages the
  jQuery ui dialog plugin included with Drupal 7.
  http://drupal.org/project/simple_dialog

[Tabs]
- Quick tabs: Create blocks of tabbed views and blocks.
  http://drupal.org/project/quicktabs

- Tabs (jQuery UI tabs): A helper module for creating tabbed pages.
  http://drupal.org/project/tabs


NOTES
-----

- jQuery UI dialog handling could be enhanced by optionally using the Modal
  Frame API, which still has not been ported to D7.


AUTHOR/MAINTAINER
-----------------

- Jacob Rockowitz
  http://drupal.org/user/371407
