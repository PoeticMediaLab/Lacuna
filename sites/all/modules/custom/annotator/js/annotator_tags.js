(function ($) {
  Drupal.behaviors.annotatorTags = {
    attach: function (context, settings) {
      Drupal.Annotator.annotator('addPlugin', 'Tags');
      // MLW - Autocomplete our tags in the window
      // @see https://github.com/openannotation/annotator/issues/92#issuecomment-3985124
      if (typeof Drupal.Annotator.data('annotator') !== 'undefined') {
        Drupal.Annotator.data('annotator').plugins.Tags.input.autocomplete({source: Drupal.settings.annotator_tags});
      }
    }
  };
})(jQuery);
