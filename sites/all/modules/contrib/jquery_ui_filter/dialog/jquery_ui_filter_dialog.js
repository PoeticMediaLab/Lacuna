(function ($) {

Drupal.jQueryUiFilter = Drupal.jQueryUiFilter || {}
Drupal.jQueryUiFilter.dialogOptions = Drupal.jQueryUiFilter.dialogOptions || {closeText : 'close'}

// Set default dialog query parameter.
var match = /dialogFeatures=([^&]+)/.exec(location.search);
Drupal.jQueryUiFilter.dialogOptions.dialogFeatures = ((match) ? match[1] : {});

/**
 * Reload page with uuid to insure cache is cleared
 */
Drupal.jQueryUiFilter.dialogReloadPage = function() {
  top.location.href = top.location.pathname +
    ((top.location.search) ? top.location.search + '&' : '?') +
    'no-cache=' + ((new Date().getTime()) * Math.random(10));

  // Close dialog so that the user sees something has happened.
  $('#jquery-ui-filter-dialog').dialog('destroy');
}

/**
 * Convert dialogFeatures array to string.
 */
Drupal.jQueryUiFilter.dialogFeaturesToString = function(dialogFeatures) {
  if (typeof dialogFeatures == 'string') {
    return dialogFeatures;
  }

  dialogFeatures['protocol'] = location.protocol.replace(':', '');

  var features = [];
  for(var name in dialogFeatures) {
    features[features.length] = name + '=' + dialogFeatures[name];
  }
  return features.join(',');
}

/**
 * Append to dialogFeatures to URL query string via '?dialogFeatures=1' or '?dialogFeatures=form-onsubmit_close=1'.
 */
Drupal.jQueryUiFilter.dialogFeaturesAppendToURL = function(url, dialogFeatures) {
  if (url.indexOf('dialogFeatures') !== -1) {
    return url;
  }

  dialogFeatures = dialogFeatures || Drupal.jQueryUiFilter.dialogOptions.dialogFeatures;
  dialogFeatures = Drupal.jQueryUiFilter.dialogFeaturesToString(dialogFeatures);

  var query = ((url.indexOf('?') === -1) ? '?' : '&') + 'dialogFeatures=' + dialogFeatures;
  if (url.indexOf('#') !== -1) {
    return url.replace('#', query + '#');
  }
  else {
    return url + query;
  }
}

/**
 * Open jQuery UI filter dialog. Allows other modules to re-use this functionality.
 */
Drupal.jQueryUiFilter.dialogOpen = function(url, options) {
  // Check url against whitelist
  if (url.indexOf('://') !== -1) {
    var domain = url.match(/:\/\/(.[^/]+)/)[1];
    var whitelist = Drupal.settings.jQueryUiFilter.dialogWhitelist.split(/\s+/);
    whitelist[whitelist.length] = location.hostname; // Always add custom host
    if (jQuery.inArray(domain, whitelist) == -1) {
      window.location = url;
      return;
    }
  }

  // Initialize options with dialogFeatures.
  options = jQuery.extend(
    {dialogFeatures: {}},
    $.ui.dialog.prototype.options,
    options
  );

  // Destroy dialog when it is closed.
  options['close'] = function(event, ui) {
    $(this).dialog('destroy').remove();
  }

  // Automatically adjust iframe height based on window settings.
  var windowHeight = $(window).height() - 50;
  var windowWidth = $(window).width() - 50;
  if (options['height'] == 'auto') {
    options['height'] = options['maxHeight'] || windowHeight;
  }
  if (options['width'] == 'auto') {
    options['width'] = options['maxWidth'] || windowWidth;
  }

  // Make sure dialog is not larger then the viewport.
  if (options['height'] > windowHeight) {
    options['height'] = windowHeight;
  }
  if (options['width'] > windowWidth) {
    options['width'] = windowWidth;
  }

  // Add close button to dialog
  if (options['closeButton']) {
    options['buttons'][ Drupal.t(options['closeText'] || 'Close') ] = function() {
      $(this).dialog('close');
    }
  }
  delete options['closeButton'];

  // Set iframe scrolling attribute.
  options['scrolling'] = options['scrolling'] || 'auto';

  // Set dialog URL with ?dialogFeature= parameters.
  url = Drupal.jQueryUiFilter.dialogFeaturesAppendToURL(url, options['dialogFeatures']);

  // Remove existing dialog and iframe, this allows us to reset the
  // dialog's options and allow dialogs to open external domains.
  $('#jquery-ui-filter-dialog').dialog('destroy').remove();

  // Create iframe
  $('body').append('<div id="jquery-ui-filter-dialog">'
    + '<div id="jquery-ui-filter-dialog-container">'
    + '<iframe id="jquery-ui-filter-dialog-iframe" name="jquery-ui-filter-dialog-iframe" width="100%" height="100%" marginWidth="0" marginHeight="0" frameBorder="0" scrolling="' + options['scrolling'] + '" src="' + url + '" />'
    + '</div>'
    + '</div>'
  );

  // Open dialog
  $('#jquery-ui-filter-dialog').dialog(options);

  // DEBUG:
  // console.log(options);
}

/**
 * jQuery UI filter dialog behavior
 */
Drupal.behaviors.jQueryUiFilterDialog = {attach: function(context) {
  if (Drupal.settings.jQueryUiFilter.disabled) {
    return;
  }

  // Append ?jquery_ui_filter_dialog=1 to all link and form action inside a dialog iframe with dialogFeatures.
  if ((top != self) && (self.location.search.indexOf('dialogFeatures') !== -1)) {
    $('a', context).once('jquery-ui-filter-dialog-link', function() {
      if (this.tagName == 'A') {
        this.href = Drupal.jQueryUiFilter.dialogFeaturesAppendToURL(this.href);
      }
      else if (this.tagName == 'FORM') {
        this.action = Drupal.jQueryUiFilter.dialogFeaturesAppendToURL(this.action);
      }
    });

    // Do not allow dialogs to be nested inside of dialogs.
    return;
  }

  $('a.jquery-ui-filter-dialog', context).once('jquery-ui-filter-dialog', function () {
    $(this).click(function() {
      // Get hidden JSON string that has been cleaned up on the server using PHP.
      // See _jquery_ui_filter_dialog_process_replacer().
      var json  = $(this).attr('rel');
      if (json) {
        var options = Drupal.jQueryUiFilter.getOptions('dialog', JSON.parse(unescape(json)));
      }
      else {
        var options = Drupal.jQueryUiFilter.getOptions('dialog', {});
      }
      // Customize dialog using the link's title.
      if ($(this).attr('title')) {
        options['title'] = $(this).attr('title');
      }

      Drupal.jQueryUiFilter.dialogOpen(this.href, options);
      return false;
    });
  });
}}

})(jQuery);
