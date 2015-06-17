/**
 *
 * Add/remove bookmarks to a page
 * Add/remove bookmark icons to the Page Turner navbar
 *
 * Uses jQuery for event pooling
 *
 * Events published:
 *  page-turner-bookmark-clicked
 *
 *  page-turner-bookmark-added
 *
 *  page-turner-bookmark-removed
 *
 *  page-turner-bookmark-toggled
 *
 * Mike Widner <mikewidner@stanford.edu>
 *
 **/

/**
 *
 * Page Turner Bookmarks Model
 *
 */
function PTBModel(bookmarks) {
    var self = this;
    self.bookmarks = bookmarks || []; // array of page range objects
    self.pages = {start: 0, end: 1};  // Default starting values

    self.bookmarks.forEach(function (element, index, array) {
        // Ensure our page numbers are integers, not strings
        array[index].start = parseInt(element.start, 10);
        array[index].end = parseInt(element.end, 10);
    });
    // Listen for page turn events and update our model
    $(document).bind('page-turner-page-changed', function(e, pages) {
        self.pages = pages;
    });

    $(document).bind('page-turner-bookmark-added', function(e, pages) {
        self.bookmarks.push(pages);
    });

    $(document).bind('page-turner-bookmark-removed', function(e, pages) {
        self.remove_bookmark(pages);
    });
}

PTBModel.prototype = {
    get_bookmarks: function() {
        return this.bookmarks;
    },

    is_bookmarked: function(pages) {
        // return true if current/given page range is bookmarked
        if (typeof pages === 'undefined') {
            pages = this.pages;
        }
        var i, l;
        for (i = 0, l = this.bookmarks.length; i < l; i++) {
            if (this.bookmarks[i].start === pages.start&&
                this.bookmarks[i].end === pages.end) {
                return true;
            }
        }
        return false;
    },

    remove_bookmark: function(pages) {
        // Remove bookmark for current or given page range
        if (typeof pages === 'undefined') {
            pages = this.pages;
        }
        var bookmark = this.find_bookmark(pages);
        this.bookmarks.splice(this.bookmarks.indexOf(bookmark), 1);
    }
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

    $(document).bind('page-turner-bookmark-clicked', function (e, id) {
        self.page_bookmarked(self.model.is_bookmarked(self.id_to_pages(id)));
    });

    $(document).bind('page-turner-bookmark-removed', function (e, pages) {
        self.remove_bookmark(pages);
        self.page_bookmarked(false);
    });

    $(document).bind('page-turner-bookmark-added', function (e, pages) {
        self.add_bookmark(pages);
        self.page_bookmarked(true);
    });

    $(document).bind('page-turner-page-changed', function (e, pages) {
       self.page_bookmarked(self.model.is_bookmarked(pages));
    });

    function draw_bookmarks() {
        // Draw all bookmarks
        self.model.get_bookmarks().forEach(function(pages) {
            this.add_bookmark(pages);
        }.bind(self));
    }

    function draw_bookmark_button() {
        // TODO: Load with correct button text
        $(self.elements.bookmark_button.container).append('<span id="' + self.elements.bookmark_button.id + '" class="' + self.elements.bookmark_button.classes.join(' ') + '"></span>');
        self.page_bookmarked(self.model.is_bookmarked());
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
        $('#' + self.elements.navbar.parent).attr('height', '150%');    // give us some room!
        draw_bookmarks();
        // 3. Set toggle button state according to whether current page is bookmarked
        //    a. If a change, notify model
    }
}

PTBView.prototype = {
    id_to_pages: function(id) {
        // Probably not the best place for this function
        var pages = id.replace(this.elements.bookmark.id, '').split('-');
        return {start: parseInt(pages[0], 10), end: parseInt(pages[1], 10)}
    },

    page_bookmarked: function(active) {
        if (active) {
            $('#' + this.elements.bookmark_button.id).text('Remove Bookmark');
        } else {
            $('#' + this.elements.bookmark_button.id).text('Add Bookmark');
        }
    },
    remove_bookmark: function(pages) {
        // Remove bookmark icon from page range
        $('#' + this.elements.bookmark.id + pages.join('-')).remove();
    },

    add_bookmark: function(pages) {
        // draw bookmark icon on page ranges
        // TODO: refactor to use jQuery, not d3 (no need to mix)?
        d3.select($(this.elements.navbar.tick)[pages.start])
            .append('text')
            .attr('id', this.elements.bookmark.id + pages.start + '-' + pages.end)
            .attr('font-family', 'FontAwesome')
            .attr('font-size','24')
            .attr('cursor', 'pointer')
            .classed(this.elements.bookmark.classes.join(' '), true)
            .text(function(d) { return '\uf097' })
            .attr('y', '20')
            .on('click', function(d) { $(document).trigger('page-turner-bookmark-clicked', this.id); });
    }
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

    $("#" + self.view.elements.bookmark_button.id).bind('page-turner-bookmark-toggled', function (event) { self.bookmark_toggle(event) });

    $(document).bind('page-turner-bookmark-clicked', function(event, id) { self.jump_to_bookmark(id); });
}

PTBController.prototype = {
    bookmark_toggle: function(event) {
        if (this.model.is_bookmarked()) {
            this.bookmark_remove();
            $(document).trigger('page-turner-bookmark-removed', this.model.pages);
        } else {
            this.bookmark_add();
            $(document).trigger('page-turner-bookmark-added', this.model.pages);
        }
    },

    bookmark_add: function() {
        // Add bookmark with current page range
        // Send Drupal the node's path, because it won't know it on POST
        $.ajax({url: this.routes.add,
            type: 'POST',
            data: {
                path: location.pathname.replace(this.routes.root, ''),
                pages: this.model.pages
            },
            context: this,
            success: function (data) {
                // TODO: do something on success, maybe draw new bookmark?
                console.log('success', data);
            }
            // TODO: Add a failure option
        });
    },

    bookmark_remove: function() {
        // delete bookmark with current page range
        $.ajax({url: this.routes.remove,
            type: 'POST',
            data: {
                path: location.pathname.replace(this.routes.root, ''),
                pages: this.model.pages
            },
            context: this,
            success: function (data) {
                // TODO: do something on success, maybe draw new bookmark?
                console.log('success removing', data);
            }
            // TODO: Add a failure option
        });
    },

    jump_to_bookmark: function(id) {
        // Jump to the page range specified by a given bookmark
        // 1. parse id for page start and end
        // 2. trigger page-turner-page-changed event with new range
        $(document).trigger('page-turner-page-changed', this.view.id_to_pages(id));
    }
};

(function($) {
  Drupal.behaviors.page_turner_bookmarks = {
    attach: function (context, settings) {
        var elements = {
            'bookmark' :
            {
              'id': 'page-turner-bookmark-id-',
              'classes' :
              [ 'page-turner-bookmark',
                //'fa',
                //'fa-bookmark-o'
              ]
            },
            'bookmark_remove' : {
                'class': 'page-turner-bookmark-remove'
            },
            'bookmark_button' : {
              'id' : 'page-turner-bookmark-button',
              'container' : 'section.region-sidebar-second',
                'classes': ['lacuna-button']
            },
            'bookmark_toggle' :
            {
              'id' : 'page-turner-bookmark-toggle',
            },
            'navbar' : {
              'id' : 'page-turner-nav',
              'parent': 'page-turner-nav-parent',
                'tick': 'g.tick'
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
