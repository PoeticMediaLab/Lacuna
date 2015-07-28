(function() {
  var $,
    __bind = function(fn, me){ return function(){ return fn.apply(me, arguments); }; },
    __hasProp = Object.prototype.hasOwnProperty,
    __extends = function(child, parent) { for (var key in parent) { if (__hasProp.call(parent, key)) child[key] = parent[key]; } function ctor() { this.constructor = child; } ctor.prototype = parent.prototype; child.prototype = new ctor; child.__super__ = parent.prototype; return child; },
    __indexOf = Array.prototype.indexOf || function(item) { for (var i = 0, l = this.length; i < l; i++) { if (i in this && this[i] === item) return i; } return -1; };

  $ = jQuery;

  Annotator.Plugin.Heatmap = (function(_super) {

    __extends(Heatmap, _super);

    Heatmap.prototype.html = {
      element: "<svg class=\"annotator-heatmap\"\n     xmlns=\"http://www.w3.org/2000/svg\"\n     xmlns:xlink=\"http://www.w3.org/1999/xlink\">\n   <defs>\n     <linearGradient id=\"heatmapGradient\"\n                     x1=\"0%\" y1=\"0%\"\n                     x2=\"0%\" y2=\"100%\">\n     </linearGradient>\n     <filter id=\"heatBlend\">\n       <feGaussianBlur stdDeviation=\"3\"><feGaussianBlur>\n     </filter>\n   </defs>\n   <rect x=\"0\" y=\"0\" width=\"800px\" height=\"50px\"\n         fill=\"url(#heatmapGradient)\"\n         filter=\"url(#heatBlend)\" />\n</svg>",
      options: {
        message: Annotator._t("Sorry, the annotation heatmap failed to load.")
      }
    };

    Heatmap.prototype.selector = {
      annotation: 'annotator-hl',
      hidden: 'af-annotation-hide'
    };

    Heatmap.prototype.pluginInit = function() {
      if (!Annotator.Plugin.Filters) return;
      this.heatmap = $(this.html.element);
      $(this.layout.container).prepend(this.html.element);
      if (!((typeof d3 !== "undefined" && d3 !== null) || (this.d3 != null))) {
        return console.error('d3.js is required to use the heatmap plugin');
      } else {
        this._setupListeners();
        return this.updateHeatmap();
      }
    };

    function Heatmap(element, options) {
      this.updateHeatmap = __bind(this.updateHeatmap, this);
      this.calculateDensity = __bind(this.calculateDensity, this);
      this.configureBins = __bind(this.configureBins, this);
      this.calculateDimensions = __bind(this.calculateDimensions, this);      Heatmap.__super__.constructor.call(this, element, options);
      this.d3 = d3;
      this.layout = options.layout;
      this.heatmapContainer = document.querySelector(this.layout.container);
      this.binSize = 0;
      this.binTotal = 0;
      this.bins = [];
    }

    Heatmap.prototype._setupListeners = function() {
      var event, events, _i, _len;
      events = ['annotationsLoaded', 'annotationCreated', 'annotationUpdated', 'annotationDeleted'];
      for (_i = 0, _len = events.length; _i < _len; _i++) {
        event = events[_i];
        this.annotator.subscribe(event, this.updateHeatmap);
      }
      $(window).resize(this.updateHeatmap);
      return $(document).bind('annotation-filters-changed', this.updateHeatmap);
    };

    Heatmap.prototype.calculateDimensions = function(node) {
      this.layout.length = node.textContent.length;
      if (this.layout.orientation === 'horizontal') {
        this.layout.width = this.heatmapContainer.offsetWidth;
      }
      return this.layout.height = this.heatmapContainer.offsetHeight;
    };

    Heatmap.prototype.configureBins = function(length) {
      if (this.layout.orientation === 'horizontal') {
        this.binTotal = $('.page-turner-ticks .tick').length;
        if (!(this.binTotal != null)) {
          this.binTotal = Math.ceil(length / this.layout.width);
        } else {
          this.binTotal = this.binTotal * 4;
        }
      }
      return this.binSize = Math.ceil(length / this.binTotal);
    };

    Heatmap.prototype.calculateDensity = function(node, length) {
      var child, counted, id, total, _i, _len, _ref;
      if (length == null) length = 0;
      counted = [];
      total = 0;
      _ref = node.childNodes;
      for (_i = 0, _len = _ref.length; _i < _len; _i++) {
        child = _ref[_i];
        length += child.textContent.length;
        if (length >= this.binSize) {
          this.bins.push(total);
          total = 0;
          length = 0;
        }
        if (child.nodeType === Node.ELEMENT_NODE && child.classList.contains(this.selector.annotation) && !child.classList.contains(this.selector.hidden)) {
          if (child.hasChildNodes()) total += this.calculateDensity(child, length);
          id = parseInt(child.dataset.annotationId, 10);
          if (__indexOf.call(counted, id) < 0) {
            total++;
            counted.push(id);
          }
        }
      }
      return total;
    };

    Heatmap.prototype.updateHeatmap = function() {
      var documentNode, node, _i, _len, _ref;
      if (typeof d3 === "undefined" || d3 === null) return;
      this.bins = [];
      documentNode = $(this.annotator.wrapper).children()[1];
      this.calculateDimensions(documentNode);
      this.configureBins(documentNode.textContent.length);
      console.log(this.binSize, this.binTotal);
      _ref = $(documentNode).find('.field-item.even').children();
      for (_i = 0, _len = _ref.length; _i < _len; _i++) {
        node = _ref[_i];
        this.calculateDensity(node);
      }
      return console.log(this.bins, this.bins.length);
    };

    return Heatmap;

  })(Annotator.Plugin);

}).call(this);
