(function($) {
  var __bind = function(fn, me){ return function(){ return fn.apply(me, arguments); }; },
    __hasProp = Object.prototype.hasOwnProperty,
    __extends = function(child, parent) { for (var key in parent) { if (__hasProp.call(parent, key)) child[key] = parent[key]; } function ctor() { this.constructor = child; } ctor.prototype = parent.prototype; child.prototype = new ctor; child.__super__ = parent.prototype; return child; };

  Annotator.Plugin.Motivations = (function(_super) {

    __extends(Motivations, _super);

    Motivations.prototype.options = {
      showField: true,
      motivations: [
        {
          value: "oa:bookmarking",
          label: "Bookmarking"
        }, {
          value: "oa:classifying",
          label: "Classifying"
        }, {
          value: "oa:commenting",
          label: "Commenting"
        }, {
          value: "oa:describing",
          label: "Describing"
        }, {
          value: "oa:editing",
          label: "Editing"
        }, {
          value: "oa:highlighting",
          label: "Highlighting"
        }, {
          value: "oa:identifying",
          label: "Identifying"
        }, {
          value: "oa:linking",
          label: "Linking"
        }, {
          value: "oa:moderating",
          label: "Moderating"
        }, {
          value: "oa:questioning",
          label: "Questioning"
        }, {
          value: "oa:replying",
          label: "Replying"
        }, {
          value: "oa:tagging",
          label: "Tagging"
        }
      ]
    };

    Motivations.prototype.field = null;

    Motivations.prototype.input = null;

    Motivations.prototype.pluginInit = function() {
      var id, m, newfield, select, _i, _len, _ref;
      if (!Annotator.supported()) return;
      this.field = this.annotator.editor.addField({
        label: Annotator._t('ExplanatoryNote'),
        load: this.updateField,
        submit: this.setAnnotationMotivations
      });
      id = Annotator.$(this.field).find('input').attr('id');
      select = '<li class="annotator-item"><select style="width:100%"><option value="">(Uncategorised)</option>';
      _ref = this.options.motivations;
      for (_i = 0, _len = _ref.length; _i < _len; _i++) {
        m = _ref[_i];
        select += '<option value="' + m.value + '">' + m.label + '</option>';
      }
      select += '</select></li>';
      newfield = Annotator.$(select);
      Annotator.$(this.field).replaceWith(newfield);
      this.field = newfield[0];
      this.annotator.viewer.addField({
        load: this.updateViewer,
        annoPlugin: this
      });
      return this.input = Annotator.$(this.field).find('select');
    };

    function Motivations(element, options) {
      this.setAnnotationMotivations = __bind(this.setAnnotationMotivations, this);
      this.updateField = __bind(this.updateField, this);      Motivations.__super__.constructor.apply(this, arguments);
      if (options.motivations) this.options.motivations = options.motivations;
    }

    Motivations.prototype.updateField = function(field, annotation) {
      var value;
      value = '';
      if (annotation.motivation) value = annotation.motivation;
      return this.input.val(value);
    };

    Motivations.prototype.setAnnotationMotivations = function(field, annotation) {
      return annotation.motivation = this.input.val();
    };

    Motivations.prototype.updateViewer = function(field, annotation) {
      var displayValue, m, _i, _len, _ref, _results;
      field = Annotator.$(field);
      if (annotation.motivation) {
        displayValue = annotation.motivation;
        _ref = this.annoPlugin.options.motivations;
        _results = [];
        for (_i = 0, _len = _ref.length; _i < _len; _i++) {
          m = _ref[_i];
          if (m.value === annotation.motivation) {
            displayValue = m.label;
            field.parent().parent().find('.annotator-motivation').html(Util.escape(displayValue) + " ");
            if (this.annoPlugin.options.showField) {
              _results.push(field.addClass('annotator-motivation').html('<span class="annotator-motivation">' + Util.escape(displayValue) + '</span>'));
            } else {
              _results.push(field.remove());
            }
          } else {
            _results.push(void 0);
          }
        }
        return _results;
      } else {
        return field.remove();
      }
    };

    return Motivations;

  })(Annotator.Plugin);

})(jQuery);
