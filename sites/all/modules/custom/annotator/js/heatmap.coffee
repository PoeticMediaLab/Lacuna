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
    annotation: 'annotator-hl'
    hidden: 'af-annotation-hide'  # Annotation Filter hidden/filtered out annotation

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
    @binSize = 0
    @binTotal = 0
    @bins = []

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

  calculateDimensions: (node) =>
    @layout.length = node.textContent.length;
    if @layout.orientation == 'horizontal'
      @layout.width = @heatmapContainer.offsetWidth
    @layout.height = @heatmapContainer.offsetHeight

  configureBins: (length) =>
    # Get the length of only the document text, not the annotations
    if @layout.orientation == 'horizontal'
    # Calculate number of bins for annotations
      @binTotal = $('.page-turner-ticks .tick').length # try to find page turner breaks first
      if !@binTotal?
        @binTotal = Math.ceil(length / @layout.width)
      else
        @binTotal = @binTotal * 4 # because we want more than 1 bar per page
    @binSize = Math.ceil(length / @binTotal)

  # Calculate the annotation density of a single bin
  calculateDensity: (node, length = 0) =>
    counted = []
    total = 0

    for child in node.childNodes
      length += child.textContent.length
      if length >= @binSize
        @bins.push(total)
        total = 0
        length = 0
      if child.nodeType == Node.ELEMENT_NODE and
          child.classList.contains(@selector.annotation) and not
          child.classList.contains(@selector.hidden)
        if child.hasChildNodes() # overlapping annotations; check them, too
          total += @calculateDensity(child, length)
        id = parseInt(child.dataset.annotationId, 10)
        if id not in counted
          total++
          counted.push(id) # don't over-count multi-span annotations
    return total
#    console.log(@bins)

# Update the heatmap
  updateHeatmap: =>
    return unless d3?
    @bins = []  # reset
    documentNode = $(@annotator.wrapper).children()[1]
    @calculateDimensions(documentNode)
    @configureBins(documentNode.textContent.length)
    console.log(@binSize, @binTotal)
    for node in $(documentNode).find('.field-item.even').children() # First field-item is document body
      @calculateDensity(node)

    console.log(@bins, @bins.length)

