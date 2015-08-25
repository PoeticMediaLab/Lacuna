(function() {
  var bind = function(fn, me){ return function(){ return fn.apply(me, arguments); }; },
    extend = function(child, parent) { for (var key in parent) { if (hasProp.call(parent, key)) child[key] = parent[key]; } function ctor() { this.constructor = child; } ctor.prototype = parent.prototype; child.prototype = new ctor(); child.__super__ = parent.prototype; return child; },
    hasProp = {}.hasOwnProperty;

  Annotator.Plugin.Permissions = (function(superClass) {
    extend(Permissions, superClass);

    Permissions.prototype.events = {
      'beforeAnnotationCreated': 'addFieldsToAnnotation'
    };

    Permissions.prototype.options = {
      showViewPermissionsCheckbox: true,
      showEditPermissionsCheckbox: true,
      userId: function(user) {
        return user;
      },
      userString: function(user) {
        return user;
      },
      userAuthorize: function(action, annotation, user) {
        var i, len, token, tokens;
        if (annotation.permissions) {
          tokens = annotation.permissions[action] || [];
          if (tokens.length === 0) {
            return true;
          }
          for (i = 0, len = tokens.length; i < len; i++) {
            token = tokens[i];
            if (this.userId(user) === token) {
              return true;
            }
          }
          return false;
        } else if (annotation.user) {
          if (user) {
            return this.userId(user) === this.userId(annotation.user);
          } else {
            return false;
          }
        }
        return true;
      },
      user: '',
      permissions: {
        'read': [],
        'update': [],
        'delete': [],
        'admin': []
      }
    };

    function Permissions(element, options) {
      this._setAuthFromToken = bind(this._setAuthFromToken, this);
      this.updateViewer = bind(this.updateViewer, this);
      this.updateAnnotationPermissions = bind(this.updateAnnotationPermissions, this);
      this.updatePermissionsField = bind(this.updatePermissionsField, this);
      this.addFieldsToAnnotation = bind(this.addFieldsToAnnotation, this);
      Permissions.__super__.constructor.apply(this, arguments);
      if (this.options.user) {
        this.setUser(this.options.user);
        delete this.options.user;
      }
    }

    Permissions.prototype.pluginInit = function() {
      var createCallback, self;
      if (!Annotator.supported()) {
        return;
      }
      self = this;
      createCallback = function(method, type) {
        return function(field, annotation) {
          return self[method].call(self, type, field, annotation);
        };
      };
      if (!this.user && this.annotator.plugins.Auth) {
        this.annotator.plugins.Auth.withToken(this._setAuthFromToken);
      }
      if (this.options.showViewPermissionsCheckbox === true) {
        this.annotator.editor.addField({
          type: 'checkbox',
          label: Annotator._t('Allow anyone to <strong>view</strong> this annotation'),
          load: createCallback('updatePermissionsField', 'read'),
          submit: createCallback('updateAnnotationPermissions', 'read')
        });
      }
      if (this.options.showEditPermissionsCheckbox === true) {
        this.annotator.editor.addField({
          type: 'checkbox',
          label: Annotator._t('Allow anyone to <strong>edit</strong> this annotation'),
          load: createCallback('updatePermissionsField', 'update'),
          submit: createCallback('updateAnnotationPermissions', 'update')
        });
      }
      this.annotator.viewer.addField({
        load: this.updateViewer
      });
      if (this.annotator.plugins.Filter) {
        return this.annotator.plugins.Filter.addFilter({
          label: Annotator._t('User'),
          property: 'user',
          isFiltered: (function(_this) {
            return function(input, user) {
              var i, keyword, len, ref;
              user = _this.options.userString(user);
              if (!(input && user)) {
                return false;
              }
              ref = input.split(/\s*/);
              for (i = 0, len = ref.length; i < len; i++) {
                keyword = ref[i];
                if (user.indexOf(keyword) === -1) {
                  return false;
                }
              }
              return true;
            };
          })(this)
        });
      }
    };

    Permissions.prototype.setUser = function(user) {
      return this.user = user;
    };

    Permissions.prototype.addFieldsToAnnotation = function(annotation) {
      if (annotation) {
        annotation.permissions = $.extend(true, {}, this.options.permissions);
        if (this.user) {
          return annotation.user = this.user;
        }
      }
    };

    Permissions.prototype.authorize = function(action, annotation, user) {
      if (user === void 0) {
        user = this.user;
      }
      if (this.options.userAuthorize) {
        return this.options.userAuthorize.call(this.options, action, annotation, user);
      } else {
        return true;
      }
    };

    Permissions.prototype.updatePermissionsField = function(action, field, annotation) {
      var input;
      field = $(field).show();
      input = field.find('input').removeAttr('disabled');
      if (!this.authorize('admin', annotation)) {
        field.hide();
      }
      if (this.authorize(action, annotation || {}, null)) {
        return input.attr('checked', 'checked');
      } else {
        return input.removeAttr('checked');
      }
    };

    Permissions.prototype.updateAnnotationPermissions = function(type, field, annotation) {
      var dataKey;
      if (!annotation.permissions) {
        annotation.permissions = $.extend(true, {}, this.options.permissions);
      }
      dataKey = type + '-permissions';
      if ($(field).find('input').is(':checked')) {
        return annotation.permissions[type] = [];
      } else {
        return annotation.permissions[type] = [this.options.userId(this.user)];
      }
    };

    Permissions.prototype.updateViewer = function(field, annotation, controls) {
      var user, username;
      field = $(field);
      username = this.options.userString(annotation.user);
      if (annotation.user && username && typeof username === 'string') {
        user = Annotator.Util.escape(this.options.userString(annotation.user));
        field.html(user).addClass('annotator-user');
      } else {
        field.remove();
      }
      if (controls) {
        if (!this.authorize('update', annotation)) {
          controls.hideEdit();
        }
        if (!this.authorize('delete', annotation)) {
          return controls.hideDelete();
        }
      }
    };

    Permissions.prototype._setAuthFromToken = function(token) {
      return this.setUser(token.userId);
    };

    return Permissions;

  })(Annotator.Plugin);

}).call(this);
