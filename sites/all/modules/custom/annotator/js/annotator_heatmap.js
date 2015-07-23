(function ($) {
  Drupal.behaviors.annotatorHeatmap = {
    attach: function (context, settings) {
      Drupal.Annotator.annotator('addPlugin', 'Heatmap', Drupal.settings.annotator_heatmap);
    }
  };
})(jQuery);
