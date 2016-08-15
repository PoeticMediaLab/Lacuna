<?php
/**
 * @file
 * Administration pages for the 'jQuery UI filter dialog' module.
 */


/**
 * Form builder; Dialog settings page for the 'jQuery UI filter' module.
 *
 * @ingroup forms
 */
function jquery_ui_filter_dialog_settings() {
  module_load_include('admin.inc', 'jquery_ui_filter');

  // General
  $form['general'] = array(
    '#type' => 'fieldset',
    '#title' => 'Dialog settings',
  );
  $form['general']['jquery_ui_filter_dialog_whitelist'] = array(
    '#type' => 'textarea',
    '#title' => t('Domain names or IPs that can be opened in a dialog (aka whitelist)'),
    '#description' => t('Enter one domain name or IP per line. The current domain %domain is automatically included in the whitelist.', array('%domain' => $_SERVER['SERVER_NAME'])),
    '#default_value' => variable_get('jquery_ui_filter_dialog_whitelist', ''),
  );

  $dialog_options = jquery_ui_filter_dialog_get_options();

  // Dialog options
  $form['jquery_ui_filter_dialog_options'] = array(
    '#type' => 'fieldset',
    '#title' => 'Dialog options',
    '#description' => t('Learn more about <a href="@href">jQuery UI dialog options</a>.', array('@href' => 'http://jqueryui.com/demos/dialog/')),
    '#tree' => TRUE,
  );

  // Dialog options: closeOnEscape
  $form['jquery_ui_filter_dialog_options']['closeOnEscape'] = array(
    '#title' => t('closeOnEscape'),
    '#type' => 'select',
    '#default_value' => $dialog_options['closeOnEscape'],
    '#options' => array('false' => 'false', 'true' => 'true'),
    '#description' => t('Specifies whether the dialog should close when it has focus and the user presses the esacpe (ESC) key.'),
  );

  // Dialog options: closeText
  $form['jquery_ui_filter_dialog_options']['closeText'] = array(
    '#title' => t('closeText'),
    '#type' => 'textfield',
    '#default_value' => $dialog_options['closeText'],
    '#description' => t('Specifies the text for the close button. Note that the close text is visibly hidden when using a standard theme.'),
  );

  // Dialog options: closeButton
  $form['jquery_ui_filter_dialog_options']['closeButton'] = array(
    '#title' => t('closeButton'),
    '#type' => 'select',
    '#default_value' => $dialog_options['closeButton'],
    '#options' => array('false' => 'false', 'true' => 'true'),
    '#description' => t('Specifies whether the dialog should display a close button.'),
  );

  // Dialog options: dialogClass
  $form['jquery_ui_filter_dialog_options']['dialogClass'] = array(
    '#title' => t('dialogClass'),
    '#type' => 'textfield',
    '#default_value' => $dialog_options['dialogClass'],
    '#description' => t('The specified class name(s) will be added to the dialog, for additional theming.'),
  );

  // Dialog options: draggable
  $form['jquery_ui_filter_dialog_options']['draggable'] = array(
    '#title' => t('draggable'),
    '#type' => 'select',
    '#default_value' => $dialog_options['draggable'],
    '#options' => array('false' => 'false', 'true' => 'true'),
    '#description' => t('If set to true, the dialog will be draggable will be draggable by the titlebar.'),
  );

  // Dialog options: height
  $form['jquery_ui_filter_dialog_options']['height'] = array(
    '#title' => t('height'),
    '#type' => 'textfield',
    '#field_suffix' => t('pixels'),
    '#default_value' => $dialog_options['height'],
    '#size' => 3,
    '#maxlength' => 5,
    '#description' => t("The height of the dialog, in pixels. Specifying 'auto' is also supported to make the dialog adjust based on its content."),
  );

  // Dialog options: width
  $form['jquery_ui_filter_dialog_options']['width'] = array(
    '#title' => t('width'),
    '#type' => 'textfield',
    '#field_suffix' => t('pixels'),
    '#default_value' => $dialog_options['width'],
    '#size' => 3,
    '#maxlength' => 5,
    '#description' => t("The width of the dialog, in pixels. Specifying 'auto' is also supported to make the dialog adjust based on its content."),
  );

  /*
  // TODO: Add support for jQueryUI hide/show effects.
  // Dialog options: hide
  $form['jquery_ui_filter_dialog_options']['hide'] = array(
    '#title' => t('hide'),
    '#type' => 'select',
    '#default_value' => $dialog_options['hide'],
    '#options' => array(
      '' => '',
      'slide' => 'slide',
      'fadeOut' => 'fade'
    ),
    '#description' => t('The effect to be used when the dialog is closed.'),
  );

  // Dialog options: show
  $form['jquery_ui_filter_dialog_options']['show'] = array(
    '#title' => t('show'),
    '#type' => 'select',
    '#default_value' => $dialog_options['show'],
    '#options' => array(
      '' => '',
      'slide' => 'slide',
      'fadeIn' => 'fade'
    ),
    '#description' => t('The effect to be used when the dialog is opened.'),
  );
  */

  // Dialog options: maxHeight
  $form['jquery_ui_filter_dialog_options']['maxHeight'] = array(
    '#title' => t('maxHeight'),
    '#type' => 'textfield',
    '#field_suffix' => t('pixels'),
    '#default_value' => $dialog_options['maxHeight'],
    '#size' => 3,
    '#maxlength' => 5,
    '#description' => t('The maximum height to which the dialog can be resized, in pixels.'),
  );

  // Dialog options: maxWidth
  $form['jquery_ui_filter_dialog_options']['maxWidth'] = array(
    '#title' => t('maxWidth'),
    '#type' => 'textfield',
    '#field_suffix' => t('pixels'),
    '#default_value' => $dialog_options['maxWidth'],
    '#size' => 3,
    '#maxlength' => 5,
    '#description' => t('The maximum width to which the dialog can be resized, in pixels.'),
  );

  // Dialog options: minHeight
  $form['jquery_ui_filter_dialog_options']['minHeight'] = array(
    '#title' => t('minHeight'),
    '#type' => 'textfield',
    '#field_suffix' => t('pixels'),
    '#default_value' => $dialog_options['minHeight'],
    '#size' => 3,
    '#maxlength' => 5,
    '#description' => t('The minimum height to which the dialog can be resized, in pixels.'),
  );

  // Dialog options: minWidth
  $form['jquery_ui_filter_dialog_options']['minWidth'] = array(
    '#title' => t('minWidth'),
    '#type' => 'textfield',
    '#field_suffix' => t('pixels'),
    '#default_value' => $dialog_options['minWidth'],
    '#size' => 3,
    '#maxlength' => 5,
    '#description' => t('The minimum width to which the dialog can be resized, in pixels.'),
  );

  // Dialog options: modal
  $form['jquery_ui_filter_dialog_options']['modal'] = array(
    '#title' => t('modal'),
    '#type' => 'select',
    '#default_value' => $dialog_options['modal'],
    '#options' => array('false' => 'false', 'true' => 'true'),
    '#description' => t('Specifies whether the dialog will stack on top of other dialogs. This will cause the dialog to move to the front of other dialogs when it gains focus.'),
  );

  // Dialog options: position
  $form['jquery_ui_filter_dialog_options']['position'] = array(
    '#title' => t('position'),
    '#type' => 'textfield',
    '#default_value' => $dialog_options['position'],
    '#description' => t('Specifies where the dialog should be displayed. Possible values:') .
      '<ol>'.
        '<li>' . t("a single string representing position within viewport: 'center', 'left', 'right', 'top', 'bottom'") . '</li>'.
        '<li>' . t("comma separated x,y coordinate pair in pixel offset from left, top corner of viewport (e.g. [350,100])") . '</li>'.
        '<li>' . t("comma separated x,y position string values (e.g. ['right','top'] for top right corner).'),") . '</li>'.
      '</ol>',
  );

  // Dialog options: resizable
  $form['jquery_ui_filter_dialog_options']['resizable'] = array(
    '#title' => t('resizable'),
    '#type' => 'select',
    '#default_value' => $dialog_options['resizable'],
    '#options' => array('false' => 'false', 'true' => 'true'),
    '#description' => t('If set to true, the dialog will be resizable.'),
  );

  // Dialog options: stack
  $form['jquery_ui_filter_dialog_options']['stack'] = array(
    '#title' => t('stack'),
    '#type' => 'select',
    '#default_value' => $dialog_options['stack'],
    '#options' => array('false' => 'false', 'true' => 'true'),
    '#description' => t('Specifies whether the dialog will stack on top of other dialogs. This will cause the dialog to move to the front of other dialogs when it gains focus.'),
  );

  // Dialog options: title
  $form['jquery_ui_filter_dialog_options']['title'] = array(
    '#title' => t('title'),
    '#type' => 'textfield',
    '#default_value' => $dialog_options['title'],
    '#description' => t('Specifies the title of the dialog. Any valid HTML may be set as the title. The title can also be specified by the title attribute on the dialog source link.'),
  );

  // Dialog options: dialogFeatures
  $form['jquery_ui_filter_dialog_options']['dialogFeatures'] = array(
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#title' => t('dialogFeatures'),
  );
  $default_features = jquery_ui_filter_dialog_get_default_features();
  foreach ($default_features as $key => $value) {
    $form['jquery_ui_filter_dialog_options']['dialogFeatures'][$key] = array(
      '#title' => $key,
      '#type' => 'checkbox',
      '#default_value' => $dialog_options['dialogFeatures'][$key],
    );
  }

  // Dialog options: Global
  $form['jquery_ui_filter_dialog_options']['jquery_ui_filter_dialog_options_global'] = array(
    '#title' => t('Globally apply all the above dialog options to all instances of the jQuery UI dialogs.'),
    '#type' => 'checkbox',
    '#default_value' => variable_get('jquery_ui_filter_dialog_options_global', FALSE),
    '#description' => t("By default the above options are only applied to dialogs generated by the jQuery UI filter. If checked, the selected options below will be applied as the defaults for all jQuery UI dialogs."),
    '#tree' => FALSE,
  );

  return _jquery_ui_filter_widget_settings_form($form, 'dialog');
}

/**
 * jQuery UI filter Dialog demo.
 */
function _jquery_ui_filter_dialog_demo(&$form_state) {
  if (isset($form_state['post']['dialog_source'])) {
    $dialog_source = $form_state['post']['dialog_source'];
  }
  else {
    global $user;
    $dialog_links = array(
      array(
        'title' => t('Edit Your User Account (with Tabs)'),
        'href' => 'user/' . $user->uid . '/edit',
        'attributes' => array(
          'title' => t('Your Account'),
          'target' => '[dialog]',
          'rel' => "{'dialogFeatures':'page-tabs=0'}",
        )
      ),
      array(
        'title' => t('Edit Your User Account (without Tabs)'),
        'href' => 'user/' . $user->uid . '/edit',
        'attributes' => array(
          'title' => t('Your Account'),
          'target' => '[dialog]',
          'rel' => "{'dialogFeatures':'page-tabs=1'}",
        )
      ),
      array(
        'title' => t('Help (Full Screen)'),
        'href' => 'admin/help',
        'attributes' => array(
          'title' => t('Help'),
          'target' => '[dialog]',
          'rel' => "{'height':'auto', 'width':'auto'}",
        )
      ),
      array(
        'title' => t('Help (Over-sized)'),
        'href' => 'admin/help',
        'attributes' => array(
          'title' => t('Help'),
          'target' => '[dialog]',
          'rel' => "{'height':4000, 'width':800}",
        )
      ),
      array(
        'title' => t('Drupal.org (Example of external URL the must be whitelisted)'),
        'href' => 'http://drupal.org',
        'attributes' => array(
          'title' => t('Drupal.org'),
          'target' => '[dialog]',
        )
      ),
    );
    if (module_exists('contact')) {
      $dialog_links[] = array(
        'title' => t('Contact'),
        'href' => 'contact',
        'attributes' => array(
          'title' => t('Contact (600x600 modal)'),
          'target' => '[dialog]',
          'rel' => "{'modal': true, 'height': 600, 'width': 600}",
        )
      );
    }
    $dialog_source = preg_replace('/ class="[^"]+"/', '', theme('links', array('links' => $dialog_links, 'attributes' => array())));
  }

  $form = array();
  $form['dialog'] = array(
    '#type' => 'fieldset',
    '#title' => t('Dialog examples'),
  );
  $form['dialog']['demo'] = array('#markup' => _jquery_ui_filter_demo_check_markup('dialog', $dialog_source));
  $form['dialog']['dialog_source'] = array(
    '#type' => 'textarea',
    '#title' => t('Dialog source'),
    '#description' => _jquery_ui_filter_dialog_tips_callback(),
    '#default_value' => $dialog_source,
    '#required' => TRUE,
  );
  return $form;
}
