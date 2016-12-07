<?php

/**
 * @file
 * Template to display a view as a table.
 * 
 * - $visualization: The rendered chart html. No JS.
 * - $header: An array of header labels keyed by field id.
 * - $rows: An array of row items. Each row is an array of content.
 *   $rows are keyed by row number, fields within rows are keyed numerically 
 *   for the purposes of chart rendering.
 * - $show_table: A boolean indicating whether or not to show the debug
 *   table.
 * @ingroup views_templates
 */
?>
<?php print $visualization; ?>
<?php print render($table); ?>
