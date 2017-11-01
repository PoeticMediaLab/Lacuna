(function ($) {
  Drupal.behaviors.annotatorPDF = {
    attach: function (context, settings) {
      Drupal.Annotator.annotator('addPlugin', 'PDF');
    }
  };
})(jQuery);