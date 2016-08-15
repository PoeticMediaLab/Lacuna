(function ($) {

$(function() {

  // Add event checkbox handler and init toogle options.
  $('#edit-jquery-ui-filter-tabs-options-cookie, #edit-jquery-ui-filter-tabs-options-fx, #edit-jquery-ui-filter-tabs-options-paging, #edit-jquery-ui-filter-tabs-options-scrollto')
    .click(Drupal.jQueryUiFilter.toggleAdminOptions)
    .each(Drupal.jQueryUiFilter.toggleAdminOptions);

});

})(jQuery);
