(function ($) {
  
  /**
   * Override default menuFieldsetSummaries.
   */
  Drupal.behaviors.menuFieldsetSummaries = {
    attach: function (context) {
      $('fieldset.menu-link-form', context).drupalSetSummary(function (context) {
        var summary = '';
        if ($('.form-item-menu-enabled input', context).is(':checked')) {
          var menuItemType = $('.form-item-menu-menu-item-type', context);
          if (menuItemType.length) {
            if ($('input:checked', menuItemType).val() == 'view') {
              summary = '';
              var name = $('.form-item-menu-menu-views-view-name select, .form-item-menu-options-menu-views-view-name select', context).first();
              if (name.length) {
                var nameValue = Drupal.checkPlain($(':selected', name).val());
                if (nameValue != '') {
                  summary = nameValue;
                  var display = $('.form-item-menu-menu-views-view-display select, .form-item-menu-options-menu-views-view-display select', context).first();
                  if (display.length) {
                    var displayValue = Drupal.checkPlain($(':selected', display).val());
                    if (displayValue != '') {
                      summary += '-' + displayValue;
                    }
                    var arguments = $('.form-item-menu-menu-views-view-arguments input, .form-item-menu-options-menu-views-view-arguments input', context).first();
                    if (arguments.length) {
                      var argumentsValue = Drupal.checkPlain(arguments.val());
                      if (argumentsValue != '') {
                        summary += '-' + argumentsValue;
                      }
                    }
                  }
                }
                if (summary == '') {
                  summary = Drupal.t('None Selected');
                }
                summary = Drupal.t('View') + ': ' + summary;
              }
            }
            else {
              var linkTitle = $('.form-item-menu-link-title input', context);
              if (linkTitle.length) {
                summary = Drupal.checkPlain(linkTitle.val());
                if (summary == '') {
                  var nodeTitle = $('.form-item-title input');
                  if (nodeTitle.length) {
                    summary = Drupal.checkPlain(nodeTitle.val());
                  }
                  if (summary == '') {
                    summary = '[' + Drupal.t('node:title') + ']';
                  }
                }
              }
              if (summary != '') {
                summary = 'Link: ' + summary;
              }
            }
          }
        }
        else {
          summary = Drupal.t('Not in menu');
        }
        if (summary == '') {
          summary = 'Loading...';
        }
        return summary;
      });
    }
  };
  
  /**
   * Move menu item settings fieldset to right column on node edit form, if using rubik.
   */
  Drupal.behaviors.menu_views = {
    attach: function (context, settings) {
      // Ensure that menu_views exists in settings.
      settings.menu_views = settings.menu_views || {};
      if (!settings.menu_views.node_form && settings.menu_views.admin_theme == 'rubik') {
        var sidebar = $('.column-side .column-wrapper', context);
        if (sidebar.length) {
          $('fieldset.menu-item-settings', sidebar).remove();
          $('fieldset.menu-item-settings', context).appendTo(sidebar);
        }
      }
    }
  };
}(jQuery));