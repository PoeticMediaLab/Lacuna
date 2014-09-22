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

