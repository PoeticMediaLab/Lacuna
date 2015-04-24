(function($, Drupal) {

/**
 * This script adds jQuery slider functionality to transform_slider form element
 */
Drupal.behaviors.jSliderFormAPI = {
  attach: function (context, settings) {
    // Create sliders
    $('.transfer-slider-container:not(.transferSlider-processed)', context).each(function () {

      $(this).addClass('transferSlider-processed');

      // Get values
      var $slider = $(this).parents('.transfer-slider', context);
      var $left  = $slider.find('.transfer-slider-left-field', context).val() - 0;
      var $right = $slider.find('.transfer-slider-right-field', context).val() - 0;

      // Setup slider
      $(this).slider({
        max: ($left + $right),
        value: $left,
        range: false,
        slide: jsliderSlideProcess,
        change: jsliderSlideProcess
      });
    });

    // Bind left textfield changes
    $('.transfer-slider-left-field:not(.transferSlider-processed)', context)
      .addClass('transferSlider-processed')
      .keyup(function(e) {

        // Get container
        var $slider = $(this).parents('.transfer-slider', context);

        // Left input value
        var $left = $(this).val() - 0;
        if (isNaN($left)) {
          $left = 0;
          $slider.find('.transfer-slider-left-field', context).val($left);
        }

        // Get slider max value
        var $jSlider = $slider.find('.transfer-slider-container', context);
        var $max = $jSlider.slider('option', 'max');

        // Validate left input
        if ($left > $max) {
          $left = $max;
          $slider.find('.transfer-slider-left-field', context).val($left);
        }

        // Setup right value
        $slider.find('.transfer-slider-right-field', context).val($max - $left);

        // Move slider without toggling events
        $jSlider.slider({value: $left});
    });

    // Bind right textfield changes
    $('.transfer-slider-right-field:not(.transferSlider-processed)', context)
      .addClass('transferSlider-processed')
      .keyup(function(e) {

        // Get container
        var $slider = $(this).parents('.transfer-slider', context);

        // Left input value
        var $right = $(this).val() - 0;
        if (isNaN($right)) {
          $right = 0;
          $slider.find('.transfer-slider-right-field', context).val($right);
        }

        // Get slider max value
        var $jSlider = $slider.find('.transfer-slider-container', context);
        var $max = $jSlider.slider('option', 'max');

        // Validate left input
        if ($right > $max) {
          $right = $max;
          $slider.find('.transfer-slider-right-field', context).val($right);
        }

        // Setup right value
        $slider.find('.transfer-slider-left-field', context).val($max - $right);

        // Move slider without toggling events
        $jSlider.slider({value: $max - $right});
    });
  }
};

// Slider processor
var jsliderSlideProcess = function(event, ui) {
  // Setup values
  var $slider = $(this).parents('.transfer-slider');
  $slider.find('.transfer-slider-left-field').val(ui.value);
  var max = $(this).slider('option', 'max');
  $slider.find('.transfer-slider-right-field').val(max - ui.value);
}

})(jQuery, Drupal);