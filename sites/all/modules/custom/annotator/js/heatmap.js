(function() {
  var $,
    __bind = function(fn, me){ return function(){ return fn.apply(me, arguments); }; },
    __hasProp = Object.prototype.hasOwnProperty,
    __extends = function(child, parent) { for (var key in parent) { if (__hasProp.call(parent, key)) child[key] = parent[key]; } function ctor() { this.constructor = child; } ctor.prototype = parent.prototype; child.prototype = new ctor; child.__super__ = parent.prototype; return child; };

  $ = jQuery;

  Annotator.Plugin.Heatmap = (function(_super) {

    __extends(Heatmap, _super);

    Heatmap.prototype.html = {
      element: "<svg class=\"annotator-heatmap\"\n     xmlns=\"http://www.w3.org/2000/svg\"\n     xmlns:xlink=\"http://www.w3.org/1999/xlink\">\n   <defs>\n     <linearGradient id=\"heatmapGradient\"\n                     x1=\"0%\" y1=\"0%\"\n                     x2=\"0%\" y2=\"100%\">\n     </linearGradient>\n     <filter id=\"heatBlend\">\n       <feGaussianBlur stdDeviation=\"3\"><feGaussianBlur>\n     </filter>\n   </defs>\n   <rect x=\"0\" y=\"0\" width=\"800px\" height=\"50px\"\n         fill=\"url(#heatmapGradient)\"\n         filter=\"url(#heatBlend)\" />\n</svg>",
      options: {
        message: Annotator._t("Sorry, the annotation heatmap failed to load.")
      }
    };

    Heatmap.prototype.pluginInit = function() {
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
      this.updateHeatmap = __bind(this.updateHeatmap, this);      Heatmap.__super__.constructor.call(this, element, options);
      this.d3 = d3;
      this.layout = options.layout;
      this.heatmapContainer = document.querySelector(this.layout.container);
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

    Heatmap.prototype.updateHeatmap = function() {
      var annotations;
      if (typeof d3 === "undefined" || d3 === null) return;
      if (this.layout.orientation === 'horizontal') {
        this.layout.width = this.heatmapContainer.offsetWidth;
      }
      this.layout.height = this.heatmapContainer.offsetHeight;
      return annotations = this.annotator.element.find('.annotator-hl:not(.af-annotation-hide)');
    };

    return Heatmap;

  })(Annotator.Plugin);

}).call(this);
