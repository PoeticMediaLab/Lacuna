# Enables PDF annotations.  Displays existing annotations over their
# respective page <canvas> elements.  Listens for mouse clicks on
# page <canvas> elements to open editor for existing annotations,
# and listens for drags to display selection box and open the editor
# to create new annotations.

$ = jQuery

# Markup for the annotation layer of a PDF page
ANNOTATION_LAYER_CLASS = 'pdf-annotation-layer'
ANNOTATION_LAYER_MARKUP = '<div class="' + ANNOTATION_LAYER_CLASS + '"></div>'

# Markup for a PDF annotation
HIGHLIGHT_CLASS = 'annotation-hl'
HIGHLIGHT_ID_CLASS_PREFIX = 'annotation-'
HIGHLIGHT_HIDDEN_CLASS = 'af-annotation-hide'
NEW_HIGHLIGHT_CLASS = 'new-annotation'
HIGHLIGHT_MARKUP = '<div class="' + HIGHLIGHT_CLASS + '"></div>'

# jQuery data key for saving annotation data to annotation element
ANNOTATION_DATA_KEY = 'annotation'

class Annotator.Plugin.PDF extends Annotator.Plugin

  # Pixels from mousedown for a mouseup to qualify as a dragend
  DRAG_THRESHOLD: 5

  # Called after plugin initialization.
  pluginInit: ->

    return unless Annotator.supported()

    # Listens for annotations loaded from API and saves them to an in-memory
    # store.
    @subscribe('annotationsLoaded', (annotations) =>
      @annotations = annotations
    )

    # Listens for annotations being deleted and removes element from
    # PDF annotation layer and in-memory annotation store.
    @subscribe('annotationDeleted', (annotation) =>
      annotation.$pdfHighlight.remove()
      index = @annotations.indexOf(annotation)
      @annotations.splice(index, 1)
    )

    # Prevents PDF scrolling, updates cursor and sets instance variable
    # when the Editor is open.
    @listenForEditorEvents()

    # Enables annotation on each PDF page as it's loaded in the
    # viewer.
    Drupal.PDFDocumentView.loaded.then(=>

      app = Drupal.PDFDocumentView.PDFViewerApplication

      # Saves a reference to the viewer DOM node.
      @viewerElement = app.pdfViewer.viewer

      # Saves a reference to the viewer's internal rendered page store
      pdfPages = app.pdfViewer._pages

      # Creates an internal store of annotation layers
      @annotationLayers = []

      # Listens for custom PDFApplicationViewer 'pagerendered' event
      # and enables annotation on each newly-rendered page.
      @viewerElement.addEventListener('pagerendered', (event) =>
        pageNumber = event.detail.pageNumber
        pageView = pdfPages[pageNumber - 1]
        @enableAnnotationsOnPage(pageNumber, pageView)
      )

    )

    # Listens for and handles custom PDF annotation creation events
    # from PDF annotation layers.
    @handlePDFAnnotationCreationEvents()


  # Listens for Annotator events for the opening and closing of
  # the Editor and freezes and unfreezes scrolling of the viewer,
  # sets an instance variable and updates the cursor accordingly.
  listenForEditorEvents: () ->

    @editing = false
    @subscribe('annotationEditorShown', () =>
      $(@viewerElement.parentElement).css({ overflow: 'hidden' })
      $(@viewerElement).addClass('editor-open')
      @editing = true
    )

    @subscribe('annotationEditorHidden', () =>
      $(@viewerElement.parentElement).css({ overflow: 'auto' })
      $(@viewerElement).removeClass('editor-open')
      @editing = false
    )


  # Enables annotation viewing and creation on a newly-rendered
  # PDF page.
  enableAnnotationsOnPage: (pageNumber, pageView) ->

    # Adds a layer over the page <canvas> elements to hold annotations.
    annotationLayer = @createAnnotationLayer(pageView)

    # Loads existing annotations on the layer
    @drawExistingAnnotations(pageNumber, pageView, annotationLayer)

    # Adds listeners to annotation layer for mouse events.
    @listenForAnnotationCreation(pageNumber, pageView, annotationLayer)


  # Creates an annotation layer for rendering existing annotations
  # and capturing interaction events.
  createAnnotationLayer: (pageView) ->
    annotationLayer = $(ANNOTATION_LAYER_MARKUP)[0]
    pageView.div.appendChild(annotationLayer)
    return annotationLayer


  # Creates a rectangle on the PDF page annotation layer for each
  # existing annotation and attaches listeners to show the viewer.
  drawExistingAnnotations: (pageNumber, pageView, annotationLayer) ->

    @annotations.forEach((annotation) =>

      if annotation.pdfRange and annotation.pdfRange.pageNumber is pageNumber

        # Creates annotation element
        $highlightElement = $(HIGHLIGHT_MARKUP)
        
        # Calculates coordinates for rendering annotation and sets
        # CSS properties to position.
        { x1Pdf, y1Pdf, x2Pdf, y2Pdf } = annotation.pdfRange
        v = pageView.viewport
        [ [ x1, y1 ], [ x2, y2 ] ] = [ [ x1Pdf, y1Pdf ], [ x2Pdf, y2Pdf ] ].map(([ x, y ]) -> v.convertToViewportPoint(x, y))
        [ width, height ] = [ x2 - x1, y2 - y1 ]
        $highlightElement.css({ left: x1, top: y1, width, height })

        # Links annotation element to annotation object.
        @setupHighlightElement($highlightElement, annotation)

        # Renders annotation to DOM.
        $(annotationLayer).append($highlightElement)

    )


  # Links an highlight element to an annotation object, creating
  # the necessary references and attaching the necessary listeners.
  setupHighlightElement: ($highlightElement, annotation) ->

    # Saves new element as property of annotation object and
    # saves annotation object as data member of highlight element.
    # Also adds a class for the annotation's ID.
    annotation.$pdfHighlight = $highlightElement
    $highlightElement.data(ANNOTATION_DATA_KEY, annotation)
    $highlightElement.addClass(HIGHLIGHT_ID_CLASS_PREFIX + annotation.id)
    $highlightElement.addClass(HIGHLIGHT_HIDDEN_CLASS) if annotation._isHidden

    # Attaches handlers to show editor on highlight element mouseover,
    # throttling event handler execution.
    THROTTLE_MS = 250
    throttling = false
    $highlightElement.on('mousemove', (event) =>
      if not throttling
        @onPDFHighlightMouseover(event)
        throttling = true
        setTimeout((-> throttling = false), THROTTLE_MS)

    )
      
    $highlightElement.on('mouseout', @annotator.startViewerHideTimer)


  # Attaches listeners to the PDF document page annotation layers,
  # publishing higher-level events to subscribed handlers.
  listenForAnnotationCreation: (pageNumber, pageView, annotationLayer) ->

    mouseDown = false
    @dragging = false
    mousedownCoordinates = null
    $(annotationLayer).on('mousedown mousemove mouseup', (event) =>

      # Disallows drag-to-create if the Editor is already open.
      if not @editing

        rect = annotationLayer.getBoundingClientRect()
        coordinates =
          x: event.clientX - rect.x
          y: event.clientY - rect.y

        eventParameters = { pageNumber, pageView, annotationLayer, coordinates }
        if event.type is 'mousedown'
          mouseDown = true
          mousedownCoordinates = coordinates

        if event.type is 'mouseup'
          mouseDown = false
          mousedownCoordinates = null
          if @dragging
            @dragging = false
            @publish('pdf-dragend', eventParameters)
          
          else
            @publish('pdf-click', eventParameters)

        if mouseDown and event.type is 'mousemove'
          if not @dragging
            if @checkDragThreshold(coordinates, mousedownCoordinates)
              @dragging = true
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
  handlePDFAnnotationCreationEvents: ->

    $newHighlightElement = null
    pageNumber = null
    startCoordinates = null
    @subscribe('pdf-dragstart', (eventParameters) =>
      pageNumber = eventParameters.pageNumber
      startCoordinates = eventParameters.coordinates
      $newHighlightElement = $(HIGHLIGHT_MARKUP).addClass(NEW_HIGHLIGHT_CLASS)
      $newHighlightElement.css({ left: eventParameters.coordinates.x, top: eventParameters.coordinates.y })
      $(eventParameters.annotationLayer).append($newHighlightElement)
    )

    @subscribe('pdf-dragmove', (eventParameters) =>
      width = eventParameters.coordinates.x - startCoordinates.x
      height = eventParameters.coordinates.y - startCoordinates.y
      $newHighlightElement.css({ width: (if width > 0 then width else 0), height: (if height > 0 then height else 0) })
    )

    @subscribe('pdf-dragend', (eventParameters) =>
      
      # Converts native CSS coordinates to PDF-specific coordinates,
      # for which the origin of each page is the lower-left corner
      # instead of the upper-left corner.
      v = eventParameters.pageView.viewport
      [ [ x1Pdf, y1Pdf ], [ x2Pdf, y2Pdf ] ] = [ [ startCoordinates.x, startCoordinates.y ], [ eventParameters.coordinates.x, eventParameters.coordinates.y ] ].map(([ x, y ]) -> v.convertToPdfPoint(x, y))
      [ widthPdf, heightPdf ] = [ x2Pdf - x1Pdf, y2Pdf - y1Pdf ]
      if widthPdf > 0 and heightPdf < 0
        pdfRange = { pageNumber, x1Pdf, y1Pdf, x2Pdf, y2Pdf }
        @editNewAnnotation(pdfRange, $newHighlightElement)
      
      else
        $newHighlightElement.remove()

      $newHighlightElement = null
      pageNumber = null
      startCoordinates = null
    
    )


  # Creates a new annotation from the supplied range, then opens
  # the editor with it.
  editNewAnnotation: (pdfRange, $newHighlightElement) ->

    # Creates new annotation
    annotation = @annotator.createAnnotation()
    annotation.pdfRange = pdfRange
    
    # Initializes required fields, otherwise core code throws errors
    annotation.quote = []
    annotation.ranges = []
    annotation.highlights = []

    save = =>
      @publish('annotationCreated', [ annotation ])
      $newHighlightElement.removeClass(NEW_HIGHLIGHT_CLASS)
      @setupHighlightElement($newHighlightElement, annotation)
      @annotations.push(annotation)
      cleanup()

    cancel = =>
      $newHighlightElement.remove()
      cleanup()

    cleanup = =>
      @unsubscribe('annotationEditorHidden', cancel)
      @unsubscribe('annotationEditorSubmit', save)

    # Calculates editor location and opens editor with new annotation.
    { top, left, bottom, right } = $newHighlightElement[0].getBoundingClientRect()
    editorLocation = { top: (top + bottom) / 2, left: (left + right) / 2 }
    @subscribe('annotationEditorSubmit', save)
    @subscribe('annotationEditorHidden', cancel)
    @annotator.showEditor(annotation, editorLocation)


  # PDF-specific versions of Annotator's internal onHighlightMouseover.
  onPDFHighlightMouseover: (event) =>
    
    @annotator.clearViewerHideTimer()

    # Don't do anything if we're creating or editing an annotation
    return false if @dragging or @editing

    # If the viewer is already shown, hide it first
    @annotator.viewer.hide() if @annotator.viewer.isShown()

    # Now show the viewer with the wanted annotation
    annotations = @getAnnotationsAtMouseLocation(event)
    location = { left: event.clientX, top: event.clientY }
    @annotator.showViewer(annotations, location)


  # Finds all annotations under the current mouse location.
  getAnnotationsAtMouseLocation: (event) ->
    
    # Extracts mouse location and parent document
    { clientX, clientY } = event
    parentDocument = event.target.ownerDocument

    # Checks each element under mouse position
    CHECKED_CLASS = 'under-mouse-position-checked'
    checked = []
    annotations = []
    while true
      element = parentDocument.elementFromPoint(clientX, clientY)
      break if element.classList.contains(ANNOTATION_LAYER_CLASS)
      element.classList.add(CHECKED_CLASS)
      checked.push(element)
      annotations.push(element) if element.classList.contains(HIGHLIGHT_CLASS)

    Array.prototype.forEach.call(checked, ((element) -> element.classList.remove(CHECKED_CLASS)))
    return Array.prototype.map.call(annotations, ((element) -> $(element).data(ANNOTATION_DATA_KEY)))
