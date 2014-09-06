(function ($) {
  Drupal.behaviors.annotatorFilter = {
    attach: function (context, settings) {
      Drupal.Annotator.annotator('addPlugin', 'Filter');
    }
  };
})(jQuery);