/*  Creates the Loading plugin for Annotator in Drupal.
*/

(function ($) {
  Drupal.behaviors.annotatorLoading = {
    attach: function (context, settings) {
      Drupal.Annotator.annotator('addPlugin', 'Loading', Drupal.settings.annotator_loading);
    }
  };
})(jQuery);
