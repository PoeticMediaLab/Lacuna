# Plugin to manage annotation privacy -- allows user to select which organic groups will have access to the annotation

$ = jQuery;

class Annotator.Plugin.Privacy extends Annotator.Plugin

  options:
    privacyClass: "annotator-privacy"
    publicClass: "annotator-privacy-public fa fa-unlock"
    privateClass: "annotator-privacy-private fa fa-lock"

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
    groups_html = privacy_html = ''

    for privacy_type in ["Private", "Instructor", "Co-Learners"]
      privacy_html += '<label class="privacy types">'
      privacy_html += '<input type="checkbox" class="privacy-type" id="' + privacy_type + '" value="' + privacy_type + '" />'
      privacy_html += privacy_type
      privacy_html += '</label>'

    groups = Drupal.settings.annotator_groups
    for gid, group of groups
      groups_html += '<label class="privacy groups">'
      groups_html += '<input type="checkbox" class="privacy-group" value="' + gid + '" />'
      groups_html += group
      groups_html += '</label>'
    $(@field).html(privacy_html + groups_html)

  savePrivacy: (event, annotation) ->
    selected_groups = []
    $('input.privacy-type[type=checkbox]').each(->
      if $(this).is(":checked")
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
    # @Mike not sure how you want to display the group info, this is just a proof of concept listing the groups
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
