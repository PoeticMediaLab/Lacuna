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
    # use annotation's saved data if possible, otherwise use defaults
    settings = if annotation.privacy_options then annotation.privacy_options else Drupal.settings.privacy_options
    groups_html = privacy_html = show_groups = ''

    privacy_html += '<span class="privacy types">'
    for privacy_type in ["Private", "Instructor", "Peer-Groups", "Everyone"]
      checked = if settings.audience[privacy_type.toLowerCase()] then 'checked' else ''
      if "Peer-Groups" == privacy_type && "checked" == checked
        show_groups = 'show-groups'
      privacy_html += '<span class="privacy-type ' + checked + '" id="' + privacy_type + '">' + privacy_type + '</span>'
    privacy_html += '</span>'

    groups = settings.groups
    for group_type, group_object of groups
      for gid, group of group_object
        groups_html += '<label class="privacy group">'
        checked = if group.selected then 'checked="checked"' else ''
        groups_html += '<input type="checkbox" class="privacy-group ' + group_type + '" value="' + gid + '" ' + checked + ' />'
        groups_html += group[0]
        groups_html += '</label>'
    groups_html = '<span class="privacy-groups ' + show_groups + '">' + groups_html + '</span>'
    $(@field).html(privacy_html + groups_html)

  savePrivacy: (event, annotation) ->
    annotation.privacy_options = {}
    peer_groups = {}
    audience = {}
    $('.annotator-editor span.privacy-type').each(->
      type = $(this).attr("id").toLowerCase()
      if $(this).hasClass("checked")
        audience[type] = 1
      else
        audience[type] = 0
      $('.annotator-editor input.privacy-group[type=checkbox]').each(->
        checked = if $(this).is(":checked") then 1 else 0
        gid = $(this).val()
        parent = $(this).parent()
        group_name = parent[0].textContent
        peer_groups[gid] = 0: group_name, selected: checked
      )
    )
    annotation.privacy_options.audience = audience
    annotation.privacy_options.groups = {peer_groups: peer_groups}

  updateViewer: (field, annotation) ->
    if annotation.privacy_options
      audience = '<div class="privacy-types">'
      for audience_type, checked of annotation.privacy_options.audience
        if checked
          audience += '<span class="privacy-type">' + audience_type + '</span>'
          if 'peer-groups' == audience_type
            has_groups = true
      audience += '</div>'
      groups = ''
      if has_groups
        groups = '<div class="privacy-groups">'
        i = 0
        for group_type, gids of annotation.privacy_options.groups
          for gid, group of gids
            if group && group.selected
              groups += '<span class="privacy-group checked ' + group_type + '">' + group[0] + '</span>'
        groups += '</div>'
      $(field).addClass("privacy").html audience + groups
