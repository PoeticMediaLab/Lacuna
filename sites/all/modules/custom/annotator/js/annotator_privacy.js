(function ($) {
  Drupal.behaviors.annotatorPrivacy = {
    attach: function (context, settings) {
      Drupal.Annotator.annotator('addPlugin', 'Privacy');
      if ($.isFunction($(document).on)) { // workaround for /admin using jquery 1.5.1 (otherwise, f() does not exist error)
        // need to use .on for future DOM elements, 1.5.1 has .delegate
        $(document).on( "change", "form.annotator-widget .privacy.types input", function(e) {
          if ("Private" == $(this).attr("id") && $(this).is(":checked")) {
            $(".privacy.types #Instructor, .privacy.types #Co-Learners").prop('checked', false);
            $(".annotator-widget .privacy.groups").hide(500);
          }
          if ("Co-Learners" == $(this).attr("id")) {
            $(".annotator-widget .privacy.groups").toggle(500);
          }
          if (("Instructor" == $(this).attr("id") || "Co-Learners" == $(this).attr("id")) && $(this).is(":checked")) {
            $(".privacy.types #Private").prop('checked', false);
          }
        });
      }
    }
  };
})(jQuery);
