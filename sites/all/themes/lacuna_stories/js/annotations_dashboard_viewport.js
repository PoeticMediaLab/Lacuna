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
Drupal.behaviors.annotator_dashboard = {
  attach: function(context, settings) {

    //  resizes the viewport for mobile screens so annotations dashboard
    //  visualizations are the correct size.
   if (window.location.pathname.indexOf('/visualization/dashboard') > -1 && window.innerWidth < 1215) {

    var meta_viewport = document.querySelector('head meta[name="viewport"]');
    meta_viewport.content = "width=1215px";

   }
  }
};


})(jQuery, Drupal, this, this.document);
