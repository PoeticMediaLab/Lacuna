(function ($) {
  Drupal.behaviors.annotatorPrivacy = {
    attach: function (context, settings) {
      Drupal.Annotator.annotator('addPlugin', 'Privacy', {
        permissions: settings.annotator_permissions.permissions,
      });
    }
  };
})(jQuery);