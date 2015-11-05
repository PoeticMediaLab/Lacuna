# Hide/show Annotator controls as appropriate
# A very slimmed down version of the core Permissions plugin

class Annotator.Plugin.Controls extends Annotator.Plugin

  pluginInit: ->
    return unless Annotator.supported()
    # Must run as a new field, upon load
    # Only way to get into the controls without having changes overwritten by Annotator
    @annotator.viewer.addField({
      load: @updateViewer
    })

  updateViewer: (field, annotation, controls) =>
    if (annotation.permissions?)
      if (!annotation.permissions.edit)
        controls.hideEdit()
      if (!annotation.permissions.del)
        controls.hideDelete()
