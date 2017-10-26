(function ($) {
  Drupal.behaviors.pdf = {
    attach: function(context, settings) {
      $('.pdf-pages', context).each(function(){
        var file = $(this).attr('file');
        var scale = $(this).attr('scale');
        $(this).html('<div id="pdfContainer" class="pdf-content"/>');

        function loadPdf(pdfPath) {
            var pdf = PDFJS.getDocument(pdfPath);
            pdf.then(renderPdf);
        }

        function renderPdf(pdf) {
            for (var i = 1; i <= pdf.pdfInfo.numPages; i++) {
              pdf.getPage(i).then(renderPage);
            }
        }
        function renderPage(page) {
          var viewport = page.getViewport(scale);
          var $canvas = jQuery("<canvas></canvas>");

          // Set the canvas height and width to the height and width of the viewport
          var canvas = $canvas.get(0);
          var context = canvas.getContext("2d");

          // The following few lines of code set up scaling on the context if we are on a HiDPI display
          var outputScale = getOutputScale(context);
          canvas.width = (Math.floor(viewport.width) * outputScale.sx) | 0;
          canvas.height = (Math.floor(viewport.height) * outputScale.sy) | 0;
          canvas.style.width = Math.floor(viewport.width) + 'px';
          canvas.style.height = Math.floor(viewport.height) + 'px';

          // Append the canvas to the pdf container div
          var $pdfContainer = jQuery("#pdfContainer");
          /*
          $pdfContainer.css("height", canvas.style.height)
                       .css("width", canvas.style.width);
          */
          $pdfContainer.append($canvas);

          //var canvasOffset = $canvas.offset();
          var $textLayerDiv = jQuery("<div />")
            .addClass("textLayer")
            .css("height", canvas.style.height)
            .css("width", canvas.style.width)
            .offset({
              top: canvas.offsetTop,
              left: canvas.offsetLeft
            });

          context._scaleX = outputScale.sx;
          context._scaleY = outputScale.sy;
          if (outputScale.scaled) {
            context.scale(outputScale.sx, outputScale.sy);
          }

          $pdfContainer.append($textLayerDiv);

          page.getTextContent().then(function (textContent) {
            var textLayer = new TextLayerBuilder({
              textLayerDiv: $textLayerDiv.get(0),
              viewport: viewport,
              pageIndex: 0
            });
            textLayer.setTextContent(textContent);

            var renderContext = {
              canvasContext: context,
              viewport: viewport
            };

            page.render(renderContext);
          });
        }

        loadPdf(file);

      });

      var canvases = $('canvas.pdf-thumbnail', context);
      Array.prototype.forEach.call(canvases, function(canvas) {
        var file = canvas.attributes.file.value;
        PDFJS.getDocument(file).then(function(pdf) {
          pdf.getPage(1).then(function(page) {
            var scale = (canvas.attributes.scale) ? canvas.attributes.scale.value : 1;
            var viewport = page.getViewport(scale);
            var context = canvas.getContext('2d');
            canvas.height = viewport.height;
            canvas.width = viewport.width;
            var renderContext = {
              canvasContext: context,
              viewport: viewport
            };
            page.render(renderContext);
          });
        });
      });
    }
  };
})(jQuery);
