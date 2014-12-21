
$ = jQuery;

class Annotator.Plugin.Privacy extends Annotator.Plugin

	options:
	  privacyClass: "annotator-privacy"
	  publicClass: "annotator-privacy-public"
	  privateClass: "annotator-privacy-private"

	pluginInit: ->
    	return unless Annotator.supported()
    	@annotator.viewer.addField({
    	  load: @updateViewer
    	})

	updateViewer: (field, annotation) =>
		field = $(field)
		field.addClass(@options.privacyClass)
		if annotation.permissions["read"].length > 0
			field.addClass(@options.privateClass).html(Annotator.Util.escape("Private"))
		else
		 	field.addClass(@options.publicClass).html(Annotator.Util.escape("Public"))		  	