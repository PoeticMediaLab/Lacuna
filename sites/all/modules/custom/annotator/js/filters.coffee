#
# Annotation Filters
#
# Creates a sidebar of annotations with filters
# Hides/shows annotations in document based on user choices
#
# Mike Widner <mikewidner@stanford.edu>
#
#######

$ = jQuery  # for Drupal

# CSS ids and classes
# All written explicitly because it's easier than
# generating them progammatically (though that's my preference)
# 'default' is the class that should be applied for each element type
select = {
            'interface':  '#annotation-filters'
            'annotation': 'annotation-'
            'hide':       'af-annotation-hide'
            'filters':
              'default':  'af-filter'
              'active':   'af-filter-active'
              'delete':   'fa fa-trash'
            'pager':
              'default': 'af-pager'
              'wrapper': 'af-pager-wrapper'
              'count':   'af-pager-count'
              'arrow':   'af-pager-arrow'
              'first':   'fa fa-angle-double-left'
              'prev':    'fa fa-angle-left'
              'next':    'fa fa-angle-right'
              'last':    'fa fa-angle-double-right'
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
    'annotationsLoaded': 'setup'
    '.annotation-filter click': 'filterSelect'

  constructor: (element, options) ->
    super
    @Model = new Model
    @View = new View
    if options.current_user?
      @Model.set('currentUser', options.current_user)
    if options.filters?
      for filter in options.filters
        @Model.registerFilter(filter)

  pluginInit: ->
    @annotator.subscribe("annotationViewerShown", (Viewer) => @View.viewerShown(Viewer))
    @annotator.subscribe("annotationCreated", (annotation) => @Model.addAnnotation(annotation))
    @annotator.subscribe("annotationUpdated", (annotation) => @Model.updateAnnotation(annotation))
    return

  setup: (annotations) ->
    # Tell the different classes about each other
    @Model.setup(annotations)
    @View.setup(@, @Model)  # this == Controller
    # add an ID to every annotation
    for annotation in annotations
      for highlight in annotation.highlights
        $(highlight).first().attr('id', select.annotation + annotation.id)
        $(highlight).addClass(select.annotation + annotation.id)
    @Model.filterAnnotations('user', @Model.get('currentUser'))
    @View.drawFilter('user', @Model.get('currentUser'))
    @View.hideAnnotations(@Model.getFilteredIDs())

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
        # @View.checkboxUncheck('highlights')
        @View.checkboxDisable('highlights')
      @Model.filterAnnotations(filter, value)
      @View.hideAnnotations(@Model.getFilteredIDs())
      @View.drawFilter(filter, value)
      # Jump to first annotation now available
      @View.scrollTo(@Model.annotation())
    $(event.target).val('')
    return false # so autocomplete won't fill in the text box

  buttonClick: (event) =>
    type = $(event.target).attr('id')
    active = $(event.target)
    previous = $('.' + select.button.active)
    if previous.attr('id') == active.attr('id') then return
    previous.removeClass(select.button.active)
    if type == select.button.mine
      @Model.removeFilter 'user'
      @Model.removeFilter 'all'
      @Model.filterAnnotations 'user', @Model.get('currentUser')
      @View.drawFilter 'user', @Model.get('currentUser')
    else if type == select.button.all
      @Model.removeFilter 'user'
      @Model.removeFilter 'all'
      @View.eraseFilter 'user'
    else if type == select.button.none
      @Model.removeFilter 'user'
      @Model.filterAnnotations 'all', null
      @View.eraseFilter 'user'
    else if type == select.button.reset
      @Model.removeAllFilters()
      @View.eraseAllFilters()
      @View.checkboxCheck('highlights')
      @View.checkboxEnable('highlights')
      $(select.button.all).addClass(select.button.active)
      return  # don't highlight the reset button - doesn't make sense
    active.addClass(select.button.active) # active button
    return

  checkboxToggle: (event) =>
    id = event.target.name
    if id == 'highlights'
      if @Model.toggleHighlights()
        # We don't know that all highlights should be shown again
        @View.showAnnotations(@Model.getUnfilteredIDs())
      else
        @View.hideAnnotations(@Model.getFilteredIDs())
    return

  removeFilterClick: (event) =>
    id = event.target.id
    value = event.target.dataset.value
    @View.eraseFilter(id, value)
    ids = @Model.removeFilter(id, value)
    console.log(ids)
    @View.showAnnotations(ids)

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
    # Update to reflect pager values change
    @View.drawPagerCount(index, total)
    # Scroll to the current annotation
    @View.scrollTo(@Model.annotation())

class Model
  state:
    mode: 'intersection'  # or 'union'
    highlights: true      # show highlights
    highlightIDs: []
    annotations: []
    annotationsFiltered: {}
    total: 0
    index: 0
    currentUser: null
    filters: {}  # {'name': {'values': [values],
                 #            'active': {value: [ids]}
                 #          }
                 # }
  setup: (annotations) ->
    @state.annotations = annotations
    @state.total = annotations.length
    if @state.total then @state.index = 1
    for annotation in annotations
      if annotation.category == 'Highlight'
        @state.highlightIDs.push(annotation.id)
      for filter of @state.filters
        # Store the values available for filters
        if annotation[filter]?
          switch filter
            when 'user'
              @addFilterValue(filter, annotation['user'].name)
            when 'tags'
              for tag in annotation.tags
                @addFilterValue(filter, tag)
            else
              @addFilterValue(filter, annotation[filter])

  get: (attr) ->
    return @state[attr]

  set: (attr, value) ->
    @state[attr] = value

  currentID: () ->
    ids = @getUnfilteredIDs()
    return ids[@state.index - 1]

  annotation: (id = null) ->
    # Return annotation for a given id
    # If no id given, return current index
    if !id?
      id = @currentID()
    for annotation in @state.annotations
      if annotation.id == id
        return annotation

  toggleMode: () ->
    return

  toggleHighlights: () ->
    # Toggle highlights
    # Return true if highlights can be shown
    @state.highlights = !@state.highlights
    if @state.highlights
      for id in @state.highlightIDs
        @filterDecrement(id)
    else
      for id in @state.highlightIDs
        @filterIncrement(id)
    return @state.highlights

  addFilterValue: (filter, value) ->
    if value not in @state.filters[filter].values
      @state.filters[filter].values.push(value)

  registerFilter: (filter) ->
    # Register an autocomplete filter
    @state.filters[filter] = {}
    @state.filters[filter].values = []
    @state.filters[filter].active = []
    return

  activateFilter: (filter, value) ->
    if filter not of @state.filters
      @registerFilter(filter)
    if value not of @state.filters[filter].active
      @state.filters[filter].active[value] = []

  filterIsActive: (filter, value) ->
    # Return true if given filter is active
    return value of @state.filters[filter].active

  getFilters: () ->
    # Return entire filter object
    return @state.filters

  getFilterValues: () ->
    # Return filter names plus available values
    ret = {}
    for filter of @state.filters
      ret[filter] = @state.filters[filter].values
    return ret

  removeAllFilters: () ->
    return

  getFilteredIDs: () ->
    # Return array of all ids currently filtered
    return Object.keys(@state.annotationsFiltered)

  getUnfilteredIDs: () ->
    # Return array of all ids that are NOT filtered
    ids = []
    for annotation in @state.annotations
      unless @state.annotationsFiltered[annotation.id]
        ids.push(annotation.id)
    return ids

  removeFilter: (filter, value) ->
    # Clear a filter
    # Return list of ids now available to show
    unfilteredIDs = []
    for id in @state.filters[filter].active[value]
      if @filterDecrement(id) <= 0
        unfilteredIDs.push(id)
    delete @state.filters[filter].active[value]
    return unfilteredIDs

  filterIncrement: (id) ->
    # Add 1 to the times this id has been filtered
    # When the count reaches zero, can be shown safely
    if !@state.annotationsFiltered[id]?
      @state.annotationsFiltered[id] = 0
      --@state.total  # only the first time
    ++@state.annotationsFiltered[id]
    if @state.total <= 0
      @state.index = 0
      @state.total = 0
    return @state.annotationsFiltered[id]

  filterDecrement: (id) ->
    # Subtract 1 from times id is filtered
    # Remove from list once at zero
    if @state.annotationsFiltered[id]
      --@state.annotationsFiltered[id]
    if @state.annotationsFiltered[id] <= 0
      ++@state.total
      if @state.total == 1
        @state.index = 1
      delete @state.annotationsFiltered[id]
      return 0
    return @state.annotationsFiltered[id]

  addToFilter: (filter, value, id) ->
    @filterIncrement(id)
    if !@state.filters[filter].active[value]?
      @state.filters[filter].active[value] = []
    @state.filters[filter].active[value].push(id)

  removeFromFilter: (filter, value, id) ->
    @filterDecrement(id)
    i = @state.filters[filter].active[value].indexOf(id)
    @state.filters[filter].active[value].splice(i, 1)

  filterAnnotations: (filter, value, match = false) ->
    # Look for matches of filter type
    # Update list of filters
    # Return ids of annotations to be filtered
    # The option "match" variable determines if we want to hide
    # everything that *does* match
    # TODO: calculate union of annotations in same type of filter
    # but for different values
    if filter == 'none'
      @activateFilter('none')
      for annotation in @state.annotations
        @addToFilter(filter, null, annotation.id)
    else
      @activateFilter(filter, value)
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

### View methods ###
class View
  setup: (Controller, Model) =>
    @viewer = new Annotator.Viewer()
    @i = $(select.interface)  # shortcut to interface selector
    @Controller = Controller
    @Model = Model
    @i.append('<h2>Annotation Filters</h2>')
    @drawPager(@Model.get('index'), @Model.get('total'))
    @i.append("<div id='#{select.button.default}'></div>")
    @drawButton(select.button.default, 'none', 'user')
    @drawButton(select.button.default, 'mine', 'user')
    @drawButton(select.button.default, 'all', 'user')
    @drawActiveButton('mine')
    @drawCheckbox('highlights', 'Show Highlights')
    for filter, values of @Model.getFilterValues()
      @drawAutocomplete(filter, values)
    @i.append("<div id='#{select.button.reset}'></div>")
    @drawButton(select.button.reset, 'reset', 'reset')
    @i.append("<div id='#{select.filters.active}'>Active Filters</div>")
    return

  update: () ->
    # Draw based on current state
    return

  drawButton: (loc, id, filter) ->
    classes = [select.button.default, select.button[id], select.button[filter]].join(' ')
    $('#' + loc).append($('<span>',
      {id: select.button[id], class: classes})
      .text(id)
      .on('click', @Controller.buttonClick))

  drawActiveButton: (id) ->
    $('#' + select.button[id]).addClass(select.button.active)
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
    $(select.interface).append($("<input type='checkbox' name='#{id}' checked>",
      {name: id})
      .on("click", @Controller.checkboxToggle)
    ).append("<span id='#{id}' class='#{classes}'>#{value}</span>")

  drawAutocomplete: (id, values) ->
    html = "<div class='#{select.autocomplete.default}'><label class='#{select.autocomplete.label}' for='#{id}'>#{id}: </label><input name='#{id}' class='#{select.autocomplete.default} #{select.autocomplete.default}-#{id}' /></div>"
    @i.append(html)
    $("input[name=#{id}]").autocomplete
      source: values
      select: (event, ui) =>
        @Controller.filterSelected(event, ui)
    return

  drawPager: (first, last) ->
    p = select.pager
    @i.append($("<i id='first' class='#{p.default} #{p.arrow} #{p.first}'/>")).on("click", 'i#first', @Controller.pagerClick)
    @i.append($("<i id='prev' class='#{p.default} #{p.arrow} #{p.prev}'/>")).on("click", 'i#prev', @Controller.pagerClick)
    @i.append($("<span id='#{p.count}' class='#{p.default}'>").text(first + ' of ' + last))
    @i.append($("<i id='next' class='#{p.default} #{p.arrow} #{p.next}'/>")).on("click", 'i#next', @Controller.pagerClick)
    @i.append($("<i id='last' class='#{p.default} #{p.arrow} #{p.last}'/>")).on("click", 'i#last', @Controller.pagerClick)
    $('.' + p.default).wrapAll("<div id='#{p.wrapper}'></div>")
    return

  drawPagerCount: (first = 1, last = null) ->
    if !last?
      last = @Model.get('total')
    $('#' + select.pager.count).text(first + ' of ' + last)

  drawFilter: (id, value) ->
    # Add to list of "Active Filters"
    classes = [select.filters.default, select.filters.active, select.filters.delete, select.filters[id]].join(' ')
    $('#' + select.filters.active).after(
      $('<div>',
        {id: id,
        class: classes,
        'data-value': value})
      .text(' ' + id + ': ' + value)
      .on("click", @Controller.removeFilterClick)
      )

  eraseFilter: (id, value) ->
    $('#' + id + '.' + select.filters.active).remove()
    if id == 'user'
      $('.' + select.button.active + '.' + select.button.user).removeClass(select.button.active)
    if id == 'category'
      @checkboxEnable('highlights')

  showAnnotations: (ids) ->
    for id in ids
      $('.' + select.annotation + id).removeClass(select.hide)
    @drawPagerCount()

  hideAnnotations: (ids) ->
    for id in ids
      $('.' + select.annotation + id).addClass(select.hide)
    @drawPagerCount()

  viewerShown: (viewer) =>
    # if !@viewer?
    #   @viewer = viewer

  scrollTo: (annotation) ->
    # Jump to selected annotation
    # Load annotation viewer
    # TODO: adjust viewer positioning so it more closely
    # matches user expectations; top/left values are not
    # exactly aligned with how one typically uses the Viewer
    highlight = $(annotation.highlights[0])
    $("html, body").animate({
      scrollTop: highlight.offset().top - 300
    }, 150)
    $(Drupal.settings.annotator.element).annotator().annotator('showViewer', [annotation], highlight.position());
