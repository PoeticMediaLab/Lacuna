
$ = jQuery;

class Annotator.Plugin.Comment extends Annotator.Plugin

	options:
	  commentClass: "annotator-comment"
	  base_url: "drupal7.dev"

	pluginInit: ->
    	return unless Annotator.supported()
    	@annotator.viewer.addField({
    	  load: @updateViewer
    	})

	updateViewer: (field, annotation) =>
		field = $(field)
		field.addClass(@options.commentClass)
		if annotation.comment_count != "0"
			field.html('<a href="'+@options.base_url+annotation.links[0].href+'#comments">'+annotation.comment_count+" Comments</a>")
		else
		 	field.html(annotation.comment_count+' Comments')