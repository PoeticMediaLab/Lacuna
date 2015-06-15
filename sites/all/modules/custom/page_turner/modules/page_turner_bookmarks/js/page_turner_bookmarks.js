/**
 *
 * Add/remove bookmarks to a page
 * Add/remove bookmark icons to the Page Turner navbar
 *
 * Mike Widner <mikewidner@stanford.edu>
 *
 **/

/**
 *
 * Uses jQuery events
 *
 * Events:
 *  page-turner-bookmark-loaded
 *
 *  page-turner-bookmark-clicked
 *
 *  page-turner-bookmark-added
 *
 *  page-turner-bookmark-removed
 *
 **/

/**
 *
 * Page Turner Bookmarks Model
 *
 */
function PTBModel(bookmarks) {
    var self = this;
    self.bookmarks = bookmarks;
    self.pages = {start: 0, end: 1};  // Default starting values

    // Listen for page turn events and update our model
    $(document).bind('page-turner-page-changed', function(e, pages) {
        self.pages = pages;
        console.log(self.pages);
    });

    $(document).bind('page-turner-bookmark-added', function(e, pages) {
        self.bookmarks.push(pages);
    });
    console.log(self);
}

PTBModel.prototype = {
    is_bookmarked: function() {
    // return true if current page range is bookmarked
        var i, l;
        for (i = 0, l = this.bookmarks.length; i < l; i++) {
            if (this.bookmarks[i].start === this.pages.start &&
                this.bookmarks[i].end === this.pages.end) {
                return true;
            }
        }
        return false;
    },

    add_bookmark: function() {
    // Save a new bookmark w/ current page range
    },

    remove_bookmark: function() {
    // Remove bookmark from current page range
    },
};

/**
 *
 * Page Turner Bookmarks View
 *
 */
function PTBView(model, elements) {
  var self = this;
  self.model = model;
  self.elements = elements;

  draw_elements(elements);

  self.navbar = $('#' + self.elements.navbar.id);

  // When a bookmark is clicked
  $('#' + self.elements.bookmark.id).on('click', function (e) {
      $(document).trigger('page-turner-bookmark-clicked', e);
    });

  // When a bookmark is added
  $('#' + self.elements.bookmark_add.id).on('click', function (e) {
      $(document).trigger('page-turner-bookmark-added', e);
    });

  // When a bookmark is removed
  $('#' + self.elements.bookmark_remove.id).on('click', function (e) {
      $(document).trigger('page-turner-bookmark-removed', e);
    });

  function draw_bookmarks() {
    // Draw all bookmarks
  }

  function draw_bookmark_button() {
    // TODO: Load with correct button text
    $(self.elements.bookmark_button.container).append('<span id="' + self.elements.bookmark_button.id + '">Bookmark</span>');
    $("#" + self.elements.bookmark_button.id).on("click", function (e) {
      $("#" + self.elements.bookmark_button.id).trigger("page-turner-bookmark-toggled", e);
    });
  }

  function draw_elements() {
    // Draw all our necessary elements
    // 1. Draw toggle button
    //    a. Set click event
    draw_bookmark_button();

    // 2. Draw all loaded bookmarks in navbar
    //    a. Set hover events for each bookmark
    //    b. Set click events
    draw_bookmarks();
    // 3. Set toggle button state according to whether current page is bookmarked
    //    a. If a change, notify model
  }
}

PTBView.prototype = {
  toggle_bookmark: function() {
    // Bookmark button clicked; toggle view text
  },
};

/**
 *
 * Page Turner Bookmarks Controller
 *
 */
function PTBController(model, view, routes) {
    var self = this;
    self.model = model;
    self.view = view;
    self.routes = routes;

    $(document).bind('page-turner-bookmark-add', function (event) { self.bookmark_add(event) });
    $(document).bind('page-turner-bookmark-remove', function (event) { self.bookmark_remove(event) });
    $("#" + self.view.elements.bookmark_button.id).bind('page-turner-bookmark-toggled', function (event) { self.bookmark_toggle(event) });
}

PTBController.prototype = {
    bookmark_toggle: function(event) {
        console.log('bookmark toggled', event);
        if (this.model.is_bookmarked()) {
            this.bookmark_remove();
        } else {
            this.bookmark_add();
        }
    },

    bookmark_add: function() {
        // PUT data via AJAX
        $.ajax({url: this.routes.add,
            type: 'POST',
            data: {
                path: location.pathname.replace(this.routes.root, ''),
                pages: this.model.pages
            },
            context: this,
            success: function (data) {
                console.log('success', data);
            }
        });
    },

    bookmark_remove: function() {
        // PUT delete request via AJAX
    }
};

(function($) {
  Drupal.behaviors.page_turner_bookmarks = {
    attach: function (context, settings) {
        var elements = {
            'bookmark' :
            {
              'id': 'page-turner-bookmark',
              'classes' :
              [ 'page-turner-bookmark',
                'fa',
                'fa-bookmark-o'
              ]
            },
            'bookmark_add' : {
              'id' : '',
            },
            'bookmark_remove' : {
              'id' : '',
            },
            'bookmark_button' : {
              'id' : 'page-turner-bookmark-button',
              'container' : 'section.region-sidebar-second'
            },
            'bookmark_toggle' :
            {
              'id' : 'page-turner-bookmark-toggle',
            },
            'navbar' : {
              'id' : 'page-turner-nav',
            },
        };
        // Our AJAX route calls
        var routes = {};
        routes.root = settings.basePath;
        routes.base = routes.root + 'admin/user-interface/page-turner/bookmark/';
        routes.load = routes.base + 'list/';
        routes.add = routes.base + 'add';
        routes.remove = routes.base + 'remove/';

        var model = new PTBModel(settings.page_turner_bookmarks);
        var view = new PTBView(model, elements);
        var controller = new PTBController(model, view, routes);
    } // END: attach
  }; // END: Drupal.behaviors.page_turner_bookmarks
})(jQuery);
