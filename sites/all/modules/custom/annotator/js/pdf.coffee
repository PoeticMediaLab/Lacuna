# Enables PDF annotations.  Displays existing annotations over their
# respective page <canvas> elements.  Listens for mouse clicks on
# page <canvas> elements to open editor for existing annotations,
# and listens for drags to display selection box and open the editor
# to create new annotations.

$ = jQuery

class Annotator.Plugin.PDF extends Annotator.Plugin

  # Markup for the annotation layer of a PDF page
  ANNOTATION_LAYER_MARKUP: '<div class="pdf-annotation-layer"></div>'

  # Markup for a PDF annotation
  ANNOTATION_MARKUP: '<div class="pdf-annotation"></div>'


  # Pixels from mousedown for a mouseup to qualify as a dragend
  DRAG_THRESHOLD: 5

  # Called after plugin initialization.
  pluginInit: ->
    
    return unless Annotator.supported()
    Drupal.PDFDocumentView.loaded.then(=>

      # Adds a layer over the page <canvas> elements to hold annotations.
      @annotationLayers = @createAnnotationLayers()

      # Adds listener to annotation layers for mouse events.
      @listenForInteraction()

      # Responds to drags across annotation pages by creating new
      # annotations.
      @enableAnnotationCreation()

    )


  # For each element containing a rendered page, creates an annotation
  # layer for rendering existing annotations and capturing interaction
  # events.
  createAnnotationLayers: ->

    Drupal.PDFDocumentView.pdfPages.map((page) => 

      $annotationLayer = $(@ANNOTATION_LAYER_MARKUP)
      $(page.div).append($annotationLayer)
      return $annotationLayer[0]

    )


  # Attaches listeners to the PDF document page annotation layers,
  # publishing higher-level events to subscribed handlers.
  listenForInteraction: ->

    mouseDown = false
    dragging = false
    mousedownAnnotationLayer = null
    mousedownCoordinates = null
    $(@annotationLayers).on('mousedown mousemove mouseup', (event) =>

      annotationLayer = mousedownAnnotationLayer || event.currentTarget
      pageNumber = @annotationLayers.indexOf(annotationLayer)
      rect = annotationLayer.getBoundingClientRect()
      coordinates =
        x: event.clientX - rect.x
        y: event.clientY - rect.y

      eventParameters = { annotationLayer: annotationLayer, pageNumber: pageNumber, coordinates: coordinates }

      if event.type is 'mousedown'
        mouseDown = true
        mousedownAnnotationLayer = annotationLayer
        mousedownCoordinates = coordinates

      if event.type is 'mouseup'
        mouseDown = false
        mousedownAnnotationLayer = null
        mousedownCoordinates = null
        if dragging
          dragging = false
          @publish('pdf-dragend', eventParameters)
        
        else
          @publish('pdf-click', eventParameters)

      if mouseDown and event.type is 'mousemove'
        if not dragging
          if @checkDragThreshold(coordinates, mousedownCoordinates)
            dragging = true
            @publish('pdf-dragstart', eventParameters)
        
        else
          @publish('pdf-dragmove', eventParameters)

    )


  # Checks if the current mouse coordinate is far enough from the
  # the mousedown coordinate to be considered a drag.
  checkDragThreshold: (current, down) ->
    x = current.x > down.x + @DRAG_THRESHOLD or current.x < down.x - @DRAG_THRESHOLD
    y = current.y > down.y + @DRAG_THRESHOLD or current.y < down.y - @DRAG_THRESHOLD
    return x or y


  # Subscribes to PDF annotation layer drag events with handler
  # that allows selection over an area and then opens the editor
  # for the new annotation.
  enableAnnotationCreation: ->

    $newAnnotation = null
    pageNumber = null
    startCoordinates = null
    @subscribe('pdf-dragstart', (eventParameters) =>
      pageNumber = eventParameters.pageNumber
      startCoordinates = eventParameters.coordinates
      $newAnnotation = $(@ANNOTATION_MARKUP).addClass('new-annotation')
      $newAnnotation.css('left', eventParameters.coordinates.x)
      $newAnnotation.css('top', eventParameters.coordinates.y)
      $(eventParameters.annotationLayer).append($newAnnotation)
    )

    @subscribe('pdf-dragmove', (eventParameters) =>
      $newAnnotation.css('width', eventParameters.coordinates.x - startCoordinates.x)
      $newAnnotation.css('height', eventParameters.coordinates.y - startCoordinates.y)
    )

    @subscribe('pdf-dragend', (eventParameters) =>
      $newAnnotation.removeClass('new-annotation')
      console.log(pageNumber, [ startCoordinates, eventParameters.coordinates ])
      $newAnnotation = null
      pageNumber = null
      startCoordinates = null
    )

