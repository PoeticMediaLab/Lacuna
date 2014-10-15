<?php

/**
 * @file
 * Theme callbacks to pre-tag rows for FPA functionality.
 */

/**
 * Implements hook_theme().
 */
function fpa_theme($existing, $type, $theme, $path) {
  return array(
    'fpa_user_admin_permissions' => array(
      'render element' => 'form',
      'file' => 'fpa.theme.inc',
    ),
  );
}

/**
 * Theme function to pre-mark rows with FPA attributes.
 * 
 * Based on Drupal Core's permissions form theme function.
 * 
 * @see theme_user_admin_permissions().
 */
function theme_fpa_user_admin_permissions($variables) {
  $form = $variables['form'];
  
  $nameless_checkbox = array(
    '#type' => 'html_tag',
    '#tag' => 'input',
    '#attributes' => array(
      'type' => 'checkbox',
      'class' => array(
        'rid-1', // Prevents Drupal core Drupal.behaviors.permissions.toggle from applying.
        'form-checkbox',
        'fpa-checkboxes-toggle',
      ),
    ),
  );
  
  $nameless_checkbox_output = drupal_render($nameless_checkbox);
  
  
  $dummy_checkbox = array(
    '#type' => 'html_tag',
    '#tag' => 'input',
    '#attributes' => array(
      'type' => 'checkbox',
      'disabled' => 'disabled',
      'checked' => 'checked',
      'title' => t('This permission is inherited from the authenticated user role.'),
      'class' => array(
        'dummy-checkbox',
      ),
    ),
  );
  
  $dummy_checkbox_output = drupal_render($dummy_checkbox);
  
  
  $permission_col_template = array(
    '#type' => 'container',
    '#attributes' => array(
      'class' => array(
        'fpa-permission-container',
      ),
    ),
    'description' => array(
      '#markup' => '',
    ),
    'checkbox_cell' => array(
      '#type' => 'container',
      '#attributes' => array(
        'class' => array(
          'fpa-row-toggle-container',
        ),
      ),
      'checkbox_form_item' => array(
        '#type' => 'container',
        '#attributes' => array(
          'title' => t('Toggle visible checkboxes in this row.'),
          'class' => array(
            'form-item',
            'form-type-checkbox',
          ),
        ),
        'label' => array(
          '#type' => 'html_tag',
          '#tag' => 'label',
          '#attributes' => array(
            'class' => array(
              'element-invisible',
            ),
          ),
          '#value' => 'test',
        ),
        'checkbox' => array(
          '#markup' => $nameless_checkbox_output,
        ),
      ),
    ),
  );
  
  $checkboxes_children = element_children($form['checkboxes']);
  
  // Prepare role names processed by drupal_html_class() ahead of time.
  $roles_attr_values = array();
  
  foreach ($checkboxes_children as $rid) {
    $roles_attr_values[$rid] = drupal_html_class($form['role_names'][$rid]['#markup']);
  }
  
  $first_role_index = array_shift($checkboxes_children);
  
  // Lists for wrapper.
  $modules = array();
  $user_roles = array();
  
  // Index of current module row.
  $module = NULL;
  
  // Row counter.
  $i = 0;
  
  $rows = array();

  // Iterate over rows in form table.
  foreach (element_children($form['permission']) as $key) {
    
    // Row template.
    $row = array(
      'data' => array(), // Array of table cells.
      'title' => array(), // HTML attribute on table row tag.
      FPA_ATTR_MODULE => array(), // HTML attribute on table row tag.
      FPA_ATTR_PERMISSION => array(), // HTML attribute on table row tag.
      FPA_ATTR_CHECKED => array(),
      FPA_ATTR_NOT_CHECKED => array(),
    );
    
    // Determine if row is module or permission.
    if (is_numeric($key)) {
      // Module row.
      
      $row['class'][] = 'fpa-module-row';
      
      // Mark current row with escaped module name.
      $row[FPA_ATTR_MODULE] = array(
        // System name
        0 => $form['permission'][$key]['#id'],
        // Readable name
        1 => strip_tags($form['permission'][$key]['#markup']),
      );
      
      // Readable
      $row['data'][] = array(
        'data' => drupal_render($form['permission'][$key]),
        'class' => array('module'),
        'id' => 'module-' . $form['permission'][$key]['#id'],
        'colspan' => count($form['role_names']['#value']) + 1,
      );
      
      $row['title'] = array($form['permission'][$key]['#id']);
      
      $row[FPA_ATTR_SYSTEM_NAME] = $row[FPA_ATTR_MODULE][0];
      
      $row[FPA_ATTR_MODULE] = array_unique(array_map('drupal_html_class', $row[FPA_ATTR_MODULE]));
      
      // Add modules to left-side modules list.
      $modules[$row[FPA_ATTR_MODULE][0]] = array(
        'text' => strip_tags($form['permission'][$key]['#markup']),
        'title' => array($form['permission'][$key]['#id']),
        FPA_ATTR_MODULE => $row[FPA_ATTR_MODULE],
        FPA_ATTR_PERMISSION => array(),
      );
      
      // Save row number for current module.
      $module = $i;
    }
    else {
      // Permission row.
      
      $row['class'][] = 'fpa-permission-row';
      
      $permission_system_name = '';
      
      // Might be empty if no modules are displayed in Permissions Filter module.
      if (!empty($form['checkboxes'][$first_role_index])) {
        $permission_system_name = $form['checkboxes'][$first_role_index][$key]['#return_value'];
      }
      
      $label = $permission_col_template;
      
      $label['description']['#markup'] = drupal_render($form['permission'][$key]);
      
      // Permissions filter might cause no Roles to display.
      if (count(element_children($form['checkboxes'])) == 0) {
        unset($label['checkbox_cell']);
      }
      
      // Readable
      $row['data'][] = array(
        'data' => drupal_render($label),
        'class' => array('permission'),
      );
      
      foreach (element_children($form['checkboxes']) as $rid) {
        $form['checkboxes'][$rid][$key]['#title'] = $form['role_names'][$rid]['#markup'] . ': ' . $form['permission'][$key]['#markup'];
        $form['checkboxes'][$rid][$key]['#title_display'] = 'invisible';
        
        // Filter permissions strips role id class from checkbox. Used by Drupal core functionality.
        $form['checkboxes'][$rid][$key]['#attributes']['class'][] = 'rid-' . $rid;
        
        // Set authenticated role behavior class on page load.
        if ($rid == 2 && $form['checkboxes'][$rid][$key]['#checked'] === TRUE) {
          $row['class'][] = 'fpa-authenticated-role-behavior';
        }
        
        // For all roles that inherit permissions from 'authenticated user' role, add in dummy checkbox for authenticated role behavior.
        if ($rid > 2) {
          $form['checkboxes'][$rid][$key]['#suffix'] = $dummy_checkbox_output; // '#suffix' doesn't have wrapping HTML like '#field_suffix'.
        }
        
        // Add rid's to row attribute for checked status filter.
        if ($form['checkboxes'][$rid][$key]['#checked'] === TRUE) {
          $row[FPA_ATTR_CHECKED][] = $rid;
        }
        else {
          $row[FPA_ATTR_NOT_CHECKED][] = $rid;
        }
        
        $row['data'][] = array(
          'data' => drupal_render($form['checkboxes'][$rid][$key]),
          'class' => array(
            'checkbox',
          ),
          'title' => array(
            $form['role_names'][$rid]['#markup'],
          ),
          // For role filter
          FPA_ATTR_ROLE => array(
            $rid,
          ),
        );
      }
      
      if (!empty($rid)) {
        $row['title'] = array(
          $form['checkboxes'][$rid][$key]['#return_value'],
        );
        
        $row[FPA_ATTR_SYSTEM_NAME] = array(
          $form['checkboxes'][$rid][$key]['#return_value'],
        );
      }
      
      // Mark current row with escaped permission name.
      $row[FPA_ATTR_PERMISSION] = array(
        // Permission system name.
        0 => $permission_system_name,
        // Readable description.
        1 => strip_tags($form['permission'][$key]['#markup']),
      );
      
      // Mark current row with current module.
      $row[FPA_ATTR_MODULE] = $rows[$module][FPA_ATTR_MODULE];
      
      $row[FPA_ATTR_PERMISSION] = array_unique(array_map('drupal_html_class', $row[FPA_ATTR_PERMISSION]));
      
      // Add current permission to current module row.
      $rows[$module][FPA_ATTR_PERMISSION] = array_merge($rows[$module][FPA_ATTR_PERMISSION], $row[FPA_ATTR_PERMISSION]);
      
      $rows[$module][FPA_ATTR_CHECKED] = array_unique(array_merge($rows[$module][FPA_ATTR_CHECKED], $row[FPA_ATTR_CHECKED]));
      $rows[$module][FPA_ATTR_NOT_CHECKED] = array_unique(array_merge($rows[$module][FPA_ATTR_NOT_CHECKED], $row[FPA_ATTR_NOT_CHECKED]));
      
      $modules[$rows[$module][FPA_ATTR_MODULE][0]][FPA_ATTR_PERMISSION][] = $row[FPA_ATTR_PERMISSION];
    }
    
    $rows[$i++] = $row;
  }
  
  $reset_button = array(
    '#type' => 'html_tag',
    '#tag' => 'input',
    '#attributes' => array(
      'type' => 'reset',
      'class' => 'form-submit',
      'value' => t('Reset changes'),
    ),
  );
  
  // If there is no submit button, don't add the reset button.
  if (count(element_children($form['actions'])) > 0) {
    
    // Have the reset button appear before the submit button.
    array_unshift($form['actions'], $reset_button);
  }
  
  $actions_output = drupal_render_children($form['actions']);
  
  $header = array();
  
  $header[] = array(
    'data' => t('Permission') . $actions_output,
  );
  
  foreach (element_children($form['role_names']) as $rid) {
    
    $header[] = array(
      'data' => drupal_render($form['role_names'][$rid]) . $nameless_checkbox_output,
      'class' => array(
        'checkbox',
      ),
      'title' => array(
        $form['role_names'][$rid]['#markup'],
      ),
      FPA_ATTR_ROLE => array(
        $rid,
      ),
    );
    $user_roles[$rid] = $form['role_names'][$rid]['#markup'];
  }
  
  $table = array(
    'header' => $header,
    'rows' => $rows,
  );
  
  $output = _fpa_wrapper($table, $modules, $user_roles, $actions_output);
  
  $output .= drupal_render_children($form);
  
  return $output;
}

/**
 * Wraps table output in the FPA filter.
 */
function _fpa_wrapper($permissions_table, $modules, $user_roles, $actions_output) {
  
  $same_page = trim(parse_url($_SERVER['HTTP_REFERER'], PHP_URL_PATH), '/') == $_GET['q'];
  
  $render = array(
    '#type' => 'container',
    '#attributes' => array(
      'class' => array(
        'fpa-container',
      ),
    ),
  );
  
  $hiders = array(
    'fpa-hide-descriptions' => array(
      'hide' => t('Hide descriptions'),
      'show' => t('Show descriptions'),
    ),
    'fpa-hide-system-names' => array(
      'hide' => t('Hide system names'),
      'show' => t('Show system names'),
    ),
  );

  $render['#attributes']['class'][] = 'fpa-hide-system-names';

  $hide_container = array(
    '#type' => 'container',
    '#attributes' => array(
      'class' => array(
        'fpa-toggle-container',
      ),
    ),
  );
  
  foreach ($hiders as $hide_class => $labels) {
    
    $hide_container[$hide_class] = array(
      '#theme' => 'link',
      '#text' => '',
      '#path' => '',
      '#options' => array(
        'attributes' => array_merge($labels, array(
          'fpa-toggle-class' => $hide_class,
        )),
        'html' => TRUE,
        'fragment' => ' ',
        'external' => TRUE, // Prevent base path from being added to link.
      ),
    );
  }
  
  $render['hide_container'] = $hide_container;
  
  $wrapper = array(
    '#type' => 'container',
    '#attributes' => array(
      'class' => array(
        'fpa-wrapper',
      ),
    ),
  );
  
  $render['wrapper'] = &$wrapper;
  
  /**
   * <style /> block template.
   */
  $style_template = array(
    '#type' => 'container',
    '#attributes' => array(
      'class' => array(
        'style-wrapper-class-name', // Override on specific block.
      ),
    ),
  );
  
  $style_template['style'] = array(
    '#type' => 'html_tag',
    '#tag' => 'style',
    '#attributes' => array(
      'type' => array(
        'text/css',
      ),
    ),
    '#value' => '', // #value needed for closing tag.
  );
  
  /**
   * <style /> block for role filtering.
   */
  $wrapper['role_styles'] = $style_template;
  $wrapper['role_styles']['#attributes']['class'][0] = 'fpa-role-styles';
  
  /**
   * <style /> block for permission filtering.
   */
  $wrapper['perm_styles'] = $style_template;
  $wrapper['perm_styles']['#attributes']['class'][0] = 'fpa-perm-styles';
  
  /**
   * Left section contains module list and form submission button.
   */
  $left_section = array(
    '#type' => 'container',
    '#attributes' => array(
      'class' => array(
        'fpa-left-section',
      ),
    ),
  );
  
  $wrapper['left_section'] = &$left_section;
  
  
  /**
   * Right section contains filter form and permissions table.
   */
  $right_section = array(
    '#type' => 'container',
    '#attributes' => array(
      'class' => array(
        'fpa-right-section',
      ),
    ),
  );
  
  $wrapper['right_section'] = &$right_section;
  
  $module_template = array(
    FPA_ATTR_MODULE => array(),
    FPA_ATTR_PERMISSION => array(),
    'data' => array(
      '#type' => 'container',
      '#attributes' => array(),
      
      'link' => array(
        '#type' => 'markup',
        '#markup' => '', // l($module['text'], 'admin/people/permissions', $options)
      ),
      
      'counters' => array(),
      
      'total' => array(
        '#type' => 'html_tag',
        '#tag' => 'span',
        '#attributes' => array(
          'class' => array('fpa-perm-total'),
          'fpa-total' => 0,
        ),
        '#value' => '', // #value needed for closing tag.
      ),
    ),
  );
  
  $counter_template = array(
    '#type' => 'html_tag',
    '#tag' => 'span',
    '#attributes' => array(
      'class' => array('fpa-perm-counter'),
      FPA_ATTR_PERMISSION => array(), // Counters only count permissions match.
    ),
    '#value' => '', // #value required for closing tag.
  );
  
  $items = array();
  
  $all_modules = array(
    'text' => t('All modules'),
    FPA_ATTR_MODULE => array(),
    FPA_ATTR_PERMISSION => array(),
  );
  
  array_unshift($modules, $all_modules);
  
  $all_modules_counters = array();
  
  foreach ($modules as $module) {
    
    $module_item = $module_template;
    
    $module_item[FPA_ATTR_MODULE] = $module[FPA_ATTR_MODULE];
    $module_item[FPA_ATTR_PERMISSION] = array_reduce($module[FPA_ATTR_PERMISSION], 'array_merge', array());
    
    // Use link for accessibility and tabability.
    $options = array(
      'fragment' => 'all',
    );
    
    if (!empty($module['title'])) {
      $options['fragment'] = 'module-' . $module['title'][0];
      $options['attributes']['title'] = $module['title'][0];
    }
    
    $module_item['data']['link']['#markup'] = l($module['text'], 'admin/people/permissions', $options);
    
    foreach ($module[FPA_ATTR_PERMISSION] as $module_perm) {
      
      $counter_item = $counter_template;
      
      $counter_item['#attributes'][FPA_ATTR_PERMISSION] = $module_perm;
      
      $all_modules_counters[] = $counter_item;
      
      $module_item['data']['counters'][] = $counter_item;
    }
    
    $module_item['data']['total']['#attributes']['fpa-total'] = count($module[FPA_ATTR_PERMISSION]);
    
    $items[] = $module_item;
  }
  
  $items[0]['data']['counters'] = $all_modules_counters;
  $items[0]['data']['total']['#attributes']['fpa-total'] = count($all_modules_counters);
  
  foreach ($items as &$item) {
    $item['data'] = drupal_render($item['data']);
  }
  
  $left_section['list'] = array(
    '#items' => $items,
    '#theme' => 'item_list',
  );
  
  $left_section['buttons'] = array(
    '#type' => 'markup',
    '#markup' => $actions_output,
  );
  
  $filter_form = array(
    '#type' => 'container',
    '#attributes' => array(
      'class' => array(
        'fpa-filter-form',
      ),
    ),
  );
  
  $clear_button = array(
    '#type' => 'html_tag',
    '#tag' => 'input',
    '#attributes' => array(
      'type' => array(
        'button',
      ),
      'class' => array(
        'fpa-clear-search',
        'form-submit',
      ),
      'value' => 'Clear filter',
    ),
  );
  
  $default_filter = '';
  
  if (!empty($_GET['fpa_perm'])) {
    $default_filter = $_GET['fpa_perm'];
  }
  
  if (!empty($_COOKIE['fpa_filter']) && $same_page) {
    $default_filter = $_COOKIE['fpa_filter'];
  }
  
  
  $filter_form['permission_module_filter'] = array(
    '#type' => 'textfield',
    '#title' => t('Filter:'),
    '#description' => t('<p>Enter in the format of "permission@module",</p><p>e.g. <em>admin@system</em> will show only permissions with the<br>text "admin" in modules with the text "system".</p><p>This will also match on system name of a permission.</p>'),
    '#size' => 25,
    '#field_suffix' => drupal_render($clear_button),
    '#attributes' => array(
      'placeholder' => array(
        'permission@module',
      ),
      'autofocus' => 'autofocus',
    ),
    '#value' => $default_filter,
  );
  
  /*
   * Populate the permission filter styles.
   */
  $matches = array();
  
  preg_match('/^\s*([^@]*)@?(.*?)\s*$/i', $filter_form['permission_module_filter']['#value'], $matches);
  
  array_shift($matches); // Remove whole match item.
  
  $safe_matches = array_map('drupal_html_class', $matches);
  
  $module_match = !empty($_COOKIE['module_match']) ? $_COOKIE['module_match'] : '*=';
  
  $filters = array(
    drupal_strlen($safe_matches[0]) > 0 ? ('[' . FPA_ATTR_PERMISSION .               '*="' . $safe_matches[0] . '"]') : '',
    drupal_strlen($safe_matches[1]) > 0 ? ('[' . FPA_ATTR_MODULE     . $module_match . '"' . $safe_matches[1] . '"]') : '',
  );
  
  $filter_styles = array(
    '.fpa-table-wrapper tr[' . FPA_ATTR_MODULE . ']{display: none;}',
    
    '.fpa-table-wrapper tr[' . FPA_ATTR_MODULE . ']',
    $filters[0],
    $filters[1],
    '{display: table-row;}',
    
    
    '.fpa-perm-counter{display: none;}',
    '.fpa-perm-counter',
    $filters[0],
    '{display: inline;}',
    
    
    '.fpa-left-section li[' . FPA_ATTR_MODULE . ']',
    drupal_strlen($filters[1]) > 0 ? $filters[1] : '[' . FPA_ATTR_MODULE . '=""]',
    '{margin-right:-1px; background-color: white; border-right: solid 1px transparent;}',
  );
  
  $wrapper['perm_styles']['style']['#value'] = implode('', $filter_styles);
  
  
  $cookie_roles = (!empty($_COOKIE['fpa_roles']) && $same_page) ? json_decode($_COOKIE['fpa_roles']) : array();
  
  $options = array(
    '*' => t('--All Roles'),
  );
  
  if (!empty($user_roles)) {
    $options += $user_roles; // Preserves keys.
  }
  
  if (in_array('*', $cookie_roles)) {
    $cookie_roles  = array('*');
  }
  
  $filter_form['role_filter'] = array(
    '#type' => 'select',
    '#title' => t('Roles:'),
    '#description' => t('Select which roles to display.<br>Ctrl+click to select multiple.'),
    '#size' => 5,
    '#options' => $options,
    '#attributes' => array(
      'multiple' => 'multiple',
      'autocomplete' => 'off', // Keep browser from populating this from 'cached' input.
    ),
    '#value' => count(array_intersect($cookie_roles, array_keys($options))) > 0 ? $cookie_roles : array('*'),
  );
  
  /*
   * Populate the roles styles.
   */
  if (!in_array('*', $filter_form['role_filter']['#value'])) {
    
    $role_styles = array(
      '.fpa-table-wrapper [' . FPA_ATTR_ROLE . '] {display: none;}',
    );
    
    foreach ($filter_form['role_filter']['#value'] as $value) {
      
      $role_styles[] = '.fpa-table-wrapper [' . FPA_ATTR_ROLE . '="' . $value . '"] {display: table-cell;}';
    }
    
    $role_styles[] = '.fpa-table-wrapper [' . FPA_ATTR_ROLE . '="' . end($filter_form['role_filter']['#value']) . '"] {border-right: 1px solid #bebfb9;}';
    
    $wrapper['role_styles']['style']['#value'] = implode('', $role_styles);
  }
  
  $checked_status = array(
    '#type' => 'checkboxes',
    '#title' => t('Display permissions that are:'),
    '#options' => array(
      FPA_ATTR_CHECKED => t('Checked'),
      FPA_ATTR_NOT_CHECKED => t('Not Checked'),
    ),
    '#attributes' => array(),
    '#title_display' => 'before',
    '#description' => t('Applies to all visible roles.<br />Unsaved changes are not counted.<br />Most effective when a single role is visible.<br />Empty module rows sometimes display when used with permission filter.'),
  );
  
  $checked_status_keys = array_keys($checked_status['#options']);
  
  $checked_status['#value'] = array_combine($checked_status_keys, $checked_status_keys);
  
  $filter_form['checked_status'] = form_process_checkboxes($checked_status);
  
  foreach (element_children($filter_form['checked_status']) as $key) {
    $filter_form['checked_status'][$key]['#checked'] = TRUE;
  }
  
  $right_section['filter_form'] = $filter_form;
  
  $table_wrapper = array(
    '#type' => 'container',
    '#attributes' => array(
      'class' => array(
        'fpa-table-wrapper',
      ),
    ),
  );
  
  $table_wrapper['table'] = array(
    '#theme' => 'table',
    '#header' => $permissions_table['header'],
    '#rows' => $permissions_table['rows'],
    '#attributes' => array(
      'id' => 'permissions',
    ),
  );
  
  // Show after full table HTML is loaded. Reduces progressive table load reflow/repaint.
  $table_wrapper['show_table'] = array(
    '#type' => 'html_tag',
    '#tag' => 'style',
    '#attributes' => array(
      'type' => array(
        'text/css',
      ),
    ),
    '#value' => '#permissions {display: table;} .fpa-table-wrapper {background: none;}',
  );
  
  $table_wrapper['buttons'] = array(
    '#type' => 'markup',
    '#markup' => $actions_output,
  );
  
  $right_section['table_wrapper'] = $table_wrapper;
  
  
  return drupal_render($render);
}
