# Display author name in Annotator Viewer

$ = jQuery

class Annotator.Plugin.Author extends Annotator.Plugin
  authorClass: 'annotator-author fa fa-user'

  pluginInit: ->
    return unless Annotator.supported()
    @annotator.viewer.addField({
      load: @updateViewer
    })

  updateViewer: (field, annotation) =>
    field = $(field)
    if annotation.user and annotation.user.name and typeof annotation.user.name == 'string'
      user = ' ' + Annotator.Util.escape(annotation.user.name)
      field.html(user).addClass(@authorClass)
    else
      field.remove()