/**
 * Page Turner hides/shows parts of a node
 * based on settings about character length
 * Here's where all the display work is done
 *
 **/

 "use strict";

(function($) {
  Drupal.behaviors.page_turner = {
    attach: function (context, settings) {

      var pages = Array();  // Used by multiple functions
      var cur_page = 1;     // current page

      function chunk_pages(content) {
        // Divide total content length by page length
        // And look for page break elements
        // Return array of page chunks
        var page = Array(); // holds all elements in a page
        var t_len = 0;  // text length
        var breaks = settings.page_turner.breaks.toLowerCase().split(',');

        // Get to the real content
        while (content.childElementCount == 1) {
          content = content.childNodes[0];
        }
        content = content.children;

        // Check that the current item is not a break point
        // and that adding it wouldn't go over the text limit
        var l = content.length;
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
          } else if (new_len <= settings.page_turner.page_length) {
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
      }

      // Class set in page_turner.css
      function hide_page(page_num) {
        $(pages[page_num]).addClass('page-turner-hidden');
      }

      function show_page(page_num) {
        $(pages[page_num]).removeClass('page-turner-hidden');
      }

      function get_current_page() {
        // Return the current page, based on query string
        // If none found, we're on the first page
        var queries = window.location.search.substring(1).split('&');
        var i;
        for (i = 0; i < queries.length; i++) {
          var params = queries[i].split('=');
          if (params[0] == 'page') {
            return params[1] - 1; // Because humans count from 1
          }
        }
        return 0;
      }

      function page_back() {

      }

      function page_forward() {

      }

      function add_pagers(content) {
        // Add the pagers and listeners to both sides of page
      }

      if (settings.page_turner.active) {
        // We assume here the body text is always the first field
        var content = context.getElementsByTagName('article')[0].getElementsByClassName('field')[0];
        var page_length = content.innerHTML.length;
        if (page_length >= settings.page_turner.min_length) {
          add_pagers(content);
          pages = chunk_pages(content);
          cur_page = get_current_page();
          var i;
          for (i = 0; i < pages.length; i++) {
            if (i != cur_page) {
              hide_page(i);
            }
          }
        }
      }
    }
  }; // END: Drupal.behaviors.page_turner
})(jQuery);
