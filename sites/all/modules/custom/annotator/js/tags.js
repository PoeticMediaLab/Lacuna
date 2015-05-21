(function() {
  var $,
    __bind = function(fn, me){ return function(){ return fn.apply(me, arguments); }; },
    __hasProp = Object.prototype.hasOwnProperty,
    __extends = function(child, parent) { for (var key in parent) { if (__hasProp.call(parent, key)) child[key] = parent[key]; } function ctor() { this.constructor = child; } ctor.prototype = parent.prototype; child.prototype = new ctor; child.__super__ = parent.prototype; return child; },
    __indexOf = Array.prototype.indexOf || function(item) { for (var i = 0, l = this.length; i < l; i++) { if (i in this && this[i] === item) return i; } return -1; };

  $ = jQuery;

  Annotator.Plugin.Tags = (function(_super) {

    __extends(Tags, _super);

    function Tags() {
      this.updateAutocompleteTags = __bind(this.updateAutocompleteTags, this);
      this.setAnnotationTags = __bind(this.setAnnotationTags, this);
      this.updateField = __bind(this.updateField, this);
      Tags.__super__.constructor.apply(this, arguments);
    }

    Tags.prototype.options = {
      parseTags: function(string) {
        var tags;
        string = $.trim(string);
        tags = [];
        if (string) tags = string.split(/,/);
        return tags;
      },
      stringifyTags: function(array) {
        return array.join(",");
      }
    };

    Tags.prototype.events = {
      'annotationEditorSubmit': "updateAutocompleteTags"
    };

    Tags.prototype.field = null;

    Tags.prototype.input = null;

    Tags.prototype.pluginInit = function() {
      if (!Annotator.supported()) return;
      this.field = this.annotator.editor.addField({
        label: Annotator._t('Add tags here, separate with commas') + '\u2026',
        load: this.updateField,
        submit: this.setAnnotationTags
      });
      this.annotator.viewer.addField({
        load: this.updateViewer
      });
      if (this.annotator.plugins.Filter) {
        this.annotator.plugins.Filter.addFilter({
          label: Annotator._t('Tag'),
          property: 'tags',
          isFiltered: Tags.filterCallback
        });
      }
      return this.input = $(this.field).find(':input');
    };

    Tags.prototype.parseTags = function(string) {
      return this.options.parseTags(string);
    };

    Tags.prototype.stringifyTags = function(array) {
      return this.options.stringifyTags(array);
    };

    Tags.prototype.updateField = function(field, annotation) {
      var value;
      value = '';
      if (annotation.tags) value = this.stringifyTags(annotation.tags);
      return this.input.val(value);
    };

    Tags.prototype.setAnnotationTags = function(field, annotation) {
      return annotation.tags = this.parseTags(this.input.val());
    };

    Tags.prototype.updateAutocompleteTags = function(event, annotation) {
      var tag, tags, _i, _len, _ref;
      tags = Drupal.settings.annotator_tags;
      _ref = annotation.tags;
      for (_i = 0, _len = _ref.length; _i < _len; _i++) {
        tag = _ref[_i];
        if (__indexOf.call(tags, tag) < 0) tags.push(tag);
      }
      return this.input.catcomplete({
        source: tags
      });
    };

    Tags.prototype.updateViewer = function(field, annotation) {
      field = $(field);
      if (annotation.tags && $.isArray(annotation.tags) && annotation.tags.length) {
        return field.addClass('annotator-tags').html(function() {
          var string;
          return string = $.map(annotation.tags, function(tag) {
            return '<span class="annotator-tag">' + Annotator.Util.escape(tag) + '</span>';
          }).join(' ');
        });
      } else {
        return field.remove();
      }
    };

    return Tags;

  })(Annotator.Plugin);

  Annotator.Plugin.Tags.filterCallback = function(input, tags) {
    var keyword, keywords, matches, tag, _i, _j, _len, _len2;
    if (tags == null) tags = [];
    matches = 0;
    keywords = [];
    if (input) {
      keywords = input.split(/,/g);
      for (_i = 0, _len = keywords.length; _i < _len; _i++) {
        keyword = keywords[_i];
        if (tags.length) {
          for (_j = 0, _len2 = tags.length; _j < _len2; _j++) {
            tag = tags[_j];
            if (tag.indexOf(keyword) !== -1) matches += 1;
          }
        }
      }
    }
    return matches === keywords.length;
  };

}).call(this);
