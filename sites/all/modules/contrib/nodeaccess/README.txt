Node Access Module

(Hopelessly out of date)

This module allows you to manage permissions for nodes by role and user. In other words,
it implements per node access control for users and groups. With this module, you can
restrict access to any individual node without having to use taxonomy. You can assign 
permission to view, edit or delete each individual node by user or role. Once enabled,
a 'grant' tab will appear on node pages. You can click this and assign permissions for 
that node.


INSTALLATION:

Put the module in your drupal modules directory and enable it in admin/modules.

I would strongly recommend backing up your database before installing
this module...

IMPORTANT!

Once you check the enable box and submit the page, no nodes will be accessible to anyone
other than the admin user. You just set permissions on the nodeaccess settings page 
(admin/settings/nodeaccess) to enable access to your site.

The settings page has a section for roles, and then a section for every node type you 
have on your site.

ALLOWED ROLES:

The allowed roles section allows you to choose what roles will appear on the node grant
tab. Just check each role you want to appear. Note that you can still set defaults for
all roles as the admin user, these options just hide what is available on each node
page.

NODE TYPE SETTINGS:

For each node type on your site, you can set default role access permissions and choose
if the grant tab should be available on that page. If the show grant tab option is 
not checked, the grant tab will not appear on the node page regardless of user permissions.

For each node type, you can also choose the default permissions for that type. To emulate 
standard drupal permissions, you would give anonymous user and authenticated user view permissions
for each node type. Note that once this module is first enabled, no permissions are granted, so
it is important to set defaults.

The default permissions for each node type will apply to any node which does not have
permissions set, either at the time you submit the settings or when any new node is
created. For already existing nodes, the defaults will apply only to those nodes which
have not had custom permissions set on the node grants tab. 

TIPS:

If you grant authenticated users edit permission, you cannot revoke that for any user
who is a member of authenticated users. For example, if you wanted all users to be able
to edit a node except for one user, you cannot do this by granted edit permission to 
authenticated users, then adding the user to the node without view permissions. Drupal
doesn't let you do that.


