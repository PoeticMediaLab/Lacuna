<?php
/**
 * @file
 * Returns the HTML for a node.
 *
 * Complete documentation for this file is available online.
 * @see https://drupal.org/node/1728164
 */

/*
* Custom PHP template for the blog node type page; copied from
* Zen theme and edited to update the Response pages.  --Cody
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

        <!-- Update to Response user information header. -->
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
    print render($content);
  ?>

  <?php print render($content['links']); ?>

  <?php print render($content['comments']); ?>

</article>
