(function ($) {

/**
 * Equal height plugin.
 *
 * From: http://www.problogdesign.com/coding/30-pro-jquery-tips-tricks-and-strategies/
 */
if (jQuery.fn.equalHeight == undefined) {
  jQuery.fn.equalHeight = function () {
    var tallest = 0;
    this.each(function() {
      tallest = ($(this).height() > tallest)? $(this).height() : tallest;
    });
    return this.height(tallest);
  }
}

Drupal.jQueryUiFilter = Drupal.jQueryUiFilter || {}
Drupal.jQueryUiFilter.tabsOptions = Drupal.jQueryUiFilter.tabsOptions || {}

/**
 * Tabs pagings
 *
 * Inspired by : http://css-tricks.com/2361-jquery-ui-tabs-with-nextprevious/
 */
Drupal.jQueryUiFilter.tabsPaging = function(selector, options) {
  options = jQuery.extend({paging: {'back': '&#171; Previous', 'next': 'Next &#187;'}}, options);

  var $tabs = $(selector);
  var numberOfTabs = $tabs.find(".ui-tabs-panel").size() - 1;

  // Add back and next buttons.
  // NOTE: Buttons are not 'themeable' since they should look like a themerolled jQuery UI button.
  $tabs.find('.ui-tabs-panel').each(function(i){
    var html = '';
    if (i != 0) {
      html += '<button type="button" class="ui-tabs-prev" rel="' + (i-1) + '" style="float:left">' + Drupal.t(options.paging.back) + '</button>';
    }
    if (i != numberOfTabs) {
      html += '<button type="button" href="#" class="ui-tabs-next" rel="' + (i+1) + '" style="float:right">' + Drupal.t(options.paging.next) + '</button>';
    }
    $(this).append('<div class="ui-tabs-paging clearfix clear-block">' +  html + '</div>');
  });

  // Init buttons
  $tabs.find('button.ui-tabs-prev, button.ui-tabs-next').button();

  // Add event handler
  $tabs.find('.ui-tabs-next, .ui-tabs-prev').click(function() {
    if ($.ui.version == '1.8.7') {
      $tabs.tabs('select', parseInt($(this).attr("rel")));
    }
    else {
      $tabs.tabs('option', 'active', parseInt($(this).attr("rel")));
    }
    return false;
  });
}

/**
 * Scroll to an accordion's active element.
 */
Drupal.jQueryUiFilter.tabsScrollTo = function(tabs) {
  var options = $(tabs).data('options') || {}
  if (!options['scrollTo']) {
    return;
  }

  var top = $(tabs).offset().top;
  if (options['scrollTo']['duration']) {
    $('html, body').animate({scrollTop: top}, options['scrollTo']['duration']);
  }
  else {
    $('html, body').scrollTop(top);
  }
}


/**
 * Tabs select event handler to bookmark selected tab in location.hash.
 */
Drupal.jQueryUiFilter.tabsSelect = function(event, ui) {
  location.hash = $(ui.tab).attr('href');
}

/**
 * On hash change select tab.
 *
 * Inspired by: http://benalman.com/code/projects/jquery-bbq/examples/fragment-jquery-ui-tabs/
 */
Drupal.jQueryUiFilter.tabsHashChangeEvent = function() {
  var $tab = $('.ui-tabs-nav > li:has(a[href="' + location.hash + '"])');
  $tabs = $tab.parent().parent();

  var selected = $tab.prevAll().length;

  if ($.ui.version == '1.8.7') {
    if ($tabs.tabs('option', 'selected') != selected) {
      $tabs.tabs('select', selected);
    }
  }
  else {
    if ($tabs.tabs('option', 'active') != selected) {
      $tabs.tabs('option', 'active', selected);
    }
  }
}

/**
 * jQuery UI filter tabs behavior
 */
Drupal.behaviors.jQueryUiFilterTabs = {attach: function(context) {
  if (Drupal.settings.jQueryUiFilter.disabled) {
    return;
  }

  var headerTag = Drupal.settings.jQueryUiFilter.tabsHeaderTag;

  // Tabs
  $('div.jquery-ui-filter-tabs', context).once('jquery-ui-filter-tabs', function () {
    var options = Drupal.jQueryUiFilter.getOptions('tabs');

    // Get <h*> text and add to tabs.
    // Sets selected tab based on location.hash.
    var scrollTo = false;
    var index = 0;
    var tabs = '<ul>';
    $(this).find(headerTag + '.jquery-ui-filter-tabs-header').each(function(){
      var id = this.id || $(this).text().toLowerCase().replace(/[^-a-z0-9]+/gm, '-');
      var hash = '#' + id;

      if (hash == location.hash) {
        scrollTo = true;
        options['selected'] = index;
      }
      index++;

      tabs += '<li><a href="' + hash + '">' + $(this).html() + '</a></li>';
      $(this).next('div.jquery-ui-filter-tabs-container').attr('id', id);
      $(this).remove();
    });
    tabs += '</ul>';
    $(this).prepend(tabs);

    // DEBUG:
    // console.log(options);

    // Save options as data and init tabs
    $(this).data('options', options).tabs(options);

    // Equal height tab
    $(this).find('.ui-tabs-nav li').equalHeight();

    // Add paging.
    if (options['paging']) {
      Drupal.jQueryUiFilter.tabsPaging(this, options);
    }

    // Bind tabs select event to record history
    if (options['history']) {
      $(this).bind('tabsselect', Drupal.jQueryUiFilter.tabsSelect);
    }

    // Scroll to selected tabs widget
    if (scrollTo) {
      Drupal.jQueryUiFilter.tabsScrollTo(this);
    }

    // Init hash change event handling once
    if (!Drupal.jQueryUiFilter.hashChangeInit) {
      Drupal.jQueryUiFilter.hashChange(Drupal.jQueryUiFilter.tabsHashChangeEvent);
    }
    Drupal.jQueryUiFilter.hashChangeInit = true;
  });
}}

})(jQuery);
