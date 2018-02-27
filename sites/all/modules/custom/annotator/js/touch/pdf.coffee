# Adds PDF annotation to Annotator Touch.  Sets up listeners for
# long taps and draggable annotation edges.

# Constants
LONG_TAP_DELAY = 500
INITIAL_ANNOTATION_SIZE = 75

class Annotator.Plugin.Touch.PDF extends Annotator.Delegator

  constructor: (annotator) ->
    @annotator = annotator
    @PDF = @annotator.plugins.PDF
    @Touch = @annotator.plugins.Touch
    @PDF.viewerElement.addEventListener('pagerendered', (event) =>
      pageNumber = event.detail.pageNumber
      pageView = @PDF.pdfPages[pageNumber - 1]
      annotationLayer = @PDF.annotationLayers[pageNumber - 1]
      @listenForLongTaps(pageNumber, pageView, annotationLayer)
    )


  # Listens for touch events, creating a new annotation highlight
  # on a long tap.
  listenForLongTaps: (pageNumber, pageView, annotationLayer) ->
    
    timeout = null
    $(annotationLayer).on('touchstart touchmove touchend', (event) =>

      if not @PDF.editing and not @PDF.$newHighlightElement

        if event.type is 'touchstart'
          
          timeout = setTimeout(=>

            timeout = null
            rect = annotationLayer.getBoundingClientRect()
            touch = event.originalEvent.changedTouches[0]
            coordinates =
              x: touch.clientX - rect.x
              y: touch.clientY - rect.y
            
            @createNewHighlight(pageNumber, pageView, annotationLayer, coordinates)

          , LONG_TAP_DELAY)

        if event.type is 'touchmove'
          clearTimeout(timeout)

        if event.type is 'touchend' and timeout
          clearTimeout(timeout)
        
    )


  # Creates a resizeable PDF annotation highlight, attaching listeners
  # for resizing and closing.
  createNewHighlight: (pageNumber, pageView, annotationLayer, coordinates) ->

    # Sets up new highlight at long-tapped location.
    topLeft = { x: coordinates.x - INITIAL_ANNOTATION_SIZE / 2, y: coordinates.y - INITIAL_ANNOTATION_SIZE / 2 }
    bottomRight = { x: coordinates.x + INITIAL_ANNOTATION_SIZE / 2, y: coordinates.y + INITIAL_ANNOTATION_SIZE / 2 }
    @PDF.createNewHighlight(annotationLayer, topLeft)
    @PDF.updateHighlight(topLeft, bottomRight)

    # Activates adder & listens for tap to adder to open editor
    # for highlight.
    @Touch.adder.removeAttr('disabled')
    @Touch.adder.bind('tap', ((event) -> event.stopPropagation()), =>
      @Touch.adder.attr('disabled', '')
      @PDF.finalizeHighlight(pageNumber, pageView, topLeft, bottomRight)
    )

    # Returns a handler for a highlight resize handle drag
    getHandleDragHandler = (top, left, bottom, right) =>
      (event) =>
        event.preventDefault()
        rect = annotationLayer.getBoundingClientRect()
        touch = event.originalEvent.changedTouches[0]
        topLeft.x = touch.clientX - rect.x if left
        topLeft.y = touch.clientY - rect.y if top
        bottomRight.x = touch.clientX - rect.x if right
        bottomRight.y = touch.clientY - rect.y if bottom
        @PDF.updateHighlight(topLeft, bottomRight)

    # Adds resize handles to the highlight
    $topLeftHandle = $('<div class="pdf-highlight-handle top-left"></div>').on('touchmove', getHandleDragHandler(true, true, false, false))
    $topRightHandle = $('<div class="pdf-highlight-handle top-right"></div>').on('touchmove', getHandleDragHandler(true, false, false, true))
    $bottomLeftHandle = $('<div class="pdf-highlight-handle bottom-left"></div>').on('touchmove', getHandleDragHandler(false, true, true, false))
    $bottomRightHandle = $('<div class="pdf-highlight-handle bottom-right"></div>').on('touchmove', getHandleDragHandler(false, false, true, true))
    @PDF.$newHighlightElement.append($topLeftHandle, $topRightHandle, $bottomLeftHandle, $bottomRightHandle)
