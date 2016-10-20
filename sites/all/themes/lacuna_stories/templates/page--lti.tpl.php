<?php
/**
 * @file
 * Returns the HTML for the LTI Resources view
 * Strips out all header/footer/menus
 * Meant to be integrated in an iFrame within the LMS
 */
header_remove('X-Frame-Options'); // Necessary for security to allow embedding

?>

<div id="page">
  <div id="main">
    <div id="content" class="column" role="main">
      <?php print render($title_prefix); ?>
      <?php if ($title): ?>

        <h1 class="page__title title" id="page-title"><?php print $title; ?></h1>
      <?php endif; ?>
      <?php print render($title_suffix); ?>
      <?php print $messages; ?>
      <?php print render($page['content']); ?>
    </div>
  </div>
</div>

