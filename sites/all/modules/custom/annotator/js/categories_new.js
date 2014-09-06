(function($) {
  var __hasProp = Object.prototype.hasOwnProperty,
    __extends = function(child, parent) { for (var key in parent) { if (__hasProp.call(parent, key)) child[key] = parent[key]; } function ctor() { this.constructor = child; } ctor.prototype = parent.prototype; child.prototype = new ctor; child.__super__ = parent.prototype; return child; };

  Annotator.Plugin.Categories = (function(_super) {

    __extends(Categories, _super);

    Categories.prototype.html = {
      element: "<li class=\"annotator-categories\">\n<h4>" + Annotator._t('Categories') + "</h4>\n<br clear=\"all\">\n</li>"
    };

    Categories.prototype.options = {
      categories: [],
      classForSelectedCategory: "selected",
      categoryClass: "annotator-category"
    };

    Categories.prototype.events = {
      '.annotator-category click': "changeSelectedCategory",
      'annotationEditorSubmit': "saveCategory",
      'annotationEditorShown': "selectCategory",
      'annotationViewerShown': "viewCategory"
    };

    Categories.prototype.field = null;

    Categories.prototype.input = null;

    Categories.prototype.pluginInit = function() {
      if (!Annotator.supported()) return;
      this.field = this.annotator.editor.addField({
        label: Annotator._t('Category'),
        load: this.updateField,
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
      if (options.categories) this.options.categories = options.categories;
    }

    Categories.prototype.annotationField = function() {
      return this.element.find("textarea:first");
    };

    Categories.prototype.selectedCategory = function() {
      return this.element.find('.annotator-category-' + this.options.classForSelectedCategory);
    };

    Categories.prototype.setSelectedCategory = function(currentCategory) {
      this.element.find('.annotator-category').removeClass(this.options.classForSelectedCategory);
      return $(currentCategory).addClass(this.options.classForSelectedCategory);
    };

    Categories.prototype.updateViewer = function(field, annotation) {
      field = $(field);
      field.addClass(this.options.categoryClass).html('CATEGORY');
      if (annotation.category && annotation.category.length) {
        return field.addClass(this.options.categoryClass).html(function() {
          return annotation.category;
        });
      }
    };

    Categories.prototype.updateField = function(field, annotation) {
      if (this.categories) {
        console.log(this.categories, 'updateField @categories');
        return this.input.val(this.categories.join(" "));
      }
    };

    Categories.prototype.changeSelectedCategory = function(event) {};

    Categories.prototype.saveCategory = function(event) {};

    Categories.prototype.selectCategory = function(event) {
      var annotation, categoryHTML;
      annotation = event.annotation;
      categoryHTML = "";
      $.each(this.options.categories, function(i, category) {
        categoryHTML += '<span class="CLASS">';
        categoryHTML += category.name;
        return categoryHTML += '</span>';
      });
      categoryHTML = categoryHTML.replace(/CLASS/g, this.options.categoryClass);
      $(this.field).html(categoryHTML);
      if (!(annotation.category != null)) {
        annotation.category = this.options.categories[0].name;
      }
      return this.setSelectedCategory(annotation.category);
    };

    Categories.prototype.viewCategory = function(event) {};

    return Categories;

  })(Annotator.Plugin);

})(jQuery);
