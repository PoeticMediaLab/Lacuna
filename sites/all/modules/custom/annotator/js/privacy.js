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
      this.savePrivacy = __bind(this.savePrivacy, this);
      this.addPrivacy = __bind(this.addPrivacy, this);
      Privacy.__super__.constructor.apply(this, arguments);
    }

    Privacy.prototype.events = {
      'annotationEditorShown': "addPrivacy",
      'annotationEditorSubmit': "savePrivacy"
    };

    Privacy.prototype.field = null;

    Privacy.prototype.input = null;

    Privacy.prototype.className = {
      "default": 'annotator-privacy',
      types: {
        wrapper: 'annotator-privacy-types',
        "default": 'annotator-privacy-type',
        private: 'annotator-privacy-private',
        instructor: 'annotator-privacy-instructor',
        'peer-groups': 'annotator-privacy-peer-groups',
        everyone: 'annotator-privacy-everyone'
      },
      groups: {
        wrapper: 'annotator-privacy-groups',
        "default": 'annotator-privacy-group'
      }
    };

    Privacy.prototype.pluginInit = function() {
      if (!Annotator.supported()) return;
      this.field = this.annotator.editor.addField({
        label: Annotator._t('Privacy')
      });
      $(this.field).addClass(this.className["default"] + ' fa fa-lock');
      return this.annotator.viewer.addField({
        load: this.updateViewer
      });
    };

    Privacy.prototype.addPrivacy = function(event, annotation) {
      var checked, gid, group, group_object, group_type, groups, groups_html, privacy_html, privacy_type, settings, show_groups, _i, _len, _ref;
      settings = annotation.privacy_options ? annotation.privacy_options : Drupal.settings.privacy_options;
      groups_html = privacy_html = show_groups = '';
      privacy_html += '<span class="' + this.className.types.wrapper + '">';
      _ref = ["Private", "Instructor", "Peer-Groups", "Everyone"];
      for (_i = 0, _len = _ref.length; _i < _len; _i++) {
        privacy_type = _ref[_i];
        checked = settings.audience[privacy_type.toLowerCase()] ? 'checked' : '';
        if ("Peer-Groups" === privacy_type && "checked" === checked) {
          show_groups = 'show-groups';
        }
        privacy_html += '<span class="' + this.className.types["default"] + ' ' + checked + '" id="' + privacy_type + '">' + privacy_type + '</span>';
      }
      privacy_html += '</span>';
      groups = settings.groups;
      for (group_type in groups) {
        group_object = groups[group_type];
        for (gid in group_object) {
          group = group_object[gid];
          groups_html += '<label class="' + this.className.groups.wrapper + ' ' + show_groups + '">';
          checked = group.selected ? 'checked="checked"' : '';
          groups_html += '<input type="checkbox" class="' + this.className.groups["default"] + ' ' + group_type + '" value="' + gid + '" ' + checked + ' />';
          groups_html += group[0];
          groups_html += '</label>';
        }
      }
      groups_html = '<span class="' + this.className.groups.wrapper + ' ' + show_groups + '">' + groups_html + '</span>';
      return $(this.field).html(privacy_html + groups_html);
    };

    Privacy.prototype.savePrivacy = function(Editor, annotation) {
      var audience, peer_groups,
        _this = this;
      annotation.privacy_options = {};
      peer_groups = {};
      audience = {};
      $('.annotator-editor .' + this.className.types["default"]).each(function(i, el) {
        var type;
        type = $(el).attr("id").toLowerCase();
        if ($(el).hasClass("checked")) {
          audience[type] = 1;
        } else {
          audience[type] = 0;
        }
        return $('.annotator-editor input.' + _this.className.groups["default"] + '[type=checkbox]').each(function() {
          var checked, gid, group_name, parent;
          checked = $(this).is(":checked") ? 1 : 0;
          gid = $(this).val();
          parent = $(this).parent();
          group_name = parent[0].textContent;
          return peer_groups[gid] = {
            0: group_name,
            selected: checked
          };
        });
      });
      annotation.privacy_options.audience = audience;
      return annotation.privacy_options.groups = {
        peer_groups: peer_groups
      };
    };

    Privacy.prototype.updateViewer = function(field, annotation) {
      var audience, audience_type, checked, gid, gids, group, group_type, groups, has_groups, _ref, _ref2;
      if (!(annotation.privacy_options != null)) return;
      audience = '<div class="' + this.className.types.wrapper + '">';
      _ref = annotation.privacy_options.audience;
      for (audience_type in _ref) {
        checked = _ref[audience_type];
        if (checked) {
          audience += '<span class="' + this.className.types["default"] + ' ' + this.className.types[audience_type];
          if (audience_type === 'private') audience += ' fa fa-lock';
          if (audience_type === 'everyone') audience += ' fa fa-unlock';
          if ('peer-groups' === audience_type) {
            audience += ' fa fa-users';
            has_groups = true;
          }
          audience += '">' + audience_type.replace('-', ' ') + '</span>';
        }
      }
      audience += '</div>';
      groups = '';
      if (has_groups) {
        groups = '<div class="' + this.className.groups.wrapper + '">';
        _ref2 = annotation.privacy_options.groups;
        for (group_type in _ref2) {
          gids = _ref2[group_type];
          for (gid in gids) {
            group = gids[gid];
            if (group && group.selected) {
              groups += '<span class="' + this.className.groups["default"] + ' checked ' + group_type + ' fa fa-check">' + group[0] + '</span>';
            }
          }
        }
        groups += '</div>';
      }
      return $(field).addClass(this.className["default"]).html(audience + groups);
    };

    return Privacy;

  })(Annotator.Plugin);

}).call(this);
