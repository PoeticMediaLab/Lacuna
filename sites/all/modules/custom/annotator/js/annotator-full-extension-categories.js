/*

From Zhila: Plugin that creates and stores the categories field by hooking into the existing Annotator class.

Original coffeescript file at: https://github.com/LacunaStories/Annotation-Studio/blob/master/lib/assets/javascripts/categories.js.coffee.

One deleted function from original file because it was trying to run undefined values and getting errors. Fixed the code but removed this function: categoriesWithAnnotation()

Code below relies on using variables set in annotator_categories.js.
*/

(function($) {
  var _ref,
  __bind = function(fn, me){ return function(){ return fn.apply(me, arguments); }; },
  __hasProp = {}.hasOwnProperty,
  __extends = function(child, parent) { for (var key in parent) { if (__hasProp.call(parent, key)) child[key] = parent[key]; } function ctor() { this.constructor = child; } ctor.prototype = parent.prototype; child.prototype = new ctor(); child.__super__ = parent.prototype; return child; };

  Annotator.Plugin.Categories = (function(_super) {
    __extends(Categories, _super);

    //Creates a space in the annotation window that says "Categories"
    Categories.prototype.html = {
      element: "<li class=\"annotator-categories\">\n<h4>" + Annotator._t('Categories') + "</h4>\n<br clear=\"all\">\n</li>"
    };

    //Not sure what this does. I think it holds different variables related to the annotations.
    Categories.prototype.options = {
      categories: [],
      categorizeAnnotations: {},
      originalAnnotations: {},
      classForSelectedCategory: "selected"
    };

    //I think this maps a jQuery event to a function, but not totally sure.
    Categories.prototype.events = {
      '.annotator-category click': "toggleSelectedCategory",
      'annotationEditorSubmit': "stringifyCategorizeAnnotation",
      'annotationEditorShown': "parseCategorizeAnnotatonsFromText",
      '.annotator-cancel click': "loadOriginalAnnotations"
    };

    //Sets default values
    Categories.prototype.field = null;
    Categories.prototype.input = null;

    //Pulls the categories variable (which is set in annotator_categories.js) and creates a separate div for each category.
    Categories.prototype.categoriesHtml = function() {
      var categories, string;
      categories = this.options.categories;
      string = $.map(categories, function(category) {
        return "<div class='annotator-category'>" + category.name + "</div>";
      }).join(' ');
      return string;
    };

    //Initializes the plugin and creates the HTML element to add to the Annotator widget.
    Categories.prototype.pluginInit = function() {
      var element;

      //Creates HTML element and appends Categories before the annotation text area.
      element = $(this.html.element);
      element.find('h4').after(this.categoriesHtml());
      this.element.find('.annotator-listing .annotator-item:first-child').before(element);

      //Adds the field and returns a view of the annotation.
      return this.annotator.viewer.addField({
        load: this.updateViewer
      });
    };

    //Not sure what this does. Some kind of starter function.
    function Categories(element, categories) {
      Categories.__super__.constructor.call(this, element, categories);
      if (categories) {
        this.options.categories = categories;
      }
    }

    //Sets and removes a special class for the Category buttons, on click. Only one button can be clicked at a time.
    Categories.prototype.setSelectedCategory = function(currentCategory) {
      this.element.find('.annotator-category').removeClass(this.options.classForSelectedCategory);
      return $(currentCategory).addClass(this.options.classForSelectedCategory);
    };

    //More category toggling settings.
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

    //Not sure what this does.
    Categories.prototype.categoriesWrapperDom = function() {
      return this.element.find('.annotator-categories');
    };

    //More category selectors.
    Categories.prototype.selectedCategory = function() {
      return this.element.find('.annotator-category.' + this.options.classForSelectedCategory);
    };

    //Gets input for first category.
    Categories.prototype.setAnnotationForFirstCategory = function() {
      this.element.find('.annotator-category').removeClass(this.options.classForSelectedCategory);
      this.element.find('.annotator-category:first').addClass(this.options.classForSelectedCategory);
      this.annotationField().val(this.getTextForCategory(this.element.find('.annotator-category:first').html()));
      return this.element.find('.annotator-category:first').trigger('click');
    };

    //Not sure what this does. Maybe gets more input.
    Categories.prototype.annotationField = function() {
      return this.element.find("textarea:first");
    };

    /* On save, this.options.categorizeAnnotations[category] returns as undefined. One function was having errors but no other functions do, so keeping this in for now. */
    Categories.prototype.getTextForCategory = function(category) {
      return this.options.categorizeAnnotations[category] || '';
    };

    //
    Categories.prototype.setTextForCategory = function(category, annotation) {
      if ((annotation != null) && !/^\s*$/.test(annotation)) {
        return this.options.categorizeAnnotations[category] = annotation;
      }
    };

  /*
    Variables below:
        categorizeAnnotations = the object that holds the selected categories and comments
        annotation.text = DB field that holds user comments and selections.
            Example: annotation.text= {Comment":"What?","Question":"Why?"}
    This function was broken because it was always receiving undefined values.
    */
    Categories.prototype.stringifyCategorizeAnnotation = function(editor, annotation) {
      this.setTextForCategory(this.selectedCategory().html(), this.annotationField().val());

    // If categorizeAnnotations is not empty (has items in it), set annotation.text.
    if ($.isEmptyObject(this.options.categorizeAnnotations) === false) {
      return annotation.text = JSON.stringify(this.options.categorizeAnnotations);
    } else {
      return annotation.text = '';
    }
  };

  //Converts annotation to JSON
  Categories.prototype.parseCategorizeAnnotatonsFromText = function(editor, annotation) {
    this.options.categorizeAnnotations = {};
    this.options.originalAnnotations = {};
    if (annotation.text) {
      this.options.categorizeAnnotations = JSON.parse(annotation.text);
      this.options.originalAnnotations = this.options.categorizeAnnotations;
    }
    this.setAnnotationForFirstCategory();
    return this.fixEditorDimension();
  };

  //Loads original annotation
  Categories.prototype.loadOriginalAnnotations = function() {
    this.options.categorizeAnnotations = this.options.originalAnnotations;
    return this.setAnnotationForFirstCategory();
  };

  //Adjusts dimensions of editor window-- default in AnnotatorJS is too small.
  Categories.prototype.fixEditorDimension = function() {
    var categoriesWidth, dom;
    dom = this.categoriesWrapperDom();
    categoriesWidth = $.map(dom.find('.annotator-category'), function(category) {
      return parseInt($(category).css('width')) + parseInt($(category).css('padding-left')) + parseInt($(category).css('padding-right')) + parseInt($(category).css('margin-left')) + parseInt($(category).css('margin-right'));
    }).reduce(function(x, y) {
      return x + y;
    });
    categoriesWidth += parseInt(dom.css('padding-left')) + parseInt(dom.css('padding-right')) + 18;
    if (dom.width() < categoriesWidth) {
      return dom.width(categoriesWidth);
    }
  };

  //Updates the page view after a new annotation is made and displays them on the page.
  Categories.prototype.updateViewer = function(filed, annotation) {
    var categories, categorizeText, viewerField;
    filed = $(filed).hide();
    if ((annotation.text != null) && annotation.text.length > 0) {
      categorizeText = JSON.parse(annotation.text);
      categories = Object.keys(categorizeText);
      viewerField = filed.parent("li.annotator-annotation").find("div:first").addClass("categories");
      viewerField.empty();
      return $.each(categories, function(i, category) {
        annotation = $('<div>').addClass('categorize-text').attr('id', category.replace(RegExp(" ", "g"), "_"));
        annotation.append($('<span>').addClass('text-category').html(category));
        annotation.append($('<span>').html(categorizeText[category]));
        return viewerField.append(annotation);
      });
    }
  };

  return Categories;

})(Annotator.Plugin);

})(jQuery);
