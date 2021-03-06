// Generated by CoffeeScript 1.12.3
(function() {
  var $,
    bind = function(fn, me){ return function(){ return fn.apply(me, arguments); }; },
    extend = function(child, parent) { for (var key in parent) { if (hasProp.call(parent, key)) child[key] = parent[key]; } function ctor() { this.constructor = child; } ctor.prototype = parent.prototype; child.prototype = new ctor(); child.__super__ = parent.prototype; return child; },
    hasProp = {}.hasOwnProperty;

  $ = jQuery;

  Annotator.Plugin.Privacy = (function(superClass) {
    extend(Privacy, superClass);

    function Privacy() {
      this.updateViewer = bind(this.updateViewer, this);
      this.savePrivacy = bind(this.savePrivacy, this);
      this.addPrivacy = bind(this.addPrivacy, this);
      return Privacy.__super__.constructor.apply(this, arguments);
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
        "private": 'annotator-privacy-private',
        student: 'annotator-privacy-student',
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
      if (!Annotator.supported()) {
        return;
      }
      this.field = this.annotator.editor.addField({
        label: Annotator._t('Privacy')
      });
      $(this.field).addClass(this.className["default"] + ' fa fa-lock');
      return this.annotator.viewer.addField({
        load: this.updateViewer
      });
    };

    Privacy.prototype.addPrivacy = function(event, annotation) {
      var checked, gid, group, group_object, group_type, groups, groups_html, j, len, peer_groups, peer_groups_disabled, privacy_html, privacy_type, ref, settings, show_groups;
      settings = annotation.privacy_options ? annotation.privacy_options : Drupal.settings.privacy_options;
      groups_html = privacy_html = show_groups = '';
      privacy_html += '<span class="' + this.className.types.wrapper + '">';
      ref = ["Private", "Instructor", "Peer-Groups", "Everyone"];
      for (j = 0, len = ref.length; j < len; j++) {
        privacy_type = ref[j];
        if (settings.is_instructor === true && privacy_type === "Instructor") {
          if (settings.response) {
            privacy_type = 'Student';
          } else {
            continue;
          }
        }
        checked = settings.audience[privacy_type.toLowerCase()] ? 'checked' : '';
        if ("Peer-Groups" === privacy_type && "checked" === checked) {
          show_groups = 'show-groups';
        }
        peer_groups = settings.groups.peer_groups;
        if ((peer_groups == null) || peer_groups.length === 0) {
          peer_groups_disabled = ' peer-groups-disabled';
        } else {
          peer_groups_disabled = '';
        }
        privacy_html += '<span class="' + this.className.types["default"] + ' ' + checked + peer_groups_disabled + '" id="' + privacy_type + '">' + privacy_type + '</span>';
      }
      privacy_html += '</span>';
      groups = settings.groups;
      for (group_type in groups) {
        group_object = groups[group_type];
        for (gid in group_object) {
          group = group_object[gid];
          if (group.private_feedback) {
            continue;
          }
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
      var audience, group, no_peer_groups_selected, peer_groups;
      annotation.privacy_options = {};
      peer_groups = {};
      audience = {};
      $('.annotator-editor .' + this.className.types["default"]).each((function(_this) {
        return function(i, el) {
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
        };
      })(this));
      if ($('.' + this.className.types.wrapper + ' #Student').hasClass("checked")) {
        annotation.privacy_options.private_feedback = Drupal.settings.privacy_options.private_feedback;
      }
      if (audience['peer-groups']) {
        no_peer_groups_selected = true;
        for (group in peer_groups) {
          if (peer_groups[group].selected) {
            no_peer_groups_selected = false;
            break;
          }
        }
        if (no_peer_groups_selected) {
          audience['peer-groups'] = 0;
          if (!audience['instructor']) {
            audience['private'] = 1;
          }
        }
      }
      annotation.privacy_options.audience = audience;
      return annotation.privacy_options.groups = {
        peer_groups: peer_groups
      };
    };

    Privacy.prototype.updateViewer = function(field, annotation) {
      var audience, audience_type, checked, gid, gids, group, group_type, groups, has_groups, ref, ref1;
      if (annotation.privacy_options == null) {
        return;
      }
      audience = '<div class="' + this.className.types.wrapper + '">';
      ref = annotation.privacy_options.audience;
      for (audience_type in ref) {
        checked = ref[audience_type];
        if (checked) {
          audience += '<span class="' + this.className.types["default"] + ' ' + this.className.types[audience_type];
          if (audience_type === 'private' || audience_type === 'student' || audience_type === 'instructor') {
            audience += ' fa fa-lock';
          }
          if (audience_type === 'everyone') {
            audience += ' fa fa-unlock';
          }
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
        ref1 = annotation.privacy_options.groups;
        for (group_type in ref1) {
          gids = ref1[group_type];
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
