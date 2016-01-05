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

        imageURL = Drupal.settings.basePath + 'sites/all/modules/custom/annotator/images/spinner.gif'

        elementHTML = """
            <span id="annotations-loading">
                <img src="#{imageURL}">
                <span>Loading annotations...</span>
            </span>
        """

        spinnerElement = $(elementHTML)