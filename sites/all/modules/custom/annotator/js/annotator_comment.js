(function ($) {
  Drupal.behaviors.annotatorComment = {
    attach: function (context, settings) {
      Drupal.Annotator.annotator('addPlugin', 'Comment', Drupal.settings.annotator_comment);
    }
  };
})(jQuery);
