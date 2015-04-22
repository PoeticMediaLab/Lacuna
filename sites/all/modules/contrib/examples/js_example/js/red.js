(function ($) {
  Drupal.behaviors.jsWeightsRed = {
    attach: function (context, settings) {
      var weight = settings.jsWeights.red;
      var newDiv = $('<div />').css('color', 'red').html('I have a weight of ' + weight);
      $('#js-weights').append(newDiv);
    }
  };
})(jQuery);
