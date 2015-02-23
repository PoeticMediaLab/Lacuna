(function() {
  var $,
    __bind = function(fn, me){ return function(){ return fn.apply(me, arguments); }; },
    __hasProp = Object.prototype.hasOwnProperty,
    __extends = function(child, parent) { for (var key in parent) { if (__hasProp.call(parent, key)) child[key] = parent[key]; } function ctor() { this.constructor = child; } ctor.prototype = parent.prototype; child.prototype = new ctor; child.__super__ = parent.prototype; return child; };

  $ = jQuery;

  Annotator.Plugin.Privacy = (function(_super) {

    __extends(Privacy, _super);

    function Privacy() {
      this.updateViewer = __bind(this.updateViewer, this);
      Privacy.__super__.constructor.apply(this, arguments);
    }

    Privacy.prototype.options = {
      privacyClass: "annotator-privacy",
      publicClass: "annotator-privacy-public fa fa-unlock",
      privateClass: "annotator-privacy-private fa fa-lock"
    };

    Privacy.prototype.events = {
      'annotationEditorShown': "onAnnotationEditorShown"
    };

    Privacy.prototype.pluginInit = function() {
      if (!Annotator.supported()) return;
      return this.annotator.viewer.addField({
        load: this.updateViewer
      });
    };

    Privacy.prototype.updateViewer = function(field, annotation) {
      field = $(field);
      field.addClass(this.options.privacyClass);
      if (annotation.permissions["read"].length > 0) {
        return field.addClass(this.options.privateClass).html(Annotator.Util.escape(" Private"));
      } else {
        return field.addClass(this.options.publicClass).html(Annotator.Util.escape(" Public"));
      }
    };

    Privacy.prototype.onAnnotationEditorShown = function() {
      return $(".annotator-item.annotator-checkbox input[type=checkbox]").attr("checked", "checked");
    };

    return Privacy;

  })(Annotator.Plugin);

}).call(this);
