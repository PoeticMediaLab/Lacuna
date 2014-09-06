(function ($) {
  Drupal.behaviors.annotatorMarkdown = {
    attach: function (context, settings) {
      Drupal.Annotator.annotator('addPlugin', 'Markdown');
    }
  };
})(jQuery);