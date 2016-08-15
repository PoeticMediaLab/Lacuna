<?php
/**
 * @file
 * Administration pages for the 'jQuery UI filter tabs' module.
 */


/**
 * Form builder; Tabs settings page for the 'jQuery UI filter' module.
 *
 * @ingroup forms
 */
function jquery_ui_filter_tabs_settings() {
  module_load_include('admin.inc', 'jquery_ui_filter');
  drupal_add_js(drupal_get_path('module', 'jquery_ui_filter') .'/jquery_ui_filter.admin.js');
  drupal_add_js(drupal_get_path('module', 'jquery_ui_filter_tabs') .'/jquery_ui_filter_tabs.admin.js');

  // General
  $form['general'] = array(
    '#type' => 'fieldset',
    '#title' => 'Tabs settings',
  );
  $form['general']['jquery_ui_filter_tabs_header_tag'] = array(
    '#type' => 'select',
    '#title' => t('Header tag'),
    '#description' => t('The selected header tag is used to generate the jQuery UI Tabs when the jQuery UI filter is assigned to an input format.'),
    '#options' => array(
      'h1' => 'h1',
      'h2' => 'h2',
      'h3' => 'h3',
      'h4' => 'h4',
      'h5' => 'h5',
      'h6' => 'h6',
    ),
    '#required' => 1,
    '#default_value' => variable_get('jquery_ui_filter_tabs_header_tag', 'h3')
  );

  $tabs_options = jquery_ui_filter_tabs_get_options();

  // Tabs
  $form['jquery_ui_filter_tabs_options'] = array(
    '#type' => 'fieldset',
    '#title' => 'Tabs options',
    '#description' => t('Learn more about <a href="@href">jQuery UI tabs options</a>.', array('@href' => 'http://jqueryui.com/demos/tabs/')),
    '#tree' => TRUE,
  );

  // Tabs: collapsible
  $form['jquery_ui_filter_tabs_options']['collapsible'] = array(
    '#title' => t('collapsible'),
    '#type' => 'select',
    '#default_value' => $tabs_options['collapsible'],
    '#options' => array('false' => 'false', 'true' => 'true'),
    '#description' => t("Set to 'true' to allow an already selected tab to become unselected again upon reselection."),
  );

  // Tabs: cookie (require jquery plugin)
  if (module_exists('jquery_plugin')) {
    $form['jquery_ui_filter_tabs_options']['cookie'] = array(
      '#title' => t('cookie'),
      '#type' => 'checkbox',
      '#default_value' => $tabs_options['cookie'],
      '#description' => t("Store the latest selected tab in a cookie. The cookie is then used to determine the initially selected tab if the selected option is not defined. (Requires cookie plugin)"),
    );
    $form['jquery_ui_filter_tabs_options']['cookie_options'] = array(
      '#type' => 'fieldset',
      '#title' => t('cookie options'),
      '#attributes' => array('id' => 'edit-jquery-ui-filter-tabs-options-cookie-options'),
    );
    $form['jquery_ui_filter_tabs_options']['cookie_options']['expires'] = array(
      '#title' => t('expires'),
      '#type' => 'textfield',
      '#field_suffix' => t('days'),
      '#default_value' => $tabs_options['cookie']['expires'],
      '#size' => 3,
      '#maxlength' => 3,
      '#description' => t('Cookie lifetime in days. If omitted, the cookie is a session cookie.'),
    );
    $form['jquery_ui_filter_tabs_options']['cookie_options']['secure'] = array(
      '#title' => t('secure'),
      '#type' => 'select',
      '#default_value' => $tabs_options['cookie']['secure'],
      '#options' => array('false' => 'false', 'true' => 'true'),
      '#description' => t('If true, the cookie transmission requires a secure protocol (https).'),
    );
  }

  // Tabs: event
  $form['jquery_ui_filter_tabs_options']['event'] = array(
    '#title' => t('event'),
    '#type' => 'select',
    '#default_value' => $tabs_options['event'],
    '#options' => array('click' => 'click', 'mouseover' => 'mouseover'),
    '#description' => t('The type of event to be used for selecting a tab.'),
  );

  // Tabs: fx
  $form['jquery_ui_filter_tabs_options']['fx'] = array(
    '#title' => t('fx'),
    '#type' => 'checkbox',
    '#default_value' => !empty($tabs_options['fx']),
    '#description' => t('Enable animations for hiding and showing tab panels.'),
  );
  $form['jquery_ui_filter_tabs_options']['fx_options'] = array(
    '#title' => t('fx options'),
    '#type' => 'fieldset',
    '#attributes' => array('id' => 'edit-jquery-ui-filter-tabs-options-fx-options'),
  );
  $form['jquery_ui_filter_tabs_options']['fx_options'][0] = array(
    '#type' => 'fieldset',
    '#title' => t('Hide'),
  ) + _jquery_ui_filter_admin_settings_fx_options($tabs_options['fx'][0]);
  $form['jquery_ui_filter_tabs_options']['fx_options'][1] = array(
    '#type' => 'fieldset',
    '#title' => t('Show'),
  ) + _jquery_ui_filter_admin_settings_fx_options($tabs_options['fx'][0]);

  // Tabs: paging
  $form['jquery_ui_filter_tabs_options']['paging'] = array(
    '#title' => t('paging'),
    '#type' => 'checkbox',
    '#default_value' => !empty($tabs_options['paging']),
    '#description' => t("Add 'back' and 'next' button to page through tabs."),
  );
  $form['jquery_ui_filter_tabs_options']['paging_options'] = array(
    '#title' => t('paging options'),
    '#type' => 'fieldset',
    '#attributes' => array('id' => 'edit-jquery-ui-filter-tabs-options-paging-options'),
  );
  $form['jquery_ui_filter_tabs_options']['paging_options']['back'] = array(
    '#title' => t('back label'),
    '#type' => 'textfield',
    '#default_value' => ($tabs_options['paging']['back']) ? $tabs_options['paging']['back'] : '&laquo; Previous',
  );
  $form['jquery_ui_filter_tabs_options']['paging_options']['next'] = array(
    '#title' => t('next label'),
    '#type' => 'textfield',
    '#default_value' => ($tabs_options['paging']['next']) ? $tabs_options['paging']['next'] : 'Next &raquo;',
  );

  // Tabs: selected
  $form['jquery_ui_filter_tabs_options']['selected'] = array(
    '#title' => t('selected'),
    '#type' => 'select',
    '#default_value' => $tabs_options['selected'],
    '#options' => array('' => '', '-1' => '-1'),
    '#description' => t("To set all tabs to unselected pass -1 as value."),
  );

  // Tabs: scrollTo
  $form['jquery_ui_filter_tabs_options']['scrollTo'] = array(
    '#title' => t('scrollTo'),
    '#type' => 'checkbox',
    '#default_value' => !empty($tabs_options['scrollTo']),
    '#description' => t("Scroll to selected tab widget when page loads."),
  );
  $form['jquery_ui_filter_tabs_options']['scrollTo_options'] = array(
    '#title' => t('scrollTo options'),
    '#type' => 'fieldset',
    '#attributes' => array('id' => 'edit-jquery-ui-filter-tabs-options-scrollTo-options'),
  );
  $form['jquery_ui_filter_tabs_options']['scrollTo_options']['duration'] = array(
    '#type' => 'select',
    '#title' => t('duration'),
    '#description' => t('A string determining how long the scroll to animation will run.'),
    '#options' => array(
      '' => 'none',
      'slow' => 'slow',
      'medium' => 'medium',
      'fast' => 'fast',
    ),
    '#default_value' => ($tabs_options['scrollTo']['duration']) ? $tabs_options['scrollTo']['duration'] : '',
  );

  // Tabs: history
  $form['jquery_ui_filter_tabs_options']['history'] = array(
    '#title' => t('history'),
    '#type' => 'select',
    '#default_value' => $tabs_options['history'],
    '#options' => array('false' => 'false', 'true' => 'true'),
    '#description' => t('Keep track of selected tab in browser history and allow users to bookmark selected tab.'),
  );

  // Tabs: Global
  $form['jquery_ui_filter_tabs_options']['jquery_ui_filter_tabs_options_global'] = array(
    '#title' => t('Globally apply all the above tabs options to all instances of the jQuery UI tabs widget.'),
    '#type' => 'checkbox',
    '#default_value' => variable_get('jquery_ui_filter_tabs_options_global', FALSE),
    '#description' => t("By default the above options are only applied to tabs widgets generated by the jQuery UI filter. If checked, the selected options below will be applied as the defaults for all jQuery UI tabs widgets."),
    '#tree' => FALSE,
  );

  return _jquery_ui_filter_widget_settings_form($form, 'tabs');
}

/**
 * jQuery UI filter Tabs demo.
 */
function _jquery_ui_filter_tabs_demo(&$form_state) {
  if (isset($form_state['post']['tabs_source'])) {
    $tabs_source = $form_state['post']['tabs_source'];
  }
  else {
    $container_html = _jquery_ui_filter_demo_get_container_html();
    $tabs_header_tag = variable_get('jquery_ui_filter_tabs_header_tag', 'h3');
    $tabs_source = "<p>[tabs]</p>
<$tabs_header_tag id=\"tabs-section-i\">Section I</$tabs_header_tag>\n$container_html
<$tabs_header_tag id=\"tabs-section-ii\">Section II</$tabs_header_tag>\n$container_html
<$tabs_header_tag id=\"tabs-section-iii\">Section III</$tabs_header_tag>\n$container_html
<p>[/tabs]</p>\n";
    $tabs_source .= '<p>Open: <a href="#tabs-section-i">Section I</a>, <a href="#tabs-section-ii">Section II</a>, or <a href="#tabs-section-iii">Section III</a></p>';
  }

  $form = array();
  $form['tabs'] = array(
    '#type' => 'fieldset',
    '#title' => t('Tabs example'),
  );
  $form['tabs']['demo'] = array('#markup' => _jquery_ui_filter_demo_check_markup('tabs', $tabs_source));
  $form['tabs']['tabs_source'] = array(
    '#type' => 'textarea',
    '#title' => t('Tabs source'),
    '#description' => _jquery_ui_filter_tabs_tips_callback(),
    '#default_value' => $tabs_source,
    '#required' => TRUE,
  );
  return $form;
}
