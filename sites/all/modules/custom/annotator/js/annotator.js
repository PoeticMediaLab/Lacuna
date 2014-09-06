(function ($) {
  Drupal.behaviors.annotator = {
    attach: function (context, settings) {
      Drupal.Annotator = $(Drupal.settings.annotator.element).annotator();
    }
  };


})(jQuery);

