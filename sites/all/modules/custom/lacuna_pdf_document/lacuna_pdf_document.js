/*
*   This script loads a PDF into the pdf.js demo viewer iframe and
*   provides an interface through which the PDF Annotator plugin
*   can access the document content to enable PDF annotation.
*/

(function() {

    Drupal.behaviors.pdfDocument = {
        attach: function() {

            Drupal.PDFDocument = {}
            Drupal.PDFDocument.loaded = Promise.resolve()
            .then(function() {

                var viewer = document.querySelector('iframe.pdf')
                var viewer_src_url = Drupal.settings.lacuna_pdf_document.viewer_src_url
                var pdf_url = Drupal.settings.lacuna_pdf_document.pdf_url
                viewer.src = viewer_src_url + '?file='
                return new Promise(function(resolve) {
                    
                    viewer.addEventListener('load', function() {

                        Drupal.PDFDocument.PDFJS = viewer.contentWindow.PDFJS
                        Drupal.PDFDocument.PDFViewerApplication = viewer.contentWindow.PDFViewerApplication
                        Drupal.PDFDocument.PDFViewerApplication.open(pdf_url)
                        resolve()
                        
                    })

                })

            })

        }
    }

})()
