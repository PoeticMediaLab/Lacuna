#
# Create a heatmap of annotations
# Update heatmap when annotations filtered
#
# Based (very) loosely on code by @tilgovi
# Initial d3 histogram code by Rhea Pokorny
# Updated for Lacuna Stories by Mike Widner <mikewidner@stanford.edu>
#

$ = jQuery

class Annotator.Plugin.Heatmap extends Annotator.Plugin
  selector:
    annotation: 'annotator-hl'
    hidden: 'af-annotation-hide'  # Annotation Filter hidden/filtered out annotation
    heatmap: 'annotation-heatmap'
    bar: 'annotation-heatmap-bar'
    pageTurner: 'page-turner-nav'

  # Initializes the heatmap plugin
  pluginInit: ->
    return unless Annotator.supported()
    return unless Annotator.Plugin.Filters # Must have the annotation IDs the filters add

    d3.select('#' + @layout.containerID).insert('svg:svg', ':first-child').append('g').attr('id', @selector.heatmap)
    @heatmapContainer = d3.select('#' + @selector.heatmap)

    unless d3? or @d3?
        console.error('d3.js is required to use the heatmap plugin')
        return
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
    @barWidth = 0
    @barTotal = 0
    @bars = []
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
    if @layout.horizontal
      @layout.width = document.getElementById(@layout.containerID).offsetWidth
    # Try for the page turner height first, then fall back to container
    @layout.height = document.getElementById(@selector.pageTurner).offsetHeight or document.getElementById(@layout.containerID).offsetHeight
    @heatmapContainer.style('width', @layout.width).style('height', @layout.height)

  configureBars: (length) =>
    # Get the length of only the document text, not the annotations
    if @layout.horizontal
    # Calculate number of bins for annotations
      @barTotal = $('.page-turner-ticks .tick').length # try to find page turner breaks first
      if !@barTotal?
        @barTotal = Math.ceil(length / @layout.width)
      else
        @barTotal = @barTotal * 4 # because we want more than 1 bar per page
    # NOTE: binTotal is just a suggestion
    @barWidth = Math.floor(length / @barTotal)

  # Calculate the annotation density of a node
  calculateDensity: (node, length = 0, overlap = false) =>
    counted = []
    total = 0
    for child in node.childNodes
      length += child.textContent.length unless overlap # length already accounted for
      if length >= @barWidth
        if total > 0
          @bars.push(total)
        else
          # fill the empty bins
          for i in [0..Math.ceil(length / @barWidth)]
            @bars.push(0)
        total = 0
        length = 0
        counted = []
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
    if d3.max(@bars) > 10
      colors = d3.scale.linear()
        .domain([0, 2, 5, 10, d3.max(@bars)])
        .range(['#f1eef6','#bdc9e1','#74a9cf','#2b8cbe','#045a8d'])
    else
      colors = d3.scale.linear()
        .domain([0, d3.max(@bars)])
        .range(['#2b8cbe','#045a8d'])

    y = d3.scale.linear()
      .domain([0, d3.max(@bars)])
      .range([0, @layout.height])

    barWidth = @layout.width / @bars.length

    heatmap = @heatmapContainer.selectAll("rect.#{@selector.bar}")
      .data(@bars)

    heatmap.exit().remove() # remove stale bars

    heatmap.enter().append('rect')
      .style('fill', colors)
      .classed(@selector.bar, true)

    heatmap.attr('width', barWidth)
      .attr('x', (d, i) =>
        return barWidth * i
      )
      .attr('height', (d) =>
        return y(d)
      )
      .attr('y', (d) =>
        return @layout.height - y(d)
      )

  # Update the heatmap
  update: =>
    return unless d3?
    @bars = []  # reset
    documentNode = $(@annotator.wrapper).children()[1]
    @calculateDimensions(documentNode)
    @configureBars(documentNode.textContent.length)
    for node in $(documentNode).find('.field-item.even').children() # First field-item is document body
      @calculateDensity(node)
    console.log(@bars, @bars.length, @barTotal)
    @updateChart()
