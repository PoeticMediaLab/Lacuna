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

      # TODO:
      # - save annotations
      # - render existing PDF annotations on each page
      # - re-render PDF annotations when canvases are destroyed
      # - update cursors for creating, hovering and editing annotations

      # ISSUES:
      # - you can't select annotation that overlap from the previous
      # page from the current page
      #  - creating an annotation that overlaps into the second page
      # selects text on the second page
      # - some mouse actions register as drags but shouldn't (e.g. ctrl-click)
      # - layering annotations can make them opaque and hide text.
      # - annotation editor doesn't scroll with iframe contents.  solution could be to freeze iframe contents

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
  # that allows selection over an area and triggers creation of a
  # new annotation.
  enableAnnotationCreation: ->

    $newAnnotationElement = null
    pageNumber = null
    startCoordinates = null
    @subscribe('pdf-dragstart', (eventParameters) =>
      pageNumber = eventParameters.pageNumber
      startCoordinates = eventParameters.coordinates
      $newAnnotationElement = $(@ANNOTATION_MARKUP).addClass('new-annotation')
      $newAnnotationElement.css('left', eventParameters.coordinates.x)
      $newAnnotationElement.css('top', eventParameters.coordinates.y)
      $(eventParameters.annotationLayer).append($newAnnotationElement)
    )

    @subscribe('pdf-dragmove', (eventParameters) =>
      width = eventParameters.coordinates.x - startCoordinates.x
      height = eventParameters.coordinates.y - startCoordinates.y
      $newAnnotationElement.css('width', if width > 0 then width else 0)
      $newAnnotationElement.css('height', if height > 0 then height else 0)
    )

    @subscribe('pdf-dragend', (eventParameters) =>
      
      # Converts native CSS coordinates to PDF-specific coordinates,
      # for which the origin of each page is the lower-left corner
      # instead of the upper-left corner.
      v = Drupal.PDFDocumentView.pdfPages[pageNumber].viewport
      [startX, startY] = v.convertToPdfPoint(startCoordinates.x, startCoordinates.y)
      [endX, endY] = v.convertToPdfPoint(eventParameters.coordinates.x, eventParameters.coordinates.y)
      width = endX - startX
      height = endY - startY
      if width > 0 and height < 0
        annotation = @annotator.createAnnotation()
        annotation.pdfRange = { pageNumber, startX, startY, width, height }
        @openEditor(annotation, $newAnnotationElement)
      
      else
        $newAnnotationElement.remove()

      $newAnnotationElement = null
      pageNumber = null
      startCoordinates = null
    
    )


  # Opens the editor given an element and associated annotation.
  openEditor: (annotation, $element) ->
    { top, left, bottom, right } = $element[0].getBoundingClientRect()
    editorLocation = { top: (top + bottom) / 2, left: (left + right) / 2 }
    @annotator.showEditor(annotation, editorLocation)
