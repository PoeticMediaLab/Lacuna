(function() {
  var $, editor_instance,
    __bind = function(fn, me){ return function(){ return fn.apply(me, arguments); }; },
    __hasProp = Object.prototype.hasOwnProperty,
    __extends = function(child, parent) { for (var key in parent) { if (__hasProp.call(parent, key)) child[key] = parent[key]; } function ctor() { this.constructor = child; } ctor.prototype = parent.prototype; child.prototype = new ctor; child.__super__ = parent.prototype; return child; };

  $ = jQuery;

  editor_instance = 'annotator-field-0';

  Annotator.Plugin.RichText = (function(_super) {

    __extends(RichText, _super);

    function RichText() {
      this.showText = __bind(this.showText, this);
      this.saveText = __bind(this.saveText, this);
      RichText.__super__.constructor.apply(this, arguments);
    }

    RichText.prototype.pluginInit = function() {
      var editor,
        _this = this;
      if (!Annotator.supported()) return;
      editor = this.annotator.editor;
      CKEDITOR.replace(editor_instance, {
        extraplugins: 'image2, oembed',
        toolbar: [
          {
            name: 'basicstyles',
            items: ['RemoveFormat']
          }, {
            name: 'paragraph',
            groups: ['list'],
            items: ['NumberedList', 'BulletedList']
          }, {
            name: 'links',
            items: ['Link', 'Unlink']
          }, {
            name: 'insert',
            items: ['Image2', 'oEmbed']
          }
        ]
      });
      this.annotator.subscribe('annotationEditorSubmit', function(Editor) {
        return _this.saveText(Editor);
      });
      return this.annotator.subscribe('annotationViewerShown', function(Viewer) {
        return _this.showText(Viewer);
      });
    };

    RichText.prototype.saveText = function(Editor) {
      return Editor.annotation.text = CKEDITOR.instances[editor_instance].getData();
    };

    RichText.prototype.showText = function(field, annotation) {
      var textDiv;
      textDiv = $(field.parentNode).find('div:first-of-type')[0];
      textDiv.innerHTML = annotation.text;
      $(textDiv).addClass('richText-annotation');
    };

    return RichText;

  })(Annotator.Plugin);

}).call(this);
