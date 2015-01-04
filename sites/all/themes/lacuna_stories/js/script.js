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
Drupal.behaviors.my_custom_behavior = {
  attach: function(context, settings) {

$(document).ready(function() {
	// Tooltip only Text
	// $('.views-field-field-display-name').hide();
	// $('.views-field-title').hide();

    $('<span class="text-content"></span>')
    .appendTo('.views-field-field-image .field-content a');

	$('img').hover(function(event){
        // Hover over code
		// console.log(event.target.nodeName); 
		console.log(event.target.parentNode);
		// console.log($(this));
        // $('<span class="views-field-text"></span>')
        // .appendTo(event.target.parentNode);
		});

	});
  }
};


})(jQuery, Drupal, this, this.document);
