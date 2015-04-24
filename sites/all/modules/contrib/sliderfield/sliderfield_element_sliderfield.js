(function($, Drupal) {
  /**
   * This script adds jQuery slider functionality to transform_slider form element
   */
  Drupal.behaviors.SliderFieldSliderField = {
    attach: function (context, settings) {

      // Create sliders
      $('.sliderfield-container:not(.sliderfield-processed)', context).each(function () {

        $(this).addClass('sliderfield-processed');
        var slider_id = $(this).parent().attr('id');
        var setting = settings['sliderfield_' + slider_id];
        // Get values
        var $slider = $(this).parents('.sliderfield', context);

        var $values = [];
        var $value = $slider.find('.sliderfield-value-field', context).val();
        var $value2 = $slider.find('.sliderfield-value2-field', context).val();
        if (!isNaN($value2)) {
          $values = [$value, $value2];
        } else {
          setting.value = $value;
          setting.current_value = $value;
        }

        if (!setting.display_inputs) {
          $slider.find('.sliderfield-value-field, .sliderfield-value2-field', context).hide();
          $slider.find('label', $slider.find('.sliderfield-value-field, .sliderfield-value2-field', context).parents()).hide();
          $slider.find('label', $slider.find('.webform-sliderfield .sliderfield-value-field,.webform-sliderfield .sliderfield-value2-field', context).parents()).show();
        }

        // Setup slider
        $(this).slider({
          value: $value,
          animate : setting.animate,
          max : setting.max - 0,
          min : setting.min - 0,
          orientation : setting.orientation,
          range : setting.range,
          step : setting.step,
          values : $values,
          slide: sliderfieldsSlideProcess,
          stop: sliderfieldsSlideStop,
          change: sliderfieldsSlideChange,
          create: sliderfieldsSlideCreate
        });

        $(document).bind('state:disabled', function(e) {
          // Only act when this change was triggered by a dependency and not by the
          // element monitoring itself.
          if (e.trigger) {
            var state = 'disable';
            if (e.value) state = 'disable'; else state = 'enable';
            $(e.target).find('.sliderfield-container').slider(state);
            $(e.target).find('select, input, textarea').attr('disabled', e.value);
            // Note: WebKit nightlies don't reflect that change correctly.
            // See https://bugs.webkit.org/show_bug.cgi?id=23789
          }
        });
        if (setting.display_ignore_button) {
          $slider.parent().find('.sliderfield-ignore').change(function() {
            var $slider = $(this).parent().parent().find('.sliderfield, .webform-sliderfield');
            var $slider_container = $slider.find('.sliderfield-container');
            $slider_id = $slider.attr('id');
            var setting = Drupal.settings['sliderfield_' + $slider_id];
            if ($(this).is(':checked')) {
              $(this).parent().parent().find('.sliderfield-value-field').val('');
              $(this).parent().parent().find('.sliderfield-value2-field').val('');
              if (setting.fields_to_sync_css_selector) {
                $(setting.fields_to_sync_css_selector).val('');
              }
              $slider_container.slider( "disable" );
            } else {
              $slider_container.slider( "enable" );
            }
          });
        }
        if (setting.disabled || ($value == '' && setting.display_ignore_button)) {
          $(this).slider( "disable" );
        }

        sliderfieldsSlideUpdateFields($slider, {value: $value, values: $values});

        // Adjust the range when the target field is changed
		if (setting.adjust_field_max_css_selector || setting.adjust_field_min_css_selector) {
		  var adjust_field_css_selector = '';
		  if (setting.adjust_field_max_css_selector) {
		    adjust_field_css_selector = setting.adjust_field_max_css_selector;
		  }
		  if (setting.adjust_field_min_css_selector) {
		    if (!adjust_field_css_selector) {
			  adjust_field_css_selector += ',';
			}
		    adjust_field_css_selector += setting.adjust_field_min_css_selector;
		  }
          var adjust_field = $(adjust_field_css_selector);
          if (adjust_field.length) {
            adjust_field.bind('keyup', function(event) {
              var $target = $(event.target);
              var option_name = "";
              var target_value = parseInt($target.val());
              if (target_value) {
                if ($(setting.adjust_field_min_css_selector).index(event.target) != -1) {
                  option_name = "min";
                  $slider.find('.sliderfield-min-value-field', context).val(target_value);
                } else if ($(setting.adjust_field_max_css_selector).index(event.target) != -1) {
                  option_name = "max";
                  $slider.find('.sliderfield-max-value-field', context).val(target_value);
                }
                var $SliderField = $slider.find('.sliderfield-container', context);
                $SliderField.slider("option", option_name, target_value);
                $SliderField.slider("option", {
                  "value" : $SliderField.slider('value'),
                  "values" : $SliderField.slider('values')
                });
              }
            });
            adjust_field.trigger('keyup');
	      }
        }

        if (setting.hide_slider_handle_when_no_value && $value == '') {
          $slider.find('.ui-slider-handle').hide();
        }
      });



      // Bind first textfield changes
      $('.sliderfield-value-field:not(.sliderfield-processed)', context)
          .addClass('sliderfield-processed')
          .keyup(function(e) {
            // Get container
            var $slider = $(this).parents('.sliderfield', context);
            $slider_id = $slider.attr('id');
            var setting = Drupal.settings['sliderfield_' + $slider_id];

            // Left input value
            var $value = $(this).val();
            if ($value != '') {
              $value = $value - 0;
              if (isNaN($value)) {
                $value = 0;
                $slider.find('.sliderfield-value-field', context).val($value);
              }

              // Get slider max value
              var $SliderField = $slider.find('.sliderfield-container', context);
              var $max = $SliderField.slider('option', 'max');

              // Validate left input
              if ($value > $max) {
                $value = $max;
                $slider.find('.sliderfield-value-field', context).val($value);
              }

              // Setup right value
              //$slider.find('.sliderfield-right-field', context).val($max - $left);

              // Move slider without toggling events
              $SliderField.slider({value: $value});

              if (!setting.disabled && setting.display_ignore_button) {
                $SliderField.slider( "enable" );
              }
            }
          });

      // Bind second textfield changes
      $('.sliderfield-value2-field:not(.sliderfield-processed)', context)
          .addClass('sliderfield-processed')
          .keyup(function(e) {

            // Get container
            var $slider = $(this).parents('.sliderfield', context);
            $slider_id = $slider.attr('id');
            var setting = Drupal.settings['sliderfield_' + $slider_id];

            // Left input value
            var $value = $(this).val();
            if ($value != '') {
              $value = $value - 0;
              if (isNaN($value)) {
                $value = 0;
                $slider.find('.sliderfield-value2-field', context).val($value);
              }

              // Get slider max value
              var $SliderField = $slider.find('.sliderfield-container', context);
              var $max = $SliderField.slider('option', 'max');

              // Validate left input
              if ($value > $max) {
                $value = $max;
                $slider.find('.sliderfield-value2-field', context).val($value);
              }

              // Setup right value
              //$slider.find('.sliderfield-right-field', context).val($max - $left);

              // Move slider without toggling events
              $SliderField.slider('values', 1, $value);

              if (!setting.disabled && setting.display_ignore_button) {
                $SliderField.slider( "enable" );
              }
            }
          });
    }
  }

  var sliderfieldsSlideStop = function($slider, ui) {
    var $slider = $(this).parents('.sliderfield');
    $slider_id = $slider.attr('id');
    var setting = Drupal.settings['sliderfield_' + $slider_id];
    // Execute a change on the value text areas to initiate any ajax calls.
    $value = $slider.find('.sliderfield-value-field').change();
    $value2 = $slider.find('.sliderfield-value2-field').change();
    if (ui.value) {
      //setting.value = ui.value;
      //setting.current_value = ui.value;
    }
  }

  // Slider update related fields
  var sliderfieldsSlideUpdateFields = function($slider, ui) {
    $slider_id = $slider.attr('id');
    var setting = Drupal.settings['sliderfield_' + $slider_id];

    var $values = [];
    if ($slider.find('.sliderfield-value2-field').length > 0) {
      $slider.find('.sliderfield-value-field').val(ui.values[0]);
      $slider.find('.sliderfield-value2-field').val(ui.values[1]);
      $values = ui.values;

    } else {
      $slider.find('.sliderfield-value-field').val(ui.value);
      $values.push(ui.value);
    }
    for(var i = 0; i < $values.length; i++) {
      // Update handler bubble
      if (setting.display_bubble) {
        if (setting.display_bubble_format.indexOf('||') > 0) {
          var bubble_formats = setting.display_bubble_format.split('||');
          var bubble_value = bubble_formats[i].replace('%{value}%', $values[i]);
        } else {
          var bubble_value = setting.display_bubble_format.replace('%{value}%', $values[i]);
        }
        $('#' + $slider_id + ' .ui-slider-handle:eq(' + i + ') .sliderfield-bubble').html(bubble_value);
      }
      $values[i] = setting.display_values_format.replace('%{value}%', $values[i]);
    }
    $slider.find('.sliderfield-display-values-field').html($values.join(' - '));
  }

  var sliderfieldsSlideChange = function(event, ui) {
    // Setup values
    var $slider = $(this).parents('.sliderfield');
    sliderfieldsSlideUpdateFields($slider, ui);

    $slider_id = $slider.attr('id');
    var setting = Drupal.settings['sliderfield_' + $slider_id];
    $slider.find('.ui-slider-handle').show();
    // Sync other sliders in the same group
    if (setting.group) {
      var $group_sliders = $('.sliderfield:[id!="' + $slider_id + '"].sliderfield-group-' + setting.group);
      if ($('.sliderfield:[id!="' + $slider_id + '"].sliderfield-group-master.sliderfield-group-' + setting.group).length < 1) {
        var $group_slider;
        var $group_slider_settings;
        var $group_ui;
        for(var i = 0; i < $group_sliders.length; i++) {
          $group_slider = $($group_sliders[i]);
          $group_ui = $group_slider.find('.sliderfield-container');
          $group_slider_settings = Drupal.settings['sliderfield_' + $group_slider.attr('id')];

          sliderfieldsSlideUpdateFields($group_slider, {value:$group_ui.slider('value'), values: $group_ui.slider('values')});

          $group_slider_settings.value = $group_ui.slider('value');
        }
      }
    }

    if (ui.value) {
      setting.value = ui.value;
    }

    //Manually trigger element change event for compatibility with Drupal's ajax system
    $slider.find('.sliderfield-value-field').trigger('change');
    if (setting.fields_to_sync_css_selector) {
        $(setting.fields_to_sync_css_selector).val(ui.value);
    }
  }

  var sliderfieldsSlideCreate = function(event, ui) {
    var $slider = $(this).parents('.sliderfield');
    $slider_id = $slider.attr('id');
    var setting = Drupal.settings['sliderfield_' + $slider_id];

    // Add bubble to each handler
    if (setting.display_bubble) {
      var handle = $(this).find('.ui-slider-handle');
      var bubble_value = '';
      var bubble = $('<div class="sliderfield-bubble-wrapper"><div class="sliderfield-bubble">' + bubble_value + '</div></div>');
      handle.append(bubble);
    }
  }

  // Slider processor
  var sliderfieldsSlideProcess = function(event, ui) {
    // Setup values
    var $slider = $(this).parents('.sliderfield');
    sliderfieldsSlideUpdateFields($slider, ui);

    $slider_id = $slider.attr('id');
    var setting = Drupal.settings['sliderfield_' + $slider_id];

    // Sync other sliders in the same group
    if (setting.group) {
      var $value_diff_orig = ui.value - setting.value;
      //var value_diff = ui.value - setting.current_value;

      var $group_sliders = $('.sliderfield:[id!="' + $slider_id + '"].sliderfield-group-' + setting.group);
      if ($('.sliderfield:[id!="' + $slider_id + '"].sliderfield-group-master.sliderfield-group-' + setting.group).length < 1) {
        var $group_slider;
        var $group_slider_settings;
        var $group_ui;
        var $items = new Array();
        var $total_diff = $value_diff_orig;
        var $total_diff_items_no = $group_sliders.length;
        var $val;

        for(var i = 0; i < $group_sliders.length; i++) {
          $group_slider = $($group_sliders[i]);
          $group_slider_settings = Drupal.settings['sliderfield_' + $group_slider.attr('id')];
          $items[i] = {value: $group_slider_settings.value, index: i};
        }
        var sortFunc = function(data_A, data_B)
        {
          return (data_A.value - data_B.value);
        }
        $items.sort(sortFunc);

        for(var i = 0; i < $group_sliders.length; i++) {
          var n = $items[i].index;
          $group_slider = $($group_sliders[n]);
          $group_ui = $group_slider.find('.sliderfield-container');
          $group_slider_settings = Drupal.settings['sliderfield_' + $group_slider.attr('id')];

          $group_ui.slider({slide: function() {}, change: function() {}});

          if (setting.group_type == 'same') {
            $group_ui.slider('value', ui.value);
          }
          if (setting.group_type == 'lock') {
            $group_ui.slider('value', $group_slider_settings.value + $value_diff_orig);
          }
          if (setting.group_type == 'total') {
            $val = $group_slider_settings.value - ($total_diff / $total_diff_items_no);
            $total_diff = $total_diff - ($total_diff / $total_diff_items_no);
            $total_diff_items_no = $total_diff_items_no - 1;
            if ($val < 0) {
              $total_diff = $total_diff + (-1 * $val);
              $val = 0;
            }

            $group_ui.slider('value', $val);
          }

          $group_ui.slider({slide: sliderfieldsSlideProcess, change: sliderfieldsSlideChange});

          sliderfieldsSlideUpdateFields($group_slider, {value:$group_ui.slider('value'), values: $group_ui.slider('values')});
        }
      }
    }
  }

})(jQuery, Drupal);
