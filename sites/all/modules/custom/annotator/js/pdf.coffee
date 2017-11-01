# Enables PDF annotations

$ = jQuery

class Annotator.Plugin.PDF extends Annotator.Plugin

  pluginInit: ->
    return unless Annotator.supported()
    Drupal.PDFDocumentView.loaded.then(->
      console.log(Drupal.PDFDocumentView.pdfPages)
    )

