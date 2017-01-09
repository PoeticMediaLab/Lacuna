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
    config = {
      extraPlugins: 'lineutils,embed,autoembed,image2',
      toolbar: [
          { name: 'paragraph', items: ['NumberedList', 'BulletedList'] },
          { name: 'links', items: ['Link', 'Unlink'] },
          { name: 'insert', items: ['embed, autoembed'] },
        ],
      # removeButtons: 'Underline,Strike,Subscript,Superscript,Anchor',
      removePlugins: 'elementspath,font,resize',
      allowedContent: true,
      autoUpdateElement: true,
    }

    # Sets custom Iframely API key, if set in
    # Configuration -> Content Authoring -> Annotator -> Richtext.
    key = Drupal.settings.annotator_richtext.iframely_api_key
    if (key?.length)
      base = '//iframe.ly/api/oembed?url={url}&callback={callback}&api_key=';
      config.embed_provider = base + key

    CKEDITOR.replace(editor_instance, config)

    # @annotator.subscribe 'annotationEditorSubmit', (Editor, annotation) => @saveText(Editor, annotation)
    @annotator.subscribe 'annotationEditorShown', (Editor, annotation) => @updateText(Editor, annotation)
    @annotator.subscribe 'annotationEditorSubmit', (Editor, annotation) => @saveText(Editor, annotation)
    @annotator.subscribe 'annotationViewerShown', (Viewer) => @convertText(Viewer)

  saveText: (Editor, annotation) =>
    # Grab the user-created text, put it in the correct annotator field
    CKEDITOR.instances[editor_instance].updateElement()
    annotation.text = CKEDITOR.instances[editor_instance].getData()

  # load existing annotation text into the wysiwyg for updating
  updateText: (Editor, annotation) =>
    CKEDITOR.instances[editor_instance].setData(annotation.text)

  # convert text back to HTML
  convertText: (Viewer) =>
    # Annotator adds the controls, then the next sibling is the div with the text in it
    divList = $(Viewer.element[0]).find('span.annotator-controls, span.annotator-touch-controls').next()
    for index, annotation of Viewer.annotations
      # reverse the HTML escaping by Annotator.Util.escape
      # possibly dangerous, but trusting WYSIWYG input filters for content
      if annotation.text?
        annotation.text = annotation.text.replace(/&amp;/g, '&').replace(/&lt;/g, '<').replace(/&gt;/g, '>').replace(/&quot;/g, '"');
        # Match the correct text to the correct div by index
        divList[index].innerHTML = annotation.text

