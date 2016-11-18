# Plugin to manage annotation privacy -- allows user to select which organic groups will have access to the annotation

$ = jQuery;

class Annotator.Plugin.Privacy extends Annotator.Plugin

  events:
    'annotationEditorShown'   : "addPrivacy"
    'annotationEditorSubmit'  : "savePrivacy"

  field: null

  input: null

  className:
    default: 'annotator-privacy'
    types:
      wrapper: 'annotator-privacy-types'
      default: 'annotator-privacy-type'
      private: 'annotator-privacy-private'
      instructor: 'annotator-privacy-instructor'
      'peer-groups': 'annotator-privacy-peer-groups'
      everyone: 'annotator-privacy-everyone'
    groups:
      wrapper: 'annotator-privacy-groups'
      default: 'annotator-privacy-group'


  pluginInit: ->
    return unless Annotator.supported()

    @field = @annotator.editor.addField({
      label: Annotator._t('Privacy')
    })
    $(@field).addClass(@className.default + ' fa fa-lock') # distinguish this field

    @annotator.viewer.addField({
      load: @updateViewer
    })

  addPrivacy: (event, annotation) =>
    # use annotation's saved data if possible, otherwise use defaults
    settings = if annotation.privacy_options then annotation.privacy_options else Drupal.settings.privacy_options
    groups_html = privacy_html = show_groups = ''

    # NOTE: Listener and logic for selecting these spans is in annotator_privacy.js, not this file
    privacy_html += '<span class="' + @className.types.wrapper + '">'
    for privacy_type in ["Private", "Instructor", "Peer-Groups", "Everyone"]
      checked = if settings.audience[privacy_type.toLowerCase()] then 'checked' else ''
      if "Peer-Groups" == privacy_type && "checked" == checked
        show_groups = 'show-groups'
      peer_groups = settings.groups.peer_groups
      if peer_groups.length == 0 then peer_groups_disabled = ' peer-groups-disabled'
      else peer_groups_disabled = ''
      privacy_html += '<span class="' + @className.types.default + ' ' + checked + peer_groups_disabled + '" id="' + privacy_type + '">' + privacy_type + '</span>'
    privacy_html += '</span>'

    groups = settings.groups
    for group_type, group_object of groups
      for gid, group of group_object
        groups_html += '<label class="' + @className.groups.wrapper + ' ' + show_groups + '">'
        checked = if group.selected then 'checked="checked"' else ''
        groups_html += '<input type="checkbox" class="' + @className.groups.default + ' ' + group_type + '" value="' + gid + '" ' + checked + ' />'
        groups_html += group[0]
        groups_html += '</label>'
    groups_html = '<span class="' + @className.groups.wrapper + ' ' + show_groups + '">' + groups_html + '</span>'
    $(@field).html(privacy_html + groups_html)

  savePrivacy: (Editor, annotation) =>
    annotation.privacy_options = {}
    peer_groups = {}
    audience = {}
    $('.annotator-editor .' + @className.types.default).each (i, el) =>
      type = $(el).attr("id").toLowerCase()
      if $(el).hasClass("checked")
        audience[type] = 1
      else
        audience[type] = 0
      $('.annotator-editor input.' + @className.groups.default + '[type=checkbox]').each ->
        checked = if $(this).is(":checked") then 1 else 0
        gid = $(this).val()
        parent = $(this).parent()
        group_name = parent[0].textContent
        peer_groups[gid] = 0: group_name, selected: checked

    # Added by <codymleff@gmail.com> on 11/14/16 to prevent setting
    # Peer-Groups as the audience without having any peer groups
    # selected.
    if audience['peer-groups']
      no_peer_groups_selected = true
      for group of peer_groups
        if peer_groups[group].selected
          no_peer_groups_selected = false
          break
      if no_peer_groups_selected
        audience['peer-groups'] = 0
        if not audience['instructor']
          audience['private'] = 1

    annotation.privacy_options.audience = audience
    annotation.privacy_options.groups = {peer_groups: peer_groups}

  updateViewer: (field, annotation) =>
    if not annotation.privacy_options?
      return
    audience = '<div class="' + @className.types.wrapper + '">'
    for audience_type, checked of annotation.privacy_options.audience
      if checked
        audience += '<span class="' + @className.types.default + ' ' + @className.types[audience_type]
        if audience_type == 'private'
          audience += ' fa fa-lock'
        if audience_type == 'everyone'
          audience += ' fa fa-unlock'
        if 'peer-groups' == audience_type
          audience += ' fa fa-users'
          has_groups = true
        audience += '">' + audience_type.replace('-', ' ') + '</span>'
    audience += '</div>'
    groups = ''
    if has_groups
      groups = '<div class="' + @className.groups.wrapper + '">'
      for group_type, gids of annotation.privacy_options.groups
        for gid, group of gids
          if group && group.selected
            groups += '<span class="' + @className.groups.default + ' checked ' + group_type + ' fa fa-check">' + group[0] + '</span>'
      groups += '</div>'
    $(field).addClass(@className.default).html audience + groups
