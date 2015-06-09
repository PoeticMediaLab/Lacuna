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
  var self = this;
  self.content = content;
  self.settings = settings.page_turner;
  var chunks = chunk_pages(content, self.settings);
  self.page = {start: 0, end: 1};   // current page range
  self.pages = chunks.pages;        // content of all pages
  self.breaks = chunks.break_pages; // indices of all break pages

  self.page_changed = new Event(self);

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
      this.page_changed.notify({start: this.page.start, end: this.page.end});
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
    this.page_changed.notify({start: this.page.start, end: this.page.end});
  },

  prev_page: function() {
    var range = this.page.end - this.page.start;
    this.page.start -= range;
    this.page.end -= range;
    if (this.page.start < 0) {
      this.page.start = 0;
      this.page.end = range;
    }
    this.page_changed.notify({start: this.page.start, end: this.page.end});
  },

  page_range: function() {
    // Return current page range
    return {'start': this.page.start, 'end': this.page.end};
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
  self.pages = {};  // current page(s)

  draw_navbar();
  draw_navbar_ticks();
  add_page_numbers();

  create_events(); // Must come *after* navbar created for click binding

  // Update view when page numbers in model change
  self.model.page_changed.attach(
    function(sender, pages) {
      self.update_brush(pages);
      self.update_pages(pages);
    });

  function draw_navbar(elements) {
    // Add our pager elements to DOM
    // Must be done first so we can bind click events
    var navbar = d3.select(document.getElementsByTagName(self.elements.content)[0].parentElement)
      .insert('div', self.elements.content)
      .attr('id', self.elements.navbar);

    navbar.append('div').attr('id', self.elements.pager.prev.id)
      .classed(self.elements.pager.prev.classes.join(' '), true);

    self.svg = d3.select('#' + self.elements.navbar).append("svg");
    self.navbar_svg = self.svg
        .attr("width", "90%") // Note: affects width calculations
        .attr("height", "100%")
      .append("g")
      .append("rect")
        .attr("id", self.elements.navbar);

    navbar.append('div').attr('id', self.elements.pager.next.id)
      .classed(self.elements.pager.next.classes.join(' '), true);

    // Add the "Page X of Y" div
    d3.select('#' + self.elements.pages.loc).append('div').attr('id', self.elements.pages.id);

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

  function add_page_numbers() {
    // Add page numbers at the bottom of every page
    var i, l;
    for (i = 0, l = self.model.page_total(); i < l; i++) {
      var selection = d3.selectAll(self.model.get_page(i));
      // selectAll returns an array of arrays
      // but we'll only get one result for each page, cuz they're unique
      d3.select(selection[0][selection[0].length - 1]).append('div').classed(self.elements.page_num, true).text(i + 1);
    }
  }

  function create_events() {
    self.pager_clicked = new Event(self);
    self.brush_moved = new Event(self);   // brush has moved

    // Set up HTML listeners for page prev/next
    d3.select('#' + self.elements.pager.next.id).on("click", function () {
      self.pager_clicked.notify({ direction: 'next' });
    });

    d3.select('#' + self.elements.pager.prev.id).on("click", function () {
      self.pager_clicked.notify({ direction: 'prev' });
    });
  }
}

PTView.prototype = {
  hide_page: function(page_num) {
    d3.selectAll(this.model.get_page(page_num)).classed(this.elements.hidden, true); //.transition().style('opacity', 0);
  },

  show_page: function(page_num) {
    d3.selectAll(this.model.get_page(page_num)).classed(this.elements.hidden, false); //.transition().style('opacity', 1);
  },

  show_pages: function(range) {
    var i;
    for (i = range.start; i < range.end; i++) {
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

  update_pages: function(pages) {
    var i, l;
    for (i = 0, l = this.model.page_total(); i < l; i++) {
      if (i < pages.start || i > pages.end - 1) {
        this.hide_page(i);
      } else {
        this.show_page(i);
      }
    }
    this.update_page_numbers(pages);
  },

  update_page_numbers: function(pages) {
    var text = 'Page';
    var range = pages.end - pages.start > 1;
    if (range) {
      text += 's'
    }
    text += ' ';
    text += pages.start + 1;  // humans count from 1
    if (range) {
      text += '–' + pages.end;
    }
    text += ' of ' + this.model.page_total();
    d3.select('#' + this.elements.pages.id).text(text);
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
      return [
        this.page_to_extent(Math.floor(this.navbar.ratio * extent[0])),
        this.page_to_extent(Math.ceil(this.navbar.ratio * extent[1]))
      ]
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

  update_brush: function(pages) {
    // Model changed, update the brush
    this.animate_brush([
      this.page_to_extent(pages.start),
      this.page_to_extent(pages.end)
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
    // this.view.hide_pages(this.model.page_range());
    if (args.direction == 'prev') {
      this.model.prev_page();
    }
    if (args.direction == 'next') {
      this.model.next_page();
    }
    // this.view.show_pages(this.model.page_range());
  },

  brush_moved: function(extent) {
    // TODO: Refactor to use notifications instead of direct calls
    // for consistency, y'know
    this.model.page.start = this.view.extent_to_page(extent[0]);
    this.model.page.end = this.view.extent_to_page(extent[1]);
    var pages = this.model.page_range()
    this.view.update_pages(pages);
    this.view.update_page_numbers(pages);
  },
}; // END: PTController

(function() {
  Drupal.behaviors.page_turner = {
    attach: function (context, settings) {
      // We assume here the body text is always the first field
      var content = context.getElementsByTagName('article')[0].getElementsByClassName('field')[0];
      var model = new PTModel(content, settings),
      // Our selectors and ids; should probably make more consistent
        view = new PTView(model, {
          'content': 'article',
          'pages': {
            'loc': 'navigation',
            'id': 'page-turner-pages'
          },
          'page_num': 'page-turner-number',
          'navbar': 'page-turner-nav',
          'pager': {
            'next': {
              'id': 'page-turner-next',
              'classes': ['page-turner-pager', 'fa', 'fa-arrow-right']
            },
            'prev': {
              'id': 'page-turner-prev',
              'classes': ['page-turner-pager', 'fa', 'fa-arrow-left']
            },
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
      view.draw_brush(cur_page, range.end - range.start);
      view.update_page_numbers(range);
    } // END: attach
  }; // END: Drupal.behaviors.page_turner
})();
