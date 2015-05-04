#
# An Annotator plugin to add CKEditor support to annotation editing
# Developed for Lacuna Stories
#
# Mike Widner <mikewidner@stanford.edu>, 2015
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; either version 2
# of the License, or (at your option) any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
#
#####
$ = jQuery

# This is the default comment field for annotations
# CKEditor looks for a textarea with a specific ID
# then adds itself immediately after it
editor_instance = 'annotator-field-0'

class Annotator.Plugin.RichText extends Annotator.Plugin

  # events:
  #   'annotationEditorSubmit' : 'convertText'

  pluginInit: ->
    return unless Annotator.supported()
    editor = @annotator.editor
    CKEDITOR.replace(editor_instance, {
      extraplugins: 'image2, oembed',
      toolbar: [
          { name: 'basicstyles', items: [ 'RemoveFormat' ] },
          { name: 'paragraph', groups: [ 'list', ], items: [ 'NumberedList', 'BulletedList'] },
          { name: 'links', items: [ 'Link', 'Unlink', ] },
          { name: 'insert', items: [ 'Image2', 'oEmbed' ] },
        ]
      }
    )
    @annotator.subscribe 'annotationEditorSubmit', (Editor) => @saveText(Editor)
    @annotator.subscribe 'annotationViewerShown', (Viewer) => @showText(Viewer)

  # Convert the rich text field into something Annotator recognizes
  saveText: (Editor) =>
    # Grab the user-created text, put in the right annotator field
    Editor.annotation.text = CKEDITOR.instances[editor_instance].getData()

  showText: (field, annotation) =>
    textDiv = $(field.parentNode).find('div:first-of-type')[0]
    textDiv.innerHTML = annotation.text
    $(textDiv).addClass('richText-annotation')
    return


