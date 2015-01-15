/**
 * @file
 * CKEditor plugin for linking to content by it's UUID.
 */

(function($) {

// Get a CKEDITOR.dialog.contentDefinition object by its ID.
var getById = function(array, id, recurse) {
  for (var i = 0, item; (item = array[i]); i++) {
    if (item.id == id) return item;
    if (recurse && item[recurse]) {
      var retval = getById(item[recurse], id, recurse);
      if (retval) return retval;
    }
  }
  return null;
};

var resetInitValues = function(dialog) {
  dialog.foreach(function(contentObj) {
    contentObj.setInitValue && contentObj.setInitValue();
  });
};

var initAutocomplete = function(input, uri) {
  input.setAttribute('autocomplete', 'OFF');
  return new Drupal.jsAC($(input), new Drupal.ACDB(uri));
};

var formatToken = function(type, value) {
  return '[uuid-link:' + type + ':' + value + ']';
};

var revertValue = function(value) {
  var parts = value.match(/\[uuid-link:([^:]+):([^:\]]+)\]/);
  if (parts && parts.length >= 2) {
    return {
      type: parts[1],
      uuid: parts[2]
    };
  }
  else {
    return false;
  }
};

var isUUIDLinkType = function(type) {
  for (var i in Drupal.settings.uuid_link.type_name) {
    if (i == type) {
      return true;
    }
  }
  return false;
};

CKEDITOR.plugins.add('uuid_link', {

  init: function(editor, pluginPath) {
    CKEDITOR.on('dialogDefinition', function(e) {
      if ((e.editor != editor) || (e.data.name != 'link') || !Drupal.settings.uuid_link) return;

      // Overrides definition.
      var definition = e.data.definition;
      definition.onFocus = CKEDITOR.tools.override(definition.onFocus, function(original) {
        return function() {
          original.call(this);
          if (isUUIDLinkType(this.getValueOf('info', 'linkType'))) {
            this.getContentElement('info', 'uuid_link').select();
          }
        };
      });

      definition.onOk = CKEDITOR.tools.override(definition.onOk, function(original) {
        return function() {
          var process = false;
          if (isUUIDLinkType(this.getValueOf('info', 'linkType')) && !this._.selectedElement) {
            var ranges = editor.getSelection().getRanges(true);
            if ((ranges.length == 1) && ranges[0].collapsed) {
              process = true;
            }
          }
          original.call(this);
          if (process) {
            var value = this.getValueOf('info', 'uuid_link');
            var index = value.lastIndexOf('(');
            if (index != -1) {
              var text = CKEDITOR.tools.trim(value.substr(0, index));
              if (text) {
                CKEDITOR.plugins.link.getSelectedLink(editor).setText(text);
              }
            }
          }
        };
      });

      // Overrides linkType definition.
      var infoTab = definition.getContents('info');
      var content = getById(infoTab.elements, 'linkType');
      var autocomplete = null;
      for (var i in Drupal.settings.uuid_link.type_name) {
        content.items.unshift(['Drupal: ' + Drupal.settings.uuid_link.type_name[i], i]);
      }

      infoTab.elements.push({
        type: 'vbox',
        id: 'drupalOptions',
        children: [{
          type: 'text',
          id: 'uuid_link',
          label: editor.lang.link.title,
          required: true,
          onLoad: function() {
            this.getInputElement().addClass('form-autocomplete');
            autocomplete = initAutocomplete(this.getInputElement().$, Drupal.settings.uuid_link.autocomplete_path);
          },
          setup: function(data) {
            this.setValue(data.uuid_link || '');
          },
          validate: function() {
            var dialog = this.getDialog();
            if (!isUUIDLinkType(dialog.getValueOf('info', 'linkType'))) {
              return true;
            }
            var func = CKEDITOR.dialog.validate.notEmpty(editor.lang.link.noUrl);
            if (!func.apply(this)) {
              return false;
            }
            // @todo: validate UUID.
            return true;
          }
        }]
      });

      content.onChange = CKEDITOR.tools.override(content.onChange, function(original) {
        return function() {
          original.call(this);
          var dialog = this.getDialog();
          var element = dialog.getContentElement('info', 'drupalOptions').getElement().getParent().getParent();
          if (isUUIDLinkType(this.getValue())) {
            element.show();
            if (editor.config.linkShowTargetTab) {
              dialog.showPage('target');
            }
            var uploadTab = dialog.definition.getContents('upload');
            if (uploadTab && !uploadTab.hidden) {
              dialog.hidePage('upload');
            }
            // Update autocomplete URL.
            autocomplete.db = new Drupal.ACDB(Drupal.settings.uuid_link.autocomplete_path + '/' + this.getValue());
          }
          else {
            element.hide();
          }
        };
      });

      content.setup = function(data) {
        if (!data.type || (data.type == 'url') && !data.url) {
          data.type = 'node';
        }
        else if (data.url && !data.url.protocol && data.url.url) {
          var dialog = this.getDialog();
          var values = revertValue(data.url.url);
          if (values) {
            data.type = values.type;
            data.uuid_link = values.uuid;
            delete data.url;
          }
          resetInitValues(dialog);
        }
        this.setValue(data.type);
        // Update autocomplete URL.
        autocomplete.db = new Drupal.ACDB(Drupal.settings.uuid_link.autocomplete_path + '/' + data.type);
      };

      content.commit = function(data) {
        var link_type = this.getValue();
        if (isUUIDLinkType(link_type)) {
          data.type = 'url';
          var dialog = this.getDialog();
          dialog.setValueOf('info', 'protocol', '');
          dialog.setValueOf('info', 'url', formatToken(link_type, dialog.getValueOf('info', 'uuid_link')));
        }
        else {
          // Set data.type as default commit callback does so other link types
          // work properly.
          data.type = link_type;
        }
      };
    });
  }

});

})(jQuery);
