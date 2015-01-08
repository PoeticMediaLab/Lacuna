
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
    if annotation.comment_count != "0"
      field.html('<a href="'+link+'#comments">'+annotation.comment_count+' Comments</a><a href="'+link+'#comment-form" class="annotator-new-comment-count-button" title="New Comment">&nbsp;&nbsp;&nbsp;&nbsp;</a>')
    else
      field.html(annotation.comment_count+' Comments<a href="'+link+'#comment-form" class="annotator-new-comment-count-button" title="New Comment">&nbsp;&nbsp;&nbsp;&nbsp;</a>')
