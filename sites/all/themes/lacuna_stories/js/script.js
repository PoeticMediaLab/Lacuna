/**
 * @file
 * A JavaScript file for the theme.
 *
 * In order for this JavaScript to be loaded on pages, see the instructions in
 * the README.txt next to this file.
 */

// JavaScript should be made compatible with libraries other than jQuery by
// wrapping it with an "anonymous closure". See:
// - https://drupal.org/node/1446420
// - http://www.adequatelygood.com/2010/3/JavaScript-Module-Pattern-In-Depth
(function ($, Drupal, window, document, undefined) {


// To understand behaviors, see https://drupal.org/node/756722#behaviors
Drupal.behaviors.mobileSupport = {
  attach: function(context, settings) {

    /*
     *   Added listener to fire click event instead of just mouseover when
     *   front-page material is tapped.  Conditional is a check for tablet
     *   that should cover most touchscreen devices.
     */
    if (window.ontouchstart !== undefined) {
      $('.view-display-id-materials .field-content a').mouseover(function(event) {
        $(event.target).trigger('click');
      });
    }

  }
};


})(jQuery, Drupal, this, this.document);
