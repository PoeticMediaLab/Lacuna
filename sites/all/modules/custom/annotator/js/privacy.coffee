
$ = jQuery;

class Annotator.Plugin.Privacy extends Annotator.Plugin

	events:
		'annotationViewerShown' : "updateViewer"

	updateViewer: (event, annotations) =>
		annotation = annotations[0]
		if annotation.permissions["read"].length > 0
		  toAppend = " | Private"
		else
		  toAppend = " | Public"
		privacyStr = Annotator.Util.escape(toAppend)
		$('.annotator-user').append privacyStr
		  	