class Annotator.Plugin.Categories extends Annotator.Plugin
  html:
    element: """
             <li class="annotator-categories">
             <h4>"""+Annotator._t('Categories')+"""</h4>
             <br clear="all">
             </li>
             """
  options:
    categories: []
    # categorizeAnnotations    : {}
    classForSelectedCategory : "selected"
    categoryClass: "annotator-category"

  events:
    '.annotator-category click' : "changeSelectedCategory"
    'annotationEditorSubmit'    : "saveCategory"
    'annotationEditorShown'     : "selectCategory"
    'annotationViewerShown'     : "viewCategory"

  # The field element added to the Annotator.Editor wrapped in jQuery. Cached to
  # save having to recreate it everytime the editor is displayed.
  field: null

  # The input element added to the Annotator.Editor wrapped in jQuery. Cached to
  # save having to recreate it everytime the editor is displayed.
  input: null

  # categoriesHtml: ->
  #   string = $.map(@options.categories,(category) ->
  #     "<div class='annotator-category'>"+category.name+"</div>"
  #   ).join(' ')
  #   string

  # Public: Initialises the plugin and adds categories field wrapper to annotator wrapper (editor and viewer)
  # Returns nothing.
  pluginInit: ->
    return unless Annotator.supported()
    # console.log(@options, 'pluginInit @options')
    @field = @annotator.editor.addField({
      label: Annotator._t('Category')
      load: @updateField
      # submit: @setAnnotationCategory
      options: @options
    })

    @annotator.viewer.addField({
      load: @updateViewer
      options: @options
    })

    @input = $(@field).find(':input')

  constructor: (element, options) ->
    super element, options
    @element = element
    @options.categories = options.categories if options.categories

  annotationField: ->
    @element.find("textarea:first")

  selectedCategory: ->
    @element.find('''.annotator-category-'''+@options.classForSelectedCategory)

  setSelectedCategory: (currentCategory) ->
    @element.find('.annotator-category').removeClass @options.classForSelectedCategory
    $(currentCategory).addClass @options.classForSelectedCategory

  updateViewer: (field, annotation) ->
    # On mouseover, gets the annotation object
    # For displaying mouseover data
    # console.log(field, 'updateViewer field')
    # console.log(annotation, 'updateViewer annotation')
    # console.log(@options, 'updateViewer @options')
    field = $(field)
    field.addClass(@options.categoryClass).html('CATEGORY')
    if annotation.category and annotation.category.length
      field.addClass(@options.categoryClass).html(->
        annotation.category
        )
  # setTextForCategory: (category, annotation) ->
  #   if annotation? && not /^\s*$/.test(annotation)
  #     @options.categorizeAnnotations[category] = annotation

  updateField: (field, annotation) ->
    if @categories
      console.log(@categories, 'updateField @categories')
      @input.val(@categories.join(" "))
    # if annotation.category
    #   @input.val(annotation.category)

  changeSelectedCategory: (event) ->
    # console.log(this, 'changeSelectedCategory this')
    # console.log(event, 'changeSelectedCategory event')
    # @setTextForCategory @selectedCategory().html(), @annotationField().val()
    # category = $(event.target).html()
    # text = @getTextForCategory category
    # @annotationField().val(text)
    # @setSelectedCategory event.target
    # @annotationField().focus()
    # @annotator.publish('annotatorSelectedCategoryChanged', [category])

  saveCategory: (event) ->
    # console.log(this, 'saveCategory this')
    # console.log(event, 'saveCategory event')

  selectCategory: (event) ->
    # console.log(this, 'selectCategory this')
    # console.log(event, 'selectCategory event')
    annotation = event.annotation
    categoryHTML = ""
    # categoryNames = $.map(@options.categories, (category) ->
    #   return category.name
    #   )
    # categoryHTML = $(categoryNames).wrapAll('<span class="' + @options.categoryClass + '" />')
    $.each(@options.categories,(i, category) ->
      categoryHTML += '<span class="CLASS">'
      categoryHTML += category.name
      categoryHTML += '</span>'
      )
    # not sure how else to access the categoryClass variable
    categoryHTML = categoryHTML.replace(/CLASS/g, @options.categoryClass)
    $(@field).html(categoryHTML)
    if !annotation.category?
      # first category is default
      annotation.category = @options.categories[0].name
    @setSelectedCategory(annotation.category)

  viewCategory: (event) ->
    # console.log(this, 'viewCategory this')
    # console.log(event, 'viewCategory event')

  # categoriesWrapperDom: ->
  #   @element.find('.annotator-categories')

  # setAnnotationCategory: (field, annotation) ->
  #   annotation.category = @input.val()

  # fixEditorDimension: ->
  #   dom = @categoriesWrapperDom()
  #   categoriesWidth = $.map(dom.find('.annotator-category'),(category) ->
  #     parseInt($(category).css('width')) +
  #     parseInt($(category).css('padding-left')) +
  #     parseInt($(category).css('padding-right')) +
  #     parseInt($(category).css('margin-left')) +
  #     parseInt($(category).css('margin-right'))
  #   ).reduce (x,y) -> x + y

  #   # 18 is width of colors tags wrapper
  #   categoriesWidth += parseInt(dom.css('padding-left')) + parseInt(dom.css('padding-right')) + 18

  #   # Lets increase width of categories dom
  #   if dom.width() < categoriesWidth
  #     dom.width categoriesWidth
