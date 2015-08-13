#
# Annotation Filters
#
# Creates a sidebar of annotations with filters
# Hides/shows annotations in document based on user choices
#
#
# Mike Widner <mikewidner@stanford.edu>
#
#######

$ = jQuery  # for Drupal and my own laziness

# CSS ids and classes
# All written explicitly because it's easier than
# generating them progammatically (though that's my preference)
# 'default' is the class that should be applied for each element type
select = {
            'interface':
              'setup':  'section.region-sidebar-second'
              'wrapper': 'annotation-filters-wrapper'
              'filters': 'annotation-filters'
            'annotation': 'annotation-'
            'hide':       'af-annotation-hide'
            'filters':
              'default':  'af-filter'
              'active':   'af-filter-active'
              'delete':   'fa fa-trash'
            'pager':
              'default': 'af-pager'
              'wrapper': 'af-pager-wrapper'
              'controls': 'af-pager-controls'
              'count':   'af-pager-count'
              'arrow':   'af-pager-arrow'
              'first':   'fa fa-angle-double-left fa-lg'
              'prev':    'fa fa-angle-left fa-lg'
              'next':    'fa fa-angle-right fa-lg'
              'last':    'fa fa-angle-double-right fa-lg'
            'button':
              'default':'af-button'
              'reset':  'af-button-reset'
              'active': 'af-button-active'
              'user':   'af-button-user'
              'none':   'af-button-none'
              'all':    'af-button-all'
              'mine':   'af-button-mine'
            'autocomplete':
              'default':  'af-autocomplete'
              'wrapper':  'af-autocomplete-wrapper'
              'label':    'af-autocomplete-label'
            'checkbox':
              'default':    'af-checkbox'
              'highlights': 'af-checkbox-highlights'
          }

class Annotator.Plugin.Filters extends Annotator.Plugin
  events:
    'annotationsLoaded'       : 'setup'
    '.annotation-filter click': 'filterSelect'
    '.annotation-filter tap'  : 'filterSelect'

  constructor: (element, options) ->
    super
    # Check if asked to jump to an annotation
    if window.location.search
      query = window.location.search.substring(1)
      for item in query.split('&')
        pair = item.split('=')
        if pair[0] == 'id'
          # Store for after full plugin initialization
          @scrollToID = pair[1]
    @Model = new Model
    @View = new View
    @View.element = element # For finding the annotator
    if options.current_user?
      @Model.set('currentUser', options.current_user)
    if options.filters?
      for filter in options.filters
        @Model.registerFilter(filter)

  pluginInit: ->
    @annotator.subscribe("annotationViewerShown", (Viewer) => @View.viewerShown(Viewer))
    # @annotator.subscribe("annotationCreated", (annotation) => @Model.addAnnotation(annotation))
    # @annotator.subscribe("annotationUpdated", (annotation) => @Model.updateAnnotation(annotation))
    return

  setup: (annotations) ->
    # Tell the different classes about each other
    @Model.setup(annotations)
    @View.setup(@, @Model)  # this == Controller
    # add an ID to every annotation
    for annotation in annotations
      for highlight in annotation.highlights
#        $(highlight).first().attr('id', select.annotation + annotation.id)
        $(highlight).addClass(select.annotation + annotation.id)
    if @scrollToID?
      @View.scrollTo(@Model.annotation(@scrollToID))
    else
      # Filter only if we're not scrolling to
      @Model.filterAnnotations('user', @Model.get('currentUser'))
      @View.drawFilter('user', @Model.get('currentUser'))
      @View.drawActiveButton(select.button.mine)
    @View.drawAnnotations()

  # Note the double arrows below:
  # methods called in click events need access to @
  filterSelected: (event, ui) =>
    # User entered a filter value
    # Take the appropriate actions
    filter = event.target.name
    value = ui.item.value
    # Don't duplicate active filters
    if not @Model.filterIsActive(filter, value)
      if filter == 'category'
        # Highlights are a special case of category
        # Clicking the box doesn't make sense now
        @View.checkboxDisable('highlights')
      @Model.filterAnnotations(filter, value)
      @View.drawAnnotations()
      @View.drawFilter(filter, value)
      # Jump to first annotation now available
      @View.scrollTo(@Model.annotation())
    $(event.target).val('')
    return false # so autocomplete won't fill in the text box

  buttonClick: (event) =>
    # Manage mutually exclusive buttons
    # Almost entirely focused on which users' annotations shown
    type = $(event.target).attr('id')
    active = $(event.target)
    previous = $('.' + select.button.active)
    if previous.attr('id') == active.attr('id') then return
    @Model.removeFilter 'user'
    @Model.removeFilter 'none'
    if type == select.button.mine
      @View.eraseFilter 'user'
      @Model.filterAnnotations 'user', @Model.get('currentUser')
      @View.drawFilter 'user', @Model.get('currentUser')
    else if type == select.button.all
      # @View.eraseFilter 'user', @Model.get('currentUser')
      @View.eraseFilter 'user'
    else if type == select.button.none
      @Model.removeAllFilters()
      @Model.filterAnnotations 'none', 'none'
      @View.eraseAllFilters()
      @View.drawFilter 'user', 'None'
    else if type == select.button.reset
      # Return to starting state
      # Currently: only the current user's annotations
      # with highlights shown
      @Model.removeAllFilters()
      @View.eraseAllFilters()
      @View.checkboxCheck('highlights')
      @View.checkboxEnable('highlights')
      @Model.filterAnnotations 'user', @Model.get('currentUser')
      @View.drawFilter 'user', @Model.get('currentUser')
      type = select.button.mine
    @View.drawActiveButton(type)
    @View.drawAnnotations()
    return null

  checkboxToggle: (event) =>
    if event.target.name == 'highlights'
      @Model.toggleHighlights()
      @View.drawAnnotations()
    return

  removeFilterClick: (event) =>
    id = event.target.id
    value = event.target.dataset.value
    @View.eraseFilter(id, value)
    @Model.removeFilter(id, value)
    if id == 'category' and not @Model.filterIsActive('category')
      @View.checkboxEnable('highlights')
    @View.drawAnnotations()

  pagerClick: (event) =>
    index = @Model.get('index')
    total = @Model.get('total')
    switch event.target.id
      when 'first'
        index = 1
      when 'prev'
        --index
        if index < 1 then index = total
      when 'next'
        ++index
        if index > total then index = 1
      when 'last'
        index = total
    @Model.set('index', index)
    # So the page turner can show the correct page, if needed
    $(document).trigger('annotation-filters-paged', @Model.annotation())
    # Update to reflect pager values change
    @View.drawPagerCount()
    # Scroll to the current annotation
    @View.scrollTo(@Model.annotation())

class Model
  state:
    showHighlights: true
    ids:                # just IDs for quick hide/show
      all: []
      highlights: []
      hidden: []
      shown: []
    annotations: []     # the full data
    total: 0            # can be ids.shown.length now
    index: 0
    currentUser: null
    filters: {}  # {'name': {'values': [values],
                 #            'active': {value: [ids]}
                 #          }
                 # }
  setup: (annotations) ->
    @state.annotations = annotations
    @state.total = annotations.length
    annotations.sort (a,b) ->
      # Order annotations by location in text, not creation time
      rangeA = document.createRange()
      if a.highlights[0]?
        rangeA.selectNodeContents(a.highlights[0])
      rangeB = document.createRange()
      if b.highlights[0]?
        rangeB.selectNodeContents(b.highlights[0])
      return rangeA.compareBoundaryPoints(Range.START_TO_START, rangeB)

    if @state.total then @state.index = 1
    for annotation in annotations
      @state.ids.all.push(annotation.id)
      if annotation.category.toLowerCase() == 'highlight'
        @state.ids.highlights.push(annotation.id)
      for filter of @state.filters
        # Store the values available for filters
        if annotation[filter]?
          switch filter
            when 'user'
              @addFilterValue(filter, annotation['user'].name)
            when 'tags'
              for tag in annotation.tags
                @addFilterValue(filter, tag) if tag?
            else
              @addFilterValue(filter, annotation[filter])

  get: (attr) ->
    return @state[attr]

  set: (attr, value) ->
    @state[attr] = value

  currentID: () ->
    return @state.ids.shown[@state.index - 1]

  addAnnotation: (annotation) ->
    return

  updateAnnotation: (annotation) ->
    return

  annotation: (id = null) ->
    # Return annotation for a given id
    # If no id given, return current index
    if !id?
      id = @currentID()
    for annotation in @state.annotations
      if annotation.id == id
        return annotation

  toggleHighlights: () ->
    # Toggle highlights
    # Return true if highlights should be shown
    # Note: they have their own filter type
    # Otherwise, they'll collide with the "real" categories
    @state.showHighlights = !@state.showHighlights
    if @state.showHighlights
      @removeFilter('highlights', 'highlights')
    else
      @activateFilter('highlights', 'highlights')
      for id in @state.ids.highlights
        @addToFilter('highlights', 'highlights', id)
    @computeFilters()
    return @state.showHighlights

  addFilterValue: (filter, value) ->
    if value not in @state.filters[filter].values
      @state.filters[filter].values.push(value)

  registerFilter: (filter) ->
    # Register an autocomplete filter
    @state.filters[filter] = {}
    @state.filters[filter].values = []
    @state.filters[filter].active = {}
    return

  activateFilter: (filter, value) ->
    if filter not of @state.filters
      @registerFilter(filter)
    if value not of @state.filters[filter].active
      @state.filters[filter].active[value] = []

  filterIsActive: (filter, value) ->
    # Return true if given filter is active
    if not value
      return Object.keys(@state.filters[filter].active).length > 0
    return value of @state.filters[filter].active

  getFilterValues: () ->
    # Return filter names plus available values
    ret = {}
    for filter of @state.filters
      ret[filter] = @state.filters[filter].values
    return ret

  getHidden: () ->
    # Return array of all ids currently filtered
    return @state.ids.hidden

  getShown: () ->
    # Return array of all ids that are NOT filtered
    return @state.ids.shown

  dropHidden: (annotations) ->
    # Remove all annotations from array that are currently hidden
    shown = []
    for annotation in annotations
      unless annotation.id in @state.ids.hidden
        shown.push(annotation)
    return shown

  removeAllFilters: () ->
    for filter of @state.filters
      for value of @state.filters[filter].active
        @removeFilter(filter, value)

  removeFilter: (filter, value) ->
    if filter of @state.filters
      if value of @state.filters[filter].active
        delete @state.filters[filter].active[value]
      else
        @state.filters[filter].active = {}
      @computeFilters()

  intersection: (a, b) ->
    result = []
    if not b.length
      return a
    if not a.length
      return b
    for id in a
      # We know our arrays are made of unique integers
      result.push(id) if id in b
    return result

  intersectAll: (lists) ->
    # Return the intersection of given arrays
    result = []
    if not lists or lists.length is 0
      return result
    else return lists[0] if lists.length is 1
    for list in lists
      result = @intersection(result, list)
    return result

  union: (arrays) ->
    # Return the union of given arrays
    result = []
    for arr in arrays
      for id in arr
        if id not in result
          result.push(id)
    return result

  computeFilters: () ->
    # Run an intersection on filter types w/ multiple values
    # then a union on the results
    # Logic: ('User A' OR 'User B') AND 'Tag C'
    @state.ids.hidden = []
    @state.ids.shown = []
    ids = []
    for filter of @state.filters
      arrays = []
      for value of @state.filters[filter].active
        if @state.filters[filter].active[value].length
          arrays.push(@state.filters[filter].active[value])
      ids.push(@intersectAll(arrays))
    @state.ids.hidden = @union(ids)
    for id in @state.ids.all
      unless id in @state.ids.hidden
        @state.ids.shown.push(id)
    @state.total = @state.ids.shown.length
    @state.index = 0
    if @state.total
      @state.index = 1

  addToFilter: (filter, value, id) ->
    if !@state.filters[filter].active[value]?
      @state.filters[filter].active[value] = []
    @state.filters[filter].active[value].push(id)

  filterAnnotations: (filter, value) ->
    # Look for matches of filter type
    # Update list of filters
    @activateFilter(filter, value)
    if filter == 'none'
      for annotation in @state.annotations
        # Filter ALL THE THINGS!
        @addToFilter(filter, filter, annotation.id)
    else
      for annotation in @state.annotations
        if filter == 'user'
          currentValue = annotation[filter].name
        else
          currentValue = annotation[filter]
        if !currentValue then currentValue = ''
        if currentValue instanceof Array
          if value not in currentValue
            @addToFilter(filter, value, annotation.id)
        else if currentValue != value
          @addToFilter(filter, value, annotation.id)
    @computeFilters()

### View methods ###
class View
  setup: (Controller, Model) =>
    @viewer = new Annotator.Viewer()
    $(select.interface.setup).append("<div id='#{select.interface.wrapper}'><div id='#{select.interface.filters}'></div></div>")
    @i = $('#' + select.interface.wrapper)  # interface shortcut
    @Controller = Controller
    @Model = Model

    # Toggle a class on title click to show or hide the filters
    # for small screens.
    @i.addClass('hidden')
    title = $('<h2>Show Annotations</h2>')
    title.click((-> @i.toggleClass('hidden')).bind(this))
    @i.append(title)

    @drawPager(@Model.get('index'), @Model.get('total'))
    @i.append("<div id='#{select.button.default}'></div>")
    @drawButton(select.button.default, 'none', 'user')
    @drawButton(select.button.default, 'mine', 'user')
    @drawButton(select.button.default, 'all', 'user')
    @drawCheckbox('highlights', 'Show Highlights')
    for filter, values of @Model.getFilterValues()
      @drawAutocomplete(filter, values)
    @i.append("<div id='#{select.button.reset}'></div>")
    @drawButton(select.button.reset, 'reset', 'reset')
    @i.append("<div id='#{select.filters.active}'>Showing Only</div>")
    return

  update: () ->
    # Draw based on current state
    return

  drawButton: (loc, id, filter) ->
    classes = [select.button.default, select.button[id], select.button[filter]].join(' ')
    $('#' + loc).append($('<span>',
      {id: select.button[id], class: classes})
      .text(id)
      .on('tap click', @Controller.buttonClick))

  drawActiveButton: (id) ->
    $('.' + select.button.active).removeClass(select.button.active)
    $('#' + id).addClass(select.button.active)
    return

  checkboxStateChange: (id, attr, state) ->
    $("input[name='#{id}'").attr(attr, state)

  # Some helper methods for changing checkbox state in a readable fashion
  checkboxCheck: (id) ->
    @checkboxStateChange(id, 'checked', true)

  checkboxUncheck: (id) ->
    @checkboxStateChange(id, 'checked', false)

  checkboxEnable: (id) ->
    @checkboxStateChange(id, 'disabled', false)

  checkboxDisable: (id)->
    @checkboxStateChange(id, 'disabled', true)

  drawCheckbox: (id, value) ->
    classes = [select.checkbox.default, select.checkbox[id]].join(' ')
    $('#' + select.interface.wrapper).append($("<input type='checkbox' name='#{id}' checked>",
      {name: id})
      .on("click", @Controller.checkboxToggle)
    ).append("<span id='#{id}' class='#{classes}'>#{value}</span>")

  drawAutocomplete: (id, values) ->
    html = "<div class='#{select.autocomplete.default}'><label class='#{select.autocomplete.label}' for='#{id}'>#{id}: </label><input name='#{id}' class='#{select.autocomplete.default} #{select.autocomplete.default}-#{id}' /></div>"
    @i.append(html)
#    if id == 'tags' # we use a special autocompletion for tags
#      $("input[name=#{id}]").catcomplete
#      source: values
#      select: (event, ui) =>
#        @Controller.filterSelected(event, ui)
#    else
    $("input[name=#{id}]").autocomplete
      source: values
      select: (event, ui) =>
        @Controller.filterSelected(event, ui)
    return

  drawPager: (first, last) ->
    p = select.pager
    @i.append($("<i id='first' class='#{p.default} #{p.arrow} #{p.first}'/>")).on("click", 'i#first', @Controller.pagerClick)
    @i.append($("<i id='prev' class='#{p.default} #{p.arrow} #{p.prev}'/>")).on("click", 'i#prev', @Controller.pagerClick)
    @i.append($("<i id='next' class='#{p.default} #{p.arrow} #{p.next}'/>")).on("click", 'i#next', @Controller.pagerClick)
    @i.append($("<i id='last' class='#{p.default} #{p.arrow} #{p.last}'/>")).on("click", 'i#last', @Controller.pagerClick)
    @i.append($("<span id='#{p.count}' class='#{p.default}'>").text(first + ' of ' + last))
    $('.' + p.default).wrapAll("<div id='#{p.wrapper}'></div>")
    $('.' + p.arrow).wrapAll("<div id='#{p.controls}'></div>")
    return

  drawPagerCount: () ->
    $('#' + select.pager.count).text(@Model.get('index') + ' of ' + @Model.get('total'))

  drawFilter: (id, value) ->
    # Add to list of "Active Filters"
    if not value
      value = ''
    classes = [select.filters.default, select.filters.active, select.filters.delete, select.filters[id]].join(' ')
    $('#' + select.filters.active).after(
      $('<div>',
        {id: id,
        class: classes,
        'data-value': value})
      .text(' ' + id + ': ' + value)
      .on("click", @Controller.removeFilterClick)
      )

  eraseAllFilters: () ->
    $('.' + select.filters.active).remove()

  eraseFilter: (id, value) ->
    if value?
      $('#' + id + '.' + select.filters.active + '[data-value="' + value + '"]').remove()
    else
      # No explicit value; remove all of this type
      $('#' + id + '.' + select.filters.active).remove()
    if id == 'user'
      $('.' + select.button.active + '.' + select.button.user).removeClass(select.button.active)

  showAnnotations: (ids) ->
    for id in ids
      $('.' + select.annotation + id).removeClass(select.hide)
    $(document).trigger('annotation-filters-changed') # fire after DOM changed

  hideAnnotations: (ids) ->
    for id in ids
      $('.' + select.annotation + id).addClass(select.hide)
    $(document).trigger('annotation-filters-changed') # fire after DOM changed

  drawAnnotations: () ->
    @showAnnotations(@Model.getShown())
    @hideAnnotations(@Model.getHidden())
    @drawPagerCount()

  viewerShown: (Viewer) =>
    # Only display Viewer for annotations that aren't hidden
    Viewer.hide()
    annotations = @Model.dropHidden(Viewer.annotations)
    if annotations.length
      Viewer.load(annotations)
      Viewer.show()

  getViewerPosition: (annotation) ->
    pos = $(annotation.highlights[0]).position()
    range = annotation.ranges[0].toObject()
    if range.endOffset > range.startOffset
      pos.left += range.endOffset - range.startOffset
    else
      pos.left += range.startOffset
    return pos

  scrollTo: (annotation) ->
    # Jump to selected annotation
    # Load annotation viewer
    return if not annotation
    $(document).trigger('annotation-filters-paged', annotation)
    highlight = $(annotation.highlights[0])
    $("html, body").animate({
      scrollTop: highlight.offset().top - 500
    }, 150)
    $(@element).annotator().annotator('showViewer', [annotation], @getViewerPosition(annotation));
