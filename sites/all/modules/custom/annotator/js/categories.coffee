#
# A plugin for Annotator that adds a field that allows users to categorize their
# annotations; loads the annotations from an object passed with the plugin is
# initialized. In Drupal, we get these values from our admin settings page
# @see Annotator module
#
# Mike Widner <mikewidner@stanford.edu>
#

$ = jQuery;

class Annotator.Plugin.Categories extends Annotator.Plugin
  options:
    categories: []
    categoryColorClasses: {}
    categoryField: "annotator-category-field"
    categoryClass: "annotator-category"
    classForSelectedCategory : "annotator-category-selected"
    emptyCategory: "Highlight"
    annotatorHighlight: 'span.annotator-hl'

  events:
    '.annotator-category click' : "changeSelectedCategory"
    'annotationEditorSubmit'    : "saveCategory"
    'annotationEditorShown'     : "highlightSelectedCategory"
    'annotationsLoaded'         : 'changeHighlightColors'

  # The field element added to the Annotator.Editor wrapped in jQuery. Cached to
  # save having to recreate it everytime the editor is displayed.
  field: null

  # The input element added to the Annotator.Editor wrapped in jQuery. Cached to
  # save having to recreate it everytime the editor is displayed.
  input: null

  widthSet: false

  # Public: Initialises the plugin and adds categories field wrapper to annotator wrapper (editor and viewer)
  # Returns nothing.
  pluginInit: ->
    return unless Annotator.supported()
    @options.categoryColorClasses[@options.emptyCategory] = @options.categoryClass + '-none'
    @field = @annotator.editor.addField({
      label: Annotator._t('Category')
      options: @options
    })
    $(@field).addClass(@options.categoryField + ' fa fa-folder-o') # distinguish this field

    # Add support for touch devices
    $(document).delegate(".annotator-category", "tap", preventDefault: false, @changeSelectedCategory)

    @annotator.viewer.addField({
      load: @updateViewer
      options: @options
    })

    @input = $(@field).find(':input')

  constructor: (element, options) ->
    super element, options
    @element = element

  changeHighlightColors: (annotations) ->
    # Update the highlight colors for all categorized annotations
    # Called after all annotations loaded
    i = 0
    for category in @options.category
      cssClass = @options.categoryClass + '-' + i
      @options.categoryColorClasses[category] = cssClass
      i++
    for annotation in annotations
      # check if category is empty
      if !annotation.category? or !annotation.category.length
        annotation.category = @options.emptyCategory
      for highlight in annotation.highlights
        $(highlight).addClass(@options.categoryColorClasses[annotation.category])

  setSelectedCategory: (currentCategory) ->
    # Change the selected category in the editor window
    # clear any selection
    $(@field).find('.annotator-category').removeClass @options.classForSelectedCategory
    # add CSS to new selection
    $(@field).find('.annotator-category:contains(' + currentCategory + ')').addClass @options.classForSelectedCategory

  updateViewer: (field, annotation) ->
    # On mouseover, gets the annotation object
    # For displaying mouseover data
    field = $(field)
    field.addClass(@options.categoryClass).html(@options.emptyCategory)
    # if !annotation.category?
    #   annotation.category = @options.emptyCategory
    if annotation.category? and annotation.category.length > 0
      field.addClass(@options.categoryClass).html(annotation.category)
      if annotation.category in @options.category
        field.addClass(@options.categoryColorClasses[annotation.category])

  changeSelectedCategory: (event) =>
    # HTML contains the string with the name of the category
    category = $(event.target).html()
    @setSelectedCategory category

  saveCategory: (Editor, annotation) ->
    # Update display, provide warning about default
    annotation.category = $(@field).find('.' + @options.classForSelectedCategory).html()
    # With CKEditor editor enabled, this will never fire
    # But we'll keep it here just in case that plugin isn't on
    # Validation of category choice occurs in the Annotation Store
    if annotation.text? and (annotation.text.length > 0) and !annotation.category?
      window.alert("You did not choose a category, so the default '#{@options.category[0]}' has been chosen.")
      annotation.category = @options.category[0]
    @changeHighlightColors([annotation])

  highlightSelectedCategory: (event, annotation) ->
    # when editor first shown
    if !annotation.category?
      annotation.category = @options.emptyCategory
      CKEDITOR.instances['annotator-field-0'].on('change', (event) =>
        if event.editor.getData()
          category = $(@field).find('.' + @options.classForSelectedCategory).html()
          @setSelectedCategory('Comment') if !category?
          event.removeListener()
      )

    categoryHTML = ""
    for category in @options.category
      categoryHTML += '<span class="' + @options.categoryClass
      categoryHTML += ' ' + @options.categoryColorClasses[category] + '">'
      categoryHTML += category
      categoryHTML += '</span>'
    $(@field).html(categoryHTML)

    if not @widthSet
      # Only set the width once
      @widthSet = true
      totalWidth = 5  # for a tiny bit of extra padding
      # Sum up widths of each category.
      $("span.annotator-category").each (index) ->
        totalWidth += parseInt($(this).outerWidth(true), 10)
        return
      # Set widget width
      $(".annotator-editor .annotator-widget").width totalWidth

    @setSelectedCategory(annotation.category)
