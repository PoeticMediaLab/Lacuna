(function ($) {
  Drupal.behaviors.annotatorStore = {
    attach: function (context, settings) {
      Drupal.Annotator.annotator('addPlugin', 'Store', {
        prefix: settings.annotator_store.prefix,
        urls: settings.annotator_store.urls,
        showViewPermissionsCheckbox: settings.annotator_store.showViewPermissionsCheckbox,
        showEditPermissionsCheckbox: settings.annotator_store.showEditPermissionsCheckbox,
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
