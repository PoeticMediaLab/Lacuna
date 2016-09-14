<?php 

function lacuna_notifications_conversations() {
	$output = "<div class='conversations-view-block'><h2 class='conversations-title'>Replies to Annotations</h2>";
	$output .= views_embed_view('replies_to_annotations_view', 'block');
	$output .= "</div>";
	$output .= "<h2 class='conversations-title'>Annotations on Responses</h2>";
	$output .= views_embed_view('annotations_on_responses_view', 'block');
	$output .= "<h2 class='conversations-title'>Comments on Responses</h2>";
	$output .= views_embed_view('comments_on_responses_view', 'block');
	$output .= "<h2 class='conversations-title'>Comments on Threads</h2>";
	$output .= views_embed_view('comments_on_threads_view', 'block');

	return $output;
}

