#
# Annotation Filters
#
# Creates a sidebar of annotations with filters
# Hides annotations not in current filter(s) from display in document
#
# Mike Widner <mikewidner@stanford.edu>
#
#######

# BUG: overlapping, multi-user highlights

class Annotator.Plugin.Filters extends Annotator.Plugin

  events:
    'annotationsLoaded': 'setup'
    '.annotator-sidebar-filter click': 'changeFilterState'
    'annotationCreated': 'addAnnotation'
    'annotationUpdated': 'addAnnotation'

  options:
    filters: {}
    current_user: null
    selector:
      sidebar: '#annotation-filters'   # where to draw the filters
      annotation: 'annotation-'          # how to find annotations
      activeFilters: '#activeFilters'
    class:
      hiddenAnnotation: 'annotation-filters-hide-annotation'
      button: 'annotation-sidebar-button'
      activeButton: 'annotation-sidebar-button-active'
      input: 'annotation-filter-input'
      activeFilter: 'annotation-filter-active'
      closeIcon: 'fa fa-times'
      filterTitle: 'annotation-filters-title'

  data:
    annotations: {}
    filterValues: {}
    activeFilters: {}
    filtered: {}

  constructor: (element, options) ->
    super
    if options.current_user?
      @options.current_user = options.current_user
    if options.selector?
      if @options.selector.sidebar?
        @options.selector.sidebar = options.selector.sidebar
    if options.filters?
      @options.filters = options.filters

  pluginInit: ->
    # Subscribe to viewer event so we can stop it when annotations filtered
    @annotator.subscribe("annotationViewerShown", (Viewer) => @filterViewer(Viewer))

  setup: (annotations) ->
    # load annotations
    for annotation in annotations
      @data.annotations[annotation.id] = annotation
      @storeFilterValues annotation
      @addAnnotationID annotation
    @drawFilters()

  addAnnotationID: (annotation) ->
    # add an ID to the annotation
    for highlight in annotation.highlights
      # we can't use an ID because we may have multiple spans for a single annotation
      annotationHighlight = $(highlight).addClass(@options.selector.annotation + annotation.id)

  addAnnotation: (annotation) ->
    # update internal data objects with new annotation
    @data.annotations[annotation.id] = annotation
    @addAnnotationID annotation
    @storeFilterValues annotation

  getValue: (annotation, key) ->
    # return the desired value for a given key
    switch key
      when 'user' then return annotation[key]['name']
      else return annotation[key]

  storeFilterValues: (annotation) ->
    if @options.filters?
      for filterName in @options.filters
        # Create a list of unique strings for each filter
        if not @data.filterValues[filterName]?
          @data.filterValues[filterName] = []
        if not @data.filtered[filterName]?
          @data.activeFilters[filterName] = []
          @data.filtered[filterName] = []
        switch filterName
          when 'tags'
            if !annotation[filterName]? then break
            for tag in annotation[filterName]
              if tag not in @data.filterValues[filterName]
                @data.filterValues[filterName].push(tag)
          when 'user'
            user = @getValue(annotation, 'user')
            if user not in @data.filterValues[filterName]
              @data.filterValues[filterName].push(user)
          else
            if annotation[filterName]? and (annotation[filterName] not in @data.filterValues[filterName])
              @data.filterValues[filterName].push(annotation[filterName])

  filterViewer: (Viewer) ->
    # if all hidden, hide
    for annotation in Viewer.annotations
      # maybe build a list of highlights here?
      # then for each highlight that is filtered
      # and not shared with one that isn't filtered?
      # this one is tricky
      for filter of @data.activeFilters
        if annotation.id in @data.filtered[filter]
          # TODO: check that the highlight doesn't overlap
          #       with one that isn't filtered
          Viewer.hide()

  buttonClick: (event) =>
    # Note the fat arrow: this is called in click events, so needed
    # otherwise, we can't access @
    buttonType = $(event.target).attr('id')
    if buttonType == 'own-annotations'
      @filterAnnotations @options.current_user, 'user'
    else if buttonType == 'all-annotations'
      @removeFilter 'user'
    else if buttonType == 'remove-filters'
      @removeAllFilters()
    # else if buttonType == 'hide-all'
    #   @hideAllAnnotations()

  # hideAllAnnotations: ->
  #   for annotationID, annotation of @data.annotations
  #     @data.filtered[]

  hideFilteredAnnotations: ->
    for annotationID of @data.annotations
      for filter in @options.filters
        for id in @data.filtered[filter]
          if annotationID == id
            $('.' + @options.selector.annotation + id).addClass(@options.class.hiddenAnnotation)
            @publish('hide', @data.annotations[annotationID])
            break

  filterSelected: (event, ui) ->
    matchValue = ui.item.value
    filterName = event.target.name
    @filterAnnotations matchValue, filterName
    $(event.target).val('')
    false # so autocomplete won't leave text in the input box

  filterAnnotations: (matchValue, filterName) ->
    for id of @data.annotations
      value = @getValue(@data.annotations[id], filterName)
      if value instanceof Array
        if matchValue not in value
          @data.filtered[filterName].push(id)
      else if value != matchValue
        @data.filtered[filterName].push(id)
    @data.activeFilters[filterName].push(matchValue)
    classes = [filterName, @options.class.activeFilter, @options.class.closeIcon].join(' ')
    $(@options.selector.activeFilters).append(
      $('<div>',
        {id: matchValue,
        class: classes})
      .text(filterName + ': ' + matchValue)
      .on("click", @removeFilterClick)
      )
    @hideFilteredAnnotations()

  removeFilterClick: (event) =>
    item = $(event.target)
    filterValue = item.attr('id')
    for filterName in @options.filters
      if item.hasClass(filterName)
        @removeFilter filterName

  removeFilter: (filterName) ->
    for id in @data.filtered[filterName]
      @showAnnotation @data.annotations[id]
    @data.filtered[filterName] = []
    $('.' + filterName + '.' + @options.class.activeFilter).remove()

  showAnnotation: (annotation) ->
    $('.' + @options.selector.annotation + annotation.id)
      .removeClass(@options.class.hiddenAnnotation)

  removeAllFilters: ->
    # show all; reset all filters
    for filter of @data.filtered
      @data.filtered[filter] = []
    $('.' + @options.class.hiddenAnnotation).removeClass(@options.class.hiddenAnnotation)
    $('.' + @options.class.activeFilter).remove()

  makeButton: (id, text) ->
    sidebar = $(@options.selector.sidebar)
    sidebar.append($('<span>',
      {id: id, class: @options.class.button})
      .text(text)
      .on("click", @buttonClick)
    )

  drawFilters: ->
    # draw the filter elements in the sidebar
    sidebar = $(@options.selector.sidebar)
    sidebar.append('<h2>Annotation Filters</h2>')
    @makeButton 'own-annotations', 'My Annotations'
    @makeButton 'all-annotations', "Everyone's Annotations"
    # @makeButton 'hide-all', 'Hide All Annotations'
    @makeButton 'remove-filters', 'Remove All Filters'
    for filter, values of @data.filterValues
      inputHTML = "<label>#{filter}: </label><input name='#{filter}' class='#{@options.class.input}' />"
      sidebar.append(inputHTML)
      $("input[name=#{filter}]").autocomplete
        source: values
        select: (event, ui) =>
          @filterSelected(event, ui)
    sidebar.append("<div id='activeFilters'></div>")
