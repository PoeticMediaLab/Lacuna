
/**
 * @file shows / hides form elements
 */

(function ($) {

Drupal.behaviors.TaxonomyManagerHideForm = {
  attach: function(context, settings) {
    $('#edit-toolbar', context).once('hideForm', function() {
      for (var key in settings.hideForm) {
        Drupal.attachHideForm(settings.hideForm[key].div, settings.hideForm[key].show_button, settings.hideForm[key].hide_button);
      }
    });
  }
}

/**
 * adds click events to show / hide button
 */
Drupal.attachHideForm = function(div, show_button, hide_button) {
  var hide = true;
  var div = $("#"+ div);
  var show_button = $("#"+ show_button);
  var hide_button = $("#"+ hide_button);

  // don't hide if there is an error in the form
  $(div).find("input").each(function() {
    if ($(this).hasClass("error")) {
      hide = false;
    }
  });

  if (!hide) {
    $(div).show();
  }
  $(show_button).click(function() {
    Drupal.hideOtherForms(div);
    $(div).toggle();
    return false;
  });

  $(hide_button).click(function() {
    $(div).hide();
    return false;
  });
}

/**
 * Helper function that hides all forms, except the current one.
*/
Drupal.hideOtherForms = function(currentFormDiv) {
  var currentFormDivId = $(currentFormDiv).attr('id');
  var settings = Drupal.settings.hideForm || [];
  for (var key in settings) {
    var div = settings[key].div;
    if (div != currentFormDivId) {
      $('#' + div).hide();
    }
  }
}

})(jQuery);
