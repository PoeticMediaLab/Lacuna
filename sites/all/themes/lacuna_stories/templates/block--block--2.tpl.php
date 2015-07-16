<?php
/**
 * @file
 * Returns the HTML for a block.
 *
 * Complete documentation for this file is available online.
 * @see https://drupal.org/node/1728246
 */
?>
<div id="<?php print $block_html_id; ?>" class="<?php print $classes; ?>"<?php print $attributes; ?>>

  <?php print render($title_prefix); ?>
  <?php if ($title): ?>
    <h2<?php print $title_attributes; ?>><?php print $title; ?></h2>
  <?php endif; ?>
  <?php print render($title_suffix); ?>

  <div class="messages status" id="signup">
    <p>This site is currently only available for students registered at the university or institution running this course.</p>
    <p>Please <a class="lacuna-button  lacuna-button-short" href="<?php
      global $base_url;
      print $base_url . '/user/register';
    ?>">Sign Up</a> or <a class="lacuna-button lacuna-button-short" href="<?php
      global $base_url;
      print $base_url . '/user/login';
    ?>">Login</a> to access the course materials.</p>
  </div>

</div>

