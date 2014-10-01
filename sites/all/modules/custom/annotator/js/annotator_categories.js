/*
  Control code for Annotator Categories. Collects settings set by the admin, sorts the categories by rank, and sets the category name to a variable used by the Categories extension.
  Extension file at annotator-full-extension-categories.js
*/
(function ($) {
  Drupal.behaviors.annotatorCategories = {
    attach: function (context, settings) {
      // settings defined in CategoriesAnnotatorPlugin.class.inc
      Drupal.Annotator.annotator('addPlugin', 'Categories', Drupal.settings.annotator_categories);
    }
  };
})(jQuery);
