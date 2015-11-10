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
 *  page-turner-update-pages
 *
 *  Events subscribed to:
 *      page-turner-page-changed
 *
 * Mike Widner <mikewidner@stanford.edu>
 *
 **/

(function($) {
/**
 *
 * Page Turner Bookmarks Model
 *
 */
function PTBModel(bookmarks) {
    var self = this;
    self.bookmarks = bookmarks || []; // array of start pages
    self.page = 0;  // Default starting page

    self.bookmarks.forEach(function (element, index, array) {
        // Ensure our page numbers are integers, not strings
        array[index] = parseInt(element, 10);
    });
    // Listen for page turn events and update our model
    $(document).bind('page-turner-page-changed', function(e, pages) {
        self.page = pages.start;
    });

    $(document).bind('page-turner-bookmark-added', function(e, page) {
        self.bookmarks.push(page);
    });
}

PTBModel.prototype = {
    get_bookmarks: function() {
        return this.bookmarks;
    },

    find_bookmark: function(start) {
        return
        var i, l;
        for (i = 0, l = this.bookmarks.length; i < l; i++) {
            if (this.bookmarks[i] === start) {
                return this.bookmarks[i];
            }
        }
        return false;
    },

    is_bookmarked: function(page) {
        // return true if current/given page is bookmarked
        if (typeof page === 'undefined') {
            page = this.page;
        }
        return this.bookmarks.indexOf(page) > -1;
    },

    remove_bookmark: function(page) {
        // Remove bookmark for current or given page range
        this.bookmarks.splice(this.bookmarks.indexOf(page), 1);
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

    $(document).bind('page-turner-bookmark-clicked', function (e, page) {
        self.page_bookmarked(true);
    });

    $(document).bind('page-turner-bookmark-removed', function (e, page) {
        self.remove_bookmark(page);
        self.page_bookmarked(false);
    });

    $(document).bind('page-turner-bookmark-added', function (e, page) {
        self.add_bookmark(page);
        self.page_bookmarked(true);
    });

    $(document).bind('page-turner-page-changed', function (e, pages) {
       self.page_bookmarked(self.model.is_bookmarked(pages.start));
    });

    function draw_bookmarks() {
        // Draw all bookmarks
        self.model.get_bookmarks().forEach(function(page) {
            this.add_bookmark(page);
        }.bind(self));
    }

    function draw_bookmark_button() {
        $(self.elements.bookmark_button.container)
            .append('<span id="' + self.elements.bookmark_button.id +
            '" class="' + self.elements.bookmark_button.classes.join(' ') +
            '"></span>');
        self.page_bookmarked(self.model.is_bookmarked());
        $("#" + self.elements.bookmark_button.id).on("click", function (e) {
            $("#" + self.elements.bookmark_button.id).trigger("page-turner-bookmark-toggled", e);
        });
    }

    function draw_elements() {
        draw_bookmark_button();
        $('#' + self.elements.navbar.parent).attr('height', '150%');    // give us some room!
        draw_bookmarks();
    }
}

PTBView.prototype = {
    page_bookmarked: function(active) {
        if (active) {
            $('#' + this.elements.bookmark_button.id)
                .text(' Remove Bookmark')   // Space for bookmark icon
                .removeClass(this.elements.bookmark_add)
                .addClass(this.elements.bookmark_remove);
        } else {
            $('#' + this.elements.bookmark_button.id)
                .text(' Place Bookmark')
                .removeClass(this.elements.bookmark_remove)
                .addClass(this.elements.bookmark_add);
        }
    },

    remove_bookmark: function(page) {
        // Remove bookmark icon from page range
        $('#' + this.elements.bookmark.id + page).remove();
    },

    add_bookmark: function(page) {
        // draw bookmark icon on page ranges
        // TODO: refactor to use jQuery, not d3 (no need to mix)
        // TODO: refactor so attributes aren't hard-coded
        d3.select($(this.elements.navbar.tick)[page])
            .append('line')
            .attr('id', this.elements.bookmark.id + page)
            .classed(this.elements.bookmark.classes.join(' '), true)
            .attr("x1", 0)
            //.attr("y1", -parseInt(d3.select('#' + this.elements.navbar.id).style('height'), 10))
            .attr("y1", 0)
            .attr("x2", 0)
            .attr("y2", 25)
            .on('click', function(d) { $(document).trigger('page-turner-bookmark-clicked', page); });
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

    $("#" + self.view.elements.bookmark_button.id).bind('page-turner-bookmark-toggled', function () { self.bookmark_toggle() });

    $(document).bind('page-turner-bookmark-clicked', function(event, page) {
        $(document).trigger('page-turner-update-pages', {start: page});
    });
}

PTBController.prototype = {
    bookmark_toggle: function() {
        if (this.model.is_bookmarked()) {
            $(document).trigger('page-turner-bookmark-removed', this.model.page);
            this.bookmark_remove();
        } else {
            this.bookmark_add();
            $(document).trigger('page-turner-bookmark-added', this.model.page);
        }
    },

    bookmark_add: function() {
        // Add bookmark with current page range
        $.ajax({url: this.routes.add,
            type: 'POST',
            data: {
                // Send Drupal the node's path, because it won't know it on POST
                path: location.pathname.replace(this.routes.root, ''),
                page: this.model.page
            },
            context: this,
            success: function (data) {
                // TODO: do something on success, maybe draw new bookmark?
            }
            // TODO: Add a failure option
        });
    },

    bookmark_remove: function(page) {
        // delete bookmark on current page
        $.ajax({url: this.routes.remove,
            type: 'POST',
            data: {
                path: location.pathname.replace(this.routes.root, ''),
                page: this.model.page
            },
            context: this,
            success: function (data) {
                this.model.remove_bookmark(page);
            }
        });
    },
};


Drupal.behaviors.page_turner_bookmarks = {
    attach: function (context, settings) {
        var elements = {
            'bookmark' :
            {
                'id': 'page-turner-bookmark-id-',
                'classes' :
                [
                    'page-turner-bookmark',
                    //'fa',
                    //'fa-bookmark-o'
                ]
            },
            'bookmark_remove' : 'page-turner-bookmark-remove',
            'bookmark_add' : 'page-turner-bookmark-add',
            'bookmark_button' : {
                'id' : 'page-turner-bookmark-button',
                'container' : 'div#page-turner-pages-container',
                'classes': [
                    'page-turner-bookmark-button',
                    //'fa',
                    //'fa-bookmark'
                ],
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
        routes.add = routes.base + 'add';
        routes.remove = routes.base + 'remove/';

        var model = new PTBModel(settings.page_turner_bookmarks);
        var view = new PTBView(model, elements);
        var controller = new PTBController(model, view, routes);
    } // END: attach
}; // END: Drupal.behaviors.page_turner_bookmarks
})(jQuery);
