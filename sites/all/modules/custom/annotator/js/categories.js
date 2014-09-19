(function($) {
  var __hasProp = Object.prototype.hasOwnProperty,
    __extends = function(child, parent) { for (var key in parent) { if (__hasProp.call(parent, key)) child[key] = parent[key]; } function ctor() { this.constructor = child; } ctor.prototype = parent.prototype; child.prototype = new ctor; child.__super__ = parent.prototype; return child; },
    __indexOf = Array.prototype.indexOf || function(item) { for (var i = 0, l = this.length; i < l; i++) { if (i in this && this[i] === item) return i; } return -1; };

  Annotator.Plugin.Categories = (function(_super) {

    __extends(Categories, _super);

    Categories.prototype.options = {
      categories: [],
      categoryColorClasses: {},
      categoryClass: "annotator-category",
      classForSelectedCategory: "annotator-category-selected",
      emptyCategory: "Highlight",
      annotatorHighlight: 'span.annotator-hl'
    };

    Categories.prototype.events = {
      '.annotator-category click': "changeSelectedCategory",
      'annotationEditorSubmit': "saveCategory",
      'annotationEditorShown': "highlightSelectedCategory",
      'annotationsLoaded': 'changeHighlightColors'
    };

    Categories.prototype.field = null;

    Categories.prototype.input = null;

    Categories.prototype.pluginInit = function() {
      if (!Annotator.supported()) return;
      this.options.categoryColorClasses[this.options.emptyCategory] = this.options.categoryClass + '-none';
      this.field = this.annotator.editor.addField({
        label: Annotator._t('Category'),
        options: this.options
      });
      this.annotator.viewer.addField({
        load: this.updateViewer,
        options: this.options
      });
      return this.input = $(this.field).find(':input');
    };

    function Categories(element, options) {
      Categories.__super__.constructor.call(this, element, options);
      this.element = element;
    }

    Categories.prototype.changeHighlightColors = function(annotations) {
      var annotation, category, cssClass, highlight, i, _i, _j, _len, _len2, _ref, _results;
      i = 0;
      _ref = this.options.category;
      for (_i = 0, _len = _ref.length; _i < _len; _i++) {
        category = _ref[_i];
        cssClass = this.options.categoryClass + '-' + i;
        this.options.categoryColorClasses[category] = cssClass;
        i++;
      }
      _results = [];
      for (_j = 0, _len2 = annotations.length; _j < _len2; _j++) {
        annotation = annotations[_j];
        _results.push((function() {
          var _k, _len3, _ref2, _results2;
          _ref2 = annotation.highlights;
          _results2 = [];
          for (_k = 0, _len3 = _ref2.length; _k < _len3; _k++) {
            highlight = _ref2[_k];
            _results2.push($(highlight).addClass(this.options.categoryColorClasses[annotation.category]));
          }
          return _results2;
        }).call(this));
      }
      return _results;
    };

    Categories.prototype.setSelectedCategory = function(currentCategory) {
      $(this.field).find('.annotator-category').removeClass(this.options.classForSelectedCategory);
      return $(this.field).find('.annotator-category:contains(' + currentCategory + ')').addClass(this.options.classForSelectedCategory);
    };

    Categories.prototype.updateViewer = function(field, annotation) {
      var _ref;
      field = $(field);
      field.addClass(this.options.categoryClass).html(this.options.emptyCategory);
      if ((annotation.category != null) && annotation.category.length > 0) {
        field.addClass(this.options.categoryClass).html(annotation.category);
        if (_ref = annotation.category, __indexOf.call(this.options.category, _ref) >= 0) {
          return field.addClass(this.options.categoryColorClasses[annotation.category]);
        }
      }
    };

    Categories.prototype.changeSelectedCategory = function(event) {
      var category;
      category = $(event.target).html();
      return this.setSelectedCategory(category);
    };

    Categories.prototype.saveCategory = function(event, annotation) {
      annotation.category = $(this.field).find('.' + this.options.classForSelectedCategory).html();
      if ((annotation.text != null) && annotation.text.length > 0 && !(annotation.category != null)) {
        window.alert('You did not choose a category, so the default has been chosen.');
        annotation.category = this.options.category[0];
      }
      if (!(annotation.category != null)) {
        annotation.category = this.options.emptyCategory;
      }
      return this.changeHighlightColors([annotation]);
    };

    Categories.prototype.highlightSelectedCategory = function(event, annotation) {
      var category, categoryHTML, _i, _len, _ref;
      if (!(annotation.category != null)) {
        annotation.category = this.options.emptyCategory;
      }
      categoryHTML = "";
      _ref = this.options.category;
      for (_i = 0, _len = _ref.length; _i < _len; _i++) {
        category = _ref[_i];
        categoryHTML += '<span class="' + this.options.categoryClass;
        categoryHTML += ' ' + this.options.categoryColorClasses[category] + '">';
        categoryHTML += category;
        categoryHTML += '</span>';
      }
      $(this.field).html(categoryHTML);
      return this.setSelectedCategory(annotation.category);
    };

    return Categories;

  })(Annotator.Plugin);

})(jQuery);
