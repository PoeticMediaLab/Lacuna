(function() {
  var $,
    __bind = function(fn, me){ return function(){ return fn.apply(me, arguments); }; },
    __hasProp = Object.prototype.hasOwnProperty,
    __extends = function(child, parent) { for (var key in parent) { if (__hasProp.call(parent, key)) child[key] = parent[key]; } function ctor() { this.constructor = child; } ctor.prototype = parent.prototype; child.prototype = new ctor; child.__super__ = parent.prototype; return child; },
    __indexOf = Array.prototype.indexOf || function(item) { for (var i = 0, l = this.length; i < l; i++) { if (i in this && this[i] === item) return i; } return -1; };

  $ = jQuery;

  Annotator.Plugin.Histogram = (function(_super) {

    __extends(Histogram, _super);

    Histogram.prototype.selector = {
      annotation: 'annotator-hl',
      hidden: 'af-annotation-hide',
      histogram: 'annotation-histogram',
      bar: 'annotation-histogram-bar',
      pageTurner: 'page-turner-nav'
    };

    Histogram.prototype.pluginInit = function() {
      if (!Annotator.supported()) return;
      if (!Annotator.Plugin.Filters) return;
      d3.select('#' + this.layout.containerID).insert('svg:svg', ':first-child').append('g').attr('id', this.selector.histogram);
      this.histogramContainer = d3.select('#' + this.selector.histogram);
      if (!((typeof d3 !== "undefined" && d3 !== null) || (this.d3 != null))) {
        console.error('d3.js is required to use the histogram plugin');
      } else {
        this._setupListeners();
        return this.update();
      }
    };

    function Histogram(element, options) {
      this.update = __bind(this.update, this);
      this.updateChart = __bind(this.updateChart, this);
      this.calculateDensity = __bind(this.calculateDensity, this);
      this.barsPerNode = __bind(this.barsPerNode, this);
      this.setBarDimensions = __bind(this.setBarDimensions, this);
      this.calculateDimensions = __bind(this.calculateDimensions, this);      Histogram.__super__.constructor.call(this, element, options);
      this.d3 = d3;
      this.layout = options.layout;
      this.barTextLength = 0;
      this.barTotal = 0;
      this.bars = [];
      this.chart;
      this.pageTurner = false;
      this.barsPerPage = 4;
    }

    Histogram.prototype._setupListeners = function() {
      var event, events, _i, _len;
      events = ['annotationsLoaded', 'annotationCreated', 'annotationUpdated', 'annotationDeleted'];
      for (_i = 0, _len = events.length; _i < _len; _i++) {
        event = events[_i];
        this.annotator.subscribe(event, this.update);
      }
      $(window).resize(this.update);
      return $(document).bind('annotation-filters-changed', this.update);
    };

    Histogram.prototype.calculateDimensions = function(node) {
      this.layout.length = node.textContent.length;
      if (this.layout.horizontal) {
        this.layout.width = document.getElementById(this.layout.containerID).offsetWidth;
      }
      this.layout.height = document.getElementById(this.selector.pageTurner).offsetHeight || document.getElementById(this.layout.containerID).offsetHeight;
      return this.histogramContainer.style('width', this.layout.width).style('height', this.layout.height);
    };

    Histogram.prototype.setBarDimensions = function(length) {
      if (this.layout.horizontal) {
        this.barTotal = $('.page-turner-ticks .tick').length;
        if (!(this.barTotal != null)) {
          this.barTotal = Math.ceil(length / this.layout.width);
        } else {
          this.pageTurner = true;
          this.barTotal = this.barTotal * this.barsPerPage;
        }
      }
      return this.barTextLength = length / this.barTotal;
    };

    Histogram.prototype.barsPerNode = function(node, length) {
      var annotation, child, counted, id, maxLength, total, totalBars, _i, _j, _len, _len2, _ref, _ref2;
      if (length == null) length = 0;
      counted = [];
      total = 0;
      if (this.pageTurner) {
        maxLength = node.textContent.length / this.barsPerPage;
      } else {
        maxLength = this.barTextLength;
      }
      _ref = node.childNodes;
      for (_i = 0, _len = _ref.length; _i < _len; _i++) {
        child = _ref[_i];
        length += child.textContent.length;
        if (length >= maxLength) {
          totalBars = Math.floor(length / maxLength);
          length = length % maxLength;
          if (total > 0) {
            this.bars.push(total);
            totalBars--;
          }
          while (totalBars--) {
            this.bars.push(0);
          }
          total = 0;
          counted = [];
        }
        if (child.nodeType === Node.ELEMENT_NODE && child.classList.contains(this.selector.annotation) && !child.classList.contains(this.selector.hidden)) {
          if (child.hasChildNodes()) {
            _ref2 = child.querySelectorAll('.' + this.selector.annotation);
            for (_j = 0, _len2 = _ref2.length; _j < _len2; _j++) {
              annotation = _ref2[_j];
              id = parseInt(child.dataset.annotationId, 10);
              if (__indexOf.call(counted, id) < 0) {
                total++;
                counted.push(id);
              }
            }
          }
          id = parseInt(child.dataset.annotationId, 10);
          if (__indexOf.call(counted, id) < 0) {
            total++;
            counted.push(id);
          }
        }
      }
      return length;
    };

    Histogram.prototype.calculateDensity = function(nodes) {
      var length, node, _i, _len, _results;
      length = 0;
      for (_i = 0, _len = nodes.length; _i < _len; _i++) {
        node = nodes[_i];
        length = this.barsPerNode(node, length);
      }
      _results = [];
      while (this.bars.length < this.barTotal) {
        _results.push(this.bars.push(0));
      }
      return _results;
    };

    Histogram.prototype.updateChart = function() {
      var barWidth, colors, histogram, y,
        _this = this;
      colors = d3.scale.linear().domain([0, d3.max(this.bars)]).range(['white', '#1693A5']);
      y = d3.scale.linear().domain([0, d3.max(this.bars)]).range([0, this.layout.height]);
      histogram = this.histogramContainer.selectAll("rect." + this.selector.bar).data(this.bars);
      histogram.exit().remove();
      histogram.enter().append('rect').classed(this.selector.bar, true);
      barWidth = this.layout.width / this.bars.length;
      return histogram.attr('width', barWidth).style('fill', function(d) {
        return colors(d);
      }).attr('x', function(d, i) {
        return barWidth * i;
      }).attr('height', function(d) {
        return y(d);
      }).attr('y', function(d) {
        return _this.layout.height - y(d);
      });
    };

    Histogram.prototype.update = function() {
      var documentNode;
      if (typeof d3 === "undefined" || d3 === null) return;
      this.bars = [];
      documentNode = $(this.annotator.wrapper).children()[1];
      this.calculateDimensions(documentNode);
      this.setBarDimensions(documentNode.textContent.length);
      this.calculateDensity($(documentNode).find('.field-item.even').children());
      return this.updateChart();
    };

    return Histogram;

  })(Annotator.Plugin);

}).call(this);
