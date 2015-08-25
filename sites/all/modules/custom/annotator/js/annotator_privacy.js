(function ($) {
  Drupal.behaviors.annotatorPrivacy = {
    attach: function (context, settings) {
      Drupal.Annotator.annotator('addPlugin', 'Privacy');
      if ($.isFunction($(document).on)) { // workaround for /admin using jquery 1.5.1 (otherwise, f() does not exist error)
        // need to use .on for future DOM elements, 1.5.1 has .delegate
        $(document).on( "click", "form.annotator-widget .annotator-privacy-types .annotator-privacy-type", function(e) {
          $(this).toggleClass("checked");
          if ("Peer-Groups" == $(this).attr("id")) {
            $(".annotator-widget .annotator-privacy-groups").toggleClass("show-groups");
          }
          if ($(this).hasClass("checked")) {
            if ("Private" == $(this).attr("id")) {
              $(".annotator-privacy-types #Instructor, .annotator-privacy-types #Peer-Groups, .annotator-privacy-types #Everyone").removeClass('checked');
              $(".annotator-widget .annotator-privacy-groups").removeClass("show-groups");
            }
            if ("Everyone" == $(this).attr("id")) {
              $(".annotator-privacy-types #Instructor, .annotator-privacy-types #Peer-Groups, .annotator-privacy-types #Private").removeClass('checked');
              $(".annotator-widget .annotator-privacy-groups").removeClass("show-groups");
            }
            if ("Instructor" == $(this).attr("id") || "Peer-Groups" == $(this).attr("id")) {
              $(".annotator-privacy-types #Private, .annotator-privacy-types #Everyone").removeClass('checked');
            }
          }
        });
      }
    }
  };
})(jQuery);
