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
function PTBModel() {
  var self = this;
  self.bookmarks = [];
  self.pages = {};  // {start: 0, end: 1}

  load_bookmarks();
  bind_events();

  function load_bookmarks() {
    // Load all our bookmark data
    $(document).trigger('page-turner-bookmarks-loaded', self.bookmarks);
  }

  function bind_events() {
    // Listen for page turn events and update our model
    $(document).bind('page-turner-page-changed', function(e, pages) {
      self.pages = pages;
      console.log(self.pages);
    });
  }
}

PTBModel.prototype = {
  // admin/user-interface/page-turner/bookmark/add
  add_bookmark: function() {
    // Save a new bookmark
  },

  // admin/user-interface/page-turner/bookmark/remove
  remove_bookmark: function() {
    // Remove the current bookmark
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

  // When bookmarks loaded, draw them; requires navbar to be created first
  // Need to fire in order somehow
  $(document).bind('page-turner-bookmarks-loaded', function(e, bookmarks) {
    self.draw_bookmarks(bookmarks);
  });

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

  function draw_bookmarks(bookmarks) {
    // Draw all bookmarks
    console.log('drawing bookmarks');
  }

  function draw_bookmark_button() {
    $(self.elements.bookmark_button.container).append('<div id="' + self.elements.bookmark_button.id + '">Bookmark</div>');
    $('#' + self.elements.bookmark_button.id).on('click', function (e) {
      $(document).trigger('page-turner-bookmark-toggle', e);
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
    // Bookmark button clicked; toggle state
  },
};

/**
 *
 * Page Turner Bookmarks Controller
 *
 */
function PTBController(model, view) {
  var self = this;
  self.model = model;
  self.view = view;

  $(document).bind('page-turner-bookmark-added');
  $(document).bind('page-turner-bookmark-removed');
  $(document).bind('page-turner-bookmark-toggle', function(e) {console.log('toggle', e);});
}

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
      var model = new PTBModel(),
        view = new PTBView(model, elements),
        controller = new PTBController(model, view);
    } // END: attach
  }; // END: Drupal.behaviors.page_turner_bookmarks
})(jQuery);
