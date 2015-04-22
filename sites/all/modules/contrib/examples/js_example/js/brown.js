(function ($) {
  Drupal.behaviors.jsWeightsBrown = {
    attach: function (context, settings) {
      var weight = settings.jsWeights.brown;
      var newDiv = $('<div />').css('color', 'brown').html('I have a weight of ' + weight);
      $('#js-weights').append(newDiv);
    }
  };
})(jQuery);
