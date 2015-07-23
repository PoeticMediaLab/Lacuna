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

  # Initializes the heatmap plugin
  pluginInit: ->
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

  # Draw or update the heatmap
  updateHeatmap: =>
    return unless d3?

    # compute dimensions
    if @layout.orientation == 'horizontal'
      @layout.width = @heatmapContainer.offsetWidth
    @layout.height = @heatmapContainer.offsetHeight

    # Get all the visible annotations
    # Note: Filters Plugin hides annotations with the .af-annotation-hide class
    annotations = @annotator.element.find('.annotator-hl:not(.af-annotation-hide)')
    