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
    pageBreak: 'page-turner-number'
    annotatorWrapper: 'annotator-wrapper'

  # Initializes the histogram plugin
  pluginInit: ->
    return unless Annotator.supported()
    return unless Annotator.Plugin.Filters # Must have the annotation IDs the filters add

    # Disables Histogram for single-page documents!
    # 11/2/16 by <codymleff@gmail.com> 
    return unless @layout.horizontal

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
    @documentNode = $(@annotator.wrapper).children()[1]
    # First field-item is document body
    @documentNodeList = $(@documentNode).find('.field-item.even').children()

    unless d3? or @d3?
        console.error('d3.js is required to use the histogram plugin')
        return
    else
      @_setupListeners()
      @countPageLengths()

  # Public: Creates a new instance of the Histogram plugin.
  #
  # element - The Annotator element (this is ignored by the plugin).
  # options - An Object literal of options.
  #
  # Returns a new instance of the plugin.
  constructor: (element, options) ->
    super element, options
    @d3 = d3  # We add d3 through Drupal
    @barTextLength = 0
    @barsPerPage = 4
    @barTotal = 0
    @bars = []
    @chart
    @pageTurnerActive = options.page_turner.active
    @duration = 250 # ms for animation time

    if (@pageTurnerActive == true)
      @layout =
        'container': 'page-turner-nav-parent'
        'horizontal': true
    else
      @layout =
        'container': 'article'
        'horizontal': false
        'width': '25'


  # Listens to annotation change events on the Annotator in order to refresh
  # the @annotations collection.
  _setupListeners: ->
    events = [
      'annotationsLoaded', 'annotationCreated',
      'annotationUpdated', 'annotationDeleted'
    ]

    for event in events
      @annotator.subscribe event, @update

    $(window).resize @update
    $(document).bind('annotation-filters-changed', @update)

  isPageBreak: (node) =>
    # don't try on text nodes
    if node.nodeType == Node.ELEMENT_NODE
      return node.classList.contains(@selector.pageBreak)
    return false

  hasPageBreak: (node) =>
    for child in node.childNodes
      return true if @isPageBreak(child)
    return false

  countPageLengths: =>
    length = 0
    @pageLengths = {}
    for node in @documentNodeList
      length += node.textContent.length
      # Because page numbers are inside p elements
      if @hasPageBreak(node)
        @pageLengths[@getPageNumber(node)] = length
        length = 0
    @barTextLength = @pageLengths[@getFirstPageNumber()] / @barsPerPage

  getFirstPageNumber: =>
    # find index of the first defined item; don't assume counting from zero
    for i, page of @pageLengths
      return i

  getPageNumber: (node) =>
    if node.nodeType == Node.ELEMENT_NODE
      pageBreak = node.querySelector('.' + @selector.pageBreak)
      if pageBreak? and pageBreak.dataset.pageNumber?
        return parseInt(pageBreak.dataset.pageNumber, 10)
      if node.dataset.pageNumber?
        return parseInt(node.dataset.pageNumber, 10)
    else
      return null

  getPageLength: (page) =>
    if @pageLengths[page]?
      return @pageLengths[page]
    else
      return 0

  countAnnotation: (node) =>
    if node.classList.contains(@selector.annotation)
      id = parseInt(node.dataset.annotationId, 10)
      if id not in @counted and not node.classList.contains(@selector.hidden)
        @counted.push(id) # don't over-count multi-span annotations
      return true
    return false

  # Wrapper for counting that handles nested elements
  countAnnotations: (node) =>
    if node.nodeType == Node.ELEMENT_NODE
      @countAnnotation(node)
      if node.hasChildNodes()
        for child in node.childNodes
          @countAnnotations(child)

  # Calculate the bars per node based on number of annotations
  assignBarsPerNode: (node, length = 0) =>
    for child in node.childNodes
      length += child.textContent.length
      if length >= @barTextLength and @barTextLength > 0
        totalBars = Math.floor(length / @barTextLength) # how many bars should we have?
        length = length % @barTextLength # save remainder for next cycle
        if @counted.length > 0
          @bars.push(@counted.length)
          totalBars--
        while totalBars-- # fill in remaining bars with zeros
          @bars.push(0)
        @counted = []
      @countAnnotations(child)
    return length

  # Loop through all nodes and calculate annotation density
  calculateDensity: (nodes) =>
    length = 0
    @counted = []
    if @pageTurnerActive
      @barTextLength = @getPageLength(@getFirstPageNumber()) / @barsPerPage
    for node in nodes
      length = @assignBarsPerNode(node, length) # update with any left-over length
      if @pageTurnerActive and @hasPageBreak(node)
        page = @getPageNumber(node)
        @barTextLength = @getPageLength(page + 1) / @barsPerPage
    while @bars.length < @barTotal
      @bars.push(0) # fill the end if needed

  calculateDimensions: (node) =>
    @layout.length = node.textContent.length;
    if @layout.horizontal
      # Firefox returns 'undefined' if we try offsetWidth here
      @layout.width = document.getElementById(@layout.container).getBoundingClientRect().width
      @layout.height = document.getElementById(@selector.pageTurner).offsetHeight   # assume page turner
    else
      @layout.height = document.getElementsByClassName(@selector.annotatorWrapper)[0].clientHeight # keep in viewport
      # [0][0] because d3 likes arrays almost as much as Drupal
      d3.select(@histogramContainer[0][0].parentNode)
        .attr('width', @layout.width)
        .attr('height', @layout.height)
        .style('float', 'left')
        .style('padding-left', '5px')
        .style('top', '3em')

  setBarDimensions: (length) =>
    # Get the length of only the document text, not the annotations
    @barTextLength = length / @barTotal
    if @layout.horizontal
      # Calculate number of bins for annotations
      @barTotal = $('.page-turner-ticks .tick').length # try to find page turner breaks first
      if !@barTotal?
        @barTotal = Math.ceil(length / @layout.width)
      else
        @pageTurnerActive = true
        @barTotal = @barTotal * @barsPerPage # because we want more than 1 bar per page
    else
      @barTotal = 20

  updateHorizontalChart: (histogram) =>
    barWidth = @layout.width / @bars.length
    height = d3.scale.linear().domain([0, d3.max(@bars)]).range([0, @layout.height])
    histogram.attr( 'width', barWidth )
      .transition().duration(@duration)
      .attr( 'height', (d) => return height(d) )
      .attr( 'x', (d, i) => return barWidth * i )
      .attr( 'y', (d) => return @layout.height - height(d) )
      .style( 'fill', (d) => @barColors(d) )

  updateVerticalChart: (histogram) =>
    barHeight = @layout.height / @barTotal
    width = d3.scale.linear().domain([0, d3.max(@bars)]).range([0, @layout.width])
    histogram.attr( 'width', (d) => return width(d) )
      .transition().duration(@duration)
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
  update: () =>
    return unless d3?
    @bars = []  # reset
    @calculateDimensions(@documentNode)
    @setBarDimensions(@documentNode.textContent.length)  # only on init; doesn't change
    @calculateDensity(@documentNodeList)
    @updateChart()
