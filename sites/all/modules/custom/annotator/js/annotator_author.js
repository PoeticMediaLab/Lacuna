/**
 * Created by widner on 8/11/15.
 */
(function ($) {
    Drupal.behaviors.annotatorAuthor = {
        attach: function (context, settings) {
            Drupal.Annotator.annotator('addPlugin', 'Author');
        }
    };
})(jQuery);
