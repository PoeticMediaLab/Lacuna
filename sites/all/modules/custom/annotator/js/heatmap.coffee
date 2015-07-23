#
# Create a heatmap of annotations
# Update heatmap when annotations filtered
#
# Based loosely on code by @tilgovi
# Updated for Lacuna Stories by Mike Widner <mikewidner@stanford.edu>
#

$ = jQuery
class Annotator.Plugin.Heatmap extends Annotator.Plugin
  # HTML templates for the plugin UI.
  html:
    element: """
             <svg class="annotator-heatmap"
                  xmlns="http://www.w3.org/2000/svg"
                  xmlns:xlink="http://www.w3.org/1999/xlink">
                <defs>
                  <linearGradient id="heatmapGradient"
                                  x1="0%" y1="0%"
                                  x2="0%" y2="100%">
                  </linearGradient>
                  <filter id="heatBlend">
                    <feGaussianBlur stdDeviation="3"><feGaussianBlur>
                  </filter>
                </defs>
                <rect x="0" y="0" width="800px" height="50px"
                      fill="url(#heatmapGradient)"
                      filter="url(#heatBlend)" />
             </svg>
             """ #" coffee-mode font lock bug

    options:
      message: Annotator._t("Sorry, the annotation heatmap failed to load.")

  selector:
    hidden: 'af-annotation-hide'  # Annotation Filter hidden annotation

  # Initializes the heatmap plugin
  pluginInit: ->
    return unless Annotator.Plugin.Filters # Must have the annotation IDs the filters add
    @heatmap = $(@html.element)
    $(@layout.container).prepend(@html.element)

    unless d3? or @d3?
        console.error('d3.js is required to use the heatmap plugin')
    else
      @_setupListeners()
      @updateHeatmap()

  # Public: Creates a new instance of the Heatmap plugin.
  #
  # element - The Annotator element (this is ignored by the plugin).
  # options - An Object literal of options.
  #
  # Returns a new instance of the plugin.
  constructor: (element, options) ->
    super element, options
    @d3 = d3  # We add d3 through Drupal
    @layout = options.layout
    @heatmapContainer = document.querySelector(@layout.container)
    @density = [] # Array for density of annotations
    @ids = [] # Annotation IDs

  # Listens to annotation change events on the Annotator in order to refresh
  # the @annotations collection.
  # TODO: Make this more granular so the entire collection isn't reloaded for
  # every single change.
  _setupListeners: ->
    events = [
      'annotationsLoaded', 'annotationCreated',
      'annotationUpdated', 'annotationDeleted'
    ]

    for event in events
      @annotator.subscribe event, @updateHeatmap

    $(window).resize @updateHeatmap
    $(document).bind('annotation-filters-changed', @updateHeatmap)

  # Calculate the annotation density for the heatmap
  calculateDensity: (annotations) =>
    @density = [] # reset

  # If it's a hidden annotation, don't include it
  skipHidden: (annotation) ->
    return annotation unless annotation.classList.contains(@selector.hidden)

  # Draw or update the heatmap
  updateHeatmap: =>
    return unless d3?

    # compute dimensions
    if @layout.orientation == 'horizontal'
      @layout.width = @heatmapContainer.offsetWidth
    @layout.height = @heatmapContainer.offsetHeight

    annotations = document.querySelectorAll(".annotator-hl:not(.#{@selector.hidden})")
    annotations = Array.prototype.slice.call(annotations) # convert from NodeList to Array
    console.log(annotations)
    # An annotation may comprise multiple spans, but they'll all have the same ID
    # Thanks to the annotation filters plugin
#    annotations.reduce((prev, current) =>
#      @ids = []
#      console.log(prev)
#      if prev.id in @ids
#        console.log('found', id)
#      else
#        @ids.push[prev.id]
#      for className in prev.classList
#        id = className.match(/^annotation-(\d+)$/)
#        if id?
#          console.log(id)
##        console.log(prev.classList)
##        console.log(current.classList)
#    , [])

#    visible = annotations.map(@skipHidden)
#    console.log(visible)
#    data = @calculateDensity(visible)
    # Get all the visible annotations
    # Note: Filters Plugin hides annotations with the .af-annotation-hide class
#    console.log(annotations)