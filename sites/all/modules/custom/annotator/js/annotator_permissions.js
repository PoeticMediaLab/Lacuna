(function ($) {
  Drupal.behaviors.annotatorPermissions = {
    attach: function (context, settings) {
      Drupal.Annotator.annotator('addPlugin', 'Permissions', {
        user: settings.annotator_permissions.user,
        permissions: settings.annotator_permissions.permissions,
        showViewPermissionsCheckbox: settings.annotator_permissions.showViewPermissionsCheckbox === 1,
        showEditPermissionsCheckbox: settings.annotator_permissions.showEditPermissionsCheckbox === 1,
        userId: function (user) {
          if (user && user.uid) {
            return user.uid;
          }
          return user;
        },
        userString: function (user) {
          if (user && user.name) {
            return user.name;
          }
          return user;
        },
        /*
        userAuthorize: function (action, annotation, user) {
          if (user && annotation) {

            // Edit own annotations
            if (annotation.permissions[action]['user'] &&
               (user.uid == annotation.user.uid) &&
               (jQuery.inArray(user.uid, annotation.permissions[action]['user']) !== -1)) {
              return true;
            }

            // Check if user has appropriate role
            for (var i = 0; i < user.roles.length; i++) {
              var role = jQuery.inArray(user.roles[i], annotation.permissions[action]['roles']);
              if (jQuery.inArray(user.roles[i], annotation.permissions[action]['roles']) !== -1) {
                return true;
              }
            }
          }

          // Deny access
          return false;
        }*/
      });
    }
  };
})(jQuery);
