/**
 * Page Turner hides/shows parts of a node
 * based on settings about character length
 *
 * Mike Widner <mikewidner@stanford.edu>
 **/

 "use strict";

/******
 *
 * Some light weight MVC to avoid problems as complexity grows
 * @see
 * https://alexatnet.com/articles/model-view-controller-mvc-javascript
 *
 ******/

/**
 * Observer object for event notification
 */
function Event(sender) {
  this.sender = sender;
  this.listeners = [];
}

Event.prototype = {
  attach: function(listener) {
    this.listeners.push(listener);
  },
  notify: function(args) {
    var i, l;

    for (i = 0, l = this.listeners.length; i < l; i++) {
      this.listeners[i](this.sender, args);
    }
  },
}; // END: Event

/**
 * Page Turner Model
 * Handles turning HTML into pages
 * accessing pages by number, etc.
 **/
function PTModel(content, settings) {
  this.content = content;
  this.settings = settings.page_turner;
  var chunks = chunk_pages(content, this.settings);
  this.page = {start: 0, end: 1};   // current page range
  this.pages = chunks.pages;        // content of all pages
  this.breaks = chunks.break_pages; // content of break pages

  function chunk_pages(content, settings) {
    // Divide total content length by page length
    // And look for page break elements
    // Return array of page chunks
    var page = Array(); // holds all elements in a page
    var t_len = 0;  // text length
    var breaks = settings.breaks.toLowerCase().split(',');
    var pages = Array();
    var break_pages = Array();

    // Get to the real content
    while (content.childElementCount == 1) {
      content = content.childNodes[0];
    }
    content = content.children;

    // Check that the current item is not a break point
    // and that adding it wouldn't go over the text limit
    var l = content.length;
    var i;
    for (i = 0; i < l; i++) {
      var is_break = (breaks.indexOf(content[i].tagName.toLowerCase()) != -1);
      var new_len = t_len + content[i].textContent.length;

      if (is_break) {
        if (t_len == 0) {
          // Start of new page
          page.push(content[i]);
          t_len = new_len;
        } else {
          // End of last page, start a new one
          pages.push(page);
          t_len = 0;
          page = Array(content[i]); // Include in the new page
        }
        break_pages.push({page: pages.length + 1, content: content[i]});
      } else if (new_len <= settings.page_length) {
        t_len = new_len;
        page.push(content[i]);
      } else if (page.length > 0) {
        // Start a new page
        pages.push(page);
        t_len = content[i].textContent.length;
        page = Array(content[i]);
      }
    }
    pages.push(page); // whatever's left over
    return {pages: pages, break_pages: break_pages};
  }  // END: _chunk_pages()
}

PTModel.prototype = {
  get_page: function(page_num) {
    if (page_num > this.page_total()) {
      return this.pages[page_total() - 1];
    }
    if (page_num < 0) {
      return this.pages[0];
    }
    return this.pages[page_num];
  },

  current_page: function(p) {
    if (p) {
      if (p > this.page_total()) {
        p = this.page_total();
      }
      if (p < 0) {
        p = 0;
      }
      var diff = this.page.start - p;
      this.page.start = p;
      this.page.end += diff;
    }
    return this.page.start;
  },

  next_page: function() {
    var range = this.page.end - this.page.start;
    var total = this.page_total();
    this.page.start += range;
    this.page.end += range;
    if (this.page.end > total) {
      this.page.start = total - range;
      this.page.end = total;
    }
  },

  prev_page: function() {
    var range = this.page.end - this.page.start;
    this.page.start -= range;
    this.page.end -= range;
    if (this.page.start < 0) {
      this.page.start = 0;
      this.page.end = range;
    }
  },

  page_range: function() {
    // Return current page range
    return [this.page.start, this.page.end];
  },

  all_pages: function() {
    // Return all page content
    return this.pages;
  },

  all_breaks: function() {
    // Returns a list of page numbers that are break points
    // with their content (for hover tip display)
    return this.break_pages;
  },

  page_total: function() {
    return this.pages.length;
  },
}; // END: PTModel

/**
 * Page Turner View
 * Shows, hides pages
 * Draws user interface elements
 **/
function PTView(model, elements) {
  var self = this;
  self.model = model;
  // Elements we expect to add # when selecting
  // so we can use them as ids w/o problems
  self.elements = elements;
  self.navbar = {};
  self.page = {};
  draw_navbar();
  create_events();

  function draw_navbar(elements) {
    // Add our pager elements to DOM
    // Must be done first to bind click events
    $(self.elements.article).before('<div id="' + self.elements.navbar + '"></div>');
    var navbar = $('#' + self.elements.navbar);
    navbar.append('<div id="' + self.elements.page.prev + '" class="page-turner-bar fa fa-3x fa-arrow-left"></div>');

    self.svg = d3.select('#' + self.elements.navbar).append("svg");
    self.navbar = self.svg
        .attr("width", "90%") // Note: affects width calculations
        .attr("height", "100%")
      .append("g")
      .append("rect")
        .attr("id", self.elements.navbar);

    navbar.append('<div id="' + self.elements.page.next + '" class="page-turner-bar fa fa-3x fa-arrow-right"></div>');
  }

  function create_events() {
    self.pager_clicked = new Event(self);
    self.brush_moved = new Event(self);   // brush has moved

    // Set up HTML listeners for page prev/next
    $('#' + self.elements.page.next).click(function () {
      self.pager_clicked.notify({ direction: 'next' });
    });

    $('#' + self.elements.page.prev).click(function () {
      self.pager_clicked.notify({ direction: 'prev' });
    });
  }
}

PTView.prototype = {
  hide_page: function(page_num) {
    // page-turner-hidden class is set in page_turner.css
    $(this.model.get_page(page_num)).addClass(this.elements.hidden);
  },

  show_page: function(page_num) {
    $(this.model.get_page(page_num)).removeClass(this.elements.hidden);
  },

  show_pages: function(range) {
    var i;
    for (i = range[0]; i < range[1]; i++) {
      this.show_page(i);
    }
  },

  hide_pages: function(range) {
    var i;
    for (i = range[0]; i < range[1]; i++) {
      this.hide_page(i);
    }
  },

  hide_all_pages: function() {
    var i, l;
    for (i = 0, l = this.model.page_total(); i < l; i++) {
      this.hide_page(i);
    }
  },

  draw_page_number: function(page_num) {

  },

  draw_navbar_markers: function(pages) {
    // Draw markers in navbar for given pages
  },

  extent_to_page: function(extent) {
    // Convert an extent value to page number
    return Math.round(this.ratio * extent);
  },

  page_to_extent: function(page_num) {
    // convert a page number to an extent value
    return page_num / this.ratio;
  },

  snap_extent_to_page_edges: function(extent) {
    // Adjust a given extent to snap to page boundaries
    return [
      this.page_to_extent(this.extent_to_page(extent[0])),
      this.page_to_extent(this.extent_to_page(extent[1]))
    ]
  },

  animate_brush: function(extent) {
    d3.select('#' + this.elements.brush).transition()
      .call(this.brush.extent(extent));
  },

  update_brush: function() {
    // Model must have changed, update the brush
    this.animate_brush([
      this.page_to_extent(this.model.page.start),
      this.page_to_extent(this.model.page.end)
    ]);
  },

  move_brush: function() {
    // Brush finished moving, snap to page boundaries, notify
    var extent = this.snap_extent_to_page_edges(this.brush.extent());
    this.animate_brush(extent);
    this.brush_moved.notify(extent);  // notify listeners
  },

  draw_brush: function(page_num) {
    // divide navbar into even sections, one per page
    // put brush over page_num
    this.navbar.width = parseInt(d3.select('#' + this.elements.navbar).style('width'), 10) * .9; // svg width = 90%
    this.page.width = this.navbar.width / this.model.page_total();
    this.ratio = this.navbar.width / this.page.width;

    var height = parseInt(d3.select('#' + this.elements.navbar).style('height'), 10);
    var x = d3.scale.linear().range([0, this.navbar.width]);

    var tickValues = Array();
    var i, l;
    for (i = 0, l = this.model.page_total(); i < l; i++ ) {
      tickValues.push((1 / this.ratio) * i);
    }

    // Draw ticks now that we have our ratios
    this.svg.append("g")
      .attr("class", "page-turner-ticks")
      .attr("transform", "translate(0," + height + ")")
      .call(d3.svg.axis()
        .scale(x)
        .orient("bottom")
        .tickValues(tickValues)
        .tickFormat("")
        .tickSize(-height)
      );

    this.brush = d3.svg.brush()
      .x(x)
      .extent([0, 1 / this.ratio])
      .on("brushend", this.move_brush.bind(this))
    ;

    this.brush_g = this.svg.append("g")
        .attr("id", this.elements.brush)
        .call(this.brush)
      .selectAll("rect")
        .attr("height", height)
    ;
  },
}; // END: PTView

/**
 * Page Turner Controller
 * Handles user interactions
 **/
function PTController(model, view) {
  this.model = model;
  this.view = view;
  var self = this;

  this.view.pager_clicked.attach(function(sender, args) {
    self.change_page(args);
  });

  this.view.brush_moved.attach(function(sender, args) {
    self.brush_moved(args);
  });
};

PTController.prototype = {
  get_current_page: function() {
    var queries = window.location.search.substring(1).split('&');
    var i, l;
    for (i = 0, l = queries.length; i < l; i++) {
      var params = queries[i].split('=');
      if (params[0] == 'page') {
        return params[1] - 1; // Because humans count from 1
      }
    }
    return 0;
  },

  change_page: function(args) {
    this.view.hide_pages(this.model.page_range());
    if (args.direction == 'prev') {
      this.model.prev_page();
    }
    if (args.direction == 'next') {
      this.model.next_page();
    }
    this.view.show_pages(this.model.page_range());
    this.view.update_brush();
  },

  brush_moved: function(extent) {
    var i;
    this.model.page.start = this.view.extent_to_page(extent[0]);
    this.model.page.end = this.view.extent_to_page(extent[1]);
    this.view.hide_all_pages();
    this.view.show_pages(this.model.page_range());
  },
}; // END: PTController

(function($) {
  Drupal.behaviors.page_turner = {
    attach: function (context, settings) {
      // We assume here the body text is always the first field
      var content = context.getElementsByTagName('article')[0].getElementsByClassName('field')[0];
      var model = new PTModel(content, settings),
        view = new PTView(model, {
          'article': 'article.node',
          'navbar': 'page-turner-nav',
          'page': {
            'next': 'page-turner-next',
            'prev': 'page-turner-prev',
          },
          'brush': 'page-turner-brush',
          'hidden': 'page-turner-hidden'
        }),
        controller = new PTController(model, view);

      // Initial page hiding
      var cur_page = controller.get_current_page();
      model.current_page(cur_page);
      var i;
      for (i = 0; i < model.page_total(); i++) {
        if (i != cur_page) {
          view.hide_page(i);
        }
      }
      view.draw_brush(cur_page);
    } // END: attach
  }; // END: Drupal.behaviors.page_turner
})(jQuery);
