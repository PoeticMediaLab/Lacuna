/**
 * Page Turner hides/shows parts of a node
 * based on settings about character length
 *
 * Mike Widner <mikewidner@stanford.edu>
 *
 **/

/******
 *
 * Some light weight MVC to avoid problems as complexity grows
 * @see https://alexatnet.com/articles/model-view-controller-mvc-javascript
 *
 * Using jQuery events for Observer
 * Events published:
 *  page-turner-page-changed
 *    Returns {start: NUM, end: NUM}
 *
 *  page-turner-pager-clicked
 *    Returns {direction: prev|next}
 *
 *  page-turner-brush-moved
 *    Returns d3.brush.extent()
 *
 * Events subscribed to:
 *  page-turner-update-pages
 *      Expects {start: NUM, [end: NUM]} (last optional)
 *
 *  annotation-filters-paged
 *    expects annotation object
 *
 ******/

(function ($) {
/**
 * Page Turner Model
 * Handles turning HTML into pages
 * accessing pages by number, etc.
 **/
function PTModel(content, settings) {
    var self = this;
    self.content = content;
    self.settings = settings.page_turner;
    self.settings.page_length = parseInt(self.settings.page_length, 10);  // force int
    var chunks = chunk_pages(content, self.settings);
    self._page_range = {start: 0, end: 1};   // current page range
    self.pages = chunks.pages;        // content of all pages
    self.breaks = chunks.break_pages; // indices of all break pages

    $(document).bind('page-turner-update-pages', function (e, pages) {
        self.page_range(pages);
    });

    function chunk_pages(content, settings) {
        // Divide total content length by page length
        // And look for page break elements
        // Return array of page chunks
        var page = [], // holds all elements in a page
            t_len = 0,  // text length
            pages = [],
            break_pages = [];

        // Get to the real content
        while (content.childElementCount === 1) {
            content = content.childNodes[0];
        }
        content = content.children;

        // Check that the current item is not a break point
        // and that adding it wouldn't go over the text limit
        var all_breaks = Array.prototype.slice.call(document.querySelectorAll(settings.breaks)),
            l = content.length,
            i;
        for (i = 0; i < l; i++) {
            var is_break = all_breaks.indexOf(content[i]) != -1,
                new_len = t_len + content[i].textContent.length;
            if (is_break) {
                if (t_len === 0) {
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
            }
            else if (new_len <= settings.page_length) {
                t_len = new_len;
                page.push(content[i]);
            }
            else if (page.length > 0) {
                // Start a new page
                pages.push(page);
                t_len = content[i].textContent.length;
                page = Array(content[i]);
            }
            else {
                page = Array(content[i]);
                t_len = content[i].textContent.length;
            }
        }
        pages.push(page); // whatever's left over
        return {pages: pages, break_pages: break_pages};
    }  // END: _chunk_pages()
}

PTModel.prototype = {
    get_page: function (page_num) {
        if (page_num > this.page_total()) {
            return this.pages[this.page_total() - 1];
        }
        if (page_num < 0) {
            return this.pages[0];
        }
        return this.pages[page_num];
    },

    current_page: function (p) {
        var diff;
        if (typeof p !== 'undefined') {
            if (p > this.page_total()) {
                p = this.page_total();
            }
            if (p < 0) {
                p = 0;
            }
            diff = p - this._page_range.start;
            this._page_range.start = p;
            this._page_range.end += diff;
            this._page_range = this.validate_page_range(this._page_range);
            $(document).trigger('page-turner-page-changed', this._page_range);
        }
        return this._page_range.start;
    },

    validate_page_range: function (pages) {
        var range,
            total = this.page_total();
        pages.start = parseInt(pages.start, 10);
        if (isNaN(pages.start)) {
            pages.start = 0;
        }
        pages.end = parseInt(pages.end, 10);
        if (isNaN(pages.end)) {
            pages.end = pages.start;
        }
        if (pages.start > pages.end) {
            // swap them!
            var tmp = pages.start;
            pages.start = pages.end;
            pages.end = tmp;
        }
        if (pages.start == pages.end) {
            ++pages.end;
        }
        range = pages.end - pages.start;
        if (pages.start < 0) {
            pages.start = 0;
            pages.end = range;
        }
        if (pages.end > total) {
            pages.start = pages.end - range;
            pages.end = total;
            if (pages.start >= pages.end) {
                pages.start = pages.end - 1;
            }
        }
        return pages;
    },

    next_page: function () {
        var range = this._page_range.end - this._page_range.start;
        this._page_range.start += range;
        this._page_range.end += range;
        this._page_range = this.validate_page_range(this._page_range);
        $(document).trigger('page-turner-page-changed', this._page_range);
    },

    prev_page: function () {
        var range = this._page_range.end - this._page_range.start;
        this._page_range.start -= range;
        this._page_range.end -= range;
        this._page_range = this.validate_page_range(this._page_range);
        $(document).trigger('page-turner-page-changed', this._page_range);
    },

    page_range: function (pages) {
        // Get/set current page range
        if (typeof pages !== 'undefined') {
            var start_only = isNaN(pages.end);
            pages = this.validate_page_range(pages);
            if (start_only) {
                // Allow for just passing start page
                pages.end = pages.start + this._page_range.end - this._page_range.start;
            }
            this._page_range = pages;
            if (start_only && this._page_range.start != pages.start) {
                // Because that's *really* where we were asked to go; just shrink range
                this._page_range.start = pages.start;
            }
            this._page_range = this.validate_page_range(this._page_range);
            $(document).trigger('page-turner-page-changed', this._page_range);
        }
        return this._page_range;
    },

    all_pages: function () {
        // Return all page content
        return this.pages;
    },

    all_breaks: function () {
        // Returns a list of page numbers that are break points
        return this.breaks;
    },

    is_break: function (page_num) {
        return this.breaks.indexOf(page_num) != -1;
    },

    page_total: function () {
        return this.pages.length;
    },

    find_page_that_contains: function (el) {
        var i,
            l = this.page_total();
        for (i = 0; i < l; i++) {
            var j, k;
            for (j = 0, k = this.pages[i].length; j < k; j++) {
                if (el === this.pages[i][j]) {
                    return i;
                }
            }
        }
        return undefined;
    }
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

    self.offset = 0;    // for a y-axis offset
    draw_navbar();
    draw_navbar_ticks();
    draw_page_x_of_y();
    add_page_numbers();
    create_events(); // Must come *after* navbar created for click binding

    // Update view when page numbers in model change
    $(document).bind('page-turner-page-changed', function (e, pages) {
        self.update_brush(pages);
        self.update_pages(pages);
    });

    function draw_navbar() {
        // Add our pager elements to DOM
        // Must be done first so we can bind click events
        var navbar = d3.select(document.getElementsByTagName(self.elements.content)[0].parentElement)
            .insert('div', self.elements.content)
            .attr('id', self.elements.navbar);

        navbar.append('div').attr('id', self.elements.pager.prev.id)
            .classed(self.elements.pager.prev.classes.join(' '), true)
            .style("padding-top", self.offset + "px");
        ;

        self.svg = d3.select('#' + self.elements.navbar).append("svg:svg");

        //  Detect window width for small screens.
        var widthDecimal;
        if (window.innerWidth < 400) widthDecimal = .75;
        else if (window.innerWidth < 540) widthDecimal = .8;
        else if (window.innerWidth < 768) widthDecimal = .83;
        else if (window.innerWidth > 1200) widthDecimal = .9;
        else widthDecimal = .86;

        var width = '' + (widthDecimal * 100) + '%';

        self.navbar_svg = self.svg
            .attr("id", self.elements.navbar_parent)
            .attr("width", width) // Note: affects width calculations
            .attr("height", "100%")
            .append("g")
            .append("rect")
            .attr("id", self.elements.navbar)
            .attr("y", self.offset)
        ;

        navbar.append('div').attr('id', self.elements.pager.next.id)
            .classed(self.elements.pager.next.classes.join(' '), true)
            .style("padding-top", self.offset + "px");

        // Set our sizing variables
        self.navbar.width = parseInt(d3.select('#' + self.elements.navbar).style('width'), 10) * widthDecimal; // svg width = 90%
        self.navbar.height = parseInt(d3.select('#' + self.elements.navbar).style('height'), 10);
        self.navbar.x = d3.scale.linear().range([0, self.navbar.width]);
        self.navbar.ratio = self.model.page_total();
    }

    function draw_page_x_of_y() {
        // Add the "Page X of Y" div
        d3.select('#' + self.elements.pages.loc).insert('div', '#page-turner-nav').attr('id', self.elements.pages.container).append('span').attr('id', self.elements.pages.id);
        d3.select('#' + self.elements.pages.container).append('span').attr('contenteditable', true).attr('id', self.elements.pages.numbers);
        d3.select('#' + self.elements.pages.container).append('span').attr('id', self.elements.pages.total).text(' of ' + self.model.page_total());
    }

    function draw_navbar_ticks() {
        // Draw tick marks in navbar
        // Draw markers for page breaks
        var tickValues = Array();
        var i, l;
        for (i = 0, l = self.model.page_total(); i < l; i++) {
            tickValues.push((1 / self.navbar.ratio) * i);
        }

        // Draw ticks now that we have our ratios
        self.svg.append("g")
            .attr("class", "page-turner-ticks")
            .attr("transform", "translate(0," + (self.navbar.height + self.offset) + ")")
            .call(d3.svg.axis()
                .scale(self.navbar.x)
                .orient("bottom")
                .tickValues(tickValues)
                .tickFormat("")
                .tickSize(-self.navbar.height))
            .selectAll(".tick")
            .classed("page-turner-break", function (d) {
                return self.model.is_break(Math.round(self.navbar.ratio * d));  //  Added Math.round() to account for rounding errors.
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
            div = d3.select(selection[0][selection[0].length - 1]).append('div').classed(self.elements.page_num, true).text(i + 1);
            div[0][0].dataset.pageNumber = i + 1; // add as data value
        }
    }

    function create_events() {
        // Set up HTML listeners for page prev/next
        $('#' + self.elements.pager.next.id).on("click", function () {
            $(document).trigger('page-turner-pager-clicked', {direction: 'next'});
        });

        d3.select('#' + self.elements.pager.prev.id).on("click", function () {
            $(document).trigger('page-turner-pager-clicked', {direction: 'prev'});
        });

        // Turn pages on arrow key presses
        document.addEventListener("keydown", function (event) {
            if (event.defaultPrevented) {
                return; // Should do nothing if the key event was already consumed.
            }
            switch (event.keyIdentifier) {
                case "Left":
                    $(document).trigger('page-turner-pager-clicked', {direction: 'prev'});
                    break;
                case "Right":
                    $(document).trigger('page-turner-pager-clicked', {direction: 'next'});
                    break;
                default:
                    return; // Quit when this doesn't handle the key event.
            }
            event.preventDefault();
        }, true);
    }
}

PTView.prototype = {
    hide_page: function (page_num) {
        d3.selectAll(this.model.get_page(page_num)).classed(this.elements.hidden, true); //.transition().style('opacity', 0);
    },

    show_page: function (page_num) {
        d3.selectAll(this.model.get_page(page_num)).classed(this.elements.hidden, false); //.transition().style('opacity', 1);
    },

    show_pages: function (range) {
        var i;
        for (i = range.start; i < range.end; i++) {
            this.show_page(i);
        }
    },

    hide_pages: function (range) {
        var i;
        for (i = range[0]; i < range[1]; i++) {
            this.hide_page(i);
        }
    },

    hide_all_pages: function () {
        var i, l;
        for (i = 0, l = this.model.page_total(); i < l; i++) {
            this.hide_page(i);
        }
    },

    update_pages: function (pages) {
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

    update_page_numbers: function (pages) {
        var text = 'Page',
            page_numbers;
        var range = pages.end - pages.start > 1;
        if (range) {
            text += 's';
        }
        text += ' ';
        page_numbers = pages.start + 1;  // humans count from 1
        if (range) {
            page_numbers += '–' + pages.end;
        }
        d3.select('#' + this.elements.pages.id).text(text);
        d3.select('#' + this.elements.pages.numbers).text(page_numbers);
    },

    extent_to_page: function (extent) {
        // Convert an extent value to page number
        return Math.round(this.navbar.ratio * extent);
    },

    page_to_extent: function (page_num) {
        // convert a page number to an extent value
        return page_num / this.navbar.ratio;
    },

    snap_extent_to_page_edges: function (extent) {
        // Adjust a given extent to snap to page boundaries
        if (extent[0] == extent[1]) {
            // we want to select at least one page
            return [
                this.page_to_extent(Math.floor(this.navbar.ratio * extent[0])),
                this.page_to_extent(Math.ceil(this.navbar.ratio * extent[1]))
            ];
        }
        return [
            this.page_to_extent(this.extent_to_page(extent[0])),
            this.page_to_extent(this.extent_to_page(extent[1]))
        ];
    },

    animate_brush: function (extent) {
        d3.select('#' + this.elements.brush).transition()
            .call(this.brush.extent(extent));
    },

    update_brush: function (pages) {
        // Model changed, update the brush
        this.animate_brush([
            this.page_to_extent(pages.start),
            this.page_to_extent(pages.end)
        ]);
    },

    move_brush: function () {
        // Brush finished moving, snap to page boundaries, notify
        var extent = this.snap_extent_to_page_edges(this.brush.extent());
        this.animate_brush(extent);
        $(document).trigger('page-turner-brush-moved', [extent]);
    },

    draw_brush: function (page_num, total_pages) {
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
            .attr("y", this.offset)
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

    $(document).bind('page-turner-pager-clicked', function (e, data) {
        self.change_page(data);
    });

    $(document).bind('page-turner-brush-moved', function (e, data) {
        self.brush_moved(data);
    });

    $(document).bind('annotation-filters-paged', function (e, annotation) {
        self.check_if_annotation_visible(annotation);
    });

    // When a user manually enters page numbers
    document.getElementById(this.view.elements.pages.numbers).addEventListener('input', function () {
        var timer = null;
        clearTimeout(timer);
        timer = setTimeout(function () {
            if (this.dataset.running) {
                return;
            }    // prevent an update loop
            this.dataset.running = true;
            self.parse_page_number_input(this);
        }.bind(this), 1000);
        delete this.dataset.running;
    }, false);
}

PTController.prototype = {
    get_current_page: function () {
        var queries = window.location.search.substring(1).split('&'),
            i,
            l;
        for (i = 0, l = queries.length; i < l; i++) {
            var params = queries[i].split('=');
            if (params[0] == 'page') {
                return params[1] - 1; // Because humans count from 1
            }
        }
        return 0;
    },

    change_page: function (args) {
        if (args.direction == 'prev') {
            this.model.prev_page();
        }
        if (args.direction == 'next') {
            this.model.next_page();
        }
    },

    parse_page_number_input: function (el) {
        var value, pages;
        // Strip returns, spaces, and non-numeric or dash characters, replaces hyphen with endash
        value = el.innerHTML.replace(/[\n\r ]/g, '').replace(/(<br ?\/?>)*/g, '').replace(/[^\d-–]/g, '').replace(/-/g, '–');
        pages = value.split('–');
        if (pages.length == 2) {
            pages = this.model.page_range({start: parseInt(pages[0], 10) - 1, end: parseInt(pages[1], 10)});
        } else if (value.match(/^\d+$/)) {
            // Reset the page range to 1, if one is already set
            value = parseInt(value, 10);
            pages = {start: (value - 1), end: value}; // we count from zero
            pages = this.model.page_range(pages);
        } else {
            // do nothing; it's not valid input yet
            return;
        }
        this.view.update_page_numbers(pages);
    },

    brush_moved: function (extent) {
        var pages = {
            'start': this.view.extent_to_page(extent[0]),
            'end': this.view.extent_to_page(extent[1])
        };
        this.model.page_range(pages)
    },

    check_if_annotation_visible: function (annotation) {
        // If invisible, jump to correct page
        var parents = [],
            parent_node = annotation.highlights[0].parentNode;
        while (parent_node) {
            parents.push(parent_node);
            parent_node = parent_node.parentNode;
        }
        var i,
            l = parents.length;
        for (i = 0; i < l; i++) {
            parent_node = parents[i];
            if (parent_node.tagName.toLowerCase() == this.view.elements.content.toLowerCase()) {
                // We've gone high enough; page is currently showing
                break;
            }
            if (parent_node.classList.contains(this.view.elements.hidden)) {
                var page = this.model.find_page_that_contains(parent_node);
                this.model.current_page(page);
                break;
            }
        }
    }
}; // END: PTController

"use strict";
Drupal.behaviors.page_turner = {
    attach: function (context, settings) {
        // We assume here the body text is always the first field
        var content = context.getElementsByTagName('article')[0].getElementsByClassName('field')[0];
        var model = new PTModel(content, settings),
        // Our selectors and ids; should probably make more consistent
            view = new PTView(model, {
                'content': 'article',
                'pages': {
                    'loc': 'content',
                    'container': 'page-turner-pages-container',
                    'id': 'page-turner-pages',
                    'numbers': 'page-turner-pages-numbers',
                    'total': 'page-turner-pages-total'
                },
                'page_num': 'page-turner-number',
                'navbar_parent': 'page-turner-nav-parent',
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
        if (cur_page > 0) {
            model.current_page(cur_page);
        }
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
})(jQuery);
