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
      <span id="image"></span>
      <a id="title">document title</a><br/>
  		<span id="author"></span><br/>
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
  <div id="dashboard">
    <a id="top"></a>
    <div id="column_left">
    </div>
    <div id="column_right">
    </div>

    <div id="visual-content">
        <div id="left">
          <div class="column left-part">
            <div class="section">
              <div id="network"><h3>Activity</h3>
              <span class="help fa fa-question-circle">
                <div class="help_text tooltip">
                  <h2>People and Materials Data</h2>
                  <p>Hover over a student or resource to view individual data. Click on a student or resource pie chart to filter data specific to that entry.</p>
                  <p>The lines between students and resources indicate the number of annotations made by the student on that resource.</p>
                  <p>At any time, click the 'Show All' button to return to viewing all data.</p>
                </div>
              </span>
							<span class="dashboard-buttons">
									<a href="#" class="dashboard-button lacuna-button" id="reset_all">Show All</a>
									<a href="<?php global $base_url; print($base_url);?>/sewing-kit?" class="dashboard-button lacuna-button" id="view_annotations">View in Sewing Kit</a>
							</span>
              </div>
            </div>
          </div>
        </div>

        <div id="right">
          <div class="column right-part">
						<div class="section">
							<div id="legend">
							</div>
							<div id="pie_types"><h3>Annotation Details</h3>
                <span class="help fa fa-question-circle">
                  <div class="help_text tooltip">
										<h2>Annotation Details</h2>
										<p>Hover over a pie chart to see a summary of student work. Click on any pie chart to change the graph to show data according to the selected chart.</p>
									</div>
                </span>
							</div>
						</div>

						<div class="section">
							<div id="time_brush"><h3>Filter by Time</h3>
                <span class="help fa fa-question-circle">
                  <div class="help_text tooltip">
										<h2>Time Filter</h2>
										<p>To see how annotations change over time, draw a box over your desired time period. You can then click and drag that box to watch how annotations change over time. Click "Remove Time Filter" to return to viewing all annotations.</p>
									</div>
                </span>
								<span class="dashboard-buttons">
									<a href="#" class="dashboard-button lacuna-button" id="reset_brush">Remove Time Filter</a>
								</span>
							</div>
						</div>

          </div>
        </div>
    </div>
    <i class="fa fa-spinner fa-5x fa-spin"></i>
    </div>
  </div>
<?php }
