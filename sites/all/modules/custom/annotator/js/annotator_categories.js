/*
  Control code for Annotator Categories. Collects settings set by the admin, sorts the categories by rank, and sets the category name to a variable used by the Categories extension.
  Extension file at annotator-full-extension-categories.js
*/
(function ($) {
  Drupal.behaviors.annotatorCategories = {
    attach: function (context, settings) {
      var data = Drupal.settings.category_list; //This variable can be printed directly from your JS console, from any page on the site.

      //Array to hold the category names once they're sorted. This is used by the Annotator Plugin.
      var categories = [];
      var count = 0;

      //Sorts categories in descending order by rank (which is set in Annotator admin). Couldn't get this working in PHP but it works here.
      // (data.category).sort(function(a,b){
      //   return b.category_rank-a.category_rank;
      // }).reverse();

      // Loop through each item.
      for (prop in data.category) {
        if (!(data.category).hasOwnProperty(prop)) {
          continue;
        }
        // Capitalizes first letter of each category.
        var category_caps = (data.category[prop].category_name).charAt(0).toUpperCase() + (data.category[prop].category_name).substring(1);

        // And adds that category name to an array. Categories is used by Annotator to set up the categories widget.
        categories.push({name: category_caps});
      }

      // Adds the array we just created to the Categories plugin, which will use the fields to generate clickable tabs.
      Drupal.Annotator.annotator('addPlugin', 'Categories', {categories: categories});
    }
  };
})(jQuery);
