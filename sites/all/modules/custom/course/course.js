(function ($, Drupal, window, document, undefined) {
  Drupal.behaviors.create_course = {
    attach: function(context, settings) {
      $('#edit-field-registered-students-und').click(function() { $(".form-field-name-field-unregistered-students").toggle();});
    }
  };
})(jQuery, Drupal, this, this.document);
