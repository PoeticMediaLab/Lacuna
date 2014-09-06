# Categories plugin allows users to add multiple annotations to the same selection
class Annotator.Plugin.Categories extends Annotator.Plugin
  # HTML templates for the plugin UI.
  html:
    element: """
             <li class="annotator-categories">
             <h4>"""+Annotator._t('Categories')+"""</h4>
             <br clear="all">
             </li>
             """

  options:
    categories: []
    categorizeAnnotations    : {}
    originalAnnotations      : {}
    classForSelectedCategory : "selected"

  events:
    '.annotator-category click' : "toggleSelectedCategory"
    'annotationEditorSubmit'    : "stringifyCategorizeAnnotation"
    'annotationEditorShown'     : "parseCategorizeAnnotatonsFromText"
    '.annotator-cancel click'   : "loadOriginalAnnotations"


  # The field element added to the Annotator.Editor wrapped in jQuery. Cached to
  # save having to recreate it everytime the editor is displayed.
  field: null

  # The input element added to the Annotator.Editor wrapped in jQuery. Cached to
  # save having to recreate it everytime the editor is displayed.
  input: null

  categoriesHtml: ->
    categories  = @options.categories
    string = $.map(categories,(category) ->
      "<div class='annotator-category'>"+category.name+"</div>"
    ).join(' ')

    string

  # Public: Initialises the plugin and adds categories field wrapper to annotator wrapper (editor and viewer)
  # Returns nothing.
  pluginInit: ->
    element = $(@html.element)
    element.find('h4').after(@categoriesHtml())
    @element.find('.annotator-listing .annotator-item:first-child').after element

    @annotator.viewer.addField({
      load: @updateViewer,
      categories: @options.categories
    })

  constructor: (element, categories) ->
    super element, categories
    @options.categories = categories if categories

  setSelectedCategory: (currentCategory) ->
    @element.find('.annotator-category').removeClass @options.classForSelectedCategory
    $(currentCategory).addClass @options.classForSelectedCategory

  toggleSelectedCategory: (event) ->
    @setTextForCategory @selectedCategory().html(), @annotationField().val()
    category = $(event.target).html()
    text = @getTextForCategory category
    @annotationField().val(text)
    @setSelectedCategory event.target
    @annotationField().focus()
    @annotator.publish('annotatorSelectedCategoryChanged', [category])

  categoriesWrapperDom: ->
    @element.find('.annotator-categories')

  selectedCategory: ->
    @element.find('''.annotator-category.'''+@options.classForSelectedCategory)

  setAnnotationForFirstCategory: ->
    @element.find('.annotator-category').removeClass @options.classForSelectedCategory
    @element.find('.annotator-category:first').addClass @options.classForSelectedCategory
    @annotationField().val @getTextForCategory(@element.find('.annotator-category:first').html())
    @element.find('.annotator-category:first').trigger 'click'


  annotationField: ->
    @element.find("textarea:first")

  getTextForCategory: (category) ->
    @options.categorizeAnnotations[category] || ''

  setTextForCategory: (category, annotation) ->
    if annotation? && not /^\s*$/.test(annotation)
      @options.categorizeAnnotations[category] = annotation

  stringifyCategorizeAnnotation: (editor, annotation)->
    # Annotation for selected category is not saved yet. So lets do it now
    # @setTextForCategory @selectedCategory().html(), @annotationField().val()
    # if @categoriesWithAnnotation().length > 0
    #   annotation.category =
    #   annotation.text = JSON.stringify(@options.categorizeAnnotations)
    # else
    #   annotation.text = ''

  parseCategorizeAnnotatonsFromText: (editor, annotation) ->
    # @options.categorizeAnnotations = {}
    # @options.originalAnnotations   = {}
    # if annotation.text
    #   @options.categorizeAnnotations = JSON.parse(annotation.text)
    #   @options.originalAnnotations   = @options.categorizeAnnotations
    @setAnnotationForFirstCategory()
    @fixEditorDimension()

  categoriesWithAnnotation: ->
    categories = []
    that = @
    $.each(@options.categories,(i, category) ->
      categories.push(category) if that.getTextForCategory(category).length > 0
    )
    categories

  loadOriginalAnnotations: ->
    @options.categorizeAnnotations = @options.originalAnnotations
    # revert value of textarea
    @setAnnotationForFirstCategory()

  fixEditorDimension: ->
    dom = @categoriesWrapperDom()
    categoriesWidth = $.map(dom.find('.annotator-category'),(category) ->
      parseInt($(category).css('width')) +
      parseInt($(category).css('padding-left')) +
      parseInt($(category).css('padding-right')) +
      parseInt($(category).css('margin-left')) +
      parseInt($(category).css('margin-right'))
    ).reduce (x,y) -> x + y

    # 18 is width of colors tags wrapper
    categoriesWidth += parseInt(dom.css('padding-left')) + parseInt(dom.css('padding-right')) + 18

    # Lets increase width of categories dom
    if dom.width() < categoriesWidth
      dom.width categoriesWidth

  updateViewer: (field, annotation) ->
    field = $(field).hide()

    if annotation.text? and annotation.text.length > 0
      category = annotation.category
      # categorizeText = JSON.parse(annotation.text)
      # categories     = Object.keys(categorizeText)
      viewerField    = field.parent("li.annotator-annotation").find("div:first").addClass("categories")
      # Remove raw annotator text
      viewerField.empty()

      $.each(@categories, (i, category) ->
        annotation = $('<div>').addClass('categorize-text').attr('id', category.replace(RegExp(" ", "g"), "_"))
        annotation.append $('<span>').addClass('text-category').html(category.name)
        # annotation.append $('<span>').html(categorizeText[category])

        viewerField.append annotation
      )
