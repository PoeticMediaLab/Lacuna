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

  pluginInit: ->
    return unless Annotator.supported()
    editor = @annotator.editor
    CKEDITOR.replace(editor_instance, {
      extraPlugins: 'lineutils,oembed,widget',
      toolbar: [
          { name: 'basicstyles', items: ['RemoveFormat', 'Bold', 'Italic'] },
          { name: 'paragraph', items: ['NumberedList', 'BulletedList'] },
          { name: 'links', items: ['Link', 'Unlink'] },
          { name: 'insert', items: ['oembed'] },
        ],
      # removeButtons: 'Underline,Strike,Subscript,Superscript,Anchor',
      removePlugins: 'elementspath,font,resize',
      allowedContent: true,
      format_tags: 'p;h1;h2;h3;pre'
      }
    )
    CKEDITOR.editorConfig

    @annotator.subscribe 'annotationEditorSubmit', (Editor) => @saveText(Editor)
    @annotator.subscribe 'annotationEditorShown', (Editor, annotation) => @updateText(Editor, annotation)
    @annotator.subscribe 'annotationViewerShown', (Viewer) => @convertText(Viewer)

  # Convert the rich text field into something Annotator recognizes
  saveText: (Editor) =>
    # Grab the user-created text, put in the right annotator field
    Editor.annotation.text = CKEDITOR.instances[editor_instance].getData()

  # load existing annotation text into the wysiwyg for updating
  updateText: (Editor, annotation) =>
    CKEDITOR.instances[editor_instance].setData(Editor.annotation.text)

  # convert text back to HTML
  convertText: (Viewer) =>
    for index of Viewer.annotations
      div = $(Viewer.element[0]).find('div:first-of-type')[index]
      # reverse the HTML escaping by Annotator.Util.escape
      # possibly dangerous, but trusting WYSIWYG input filters for content
      annotation = Viewer.annotations[index]
      annotation.text = annotation.text.replace(/&amp;/g, '&').replace(/&lt;/g, '<').replace(/&gt;/g, '>').replace(/&quot;/g, '"');
      div.innerHTML = annotation.text

