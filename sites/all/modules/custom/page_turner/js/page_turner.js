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
    var index, l;

    for (index = 0, l = this.listeners.length; index < l; index += 1) {
      this.listeners[index](this.sender, args);
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
  this.index = 0;
  var chunks = chunk_pages(content, this.settings);
  this.pages = chunks.pages;
  this.breaks = chunks.break_pages;

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
  page: function(page_num) {
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
      this.index = p;
    }
    return this.index;
  },

  next_page: function() {
    if (this.index < this.page_total()) {
      ++this.index;
    }
  },

  prev_page: function() {
    if (this.index > 0) {
      --this.index;
    }
  },

  all_pages: function() {
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
  this.model = model;
  this.elements = elements;
  var _this = this;
  draw_navbar();
  create_events();

  function draw_navbar(elements) {
    // Add our pager elements to DOM
    // Must be done first to bind click events
    var navbar_id = _this.elements.navbar.substring(1);
    $(_this.elements.article).before('<div id="' + navbar_id + '"></div>')
    $(_this.elements.navbar).append('<div id="page-turner-prev" class="page-turner-bar fa fa-3x fa-arrow-left"></div>');

    _this.svg = d3.select(_this.elements.navbar).append("svg");
    _this.navbar = _this.svg
        .attr("width", "90%")
        .attr("height", "100%")
      .append("g")
      .append("rect")
        .attr("id", navbar_id);

    $(_this.elements.navbar).append('<div id="page-turner-next" class="page-turner-bar fa fa-3x fa-arrow-right"></div>');
  }

  function create_events() {
    _this.pager_clicked = new Event(_this);

    // Set up HTML listeners for page prev/next
    $(_this.elements.page_next).click(function () {
      _this.pager_clicked.notify({ direction: 'next' });
    });

    $(_this.elements.page_prev).click(function () {
      _this.pager_clicked.notify({ direction: 'prev' });
    });
  }
}

PTView.prototype = {
  hide_page: function(page_num) {
    // page-turner-hidden class is set in page_turner.css
    $(this.model.page(page_num)).addClass('page-turner-hidden');
  },

  show_page: function(page_num) {
    $(this.model.page(page_num)).removeClass('page-turner-hidden');
  },

  draw_page_number: function(page_num) {

  },

  draw_navbar_markers: function(pages) {
    // Draw markers in navbar for given pages
  },

  move_brush: function(page_num) {
    // Move brush to the current page
  },

  brush_move: function(_this) {
    console.log(_this);
    console.log(_this.brush);
    // var extent = brush.extent();
    // console.log(extent);
    // console.log(_this.brush.extent());
  },

  brush_end: function() {
    // Brush finished moving
    // Snap to a full page
    console.log('brush end');
  },

  draw_brush: function(page_num) {
    // divide navbar into even sections, one per page
    // put brush over page_num
    var navbar_width = parseInt(d3.select(this.elements.navbar).style('width'), 10);
    this.brush = d3.svg.brush()
      .x(d3.scale.linear().range([0, navbar_width]))
      // Set initial extent here
      .on("brush", this.brush_move(this))
      .on("brushend", this.brush_end(this));
    this.svg.append("g")
        .attr("class", "page-turner-brush")
        .call(this.brush)
      .selectAll("rect")
        .attr("height", parseInt(d3.select(this.elements.navbar).style('height'), 10))
        .attr("width", navbar_width / this.model.page_total())
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
  var _this = this;

  this.view.pager_clicked.attach(function(sender, args) {
    _this.change_page(args);
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
    this.view.hide_page(this.model.current_page());
    if (args.direction == 'prev') {
      this.model.prev_page();
    }
    if (args.direction == 'next') {
      this.model.next_page();
    }
    this.view.show_page(this.model.current_page());
    this.view.move_brush(this.model.current_page());
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
          'navbar': '#page-turner-nav',
          'page_next': '#page-turner-next',
          'page_prev': '#page-turner-prev',
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
