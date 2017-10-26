(function ($) {
  Drupal.behaviors.pdf = {
    attach: function(context, settings) {
      var info = getAcrobatInfo();
      console.log(info.browser + " " + info.acrobat + " " + info.acrobatVersion);
      var iframe = $('iframe.pdf');
      if (info.acrobat) {
        iframe.each(function(){
          setIframeSrc($(this));
          $(this).attr('src', $(this).text());
        });
      }

      if (!isCanvasSupported()) {
        // pdf.js isn't going to work in this browser--let's try acrobat.
        if (info.acrobat) {
          iframe.each(function(){
            setIframeSrc($(this));
            $(this).attr('src', $(this).text());
          });
        }
        else {
          // Even Acrobat isn't going to work--output a message telling user to upgrade their browser.
          $('<p/>', {
            text: 'Your browser is not capable of displaying a pdf. Please upgrade your browser to view this page as it was intended.',
            'class': 'pdf acrobat-browser-messsage',
          }).replaceAll(iframe);
        }
      }
    }
  };
})(jQuery);

/**
 * Detect browser support for canvas.
 *
 * Canvas support is one of the main things that is needed by pdf.js
 * so detecting this should rule out most of the browsers that aren't
 * going to work.
 *
 * See: http://stackoverflow.com/questions/2745432/best-way-to-detect-that-html5-canvas-is-not-supported
 */
function isCanvasSupported(){
  var elem = document.createElement('canvas');
  return !!(elem.getContext && elem.getContext('2d'));
}

/**
 * Set the iframe's source to be the value that was passed through in the
 * data-src attribute.
 */
function setIframeSrc(e){
  e.attr('src', e.attr('data-src')).removeAttr('data-src');
}
