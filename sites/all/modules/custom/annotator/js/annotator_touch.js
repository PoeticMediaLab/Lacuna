(function ($) {
  Drupal.behaviors.annotatorTouch = {
    attach: function (context, settings) {
      Drupal.Annotator.annotator('addPlugin', 'Touch');
    }
  };
})(jQuery);
