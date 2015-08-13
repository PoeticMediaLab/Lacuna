(function() {
  var $,
    __bind = function(fn, me){ return function(){ return fn.apply(me, arguments); }; },
    __hasProp = Object.prototype.hasOwnProperty,
    __extends = function(child, parent) { for (var key in parent) { if (__hasProp.call(parent, key)) child[key] = parent[key]; } function ctor() { this.constructor = child; } ctor.prototype = parent.prototype; child.prototype = new ctor; child.__super__ = parent.prototype; return child; };

  $ = jQuery;

  Annotator.Plugin.Author = (function(_super) {

    __extends(Author, _super);

    function Author() {
      this.updateViewer = __bind(this.updateViewer, this);
      Author.__super__.constructor.apply(this, arguments);
    }

    Author.prototype.authorClass = 'annotator-author fa fa-user';

    Author.prototype.pluginInit = function() {
      if (!Annotator.supported()) return;
      return this.annotator.viewer.addField({
        load: this.updateViewer
      });
    };

    Author.prototype.updateViewer = function(field, annotation) {
      var user;
      field = $(field);
      if (annotation.user && annotation.user.name && typeof annotation.user.name === 'string') {
        user = ' ' + Annotator.Util.escape(annotation.user.name);
        return field.html(user).addClass(this.authorClass);
      } else {
        return field.remove();
      }
    };

    return Author;

  })(Annotator.Plugin);

}).call(this);
