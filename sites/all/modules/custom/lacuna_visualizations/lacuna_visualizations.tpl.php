<?php
/**
 * @file
 * Default theme file for d3 visualizations.
 * TODO: MAKE THIS DISPLAY MORE RELEVANT NODE INFORMATION (title,
 * abstract, date of publication?)
 *
 */

?>
<div <?php print $attributes ?> class="<?php print implode(' ',
  $classes_array); ?>">

<?php if (current_path() != 'visualization/dashboard') { ?>
  	<div id="maps-tooltip" class="hidden">
  		<p><strong>author: </strong> <span id="author"></span></p>
  		<p><strong>title: </strong> <a id="title">document title</a></p>
  		<p class="hidden" id="links"><strong>links to: </strong> <span id="links"></span></p>
  		<p class="hidden" id="abstract"><strong>abstract: </strong><span id="abstract"></span></p>

  	</div>

  	<div id="journeys-tooltip" class="hidden">
  		<p><strong>title: </strong> <a id="title">document title</a> </p>

  	</div>

  </div>

<?php
}
elseif (current_path() == 'visualization/dashboard') { ?>
  <a id="top"></a>
  <div id="column_left">
  </div>
  <div id="column_right">
  </div>
  <div class="section">
    <div class="help fa fa-question-circle"></div>
    <div id="time_brush"></div>
    <div class="help_text">
      <h2>Time Filter</h2>
      <p>To see how annotations change over time, draw a box over your desired time period. You can then click and drag that box to watch how annotations change over time. Click "Remove Time Filter" to return to viewing all annotations.</p>
    </div>
  </div>

  <div class="section">
    <div id="pie_types"></div>
    <div class="help fa fa-question-circle"></div>
    <div class="help_text">
      <h2>Annotation Types</h2>
      <p>Hover over a pie chart to see a summary of student work. Click on any pie chart to change the graph below to show data according to the selected chart.</p>
    </div>
  </div>

  <div class="section" id="buttons">
    <a href="#" class="lacuna-button" id="reset_all">Reset</a>
    <a href="#" class="lacuna-button" id="reset_brush">Remove Time Filter</a>
    <a href="#return_to_vis" class="lacuna-button" id="view_annotations"></a>
  </div>

  <div class="section">
    <div id="network"></div>
    <div class="help fa fa-question-circle"></div>
    <div class="help_text">
      <h2>Student and Resource Data</h2>
      <p>Hover over a student or resource to view individual data. Click on a student or resource pie chart to filter data specific to that entry.</p>
      <p>The lines between students and resources indicate the number of annotations made by the student on that resource.</p>
      <p>At any time, click the "Reset" button to return to viewing all data.</p>
    </div>
  </div>

  <div class="section" id="annotations_table">
    <a class="lacuna-button" id="return_to_vis" href="#top">Return to visualization</a>
    <table id="annotations_table_draw" class="display" cellspacing="0" width="100%">
        <thead>
            <tr>
                <th>Student</th>
                <th>Category</th>
                <th>Title</th>
                <th>Annotation</th>
                <th>Quote</th>
                <th>Tags</th>
                <th>Sharing</th>
                <th>Created</th>
            </tr>
        </thead>

        <tfoot>
            <tr>
                <th>Student</th>
                <th>Category</th>
                <th>Title</th>
                <th>Annotation</th>
                <th>Quote</th>
                <th>Tags</th>
                <th>Sharing</th>
                <th>Created</th>
            </tr>
        </tfoot>
    </table>
    <a class="lacuna-button" id="return_to_vis" href="#top">Return to visualization</a>
  </div>
<?php }
