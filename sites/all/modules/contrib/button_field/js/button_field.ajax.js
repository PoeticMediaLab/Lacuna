(function ($) {
$(document).ready(function() {
  if (Drupal.ajax) {
    // Add a new ajax command that will change the location of the current page.
	Drupal.ajax.prototype.commands.buttonFieldLocation = function(ajax, response, status) {
	  location.href = response.url;
	};
  }
});
})(jQuery);