(function ($) {
  Drupal.behaviors.annotatorControls = {
    attach: function (context, settings) {
      try {
        Drupal.Annotator.annotator('addPlugin', 'Controls', Drupal.settings);
      }
      catch (err) {
        console.error('Error loading Controls plugin: ' + err);
      }
    }
  };
})(jQuery);