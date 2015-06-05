/**
 * Page Turner hides/shows parts of a node
 * based on settings about character length
 *
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
  this._sender = sender;
  this._listeners = [];
}

Event.prototype = {
  attach: function(listener) {
    this._listeners.push(listener);
  },
  notify: function(args) {
    var index;

    for (index = 0; index < this._listeners.length; index += 1) {
      this._listeners[index](this._sender, args);
    }
  },
}; // END: Event

/**
 * Page Turner Model
 * Handles turning HTML into pages
 * accessing pages by number, etc.
 **/
function PTModel(content, settings) {
  this._content = content;
  this._settings = settings.page_turner;
  this._current_page = 0;
  this._pages = _chunk_pages(content, this._settings);

  function _chunk_pages(content, settings) {
    // Divide total content length by page length
    // And look for page break elements
    // Return array of page chunks
    var page = Array(); // holds all elements in a page
    var t_len = 0;  // text length
    var breaks = settings.breaks.toLowerCase().split(',');
    var pages = Array();

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
    return pages;
  }  // END: _chunk_pages()
}

PTModel.prototype = {
  page: function(page_num) {
    if (page_num > this.page_total()) {
      return this._pages[page_total() - 1];
    }
    if (page_num < 0) {
      return this._pages[0];
    }
    return this._pages[page_num];
  },

  current_page: function(p) {
    if (p) {
      if (p > this.page_total()) {
        p = this.page_total();
      }
      if (p < 0) {
        p = 0;
      }
      this._current_page = p;
    }
    return this._current_page;
  },

  next_page: function() {
    if (this._current_page < this.page_total()) {
      ++this._current_page;
    }
  },

  prev_page: function() {
    if (this._current_page > 0) {
      --this._current_page;
    }
  },

  all_pages: function() {
    return this._pages;
  },

  page_total: function() {
    return this._pages.length;
  },
}; // END: PTModel

/**
 * Page Turner View
 * Shows, hides pages
 * Draws user interface elements
 **/
function PTView(model, elements) {
  this._model = model;
  this._elements = elements;
  var _this = this;

  // Add our pager elements to DOM
  // Must be done first to bind click events
  var navbar_id = this._elements.nav_bar.substring(1);
  $(this._elements.article).before('<div id="' + navbar_id + '"></div>')
  $(this._elements.nav_bar).append('<div id="page-turner-prev" class="page-turner-bar fa fa-3x fa-arrow-left"></div>');
  $(this._elements.nav_bar).append('<div id="page-turner-next" class="page-turner-bar fa fa-3x fa-arrow-right"></div>');

  this.pager_clicked = new Event(this);

  // Set up HTML listeners for page prev/next
  $(this._elements.page_next).click(function () {
    console.log('next');
    _this.pager_clicked.notify({ direction: 'next' });
  });

  $(this._elements.page_prev).click(function () {
    console.log('prev');
    _this.pager_clicked.notify({ direction: 'prev' });
  });
}

PTView.prototype = {
  hide_page: function(page_num) {
    // page-turner-hidden class is set in page_turner.css
    $(this._model.page(page_num)).addClass('page-turner-hidden');
  },

  show_page: function(page_num) {
    $(this._model.page(page_num)).removeClass('page-turner-hidden');
  },
}; // END: PTView

/**
 * Page Turner Controller
 * Handles user interactions
 **/
function PTController(model, view) {
  this._model = model;
  this._view = view;
  var _this = this;

  this._view.pager_clicked.attach(function(sender, args) {
    _this.change_page(args);
  });
};

PTController.prototype = {
  get_current_page: function() {
    var queries = window.location.search.substring(1).split('&');
    var i;
    for (i = 0; i < queries.length; i++) {
      var params = queries[i].split('=');
      if (params[0] == 'page') {
        return params[1] - 1; // Because humans count from 1
      }
    }
    return 0;
  },

  change_page: function(args) {
    this._view.hide_page(this._model.current_page());
    if (args.direction == 'prev') {
      this._model.prev_page();
    }
    if (args.direction == 'next') {
      this._model.next_page();
    }
    this._view.show_page(this._model.current_page());
  },
}; // END: PTController

(function($) {
  Drupal.behaviors.page_turner = {
    attach: function (context, settings) {
      // Check if we even need to do anything
      if (settings.page_turner.active) {
        // We assume here the body text is always the first field
        var content = context.getElementsByTagName('article')[0].getElementsByClassName('field')[0];
        var page_length = content.innerHTML.length;
        if (page_length >= settings.page_turner.min_length) {
          // Yup! Fire it up!
          main(content, settings);
        }
      }

      // Main loop
      function main(content, settings) {
        var model, view, controller;

        model = new PTModel(content, settings);

        view = new PTView(model, {
            'article': 'article.node',
            'nav_bar': '#page-turner-nav',
            'page_next': '#page-turner-next',
            'page_prev': '#page-turner-prev',
          });

        controller = new PTController(model, view);

        // Initial page hiding
        var cur_page = controller.get_current_page()
        model.current_page(cur_page);
        var i;
        for (i = 0; i < model.page_total(); i++) {
          if (i != cur_page) {
            view.hide_page(i);
          }
        }
      } // END: main()
    } // END: attach
  }; // END: Drupal.behaviors.page_turner
})(jQuery);
