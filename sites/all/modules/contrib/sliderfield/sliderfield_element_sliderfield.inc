<?php

/**
 * Implements hook_theme().
 */
function _sliderfield_theme_sliderfield() {
  $data['sliderfield_sliderfield'] = array(
    'render element' => 'element',
    'file' => 'sliderfield_element_sliderfield.inc',
  );
  return $data;
}

/**
 * Implements hook_element_info().
 */
function _sliderfield_element_info_sliderfield() {
  $types['slider'] =  array(
    '#input'            => TRUE,
    '#process'          => array('_sliderfield_sliderfield_process'),
    //'#value_callback'   => 'sliderfield_sliderfield_value_callback',
    '#element_validate' => array('sliderfield_sliderfield_validate'),
    '#theme'   => array('sliderfield_sliderfield'),
    '#theme_wrappers'   => array('form_element'),

    '#title' => NULL,
    '#title2' => NULL,
    '#input_title' => t('Min'),
    '#input2_title' => t('Max'),
    /**
    * Make the min value adjustable dynamically via another element
    * Type of the value is CSS selector
    * like .myfield, #element_id
    */
    '#adjust_field_min' => NULL,
    /**
    * Make the max value adjustable dynamically via another element
    * Type of the value is CSS selector
    * like .myfield, #element_id
    */
    '#adjust_field_max' => NULL,
    /**
     * Boolean: When set to true, the handle will animate with the default duration.
     * String: The name of a speed, such as "fast" or "slow".
     * Number: The duration of the animation, in milliseconds.
     */
    '#animate' => 'fast',
    /**
     * Disables the slider if set to true.
     */
    '#disabled' => FALSE,
    /**
     * The maximum value of the slider.
     */
    '#max' => 100,
    /**
     * The minimum value of the slider.
     */
    '#min' => 0,
    /**
     * Determines whether the slider handles move horizontally (min on left, max on right)
     * or vertically (min on bottom, max on top). Possible values: "horizontal", "vertical".
     */
    '#orientation' => 'horizontal',
    /**
     * Whether the slider represents a range.
     * Multiple types supported:
     *   Boolean: If set to true, the slider will detect if you have two handles and create a stylable range element between these two.
     *   String: Either "min" or "max". A min range goes from the slider min to one handle. A max range goes from one handle to the slider max.
     */
    '#range' => FALSE,
    /**
     * Determines the size or amount of each interval or step the slider takes between the min and max.
     * The full specified value range of the slider (max - min) should be evenly divisible by the step.
     */
    '#step' => 1,
    /**
     * Determines the value of the slider, if there's only one handle.
     * If there is more than one handle, determines the value of the first handle.
     * Or an array of values can be passed array('value'=>1 , 'value2'=> 2) ,
     * the order of values is important
     */
    //'#value' => 0,
    '#default_value' => NULL,
    /**
     * Some default color styles for ease of use
     * red, green, blue
     */
    '#slider_style' => NULL,
    /**
     * Default size for input values
     */
    '#size' => 3,
    /**
     * If set to FALSE will display inputs only when javascript is disabled
     */
    '#display_inputs' => TRUE,
    /**
     * If enabled display the current values of slider
     * as simple text
     */
    '#display_values' => FALSE,
    /**
     * Format of the displayed values
     * The usage is mostly for showing $,% or other signs near the value
     */
    '#display_values_format' => '%{value}%',
    /**
     * Display a hint/bubble near each slider handle showing the value of that handle
     */
	'#display_bubble' => FALSE,
	/**
	* Format of the displaied values in bubble/hint, The usage is mostly for showing $,% or other signs near the value. Use %{value}% as slider value
	* For range slider it can have two values separated by || like "$%{value}%MIN||$%{value}%MAX"
	*/
	'#display_bubble_format' => '%{value}%',
    /**
     * Acceptable types are the same as css with and height and it will be used as width
     * or height depending on #orientation
     */
    '#slider_length' => NULL,
    /**
     * Display the element inside a fieldset
     */
    '#display_inside_fieldset' => FALSE,
    /**
     * Sliders with the same group will be linked
     * The behavior of linked sliders depends on group_type parameter
     * group name can only contain letters, numbers and underscore
     */
    '#group' => NULL,
    /**
     * same : All sliders in the same group will have the same value.
     * lock : All sliders in the same group will move with the exact same amount
     * total : The total value of all sliders will be between min/max , increasing value of
     *         one slider decreases the rest of the sliders in the same group
     */
    '#group_type' => 'same',
    /**
     * When set to TRUE, other sliders in the same
     * group will change only if this slider changes
     * values : TRUE , FALSE
     */
    '#group_master' => FALSE,
    /**
     * Disable buildin range validation
     * useful when element is used as widget
     * for fields, since integer fields have range validation
     * values : TRUE , FALSE
     */
    '#validate_range' => TRUE,
    /**
     * In case there are other fields that should be sync dynamically when
     * the slider changes
     * value : .my_field_css_class
     */
    '#fields_to_sync_css_selector' => NULL,
     /**
      * When field is not required, and display_inputs option is inactive
      * a checkbox will be shown allowing user to ignore the field
      * and enter no value
      * values : TRUE , FALSE
      */
     '#display_ignore_button' => FALSE,
     /**
      * When the slider does not have any value by enabling this option it won't show the
      * the slider handle unless user clicks on the slider to select a value
      * values : TRUE , FALSE
      */
     '#hide_slider_handle_when_no_value' => FALSE,
  );
  $types['jslider'] = $types['slider'];
  return $types;
}

/**
 * Processes transfer slider: add textfields
 * @param unknown_type $element
 */
function _sliderfield_element_sliderfield_structure($element, &$form_state) {
  $element['#tree'] = TRUE;
  /*
  $values = NULL;
  $input = NULL;
  if (isset($form_state['values'])) {
    $values = drupal_array_get_nested_value($form_state['values'], $element['#parents']);
    $input = drupal_array_get_nested_value($form_state['input'], $element['#parents']);
  }
  */

  if (is_array($element['#value'])) {
    $value = isset($element['#value']['value']) ? $element['#value']['value'] : NULL;
    $value2 = isset($element['#value']['value2']) ? $element['#value']['value2'] : NULL;
  } else {
    $value = $element['#value'];
    $value2 = NULL;
  }

  if ($element['#display_inside_fieldset']) {
    $element['slider'] = array(
      '#type'             => 'fieldset',
      '#title'    => $element['#title']
    );
  } elseif ($element['#title']) {
    $element['slider'] = array(
      '#type' => 'container'
    );
    /*
    $element['slider']['title'] = array(
      '#type'             => 'item',
      '#markup'    => '<label>' . $element['#title'] . '</label>'
    );
    */
  }

  if (!is_null($value) && $value !== '') {
    if ($value < $element['#min']) {
      $value = $element['#min'];
    }
    if ($value > $element['#max']) {
      $value = $element['#max'];
    }
  }
  $values = array();
  $values[] = $value;

  $group_css = '';
  if ($element['#group']) {
    $group_css = 'sliderfield-group-' . $element['#group'];

    if ($element['#group_master']) {
      $group_css .= ' sliderfield-group-master';
    }
  }

  if ($element['#display_ignore_button'] && !$element['#display_inputs']) {
      $element['ignore'] = array(
        '#type' => 'checkbox',
        '#title' => t('Not Selected (Uncheck to select a value)'),
        '#value' => (is_null($value) || $value === ''),
        '#disabled' => $element['#disabled'],
        '#attributes' => array('class' => array('sliderfield-ignore'))
      );
  }

  // Generate input for slider
  $element['value'] = array(
    '#tree'             => TRUE,
    '#prefix'           => '<div id="' . $element['#id'] . '" class="sliderfield ' . $group_css . '">' . '<div class="sliderfield-event-field-container">',
    '#suffix' => '</div>',
    '#type'             => 'textfield',
    '#required'    => $element['#required'],
    '#element_validate' => array('sliderfield_validate_number'),
    '#title'             => $element['#input_title'],
    '#default_value'    => $value,
    '#disabled'    => $element['#disabled'],
    '#size'             => $element['#size'],
    '#attributes'       => array('class' => array('sliderfield-value-field')),
  );

  //Only show title for input fields when there is more than one value
  if (is_null($value2)) {
    $element['value']['#title'] = NULL;
  }

  #--(Begin)--> For Ajax compatibility
  if (isset($element['#ajax'])) {
    $ajax = @$element['#ajax'];
    if (!isset($ajax['trigger_as']) && isset($element['#name'])) {
      $value = NULL;
      $ajax['trigger_as'] = array(
        'name' => $element['#name'],
        'value' => $value
      );
    }
    if (!isset($ajax['event'])) {
      $ajax['event'] = 'change';
    }
    // Generate input for slider
    $element['value']['#ajax'] = $ajax;
  }
  #--(End)--> For Ajax compatibility

  if (!is_null($value2)) {
    if (!is_null($value2) && $value2 !== '') {
      if ($value2 < $element['#min']) {
        $value2 = $element['#min'];
      }
      if ($value2 > $element['#max']) {
        $value2 = $element['#max'];
      }
    }
    if ($value2 < $value) {
      $value2 = $value;
    }
    $values[] = $value2;
    $element['value2'] = array(
      '#type'             => 'textfield',
      '#default_value'    => $value2,
      '#required'    => $element['#required'],
      '#title'             => $element['#input2_title'],
      '#element_validate' => array('sliderfield_validate_number'),
      '#disabled'    => $element['#disabled'],
      '#size'             => $element['#size'],
      '#attributes'       => array('class' => array('sliderfield-value2-field')),
    );
  }

  if ($element['#range'] === TRUE && (!isset($value2) || is_null($value2))) {
    $element['#range'] = FALSE;
  }

  if ($element['#display_values']) {
    foreach ($values as $key => $value) {
      $values[$key] = str_replace('%{value}%', $value ,$element['#display_values_format']);
    }
    $element['values_text'] = array(
      '#markup'     => '<div class="sliderfield-display-values-field">' . htmlentities(implode(' - ',  $values)) . '</div>'
    );
  }

  $style = NULL;
  if (!is_null($element['#slider_length'])) {
    if ($element['#orientation'] == 'horizontal') {
      $style = "width : {$element['#slider_length']}";
    } else {
      $style = "height : {$element['#slider_length']}";
    }
  }
  if ($element['#hide_slider_handle_when_no_value']) {
    $element['note'] = array(
      '#type' => 'markup',
      '#markup' => '<div class="sliderfield-selectvalue-description">' . t('Please click on any part of the slider to select a value') . '</div>'
    );
  }

 $_attributes_new = array('class' => array('sliderfield-container', $element['#slider_style']), 'style' => $style);
 if (isset($element['#attributes']) && is_array($element['#attributes'])) {
   $_attributes_new = drupal_array_merge_deep($_attributes_new, $element['#attributes']);
 }
 // Create markup for slider container
  $element['container'] = array(
    '#type' => 'container',
    '#attributes' => $_attributes_new,
    '#attached' => array(
      'library' => array(
        array('system', 'ui.slider')
      ),
      'js' => array(
        drupal_get_path('module', 'sliderfield') . '/sliderfield_element_sliderfield.js',
        array(
          'data' => array(
            'sliderfield_' . $element['#id'] => array(
              'animate' => $element['#animate'],
              'adjust_field_min_css_selector' => $element['#adjust_field_min'],
              'adjust_field_max_css_selector' => $element['#adjust_field_max'],
              'disabled' => $element['#disabled'],
              'max' => $element['#max'] * 1,
              'min' => $element['#min'] * 1,
              'orientation' => $element['#orientation'],
              'range' => $element['#range'],
              'step' => $element['#step'] * 1,
              'display_inputs' => $element['#display_inputs'],
              'display_values_format' => $element['#display_values_format'],
              'display_bubble' => $element['#display_bubble'],'display_bubble' => $element['#display_bubble'],
              'display_bubble_format' => $element['#display_bubble_format'],
              'display_values' => $element['#display_values'],
              'group' => $element['#group'],
              'group_type' => $element['#group_type'],
              'group_master' => $element['#group_master'],
              'fields_to_sync_css_selector' => $element['#fields_to_sync_css_selector'],
              'display_ignore_button' => $element['#display_ignore_button'],
              'hide_slider_handle_when_no_value' => $element['#hide_slider_handle_when_no_value']
            )
          ),
          'type' => 'setting',
        )
      ),
      'css' => array(
        array(
          'data' => drupal_get_path('module', 'sliderfield') . '/sliderfield_element_sliderfield.css',
          'type' => 'file',
          //'group' => CSS_SYSTEM,
          'weight' => 2000,
        )
      ),
    ),

    '#markup' => '',
    '#suffix' => '</div>'
  );

  if ($element['#title2']) {
    $element['title2'] = array(
      '#type'   => 'item',
      '#markup' => '<label>' . $element['#title2'] . '</label>'
    );
  }

  // Generate input for sliders with adjustable min/max
  if (!empty($element['#adjust_field_min'])) {
    $element['container']['min_value'] = array(
      '#tree'       => TRUE,
      '#type'       => 'hidden',
      '#default_value' => $element['#min'],
      '#attributes' => array('class' => array('sliderfield-min-value-field')),
    );
  }
  if (!empty($element['#adjust_field_max'])) {
    $element['container']['max_value'] = array(
      '#tree'       => TRUE,
      '#type'       => 'hidden',
      '#default_value' => $element['#max'],
      '#attributes' => array('class' => array('sliderfield-max-value-field')),
    );
  }

  //$element = ajax_pre_render_element($element);
  //dpm($element);

  return $element;
}

/**
 * Processes transfer slider: add textfields
 * @param unknown_type $element
 */
function _sliderfield_sliderfield_process($element, &$form_state) {
  $element = _sliderfield_element_sliderfield_structure($element, $form_state);
  $element['#process_called'] = TRUE;
  return $element;
}


/**
 * Validates sliderfield
 *
 * @param array $element
 * @param array $form_state
 */
function sliderfield_sliderfield_validate($element, &$form_state) {
  $form_state_value = $form_state['values'];
  foreach ($element['#parents'] as $parent) {
    $form_state_value = isset($form_state_value[$parent]) ? $form_state_value[$parent] : 0;
  }
  $element_value = $form_state_value;

  #--(Begin)--> Correct the value
  //watchdog('element_value', print_r($element_value['value'], true));
  //form_set_value($element, $element_value, $form_state);
  #--(End)--> Correct the value

  if ($element['#validate_range']) {
    if (@isset($form_state['values']['instance']['settings']['min'])) {
      $element['#max'] = $form_state['values']['instance']['settings']['max'];
      $element['#min'] = $form_state['values']['instance']['settings']['min'];
    }
    if ($element_value['value'] > $element['#max'] || $element_value['value'] < $element['#min']) {
      form_error($element, t("The entered values are not within valid range."));
    }
    if (isset($element_value['value2']) && is_null($element_value['value2']))
    if ($element_value['value2'] > $element['#max'] || $element_value['value2'] < $element['#min']) {
      form_error($element, t("The entered values are not within valid range."));
    }
  }
}

/**
 * Theme output of sliderfield
 *
 * @param array $element
 */
function theme_sliderfield_sliderfield($vars) {
  if (!isset($variables['element']['#process_called']) && 1==0) {
    $element = _sliderfield_element_sliderfield_structure($variables['element']);
    $html = '';
    if (isset($element['slider'])) {
      $html .= drupal_render($element['slider']);
    }

    return $html;
  }
}




/**
 *
 */
function _sliderfield_field_widget_info_sliderfield() {
  return array(
    'sliderfield' => array(
      'label' => t('Slider'),
      'field types' => array('number_decimal', 'number_integer', 'number_float'),
      'behaviors' => array(
        'multiple values' => FIELD_BEHAVIOR_CUSTOM,
      ),
      'settings' => array(
        'sliderfield_settings' => array(
          /**
           * Boolean: When set to true, the handle will animate with the default duration.
           * String: The name of a speed, such as "fast" or "slow".
           * Number: The duration of the animation, in milliseconds.
           */
          'animate' => TRUE,
          /**
          * Make the min value adjustable dynamically via another element
          * Type of the value is field name
          */
          'adjust_field_min' => NULL,
          /**
          * Make the max value adjustable dynamically via another element
          * Type of the value is field name
          */
          'adjust_field_max' => NULL,
          /**
           * Determines whether the slider handles move horizontally (min on left, max on right)
           * or vertically (min on bottom, max on top). Possible values: "horizontal", "vertical".
           */
          'orientation' => 'horizontal',
          /**
           * Whether the slider represents a range.
           * Multiple types supported:
           *   Boolean: If set to true, the slider will detect if you have two handles and create a stylable range element between these two.
           *   String: Either "min" or "max". A min range goes from the slider min to one handle. A max range goes from one handle to the slider max.
           */
          'range' => FALSE,
          /**
           * Determines the size or amount of each interval or step the slider takes between the min and max.
           * The full specified value range of the slider (max - min) should be evenly divisible by the step.
           */
          'step' => 1,
          /**
           * Some default color styles for ease of use
           * red, green, blue
           */
          'slider_style' => NULL,
          /**
           * If enabled display the current values of slider
           * as simple text
           */
          'display_values' => TRUE,
          /**
           * Format of the displaied values
           * The usage is mostly for showing $,% or other signs near the value
           */
          'display_values_format' => '%{value}%',
          /**
           * Display a hint/bubble near each slider handle showing the value of that handle
           */
          'display_bubble' => FALSE,
          /**
           * Format of the displaied value in bubble/hint
           * The usage is mostly for showing $,% or other signs near the value
		   * For range slider it can have two values separated by || like "$%{value}%MIN||$%{value}%MAX"
           */
          'display_bubble_format' => '%{value}%',
          /**
           * Acceptable types are the same as css with and height and it will be used as width
           * or height depending on #orientation
           */
          'slider_length' => NULL,
          /**
           *
           */
          'hide_inputs' => TRUE,
          /**
           * Whether the slider represents more than one value.
           * Multiple types supported:
           *   0/False: Disabled.
           *   "separate" : Enabled. Uses field's multi value feature to store the values, currently only 2 values are supported.
		   *        A separate handle for each value will be shown on slider
           */
          'multi_value' => FALSE,
          /**
           * When field is not required, and display_inputs option is inactive
           * a checkbox will be shown allowing user to ignore the field
           * and enter no value
           */
          'display_ignore_button' => TRUE,
          /**
           * When the slider does not have any value by enabling this option it won't show the
           * the slider handle unless user clicks on the slider to select a value
           */
          'hide_slider_handle_when_no_value' => FALSE,
        )
      ),
    ),
  );
}

/**
 * @param $field
 * @param $instance
 */
function _sliderfield_field_widget_settings_form_sliderfield($field = NULL, $instance = NULL) {
  $widget = $instance['widget'];
  $form = array();
  if ($widget['type'] == 'sliderfield') {
    $settings = $widget['settings']['sliderfield_settings'];
    $form['sliderfield_settings'] = array(
      '#type' => 'fieldset',
      '#title' => t('Slider Settings'),
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
      '#weight' => 0
    );

    if (!is_null($field) && !is_null($instance)) {
      $entity_fields = field_info_instances($instance['entity_type'], $instance['bundle']);
      $all_fields = field_info_fields();
      $supported_field_types = array('number_decimal', 'number_integer', 'number_float');
      $valid_fields = array();

      // Get a list of all valid fields that we both support and are part of this entity
      foreach ($all_fields as $_field) {
        if (array_key_exists($_field['field_name'], $entity_fields)) {
          if (in_array($_field['type'], array_values($supported_field_types)) && ($_field['field_name'] != $field['field_name'])) {
             $valid_fields[$_field['field_name']] = $entity_fields[$_field['field_name']]['label'];
          }
        }
      }

     $valid_fields = array('' => '--') + $valid_fields;
     $form['sliderfield_settings']['adjust_field_min'] = array(
       '#type' => 'select',
       '#title' => t('Adjust the Minimum value from field'),
       '#default_value' => isset($settings['adjust_field_min']) ? $settings['adjust_field_min']: '',
       '#options' => $valid_fields,
       '#description' => t('Select which field you would like to use to adjust the slider\'s Minimum value.'),
     );

     $valid_fields = array('' => '--') + $valid_fields;
     $form['sliderfield_settings']['adjust_field_max'] = array(
        '#type' => 'select',
        '#title' => t('Adjust the Maximum value from field'),
        '#default_value' => isset($settings['adjust_field_max']) ? $settings['adjust_field_max']: '',
        '#options' => $valid_fields,
        '#description' => t('Select which field you would like to use to adjust the slider\'s Maximum value.'),
      );
    }



    $form['sliderfield_settings']['animate'] = array(
      '#type' => 'select',
      '#title' => t('Animate'),
      '#options' => array(
        FALSE => t('Disable'),
        TRUE => t('Default'),
        'fast' => t('Fast'),
        'slow' => t('Slow'),
        'custom' => t('Custom')
      ),
      //'#description' => t('Determines whether the slider handles move horizontally (min on left, max on right) or vertically (min on bottom, max on top).'),
      '#default_value' => $settings['animate']
    );
    $form['sliderfield_settings']['orientation'] = array(
      '#type' => 'select',
      '#title' => t('Orientation'),
      '#options' => array(
        'horizontal' => t('Horizontal'),
        'vertical' => t('Vertical')
      ),
      '#require' => TRUE,
      '#description' => t('Determines whether the slider handles move horizontally (min on left, max on right) or vertically (min on bottom, max on top).'),
      '#default_value' => $settings['orientation']
    );
    $form['sliderfield_settings']['range'] = array(
      '#type' => 'select',
      '#title' => t('Range'),
      '#options' => array(
        FALSE => t('Disable'),
        TRUE => t('Auto'),
        'min' => t('Minimum'),
        'max' => t('Maximum')
      ),
      '#description' => t('Whether the slider represents a range.'),
      '#default_value' => $settings['range']
    );
    $form['sliderfield_settings']['step'] = array(
      '#type' => 'textfield',
      '#title' => t('Step'),
      '#size' => 5,
      '#description' => t('Determines the size or amount of each interval or step the slider takes between the min and max. The full specified value range of the slider (max - min) should be evenly divisible by the step.'),
      '#required' => TRUE,
      '#element_validate' => array('sliderfield_validate_positive_number'),
      '#default_value' => $settings['step']
    );
    $form['sliderfield_settings']['slider_style'] = array(
      '#type' => 'select',
      '#title' => t('Style'),
      '#options' => sliderfield_get_styles(),
      '#description' => t('Some default color styles for ease of use'),
      '#default_value' => $settings['slider_style']
    );
    $form['sliderfield_settings']['display_values'] = array(
      '#type' => 'checkbox',
      '#title' => t('Display Values'),
      '#description' => t('If enabled display the current values of slider as simple text.'),
      '#default_value' => $settings['display_values']
    );
	if (!isset($settings['display_values_format'])) $settings['display_values_format'] = '%{value}%';
    $form['sliderfield_settings']['display_values_format'] = array(
      '#type' => 'textfield',
      '#title' => t('Display Values Format'),
      '#size' => 15,
      '#description' => t('Format of the displaied values, The usage is mostly for showing $,% or other signs near the value. Use %{value}% as slider value'),
      '#default_value' => $settings['display_values_format']
    );
	if (!isset($settings['display_bubble'])) $settings['display_bubble'] = FALSE;
    $form['sliderfield_settings']['display_bubble'] = array(
      '#type' => 'checkbox',
      '#title' => t('Display bubble/hint'),
      '#description' => t('Display a hint/bubble near each slider handle showing the value of that handle.'),
      '#default_value' => $settings['display_bubble']
    );
	if (!isset($settings['display_bubble_format'])) $settings['display_bubble_format'] = '%{value}%';
    $form['sliderfield_settings']['display_bubble_format'] = array(
      '#type' => 'textfield',
	  '#size' => 15,
      '#title' => t('Display bubble/hint format'),
      '#description' => t('Format of the displaied values in bubble/hint, The usage is mostly for showing $,% or other signs near the value. Use %{value}% as slider value. For range slider it can have two values separated by || like "$%{value}%MIN||$%{value}%MAX"'),
      '#default_value' => $settings['display_bubble_format']
    );
    $form['sliderfield_settings']['slider_length'] = array(
      '#type' => 'textfield',
      '#title' => t('Slider Length'),
      '#size' => 5,
      '#description' => t('Acceptable types are the same as css width and height (100px) and it will be used as width or height depending on #orientation'),
      '#default_value' => $settings['slider_length']
    );
    $form['sliderfield_settings']['hide_inputs'] = array(
      '#type' => 'checkbox',
      '#title' => t('Hide Input Textfields'),
      '#description' => t('If enabled displays only the slider and hides input textfields.'),
      '#default_value' => $settings['hide_inputs']
    );
    $form['sliderfield_settings']['multi_value'] = array(
      '#type' => 'select',
      '#title' => t('Multi Value'),
      '#options' => array(
        FALSE => t('Disable'),
        'separate' => t('Enable')
      ),
      '#description' => t('Uses field\'s multi value feature to store the values, currently only 2 values are supported. A separate handle for each value will be shown on slider'),
      '#default_value' => (!isset($settings['multi_value'])) ? '' : $settings['multi_value']
    );
    $form['sliderfield_settings']['display_ignore_button'] = array(
      '#type' => 'checkbox',
      '#title' => t('Display ignore button'),
      '#description' => t('When field is not required, and hide input fields option is active a checkbox will be shown allowing user to ignore the field allowing user to ignore the field and enter no value.'),
      '#default_value' => $settings['display_ignore_button'],
    );
    $form['sliderfield_settings']['hide_slider_handle_when_no_value'] = array(
      '#type' => 'checkbox',
      '#title' => t('Hide slider handle when there is no value'),
      '#description' => t('When the slider does not have any value by enabling this option it won\'t show the the slider handle unless user clicks on the slider to select a value.'),
      '#default_value' => $settings['hide_slider_handle_when_no_value']
    );
  }

  return $form;
}

/**
 * @param $form
 * @param $form_state
 * @param $field
 * @param $instance
 * @param $langcode
 * @param $items
 * @param $delta
 * @param $element
 * @return mixed
 */
function _sliderfield_field_widget_form(&$form, &$form_state, $field, $instance, $langcode, $items, $delta, $element) {
  switch ($instance['widget']['type']) {
    case 'sliderfield':
      if (!is_null($field)) {
        $multiple = $field['cardinality'] > 1 || $field['cardinality'] == FIELD_CARDINALITY_UNLIMITED;
      }
	  //$has_value = isset($items[0][$value_key]);

      $settings = $instance['widget']['settings']['sliderfield_settings'];
      $value = NULL;
      if (!empty($items) && isset($items[$delta]) && isset($items[$delta]['value'])) {
        $value = $items[$delta]['value'];
      } else {
        $value = $instance['settings']['min'];
      }
      $element['#element_validate'] = array('sliderfield_sliderfield_container_validate');
      if (!isset($settings['display_values_format'])) {
        $settings['display_values_format'] = '%{value}%';
      }
      if (!isset($settings['display_bubble'])) {
        $settings['display_bubble'] = FALSE;
      }
      if (!isset($settings['display_bubble_format'])) {
        $settings['display_bubble_format'] = '%{value}%';
      }
      //$element['#tree'] = FALSE;
      $element['value'] = array(
        //'#value_callback' => 'sliderfield_sliderfield_widget_value_callback',
        //'#tree' => FALSE,
        '#title' => $instance['label'],
        '#default_value' => $value,
        '#description' => $instance['description'],
        '#type' => 'slider',
        '#input_title' => NULL,
        '#required' => $instance['required'],
        '#input2_title' => t('Max'),
        '#animate' => $settings['animate'],
        '#adjust_field_min' => isset($settings['adjust_field_min'])? '.' . drupal_clean_css_identifier('sliderfield-field-adjust-' . $settings['adjust_field_min']) : '',
        '#adjust_field_max' => isset($settings['adjust_field_max'])? '.' . drupal_clean_css_identifier('sliderfield-field-adjust-' . $settings['adjust_field_max']) : '',
        '#disabled' => (isset($element['#disabled']))?$element['#disabled']:FALSE,
        '#max' => $instance['settings']['max'],
        '#min' => $instance['settings']['min'],
        '#orientation' => $settings['orientation'],
        '#range' => $settings['range'],
        '#step' => $settings['step'],
        '#slider_style' => $settings['slider_style'],
        '#size' => 3,
        '#display_inputs' => !$settings['hide_inputs'],
        '#display_values' => $settings['display_values'],
        '#display_values_format' => $settings['display_values_format'],
        '#slider_length' => $settings['slider_length'],
        '#display_inside_fieldset' => FALSE,
        '#validate_range' => FALSE,
        '#display_bubble' => $settings['display_bubble'],
        '#display_ignore_button' => $settings['display_ignore_button'],
        '#hide_slider_handle_when_no_value' => $settings['hide_slider_handle_when_no_value'],
        '#fields_to_sync_css_selector' => @$settings['fields_to_sync_css_selector']
      );
      break;
  }
  return $element;
}


function sliderfield_sliderfield_container_validate($element, &$form_state) {

  #--(Begin)--> Set min/max for sliders with adjustable min/max
  if (isset($element['value']['container']['max_value'])) {
    $form_state_value = $form_state['values'];
    foreach ($element['value']['container']['max_value']['#parents'] as $parent) {
      $form_state_value = isset($form_state_value[$parent]) ? $form_state_value[$parent] : 0;
    }
    $element_max_value = $form_state_value;
    $element['#max'] = $element_max_value;
	$field_state = field_form_get_state($element['#field_parents'], $element['#field_name'], $element['#language'], $form_state);
    $field_state['instance']['settings']['max'] = $element['#max'];
	field_form_set_state($element['#field_parents'], $element['#field_name'], $element['#language'], $form_state, $field_state);
	$s = field_widget_instance($element, $form_state);
  }
  if (isset($element['value']['container']['min_value'])) {
    $form_state_value = $form_state['values'];
    foreach ($element['value']['container']['min_value']['#parents'] as $parent) {
      $form_state_value = isset($form_state_value[$parent]) ? $form_state_value[$parent] : 0;
    }
    $element_min_value = $form_state_value;
    $element['#min'] = $element_min_value;
    $form_state['field'][$element['#field_name']][$element['#language']]['instance']['settings']['min'] = $element['#min'];
  }
  #--(End)--> Set min/max for sliders with adjustable min/max

  $form_state_value = $form_state['values'];
  foreach ($element['#parents'] as $parent) {
    $form_state_value = isset($form_state_value[$parent]) ? $form_state_value[$parent] : 0;
  }
  $element_value = $form_state_value;
  if (isset($element_value['value'])) {
    $element_value = $element_value['value'];
  }

  #--(Begin)--> Correct the value
  form_set_value($element, array('item' => $element_value), $form_state);
  #--(End)--> Correct the value
}

/**
 * @param $entity_type
 * @param $entity
 * @param $field
 * @param $instance
 * @param $langcode
 * @param $items
 * @param $errors
 */
function _sliderfield_sliderfield_field_validate($entity_type, $entity, $field, $instance, $langcode, $items, &$errors) {
  /*
  foreach ($items as $delta => $item) {
    if (!empty($item['value'])) {
    }
  }
  */
}


/**
 * @param $element
 * @param bool $input
 * @param $form_state
 * @return mixed
 */
function sliderfield_sliderfield_widget_value_callback(&$element, $input = FALSE, $form_state = NULL) {
  /*
  dpm('test');
  //return 100;
  if ($input) {
    //dpm($form_state);
    //dpm($element);
    $form_state_value = $form_state['input'];
    //$element['#parents'][] = 'value';
    foreach ($element['#parents'] as $parent) {
      $form_state_value = isset($form_state_value[$parent]) ? $form_state_value[$parent] : 0;
    }
    $element_value = $form_state_value;
    //dpm($element_value);
    return $element_value;
  }
  */
}


/**
 * @param $form
 * @param $form_state
 */
function _sliderfield_form_field_ui_field_edit_form_alter_sliderfield(&$form, &$form_state) {
  if ($form['#instance']['widget']['type'] == 'sliderfield') {
    $form['instance']['settings']['min']['#weight'] = 0;
    $form['instance']['settings']['max']['#weight'] = 0;
    $form['instance']['settings']['min']['#required'] = TRUE;
    $form['instance']['settings']['max']['#required'] = TRUE;
  }
}


/**
 * Implements hook_field_widget_form_alter().
 *
 * Add a css class to adjustment form elements, to enable them to be targeted
 * by the appropriate javascript.
 */
function _sliderfield_sliderfield_widget_field_widget_form_alter(&$element, &$form_state, $context) {
  $instance = $context['instance'];
  if ($instance['widget']['type'] == 'sliderfield') {
  }
  if ($instance['widget']['type'] == 'number') {
    $entity_fields = field_info_instances($instance['entity_type'], $instance['bundle']);
    if (array_key_exists($instance['field_name'], $entity_fields)) {
      $element['value']['#process'][] = '_sliderfield_sliderfield_widget_adjust_process';
    }
  }
}

/**
 * Helper function to add css class to adjustment elements.
 */
function _sliderfield_sliderfield_widget_adjust_process($element, &$form_state, $form) {
  $instance = field_widget_instance($element, $form_state);
  $widget_settings = $instance['widget']['settings'];
  $element['#attributes']['class'][] = 'sliderfield-field-adjust-'.drupal_clean_css_identifier($element['#field_name']);
  return $element;
}