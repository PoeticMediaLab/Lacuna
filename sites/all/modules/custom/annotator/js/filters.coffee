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
select = {
            'default':    'af'  # annotation filter
            'interface':  '#annotation-filters'
            'annotation': 'annotation-'
            'pager':
              'wrapper': 'pager-wrapper'
              'count':   'pager-count'
              'arrow':   'pager-arrow'
              'first':   'fa fa-angle-double-left'
              'prev':    'fa fa-angle-left'
              'next':    'fa fa-angle-right'
              'last':    'fa fa-angle-double-right'
            'button':
              'active': 'button-filter-active'
              'user':   'button-filter-user'
              'none':   'button-filter-none'
              'all':    'button-filter-all'
              'mine':   'button-filter-mine'
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
      @Model.setCurrentUser(options.current_user)
    # if options.select?
    #   if @options.select.sidebar?
    #     @options.select.sidebar = options.select.sidebar
    # if options.filters?
    #   @options.filters = options.filters

  pluginInit: ->
    @annotator.subscribe("annotationViewerShown", (Viewer) => @View.viewerShown(Viewer))
    @annotator.subscribe("annotationCreated", (annotation) => @Model.addAnnotation(annotation))
    @annotator.subscribe("annotationUpdated", (annotation) => @Model.updateAnnotation(annotation))
    return

  setup: (annotations) ->
    # Tell the different classes about each other
    @Model.setup(annotations)
    @View.setup(@, @Model)

  filterSelect: (event) =>
    return

  buttonClick: (event) =>
    console.log(event, 'buttonClick')
    return

  checkboxToggle: (event) =>
    return

  getSelector: (item, selector) ->
    # Generates classes/ids for adding to DOM
    # input: 'button'
    # output: 'af-button'
    # input: 'button': 'user'
    # output: 'af-button af-button-user'
    # input: 'button': ['user', 'all']
    # output: 'af-button af-button-user af-button-all'
    # input: 'button': {'user': 'all'}
    # output: 'af-button af-button-user af-button-user-all'
    # input: 'pager': 'prev'
    # output: 'af-pager af-pager-prev fa fa-angle-left'
    console.log([item, selector], 'start')
    if not selector
      selector = []
    # if not selector
    #   selector = select.default + '-'
    # else
    #   selector += ' ' + select.default + '-'
    if typeof item == 'string'
      console.log('string')
      if !select[item]? or select[item] instanceof Object
        selector.push(item)
      else
        selector.push(select[item])
    else if item instanceof Array
      console.log('array')
      for i in item
        console.log(i, 'recurse Array')
        selector.push(@getSelector(i, selector))
    else if item instanceof Object
      console.log('object Recurse')
      for key of item
        selector.push(@getSelector(key, selector))
        selector += @getSelector(key + '-' + item[key], selector + ' ')
    console.log([item, selector])
    return selector.trim()

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
    # Scroll to the annotation
    @View.scrollTo(@Model.annotation())

class Model
  state:
    mode: 'intersection'  # or 'union'
    highlights: true      # show highlights
    annotations: []
    annotationsHidden: []
    annotationsShown: []
    total: 0
    index: 0
    currentUser: null
    filters: []
            # ['name': {'choices': [],
            #           'active': false,
            #           'type': 'autocomplete'
            #           'values': ['value': 'label']
            #           }
            # ]

  setup: (annotations) ->
    @state.annotations = annotations
    # add an ID to every annotation
    for annotation in annotations
      for highlight in annotation.highlights
        $(highlight).first().attr('id', select.annotation + annotation.id)
        $(highlight).addClass(select.annotation + annotation.id)
    @state.total = annotations.length
    if @state.total then @state.index = 1

  get: (attr) ->
    return @state[attr]

  set: (attr, value) ->
    @state[attr] = value

  currentID: () ->
    return @state.annotations[@state.index - 1].id

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

  addFilter: (name, value) ->
    return

  removeFilter: (name, value) ->
    return

  toggleHighlights: () ->
    return

  changePager: (direction) ->
    # Can be: first, prev, next, last
    return

  setCurrentUser: (currentUser) ->
    @state.currentUser = currentUser

### View methods ###
class View
  setup: (Controller, Model) =>
    @i = select.interface
    @Controller = Controller
    @Model = Model
    $(@i).append('<h2>Annotation Filters</h2>')
    @drawPager(@Model.get('index'), @Model.get('total'))
    $(@i).append('<div id="' + @Controller.getSelector('button') + '"></div>')
    @drawButton(select.button.user, 'none', 'user')
    @drawButton(select.button.user, 'mine', 'user')
    @drawButton(select.button.user, 'all', 'user')
    return

  update: () ->
    # Draw based on current state
    return

  viewerShown: (Viewer) ->
    # For when Annotator viewer appears
    return

  drawButton: (loc, id, filter) ->
    classes = @Controller.getSelector(['button',[id, filter]])
    $('#' + loc).append($('<span>',
      {id: id, class: classes})
      .text(id)
      .on('click', @Controller.buttonClick))

  drawActiveButton: (id) ->
    return

  drawCheckbox: (id, value) ->
    return

  drawAutocomplete: (id, values) ->
    return

  drawPager: (first, last) ->
    p = select.pager
    base = select.annotation + 'pager'
    $(@i).append($("<i id='first' class='#{base} #{p.arrow} #{p.first}'/>")).on("click", 'i#first', @Controller.pagerClick)
    $(@i).append($("<i id='prev' class='#{base} #{p.arrow} #{p.prev}'/>")).on("click", 'i#prev', @Controller.pagerClick)
    $(@i).append($("<span id='#{p.count}' class='#{base}'>").text(first + ' of ' + last))
    $(@i).append($("<i id='next' class='#{base} #{p.arrow} #{p.next}'/>")).on("click", 'i#next', @Controller.pagerClick)
    $(@i).append($("<i id='last' class='#{base} #{p.arrow} #{p.last}'/>")).on("click", 'i#last', @Controller.pagerClick)
    $('.' + base).wrapAll("<div id='#{p.wrapper}'></div>")
    return

  drawPagerCount: (first, last) ->
    $('#' + select.pager.count).text(first + ' of ' + last)

  drawFilter: (id, value) ->
    return

  eraseFilter: (id, value) ->
    return

  showAnnotations: (annotations) ->
    return

  hideAnnotations: (annotations) ->
    return

  scrollTo: (annotation) ->
    highlight = $(annotation.highlights[0])
    $("html, body").animate({
      scrollTop: highlight.offset().top - 20
    }, 150)
