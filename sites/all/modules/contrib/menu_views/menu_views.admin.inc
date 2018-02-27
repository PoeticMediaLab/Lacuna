<?php

/**
 * @file
 * Form hooks for the menu_views module.
 */

/**
 * Implements hook_form_FORM_ID_alter().
 *
 * Appends the attached view to the title of the menu item.
 */
function menu_views_form_menu_overview_form_alter(&$form, &$form_state) {
  $attached = FALSE;
  $elements = element_children($form);
  foreach ($elements as $mlid) {
    $element = &$form[$mlid];
    // Only process menu items
    if (isset($element['#item'])) {
      $menu_item = &$element['#item'];
      // Only change the title for attached views
      $item = _menu_views_get_item($menu_item);
      _menu_views_tokenize($item, TRUE);
      
      if ($item['type'] == 'view' && $item['view']['name'] && $item['view']['display']) {
        if (!$attached) {
          $form['#attached']['css'][] = drupal_get_path('module', 'menu_views') . '/menu_views.admin.css';
          $attached = TRUE;
        }
        $title = '';
        if ($view = views_get_view($item['view']['name'])) {
          if ($view->access($item['view']['display']) && $view->set_display($item['view']['display'])) {
            $view->set_arguments(explode('/', $item['view']['arguments']));
            // Provide title options for the view.
            $title = filter_xss_admin($item['view']['settings']['title_override']);
            if (empty($title)) {
              $title = filter_xss_admin($view->get_title());
            }
          }
          $view->destroy();
        }
        if (empty($title)) {
          $title = t($item['view']['name']) . '-' . t($item['view']['display']);
        }
        $element['title'] = array(
          '#prefix' => '<div class="view" title="View: ' . $item['view']['name'] . '-' . $item['view']['display'] . '">',
          '#suffix' => '</div>',
          '#markup' => '<strong>View:</strong> ' . $title . ($menu_item['hidden'] ? ' (' . t('disabled') . ')' : ''),
        );
      }
    }
  }
}

/**
 * Implements hook_form_FORM_ID_alter().
 *
 * Adds menu views options to the menu edit item form.
 *
 * @see _menu_views_form_alter()
 */
function menu_views_form_menu_edit_item_alter(&$form, &$form_state) {
  drupal_set_title(t('Edit menu item'));
  _menu_views_form_alter($form, $form, $form_state);
}

/**
 * Implements hook_form_FORM_ID_alter().
 *
 * Adds menu views options to the node's edit menu item form.
 *
 * @see _menu_views_form_alter()
 */
function menu_views_form_node_form_alter(&$form, &$form_state) {
  if (isset($form['menu']['link'])) {
    _menu_views_form_alter($form['menu']['link'], $form, $form_state);
  }
}

/**
 * Helper function to determine where form values for menu views are located.
 *
 * @return
 *  Array of parents to the menu views form elements.
 */
function _menu_views_form_parents($form) {
  $parents = array();
  if (isset($form['#node'])) {
    $parents[] = 'menu';
    $parents[] = 'options';
  }
  elseif (_menu_views_options_tree($form)) {
    $parents[] = 'options';
  }
  $parents[] = 'menu_views';
  $parents[] = 'view';
  return $parents;
}

/**
 * Helper function that inserts a fieldset containing available replacement tokens.
 *
 * @see _menu_views_form()
 */
function _menu_views_form_tokens_ui(array &$element) {
  static $enabled;
  if (!isset($enabled)) {
    $enabled = module_exists('token'); 
  }
  if ($enabled) {
    $i = 0;
    while (isset($element['tokens_' . $i])) {
      $i++;
    }
    $element['tokens_' . $i] = array(
      '#type' => 'container',
    );
    $element['tokens_' . $i]['tokens'] = array(
      '#theme' => 'token_tree',
      '#token_types' => array('menu-link'),
      '#dialog' => TRUE,
    );
  }
}

/**
 * Alters existing forms in preparation for adding Menu Views to it.
 *
 * @param $element
 *   The top level menu item edit form element passed by reference.
 * @param $form
 *   The complete form array passed by reference.
 * @param $form_state
 *   The complete form state array passed by reference.
 */
function _menu_views_form_alter(array &$element, array &$form, array &$form_state) {
  // Still need to render the form, just hide it for those who don't have access.
  $access = user_access('administer menu views');
  // Only need to attach or alter form if user has access.
  if ($access) {
    // Unset the previous values so that the new values can get saved.
    if (isset($element['options']['#value']['menu_views'])) {
      unset($element['options']['#value']['menu_views']);
    }
    $module_path = drupal_get_path('module', 'menu_views');
    // Attach CSS.
    $element['#attached']['css'][] = array(
      'data' => $module_path . '/menu_views.admin.css',
      'type' => 'file',
      'group' => CSS_THEME,
      'weight' => 100
    );
    // Attach JavaScript.
    $element['#attached']['js'][] = array(
      'data' => array('menu_views' => array(
        'admin_theme' => variable_get('admin_theme', 'bartik'),
        'node_form' => isset($form['#node']),
      )),
      'type' => 'setting',
    );
    $element['#attached']['js'][] = array(
      'data' => $module_path . '/menu_views.admin.js',
      'type' => 'file',
      'group' => JS_THEME,
      'weight' => 100,
    );
    // Create AJAX wrapper around the menu edit form element.
    $element['#prefix'] = '<div id="menu-edit-item-wrapper">';
    $element['#suffix'] = '</div>';
  }
    
  // Get values for the new menu views item, existing menu views item or submitted form values.
  $item = _menu_views_get_item($form, $form_state);
  // Use the loaded node if it exists.
  $node = isset($form['#node']) ? $form['#node'] : FALSE;
  
  // Get the original menu link, if it exists.
  $menu_link = array();
  if (isset($form['original_item']['#value'])) {
    $menu_link = $form['original_item']['#value'];
  }
  elseif ($node && isset($node->menu)) {
    $menu_link = $node->menu;
  }
  
  // Determine which menu item type is visible.
  $visible = !('view' === $item['type']);
  
  // Determine the correct link path to show or set values for.
  if (isset($element['link_path'])) {
    if ('link' === $item['type'] && !empty($element['link_path']['#default_value']) && '<view>' === $element['link_path']['#default_value']) {
      $element['link_path']['#default_value'] = $item['original_path'];
    }
    elseif ('view' === $item['type']) {
      if (!empty($element['link_path']['#default_value']) && '<view>' !== $element['link_path']['#default_value']) {
        $item['original_path'] = $element['link_path']['#default_value'];
      }
      $element['link_path']['#default_value'] = '<view>';
    }
  }
  elseif ($node) {
    if ('view' === $item['type']) {
      $element['link_path'] = array(
        '#type' => 'value',
        '#value' => '<view>',
      );
    }
    else {
      $element['link_path'] = array(
        '#type' => 'value',
        '#value' => $node && isset($node->nid) ? 'node/' . $node->nid : '',
      );
    }
  }
  
  // If the original path is empty and this is a node, use the node path.
  if (empty($item['original_path']) && $node && isset($node->nid) && $node->nid) {
    $item['original_path'] = 'node/' . $node->nid;
  }
  
  // If this menu item is a view and user does not have permissions to administer menu views, restrict access to the form.
  // Cannot use drupal_access_denied() because this form can also be inside a node edit form.
  if ($item['type'] == 'view' && !$access) {
    $element['disabled'] = array(
      '#prefix' => '<div class="messages error">',
      '#suffix' => '</div>',
      '#markup' => t('You do not have access to edit this type of menu item.'),
      '#weight' => -9999,
    );
    $visible = FALSE;
    // Hide the action buttons on menu item edit forms.
    if (isset($element['actions'])) {
      $element['actions']['#access'] = $access;
    }
    // Hide the checkbox toggle on node edit forms.
    if (isset($form['menu']['enabled'])) {
      $form['menu']['enabled']['#access'] = $access;
    }
  }
  
  // Replace Parent Menu Options
  $options = _menu_views_parent_options(menu_get_menus(), $menu_link);
  if ($node && isset($node->type)) {
    $options = _menu_views_parent_options(menu_get_menus(), $menu_link['mlid'] ? $menu_link : $node->type, $node->type);
  }
  $element['parent']['#title'] = t('Parent Item');
  $element['parent']['#options'] = $options;

  // Move general menu item settings into a container.
  if ($access) {
    $element['menu_item_settings'] = array(
      '#access' => $access,
      '#type' => 'fieldset',
      '#title' => t('Menu item settings'),
      '#parents' => isset($form['#node']) ? array('menu') : array(),
      '#weight' => $item['type'] == 'view' ? 50 : 1,
      '#attributes' => array('id' => 'menu_item_settings', 'class' => array('menu-item-settings')),
    );
    if (isset($element['enabled'])) {
      $element['menu_item_settings']['enabled'] = $element['enabled'];
      unset($element['enabled']);
    }
    $element['menu_item_settings']['expanded'] = $element['expanded'];
    unset($element['expanded']);
    $element['menu_item_settings']['parent'] = $element['parent'];
    unset($element['parent']);
    $element['menu_item_settings']['weight'] = $element['weight'];
    unset($element['weight']);
  }

  // Add support for the xmlsitemap_menu module.
  if (module_exists('xmlsitemap_menu')) {
    $element['xmlsitemap']['#weight'] = $item['type'] === 'view' ? 51 : 30;
  }

  // Create a radio toggle for menu item types: link or view.
  $element['menu_item_type'] = array(
    '#access' => $access,
    '#type' => 'radios',
    '#title' => t('Menu item type'),
    '#options' => array('link' => t('Link'), 'view' => t('View')),
    '#default_value' => $item['type'],
    // Add container-inline style for admin themes like Rubik.
    '#prefix' => '<div id="menu-item-type" class="form-item container-inline">',
    '#suffix' => '</div>',
    '#ajax' => array(
      'callback' => '_menu_views_form_ajax',
      'wrapper' => 'menu-edit-item-wrapper',
    ),
    // Ensure this is rendered at the top of the form.
    '#weight' => -1000,
  );
  
  // Determine if menu_attributes is enabled.
  $menu_attributes = module_exists('menu_attributes');

  // Show/Hide the core link form elements based on menu item type of: link or view.
  foreach (element_children($element) as $child) {
    // Skip options (handled below) and actions.
    $type = isset($element[$child]['#type']) ? $element[$child]['#type'] : '';

    // Ensure necessary children are always present (regardless of their type).
    $ignore_children = array(
      'menu_item_type', 'disabled', 'menu_item_settings',
      'form_build_id', 'form_token', 'form_id',
      'xmlsitemap',
    );

    // Allow the menu_attributes module to control the description field.
    if ($menu_attributes) {
      $ignore_children[] = 'description';
    }

    $ignore_types = array('actions', 'hidden', 'value', 'token');
    if (in_array($child, $ignore_children) || !$type || in_array($type, $ignore_types)) {
      continue;
    }
    $element[$child]['#access'] = $visible;
  }
  // Show/Hide the link options form elements based on menu item type of: link or view.
  foreach (element_children($element['options']) as $child) {
    // Skip menu_view options.
    $type = isset($element['options'][$child]['#type']) ? $element['options'][$child]['#type'] : '';
    // Ensure necessary children are always present (regardless of their type).
    $ignore_children = array('menu_views');
    $ignore_types = array('hidden', 'value', 'token');
    if (in_array($child, $ignore_children) || !$type || in_array($type, $ignore_types)) {
      continue;
    }
    $element['options'][$child]['#access'] = $visible;
  }
  
  // Place menu views in the options array.
  $element['options']['menu_views'] = array(
    '#type' => 'container',
    '#tree' => TRUE,
    '#weight' => 10,
    '#access' => $access,
  );
  
  // Create the actual Menu Views form.
  _menu_views_form($item, $element['options']['menu_views'], $form, $form_state);
  
  // Add menu views form handlers.
  array_unshift($form['#validate'], '_menu_views_form_validate');
  array_unshift($form['#submit'], '_menu_views_form_submit');
}

/**
 * Adds Menu Views settings to an existing form.
 *
 * @param $item
 *   The menu views item array passed by reference.
 *   @see _menu_views_get_item()
 * @param $element
 *   The top level menu item edit form element passed by reference.
 * @param $form
 *   The complete form array passed by reference.
 * @param $form_state
 *   The complete form state array passed by reference.
 */
function _menu_views_form(&$item, &$element, &$form, &$form_state) {
  $element['mlid'] = array(
    '#type' => 'value',
    '#value' => $item['mlid'],
  );
  $element['type'] = array(
    '#type' => 'value',
    '#value' => $item['type'],
  );
  $element['original_path'] = array(
    '#type' => 'value',
    '#value' => $item['original_path'],
  );
  
  // Container for the actual view settings.
  $element['view'] = array(
    '#type' => 'container',
    '#access' => $item['type'] == 'view' ? TRUE : FALSE,
  );

  $view_options = array();
  $display_options = array();
  foreach (views_get_enabled_views() as $view_name => $view) {
    $view_options[$view_name] = $view->human_name . ' (' . $view_name . ')';
    foreach ($view->display as $display_name => $display) {
      if ('default' !== $display_name && 'page' !== $display_name && 'rss' !== $display_name) {
        $display_options[$view_name][$display_name] = $display->display_title . ' (' . $display_name . ')';
      }
    }
    // If view has no compatiable displays, remove the view as an option.
    if (empty($display_options[$view_name])) {
      unset($view_options[$view_name]);
    }
    else {
      // Sort the displays for the view.
      ksort($display_options[$view_name]);
    }
  }
  ksort($view_options);
  $element['view']['container'] = array(
    '#type' => 'fieldset',
    '#title' => t('View'),
    '#parents' => _menu_views_form_parents($form),
  );
  $element['view']['container']['name'] = array(
    '#type' => 'select',
    '#title' => t('Name'),
    '#empty_option' => t('- Select View -'),
    '#description' => t('Select the name of a view to use. The following view displays cannot be used: Master (default), Page and RSS. If the view or display you are looking for does not exist, create a block display in that view.'),
    '#required' => TRUE,
    '#default_value' => $item['view']['name'],
    '#options' => $view_options,
    '#ajax' => array(
      'callback' => '_menu_views_form_ajax',
      'wrapper' => 'menu-edit-item-wrapper',
    ),
  );
  if ($item['view']['name'] && !empty($display_options[$item['view']['name']])) {
    $element['view']['container']['display'] = array(
      '#type' => 'select',
      '#title' => t('Display'),
      '#description' => t('Select the name of a view display to use. The following view displays cannot be used: Master (default), Page and RSS. If the view or display you are looking for does not exist, create a block display in that view.'),
      '#required' => TRUE,
      '#empty_option' => t('- Select Display -'),
      '#default_value' => $item['view']['display'],
      '#options' => $display_options[$item['view']['name']],
      '#ajax' => array(
        'callback' => '_menu_views_form_ajax',
        'wrapper' => 'menu-edit-item-wrapper',
      ),
    );
    if ($item['view']['display']) {
      $element['view']['container']['arguments'] = array(
        '#type' => 'textfield',
        '#title' => t('Arguments'),
        '#description' => t('You can reference the node associated with this menu link by using <code>[menu-link:node:nid]</code>.<br />You can reference the node associated with the parent of this menu link by using <code>[menu-link:parent:node:nid]</code>.'),
        '#default_value' => $item['view']['arguments'],
      );
      _menu_views_form_tokens_ui($element['view']['container']);
      
      // Advanced Settings.
      $element['view']['settings'] = array(
        '#type' => 'container',
      );
      $parents = _menu_views_form_parents($form);
      $parents[] = 'settings';
      
      $parents_name = $parents;
      $parents_name_first = array_shift($parents_name);
      $parents_name = $parents_name_first . '[' . implode('][', $parents_name);
      
      $settings = &$element['view']['settings'];

      // Wrapper Class
      $settings['wrapper_classes'] = array(
        '#type' => 'fieldset',
        '#title' => t('Wrapper Classes'),
        '#collapsible' => TRUE,
        '#collapsed' => TRUE,
        '#parents' => $parents,
      );
      $settings['wrapper_classes']['wrapper_classes'] = array(
        '#type' => 'textfield',
        '#description' => t('Provide any additional classes, separated by spaces.'),
        '#default_value' => $item['view']['settings']['wrapper_classes'],
      );

      // View Title
      $settings['title'] = array(
        '#type' => 'fieldset',
        '#title' => t('View Title'),
        '#collapsible' => TRUE,
        '#collapsed' => TRUE,
        '#parents' => $parents,
      );
      $settings['title']['title'] = array(
        '#type' => 'checkbox',
        '#title' => t('Show view title'),
        '#default_value' => $item['view']['settings']['title'],
      );
      $settings['title']['title_settings'] = array(
        '#type' => 'container',
        '#parents' => $parents,
        '#states' => array(
          'visible' => array(
           ':input[name="' . $parents_name . '][title]"]' => array('checked' => TRUE),
          ),
        ),
      );
      $title = &$settings['title']['title_settings'];
      $title['title_wrapper'] = array(
        '#type' => 'select',
        '#title' => t('Element Wrapper'),
        '#description' => t('Choose which element wrapper to use around the title of the view. Default: H3'),
        '#default_value' => $item['view']['settings']['title_wrapper'],
        '#options' => variable_get('views_field_rewrite_elements', array(
          '' => t('- Use default -'),
          '0' => t('- None -'),
          'div' => 'DIV',
          'span' => 'SPAN',
          'h1' => 'H1',
          'h2' => 'H2',
          'h3' => 'H3',
          'h4' => 'H4',
          'h5' => 'H5',
          'h6' => 'H6',
          'p' => 'P',
          'strong' => 'STRONG',
          'em' => 'EM',
        )),
      );
      $title['title_classes'] = array(
        '#type' => 'textfield',
        '#title' => t('Classes'),
        '#description' => t('Provide any additional classes, separated by spaces. Title must use the element wrapper above for this take effect.'),
        '#default_value' => $item['view']['settings']['title_classes'],
      );
      $title['title_override'] = array(
        '#type' => 'textfield',
        '#title' => t('Override Title'),
        '#description' => t('Enter custom text to override title output. Default: Title will be provided from the view.'),
        '#default_value' => $item['view']['settings']['title_override'],
      );
      _menu_views_form_tokens_ui($title);

      // Breadcrumb
      $settings['breadcrumb'] = array(
        '#type' => 'fieldset',
        '#title' => t('Breadcrumb'),
        '#collapsible' => TRUE,
        '#collapsed' => TRUE,
        '#parents' => $parents,
      );
      $settings['breadcrumb']['breadcrumb'] = array(
        '#type' => 'checkbox',
        '#title' => t('Show breadcrumb link'),
        '#default_value' => $item['view']['settings']['breadcrumb'],
      );
      $settings['breadcrumb']['breadcrumb_settings'] = array(
        '#type' => 'container',
        '#parents' => $parents,
        '#states' => array(
          'visible' => array(
           ':input[name="' . $parents_name . '][breadcrumb]"]' => array('checked' => TRUE),
          ),
        ),
      );
      $breadcrumb = &$settings['breadcrumb']['breadcrumb_settings'];
      $breadcrumb['breadcrumb_title'] = array(
        '#type' => 'textfield',
        '#title' => t('Link Title'),
        '#description' => t('Title to use for the breadcrumb link. Note: If there is not a title provided by the view then the breadcrumb will not be displayed. Default: View Title'),
        '#default_value' => $item['view']['settings']['breadcrumb_title'],
      );
      _menu_views_form_tokens_ui($breadcrumb);
      $breadcrumb['breadcrumb_path'] = array(
        '#type' => 'textfield',
        '#title' => t('Link Path'),
        '#description' => t('Path to use for the breadcrumb link. Default: %front.', array('%front' => '<front>')),
        '#default_value' => $item['view']['settings']['breadcrumb_path'],
      );      
      _menu_views_form_tokens_ui($breadcrumb);
    }
  }
}

/**
 * Ajax callback for re-rendering the attach views portion of the form.
 */
function _menu_views_form_ajax(&$form, &$form_state) {
  if (isset($form['#node'])) {
    return $form['menu']['link'];
  }
  return $form;
}

/**
 * Validate handler for menu_edit_item form.
 */
function _menu_views_form_validate($form, &$form_state) {
  // Only run this validation when the form is fully submitted.
  if ($form_state['submitted']) {
    $item = _menu_views_get_item($form, $form_state);
    if ($item['type'] == 'view') {
      if (!$item['view']['name']) {
        form_set_error(implode('][', _menu_views_form_parents($form)) . '][name', t('The menu item type for this @type is a view. A view name is required before this @type can be saved.', array('@type' => isset($form['#node']) ? 'node' : 'menu item')));
      }
      elseif (!$item['view']['display']) {
        form_set_error(implode('][', _menu_views_form_parents($form)) . '][display', t('The menu item type for this @type is a view. A view display is required before this @type can be saved.', array('@type' => isset($form['#node']) ? 'node' : 'menu item')));
      }
    }
  }
}

/**
 * Submit handler for menu_edit_item form.
 */
function _menu_views_form_submit($form, &$form_state) {
  $values = &$form_state['values'];
  if (isset($form['#node'])) {
    $values = &$form_state['values']['menu'];
  }
  
  // Get view settings from menu item.
  $item = _menu_views_get_item($form, $form_state);
  
  // Remove this unecessary property from the values.
  if (isset($values['menu_views'])) {
    unset($values['menu_views']);
  }
  
  // We really only want to intercept the menu edit item submit handle if this is actually a view.
  if ($item['type'] == 'view') {
    // If this is a new menu item, save a quick version of the menu item and return the mlid.
    // The menu item will get updated with the rest of the values again shortly.
    if (!$values['mlid']) {
      $values['hidden'] = (int) !$values['enabled'];
      $values['options']['attributes']['title'] = $values['description'];
      list($values['menu_name'], $values['plid']) = explode(':', $values['parent']);
      if (!$values['mlid'] = menu_link_save($values)) {
        drupal_set_message(t('There was an error creating the menu item.'), 'error');
      }
    }
    $default = _menu_views_default_values();
    $item = array(
      // The mlid should remain constant, always use the information provided by the menu module and not this one.
      'mlid' => $values['mlid'],
      'type' => $item['type'],
      'original_path' => $item['original_path'],
      'view' => $item['view'],
    );
    // Replace the menu views values in the menu item's options.
    $values['options']['menu_views'] = _menu_views_array_merge_recursive($default, $item);
  }
}


/**
 * Return a list of menu items that are valid possible parents for the given menu item.
 *
 * @param $menus
 *   An array of menu names and titles, such as from menu_get_menus().
 * @param $item
 *   The menu item or the node type for which to generate a list of parents.
 *   If $item['mlid'] == 0 then the complete tree is returned.
 * @param $type
 *   The node type for which to generate a list of parents.
 *   If $item itself is a node type then $type is ignored.
 * @return
 *   An array of menu link titles keyed on the a string containing the menu name
 *   and mlid. The list excludes the given item and its children.
 *
 * @todo This has to be turned into a #process form element callback. The
 *   'menu_override_parent_selector' variable is entirely superfluous.
 */
function _menu_views_parent_options($menus, $item, $type = '') {
  // The menu_links table can be practically any size and we need a way to
  // allow contrib modules to provide more scalable pattern choosers.
  // hook_form_alter is too late in itself because all the possible parents are
  // retrieved here, unless menu_override_parent_selector is set to TRUE.
  if (variable_get('menu_override_parent_selector', FALSE)) {
    return array();
  }

  $available_menus = array();
  if (!is_array($item)) {
    // If $item is not an array then it is a node type.
    // Use it as $type and prepare a dummy menu item for _menu_get_options().
    $type = $item;
    $item = array('mlid' => 0);
  }
  if (isset($item['mlid']) && $item['mlid']) {
    $item = menu_link_load($item['mlid']);
  }
  if (empty($type)) {
    // If no node type is set, use all menus given to this function.
    $available_menus = $menus;
  }
  else {
    // If a node type is set, use all available menus for this type.
    $type_menus = variable_get('menu_options_' . $type, array('main-menu' => 'main-menu'));
    foreach ($type_menus as $menu) {
      $available_menus[$menu] = $menu;
    }
  }

  return _menu_views_get_options($menus, $available_menus, $item);
}

/**
 * Helper function to get the items of the given menu.
 */
function _menu_views_get_options($menus, $available_menus, $item) {
  // If the item has children, there is an added limit to the depth of valid parents.
  if (isset($item['parent_depth_limit'])) {
    $limit = $item['parent_depth_limit'];
  }
  else {
    $limit = _menu_parent_depth_limit($item);
  }

  $options = array();
  foreach ($menus as $menu_name => $title) {
    if (isset($available_menus[$menu_name])) {
      $tree = menu_tree_all_data($menu_name, NULL);
      $options[$menu_name . ':0'] = '<' . $title . '>';
      _menu_views_parents_recurse($tree, $menu_name, '--', $options, $item['mlid'], $limit);
    }
  }
  return $options;
}

/**
 * Recursive helper function for menu_parent_options().
 */
function _menu_views_parents_recurse($tree, $menu_name, $indent, &$options, $exclude, $depth_limit) {
  foreach ($tree as $data) {
    if ($data['link']['depth'] > $depth_limit) {
      // Don't iterate through any links on this level.
      break;
    }
    if ($data['link']['mlid'] != $exclude && $data['link']['hidden'] >= 0) {
      $item = _menu_views_get_item($data['link']);
      _menu_views_tokenize($item);
      if ($item['type'] == 'view' && $item['view']['name'] && $item['view']['display']) {
        $title = t($item['view']['name']) . '-' . t($item['view']['display']);
        $view_title = filter_xss_admin($item['view']['settings']['title_override']);
        if (empty($view_title) && ($view = views_get_view($item['view']['name']))) {
          if ($view->access($item['view']['display']) && $view->set_display($item['view']['display'])) {
            $view->set_arguments(explode('/', $item['view']['arguments']));
            $view_title = filter_xss_admin($view->get_title());
          }
          $view->destroy();
        }
        if (!empty($view_title)) {
          $title = $view_title . ' (' . $title . ')';
        }
        $title = $indent . ' [view] ' . truncate_utf8($title, 30, TRUE, FALSE);
      }
      else {
        $title = $indent . ' ' . truncate_utf8($data['link']['title'], 30, TRUE, FALSE);
      }
      if ($data['link']['hidden']) {
        $title .= ' (' . t('disabled') . ')';
      }
      $options[$menu_name . ':' . $data['link']['mlid']] = $title;
      if ($data['below']) {
        _menu_views_parents_recurse($data['below'], $menu_name, $indent . '--', $options, $exclude, $depth_limit);
      }
    }
  }
}
