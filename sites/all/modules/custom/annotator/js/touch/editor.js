(function() {
  var __bind = function(fn, me){ return function(){ return fn.apply(me, arguments); }; },
    __hasProp = Object.prototype.hasOwnProperty,
    __extends = function(child, parent) { for (var key in parent) { if (__hasProp.call(parent, key)) child[key] = parent[key]; } function ctor() { this.constructor = child; } ctor.prototype = parent.prototype; child.prototype = new ctor; child.__super__ = parent.prototype; return child; };

  Annotator.Plugin.Touch.Editor = (function(_super) {
    var Touch, jQuery, _t;

    __extends(Editor, _super);

    _t = Annotator._t;

    jQuery = Annotator.$;

    Touch = Annotator.Plugin.Touch;

    Editor.prototype.events = {
      "click": "_onOverlayTap",
      ".annotator-save tap": "_onSubmit",
      ".annotator-cancel tap": "_onCancel",
      ".annotator-quote-toggle tap": "_onExpandTap"
    };

    Editor.prototype.classes = {
      expand: "annotator-touch-expand"
    };

    Editor.prototype.templates = {
      quote: "<button class=\"annotator-quote-toggle\">" + _t("expand") + "</button>\n<span class=\"quote\"></span>"
    };

    function Editor(editor, options) {
      var _this = this;
      this.editor = editor;
      this._onOverlayTap = __bind(this._onOverlayTap, this);
      this._onCancel = __bind(this._onCancel, this);
      this._onSubmit = __bind(this._onSubmit, this);
      this._onExpandTap = __bind(this._onExpandTap, this);
      this._triggerAndroidRedraw = __bind(this._triggerAndroidRedraw, this);
      Editor.__super__.constructor.call(this, this.editor.element[0], options);
      this.element.addClass("annotator-touch-editor");
      this.element.wrapInner('<div class="annotator-touch-widget" />');
      this.element.find("form").addClass("annotator-touch-widget-inner");
      this.element.find(".annotator-controls a").addClass("annotator-button");
      this.element.undelegate("textarea", "keydown");
      this.on("hide", function() {
        return _this.element.find(":focus").blur();
      });
      this._setupQuoteField();
      this._setupAndroidRedrawHack();
    }

    Editor.prototype.showQuote = function() {
      this.quote.addClass(this.classes.expand);
      this.quote.find("button").text(_t("Collapse"));
      return this;
    };

    Editor.prototype.hideQuote = function() {
      this.quote.removeClass(this.classes.expand);
      this.quote.find("button").text(_t("Expand"));
      return this;
    };

    Editor.prototype.isQuoteHidden = function() {
      return !this.quote.hasClass(this.classes.expand);
    };

    Editor.prototype._setupQuoteField = function() {
      var _this = this;
      this.quote = jQuery(this.editor.addField({
        id: 'quote',
        load: function(field, annotation) {
          _this.hideQuote();
          _this.quote.find('span').html(Annotator.Util.escape(annotation.quote || ''));
          return _this.quote.find("button").toggle(_this._isTruncated());
        }
      }));
      this.quote.empty().addClass("annotator-item-quote");
      return this.quote.append(this.templates.quote);
    };

    Editor.prototype._setupAndroidRedrawHack = function() {
      var check, timer,
        _this = this;
      if (Touch.isAndroid()) {
        timer = null;
        check = function() {
          timer = null;
          return _this._triggerAndroidRedraw();
        };
        return jQuery(window).bind("scroll", function() {
          if (!timer) return timer = setTimeout(check, 100);
        });
      }
    };

    Editor.prototype._triggerAndroidRedraw = function() {
      if (!this._input) this._input = this.element.find(":input:first");
      if (!this._default) {
        this._default = parseFloat(this._input.css("padding-top"));
      }
      this._multiplier = (this._multiplier || 1) * -1;
      this._input[0].style.paddingTop = (this._default + this._multiplier) + "px";
      return this._input[0].style.paddingTop = (this._default - this._multiplier) + "px";
    };

    Editor.prototype._isTruncated = function() {
      var expandedHeight, isHidden, truncatedHeight;
      isHidden = this.isQuoteHidden();
      if (!isHidden) this.hideQuote();
      truncatedHeight = this.quote.height();
      this.showQuote();
      expandedHeight = this.quote.height();
      if (isHidden) {
        this.hideQuote();
      } else {
        this.showQuote();
      }
      return expandedHeight > truncatedHeight;
    };

    Editor.prototype._onExpandTap = function(event) {
      event.preventDefault();
      event.stopPropagation();
      if (this.isQuoteHidden()) {
        return this.showQuote();
      } else {
        return this.hideQuote();
      }
    };

    Editor.prototype._onSubmit = function(event) {
      event.preventDefault();
      return this.editor.submit();
    };

    Editor.prototype._onCancel = function(event) {
      event.preventDefault();
      return this.editor.hide();
    };

    Editor.prototype._onOverlayTap = function(event) {
      if (event.target === this.element[0]) return this.editor.hide();
    };

    return Editor;

  })(Annotator.Delegator);

}).call(this);
