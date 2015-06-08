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
  this.breaks = chunks.break_pages; // indices of all break pages

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
        break_pages.push(pages.length);
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
      var diff = p - this.page.start;
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
    return this.breaks;
  },

  is_break: function(page_num) {
    return this.breaks.indexOf(page_num) != -1;
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
  self.brush = {};

  draw_navbar();
  draw_navbar_ticks();

  create_events(); // Must come *after* navbar created

  function draw_navbar(elements) {
    // Add our pager elements to DOM
    // Must be done first so we can bind click events
    var navbar = d3.select(document.getElementsByTagName(self.elements.content)[0].parentElement)
      .insert('div', self.elements.content)
      .attr('id', self.elements.navbar);

    navbar.append('div').attr('id', self.elements.page.prev)
      .classed({'page-turner-bar': true,
                'fa': true,
                'fa-3x': true,
                'fa-arrow-left': true});

    self.svg = d3.select('#' + self.elements.navbar).append("svg");
    self.navbar_svg = self.svg
        .attr("width", "90%") // Note: affects width calculations
        .attr("height", "100%")
      .append("g")
      .append("rect")
        .attr("id", self.elements.navbar);

    navbar.append('div').attr('id', self.elements.page.next)
      .classed({'page-turner-bar': true,
                'fa': true,
                'fa-3x': true,
                'fa-arrow-right': true});

    // Set our sizing variables
    self.navbar.width = parseInt(d3.select('#' + self.elements.navbar).style('width'), 10) * .9; // svg width = 90%
    self.navbar.height = parseInt(d3.select('#' + self.elements.navbar).style('height'), 10);
    self.navbar.x = d3.scale.linear().range([0, self.navbar.width]);
    self.navbar.ratio = self.model.page_total();
  }

  function draw_navbar_ticks() {
    // Draw tick marks in navbar
    // Draw markers for page breaks
    var tickValues = Array();
    var i, l;
    for (i = 0, l = self.model.page_total(); i < l; i++ ) {
      tickValues.push((1 / self.navbar.ratio) * i);
    }

    // Draw ticks now that we have our ratios
    self.svg.append("g")
      .attr("class", "page-turner-ticks")
      .attr("transform", "translate(0," + self.navbar.height + ")")
      .call(d3.svg.axis()
        .scale(self.navbar.x)
        .orient("bottom")
        .tickValues(tickValues)
        .tickFormat("")
        .tickSize(-self.navbar.height))
      .selectAll(".tick")
        .classed("page-turner-break", function (d) {
          return self.model.is_break(self.navbar.ratio * d);
        }.bind(self))
    ;
  }

  function create_events() {
    self.pager_clicked = new Event(self);
    self.brush_moved = new Event(self);   // brush has moved

    // Set up HTML listeners for page prev/next
    d3.select('#' + self.elements.page.next).on("click", function () {
      self.pager_clicked.notify({ direction: 'next' });
    });

    d3.select('#' + self.elements.page.prev).on("click", function () {
      self.pager_clicked.notify({ direction: 'prev' });
    });
  }
}

PTView.prototype = {
  hide_page: function(page_num) {
    // page-turner-hidden class is set in page_turner.css
    d3.selectAll(this.model.get_page(page_num)).classed(this.elements.hidden, true);
  },

  show_page: function(page_num) {
    d3.selectAll(this.model.get_page(page_num)).classed(this.elements.hidden, false);
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

  extent_to_page: function(extent) {
    // Convert an extent value to page number
    return Math.round(this.navbar.ratio * extent);
  },

  page_to_extent: function(page_num) {
    // convert a page number to an extent value
    return page_num / this.navbar.ratio;
  },

  snap_extent_to_page_edges: function(extent) {
    // Adjust a given extent to snap to page boundaries
    if (extent[0] == extent[1]) {
      // we want to select at least one page
      extent[1] += this.navbar.ratio;
    }
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
    // Model changed, update the brush
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

  draw_brush: function(page_num, total_pages) {
    // Draw the brush to given page and range
    this.brush = d3.svg.brush()
      .x(this.navbar.x)
      .extent([this.page_to_extent(page_num),
        (1 / this.navbar.ratio) * total_pages])
      .on("brushend", this.move_brush.bind(this))
    ;

    this.svg.append("g")
        .attr("id", this.elements.brush)
        .call(this.brush)
      .selectAll("rect")
        .attr("height", this.navbar.height)
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

(function() {
  Drupal.behaviors.page_turner = {
    attach: function (context, settings) {
      // We assume here the body text is always the first field
      var content = context.getElementsByTagName('article')[0].getElementsByClassName('field')[0];
      var model = new PTModel(content, settings),
        view = new PTView(model, {
          'content': 'article',
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
      var i, l;
      for (i = 0, l = model.page_total(); i < l; i++) {
        if (i != cur_page) {
          view.hide_page(i);
        }
      }
      var range = model.page_range();
      view.draw_brush(cur_page, range[1] - range[0]);
    } // END: attach
  }; // END: Drupal.behaviors.page_turner
})();
