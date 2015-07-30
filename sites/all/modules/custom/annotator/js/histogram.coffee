#
# Create a histogram of annotations
# Update histogram when annotations filtered
#
# Based (very) loosely on code by @tilgovi
# Initial d3 histogram code by Rhea Pokorny
# Updated for Lacuna Stories by Mike Widner <mikewidner@stanford.edu>
#

$ = jQuery

class Annotator.Plugin.Histogram extends Annotator.Plugin
  selector:
    annotation: 'annotator-hl'
    hidden: 'af-annotation-hide'  # Annotation Filter hidden/filtered out annotation
    histogramID: 'annotation-histogram'
    histogramWrapperID: 'annotation-histogram-wrapper'
    bar: 'annotation-histogram-bar'
    pageTurner: 'page-turner-nav'

  # Initializes the histogram plugin
  pluginInit: ->
    return unless Annotator.supported()
    return unless Annotator.Plugin.Filters # Must have the annotation IDs the filters add

    if @layout.horizontal
      # Note: horizontal uses an ID, vertical does not >:O
      d3.select('#' + @layout.container).insert('svg:svg', ':first-child')
        .append('g').attr('id', @selector.histogramID)
    else
      # we want a div wrapper for positioning along the side
      d3.select(@layout.container).insert('div', ':first-child').attr('id', @selector.histogramWrapperID)
        .append('svg:svg')
        .append('g').attr('id', @selector.histogramID)
    @histogramContainer = d3.select('#' + @selector.histogramID)

    unless d3? or @d3?
        console.error('d3.js is required to use the histogram plugin')
        return
    else
      @_setupListeners()
      @update()

  # Public: Creates a new instance of the Histogram plugin.
  #
  # element - The Annotator element (this is ignored by the plugin).
  # options - An Object literal of options.
  #
  # Returns a new instance of the plugin.
  constructor: (element, options) ->
    super element, options
    @d3 = d3  # We add d3 through Drupal
    @layout = options.layout
    @barTextLength = 0
    @barTotal = 0
    @bars = []
    @chart
    @pageTurner = false
    @barsPerPage = 4

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

  # Calculate the annotation density of a node
  barsPerNode: (node, length = 0) =>
    counted = []
    total = 0

    if @pageTurner
      maxLength = node.textContent.length  / @barsPerPage # because Page Turner has variable page lengths
    else
      maxLength = @barTextLength

    for child in node.childNodes
      length += child.textContent.length
      if length >= maxLength
        totalBars = Math.floor(length / maxLength) # how many bars should we have?
        length = length % maxLength # save remainder for next cycle
        if total > 0
          @bars.push(total)
          totalBars--
        while totalBars-- # fill in remaining bars with zeros
          @bars.push(0)
        total = 0
        counted = []
      if child.nodeType == Node.ELEMENT_NODE and child.classList.contains(@selector.annotation) and not child.classList.contains(@selector.hidden)
        if child.hasChildNodes() # possible overlapping annotations; count them, too
          for annotation in child.querySelectorAll('.' + @selector.annotation)
            id = parseInt(child.dataset.annotationId, 10)
            if id not in counted
              total++
              counted.push(id)
        id = parseInt(child.dataset.annotationId, 10)
        if id not in counted
          total++
          counted.push(id) # don't over-count multi-span annotations
    return length

  calculateDensity: (nodes) =>
    length = 0
    for node in nodes
      length = @barsPerNode(node, length) # update any left-over length
    while @bars.length < @barTotal
      @bars.push(0) # fill the end if needed

  calculateDimensions: (node) =>
    @layout.length = node.textContent.length;
    if @layout.horizontal
      @layout.width = document.getElementById(@layout.container).offsetWidth
      @layout.height = document.getElementById(@selector.pageTurner).offsetHeight # assume page turner
    else
      @layout.height = window.innerHeight # keep in viewport
      # [0][0] because d3 likes arrays almost as much as Drupal
      d3.select(@histogramContainer[0][0].parentNode)
      .attr('width', @layout.width)
      .attr('height', @layout.height)
      .style('float', 'left')
      .style('padding-left', '5px')

  setBarDimensions: (length) =>
    # Get the length of only the document text, not the annotations
    if @layout.horizontal
      # Calculate number of bins for annotations
      @barTotal = $('.page-turner-ticks .tick').length # try to find page turner breaks first
      if !@barTotal?
        @barTotal = Math.ceil(length / @layout.width)
      else
        @pageTurner = true
        @barTotal = @barTotal * @barsPerPage # because we want more than 1 bar per page
    else
      @barTotal = 20
    @barTextLength = length / @barTotal

  updateHorizontalChart: (histogram) =>
    barWidth = @layout.width / @bars.length
    height = d3.scale.linear().domain([0, d3.max(@bars)]).range([0, @layout.height])
    histogram.attr( 'width', barWidth )
      .attr( 'height', (d) => return height(d) )
      .attr( 'x', (d, i) => return barWidth * i )
      .attr( 'y', (d) => return @layout.height - height(d) )
      .style( 'fill', (d) => @barColors(d) )

  updateVerticalChart: (histogram) =>
    barHeight = @layout.height / @barTotal
    width = d3.scale.linear().domain([0, d3.max(@bars)]).range([0, @layout.width])
    histogram.attr( 'width', (d) => return width(d) )
      .attr( 'height', barHeight )
      .attr( 'x', (d) => return @layout.width - width(d) )
      .attr( 'y', (d, i) => return barHeight * i )
      .style( 'fill', (d) => @barColors(d) )

  updateChart: =>
    @barColors = d3.scale.linear().domain([0, d3.max(@bars)]).range(['white', '#1693A5'])
    histogram = @histogramContainer.selectAll("rect.#{@selector.bar}").data(@bars)
    histogram.exit().remove() # remove stale bars
    histogram.enter().append('rect')
      .classed( @selector.bar, true )
    if @layout.horizontal
      @updateHorizontalChart(histogram)
    else
      @updateVerticalChart(histogram)


  # Update the histogram
  update: =>
    return unless d3?
    @bars = []  # reset
    documentNode = $(@annotator.wrapper).children()[1]
    @calculateDimensions(documentNode)
    @setBarDimensions(documentNode.textContent.length)
    @calculateDensity($(documentNode).find('.field-item.even').children()) # First field-item is document body)
    @updateChart()
