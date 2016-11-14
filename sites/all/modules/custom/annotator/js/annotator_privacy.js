(function ($) {
  Drupal.behaviors.annotatorPrivacy = {
    attach: function (context, settings) {
      Drupal.Annotator.annotator('addPlugin', 'Privacy');
      if ($.isFunction($(document).on)) { // workaround for /admin using jquery 1.5.1 (otherwise, f() does not exist error)
        // need to use .on for future DOM elements, 1.5.1 has .delegate
        $(document).on( "click", "form.annotator-widget .annotator-privacy-types .annotator-privacy-type", function(e) {
          if ($(this).hasClass("checked")) return;
          if ("Peer-Groups" == $(this).attr("id")) {
            //  Return if trying to click Peer Groups when user isn't in any
            var $groups = $(".annotator-widget .annotator-privacy-group");
            if ($groups.length === 0) return;
            //  Show available peer groups and select the first one
            $(".annotator-widget .annotator-privacy-groups").addClass("show-groups");
            $groups.prop('checked', true);
          }
          $(this).toggleClass("checked");
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
