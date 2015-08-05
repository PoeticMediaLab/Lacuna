(function ($, Drupal, window, document, undefined) {
  Drupal.behaviors.create_course = {
    attach: function(context, settings) {
      // createcourse-2
      $('#edit-field-registered-students-und').click(function() { $(".form-field-name-field-unregistered-students").toggle();});

      // createcourse-3
      terms = [];
      $(".term").each(function() {
        terms.push($(this).text().trim());
      });
      $('#ajax-units').click(function() {
        if (new_term = $('#edit-term').val().trim()) {
          $.post(settings['basePath'] + "/ajax/add-unit-term", {term: new_term, nid: $("[name=course_nid]").val()});
          new_terms = new_term.split(',')
          for (i=0; i < new_terms.length; i++) {
            if (terms.indexOf(new_terms[i].trim()) == -1) {
              $(".terms").append("<div class='term'><span class='name'>" + new_terms[i].trim() + "</span><span class='fa fa-minus'></span></div>");
              terms.push(new_terms[i].trim());
            }
          }
          $('#edit-term').val('');
        }
        return false; // dont submit the form
      });
      $('.terms .fa-minus').click(function() {
        term = $(this).siblings(".name").text();
        nid = $("[name=course_nid]").val();
        $.ajax({
          url: settings['bathPath'] + '/ajax/delete-unit-term/' + nid + '/' + term,
          method: 'DELETE',
          done: function(result) {
            i = terms.indexOf(term);
            if (i != -1) {
              terms.splice(i, 1);
            }
          }
        });
        $(this).parent().remove();
      });

      // createcourse-4
      if ($(".page-createcourse-4").length) {
        doc_nid = window.location.pathname.split('/')[2];
        // selecting the biblio type reloads the page
        if (0 != $("#edit-biblio-type option:selected").val()) {
          $(".biblio-form").show();
          $("#" + $.cookie("course-material-type-" + doc_nid)).addClass("selected");
        }

        $("#e-access button").click(function(e) {
          if ($("#studynet").hasClass("selected")) {
            $("#studynet").removeClass("selected");
          }
          else {
            $(".biblio-form").toggle(300);
          }
          $(this).blur().parent().toggleClass("selected");
          $.cookie("course-material-type-" + doc_nid, $(this).parent().attr("id"));
        });
        $("#studynet button").click(function(e) {
          if ($("#e-access").hasClass("selected")) {
            $("#e-access").removeClass("selected");
          }
          else {
            $(".biblio-form").toggle(300);
          }
          $(this).blur().parent().toggleClass("selected");
          $.cookie("course-material-type-" + doc_nid, $(this).parent().attr("id"));
        });
      }

    }
  };
})(jQuery, Drupal, this, this.document);
