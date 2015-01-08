(function ($) {
  Drupal.behaviors.annotatorCommentCount = {
    attach: function (context, settings) {
      Drupal.Annotator.annotator('addPlugin', 'CommentCount', Drupal.settings.annotator_commentcount);
    }
  };
})(jQuery);