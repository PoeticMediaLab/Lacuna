<?php

/**
 * @file
 * global_filter.admin.inc
 */

/**
 * Menu callback for admin settings.
 */
function global_filter_admin_config() {
  $form['global_filter_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Global Filter module-wide configuration'),
    '#description' => '',
  );
  $form['global_filter_settings']['global_filter_num_filters'] = array(
    '#type' => 'textfield',
    '#size' => 2,
    '#title' => t('Maximum number of global filter blocks you may need'),
    '#default_value' => global_filter_get_module_parameter('num_filters', GLOBAL_FILTER_DEF_NUM_FILTERS),
    '#description' => t('Determines how many global filter blocks will be available for you to use at <a href="@url">Structure >> Blocks</a>.<br/>You may increase or decrease this number at any time.', array(
      '@url' => url('admin/structure/block'))),
  );
  $form['global_filter_settings']['global_filter_links_widget_via_post'] = array(
    '#type' => 'checkbox',
    '#title' => t('Suppress URL parameters in the links of the links widget'),
    '#default_value' => global_filter_get_module_parameter('links_widget_via_post', TRUE),
    '#description' => t('When ticked global filter values are transmitted via HTTP POST rather than HTTP GET.'),
  );
  $form['global_filter_settings']['global_filter_set_from_profile_on_login'] = array(
    '#type' => 'checkbox',
    '#title' => t('Set global filters according to the user profile upon <strong>login</strong>'),
    '#default_value' => global_filter_get_module_parameter('set_from_profile_on_login', TRUE),
    '#description' => t('Applies to core and Profile2 user profiles.'),
  );
  $form['global_filter_settings']['global_filter_set_from_profile_on_submit'] = array(
    '#type' => 'checkbox',
    '#title' => t('Set global filters according to the user profile when <strong>saved</strong>'),
    '#default_value' => global_filter_get_module_parameter('set_from_profile_on_submit', FALSE),
    '#description' => t('With this box ticked you can optionally put all your global filter blocks in the <em>&ltnone&gt;</em> region, making them invisible. Users then change their global filters through their profile preferences. Applies to core and Profile2 user profiles.'),
  );

  $form['global_filter_settings_advanced'] = array(
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#title' => t('Global Filter advanced configuration'),
    '#description' => '',
  );

  $form['global_filter_settings_advanced']['global_filter_mutex_mode'] = array(
    '#type' => 'checkbox',
    '#title' => t('Make global filters mutually exclusive'),
    '#default_value' => global_filter_get_module_parameter('mutex_mode', FALSE),
    '#description' => t('When the user sets one global filter, all other global filters are reset to their global defaults or to "all", where no defaults are set.'),
  );
  $form['global_filter_settings_advanced']['global_filter_visible_filters_only'] = array(
    '#type' => 'checkbox',
    '#title' => t('Optimise'),
    '#default_value' => global_filter_get_module_parameter('visible_filters_only', FALSE),
    '#description' => t('When ticked the system will only evaluate global filter blocks that are visibile on the current page. Depending on your page layout this method can be a little unreliable, so if after ticking this box you find that you have to refresh pages in order to have global filter selections effectuated, then untick this box.'),
  );
  $form['global_filter_settings_advanced']['global_filter_show_debug_messages'] = array(
    '#type' => 'textfield',
    '#title' => t('Show Global Filter informational messages during execution'),
    '#default_value' => global_filter_get_module_parameter('show_debug_messages', FALSE),
    '#description' => t('Enter a comma-separated list of names of users that should see info messages coming from this module, e.g., for debugging purposes. Use <strong>anon</strong> for the anonymous user.'),
  );

  $form['global_filter_settings_advanced']['global_filter_autocycle'] = array(
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#title' => t('Global Filter auto-cycle configuration'),
    '#description' => '',
  );
  $form['global_filter_settings_advanced']['global_filter_autocycle']['global_filter_view_autocycle'] = array(
    '#type' => 'select',
    '#title' => t('Auto-cycle filter: select a view for supplying a next global filter value each time the filter is required.'),
    '#default_value' => global_filter_get_module_parameter('view_autocycle'),
    '#options' => array_merge(
      array('' => t('None')),
      global_filter_get_view_names()
    ),
    '#description' => t('This global filter does not have any UI associated with it, as it does not need a user to select a value.'),
  );
  $form['global_filter_settings_advanced']['global_filter_autocycle']['global_filter_view_autocycle_every_click'] = array(
    '#type' => 'radios',
    '#title' => t('The auto-cycle filter selected above is to supply its next value:'),
    '#options' => array(
      FALSE => t('only when the Global Filter API is called explicitly'),
      TRUE  => t('on every page load'),
    ),
    '#default_value' => global_filter_get_module_parameter('view_autocycle_every_click', FALSE),
  );
  return system_settings_form($form);
}
