document.addEventListener('DOMContentLoaded', function() {

    var viewer = document.querySelector('iframe.pdf')
    viewer.addEventListener('load', function() {

        var pdfViewerApplication = viewer.contentWindow.PDFViewerApplication

    })
    
})
