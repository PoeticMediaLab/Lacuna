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
Drupal.behaviors.iframe_resize = {
  attach: function(context, settings) {

    //  get iframes on document
    var $frames = $('.field-name-field-media iframe');
    var parent = $frames[0] ? $frames[0].parentElement : null;

    //  record the aspect ratio of each and remove dimensions
    //  from elements
    $frames.each(function(index, element) {

        $(element).data('aspectRatio', element.height / element.width);
        element.removeAttribute('height');
        element.removeAttribute('width');

    });

    //  resize elements on window resize
    $(window).resize(function() {

        var width = parent ? parent.offsetWidth : null;
        $frames.each(function(index, element) {

            element.setAttribute('width', width);
            element.setAttribute('height', width * $(element).data('aspectRatio'));

        });

    });

    //  resize once to set correct size
    setTimeout(function() { $(window).resize(); }, 0);

  }
};


})(jQuery, Drupal, this, this.document);
