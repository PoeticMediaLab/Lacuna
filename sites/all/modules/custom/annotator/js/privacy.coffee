# Plugin to manage annotation privacy -- allows user to select which organic groups will have access to the annotation

$ = jQuery;

class Annotator.Plugin.Privacy extends Annotator.Plugin

	options:
	  privacyClass: "annotator-privacy"
	  publicClass: "annotator-privacy-public fa fa-unlock"
	  privateClass: "annotator-privacy-private fa fa-lock"

	events:
		'annotationEditorShown'     : "updateAutocompleteGroups"

	field: null

	input: null

	pluginInit: ->
		return unless Annotator.supported()

		@field = @annotator.editor.addField({
			label: Annotator._t('Privacy: what groups should see your annotations?')
		#load: this.updateField
			options: ['blue', 'pink', 'red']
		#submit: this.setAnnotationGroups
		})

	#@annotator.viewer.addField({
	#  load: this.updateViewer
	#})

	setAnnotationGroups: (field, annotation) =>
		annotation.groups = @input.val()

	updateAutocompleteGroups: (event, annotation) =>
		groups_html = ''
		groups = Drupal.settings.annotator_groups
		console.log groups
		for gid, group of groups
			if gid not in groups
				groups_html += '<span class="annotations-privacy-group' + gid + '">'
				groups_html += group
				groups_html += '</span>'
				groups.gid = group
		console.log groups_html
		$(@field).html(groups_html)
	#@input.catcomplete({source: tags})

	updateViewer: (field, annotation) ->
		field = $(field)

		if annotation.groups and $.isArray(annotation.groups) and annotation.groups.length
			field.addClass('annotator-groups').html(->
				string = $.map(annotation.groups,(group) ->
					'<span class="annotator-group">' +
						Annotator.Util.escape(group) +
						'</span>'
				).join(' ')
			)
		else
			field.remove()

	updateField: (field, annotation) =>
		console.log field
#@input.val(annotation.groups)