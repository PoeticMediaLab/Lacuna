(function ($) {
  Drupal.behaviors.annotatorStore = {
    attach: function (context, settings) {
      Drupal.Annotator.annotator('addPlugin', 'Store', {
        prefix: settings.annotator_store.prefix,
        urls: settings.annotator_store.urls,
        annotationData: {
          'uri': window.location.href,
          'type': 'annotator'
        },
        loadFromSearch: {
          'limit': 0,
          'uri': window.location.href
        }
      });
    }
  };
})(jQuery);
