(function() {
  var $, Model, View, select,
    __bind = function(fn, me){ return function(){ return fn.apply(me, arguments); }; },
    __hasProp = Object.prototype.hasOwnProperty,
    __extends = function(child, parent) { for (var key in parent) { if (__hasProp.call(parent, key)) child[key] = parent[key]; } function ctor() { this.constructor = child; } ctor.prototype = parent.prototype; child.prototype = new ctor; child.__super__ = parent.prototype; return child; },
    __indexOf = Array.prototype.indexOf || function(item) { for (var i = 0, l = this.length; i < l; i++) { if (i in this && this[i] === item) return i; } return -1; };

  $ = jQuery;

  select = {
    'interface': {
      'setup': 'section.region-sidebar-second',
      'wrapper': 'annotation-filters-wrapper',
      'filters': 'annotation-filters'
    },
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
      'controls': 'af-pager-controls',
      'count': 'af-pager-count',
      'arrow': 'af-pager-arrow',
      'first': 'fa fa-angle-double-left fa-lg',
      'prev': 'fa fa-angle-left fa-lg',
      'next': 'fa fa-angle-right fa-lg',
      'last': 'fa fa-angle-double-right fa-lg'
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
      '.annotation-filter click': 'filterSelect',
      '.annotation-filter tap': 'filterSelect'
    };

    function Filters(element, options) {
      this.pagerClick = __bind(this.pagerClick, this);
      this.removeFilterClick = __bind(this.removeFilterClick, this);
      this.checkboxToggle = __bind(this.checkboxToggle, this);
      this.buttonClick = __bind(this.buttonClick, this);
      this.filterSelected = __bind(this.filterSelected, this);
      var filter, item, pair, query, _i, _j, _len, _len2, _ref, _ref2;
      Filters.__super__.constructor.apply(this, arguments);
      if (window.location.search) {
        query = window.location.search.substring(1);
        _ref = query.split('&');
        for (_i = 0, _len = _ref.length; _i < _len; _i++) {
          item = _ref[_i];
          pair = item.split('=');
          if (pair[0] === 'id') this.scrollToID = pair[1];
        }
      }
      this.Model = new Model;
      this.View = new View;
      this.View.element = element;
      if (options.current_user != null) {
        this.Model.set('currentUser', options.current_user);
      }
      if (options.filters != null) {
        _ref2 = options.filters;
        for (_j = 0, _len2 = _ref2.length; _j < _len2; _j++) {
          filter = _ref2[_j];
          this.Model.registerFilter(filter);
        }
      }
    }

    Filters.prototype.pluginInit = function() {
      var _this = this;
      this.annotator.subscribe("annotationViewerShown", function(Viewer) {
        return _this.View.viewerShown(Viewer);
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
          $(highlight).addClass(select.annotation + annotation.id);
        }
      }
      if (this.scrollToID != null) {
        this.View.scrollTo(this.Model.annotation(this.scrollToID));
      } else {
        this.Model.filterAnnotations('user', this.Model.get('currentUser'));
        this.View.drawFilter('user', this.Model.get('currentUser'));
        this.View.drawActiveButton(select.button.mine);
      }
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
        this.View.eraseFilter('user');
        this.Model.filterAnnotations('user', this.Model.get('currentUser'));
        this.View.drawFilter('user', this.Model.get('currentUser'));
      } else if (type === select.button.all) {
        this.View.eraseFilter('user');
      } else if (type === select.button.none) {
        this.Model.removeAllFilters();
        this.Model.filterAnnotations('none', 'none');
        this.View.eraseAllFilters();
        this.View.drawFilter('user', 'None');
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
      return null;
    };

    Filters.prototype.checkboxToggle = function(event) {
      if (event.target.name === 'highlights') {
        this.Model.toggleHighlights();
        this.View.drawAnnotations();
      }
    };

    Filters.prototype.removeFilterClick = function(event) {
      var id, value;
      id = event.target.id;
      value = event.target.dataset.value;
      this.View.eraseFilter(id, value);
      this.Model.removeFilter(id, value);
      if (id === 'category' && !this.Model.filterIsActive('category')) {
        this.View.checkboxEnable('highlights');
      }
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
      $(document).trigger('annotation-filters-paged', this.Model.annotation());
      this.View.drawPagerCount();
      return this.View.scrollTo(this.Model.annotation());
    };

    return Filters;

  })(Annotator.Plugin);

  Model = (function() {

    function Model() {}

    Model.prototype.state = {
      showHighlights: true,
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
      annotations.sort(function(a, b) {
        var rangeA, rangeB;
        rangeA = document.createRange();
        if (a.highlights[0] != null) rangeA.selectNodeContents(a.highlights[0]);
        rangeB = document.createRange();
        if (b.highlights[0] != null) rangeB.selectNodeContents(b.highlights[0]);
        return rangeA.compareBoundaryPoints(Range.START_TO_START, rangeB);
      });
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
                      if (tag != null) {
                        _results3.push(this.addFilterValue(filter, tag));
                      } else {
                        _results3.push(void 0);
                      }
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

    Model.prototype.addAnnotation = function(annotation) {};

    Model.prototype.updateAnnotation = function(annotation) {};

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
      this.state.showHighlights = !this.state.showHighlights;
      if (this.state.showHighlights) {
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
      return this.state.showHighlights;
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
      if (!value) return Object.keys(this.state.filters[filter].active).length > 0;
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

    Model.prototype.dropHidden = function(annotations) {
      var annotation, shown, _i, _len, _ref;
      shown = [];
      for (_i = 0, _len = annotations.length; _i < _len; _i++) {
        annotation = annotations[_i];
        if (_ref = annotation.id, __indexOf.call(this.state.ids.hidden, _ref) < 0) {
          shown.push(annotation);
        }
      }
      return shown;
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

    Model.prototype.intersection = function(a, b) {
      var id, result, _i, _len;
      result = [];
      if (!b.length) return a;
      if (!a.length) return b;
      for (_i = 0, _len = a.length; _i < _len; _i++) {
        id = a[_i];
        if (__indexOf.call(b, id) >= 0) result.push(id);
      }
      return result;
    };

    Model.prototype.intersectAll = function(lists) {
      var list, result, _i, _len;
      result = [];
      if (!lists || lists.length === 0) {
        return result;
      } else {
        if (lists.length === 1) return lists[0];
      }
      for (_i = 0, _len = lists.length; _i < _len; _i++) {
        list = lists[_i];
        result = this.intersection(result, list);
      }
      return result;
    };

    Model.prototype.union = function(arrays) {
      var arr, id, result, _i, _j, _len, _len2;
      result = [];
      for (_i = 0, _len = arrays.length; _i < _len; _i++) {
        arr = arrays[_i];
        for (_j = 0, _len2 = arr.length; _j < _len2; _j++) {
          id = arr[_j];
          if (__indexOf.call(result, id) < 0) result.push(id);
        }
      }
      return result;
    };

    Model.prototype.computeFilters = function() {
      var arrays, filter, id, ids, value, _i, _len, _ref;
      this.state.ids.hidden = [];
      this.state.ids.shown = [];
      ids = [];
      for (filter in this.state.filters) {
        arrays = [];
        for (value in this.state.filters[filter].active) {
          if (this.state.filters[filter].active[value].length) {
            arrays.push(this.state.filters[filter].active[value]);
          }
        }
        ids.push(this.intersectAll(arrays));
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
      var filter, title, values, _ref;
      this.viewer = new Annotator.Viewer();
      $(select.interface.setup).append("<div id='" + select.interface.wrapper + "'><div id='" + select.interface.filters + "'></div></div>");
      this.i = $('#' + select.interface.wrapper);
      this.Controller = Controller;
      this.Model = Model;
      this.i.addClass('hidden');
      title = $('<h2>Show Annotations</h2>');
      title.click((function() {
        return this.i.toggleClass('hidden');
      }).bind(this));
      this.i.append(title);
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
      this.i.append("<div id='" + select.filters.active + "'>Showing Only</div>");
    };

    View.prototype.update = function() {};

    View.prototype.drawButton = function(loc, id, filter) {
      var classes;
      classes = [select.button["default"], select.button[id], select.button[filter]].join(' ');
      return $('#' + loc).append($('<span>', {
        id: select.button[id],
        "class": classes
      }).text(id).on('tap click', this.Controller.buttonClick));
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
      return $('#' + select.interface.wrapper).append($("<input type='checkbox' name='" + id + "' checked>", {
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
      this.i.append($("<i id='next' class='" + p["default"] + " " + p.arrow + " " + p.next + "'/>")).on("click", 'i#next', this.Controller.pagerClick);
      this.i.append($("<i id='last' class='" + p["default"] + " " + p.arrow + " " + p.last + "'/>")).on("click", 'i#last', this.Controller.pagerClick);
      this.i.append($("<span id='" + p.count + "' class='" + p["default"] + "'>").text(first + ' of ' + last));
      $('.' + p["default"]).wrapAll("<div id='" + p.wrapper + "'></div>");
      $('.' + p.arrow).wrapAll("<div id='" + p.controls + "'></div>");
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
      if (value != null) {
        $('#' + id + '.' + select.filters.active + '[data-value="' + value + '"]').remove();
      } else {
        $('#' + id + '.' + select.filters.active).remove();
      }
      if (id === 'user') {
        return $('.' + select.button.active + '.' + select.button.user).removeClass(select.button.active);
      }
    };

    View.prototype.showAnnotations = function(ids) {
      var id, _i, _len;
      for (_i = 0, _len = ids.length; _i < _len; _i++) {
        id = ids[_i];
        $('.' + select.annotation + id).removeClass(select.hide);
      }
      return $(document).trigger('annotation-filters-changed');
    };

    View.prototype.hideAnnotations = function(ids) {
      var id, _i, _len;
      for (_i = 0, _len = ids.length; _i < _len; _i++) {
        id = ids[_i];
        $('.' + select.annotation + id).addClass(select.hide);
      }
      return $(document).trigger('annotation-filters-changed');
    };

    View.prototype.drawAnnotations = function() {
      this.showAnnotations(this.Model.getShown());
      this.hideAnnotations(this.Model.getHidden());
      return this.drawPagerCount();
    };

    View.prototype.viewerShown = function(Viewer) {
      var annotations;
      Viewer.hide();
      annotations = this.Model.dropHidden(Viewer.annotations);
      if (annotations.length) {
        Viewer.load(annotations);
        return Viewer.show();
      }
    };

    View.prototype.getViewerPosition = function(annotation) {
      var pos, range;
      pos = $(annotation.highlights[0]).position();
      range = annotation.ranges[0].toObject();
      if (range.endOffset > range.startOffset) {
        pos.left += range.endOffset - range.startOffset;
      } else {
        pos.left += range.startOffset;
      }
      return pos;
    };

    View.prototype.scrollTo = function(annotation) {
      var highlight;
      if (!annotation) return;
      $(document).trigger('annotation-filters-paged', annotation);
      highlight = $(annotation.highlights[0]);
      $("html, body").animate({
        scrollTop: highlight.offset().top - 500
      }, 150);
      return $(this.element).annotator().annotator('showViewer', [annotation], this.getViewerPosition(annotation));
    };

    return View;

  })();

}).call(this);
