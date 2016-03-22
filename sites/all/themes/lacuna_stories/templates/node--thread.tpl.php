<?php
/**
 * @file
 * Returns the HTML for a Thread node.
 *
 * Complete documentation for this file is available online.
 * @see https://drupal.org/node/1728164
 */
?>
<article class="node-<?php print $node->nid; ?> <?php print $classes; ?> clearfix"<?php print $attributes; ?>>

  <?php if ($title_prefix || $title_suffix || $display_submitted || $unpublished || !$page && $title): ?>
    <header>
      <?php print render($title_prefix); ?>
      <?php if (!$page && $title): ?>
        <h2<?php print $title_attributes; ?>><a href="<?php print $node_url; ?>"><?php print $title; ?></a></h2>
      <?php endif; ?>
      <?php print render($title_suffix); ?>

      <?php if ($display_submitted): ?>
      <div class="submitted response-user-information">
        <?php print $user_picture; ?>
        <div class="username-and-date">
          <?php print $name; ?>
          <br>
            <span class="date-month-day-year">
              <?php print format_date($timestamp = $created,
                $type = 'medium',
                $format = 'F jS, Y',
                $timezone = NULL,
                $langcode = NULL); ?>
            </span>
        </div>
      </div>
      <?php endif; ?>

      <?php if ($unpublished): ?>
        <mark class="unpublished"><?php print t('Unpublished'); ?></mark>
      <?php endif; ?>
    </header>
  <?php endif; ?>

  <?php
    // We hide the comments and links now so that we can render them later.
    hide($content['comments']);
    hide($content['links']);
    print render($content['thread_description']);
    global $user;
    // Hard-coded view title; bad, I know, but other option
    // is to load the entire view, then get the title, which
    // causes a PHP warning about passing non-variables by references
    print '<h2 id="stitchings">Stitchings</h2>';
    if ($user->uid === $node->uid) {
      // Allow node author to edit the stitchings
      print views_embed_view('stitchings', 'vbo_block', $node->nid);
    } else {
      print views_embed_view('stitchings', 'view_block', $node->nid);
    }

  ?>

  <?php print render($content['links']); ?>

  <?php print render($content['comments']); ?>

</article>
