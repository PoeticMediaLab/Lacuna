<?php
/**
 * @file
 * Administration pages for the 'jQuery UI filter accordion' module.
 */


/**
 * Form builder; Accordion settings page for the 'jQuery UI filter' module.
 *
 * http://www.phpeveryday.com/articles/jQuery-UI-Configuration-Accordion-Widget-P997.html
 * @ingroup forms
 */
function jquery_ui_filter_accordion_settings() {
  module_load_include('admin.inc', 'jquery_ui_filter');
  drupal_add_js(drupal_get_path('module', 'jquery_ui_filter') .'/jquery_ui_filter.admin.js');
  drupal_add_js(drupal_get_path('module', 'jquery_ui_filter_accordion') .'/jquery_ui_filter_accordion.admin.js');

  $accordion_options = jquery_ui_filter_accordion_get_options();

  // General
  $form['general'] = array(
    '#type' => 'fieldset',
    '#title' => 'Accordion settings',
  );
  $form['general']['jquery_ui_filter_accordion_header_tag'] = array(
    '#type' => 'select',
    '#title' => t('Header tag'),
    '#description' => t('The selected header tag is used to generate the jQuery UI Accordion when the jQuery UI filter is assigned to an input format.'),
    '#options' => array(
      'h1' => 'h1',
      'h2' => 'h2',
      'h3' => 'h3',
      'h4' => 'h4',
      'h5' => 'h5',
      'h6' => 'h6',
    ),
    '#required' => 1,
    '#default_value' => variable_get('jquery_ui_filter_accordion_header_tag', 'h3')
  );

  // Accordion
  $form['jquery_ui_filter_accordion_options'] = array(
    '#type' => 'fieldset',
    '#title' => 'Accordion options',
    '#description' => t('Learn more about <a href="@href">jQuery UI accordion options</a>.', array('@href' => 'http://jqueryui.com/demos/accordion/')),
    '#tree' => TRUE,
  );

  // Accordion: active
  $form['jquery_ui_filter_accordion_options']['active'] = array(
    '#title' => t('active'),
    '#type' => 'select',
    '#default_value' => $accordion_options['active'],
    '#options' => array('false' => 'none', 0 => 'first child'),
    '#description' => t('Selector for the active element. Needs collapsible: true..'),
  );

  // Accordion: animated
  $form['jquery_ui_filter_accordion_options']['animated'] = array(
    '#title' => t('animated'),
    '#type' => 'select',
    '#default_value' => $accordion_options['animated'],
    '#options' => array(
      0 => 'false',
      'slide' => 'slide',
      'bounceslide' => 'bounceslide',
    ),
    '#description' => t("Choose your favorite animation, or disable them (set to false)."),
  );

  // Accordion: auto Height
  $form['jquery_ui_filter_accordion_options']['autoHeight'] = array(
    '#title' => t('autoHeight'),
    '#type' => 'select',
    '#default_value' => $accordion_options['autoHeight'],
    '#options' => array('false' => 'false', 'true' => 'true'),
    '#description' => t('If set, the highest content part is used as height reference for all other parts. Provides more consistent animations.'),
  );

  // Accordion: clearStyle
  $form['jquery_ui_filter_accordion_options']['clearStyle'] = array(
    '#title' => t('clearStyle'),
    '#type' => 'select',
    '#default_value' => $accordion_options['clearStyle'],
    '#options' => array('false' => 'false', 'true' => 'true'),
    '#description' => t("If set, clears height and overflow styles after finishing animations. This enables accordions to work with dynamic content. Won't work together with autoHeight."),
  );

  // Accordion: collapsible
  $form['jquery_ui_filter_accordion_options']['collapsible'] = array(
    '#title' => t('collapsible'),
    '#type' => 'select',
    '#default_value' => $accordion_options['collapsible'],
    '#options' => array('false' => 'false', 'true' => 'true'),
    '#description' => t('Whether all the sections can be closed at once. Allows collapsing the active section by the triggering event (click is the default).'),
  );

  // Accordion: event
  $form['jquery_ui_filter_accordion_options']['event'] = array(
    '#title' => t('event'),
    '#type' => 'select',
    '#default_value' => $accordion_options['event'],
    '#options' => array('click' => 'click', 'mouseover' => 'mouseover'),
    '#description' => t('The event on which to trigger the accordion.'),
  );

  // Accordion: fillSpace [SKIPPED]
  // Since accordion is embedded inside content there is no way of knowing what
  // the container's height will be which makes this settings unpredicable.

  // Accordion: navigation [SKIPPED]
  // Deprecate navigation options - http://bugs.jqueryui.com/ticket/5869

  // Accordion: scrollTo
  $form['jquery_ui_filter_accordion_options']['scrollTo'] = array(
    '#title' => t('scrollTo'),
    '#type' => 'checkbox',
    '#default_value' => !empty($accordion_options['scrollTo']),
    '#description' => t("Scroll to active pane when page loads."),
  );
  $form['jquery_ui_filter_accordion_options']['scrollTo_options'] = array(
    '#title' => t('scrollTo options'),
    '#type' => 'fieldset',
    '#attributes' => array('id' => 'edit-jquery-ui-filter-accordion-options-scrollto-options'),
  );
  $form['jquery_ui_filter_accordion_options']['scrollTo_options']['duration'] = array(
    '#type' => 'select',
    '#title' => t('duration'),
    '#description' => t('A string determining how long the scroll to animation will run.'),
    '#options' => array(
      '' => 'none',
      'slow' => 'slow',
      'medium' => 'medium',
      'fast' => 'fast',
    ),
    '#default_value' => ($accordion_options['scrollTo']['duration']) ? $accordion_options['scrollTo']['duration'] : '',
  );

  // Accordion: history
  $form['jquery_ui_filter_accordion_options']['history'] = array(
    '#title' => t('history'),
    '#type' => 'select',
    '#default_value' => $accordion_options['history'],
    '#options' => array('false' => 'false', 'true' => 'true'),
    '#description' => t('Keep track of accordion state in browser history and allow users to bookmark active accordion element.'),
  );

  // Accordion: Global
  $form['jquery_ui_filter_accordion_options']['jquery_ui_filter_accordion_options_global'] = array(
    '#title' => t('Globally apply all the above accordion options to all instances of the jQuery UI accordion widget.'),
    '#type' => 'checkbox',
    '#default_value' => variable_get('jquery_ui_filter_accordion_options_global', FALSE),
    '#description' => t("By default the above options are only applied to accordion widgets generated by the jQuery UI filter. If checked, the selected options below will be applied as the defaults for all jQuery UI accordion widgets."),
    '#tree' => FALSE,
  );

  return _jquery_ui_filter_widget_settings_form($form, 'accordion');
}

/**
 * jQuery UI filter Accordion demo.
 */
function _jquery_ui_filter_accordion_demo(&$form_state) {
  if (isset($form_state['post']['accordion_source'])) {
    $accordion_source = $form_state['post']['accordion_source'];
  }
  else {
    $container_html = _jquery_ui_filter_demo_get_container_html();
    $accordion_header_tag = variable_get('jquery_ui_filter_accordion_header_tag', 'h3');
    $accordion_source = "<p>[accordion]</p>
<$accordion_header_tag id=\"accordion-section-i\">Section I</$accordion_header_tag>\n$container_html
<$accordion_header_tag id=\"accordion-section-ii\">Section II</$accordion_header_tag>\n$container_html
<$accordion_header_tag id=\"accordion-section-iii\">Section III</$accordion_header_tag>\n$container_html
<p>[/accordion]</p>\n";
    $accordion_source .= '<p>Open: <a href="#accordion-section-i">Section I</a>, <a href="#accordion-section-ii">Section II</a>, or <a href="#accordion-section-iii">Section III</a></p>';
  }

  $form = array();
  $form['accordion'] = array(
    '#type' => 'fieldset',
    '#title' => t('Accordion example'),
  );

  $form['accordion']['demo'] = array('#markup' => _jquery_ui_filter_demo_check_markup('accordion', $accordion_source));
  $form['accordion']['accordion_source'] = array(
    '#type' => 'textarea',
    '#title' => t('Accordion source'),
    '#description' => _jquery_ui_filter_accordion_tips_callback(),
    '#default_value' => $accordion_source,
    '#required' => TRUE,
  );
  return $form;
}
