(function ($, Drupal, window, document, undefined) {
  Drupal.behaviors.create_course = {
    attach: function(context, settings) {
      // createcourse-2
      $('#edit-field-registered-students-und').click(function() { $(".form-field-name-field-unregistered-students").toggle();});

      // createcourse-3
      terms = [];
      $(".term").each(function() {
        terms.push($(this).text());
      });
      $('#ajax-units').click(function() {
        if (new_term = $('#edit-term').val()) {
          $.get("/ajax/add-unit-term/" + new_term, function() {});
          if (terms.indexOf(new_term) == -1) {
            $(".terms").append("<div class='term'>" + new_term + "</div>");
            terms.push(new_term);
          }
          $('#edit-term').val('');
        }
        return false; // dont submit the form
      });
    }
  };
})(jQuery, Drupal, this, this.document);
