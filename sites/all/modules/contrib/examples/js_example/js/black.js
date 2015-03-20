(function ($) {
  Drupal.behaviors.jsWeightsBlack = {
    attach: function (context, settings) {
      var weight = settings.jsWeights.black;
      var newDiv = $('<div />').css('color', 'black').html('I have a weight of ' + weight);
      $('#js-weights').append(newDiv);
    }
  };
})(jQuery);
