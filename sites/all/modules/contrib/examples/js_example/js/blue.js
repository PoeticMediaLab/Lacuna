(function ($) {
  Drupal.behaviors.jsWeightsBlue = {
    attach: function (context, settings) {
      var weight = settings.jsWeights.blue;
      var newDiv = $('<div />').css('color', 'blue').html('I have a weight of ' + weight);
      $('#js-weights').append(newDiv);
    }
  };
})(jQuery);
