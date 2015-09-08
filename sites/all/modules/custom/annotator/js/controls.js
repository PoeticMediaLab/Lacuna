(function() {
  var __bind = function(fn, me){ return function(){ return fn.apply(me, arguments); }; },
    __hasProp = Object.prototype.hasOwnProperty,
    __extends = function(child, parent) { for (var key in parent) { if (__hasProp.call(parent, key)) child[key] = parent[key]; } function ctor() { this.constructor = child; } ctor.prototype = parent.prototype; child.prototype = new ctor; child.__super__ = parent.prototype; return child; };

  Annotator.Plugin.Controls = (function(_super) {

    __extends(Controls, _super);

    function Controls() {
      this.updateViewer = __bind(this.updateViewer, this);
      Controls.__super__.constructor.apply(this, arguments);
    }

    Controls.prototype.pluginInit = function() {
      if (!Annotator.supported()) return;
      return this.annotator.viewer.addField({
        load: this.updateViewer
      });
    };

    Controls.prototype.updateViewer = function(field, annotation, controls) {
      if ((annotation.permissions != null)) {
        if (!annotation.permissions.edit) controls.hideEdit();
        if (!annotation.permissions.del) return controls.hideDelete();
      }
    };

    return Controls;

  })(Annotator.Plugin);

}).call(this);
