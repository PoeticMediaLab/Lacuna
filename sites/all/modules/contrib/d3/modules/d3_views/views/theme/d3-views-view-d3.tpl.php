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

<?php if ($show_table): ?>

<table id="views-debug-table">
  <?php if (!empty($header)) : ?>
    <thead>
      <tr>
        <?php foreach ($header as $field => $label): ?>
          <th>
            <?php print $label; ?>
          </th>
        <?php endforeach; ?>
      </tr>
    </thead>
  <?php endif; ?>
  <tbody>
    <?php foreach ($rows as $row_count => $row): ?>
      <tr>
        <?php foreach ($row as $field => $content): ?>
          <td>
            <?php print $content; ?>
          </td>
        <?php endforeach; ?>
      </tr>
    <?php endforeach; ?>
  </tbody>
</table>

<?php endif; ?>
