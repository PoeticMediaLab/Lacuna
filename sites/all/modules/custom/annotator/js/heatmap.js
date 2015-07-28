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
      element: '<g id ="annotation-heatmap"></g>'
    };

    Heatmap.prototype.selector = {
      annotation: 'annotator-hl',
      hidden: 'af-annotation-hide',
      heatmap: '#annotation-heatmap',
      bar: 'annotation-heatmap-bar'
    };

    Heatmap.prototype.pluginInit = function() {
      if (!Annotator.Plugin.Filters) return;
      $('#' + this.layout.containerID).prepend(this.html.element);
      this.heatmapContainer = d3.select(this.selector.heatmap);
      if (!((typeof d3 !== "undefined" && d3 !== null) || (this.d3 != null))) {
        return console.error('d3.js is required to use the heatmap plugin');
      } else {
        this._setupListeners();
        return this.update();
      }
    };

    function Heatmap(element, options) {
      this.update = __bind(this.update, this);
      this.updateChart = __bind(this.updateChart, this);
      this.calculateDensity = __bind(this.calculateDensity, this);
      this.configureBins = __bind(this.configureBins, this);
      this.calculateDimensions = __bind(this.calculateDimensions, this);      Heatmap.__super__.constructor.call(this, element, options);
      this.d3 = d3;
      this.layout = options.layout;
      this.binSize = 0;
      this.binTotal = 0;
      this.bins = [];
      this.chart;
    }

    Heatmap.prototype._setupListeners = function() {
      var event, events, _i, _len;
      events = ['annotationsLoaded', 'annotationCreated', 'annotationUpdated', 'annotationDeleted'];
      for (_i = 0, _len = events.length; _i < _len; _i++) {
        event = events[_i];
        this.annotator.subscribe(event, this.update);
      }
      $(window).resize(this.update);
      return $(document).bind('annotation-filters-changed', this.update);
    };

    Heatmap.prototype.calculateDimensions = function(node) {
      this.layout.length = node.textContent.length;
      if (this.layout.orientation === 'horizontal') {
        this.layout.width = document.getElementById(this.layout.containerID).offsetWidth;
      }
      this.layout.height = document.getElementById(this.layout.containerID).offsetHeight;
      return this.heatmapContainer.style('width', this.layout.width).style('height', this.layout.height);
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
      return this.binSize = Math.floor(length / this.binTotal);
    };

    Heatmap.prototype.calculateDensity = function(node, length, overlap) {
      var child, counted, i, id, total, _i, _len, _ref, _ref2;
      if (length == null) length = 0;
      if (overlap == null) overlap = false;
      counted = [];
      total = 0;
      _ref = node.childNodes;
      for (_i = 0, _len = _ref.length; _i < _len; _i++) {
        child = _ref[_i];
        if (!overlap) length += child.textContent.length;
        if (length >= this.binSize) {
          if (total > 0) {
            this.bins.push(total);
          } else {
            for (i = 0, _ref2 = Math.ceil(length / this.binSize); 0 <= _ref2 ? i <= _ref2 : i >= _ref2; 0 <= _ref2 ? i++ : i--) {
              this.bins.push(0);
            }
          }
          total = 0;
          length = 0;
        }
        if (child.nodeType === Node.ELEMENT_NODE && child.classList.contains(this.selector.annotation) && !child.classList.contains(this.selector.hidden)) {
          if (child.hasChildNodes()) {
            total += this.calculateDensity(child, length, true);
          }
          id = parseInt(child.dataset.annotationId, 10);
          if (__indexOf.call(counted, id) < 0) {
            total++;
            counted.push(id);
          }
        }
      }
      return total;
    };

    Heatmap.prototype.updateChart = function() {
      var barWidth, colors, heatmap, y,
        _this = this;
      colors = d3.scale.linear().domain([0, d3.max(this.bins)]).range(['blue', 'green']);
      y = d3.scale.linear().domain([0, d3.max(this.bins)]).range([0, this.layout.height]);
      console.log(y(0), y(1), y(2), y(3), y(4));
      barWidth = this.layout.width / this.bins.length;
      heatmap = this.heatmapContainer.selectAll("rect." + this.selector.bar).data(this.bins);
      heatmap.exit().remove();
      heatmap.enter().append('rect').style('fill', colors).classed(this.selector.bar, true);
      return heatmap.attr('width', barWidth).attr('x', function(d, i) {
        return barWidth * i;
      }).attr('height', function(d) {
        return y(d);
      }).attr('y', function(d) {
        return _this.layout.height - y(d);
      });
    };

    Heatmap.prototype.update = function() {
      var documentNode, node, _i, _len, _ref;
      if (typeof d3 === "undefined" || d3 === null) return;
      this.bins = [];
      documentNode = $(this.annotator.wrapper).children()[1];
      this.calculateDimensions(documentNode);
      this.configureBins(documentNode.textContent.length);
      _ref = $(documentNode).find('.field-item.even').children();
      for (_i = 0, _len = _ref.length; _i < _len; _i++) {
        node = _ref[_i];
        this.calculateDensity(node);
      }
      return this.updateChart();
    };

    return Heatmap;

  })(Annotator.Plugin);

}).call(this);
