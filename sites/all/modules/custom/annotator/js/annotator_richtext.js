/*
 Annotator Rich Text plugin
*/
(function ($) {
  Drupal.behaviors.annotatorRichtext = {
    attach: function (context, settings) {
        Drupal.Annotator.annotator('addPlugin', 'RichText');
    }
  };
})(jQuery);
