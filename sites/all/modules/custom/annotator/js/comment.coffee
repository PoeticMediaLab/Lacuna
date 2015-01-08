
$ = jQuery;

class Annotator.Plugin.Comment extends Annotator.Plugin

	options:
   commentClass: "annotator-comment-count fa fa-reply"

  pluginInit: ->
    return unless Annotator.supported()
    @annotator.viewer.addField({
      load: @updateViewer
    })

  updateViewer: (field, annotation) =>
    field = $(field)
    field.addClass(@options.commentClass)
    link = Drupal.settings.annotator_comment.base_root + annotation.links[0].href
    field.html('&nbsp;<a href="' + link + '#comments" target="_blank">' + annotation.comment_count + ' Comment' + (if annotation.comment_count != "1" then 's' else '') + '</a>')
