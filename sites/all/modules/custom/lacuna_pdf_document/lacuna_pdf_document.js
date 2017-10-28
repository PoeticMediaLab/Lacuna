/*
*   This script loads a PDF into the pdf.js demo viewer iframe and
*   provides an interface through which the PDF Annotator plugin
*   can access the document content to enable PDF annotation.
*/

(function() {


    /*
    *   References to the PDFJS library and the PDFViewerApplication
    *   inside the iframe.
    */

    var PDFJS, PDFViewerApplication


    /*
    *   Once the page and PDF-rendering iframe have loaded, gathers
    *   references to the PDFJS library and PDFViewerApplication and
    *   loads the content PDF.
    */

    document.addEventListener('DOMContentLoaded', function() {

        var viewer = document.querySelector('iframe.pdf')
        var viewer_src_url = Drupal.settings.lacuna_pdf_document.viewer_src_url
        var pdf_url = Drupal.settings.lacuna_pdf_document.pdf_url
        viewer.src = viewer_src_url + '?file='/* + encodeURIComponent(pdf_url)*/
        viewer.addEventListener('load', function() {

            PDFJS = viewer.contentWindow.PDFJS
            PDFViewerApplication = viewer.contentWindow.PDFViewerApplication
            PDFViewerApplication.open(pdf_url)
            
        })
        
    })

})()
