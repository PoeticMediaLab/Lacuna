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
    'annotationUpdated': 'addAnnotation',
    'annotationViewerShown': 'updateCurrentIndex'
  };

  Filters.prototype.options = {
    filters: {},
    current_user: null,
    selector: {
      sidebar: '#annotation-filters',
      annotation: 'annotation-',
      activeFilters: 'active-filters',
      userButtons: 'annotation-filters-user-buttons'
    },
    "class": {
      hide: 'annotation-hide',
      button: 'annotation-filters-button',
      activeButton: 'annotation-filters-button-active',
      input: 'annotation-filter-input',
      activeFilter: 'annotation-filter-active',
      closeIcon: 'fa fa-trash',
      filterWrapper: 'annotation-filter-wrapper',
      filterLabel: 'annotation-filter-label',
      buttonType: {
        user: 'annotation-filter-button-user',
        reset: 'annotation-filter-button-reset'
      },
      checkboxType: {
        highlights: 'annotation-filter-checkbox-highlights'
      }
    }
  };

  Filters.prototype.data = {
    annotations: {},
    filterValues: {},
    activeFilters: {},
    filtered: {},
    currentIndex: 0,
    currentTotal: 0
  };

  function Filters(element, options) {
    this.buttonClick = __bind(this.buttonClick, this);
    this.checkboxToggle = __bind(this.checkboxToggle, this);
    this.pagerClick = __bind(this.pagerClick, this);
    this.removeFilterClick = __bind(this.removeFilterClick, this);    Filters.__super__.constructor.apply(this, arguments);
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
      ++this.data.currentTotal;
    }
    if (Object.keys(annotations).length) this.data.currentIndex = 1;
    return this.drawAllFilters();
  };

  Filters.prototype.addAnnotationID = function(annotation) {
    var highlight, _i, _len, _ref, _results;
    _ref = annotation.highlights;
    _results = [];
    for (_i = 0, _len = _ref.length; _i < _len; _i++) {
      highlight = _ref[_i];
      $(highlight).first().attr('id', this.options.selector.annotation + annotation.id);
      _results.push($(highlight).addClass(this.options.selector.annotation + annotation.id));
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

  Filters.prototype.filterAnnotations = function(filterName, matchValue, match) {
    var id, value;
    if (match == null) match = false;
    if (filterName === 'all') {
      this.data.filtered['all'] = (function() {
        var _results;
        _results = [];
        for (id in this.data.annotations) {
          _results.push(id);
        }
        return _results;
      }).call(this);
      this.hideFilteredAnnotations();
      this.data.currentTotal = 0;
      this.redrawPager();
      return;
    }
    if (this.data.activeFilters[filterName] != null) {
      this.data.activeFilters[filterName] = [];
      this.data.filtered[filterName] = [];
    }
    for (id in this.data.annotations) {
      value = this.getValue(this.data.annotations[id], filterName);
      if (!value) value = '';
      if (value instanceof Array) {
        if ((!match && __indexOf.call(value, matchValue) < 0) || (match && __indexOf.call(value, matchValue) >= 0)) {
          this.data.filtered[filterName].push(id);
          --this.data.currentTotal;
        }
      } else if ((!match && value !== matchValue) || (match && (value === matchValue))) {
        this.data.filtered[filterName].push(id);
        --this.data.currentTotal;
      }
    }
    if (!(this.data.activeFilters[filterName] != null)) {
      this.data.activeFilters[filterName] = [];
    }
    this.data.activeFilters[filterName].push(matchValue);
    this.hideFilteredAnnotations();
    return this.redrawPager();
  };

  Filters.prototype.filterViewer = function(Viewer) {
    var annotation, filter, _i, _len, _ref, _results;
    return;
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

  Filters.prototype.hideFilteredAnnotations = function() {
    var filter, id, _results;
    _results = [];
    for (filter in this.data.filtered) {
      _results.push((function() {
        var _i, _len, _ref, _results2;
        _ref = this.data.filtered[filter];
        _results2 = [];
        for (_i = 0, _len = _ref.length; _i < _len; _i++) {
          id = _ref[_i];
          $('.' + this.options.selector.annotation + id).addClass(this.options["class"].hide);
          _results2.push(this.publish('hide', this.data.annotations[id]));
        }
        return _results2;
      }).call(this));
    }
    return _results;
  };

  Filters.prototype.showAnnotation = function(annotation) {
    return $('.' + this.options.selector.annotation + annotation.id).removeClass(this.options["class"].hide);
  };

  Filters.prototype.removeAllFilters = function() {
    var filter, _results;
    _results = [];
    for (filter in this.data.filtered) {
      _results.push(this.removeFilter(filter));
    }
    return _results;
  };

  Filters.prototype.removeFilter = function(filterName) {
    var filter, filteredIDs, id, _i, _j, _len, _len2, _ref, _ref2;
    filteredIDs = {};
    for (filter in this.data.filtered) {
      _ref = this.data.filtered[filter];
      for (_i = 0, _len = _ref.length; _i < _len; _i++) {
        id = _ref[_i];
        if (!(filteredIDs[id] != null)) filteredIDs[id] = 0;
        ++filteredIDs[id];
      }
    }
    if (this.data.filtered[filterName] != null) {
      _ref2 = this.data.filtered[filterName];
      for (_j = 0, _len2 = _ref2.length; _j < _len2; _j++) {
        id = _ref2[_j];
        --filteredIDs[id];
        if (filteredIDs[id] === 0) {
          this.showAnnotation(this.data.annotations[id]);
          ++this.data.currentTotal;
        }
      }
    }
    this.data.filtered[filterName] = [];
    this.data.activeFilters[filterName] = [];
    if (filterName === 'category') {
      this.changeShowHighlightsState('checked', true);
      this.changeShowHighlightsState('disabled', false);
    }
    return this.redrawPager();
  };

  Filters.prototype.drawButton = function(id, text, type, selector) {
    var classes;
    if (selector == null) selector = this.options.selector.sidebar;
    selector = $(selector);
    classes = [this.options["class"].button, this.options["class"].buttonType[type]].join(' ');
    return selector.append($('<span>', {
      id: id,
      "class": classes
    }).text(text).on("click", this.buttonClick));
  };

  Filters.prototype.drawAllFilters = function() {
    var filter, inputHTML, sidebar, values, _ref,
      _this = this;
    sidebar = $(this.options.selector.sidebar);
    sidebar.append('<h2>Annotation Filters</h2>');
    this.drawPager(sidebar);
    sidebar.append('<div id="' + this.options.selector.userButtons + '"></div>');
    this.drawButton('no-annotations', 'None', 'user', '#' + this.options.selector.userButtons);
    this.drawButton('own-annotations', 'Mine', 'user', '#' + this.options.selector.userButtons);
    this.drawButton('all-annotations', 'All', 'user', '#' + this.options.selector.userButtons);
    this.drawCheckbox('show-highlights', 'Show Highlights', 'highlights');
    _ref = this.data.filterValues;
    for (filter in _ref) {
      values = _ref[filter];
      inputHTML = "<div class='" + this.options["class"].filterWrapper + "'><label class='" + this.options["class"].filterLabel + "' for='" + filter + "'>" + filter + ": </label><input name='" + filter + "' class='" + this.options["class"].input + "' /></div>";
      sidebar.append(inputHTML);
      $("input[name=" + filter + "]").autocomplete({
        source: values,
        select: function(event, ui) {
          return _this.filterAutocomplete(event, ui);
        }
      });
    }
    this.drawButton('reset', 'Reset', 'reset');
    sidebar.append("<div id='" + this.options.selector.activeFilters + "'>Active Filters</div>");
    $('#own-annotations').addClass(this.options["class"].activeButton);
    this.filterAnnotations('user', this.options.current_user);
    return this.drawActiveFilter('user', this.options.current_user);
  };

  Filters.prototype.drawActiveFilter = function(filterName, matchValue) {
    var classes;
    classes = [filterName, this.options["class"].activeFilter, this.options["class"].closeIcon].join(' ');
    return $('#' + this.options.selector.activeFilters).after($('<div>', {
      id: matchValue,
      "class": classes
    }).text(' ' + filterName + ': ' + matchValue).on("click", this.removeFilterClick));
  };

  Filters.prototype.drawCheckbox = function(id, text, type, selector) {
    var classes;
    if (selector == null) selector = this.options.selector.sidebar;
    selector = $(selector);
    classes = [this.options["class"].checkbox, this.options["class"].checkboxType[type]].join(' ');
    return selector.append($("<input type='checkbox' name='" + id + "' checked>", {
      name: id
    }).on("click", this.checkboxToggle)).append("<span id='" + id + "' class='" + classes + "'>" + text + "</span>");
  };

  Filters.prototype.drawPager = function(selector) {
    var first, last, next, prev;
    first = 'fa fa-angle-double-left';
    prev = 'fa fa-angle-left';
    next = 'fa fa-angle-right';
    last = 'fa fa-angle-double-right';
    $(selector).append($("<i id='first' class='pager pager-arrow " + first + "'/>")).on("click", 'i#first', this.pagerClick);
    $(selector).append($("<i id='prev' class='pager pager-arrow " + prev + "'/>")).on("click", 'i#prev', this.pagerClick);
    $(selector).append($("<span id='pager-count' class='pager'>").text(this.data.currentIndex + " of " + this.data.currentTotal));
    $(selector).append($("<i id='next' class='pager pager-arrow " + next + "'/>")).on("click", 'i#next', this.pagerClick);
    $(selector).append($("<i id='last' class='pager pager-arrow " + last + "'/>")).on("click", 'i#last', this.pagerClick);
    $('.pager').wrapAll('<div id="pager-wrapper"></div>');
  };

  Filters.prototype.redrawPager = function() {
    var filter, id, total, uniqueIDs, _i, _len, _ref;
    total = Object.keys(this.data.annotations).length;
    uniqueIDs = [];
    for (filter in this.data.filtered) {
      if (this.data.filtered[filter].length) {
        this.data.currentIndex = 1;
        _ref = this.data.filtered[filter];
        for (_i = 0, _len = _ref.length; _i < _len; _i++) {
          id = _ref[_i];
          if (__indexOf.call(uniqueIDs, id) < 0) uniqueIDs.push(id);
        }
      }
    }
    total -= uniqueIDs.length;
    if (total <= 0) {
      total = 0;
      this.data.currentIndex = 0;
    }
    if (uniqueIDs.length && this.data.currentIndex > this.data.currentTotal) {
      this.data.currentIndex = 1;
    }
    return $('#pager-count').text(this.data.currentIndex + ' of ' + total);
  };

  Filters.prototype.eraseFilter = function(filterName) {
    $('.' + filterName + '.' + this.options["class"].activeFilter).remove();
    if (filterName === 'user') {
      return $('.' + this.options["class"].activeButton + '.' + this.options["class"].buttonType.user).removeClass(this.options["class"].activeButton);
    }
  };

  Filters.prototype.eraseAllFilters = function() {
    $('.' + this.options["class"].hide).removeClass(this.options["class"].hide);
    return $('.' + this.options["class"].activeFilter).remove();
  };

  Filters.prototype.changeShowHighlightsState = function(attr, state) {
    return $("input[name='show-highlights'").attr(attr, state);
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
        this.removeFilter(filterName);
        _results.push(this.eraseFilter(filterName));
      } else {
        _results.push(void 0);
      }
    }
    return _results;
  };

  Filters.prototype.pagerClick = function(event) {
    var highlight, id;
    switch (event.target.id) {
      case 'first':
        this.data.currentIndex = 1;
        break;
      case 'prev':
        this.data.currentIndex -= 1;
        if (this.data.currentIndex < 1) {
          this.data.currentIndex = this.data.currentTotal;
        }
        break;
      case 'next':
        this.data.currentIndex += 1;
        if (this.data.currentIndex > this.data.currentTotal) {
          this.data.currentIndex = 1;
        }
        break;
      case 'last':
        this.data.currentIndex = this.data.currentTotal;
    }
    id = Object.keys(this.data.annotations)[this.data.currentIndex - 1];
    highlight = $(this.data.annotations[id].highlights[0]);
    $("html, body").animate({
      scrollTop: highlight.offset().top - 20
    }, 150);
    return this.redrawPager();
  };

  Filters.prototype.updateCurrentIndex = function(Viewer) {
    var id;
    id = Viewer.annotations[0].id;
    this.data.currentIndex = Object.keys(this.data.annotations).indexOf(id.toString()) + 1;
    return this.redrawPager();
  };

  Filters.prototype.checkboxToggle = function(event) {
    if (event.target.name === 'show-highlights') {
      if (event.target.checked) {
        return this.removeFilter('category', 'Highlight');
      } else {
        return this.filterAnnotations('category', 'Highlight', true);
      }
    }
  };

  Filters.prototype.filterAutocomplete = function(event, ui) {
    var filterName, matchValue;
    matchValue = ui.item.value;
    filterName = event.target.name;
    if (filterName === 'category') {
      this.changeShowHighlightsState('checked', false);
      this.changeShowHighlightsState('disabled', true);
    }
    this.filterAnnotations(filterName, matchValue);
    this.drawActiveFilter(filterName, matchValue);
    $(event.target).val('');
    return false;
  };

  Filters.prototype.buttonClick = function(event) {
    var activeButton, buttonType, prevActiveButton;
    buttonType = $(event.target).attr('id');
    activeButton = $(event.target);
    prevActiveButton = $('.' + this.options["class"].activeButton);
    if (prevActiveButton.attr('id') === activeButton.attr('id')) return;
    prevActiveButton.removeClass(this.options["class"].activeButton);
    if (buttonType === 'own-annotations') {
      this.removeFilter('user');
      this.removeFilter('all');
      this.filterAnnotations('user', this.options.current_user);
      this.drawActiveFilter('user', this.options.current_user);
    } else if (buttonType === 'all-annotations') {
      this.removeFilter('user');
      this.removeFilter('all');
      this.eraseFilter('user');
    } else if (buttonType === 'no-annotations') {
      this.removeFilter('user');
      this.filterAnnotations('all', null);
      this.eraseFilter('user');
    } else if (buttonType === 'reset') {
      this.removeAllFilters();
      this.eraseAllFilters();
      this.changeShowHighlightsState('checked', true);
      this.changeShowHighlightsState('disabled', false);
      $('#all-annotations').addClass(this.options["class"].activeButton);
      return;
    }
    return activeButton.addClass(this.options["class"].activeButton);
  };

  return Filters;

})(Annotator.Plugin);
