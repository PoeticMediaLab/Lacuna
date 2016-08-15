(function ($) {

Drupal.jQueryUiFilter.toggleAdminOptions = function() {
  var id = ('#' + this.id + '-options').toLowerCase();
  if (this.checked) {
    $(id).show();
  }
  else {
    $(id).hide();
  }
}

})(jQuery);
