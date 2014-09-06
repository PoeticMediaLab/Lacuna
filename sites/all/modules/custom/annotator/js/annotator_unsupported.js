(function ($) {
  Drupal.behaviors.annotatorUnsupported = {
    attach: function (context, settings) {
      Drupal.Annotator.annotator('addPlugin', 'Unsupported');
    }
  };
})(jQuery);