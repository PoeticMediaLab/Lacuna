# Enables PDF annotations

$ = jQuery

class Annotator.Plugin.PDF extends Annotator.Plugin

  pluginInit: ->
    return unless Annotator.supported()
    console.log('PDF annotations enabled!')
