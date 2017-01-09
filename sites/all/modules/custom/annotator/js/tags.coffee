# NOTE: Tags is a core Annotator plugin
# This version has been modified for use in Drupal
# and to allow for comma-separated tags -MLW

$ = jQuery


# Public: Tags plugin allows users to tag thier annotations with metadata
# stored in an Array on the annotation as tags.
class Annotator.Plugin.Tags extends Annotator.Plugin

  options:
    # Configurable function which accepts a string (the contents)
    # of the tags input as an argument, and returns an array of
    # tags.
    parseTags: (string) ->
      string = $.trim(string)

      tags = []
      tags = string.split(/,/) if string
      tags

    # Configurable function which accepts an array of tags and
    # returns a string which will be used to fill the tags input.
    stringifyTags: (array) ->
      array.join(", ")

  events:
    'annotationEditorSubmit'    : "updateAutocompleteTags"

  # The field element added to the Annotator.Editor wrapped in jQuery. Cached to
  # save having to recreate it everytime the editor is displayed.
  field: null

  # The input element added to the Annotator.Editor wrapped in jQuery. Cached to
  # save having to recreate it everytime the editor is displayed.
  input: null

  # Public: Initialises the plugin and adds custom fields to both the
  # annotator viewer and editor. The plugin also checks if the annotator is
  # supported by the current browser.
  #
  # Returns nothing.
  pluginInit: ->
    return unless Annotator.supported()

    @field = @annotator.editor.addField({
      label: Annotator._t('Add tags here, separate with commas') + '\u2026'
      load: @updateField
      submit: @setAnnotationTags
    })

    @annotator.viewer.addField({
      load: @updateViewer
    })

    # Add a filter to the Filter plugin if loaded.
    # if @annotator.plugins.Filter
    #   @annotator.plugins.Filter.addFilter
    #     label: Annotator._t('Tag')
    #     property: 'tags'
    #     isFiltered: Tags.filterCallback

    @input = $(@field).find(':input')

  # Public: Extracts tags from the provided String.
  #
  # string - A String of tags seperated by spaces.
  #
  # Examples
  #
  #   plugin.parseTags('cake chocolate cabbage')
  #   # => ['cake', 'chocolate', 'cabbage']
  #
  # Returns Array of parsed tags.
  parseTags: (string) ->
    @options.parseTags(string)

  # Public: Takes an array of tags and serialises them into a String.
  #
  # array - An Array of tags.
  #
  # Examples
  #
  #   plugin.stringifyTags(['cake', 'chocolate', 'cabbage'])
  #   # => 'cake chocolate cabbage'
  #
  # Returns Array of parsed tags.
  stringifyTags: (array) ->
    @options.stringifyTags(array)

  # Annotator.Editor callback function. Updates the @input field with the
  # tags attached to the provided annotation.
  #
  # field      - The tags field Element containing the input Element.
  # annotation - An annotation object to be edited.
  #
  # Examples
  #
  #   field = $('<li><input /></li>')[0]
  #   plugin.updateField(field, {tags: ['apples', 'oranges', 'cake']})
  #   field.value # => Returns 'apples oranges cake'
  #
  # Returns nothing.
  updateField: (field, annotation) =>
    value = ''
    value = this.stringifyTags(annotation.tags) if annotation.tags
    @input.val(value)

  # Annotator.Editor callback function. Updates the annotation field with the
  # data retrieved from the @input property.
  #
  # field      - The tags field Element containing the input Element.
  # annotation - An annotation object to be updated.
  #
  # Examples
  #
  #   annotation = {}
  #   field = $('<li><input value="cake chocolate cabbage" /></li>')[0]
  #
  #   plugin.setAnnotationTags(field, annotation)
  #   annotation.tags # => Returns ['cake', 'chocolate', 'cabbage']
  #
  # Returns nothing.
  setAnnotationTags: (field, annotation) =>
    annotation.tags = this.parseTags(@input.val())

  # Sorts tags after a new tag is added by AJAX.  Modified to correctly
  # re-sort flagged (curated) tags above other tags.
  sortTags: (a, b) ->
    if a.flagged and !b.flagged then return -1
    if !a.flagged and b.flagged then return 1
    return a.label.localeCompare(b.label)

  updateAutocompleteTags: (event, annotation) =>
    # update the autocomplete field in the Editor
    # based on any new tags
    tags = (tag.label for tag in Drupal.settings.annotator_tags.tags)
    for tag in annotation.tags
      if tag not in tags
        Drupal.settings.annotator_tags.tags.push({label: tag, flagged: 0})
    @input.catcomplete({source: Drupal.settings.annotator_tags.tags.sort( @sortTags ) })

  # Annotator.Viewer callback function. Updates the annotation display with tags
  # removes the field from the Viewer if there are no tags to display.
  #
  # field      - The Element to populate with tags.
  # annotation - An annotation object to be display.
  #
  # Examples
  #
  #   field = $('<div />')[0]
  #   plugin.updateField(field, {tags: ['apples']})
  #   field.innerHTML # => Returns '<span class="annotator-tag">apples</span>'
  #
  # Returns nothing.
  updateViewer: (field, annotation) ->
    field = $(field)

    if annotation.tags and $.isArray(annotation.tags) and annotation.tags.length
      field.addClass('annotator-tags').html(->
        $.map(annotation.tags, (tag) ->
          '<span class="annotator-tag">' +
          Annotator.Util.escape(tag) +
          '</span>'
        ).join(' ')
      )
    else
      field.remove()

# Checks an input string of keywords against an array of tags. If the keywords
# match _all_ tags the function returns true. This should be used as a callback
# in the Filter plugin.
#
# input - A String of keywords from a input field.
#
# Examples
#
#   Tags.filterCallback('cat dog mouse', ['cat', 'dog', 'mouse']) //=> true
#   Tags.filterCallback('cat dog', ['cat', 'dog', 'mouse']) //=> true
#   Tags.filterCallback('cat dog', ['cat']) //=> false
#
# Returns true if the input keywords match all tags.
Annotator.Plugin.Tags.filterCallback = (input, tags = []) ->
  matches  = 0
  keywords = []
  if input
    keywords = input.split(/,/g)
    for keyword in keywords when tags.length
      matches += 1 for tag in tags when tag.indexOf(keyword) != -1

  matches == keywords.length

