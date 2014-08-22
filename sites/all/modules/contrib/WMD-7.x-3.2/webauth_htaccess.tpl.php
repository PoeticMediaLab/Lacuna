# This file is auto-generated. Changes will be overwritten.

AuthType WebAuth
WebAuthLdapAttribute displayName
WebAuthLdapAttribute suAffiliation
WebAuthLdapAttribute mail

<?php if ($rewrite_url): ?>
RewriteEngine on
RewriteCond %{REQUEST_FILENAME} !-f
<?php print $rewrite_url; ?>
<?php endif; ?>

<?php if ($require_valid_user): ?>
require valid-user
<?php else: ?>
<?php foreach($users as $u): ?>
require user <?php print $u; ?>

<?php endforeach; ?>

<?php foreach($privgroups as $group): ?>
require privgroup <?php print $group; ?>

<?php endforeach; ?>
<?php endif; ?>

<?php foreach ($groups as $group): ?>
WebAuthLdapPrivgroup <?php print $group . "\n"; ?>
<?php endforeach; ?>
