(function() {
  var $, Model, View, select,
    __bind = function(fn, me){ return function(){ return fn.apply(me, arguments); }; },
    __hasProp = Object.prototype.hasOwnProperty,
    __extends = function(child, parent) { for (var key in parent) { if (__hasProp.call(parent, key)) child[key] = parent[key]; } function ctor() { this.constructor = child; } ctor.prototype = parent.prototype; child.prototype = new ctor; child.__super__ = parent.prototype; return child; },
    __indexOf = Array.prototype.indexOf || function(item) { for (var i = 0, l = this.length; i < l; i++) { if (i in this && this[i] === item) return i; } return -1; };

  $ = jQuery;

  select = {
    'interface': '#annotation-filters',
    'annotation': 'annotation-',
    'hide': 'af-annotation-hide',
    'filters': {
      'default': 'af-filter',
      'active': 'af-filter-active',
      'delete': 'fa fa-trash'
    },
    'pager': {
      'default': 'af-pager',
      'wrapper': 'af-pager-wrapper',
      'count': 'af-pager-count',
      'arrow': 'af-pager-arrow',
      'first': 'fa fa-angle-double-left',
      'prev': 'fa fa-angle-left',
      'next': 'fa fa-angle-right',
      'last': 'fa fa-angle-double-right'
    },
    'button': {
      'default': 'af-button',
      'reset': 'af-button-reset',
      'active': 'af-button-active',
      'user': 'af-button-user',
      'none': 'af-button-none',
      'all': 'af-button-all',
      'mine': 'af-button-mine'
    },
    'autocomplete': {
      'default': 'af-autocomplete',
      'wrapper': 'af-autocomplete-wrapper',
      'label': 'af-autocomplete-label'
    },
    'checkbox': {
      'default': 'af-checkbox',
      'highlights': 'af-checkbox-highlights'
    }
  };

  Annotator.Plugin.Filters = (function(_super) {

    __extends(Filters, _super);

    Filters.prototype.events = {
      'annotationsLoaded': 'setup',
      '.annotation-filter click': 'filterSelect'
    };

    function Filters(element, options) {
      this.pagerClick = __bind(this.pagerClick, this);
      this.removeFilterClick = __bind(this.removeFilterClick, this);
      this.checkboxToggle = __bind(this.checkboxToggle, this);
      this.buttonClick = __bind(this.buttonClick, this);
      this.filterSelected = __bind(this.filterSelected, this);
      var filter, _i, _len, _ref;
      Filters.__super__.constructor.apply(this, arguments);
      this.Model = new Model;
      this.View = new View;
      if (options.current_user != null) {
        this.Model.set('currentUser', options.current_user);
      }
      if (options.filters != null) {
        _ref = options.filters;
        for (_i = 0, _len = _ref.length; _i < _len; _i++) {
          filter = _ref[_i];
          this.Model.registerFilter(filter);
        }
      }
    }

    Filters.prototype.pluginInit = function() {
      var _this = this;
      this.annotator.subscribe("annotationViewerShown", function(Viewer) {
        return _this.View.viewerShown(Viewer);
      });
      this.annotator.subscribe("annotationCreated", function(annotation) {
        return _this.Model.addAnnotation(annotation);
      });
      this.annotator.subscribe("annotationUpdated", function(annotation) {
        return _this.Model.updateAnnotation(annotation);
      });
    };

    Filters.prototype.setup = function(annotations) {
      var annotation, highlight, _i, _j, _len, _len2, _ref;
      this.Model.setup(annotations);
      this.View.setup(this, this.Model);
      for (_i = 0, _len = annotations.length; _i < _len; _i++) {
        annotation = annotations[_i];
        _ref = annotation.highlights;
        for (_j = 0, _len2 = _ref.length; _j < _len2; _j++) {
          highlight = _ref[_j];
          $(highlight).first().attr('id', select.annotation + annotation.id);
          $(highlight).addClass(select.annotation + annotation.id);
        }
      }
      this.Model.filterAnnotations('user', this.Model.get('currentUser'));
      this.View.drawFilter('user', this.Model.get('currentUser'));
      this.View.drawActiveButton(select.button.mine);
      return this.View.drawAnnotations();
    };

    Filters.prototype.filterSelected = function(event, ui) {
      var filter, value;
      filter = event.target.name;
      value = ui.item.value;
      if (!this.Model.filterIsActive(filter, value)) {
        if (filter === 'category') this.View.checkboxDisable('highlights');
        this.Model.filterAnnotations(filter, value);
        this.View.drawAnnotations();
        this.View.drawFilter(filter, value);
        this.View.scrollTo(this.Model.annotation());
      }
      $(event.target).val('');
      return false;
    };

    Filters.prototype.buttonClick = function(event) {
      var active, previous, type;
      type = $(event.target).attr('id');
      active = $(event.target);
      previous = $('.' + select.button.active);
      if (previous.attr('id') === active.attr('id')) return;
      this.Model.removeFilter('user');
      this.Model.removeFilter('none');
      if (type === select.button.mine) {
        this.Model.filterAnnotations('user', this.Model.get('currentUser'));
        this.View.drawFilter('user', this.Model.get('currentUser'));
      } else if (type === select.button.all) {
        this.View.eraseFilter('user', this.Model.get('currentUser'));
      } else if (type === select.button.none) {
        this.Model.filterAnnotations('none', 'none');
        this.View.eraseAllFilters();
      } else if (type === select.button.reset) {
        this.Model.removeAllFilters();
        this.View.eraseAllFilters();
        this.View.checkboxCheck('highlights');
        this.View.checkboxEnable('highlights');
        this.Model.filterAnnotations('user', this.Model.get('currentUser'));
        this.View.drawFilter('user', this.Model.get('currentUser'));
        type = select.button.mine;
      }
      this.View.drawActiveButton(type);
      this.View.drawAnnotations();
    };

    Filters.prototype.checkboxToggle = function(event) {
      if (event.target.name === 'highlights') {
        if (this.Model.toggleHighlights()) {
          this.View.drawAnnotations();
        } else {
          this.View.drawAnnotations();
        }
      }
    };

    Filters.prototype.removeFilterClick = function(event) {
      var id, value;
      id = event.target.id;
      value = event.target.dataset.value;
      this.View.eraseFilter(id, value);
      this.Model.removeFilter(id, value);
      return this.View.drawAnnotations();
    };

    Filters.prototype.pagerClick = function(event) {
      var index, total;
      index = this.Model.get('index');
      total = this.Model.get('total');
      switch (event.target.id) {
        case 'first':
          index = 1;
          break;
        case 'prev':
          --index;
          if (index < 1) index = total;
          break;
        case 'next':
          ++index;
          if (index > total) index = 1;
          break;
        case 'last':
          index = total;
      }
      this.Model.set('index', index);
      this.View.drawPagerCount();
      return this.View.scrollTo(this.Model.annotation());
    };

    return Filters;

  })(Annotator.Plugin);

  Model = (function() {

    function Model() {}

    Model.prototype.state = {
      highlights: true,
      ids: {
        all: [],
        highlights: [],
        hidden: [],
        shown: []
      },
      annotations: [],
      total: 0,
      index: 0,
      currentUser: null,
      filters: {}
    };

    Model.prototype.setup = function(annotations) {
      var annotation, filter, tag, _i, _len, _results;
      this.state.annotations = annotations;
      this.state.total = annotations.length;
      if (this.state.total) this.state.index = 1;
      _results = [];
      for (_i = 0, _len = annotations.length; _i < _len; _i++) {
        annotation = annotations[_i];
        this.state.ids.all.push(annotation.id);
        if (annotation.category.toLowerCase() === 'highlight') {
          this.state.ids.highlights.push(annotation.id);
        }
        _results.push((function() {
          var _results2;
          _results2 = [];
          for (filter in this.state.filters) {
            if (annotation[filter] != null) {
              switch (filter) {
                case 'user':
                  _results2.push(this.addFilterValue(filter, annotation['user'].name));
                  break;
                case 'tags':
                  _results2.push((function() {
                    var _j, _len2, _ref, _results3;
                    _ref = annotation.tags;
                    _results3 = [];
                    for (_j = 0, _len2 = _ref.length; _j < _len2; _j++) {
                      tag = _ref[_j];
                      _results3.push(this.addFilterValue(filter, tag));
                    }
                    return _results3;
                  }).call(this));
                  break;
                default:
                  _results2.push(this.addFilterValue(filter, annotation[filter]));
              }
            } else {
              _results2.push(void 0);
            }
          }
          return _results2;
        }).call(this));
      }
      return _results;
    };

    Model.prototype.get = function(attr) {
      return this.state[attr];
    };

    Model.prototype.set = function(attr, value) {
      return this.state[attr] = value;
    };

    Model.prototype.currentID = function() {
      return this.state.ids.shown[this.state.index - 1];
    };

    Model.prototype.annotation = function(id) {
      var annotation, _i, _len, _ref;
      if (id == null) id = null;
      if (!(id != null)) id = this.currentID();
      _ref = this.state.annotations;
      for (_i = 0, _len = _ref.length; _i < _len; _i++) {
        annotation = _ref[_i];
        if (annotation.id === id) return annotation;
      }
    };

    Model.prototype.toggleHighlights = function() {
      var id, _i, _len, _ref;
      this.state.highlights = !this.state.highlights;
      if (this.state.highlights) {
        this.removeFilter('highlights', 'highlights');
      } else {
        this.activateFilter('highlights', 'highlights');
        _ref = this.state.ids.highlights;
        for (_i = 0, _len = _ref.length; _i < _len; _i++) {
          id = _ref[_i];
          this.addToFilter('highlights', 'highlights', id);
        }
      }
      this.computeFilters();
      return this.state.highlights;
    };

    Model.prototype.addFilterValue = function(filter, value) {
      if (__indexOf.call(this.state.filters[filter].values, value) < 0) {
        return this.state.filters[filter].values.push(value);
      }
    };

    Model.prototype.registerFilter = function(filter) {
      this.state.filters[filter] = {};
      this.state.filters[filter].values = [];
      this.state.filters[filter].active = {};
    };

    Model.prototype.activateFilter = function(filter, value) {
      if (!(filter in this.state.filters)) this.registerFilter(filter);
      if (!(value in this.state.filters[filter].active)) {
        return this.state.filters[filter].active[value] = [];
      }
    };

    Model.prototype.filterIsActive = function(filter, value) {
      return value in this.state.filters[filter].active;
    };

    Model.prototype.getFilterValues = function() {
      var filter, ret;
      ret = {};
      for (filter in this.state.filters) {
        ret[filter] = this.state.filters[filter].values;
      }
      return ret;
    };

    Model.prototype.getHidden = function() {
      return this.state.ids.hidden;
    };

    Model.prototype.getShown = function() {
      return this.state.ids.shown;
    };

    Model.prototype.removeAllFilters = function() {
      var filter, value, _results;
      _results = [];
      for (filter in this.state.filters) {
        _results.push((function() {
          var _results2;
          _results2 = [];
          for (value in this.state.filters[filter].active) {
            _results2.push(this.removeFilter(filter, value));
          }
          return _results2;
        }).call(this));
      }
      return _results;
    };

    Model.prototype.removeFilter = function(filter, value) {
      if (filter in this.state.filters) {
        if (value in this.state.filters[filter].active) {
          delete this.state.filters[filter].active[value];
        } else {
          this.state.filters[filter].active = {};
        }
        return this.computeFilters();
      }
    };

    Model.prototype._intersect = function(a, b) {
      var item, result, _i, _len;
      result = [];
      if (!b.length) return a;
      if (!a.length) return b;
      for (_i = 0, _len = a.length; _i < _len; _i++) {
        item = a[_i];
        if (__indexOf.call(b, item) >= 0) result.push(item);
      }
      return result;
    };

    Model.prototype.intersection = function(arrays) {
      var arr, result, _i, _len;
      result = [];
      if (arrays.length === 0) return result;
      if (arrays.length === 1) return arrays.pop();
      for (_i = 0, _len = arrays.length; _i < _len; _i++) {
        arr = arrays[_i];
        result = this._intersect(result, arr);
      }
      return result;
    };

    Model.prototype.union = function(arrays) {
      var arr, item, result, _i, _j, _len, _len2;
      result = [];
      for (_i = 0, _len = arrays.length; _i < _len; _i++) {
        arr = arrays[_i];
        for (_j = 0, _len2 = arr.length; _j < _len2; _j++) {
          item = arr[_j];
          if (__indexOf.call(result, item) < 0) result.push(item);
        }
      }
      return result;
    };

    Model.prototype.computeFilters = function() {
      var arrays, filter, id, ids, value, _i, _len, _ref;
      this.state.ids.hidden = [];
      this.state.ids.shown = [];
      ids = [];
      arrays = [];
      for (filter in this.state.filters) {
        for (value in this.state.filters[filter].active) {
          if (this.state.filters[filter].active[value].length) {
            arrays.push(this.state.filters[filter].active[value]);
          }
        }
        ids.push(this.intersection(arrays));
      }
      this.state.ids.hidden = this.union(ids);
      _ref = this.state.ids.all;
      for (_i = 0, _len = _ref.length; _i < _len; _i++) {
        id = _ref[_i];
        if (__indexOf.call(this.state.ids.hidden, id) < 0) {
          this.state.ids.shown.push(id);
        }
      }
      this.state.total = this.state.ids.shown.length;
      this.state.index = 0;
      if (this.state.total) return this.state.index = 1;
    };

    Model.prototype.addToFilter = function(filter, value, id) {
      if (!(this.state.filters[filter].active[value] != null)) {
        this.state.filters[filter].active[value] = [];
      }
      return this.state.filters[filter].active[value].push(id);
    };

    Model.prototype.removeFromFilter = function(filter, value, id) {
      var i;
      i = this.state.filters[filter].active[value].indexOf(id);
      return this.state.filters[filter].active[value].splice(i, 1);
    };

    Model.prototype.filterAnnotations = function(filter, value) {
      var annotation, currentValue, _i, _j, _len, _len2, _ref, _ref2;
      this.activateFilter(filter, value);
      if (filter === 'none') {
        _ref = this.state.annotations;
        for (_i = 0, _len = _ref.length; _i < _len; _i++) {
          annotation = _ref[_i];
          this.addToFilter(filter, filter, annotation.id);
        }
      } else {
        _ref2 = this.state.annotations;
        for (_j = 0, _len2 = _ref2.length; _j < _len2; _j++) {
          annotation = _ref2[_j];
          if (filter === 'user') {
            currentValue = annotation[filter].name;
          } else {
            currentValue = annotation[filter];
          }
          if (!currentValue) currentValue = '';
          if (currentValue instanceof Array) {
            if (__indexOf.call(currentValue, value) < 0) {
              this.addToFilter(filter, value, annotation.id);
            }
          } else if (currentValue !== value) {
            this.addToFilter(filter, value, annotation.id);
          }
        }
      }
      return this.computeFilters();
    };

    return Model;

  })();

  /* View methods
  */

  View = (function() {

    function View() {
      this.viewerShown = __bind(this.viewerShown, this);
      this.setup = __bind(this.setup, this);
    }

    View.prototype.setup = function(Controller, Model) {
      var filter, values, _ref;
      this.viewer = new Annotator.Viewer();
      this.i = $(select.interface);
      this.Controller = Controller;
      this.Model = Model;
      this.i.append('<h2>Annotation Filters</h2>');
      this.drawPager(this.Model.get('index'), this.Model.get('total'));
      this.i.append("<div id='" + select.button["default"] + "'></div>");
      this.drawButton(select.button["default"], 'none', 'user');
      this.drawButton(select.button["default"], 'mine', 'user');
      this.drawButton(select.button["default"], 'all', 'user');
      this.drawCheckbox('highlights', 'Show Highlights');
      _ref = this.Model.getFilterValues();
      for (filter in _ref) {
        values = _ref[filter];
        this.drawAutocomplete(filter, values);
      }
      this.i.append("<div id='" + select.button.reset + "'></div>");
      this.drawButton(select.button.reset, 'reset', 'reset');
      this.i.append("<div id='" + select.filters.active + "'>Active Filters</div>");
    };

    View.prototype.update = function() {};

    View.prototype.drawButton = function(loc, id, filter) {
      var classes;
      classes = [select.button["default"], select.button[id], select.button[filter]].join(' ');
      return $('#' + loc).append($('<span>', {
        id: select.button[id],
        "class": classes
      }).text(id).on('click', this.Controller.buttonClick));
    };

    View.prototype.drawActiveButton = function(id) {
      $('.' + select.button.active).removeClass(select.button.active);
      $('#' + id).addClass(select.button.active);
    };

    View.prototype.checkboxStateChange = function(id, attr, state) {
      return $("input[name='" + id + "'").attr(attr, state);
    };

    View.prototype.checkboxCheck = function(id) {
      return this.checkboxStateChange(id, 'checked', true);
    };

    View.prototype.checkboxUncheck = function(id) {
      return this.checkboxStateChange(id, 'checked', false);
    };

    View.prototype.checkboxEnable = function(id) {
      return this.checkboxStateChange(id, 'disabled', false);
    };

    View.prototype.checkboxDisable = function(id) {
      return this.checkboxStateChange(id, 'disabled', true);
    };

    View.prototype.drawCheckbox = function(id, value) {
      var classes;
      classes = [select.checkbox["default"], select.checkbox[id]].join(' ');
      return $(select.interface).append($("<input type='checkbox' name='" + id + "' checked>", {
        name: id
      }).on("click", this.Controller.checkboxToggle)).append("<span id='" + id + "' class='" + classes + "'>" + value + "</span>");
    };

    View.prototype.drawAutocomplete = function(id, values) {
      var html,
        _this = this;
      html = "<div class='" + select.autocomplete["default"] + "'><label class='" + select.autocomplete.label + "' for='" + id + "'>" + id + ": </label><input name='" + id + "' class='" + select.autocomplete["default"] + " " + select.autocomplete["default"] + "-" + id + "' /></div>";
      this.i.append(html);
      $("input[name=" + id + "]").autocomplete({
        source: values,
        select: function(event, ui) {
          return _this.Controller.filterSelected(event, ui);
        }
      });
    };

    View.prototype.drawPager = function(first, last) {
      var p;
      p = select.pager;
      this.i.append($("<i id='first' class='" + p["default"] + " " + p.arrow + " " + p.first + "'/>")).on("click", 'i#first', this.Controller.pagerClick);
      this.i.append($("<i id='prev' class='" + p["default"] + " " + p.arrow + " " + p.prev + "'/>")).on("click", 'i#prev', this.Controller.pagerClick);
      this.i.append($("<span id='" + p.count + "' class='" + p["default"] + "'>").text(first + ' of ' + last));
      this.i.append($("<i id='next' class='" + p["default"] + " " + p.arrow + " " + p.next + "'/>")).on("click", 'i#next', this.Controller.pagerClick);
      this.i.append($("<i id='last' class='" + p["default"] + " " + p.arrow + " " + p.last + "'/>")).on("click", 'i#last', this.Controller.pagerClick);
      $('.' + p["default"]).wrapAll("<div id='" + p.wrapper + "'></div>");
    };

    View.prototype.drawPagerCount = function() {
      return $('#' + select.pager.count).text(this.Model.get('index') + ' of ' + this.Model.get('total'));
    };

    View.prototype.drawFilter = function(id, value) {
      var classes;
      if (!value) value = '';
      classes = [select.filters["default"], select.filters.active, select.filters["delete"], select.filters[id]].join(' ');
      return $('#' + select.filters.active).after($('<div>', {
        id: id,
        "class": classes,
        'data-value': value
      }).text(' ' + id + ': ' + value).on("click", this.Controller.removeFilterClick));
    };

    View.prototype.eraseAllFilters = function() {
      return $('.' + select.filters.active).remove();
    };

    View.prototype.eraseFilter = function(id, value) {
      $('#' + id + '.' + select.filters.active + ("[data-value='" + value + "'")).remove();
      if (id === 'user') {
        $('.' + select.button.active + '.' + select.button.user).removeClass(select.button.active);
      }
      if (id === 'category') return this.checkboxEnable('highlights');
    };

    View.prototype.showAnnotations = function(ids) {
      var id, _i, _len;
      for (_i = 0, _len = ids.length; _i < _len; _i++) {
        id = ids[_i];
        $('.' + select.annotation + id).removeClass(select.hide);
      }
      return this.drawPagerCount();
    };

    View.prototype.hideAnnotations = function(ids) {
      var id, _i, _len;
      for (_i = 0, _len = ids.length; _i < _len; _i++) {
        id = ids[_i];
        $('.' + select.annotation + id).addClass(select.hide);
      }
      return this.drawPagerCount();
    };

    View.prototype.drawAnnotations = function() {
      this.showAnnotations(this.Model.getShown());
      return this.hideAnnotations(this.Model.getHidden());
    };

    View.prototype.viewerShown = function(Viewer) {};

    View.prototype.scrollTo = function(annotation) {
      var highlight;
      highlight = $(annotation.highlights[0]);
      $("html, body").animate({
        scrollTop: highlight.offset().top - 300
      }, 150);
      return $(Drupal.settings.annotator.element).annotator().annotator('showViewer', [annotation], highlight.position());
    };

    return View;

  })();

}).call(this);
