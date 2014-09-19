(function($) {
  var __bind = function(fn, me){ return function(){ return fn.apply(me, arguments); }; },
    __hasProp = Object.prototype.hasOwnProperty,
    __extends = function(child, parent) { for (var key in parent) { if (__hasProp.call(parent, key)) child[key] = parent[key]; } function ctor() { this.constructor = child; } ctor.prototype = parent.prototype; child.prototype = new ctor; child.__super__ = parent.prototype; return child; },
    __indexOf = Array.prototype.indexOf || function(item) { for (var i = 0, l = this.length; i < l; i++) { if (i in this && this[i] === item) return i; } return -1; };

  Annotator.Plugin.Filters = (function(_super) {

    __extends(Filters, _super);

    Filters.prototype.events = {
      'annotationsLoaded': 'setup',
      '.annotator-sidebar-filter click': 'changeFilterState',
      'annotationCreated': 'addAnnotation',
      'annotationUpdated': 'addAnnotation'
    };

    Filters.prototype.options = {
      filters: {},
      current_user: null,
      selector: {
        sidebar: '#annotation-filters',
        annotation: 'annotation-',
        activeFilters: '#activeFilters'
      },
      "class": {
        hiddenAnnotation: 'annotation-filters-hide-annotation',
        button: 'annotation-sidebar-button',
        activeButton: 'annotation-sidebar-button-active',
        input: 'annotation-filter-input',
        activeFilter: 'annotation-filter-active',
        closeIcon: 'fa fa-times',
        filterTitle: 'annotation-filters-title'
      }
    };

    Filters.prototype.data = {
      annotations: {},
      filterValues: {},
      activeFilters: {},
      filtered: {}
    };

    function Filters(element, options) {
      this.removeFilterClick = __bind(this.removeFilterClick, this);
      this.buttonClick = __bind(this.buttonClick, this);      Filters.__super__.constructor.apply(this, arguments);
      if (options.current_user != null) {
        this.options.current_user = options.current_user;
      }
      if (options.selector != null) {
        if (this.options.selector.sidebar != null) {
          this.options.selector.sidebar = options.selector.sidebar;
        }
      }
      if (options.filters != null) this.options.filters = options.filters;
    }

    Filters.prototype.pluginInit = function() {
      var _this = this;
      return this.annotator.subscribe("annotationViewerShown", function(Viewer) {
        return _this.filterViewer(Viewer);
      });
    };

    Filters.prototype.setup = function(annotations) {
      var annotation, _i, _len;
      for (_i = 0, _len = annotations.length; _i < _len; _i++) {
        annotation = annotations[_i];
        this.data.annotations[annotation.id] = annotation;
        this.storeFilterValues(annotation);
        this.addAnnotationID(annotation);
      }
      return this.drawFilters();
    };

    Filters.prototype.addAnnotationID = function(annotation) {
      var annotationHighlight, highlight, _i, _len, _ref, _results;
      _ref = annotation.highlights;
      _results = [];
      for (_i = 0, _len = _ref.length; _i < _len; _i++) {
        highlight = _ref[_i];
        _results.push(annotationHighlight = $(highlight).addClass(this.options.selector.annotation + annotation.id));
      }
      return _results;
    };

    Filters.prototype.addAnnotation = function(annotation) {
      this.data.annotations[annotation.id] = annotation;
      this.addAnnotationID(annotation);
      return this.storeFilterValues(annotation);
    };

    Filters.prototype.getValue = function(annotation, key) {
      switch (key) {
        case 'user':
          return annotation[key]['name'];
        default:
          return annotation[key];
      }
    };

    Filters.prototype.storeFilterValues = function(annotation) {
      var filterName, tag, user, _i, _len, _ref, _ref2, _results;
      if (this.options.filters != null) {
        _ref = this.options.filters;
        _results = [];
        for (_i = 0, _len = _ref.length; _i < _len; _i++) {
          filterName = _ref[_i];
          if (!(this.data.filterValues[filterName] != null)) {
            this.data.filterValues[filterName] = [];
          }
          if (!(this.data.filtered[filterName] != null)) {
            this.data.activeFilters[filterName] = [];
            this.data.filtered[filterName] = [];
          }
          switch (filterName) {
            case 'tags':
              if (!(annotation[filterName] != null)) break;
              _results.push((function() {
                var _j, _len2, _ref2, _results2;
                _ref2 = annotation[filterName];
                _results2 = [];
                for (_j = 0, _len2 = _ref2.length; _j < _len2; _j++) {
                  tag = _ref2[_j];
                  if (__indexOf.call(this.data.filterValues[filterName], tag) < 0) {
                    _results2.push(this.data.filterValues[filterName].push(tag));
                  } else {
                    _results2.push(void 0);
                  }
                }
                return _results2;
              }).call(this));
              break;
            case 'user':
              user = this.getValue(annotation, 'user');
              if (__indexOf.call(this.data.filterValues[filterName], user) < 0) {
                _results.push(this.data.filterValues[filterName].push(user));
              } else {
                _results.push(void 0);
              }
              break;
            default:
              if ((annotation[filterName] != null) && (_ref2 = annotation[filterName], __indexOf.call(this.data.filterValues[filterName], _ref2) < 0)) {
                _results.push(this.data.filterValues[filterName].push(annotation[filterName]));
              } else {
                _results.push(void 0);
              }
          }
        }
        return _results;
      }
    };

    Filters.prototype.filterViewer = function(Viewer) {
      var annotation, filter, _i, _len, _ref, _results;
      _ref = Viewer.annotations;
      _results = [];
      for (_i = 0, _len = _ref.length; _i < _len; _i++) {
        annotation = _ref[_i];
        _results.push((function() {
          var _ref2, _results2;
          _results2 = [];
          for (filter in this.data.activeFilters) {
            if (_ref2 = annotation.id, __indexOf.call(this.data.filtered[filter], _ref2) >= 0) {
              _results2.push(Viewer.hide());
            } else {
              _results2.push(void 0);
            }
          }
          return _results2;
        }).call(this));
      }
      return _results;
    };

    Filters.prototype.buttonClick = function(event) {
      var buttonType;
      buttonType = $(event.target).attr('id');
      if (buttonType === 'own-annotations') {
        return this.filterAnnotations(this.options.current_user, 'user');
      } else if (buttonType === 'all-annotations') {
        return this.removeFilter('user');
      } else if (buttonType === 'remove-filters') {
        return this.removeAllFilters();
      }
    };

    Filters.prototype.hideFilteredAnnotations = function() {
      var annotationID, filter, id, _results;
      _results = [];
      for (annotationID in this.data.annotations) {
        _results.push((function() {
          var _i, _len, _ref, _results2;
          _ref = this.options.filters;
          _results2 = [];
          for (_i = 0, _len = _ref.length; _i < _len; _i++) {
            filter = _ref[_i];
            _results2.push((function() {
              var _j, _len2, _ref2, _results3;
              _ref2 = this.data.filtered[filter];
              _results3 = [];
              for (_j = 0, _len2 = _ref2.length; _j < _len2; _j++) {
                id = _ref2[_j];
                if (annotationID === id) {
                  $('.' + this.options.selector.annotation + id).addClass(this.options["class"].hiddenAnnotation);
                  this.publish('hide', this.data.annotations[annotationID]);
                  break;
                } else {
                  _results3.push(void 0);
                }
              }
              return _results3;
            }).call(this));
          }
          return _results2;
        }).call(this));
      }
      return _results;
    };

    Filters.prototype.filterSelected = function(event, ui) {
      var filterName, matchValue;
      matchValue = ui.item.value;
      filterName = event.target.name;
      this.filterAnnotations(matchValue, filterName);
      $(event.target).val('');
      return false;
    };

    Filters.prototype.filterAnnotations = function(matchValue, filterName) {
      var classes, id, value;
      for (id in this.data.annotations) {
        value = this.getValue(this.data.annotations[id], filterName);
        if (value instanceof Array) {
          if (__indexOf.call(value, matchValue) < 0) {
            this.data.filtered[filterName].push(id);
          }
        } else if (value !== matchValue) {
          this.data.filtered[filterName].push(id);
        }
      }
      this.data.activeFilters[filterName].push(matchValue);
      classes = [filterName, this.options["class"].activeFilter, this.options["class"].closeIcon].join(' ');
      $(this.options.selector.activeFilters).append($('<div>', {
        id: matchValue,
        "class": classes
      }).text(filterName + ': ' + matchValue).on("click", this.removeFilterClick));
      return this.hideFilteredAnnotations();
    };

    Filters.prototype.removeFilterClick = function(event) {
      var filterName, filterValue, item, _i, _len, _ref, _results;
      item = $(event.target);
      filterValue = item.attr('id');
      _ref = this.options.filters;
      _results = [];
      for (_i = 0, _len = _ref.length; _i < _len; _i++) {
        filterName = _ref[_i];
        if (item.hasClass(filterName)) {
          _results.push(this.removeFilter(filterName));
        } else {
          _results.push(void 0);
        }
      }
      return _results;
    };

    Filters.prototype.removeFilter = function(filterName) {
      var id, _i, _len, _ref;
      _ref = this.data.filtered[filterName];
      for (_i = 0, _len = _ref.length; _i < _len; _i++) {
        id = _ref[_i];
        this.showAnnotation(this.data.annotations[id]);
      }
      this.data.filtered[filterName] = [];
      return $('.' + filterName + '.' + this.options["class"].activeFilter).remove();
    };

    Filters.prototype.showAnnotation = function(annotation) {
      return $('.' + this.options.selector.annotation + annotation.id).removeClass(this.options["class"].hiddenAnnotation);
    };

    Filters.prototype.removeAllFilters = function() {
      var filter;
      for (filter in this.data.filtered) {
        this.data.filtered[filter] = [];
      }
      $('.' + this.options["class"].hiddenAnnotation).removeClass(this.options["class"].hiddenAnnotation);
      return $('.' + this.options["class"].activeFilter).remove();
    };

    Filters.prototype.makeButton = function(id, text) {
      var sidebar;
      sidebar = $(this.options.selector.sidebar);
      return sidebar.append($('<span>', {
        id: id,
        "class": this.options["class"].button
      }).text(text).on("click", this.buttonClick));
    };

    Filters.prototype.drawFilters = function() {
      var filter, inputHTML, sidebar, values, _ref,
        _this = this;
      sidebar = $(this.options.selector.sidebar);
      sidebar.append('<h2>Annotation Filters</h2>');
      this.makeButton('own-annotations', 'My Annotations');
      this.makeButton('all-annotations', "Everyone's Annotations");
      this.makeButton('remove-filters', 'Remove All Filters');
      _ref = this.data.filterValues;
      for (filter in _ref) {
        values = _ref[filter];
        inputHTML = "<label>" + filter + ": </label><input name='" + filter + "' class='" + this.options["class"].input + "' />";
        sidebar.append(inputHTML);
        $("input[name=" + filter + "]").autocomplete({
          source: values,
          select: function(event, ui) {
            return _this.filterSelected(event, ui);
          }
        });
      }
      return sidebar.append("<div id='activeFilters'></div>");
    };

    return Filters;

  })(Annotator.Plugin);

})(jQuery);
