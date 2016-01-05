#   A plugin for displaying the status of loading annotations on a document.

$ = jQuery

class Annotator.Plugin.Loading extends Annotator.Plugin

    pluginInit: ->
        
        return unless Annotator.supported()
        console.log('hey there from the plugin!')