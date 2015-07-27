(function($) {

  Drupal.behaviors.GlobalFilterSubmit = {
    attach: function(context, setting) {
      // Cater for up to 20 global filters across the blocks on this page.
      // This is hacky... for historic reasons.
      var filterSettings =
        [setting.global_filter_1,  setting.global_filter_2,  setting.global_filter_3,
         setting.global_filter_4,  setting.global_filter_5,  setting.global_filter_6,
         setting.global_filter_7,  setting.global_filter_8,  setting.global_filter_9,
         setting.global_filter_10, setting.global_filter_11, setting.global_filter_12,
         setting.global_filter_13, setting.global_filter_14, setting.global_filter_15,
         setting.global_filter_16, setting.global_filter_17, setting.global_filter_18,
         setting.global_filter_19, setting.global_filter_20];

      var confirmQuestion = [];
      // Ie set-on-change.
      var autoSubmit = [];
      var oldValues = [];

      // Find global filter widgets on this page and define on-change handlers
      // for those that have either a confirmation msg or set-on-change set.
      for (var i = 0; i < filterSettings.length; i++) {
        if (filterSettings[i] != undefined) {

          var selector = '', elId = '';
          // For eg '.global-filter-2-field-acc-type'.
          var claz = '.' + filterSettings[i][0];

          $(claz + ' input:radio[checked]').each(function() {
            // Catch ANY of the radio buttons.
            selector = claz + ' input:radio';
            elId = $(this).attr('class');
            oldValues[elId] = $(this).attr('id');
          });
          $(claz + ' input:checkbox').each(function() {
            // Catch ALL checkboxes in the family.
            selector = claz + ' input:checkbox';
            elId = $(this).attr('class');
            // Break on first match.
            return false;
          });
          if (elId == '') {
            // Single/Multi selects, date fields, text fields and proximity form
            var selectors = [
              'select' + claz,
              claz + ' select',
              'input:text' + claz,
              claz + ' input.date-clear',
              '.global-filter-links' + claz,
              // Proximity form.
              claz + ' input[name="location"],' + claz + ' input[name="distance"]'
            ];
            for (var sel = 0; sel < selectors.length; sel++) {
              $(selectors[sel]).each(function() {
                // Date range has 2 fields.
                selector = selectors[sel];
                if (!(elId = $(this).attr('id'))) {
                  elId = $(this).attr('class');
                }
                oldValues[elId] = $(this).val();
                // For ex 'Are you sure?'.
                confirmQuestion[elId] = filterSettings[i][1];
                // Is '1' or undefined.
                autoSubmit[elId] = filterSettings[i][2];
              });
            }
          }
          else {
            confirmQuestion[elId] = filterSettings[i][1];
            autoSubmit[elId] = filterSettings[i][2];
          }

          if (selector == '') {
            continue;
          }
          // Define on-change event handlers for all widgets on the page
          $(selector).change(function(event) {
            var type = $(this).attr('type');
            var elId = $(this).attr(type == 'radio' || type == 'checkbox' ? 'class' : 'id');
            var changeConfirmed = !confirmQuestion[elId] || confirm(Drupal.t(confirmQuestion[elId]));
            if (!changeConfirmed) {
              // On second thoughts user declined: restore old selection
              switch (type) {
                case 'radio':
                  // Press the originally selected radio button again.
                  $('#' + oldValues[elId]).attr('checked', true);
                  break;

                case 'checkbox':
                  // Toggle back the checkbox just clicked
                  $(this).attr('checked', !$(this).attr('checked'));
                  break;

                default:
                  // Put the old value back in the box
                  $(this).val(oldValues[elId]);
              }
            }
            if (autoSubmit[elId] || changeConfirmed) {
              // Find enclosing form and auto-submit as soon as a new value is selected.
              for (var element = $(this).parent(); !element.is('form'); element = element.parent()) {}
              element.submit();
            }
          });

          // On-change handler for links widget is an on-click handler
          $('.global-filter-links' + claz + ' li a').click(function(event) {
            elId = $(this).parent().parent().attr('class');
            var changeConfirmed = !confirmQuestion[elId] || confirm(Drupal.t(confirmQuestion[elId]));
            if (!changeConfirmed) {
              // Inhibit click action.
              event.preventDefault();
            }
            else if (setting.links_widget_via_post) {
              // Inhibit click and post instead.
              event.preventDefault();
              var id = $(this).attr('id');
              // id has format <field>:<value>
              var pos = id.indexOf(':');
              var field = id.substr(0, pos);
              var value = id.substr(pos + 1);
              var data = new Object;
              data['from_links_widget'] = field;
              data[field] = value;
              global_filter_post_to('', data);
            }
          });
        }
      }
    }
  }

})(jQuery);

function global_filter_post_to(url, data) {
  jQuery.post(
    url,
    data,
    // Upon confirmation that the post was received, initiate a page refresh.
    // At this time the main module has already set the filter on the session.
    function(response) {
      location.href = '';
    }
  );
}
