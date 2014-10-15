
/**
 * @file
 * JS functionality that creates dynamic CSS which hides permission rows and role columns.
 */

// Wrapper normalizes 'jQuery' to '$'.
;(function fpa_scope($, Drupal, window, document) {
  "use strict";
  
  var Fpa = function (context, settings) {
    this.init(context, settings);
    
    return this;
  };
  
  Fpa.prototype.selector = {
    form: '#user-admin-permissions',
    table : '#permissions'
  };
  
  Fpa.prototype.init = function (context, settings) {
    
    this.drupal_html_class_cache = {};
    
    this.dom = {};
    
    this.attr = settings.attr;
    
    this.filter_timeout= null;
    this.filter_timeout_time = 0;
    
    this.module_match = '*=';
    
    this.filter_selector_cache = {
      '*=': {},
      '~=': {}
    };
    
    this.selector.table_base_selector = '.fpa-table-wrapper tr[' + this.attr.module + ']';
    this.selector.list_counter_selector = '.fpa-perm-counter';
    this.selector.list_base_selector = '.fpa-left-section li[' + this.attr.module + ']';
    
    if (this.select(context)) {
      
      this.prepare();
      
      this.authenticated_role_behavior();
    }
  };
  
  Fpa.prototype.styles = {
    module_active_style: '{margin-right:-1px; background-color: white; border-right: solid 1px transparent;}'
  };
  
  /**
   * Select all elements that are used by FPA ahead of time and cache on 'Fpa' instance.
   */
  Fpa.prototype.select = function (context) {
    
    this.dom.context = $(context);
    
    this.dom.form = this.dom.context.find(this.selector.form);
    
    // Prevent anything else from running if the form is not found.
    if (this.dom.form.length === 0) {
      return false;
    }
    
    this.dom.container = this.dom.form.find('.fpa-container');
    
    // Raw element since $().html(); does not work for <style /> elements.
    this.dom.perm_style = this.dom.container.find('.fpa-perm-styles style').get(0);
    this.dom.role_style = this.dom.container.find('.fpa-role-styles style').get(0);
    
    this.dom.section_left = this.dom.container.find('.fpa-left-section');
    this.dom.section_right = this.dom.container.find('.fpa-right-section');
    
    this.dom.table_wrapper = this.dom.section_right.find('.fpa-table-wrapper');
    this.dom.table = this.dom.table_wrapper.find(this.selector.table);
    
    this.dom.module_list = this.dom.section_left.find('ul');
    
    this.dom.filter_form = this.dom.container.find('.fpa-filter-form');
    
    this.dom.filter = this.dom.filter_form.find('input[type="text"]');
    this.dom.role_select = this.dom.filter_form.find('select');
    this.dom.checked_status = this.dom.filter_form.find('input[type="checkbox"]');
    
    return true;
  };
  
  /**
   * Prepares a string for use as a CSS identifier (element, class, or ID name).
   * 
   * @see https://api.drupal.org/api/drupal/includes!common.inc/function/drupal_clean_css_identifier/7
   */
  Fpa.prototype.drupal_clean_css_identifier = function (str) {
    
    return str
    // replace ' ', '_', '/', '[' with '-'
    .replace(/[ _\/\[]/g, '-')
    // replace ']' with ''
    .replace(/\]/g, '')
    // Valid characters in a CSS identifier are:
    // - the hyphen (U+002D)
    // - a-z (U+0030 - U+0039)
    // - A-Z (U+0041 - U+005A)
    // - the underscore (U+005F)
    // - 0-9 (U+0061 - U+007A)
    // - ISO 10646 characters U+00A1 and higher
    // We strip out any character not in the above list.
    .replace(/[^\u002D\u0030-\u0039\u0041-\u005A\u005F\u0061-\u007A\u00A1-\uFFFF]/, '');
  };
  
  /**
   * Prepares a string for use as a valid class name.
   * 
   * @see https://api.drupal.org/api/drupal/includes!common.inc/function/drupal_html_class/7
   */
  Fpa.prototype.drupal_html_class = function (str) {
    
    if (this.drupal_html_class_cache[str] === undefined) {
      this.drupal_html_class_cache[str] = this.drupal_clean_css_identifier(str.toLowerCase());
    }
    
    return this.drupal_html_class_cache[str];
  };
  
  /**
   * Handles applying styles to <style /> tags.
   */
  Fpa.prototype.set_style = (function () {
    
    // Feature detection. Mainly for IE8.
    if ($('<style type="text/css" />').get(0).styleSheet) {
      return function (element, styles) {
        
        element.styleSheet.cssText = styles;
      };
    }
    
    // Default that works in modern browsers.
    return function (element, styles) {
      element.innerHTML = styles;
    };
  })();
  
  /**
   * Callback for click events on module list.
   */
  Fpa.prototype.filter_module = function (e) {
    
    e.preventDefault();
    e.stopPropagation();
    
    var $this = $(e.currentTarget);
    
    this.dom.filter.val([
      
      // remove current module filter string.
      this.dom.filter.val().replace(/(@.*)/, ''),
      
      // remove trailing @ as that means no module; clean 'All' filter value
      $this.attr(this.attr.module) !== '' ? '@' + $this.find('a[href]').text() : ''
      
    ].join('')); 
    
    /**
     * ~= matches exactly one whitespace separated word in attribute.
     * 
     * @see http://www.w3.org/TR/CSS2/selector.html#matching-attrs
     */
    this.module_match = '~=';
    
    this.filter();
  };
  
  Fpa.prototype.build_filter_selectors = function (filter_string) {
    
    // Extracts 'permissions@module', trimming leading and trailing whitespace.
    var matches = filter_string.match(/^\s*([^@]*)@?(.*?)\s*$/i);
    
    matches.shift(); // Remove whole match item.
    
    var safe_matches = $.map(matches, $.proxy(this.drupal_html_class, this));
    
    this.filter_selector_cache[this.module_match][filter_string] = [
      safe_matches[0].length > 0 ? '[' + this.attr.permission          + '*="' + safe_matches[0] + '"]' : '',
      safe_matches[1].length > 0 ? '[' + this.attr.module + this.module_match + '"' + safe_matches[1] + '"]' : ''
    ];
    
    return this.filter_selector_cache[this.module_match][filter_string];
  };
  
  Fpa.prototype.get_filter_selectors = function (filter_string) {
    
    filter_string = filter_string || this.dom.filter.val();
    
    return this.filter_selector_cache[this.module_match][filter_string] || this.build_filter_selectors(filter_string);
  };
  
  Fpa.prototype.permission_grid_styles = function (filters) {
    
    filters = filters || this.get_filter_selectors();
    
    var checked_filters = this.build_checked_selectors();
    
    var styles = [
      this.selector.table_base_selector,
      '{display: none;}'
    ];
    
    for (var i = 0; i < checked_filters.length; i++) {
      
      styles = styles.concat([
        this.selector.table_base_selector,
        
        checked_filters[i],
        
        filters[0],
        filters[1],
        '{display: table-row;}'
      ]);
    }
    
    return styles.join('');
    
  };
  
  Fpa.prototype.counter_styles = function (filters) {
    
    filters = filters || this.get_filter_selectors();
    
    return [
      this.selector.list_counter_selector,
      '{display: none;}',
      
      this.selector.list_counter_selector,
      filters[0],
      '{display: inline;}'
    ].join('');
    
  };
  
  Fpa.prototype.module_list_styles = function (filters) {
    
    filters = filters || this.get_filter_selectors();
    
    return [ 
      this.selector.list_base_selector,
      (filters[1].length > 0 ? filters[1] : '[' + this.attr.module + '=""]'),
      this.styles.module_active_style
    ].join('');
    
  };
  
  Fpa.prototype.filter = function () {
    
    var perm = this.dom.filter.val();
    
    $.cookie('fpa_filter', perm, {path: '/'});
    $.cookie('fpa_module_match', this.module_match, {path: '/'});
          
    this.save_filters();
    
    var filter_selector = this.get_filter_selectors(perm);
    
    this.set_style(this.dom.perm_style, [
      
      this.permission_grid_styles(filter_selector),
      
      this.counter_styles(filter_selector),
      
      this.module_list_styles(filter_selector)
      
    ].join(''));
  };
  
  Fpa.prototype.build_role_selectors = function (roles) {
    
    roles = roles || this.dom.role_select.val();
    
    var selectors = ['*'];
    
    if ($.inArray('*', roles) === -1) {
      
      selectors = $.map(roles, $.proxy(function (value, index) {
        
        return '[' + this.attr.role + '="' + value + '"]';
        
      }, this));
    }
    
    return selectors;
  };
  
  Fpa.prototype.build_checked_selectors = function (roles) {
    
    roles = roles || this.dom.role_select.val();
    
    var checked_boxes = $.map(this.dom.checked_status, function (element, index) {
      return element.checked ? $(element).val() : null;
    });
    
    var selectors = [''];
    
    if ($.inArray('*', roles) !== -1) {
      roles = $.map(this.dom.role_select.find('option').not('[value="*"]'), $.proxy(function (element, index) {
        
        return $(element).attr('value');
        
      }, this));
    }
    
    if (checked_boxes.length != this.dom.checked_status.length) {
      
      selectors = $.map(roles, $.proxy(function (value, index) {
        
        return $.map(checked_boxes, $.proxy(function (checked_attr, index) {
          
          return '[' + checked_attr + '~="' + value + '"]';
          
        }, this));
        
      }, this));
    }
    
    return selectors;
  };
  
  // Even handler for role selection.
  Fpa.prototype.filter_roles = function () {
    
    this.save_filters();
    
    var values = this.dom.role_select.val() || [];
    var role_style_code = [];
    
    $.cookie('fpa_roles', JSON.stringify(values), {path: '/'});
    
    // Only filter if "All Roles" is not selected.
    if ($.inArray('*', values) === -1) {
      
      role_style_code.push('.fpa-table-wrapper [' + this.attr.role + '] {display: none;}');
      
      if (values.length > 0) {
        
        var role_selectors = this.build_role_selectors(values);
        
        role_style_code = role_style_code.concat($.map(role_selectors, $.proxy(function (value, index) {
          
          return '.fpa-table-wrapper ' + value + ' {display: table-cell;}';
          
        }, this)));
        
        // Ensure right border on last visible role.
        role_style_code.push('.fpa-table-wrapper ' + role_selectors.pop() + ' {border-right: 1px solid #bebfb9;}');
      }
      else {
        role_style_code.push('td[class="permission"] {border-right: 1px solid #bebfb9;}');
      }
      
    }
    
    this.set_style(this.dom.role_style, role_style_code.join(''));
    
    this.filter();
  };
  
  /**
   * Prevent the current filter from being cleared on form reset.
   */
  Fpa.prototype.save_filters = function () {
    
    /**
     * element.defaultValue is what 'text' elements reset to.
     * 
     * @link http://www.w3.org/TR/REC-DOM-Level-1/level-one-html.html#ID-26091157
     */
    this.dom.filter.get(0).defaultValue = this.dom.filter.val();
    
    /**
     * element.defaultSelected is what 'option' elements reset to.
     * 
     * @see http://www.w3.org/TR/REC-DOM-Level-1/level-one-html.html#ID-37770574
     */
    this.dom.role_select.find('option').each(function (index, element) {
      element.defaultSelected = element.selected;
    });
    
    /**
     * element.defaultChecked is what 'checkbox' elements reset to.
     * 
     * @see http://www.w3.org/TR/REC-DOM-Level-1/level-one-html.html#ID-20509171
     */
    this.dom.checked_status.each(function (index, element) {
      element.defaultChecked = element.checked;
    });
  };
  
  Fpa.prototype.prepare = function () {
    
    this.filter_timeout_time = Math.min(this.dom.table.find('tr').length, 200);
    
    this.dom.form
      .delegate('.fpa-toggle-container a', 'click', $.proxy(function fpa_toggle(e) {
        e.preventDefault();
        
        var toggle_class = $(e.currentTarget).attr('fpa-toggle-class');
        
        this.dom.container.toggleClass(toggle_class).hasClass(toggle_class);
        
      }, this))
    ;
    
    this.dom.section_left
      .delegate('li', 'click', $.proxy(this.filter_module, this))
    ;
    
    this.dom.filter
      // Prevent Enter/Return from submitting form.
      .keypress(function fpa_prevent_form_submission(e) {
        if (e.which === 13) {
          e.preventDefault();
          e.stopPropagation();
        }
      })
      // Prevent non-character keys from triggering filter.
      .keyup($.proxy(function fpa_filter_keyup(e) {
        
        // Prevent ['Enter', 'Shift', 'Ctrl', 'Alt'] from triggering filter.
        if ($.inArray(e.which, [13, 16, 17, 18]) === -1) {
          
          window.clearTimeout(this.filter_timeout);
          
          this.filter_timeout = window.setTimeout($.proxy(function () {
            
            this.dom.table_wrapper
              .detach()
              .each($.proxy(function (index, element) {
                
                this.module_match = '*=';
                
                this.filter();
              }, this))
              .appendTo(this.dom.section_right)
            ;
            
          }, this), this.filter_timeout_time);
        }
      }, this))
    ;
    
    // Handle links to sections on permission admin page.
    this.dom.form
      .delegate('a[href*="admin/people/permissions#"]', 'click', $.proxy(function fpa_inter_page_links_click(e) {
        e.preventDefault();
        e.stopPropagation();
        
        this.dom.module_list
          .find('li[' + this.attr.module + '~="' + this.drupal_html_class(e.currentTarget.hash.substring(8)) + '"]')
          .click()
        ;
        
        $('body').scrollTop(this.dom.container.position().top);
      }, this))
    ;
    
    // Handler for links that use #hash and can't be capture server side.
    if(window.location.hash.indexOf('module-') === 1) {
      
      this.dom.module_list
        .find('li[' + this.attr.module + '~="' + this.drupal_html_class(window.location.hash.substring(8)) + '"]')
        .click()
      ;
    }
    
    /**
     * Reset authenticated role behavior when form resets.
     * 
     * @todo should this be synchronous? Would have to trigger reset on elements while detached.
     */
    this.dom.form.bind('reset', $.proxy(function fpa_form_reset(e) {
      
      // Wait till after the form elements have been reset.
      window.setTimeout($.proxy(function fpa_fix_authenticated_behavior() {
        
        this.dom.table_wrapper
          .detach() // Don't make numerous changes while elements are in the rendered DOM.
          .each($.proxy(function (index, element) {
            
            $(element)
              .find('input[type="checkbox"].rid-2')
              .each(this.dummy_checkbox_behavior)
            ;
          }, this))
          .appendTo(this.dom.section_right)
        ;
        
      }, this), 0);
    }, this));
    
    
    // Role checkboxes toggle all visible permissions for this column.
    this.dom.section_right
      .delegate('th[' + this.attr.role + '] input[type="checkbox"].fpa-checkboxes-toggle', 'change', $.proxy(function fpa_role_permissions_toggle(e) {
        
        var $this = $(e.currentTarget);
        
        // Get visible rows selectors.
        var filters = this.get_filter_selectors(this.dom.filter.val());
        
        this.dom.table_wrapper
          .detach()
          .each($.proxy(function (index, element) {
            
            var rid = $this.closest('[' + this.attr.role + ']').attr(this.attr.role);
            
            $(element)
              .find([
                'tr' + filters.join(''),
                'td.checkbox[' + this.attr.role + '="' + rid + '"]',
                'input[type="checkbox"][name]'
              ].join(' ')) // Array is easier to read, separated for descendant selectors.
              
              .attr('checked', $this.attr('checked'))
              
              .filter('.rid-2') // Following only applies to "Authenticated User" role.
              .each(this.dummy_checkbox_behavior)
            ;
          }, this))
          .appendTo(this.dom.section_right)
        ;
        
      }, this))
    ;
    
    // Permission checkboxes toggle all visible permissions for this row.
    this.dom.section_right
      .delegate('td.permission input[type="checkbox"].fpa-checkboxes-toggle', 'change', $.proxy(function fpa_role_permissions_toggle(e) {
        
        // Get visible rows selectors.
        
        var $row = $(e.currentTarget).closest('tr');
        
        $row.prev('tr').after(
          
          $row
          .detach()
          .each($.proxy(function (index, element) {
            
            $(element)
              .find('td.checkbox')
              .filter(this.build_role_selectors().join(','))
              .find('input[type="checkbox"][name]')
              
              .attr('checked', e.currentTarget.checked)
              
              .filter('.rid-2') // Following only applies to "Authenticated User" role.
              .each(this.dummy_checkbox_behavior)
            ;
            
          }, this))
        );
        
      }, this))
    ;
    
    // Clear contents of search field and reset visible permissions.
    this.dom.section_right
      .delegate('.fpa-clear-search', 'click', $.proxy(function (e) {
        
        this.dom.filter
          .val('')
        ;
        
        this.filter();
      }, this))
    ;
    
    // Change visible roles.
    this.dom.role_select
      .bind('change blur', $.proxy(this.filter_roles, this))
    ;
    
    this.dom.checked_status
      .bind('change', $.proxy(function (e) {
        
        this.save_filters();
        
        this.filter();
        
      }, this))
    ;

    /**
     * System name is not normally selectable because its a pseudo-element.
     *
     * This detects clicks directly on the TR, which happens when a click is on
     * the pseudo-element, and displays a prompt() with the system name as the
     * pre-populated value.
     */
    this.dom.table
      .delegate('tr[' + this.attr.system_name + ']', 'click', $.proxy(function (e) {
        var $target = $(e.target);

        if ($target.is('tr[' + this.attr.system_name + ']')) {

          window.prompt('You can grab the system name here', $target.attr(this.attr.system_name));
        }
      }, this))
    ;
    
    // Focus on element takes long time, bump after normal execution.
    window.setTimeout($.proxy(function fpa_filter_focus() {
      this.dom.filter.focus();
    }, this), 0);
    
  };
  
  /**
   * Event handler/iterator.
   * 
   * Should not be $.proxy()'d.
   */
  Fpa.prototype.dummy_checkbox_behavior = function () {
    // 'this' refers to the element, not the 'Fpa' instance.
    $(this).closest('tr').toggleClass('fpa-authenticated-role-behavior', this.checked);
  };
  
  Fpa.prototype.authenticated_role_behavior = function () {
    
    this.dom.table_wrapper
      .delegate('input[type=checkbox].rid-2', 'mousedown', function (e) {
        
        $(e.currentTarget).unbind('click.permissions');
      })
      .delegate('input[type=checkbox].rid-2', 'change.fpa_authenticated_role', this.dummy_checkbox_behavior)
    ;
  };
  
  Drupal.behaviors.fpa = {
    attach: function (context, settings) {
      
      // Add touch-screen styling for checkboxes to make easier to use.
      if (document.documentElement.ontouchstart !== undefined) {
        $(document.body).addClass('fpa-mobile');
      }
      
      // Fix table sticky table headers width due to changes in visible roles.
      $(window)
        .bind('scroll', function fpa_fix_tableheader(e) {
          $(e.currentTarget).triggerHandler('resize.drupal-tableheader');
        })
      ;
    
      new Fpa(context, settings.fpa);
    }
  };
  
  // Override Drupal core's Authenticated role checkbox behavior.
  Drupal.behaviors.permissions.attach = $.noop;
  
  // Drupal.behaviors.formUpdated.attach = $.noop;
})(jQuery, Drupal, window, document);
