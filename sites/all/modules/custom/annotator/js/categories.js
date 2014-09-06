(function() {
  var __hasProp = Object.prototype.hasOwnProperty,
    __extends = function(child, parent) { for (var key in parent) { if (__hasProp.call(parent, key)) child[key] = parent[key]; } function ctor() { this.constructor = child; } ctor.prototype = parent.prototype; child.prototype = new ctor; child.__super__ = parent.prototype; return child; };

  Annotator.Plugin.Categories = (function(_super) {

    __extends(Categories, _super);

    Categories.prototype.html = {
      element: "<li class=\"annotator-categories\">\n<h4>" + Annotator._t('Categories') + "</h4>\n<br clear=\"all\">\n</li>"
    };

    Categories.prototype.options = {
      categories: [],
      categorizeAnnotations: {},
      originalAnnotations: {},
      classForSelectedCategory: "selected"
    };

    Categories.prototype.events = {
      '.annotator-category click': "toggleSelectedCategory",
      'annotationEditorSubmit': "stringifyCategorizeAnnotation",
      'annotationEditorShown': "parseCategorizeAnnotatonsFromText",
      '.annotator-cancel click': "loadOriginalAnnotations"
    };

    Categories.prototype.field = null;

    Categories.prototype.input = null;

    Categories.prototype.categoriesHtml = function() {
      var categories, string;
      categories = this.options.categories;
      string = $.map(categories, function(category) {
        return "<div class='annotator-category'>" + category.name + "</div>";
      }).join(' ');
      return string;
    };

    Categories.prototype.pluginInit = function() {
      var element;
      element = $(this.html.element);
      element.find('h4').after(this.categoriesHtml());
      this.element.find('.annotator-listing .annotator-item:first-child').after(element);
      return this.annotator.viewer.addField({
        load: this.updateViewer,
        categories: this.options.categories
      });
    };

    function Categories(element, categories) {
      Categories.__super__.constructor.call(this, element, categories);
      if (categories) this.options.categories = categories;
    }

    Categories.prototype.setSelectedCategory = function(currentCategory) {
      this.element.find('.annotator-category').removeClass(this.options.classForSelectedCategory);
      return $(currentCategory).addClass(this.options.classForSelectedCategory);
    };

    Categories.prototype.toggleSelectedCategory = function(event) {
      var category, text;
      this.setTextForCategory(this.selectedCategory().html(), this.annotationField().val());
      category = $(event.target).html();
      text = this.getTextForCategory(category);
      this.annotationField().val(text);
      this.setSelectedCategory(event.target);
      this.annotationField().focus();
      return this.annotator.publish('annotatorSelectedCategoryChanged', [category]);
    };

    Categories.prototype.categoriesWrapperDom = function() {
      return this.element.find('.annotator-categories');
    };

    Categories.prototype.selectedCategory = function() {
      return this.element.find('.annotator-category.' + this.options.classForSelectedCategory);
    };

    Categories.prototype.setAnnotationForFirstCategory = function() {
      this.element.find('.annotator-category').removeClass(this.options.classForSelectedCategory);
      this.element.find('.annotator-category:first').addClass(this.options.classForSelectedCategory);
      this.annotationField().val(this.getTextForCategory(this.element.find('.annotator-category:first').html()));
      return this.element.find('.annotator-category:first').trigger('click');
    };

    Categories.prototype.annotationField = function() {
      return this.element.find("textarea:first");
    };

    Categories.prototype.getTextForCategory = function(category) {
      return this.options.categorizeAnnotations[category] || '';
    };

    Categories.prototype.setTextForCategory = function(category, annotation) {
      if ((annotation != null) && !/^\s*$/.test(annotation)) {
        return this.options.categorizeAnnotations[category] = annotation;
      }
    };

    Categories.prototype.stringifyCategorizeAnnotation = function(editor, annotation) {};

    Categories.prototype.parseCategorizeAnnotatonsFromText = function(editor, annotation) {
      this.setAnnotationForFirstCategory();
      return this.fixEditorDimension();
    };

    Categories.prototype.categoriesWithAnnotation = function() {
      var categories, that;
      categories = [];
      that = this;
      $.each(this.options.categories, function(i, category) {
        if (that.getTextForCategory(category).length > 0) {
          return categories.push(category);
        }
      });
      return categories;
    };

    Categories.prototype.loadOriginalAnnotations = function() {
      this.options.categorizeAnnotations = this.options.originalAnnotations;
      return this.setAnnotationForFirstCategory();
    };

    Categories.prototype.fixEditorDimension = function() {
      var categoriesWidth, dom;
      dom = this.categoriesWrapperDom();
      categoriesWidth = $.map(dom.find('.annotator-category'), function(category) {
        return parseInt($(category).css('width')) + parseInt($(category).css('padding-left')) + parseInt($(category).css('padding-right')) + parseInt($(category).css('margin-left')) + parseInt($(category).css('margin-right'));
      }).reduce(function(x, y) {
        return x + y;
      });
      categoriesWidth += parseInt(dom.css('padding-left')) + parseInt(dom.css('padding-right')) + 18;
      if (dom.width() < categoriesWidth) return dom.width(categoriesWidth);
    };

    Categories.prototype.updateViewer = function(field, annotation) {
      var category, viewerField;
      field = $(field).hide();
      if ((annotation.text != null) && annotation.text.length > 0) {
        category = annotation.category;
        viewerField = field.parent("li.annotator-annotation").find("div:first").addClass("categories");
        viewerField.empty();
        return $.each(this.categories, function(i, category) {
          annotation = $('<div>').addClass('categorize-text').attr('id', category.replace(RegExp(" ", "g"), "_"));
          annotation.append($('<span>').addClass('text-category').html(category.name));
          return viewerField.append(annotation);
        });
      }
    };

    return Categories;

  })(Annotator.Plugin);

}).call(this);
