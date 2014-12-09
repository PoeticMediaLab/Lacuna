(function ($) {
  Drupal.behaviors.annotatorAuth = {
    attach: function (context, settings) {
      Drupal.Annotator.annotator('addPlugin', 'Auth', {
        tokenUrl: settings.annotator_auth.tokenUrl,
        token: settings.annotator_auth.token,
        autoFetch: settings.annotator_auth.autoFetch
      });
    }
  };
})(jQuery);
