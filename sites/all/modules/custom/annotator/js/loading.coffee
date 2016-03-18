#   A plugin for displaying the status of loading annotations on a document.

$ = jQuery

class Annotator.Plugin.Loading extends Annotator.Plugin

    constructor: (element) ->

        @element = element


    pluginInit: ->
        
        return unless Annotator.supported()

        spinnerElement = @setupElement()

        $(@element).prepend(spinnerElement)
        
        @annotator.subscribe('annotationsLoaded', ->
            spinnerElement.remove()
        )


    setupElement: ->

        elementHTML = """
            <span id="annotations-loading">
                <i class="fa fa-spinner fa-pulse"></i>
                <span>Loading annotations...</span>
            </span>
        """

        spinnerElement = $(elementHTML)