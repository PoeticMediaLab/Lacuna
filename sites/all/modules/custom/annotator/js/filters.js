(function() {
  var $, Model, View, select,
    __bind = function(fn, me){ return function(){ return fn.apply(me, arguments); }; },
    __hasProp = Object.prototype.hasOwnProperty,
    __extends = function(child, parent) { for (var key in parent) { if (__hasProp.call(parent, key)) child[key] = parent[key]; } function ctor() { this.constructor = child; } ctor.prototype = parent.prototype; child.prototype = new ctor; child.__super__ = parent.prototype; return child; };

  $ = jQuery;

  select = {
    'default': 'af',
    'interface': '#annotation-filters',
    'annotation': 'annotation-',
    'pager': {
      'wrapper': 'pager-wrapper',
      'count': 'pager-count',
      'arrow': 'pager-arrow',
      'first': 'fa fa-angle-double-left',
      'prev': 'fa fa-angle-left',
      'next': 'fa fa-angle-right',
      'last': 'fa fa-angle-double-right'
    },
    'button': {
      'active': 'button-filter-active',
      'user': 'button-filter-user',
      'none': 'button-filter-none',
      'all': 'button-filter-all',
      'mine': 'button-filter-mine'
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
      this.checkboxToggle = __bind(this.checkboxToggle, this);
      this.buttonClick = __bind(this.buttonClick, this);
      this.filterSelect = __bind(this.filterSelect, this);      Filters.__super__.constructor.apply(this, arguments);
      this.Model = new Model;
      this.View = new View;
      if (options.current_user != null) {
        this.Model.setCurrentUser(options.current_user);
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
      this.Model.setup(annotations);
      return this.View.setup(this, this.Model);
    };

    Filters.prototype.filterSelect = function(event) {};

    Filters.prototype.buttonClick = function(event) {
      console.log(event, 'buttonClick');
    };

    Filters.prototype.checkboxToggle = function(event) {};

    Filters.prototype.getSelector = function(item, selector) {
      var i, key, _i, _len;
      console.log([item, selector], 'start');
      if (!selector) selector = '';
      if (typeof item === 'string') {
        console.log('string');
        if (!(select[item] != null) || select[item] instanceof Object) {
          selector += select["default"] + '-' + item;
        } else {
          selector += select[item];
        }
      } else if (item instanceof Array) {
        console.log('array');
        for (_i = 0, _len = item.length; _i < _len; _i++) {
          i = item[_i];
          console.log(i, 'recurse Array');
          selector = this.getSelector(i, selector + ' ');
        }
      } else if (item instanceof Object) {
        console.log('object Recurse');
        for (key in item) {
          selector += this.getSelector(key, selector + ' ');
          selector += this.getSelector(key + '-' + item[key], selector + ' ');
        }
      }
      console.log([item, selector]);
      return selector.trim();
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
      this.View.drawPagerCount(index, total);
      return this.View.scrollTo(this.Model.annotation());
    };

    return Filters;

  })(Annotator.Plugin);

  Model = (function() {

    function Model() {}

    Model.prototype.state = {
      mode: 'intersection',
      highlights: true,
      annotations: [],
      annotationsHidden: [],
      annotationsShown: [],
      total: 0,
      index: 0,
      currentUser: null,
      filters: []
    };

    Model.prototype.setup = function(annotations) {
      var annotation, highlight, _i, _j, _len, _len2, _ref;
      this.state.annotations = annotations;
      for (_i = 0, _len = annotations.length; _i < _len; _i++) {
        annotation = annotations[_i];
        _ref = annotation.highlights;
        for (_j = 0, _len2 = _ref.length; _j < _len2; _j++) {
          highlight = _ref[_j];
          $(highlight).first().attr('id', select.annotation + annotation.id);
          $(highlight).addClass(select.annotation + annotation.id);
        }
      }
      this.state.total = annotations.length;
      if (this.state.total) return this.state.index = 1;
    };

    Model.prototype.get = function(attr) {
      return this.state[attr];
    };

    Model.prototype.set = function(attr, value) {
      return this.state[attr] = value;
    };

    Model.prototype.currentID = function() {
      return this.state.annotations[this.state.index - 1].id;
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

    Model.prototype.toggleMode = function() {};

    Model.prototype.addFilter = function(name, value) {};

    Model.prototype.removeFilter = function(name, value) {};

    Model.prototype.toggleHighlights = function() {};

    Model.prototype.changePager = function(direction) {};

    Model.prototype.setCurrentUser = function(currentUser) {
      return this.state.currentUser = currentUser;
    };

    return Model;

  })();

  /* View methods
  */

  View = (function() {

    function View() {
      this.setup = __bind(this.setup, this);
    }

    View.prototype.setup = function(Controller, Model) {
      this.i = select.interface;
      this.Controller = Controller;
      this.Model = Model;
      $(this.i).append('<h2>Annotation Filters</h2>');
      this.drawPager(this.Model.get('index'), this.Model.get('total'));
      $(this.i).append('<div id="' + this.Controller.getSelector('button') + '"></div>');
      this.drawButton(select.button.user, 'none', 'user');
      this.drawButton(select.button.user, 'mine', 'user');
      this.drawButton(select.button.user, 'all', 'user');
    };

    View.prototype.update = function() {};

    View.prototype.viewerShown = function(Viewer) {};

    View.prototype.drawButton = function(loc, id, filter) {
      var classes;
      classes = this.Controller.getSelector(['button', [id, filter]]);
      return $('#' + loc).append($('<span>', {
        id: id,
        "class": classes
      }).text(id).on('click', this.Controller.buttonClick));
    };

    View.prototype.drawActiveButton = function(id) {};

    View.prototype.drawCheckbox = function(id, value) {};

    View.prototype.drawAutocomplete = function(id, values) {};

    View.prototype.drawPager = function(first, last) {
      var base, p;
      p = select.pager;
      base = select.annotation + 'pager';
      $(this.i).append($("<i id='first' class='" + base + " " + p.arrow + " " + p.first + "'/>")).on("click", 'i#first', this.Controller.pagerClick);
      $(this.i).append($("<i id='prev' class='" + base + " " + p.arrow + " " + p.prev + "'/>")).on("click", 'i#prev', this.Controller.pagerClick);
      $(this.i).append($("<span id='" + p.count + "' class='" + base + "'>").text(first + ' of ' + last));
      $(this.i).append($("<i id='next' class='" + base + " " + p.arrow + " " + p.next + "'/>")).on("click", 'i#next', this.Controller.pagerClick);
      $(this.i).append($("<i id='last' class='" + base + " " + p.arrow + " " + p.last + "'/>")).on("click", 'i#last', this.Controller.pagerClick);
      $('.' + base).wrapAll("<div id='" + p.wrapper + "'></div>");
    };

    View.prototype.drawPagerCount = function(first, last) {
      return $('#' + select.pager.count).text(first + ' of ' + last);
    };

    View.prototype.drawFilter = function(id, value) {};

    View.prototype.eraseFilter = function(id, value) {};

    View.prototype.showAnnotations = function(annotations) {};

    View.prototype.hideAnnotations = function(annotations) {};

    View.prototype.scrollTo = function(annotation) {
      var highlight;
      highlight = $(annotation.highlights[0]);
      return $("html, body").animate({
        scrollTop: highlight.offset().top - 20
      }, 150);
    };

    return View;

  })();

}).call(this);
