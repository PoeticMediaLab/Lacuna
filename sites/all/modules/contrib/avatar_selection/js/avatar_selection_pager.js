
/**
 * Fetches the new page and puts it inline.
 */
(function ($) {
  Drupal.behaviors.avatar_selection_pager = {
    attach: function (context) {
      $('.avatar-selection-pager-nav a').click(function() {
        $('body').css({'opacity': 0.5});
        $('#avatar-selection-loading').show();
        var url = $(this).attr('href');
        var form_id = $(this).parents('form').attr('id');
        $.get(url, function(data, status) {
          var selects = $(data).find('div.user-avatar-select');
          $('div.user-avatar-select').html(selects);
          var pager = $(data).find(".avatar-selection-pager-nav");
          $(".avatar-selection-pager-nav").html(pager);
          Drupal.attachBehaviors(data);
          var action = url;
          $('#' + form_id).attr("action", action);
          $("#avatar-selection-loading").hide();
          $("body").css({'opacity': 1});
        });
        return false;
      });
    }
  }
})(jQuery);

