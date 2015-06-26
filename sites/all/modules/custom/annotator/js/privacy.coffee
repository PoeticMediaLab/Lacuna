# Plugin to manage annotation privacy -- allows user to select which organic groups will have access to the annotation

$ = jQuery;

class Annotator.Plugin.Privacy extends Annotator.Plugin

  events:
    'annotationEditorShown'   : "addPrivacy"
    'annotationEditorSubmit'  : "savePrivacy"

  field: null

  input: null

  pluginInit: ->
    return unless Annotator.supported()

    @field = @annotator.editor.addField({
      label: Annotator._t('Privacy')
    })

    @annotator.viewer.addField({
      load: this.updateViewer
    })

  addPrivacy: (event, annotation) =>
    # default settings
    settings = Drupal.settings.privacy_options

    if annotation.privacy_options
      for attr in annotation.privacy_options
        console.log attr
        settings[attr] = annotation.privacy_options[attr]

    console.log settings
    groups_html = privacy_html = ''

    privacy_html += '<span class="privacy types">'
    for privacy_type in ["Private", "Instructor", "Co-Learners"]
      checked = if settings.audience[privacy_type.toLowerCase()] then 'checked' else ''
      privacy_html += '<span class="privacy-type ' + checked + '" id="' + privacy_type + '">' + privacy_type + '</span>'
    privacy_html += '</span>'

    groups = settings.groups
    for group_type, group_object of groups
      for gid, group of group_object
        groups_html += '<label class="privacy groups">'
        checked = if group.selected then 'checked="checked"' else ''
        groups_html += '<input type="checkbox" class="privacy-group ' + group_type + '" value="' + gid + '" ' + checked + ' />'
        groups_html += group[0]
        groups_html += '</label>'
    $(@field).html(privacy_html + groups_html)

  savePrivacy: (event, annotation) ->
    selected_groups = []
    $('span.privacy-type').each(->
      if $(this).hasClass("checked")
        selected_groups.push($(this).val().toUpperCase())
        if "Co-Learners" == $(this).attr("id")
          $('input.privacy-group[type=checkbox]').each(->
            if $(this).is(":checked")
              selected_groups.push($(this).val())
          )
    )
    annotation.groups = selected_groups

    if annotation.text? and (annotation.text.length > 0) and 0 == annotation.groups.length
      window.alert("You did not select a Privacy Setting, so the default 'Instructor' has been chosen.")
      annotation.groups = ["INSTRUCTOR"]

  updateViewer: (field, annotation) ->
    field = $(field)
    console.log annotation
    if annotation.groups and $.isArray(annotation.groups) and annotation.groups.length
      field.addClass('annotator-groups').html(->
        string = $.map(annotation.groups,(group) ->
          '<span class="annotator-group">' +
            Annotator.Util.escape(group) +
            '</span>'
        ).join(' ')
      )
    else
      field.remove()
