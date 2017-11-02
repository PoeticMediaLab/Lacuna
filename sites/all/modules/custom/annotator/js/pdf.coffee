# Enables PDF annotations.  Displays existing annotations over their
# respective page <canvas> elements.  Listens for mouse clicks on
# page <canvas> elements to open editor for existing annotations,
# and listens for drags to display selection box and open the editor
# to create new annotations.

$ = jQuery

class Annotator.Plugin.PDF extends Annotator.Plugin

  # Markup for the annotation layer of a PDF page
  ANNOTATION_LAYER_MARKUP: '<div class="pdf-annotation-layer" style="position: absolute; top: 0; right: 0; bottom: 0; left: 0; z-index: 1;"></div>'

  # Pixels from mousedown for a mouseup to qualify as a dragend
  DRAG_THRESHOLD: 5

  # Called after plugin initialization.
  pluginInit: ->
    
    return unless Annotator.supported()
    Drupal.PDFDocumentView.loaded.then(=>

      # Adds a layer over the page <canvas> elements to hold annotations.
      @annotationLayers = @createAnnotationLayers()

      # Adds listener to annotation layers for clicks and drags
      # on the PDF pages.
      @listenForInteraction()

    )


  # For each element containing a rendered page, creates an annotation
  # layer for rendering existing annotations and capturing interaction
  # events.
  createAnnotationLayers: ->

    Drupal.PDFDocumentView.pdfPages.map((page) => 

      t = document.createElement('div')
      t.innerHTML = @ANNOTATION_LAYER_MARKUP
      annotationLayer = page.div.appendChild(t.firstChild)

    )




  # Attaches a listener to the PDF document container that publishes 
  listenForInteraction: ->

    mouseDown = false
    dragging = false
    mousedownCoordinates = null
    $(@annotationLayers).on('mousedown mousemove mouseup', (event) =>

      page = @annotationLayers.indexOf(event.target)
      rect = event.target.getBoundingClientRect()
      coordinates =
        x: event.clientX - rect.x
        y: event.clientY - rect.y

      if event.type is 'mousedown'
        mouseDown = true
        mousedownCoordinates = coordinates

      if event.type is 'mouseup'
        mouseDown = false
        mousedownCoordinates = null
        if dragging
          dragging = false
          @publish('pdf-dragend', { event: event, page, coordinates: coordinates })
        
        else
          @publish('pdf-click', { event: event, page, coordinates: coordinates })

      if mouseDown and event.type is 'mousemove'
        if not dragging
          if @checkDragThreshold(coordinates, mousedownCoordinates)
            dragging = true
            @publish('pdf-dragstart', { event: event, page, coordinates: coordinates })
        
        else
          @publish('pdf-dragmove', { event: event, page, coordinates: coordinates })

    )


  # Checks if the current mouse coordinate is far enough from the
  # the mousedown coordinate to be considered a drag.
  checkDragThreshold: (current, down) ->
    x = current.x > down.x + @DRAG_THRESHOLD or current.x < down.x - @DRAG_THRESHOLD
    y = current.y > down.y + @DRAG_THRESHOLD or current.y < down.y - @DRAG_THRESHOLD
    return x or y

