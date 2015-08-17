(function ($) {
  Drupal.behaviors.annotatorHistogram = {
    attach: function (context, settings) {
      try {
        Drupal.Annotator.annotator('addPlugin', 'Histogram', Drupal.settings);
      }
      catch (err) {
        console.error('Error loading histogram: ' + err);
      }
    }
  };
})(jQuery);