#
# Create a heatmap of annotations
# Update heatmap when annotations filtered
#
# Based loosely on code by @tilgovi
# Updated for Lacuna Stories by Mike Widner <mikewidner@stanford.edu>
#

$ = jQuery
class Annotator.Plugin.Heatmap extends Annotator.Plugin
  html:
    element: '<g id ="annotation-heatmap"></g>'

  selector:
    annotation: 'annotator-hl'
    hidden: 'af-annotation-hide'  # Annotation Filter hidden/filtered out annotation

  # Initializes the heatmap plugin
  pluginInit: ->
    return unless Annotator.Plugin.Filters # Must have the annotation IDs the filters add
    $(@layout.container).prepend(@html.element)
    @heatmapContainer = $(@html.element)

    unless d3? or @d3?
        console.error('d3.js is required to use the heatmap plugin')
    else
      @_setupListeners()
      @update()

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
    @binSize = 0
    @binTotal = 0
    @bins = []
    @chart

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
      @annotator.subscribe event, @update

    $(window).resize @update
    $(document).bind('annotation-filters-changed', @update)

  calculateDimensions: (node) =>
    @layout.length = node.textContent.length;
    if @layout.orientation == 'horizontal'
      @layout.width = @heatmapContainer.offsetWidth
    @layout.height = @heatmapContainer.offsetHeight
    @chart = d3.select(@heatmapContainer)
      .append('g')
      .attr('id', 'annotation-heatmap')
      .style('width', @layout.width)
      .style('height', @layout.height)

  configureBins: (length) =>
    # Get the length of only the document text, not the annotations
    if @layout.orientation == 'horizontal'
    # Calculate number of bins for annotations
      @binTotal = $('.page-turner-ticks .tick').length # try to find page turner breaks first
      if !@binTotal?
        @binTotal = Math.ceil(length / @layout.width)
      else
        @binTotal = @binTotal * 4 # because we want more than 1 bar per page
    # NOTE: binTotal is just a suggestion
    @binSize = Math.floor(length / @binTotal)

  # Calculate the annotation density of a node
  calculateDensity: (node, length = 0, overlap = false) =>
    counted = []
    total = 0
    for child in node.childNodes
      length += child.textContent.length unless overlap # length already accounted for
      if length >= @binSize
        if total > 0
          @bins.push(total)
        else
          # fill the empty bins
          for i in [0..Math.ceil(length / @binSize)]
            @bins.push(0)
        total = 0
        length = 0
      if child.nodeType == Node.ELEMENT_NODE and
          child.classList.contains(@selector.annotation) and not
          child.classList.contains(@selector.hidden)
        if child.hasChildNodes() # overlapping annotations; check them, too
          total += @calculateDensity(child, length, true)
        id = parseInt(child.dataset.annotationId, 10)
        if id not in counted
          total++
          counted.push(id) # don't over-count multi-span annotations
    return total

  updateChart: =>
    console.log(@chart)

    colors = d3.scale.linear()
      .domain([0, 2, 6, 10, d3.max(@bins)])
      .range(["#eff3ff","#bdd7e7","#6baed6","#3182bd","#08519c"])

    y = d3.scale.linear()
      .domain([0, 2, 6, 10, d3.max(@bins)])
      .range([0, @layout.height / 2, @layout.height, @layout.height * 2, @layout.height * 4])

    heatmap = @chart.selectAll('rect.heatmap')
      .data(@bins)

    barWidth = @layout.width / @bins.length
    heatmap.enter().append('rect')
      .style('fill', colors)
      .classed('heatmap', true)
      .attr('width', barWidth)
      .attr('x', (d, i) =>
        return barWidth * i
      )
    .attr('height', (d) =>
      return y(d)
    )
    .attr('y', (d) =>
      return @layout.height - y(d)
    )

    heatmap.exit().remove()

# Update the heatmap
  update: =>
    return unless d3?
    @bins = []  # reset
    documentNode = $(@annotator.wrapper).children()[1]
    @calculateDimensions(documentNode)
    @configureBins(documentNode.textContent.length)
    for node in $(documentNode).find('.field-item.even').children() # First field-item is document body
      @calculateDensity(node)
    @updateChart()


