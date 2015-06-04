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
    this._current_page = 1;
    this._pages = Array();
}

PTModel.prototype = {
  init: function() {
    this._chunk_pages();
  },

  _chunk_pages: function() {
    // Divide total content length by page length
    // And look for page break elements
    // Return array of page chunks
    var page = Array(); // holds all elements in a page
    var t_len = 0;  // text length
    var breaks = this._settings.breaks.toLowerCase().split(',');
    var content = this._content;

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
          this._pages.push(page);
          t_len = 0;
          page = Array(content[i]); // Include in the new page
        }
      } else if (new_len <= this._settings.page_length) {
        t_len = new_len;
        page.push(content[i]);
      } else if (page.length > 0) {
        // Start a new page
        this._pages.push(page);
        t_len = content[i].textContent.length;
        page = Array(content[i]);
      }
    }
    this._pages.push(page); // whatever's left over
  },  // END: _chunk_pages()

  page: function(page_num) {
    if (page_num > this._pages.length) {
      return this._pages[this._pages.length - 1];
    }
    if (page_num < 0) {
      return this._pages[0];
    }
    return this._pages[page_num];
  },

  current_page: function(p) {
    if (p) {
      if (p > this.page_total) {
        p = this.page_total
      }
      if (p < 0) {
        p = 0;
      }
      this._current_page = p;
    }
    return this._current_page;
  },

  next_page: function() {},

  prev_page: function() {},

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

  this.page_forward = new Event(this);
  this.page_back = new Event(this);

  var _this = this;
}

PTView.prototype = {
  // Class is set in page_turner.css
  hide_page: function(page_num) {
    $(this._model.page(page_num)).addClass('page-turner-hidden');
  },

  show_page: function(page_num) {
    $(this._model.page(page_num)).removeClass('page-turner-hidden');
  },

  add_pagers: function() {
    // draw the pagers
  },

  draw: function() {
    // Do all my drawin'
    this.add_pagers();
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

  page_forward: function() {
  },

  page_back: function() {
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
        model.init();
        view = new PTView(model, {
            'main': $(content),
            'page_forward': $('#pt_forward'),
            'page_back': $('#pt_back')
          });
        controller = new PTController(model, view);

        // Initial page hiding
        console.log(controller, model, view);
        var cur_page = controller.get_current_page()
        model.current_page(cur_page);
        var i;
        for (i = 0; i < model.page_total(); i++) {
          if (i != cur_page) {
            view.hide_page(i);
          }
        }
        view.draw();
      } // END: main()
    } // END: attach
  }; // END: Drupal.behaviors.page_turner
})(jQuery);
