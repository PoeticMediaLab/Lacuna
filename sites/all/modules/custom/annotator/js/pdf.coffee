# Enables PDF annotations

$ = jQuery

class Annotator.Plugin.PDF extends Annotator.Plugin

  pluginInit: ->
    return unless Annotator.supported()
    Drupal.PDFDocument.loaded.then(() ->

      console.log('PDF document loaded and ready for annotation!', Drupal.PDFDocument.PDFViewerApplication)

    )
