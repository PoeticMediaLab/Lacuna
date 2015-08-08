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
            // We set the ID for each taxonomy in the fieldset element wrapping it all
            var wrapper = $(event.srcElement).parents('fieldset'),
                terms = [],
                vocab = wrapper.attr('id'),
                input = wrapper.find("input[name='term']"),
                term = input.val(),
                terms_list = wrapper.find('.terms'),
                new_terms,
                new_term,
                i, l,
                clone;
            wrapper.find('.terms > .term > .name').each(function() {
                terms.push(this.textContent.trim());
            });
            if (term.length > 0) {
                $.post(settings['basePath'] + "ajax/add-term/" + vocab, { terms: term });
                new_terms = term.split(',')
                for (i = 0, l = new_terms.length; i < l; i++) {
                    new_term = new_terms[i].trim();
                    if (terms.indexOf(new_term) == -1) {
                        // Note: needs to match initial form list
                        terms_list.append("<div class='term'><span class='fa fa-trash-o'></span><span class='name'>" + new_term + "</span></div>");
                        terms.push(new_terms);
                    }
                }
                input.val('');
            }
            return false; // don't submit the form
      });

      $('.terms').on('click', '.term .fa-trash-o', function(event) {
        var wrapper = $(event.srcElement).parents('fieldset'),
            vocab = wrapper.attr('id'),
            term = $(this).siblings(".name").text();
            $.ajax({
              url: settings['basePath'] + 'ajax/delete-term/' + vocab + '/' + term,
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
      if ($(".page-course-setup-add-materials").length) {
        // selecting the biblio type reloads the page
        if (0 != $("#edit-biblio-type option:selected").val()) {
          $(".biblio-form").show();
          $("#" + $.cookie("course-material-type-" + Drupal.settings.course.current_course)).addClass("selected");
        }

        $("#add-documents button").click(function(e) {
          if ($("#add-documents").hasClass("selected")) {
              $("#add-documents").removeClass("selected");
          }
          else {
              $(".biblio-form").toggle(300);
          }
          $(this).blur().parent().toggleClass("selected");
          $.cookie("course-material-type-" + doc_nid, $(this).parent().attr("id"));
        });

        //$("#e-access button").click(function(e) {
        //  if ($("#studynet").hasClass("selected")) {
        //    $("#studynet").removeClass("selected");
        //  }
        //  else {
        //    $(".biblio-form").toggle(300);
        //  }
        //  $(this).blur().parent().toggleClass("selected");
        //  $.cookie("course-material-type-" + doc_nid, $(this).parent().attr("id"));
        //});
        //$("#studynet button").click(function(e) {
        //  if ($("#e-access").hasClass("selected")) {
        //    $("#e-access").removeClass("selected");
        //  }
        //  else {
        //    $(".biblio-form").toggle(300);
        //  }
        //  $(this).blur().parent().toggleClass("selected");
        //  $.cookie("course-material-type-" + doc_nid, $(this).parent().attr("id"));
        //});
      }
    }
  };
})(jQuery);
