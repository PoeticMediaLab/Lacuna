(function ($) {

$(function() {

  // Add event checkbox handler and init toogle options.
  $('#edit-jquery-ui-filter-accordion-options-scrollto')
    .click(Drupal.jQueryUiFilter.toggleAdminOptions)
    .each(Drupal.jQueryUiFilter.toggleAdminOptions);

});

})(jQuery);
