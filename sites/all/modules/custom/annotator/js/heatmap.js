(function() {
  var $,
    __bind = function(fn, me){ return function(){ return fn.apply(me, arguments); }; },
    __hasProp = Object.prototype.hasOwnProperty,
    __extends = function(child, parent) { for (var key in parent) { if (__hasProp.call(parent, key)) child[key] = parent[key]; } function ctor() { this.constructor = child; } ctor.prototype = parent.prototype; child.prototype = new ctor; child.__super__ = parent.prototype; return child; },
    __indexOf = Array.prototype.indexOf || function(item) { for (var i = 0, l = this.length; i < l; i++) { if (i in this && this[i] === item) return i; } return -1; };

  $ = jQuery;

  Annotator.Plugin.Heatmap = (function(_super) {

    __extends(Heatmap, _super);

    Heatmap.prototype.selector = {
      annotation: 'annotator-hl',
      hidden: 'af-annotation-hide',
      heatmap: 'annotation-heatmap',
      bar: 'annotation-heatmap-bar',
      pageTurner: 'page-turner-nav'
    };

    Heatmap.prototype.pluginInit = function() {
      if (!Annotator.supported()) return;
      if (!Annotator.Plugin.Filters) return;
      d3.select('#' + this.layout.containerID).insert('svg:svg', ':first-child').append('g').attr('id', this.selector.heatmap);
      this.heatmapContainer = d3.select('#' + this.selector.heatmap);
      if (!((typeof d3 !== "undefined" && d3 !== null) || (this.d3 != null))) {
        console.error('d3.js is required to use the heatmap plugin');
      } else {
        this._setupListeners();
        return this.update();
      }
    };

    function Heatmap(element, options) {
      this.update = __bind(this.update, this);
      this.updateChart = __bind(this.updateChart, this);
      this.calculateDensity = __bind(this.calculateDensity, this);
      this.configureBars = __bind(this.configureBars, this);
      this.calculateDimensions = __bind(this.calculateDimensions, this);      Heatmap.__super__.constructor.call(this, element, options);
      this.d3 = d3;
      this.layout = options.layout;
      this.barWidth = 0;
      this.barTotal = 0;
      this.bars = [];
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
      if (this.layout.horizontal) {
        this.layout.width = document.getElementById(this.layout.containerID).offsetWidth;
      }
      this.layout.height = document.getElementById(this.selector.pageTurner).offsetHeight || document.getElementById(this.layout.containerID).offsetHeight;
      return this.heatmapContainer.style('width', this.layout.width).style('height', this.layout.height);
    };

    Heatmap.prototype.configureBars = function(length) {
      if (this.layout.horizontal) {
        this.barTotal = $('.page-turner-ticks .tick').length;
        if (!(this.barTotal != null)) {
          this.barTotal = Math.ceil(length / this.layout.width);
        } else {
          this.barTotal = this.barTotal * 4;
        }
      }
      return this.barWidth = Math.floor(length / this.barTotal);
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
        if (length >= this.barWidth) {
          if (total > 0) {
            this.bars.push(total);
          } else {
            for (i = 0, _ref2 = Math.ceil(length / this.barWidth); 0 <= _ref2 ? i <= _ref2 : i >= _ref2; 0 <= _ref2 ? i++ : i--) {
              this.bars.push(0);
            }
          }
          total = 0;
          length = 0;
          counted = [];
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
      if (d3.max(this.bars) > 10) {
        colors = d3.scale.linear().domain([0, 2, 5, 10, d3.max(this.bars)]).range(['#f1eef6', '#bdc9e1', '#74a9cf', '#2b8cbe', '#045a8d']);
      } else {
        colors = d3.scale.linear().domain([0, d3.max(this.bars)]).range(['#2b8cbe', '#045a8d']);
      }
      y = d3.scale.linear().domain([0, d3.max(this.bars)]).range([0, this.layout.height]);
      barWidth = this.layout.width / this.bars.length;
      heatmap = this.heatmapContainer.selectAll("rect." + this.selector.bar).data(this.bars);
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
      this.bars = [];
      documentNode = $(this.annotator.wrapper).children()[1];
      this.calculateDimensions(documentNode);
      this.configureBars(documentNode.textContent.length);
      _ref = $(documentNode).find('.field-item.even').children();
      for (_i = 0, _len = _ref.length; _i < _len; _i++) {
        node = _ref[_i];
        this.calculateDensity(node);
      }
      console.log(this.bars, this.bars.length, this.barTotal);
      return this.updateChart();
    };

    return Heatmap;

  })(Annotator.Plugin);

}).call(this);
