<?php

/**
 * @file
 * Default theme implementation: Display a sample object with contextual links.
 *
 * Available variables:
 * - $title: The sanitized title of the object.
 * - $content: The sanitized content of the object.
 * These are defined in template_preprocess_contextual_links_example_object()
 * and represent whichever variables you might actually use to display the
 * main content of your module's object.
 *
 * Standard variables (required for contextual links):
 * - $classes: String of classes that can be used to style contextually through
 *   CSS.
 * - $title_prefix (array): An array containing additional output populated by
 *   modules, intended to be displayed in front of the main title tag that
 *   appears in the template.
 * - $title_suffix (array): An array containing additional output populated by
 *   modules, intended to be displayed after the main title tag that appears in
 *   the template.
 * The above variables are a subset of those which Drupal provides to all
 * templates, and they must be printed in your template file in order for
 * contextual links to be properly attached. For example, the core Contextual
 * Links module adds the renderable contextual links themselves inside
 * $title_suffix, so they will appear immediately after the object's title in
 * the HTML. (This placement is for accessibility reasons, among others.)
 */
?>
<div class="<?php print $classes; ?>">
  <?php print render($title_prefix); ?>
  <h2><?php print $title; ?></h2>
  <?php print render($title_suffix); ?>
  <?php print $content; ?>
</div>
