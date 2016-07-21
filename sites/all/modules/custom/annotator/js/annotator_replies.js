(function ($) {
  Drupal.behaviors.annotatorReplies = {
    attach: function (context, settings) {
      Drupal.Annotator.annotator('addPlugin', 'Replies', Drupal.settings.annotator_replies);
    }
  };
})(jQuery);
