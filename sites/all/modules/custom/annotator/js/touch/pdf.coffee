# Adds PDF annotation to Annotator Touch.  Sets up listeners for
# long taps and draggable annotation edges.

# Constants
LONG_TAP_DELAY = 500
INITIAL_ANNOTATION_SIZE = 75

class Annotator.Plugin.Touch.PDF extends Annotator.Delegator

  constructor: (annotator) ->
    @annotator = annotator
    @pdfPlugin = @annotator.plugins.PDF
    @pdfPlugin.viewerElement.addEventListener('pagerendered', (event) =>
      pageNumber = event.detail.pageNumber
      pageView = @pdfPlugin.pdfPages[pageNumber - 1]
      annotationLayer = @pdfPlugin.annotationLayers[pageNumber - 1]
      @listenForPDFTouchAnnotationCreation(pageNumber, pageView, annotationLayer)
    )


  # Listens for touch events, creating a new annotation highlight
  # on a long tap.
  listenForPDFTouchAnnotationCreation: (pageNumber, pageView, annotationLayer) ->
    
    # Publishes a long tap Annotator event.
    timeout = null
    $(annotationLayer).on('touchstart touchmove touchend', (event) =>

      if event.type is 'touchstart'
        
        timeout = setTimeout(=>

          timeout = null
          rect = annotationLayer.getBoundingClientRect()
          touch = event.originalEvent.changedTouches[0]
          coordinates =
            x: touch.clientX - rect.x
            y: touch.clientY - rect.y
          
          @createNewPDFTouchHighlight(pageNumber, pageView, annotationLayer, coordinates)

        , LONG_TAP_DELAY)

      if event.type is 'touchmove'
        clearTimeout(timeout)

      if event.type is 'touchend' and timeout
        clearTimeout(timeout)
        
    )


  # Creates a resizeable PDF annotation highlight, attaching listeners
  # for resizing and closing.
  createNewPDFTouchHighlight: (pageNumber, pageView, annotationLayer, coordinates) ->
    console.log('creating new highlight at page ' + pageNumber + ', (' + coordinates.x + ', ' + coordinates.y + ')')
    initialUpperLeft = { x: coordinates.x - INITIAL_ANNOTATION_SIZE / 2, y: coordinates.y - INITIAL_ANNOTATION_SIZE / 2 }
    initialLowerRight = { x: coordinates.x + INITIAL_ANNOTATION_SIZE / 2, y: coordinates.y + INITIAL_ANNOTATION_SIZE / 2 }
    @pdfPlugin.createNewHighlight(annotationLayer, initialUpperLeft)
    @pdfPlugin.updateHighlightDimensions(initialLowerRight, initialUpperLeft)
