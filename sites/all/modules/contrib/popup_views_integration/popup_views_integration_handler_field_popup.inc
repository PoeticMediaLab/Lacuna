<?php

/**
 * @file
 * Contain the integration with views
 * A handler to provide a field that is completely custom by the administrator.
 *
 * @ingroup views_field_handlers
 */

class popup_views_integration_handler_field_popup extends views_handler_field {
  function query() {
    $this->ensure_my_table();
    $this->add_additional_fields();
  }

  function option_definition() {
    $options = parent::option_definition();

    $options['link'] = array('default' => '');
    $options['title'] = array('default' => '');
    $options['text'] = array('default' => '');
    $options['effect'] = array('default' => 'default');
    $options['activate'] = array('default' => 'hover');
    $options['close'] = array('default' => '');
    $options['origin'] = array('default' => 'bottom-right');
    $options['expand'] = array('default' => 'bottom-right');
    $options['expand'] = array('default' => 'bottom-right');
    $options['width'] = array('default' => variable_get('popup-width', 150));
    $options['height'] = array('default' => '');
    $options['style'] = array('default' => variable_get('popup-style', 0));

    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
  
    $form['title'] = array(
      '#type' => 'textarea',
      '#title' => t('Link'),
      '#description' => t('Combine tokens from the "Replacement patterns" and html to create the trigger link.'),
      '#options' => $fields,
      '#default_value' => $this->options['title'],
    );
    
    $form['text'] = array(
      '#type' => 'textarea',
      '#title' => t('Text to display : combine tokens from the "Replacement patterns"'),
      '#default_value' => $this->options['text'],
    );
    
    
    module_load_include('inc', 'popup', 'includes/popup.util');
    $style_names = array_keys(_popup_styles());
    $style_options = array_combine(
      $style_names,
      $style_names
    );
    array_unshift($style_options, t('No style'));    
    
    $form['style'] = array(
      '#type' => 'select',
      '#title' => t('Add close button'),
      '#default_value' => $this->options['style'],
      '#options' => $style_options,
      '#description' => t('Preview may not take the defined style'),
    );      

    $form['activate'] = array(
      '#type' => 'select',
      '#title' => t('Activation mode'),
      '#default_value' => $this->options['activate'],
      '#options' => array('hover' => t('On hover'), 'click' => t('On click')),
    );  
    
    $form['close'] = array(
      '#type' => 'checkbox',
      '#title' => t('Add close button'),
      '#description' => t('Only work with "On click" activation mode'),
      '#default_value' => $this->options['close'],
    );    
    
    $form['effect'] = array(
      '#type' => 'select',
      '#title' => t('Effect'),
      '#options' => array(
        'default' => t('No effect'),
        'fade' => t('Fade'),
        'slide-down' => t('Slide down'),
        'slide-down-fade' => t('Slide down and fade')
       ),
      '#default_value' => $this->options['effect'],
    );

    $form['origin'] = array(
      '#type' => 'select',
      '#title' => t('Origin'),
      '#options' => array(
        'top-left' => t('Top left'),
        'top-right' => t('Top right'),
        'bottom-left' => t('Bottom left'),
        'bottom-right' => t('Bottom-right')
       ),
      '#default_value' => $this->options['origin'],
    );

    $form['expand'] = array(
      '#type' => 'select',
      '#title' => t('Position'),
      '#options' => array(
        'top-left' => t('Top left'),
        'top-right' => t('Top right'),
        'bottom-left' => t('Bottom left'),
        'bottom-right' => t('Bottom-right')
       ),
      '#default_value' => $this->options['expand'],
    );

    $form['width'] = array(
      '#type' => 'textfield',
      '#title' => t('Width'),
      '#default_value' => $this->options['width'],
    );    

    $form['height'] = array(
      '#type' => 'textfield',
      '#title' => t('Height'),
      '#default_value' => $this->options['height'],
    );

  }

  /**
   * Render the trigger field and its linked popup information.
   */
  function render($values) {
    // We need to have multiple unique IDs, one for each record.
    static $i = 0;
    static $link;
    if (!empty($this->options['title'])) {
    
      $tokens = $this->get_render_tokens($this->options['alter']);
      $attributes = $this->options;
      $attributes['title'] = filter_xss_admin($this->options['title']);
      $attributes['text'] = filter_xss_admin($this->options['text']);
      $attributes['height'] = filter_xss_admin($this->options['height']);
      $attributes['width'] = filter_xss_admin($this->options['width']);
      $attributes['link'] = strtr($attributes['link'], $tokens);
      
      // Filter links because it breaks the popup.
      $title = strtr($attributes['title'], $tokens);
      $attributes['title'] = preg_replace(array('/<[^>]+>/i', '</a>'), '', $title);
      $attributes['text'] = strtr($attributes['text'], $tokens);
      $attributes['height'] = strtr($attributes['height'], $tokens);
      $attributes['width'] = strtr($attributes['width'], $tokens);
      
      module_load_include('inc', 'popup', 'includes/popup.api');
      return popup($attributes);
    }
    else {
      return;
    }
  }
}
