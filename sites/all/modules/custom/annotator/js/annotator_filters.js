(function ($) {
  Drupal.behaviors.annotatorFilters = {
    attach: function (context, settings) {
      Drupal.Annotator.annotator('addPlugin', 'Filters', Drupal.settings.annotator_filters);
    }
  };
})(jQuery);
