# Adds PDF annotation to Annotator Touch.  Sets up listeners for
# long taps and draggable annotation edges.

# Constants
LONG_TAP_DELAY = 500
INITIAL_ANNOTATION_SIZE = 75

class Annotator.Plugin.Touch.PDF extends Annotator.Delegator

  constructor: (annotator) ->
    @annotator = annotator
    @pdfPlugin = @annotator.plugins.PDF
    @touchPlugin = @annotator.plugins.Touch
    @pdfPlugin.viewerElement.addEventListener('pagerendered', (event) =>
      pageNumber = event.detail.pageNumber
      pageView = @pdfPlugin.pdfPages[pageNumber - 1]
      annotationLayer = @pdfPlugin.annotationLayers[pageNumber - 1]
      @listenForLongTaps(pageNumber, pageView, annotationLayer)
    )


  # Listens for touch events, creating a new annotation highlight
  # on a long tap.
  listenForLongTaps: (pageNumber, pageView, annotationLayer) ->
    
    # Publishes a long tap Annotator event.
    timeout = null
    $(annotationLayer).on('touchstart touchmove touchend', (event) =>

      if not @pdfPlugin.editing

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
    @pdfPlugin.createNewHighlight(annotationLayer, topLeft)
    @pdfPlugin.updateHighlight(topLeft, bottomRight)
    
    # Activates adder & listens for tap to adder to open editor
    # for highlight.
    @touchPlugin.adder.removeAttr('disabled')
    @touchPlugin.adder.bind('tap', ((event) -> event.stopPropagation()), =>
      @touchPlugin.adder.attr('disabled', '')
      @pdfPlugin.finalizeHighlight(pageNumber, pageView, topLeft, bottomRight)
    )
