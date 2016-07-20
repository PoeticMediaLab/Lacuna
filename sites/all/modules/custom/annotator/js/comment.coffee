#
# Allow users to view comments and add new threaded comments to annotations
#
$ = jQuery

class Annotator.Plugin.Comment extends Annotator.Plugin

  commentClass: "annotator-comment fa fa-reply"

  pluginInit: ->
    return unless Annotator.supported()
    @annotator.viewer.addField({
      load: @updateViewer
    })

  updateViewer: (field, annotation) =>
    field = $(field)
    n_comments = 0
    replies = "Replies"
    if Object.keys(annotation.comments).length > 0
      n_comments = Object.keys(annotation.comments).length
      if n_comments == 1
        replies = "Reply"
    if annotation.links?
      link = Drupal.settings.annotator_comment.base_root + annotation.links[0].href
      field.html("<a href=\"#{link}#comments\" target=\"_blank\">#{n_comments} #{replies}</a>").addClass(@commentClass)
    else
      field.remove()

