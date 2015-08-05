/*
 * Handle the AJAX interactions during the course setup process
 * Relies a lot on knowing which selectors are set in forms built in course.pages.inc
 */

(function ($) {
    'use strict';

    Drupal.behaviors.create_course = {
    attach: function(context, settings) {
        // TODO: Refactor into separate js files for each step
      // createcourse-2
      $('#edit-field-registered-students-und').click(function() { $(".form-field-name-field-unregistered-students").toggle();});

        // Accept new terms to add to taxonomies
        $('.ajax-add-term').click(function(event) {
            // Fieldsets, which we use, have an extra fieldset wrapper div
            // We set the ID for each taxonomy in the fieldset element
            var wrapper = $(event.srcElement.parentNode.parentNode),
                terms = [],
                vocab = event.srcElement.parentNode.parentNode.id,
                input = wrapper.find("input[name='term']"),
                term = input.val(),
                new_terms,
                i;
            wrapper.find('.terms').each(function() {
                terms.push($(this).text().trim());
            });
            if (term.length > 0) {
                console.log(settings['basePath'] + "ajax/add-term/" + vocab, { terms: term });
                $.post(settings['basePath'] + "ajax/add-term/" + vocab, { terms: term });
                new_terms = term.split(',')
                for (i = 0; i < new_terms.length; i++) {
                    if (terms.indexOf(new_terms[i].trim()) == -1) {
                        $('#terms-' + vocab).append("<div class='term'><span class='name'>" + new_terms[i].trim() + "</span><span class='fa fa-trash-o'></span></div>");
                        terms.push(new_terms[i].trim());
                    }
                }
                $('#edit-term').val('');
            }
            return false; // don't submit the form
      });

    //  $('.terms .trash-o').click(function() {
    //    term = $(this).siblings(".name").text();
    //    nid = $("[name=course_nid]").val();
    //    $.ajax({
    //      url: settings['bathPath'] + 'ajax/delete-term/' + nid + '/' + term,
    //      method: 'DELETE',
    //      done: function(result) {
    //        i = terms.indexOf(term);
    //        if (i != -1) {
    //          terms.splice(i, 1);
    //        }
    //      }
    //    });
    //    $(this).parent().remove();
    //  });
    //
    //  // createcourse-4
    //  if ($(".page-createcourse-4").length) {
    //    doc_nid = window.location.pathname.split('/')[2];
    //    // selecting the biblio type reloads the page
    //    if (0 != $("#edit-biblio-type option:selected").val()) {
    //      $(".biblio-form").show();
    //      $("#" + $.cookie("course-material-type-" + doc_nid)).addClass("selected");
    //    }
    //
    //    $("#e-access button").click(function(e) {
    //      if ($("#studynet").hasClass("selected")) {
    //        $("#studynet").removeClass("selected");
    //      }
    //      else {
    //        $(".biblio-form").toggle(300);
    //      }
    //      $(this).blur().parent().toggleClass("selected");
    //      $.cookie("course-material-type-" + doc_nid, $(this).parent().attr("id"));
    //    });
    //    $("#studynet button").click(function(e) {
    //      if ($("#e-access").hasClass("selected")) {
    //        $("#e-access").removeClass("selected");
    //      }
    //      else {
    //        $(".biblio-form").toggle(300);
    //      }
    //      $(this).blur().parent().toggleClass("selected");
    //      $.cookie("course-material-type-" + doc_nid, $(this).parent().attr("id"));
    //    });
    //  }
    }
  };
})(jQuery);
