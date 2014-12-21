// Generated by CoffeeScript 1.8.0
var $,
  __bind = function(fn, me){ return function(){ return fn.apply(me, arguments); }; },
  __hasProp = {}.hasOwnProperty,
  __extends = function(child, parent) { for (var key in parent) { if (__hasProp.call(parent, key)) child[key] = parent[key]; } function ctor() { this.constructor = child; } ctor.prototype = parent.prototype; child.prototype = new ctor(); child.__super__ = parent.prototype; return child; };

$ = jQuery;

Annotator.Plugin.Comment = (function(_super) {
  __extends(Comment, _super);

  function Comment() {
    this.updateViewer = __bind(this.updateViewer, this);
    return Comment.__super__.constructor.apply(this, arguments);
  }

  Comment.prototype.options = {
    commentClass: "annotator-comment",
    base_url: "drupal7.dev"
  };

  Comment.prototype.pluginInit = function() {
    if (!Annotator.supported()) {
      return;
    }
    return this.annotator.viewer.addField({
      load: this.updateViewer
    });
  };

  Comment.prototype.updateViewer = function(field, annotation) {
    field = $(field);
    field.addClass(this.options.commentClass);
    if (annotation.comment_count !== "0") {
      return field.html('<a href="' + this.options.base_url + annotation.links[0].href + '#comments">' + annotation.comment_count + " Comments</a>");
    } else {
      return field.html(annotation.comment_count + ' Comments');
    }
  };

  return Comment;

})(Annotator.Plugin);