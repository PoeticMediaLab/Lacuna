<?php 

function lacuna_notifications_conversations() {
	$output = "<div class='latest-conversations-banner'></div><div class='conversations-view-block'><h2 class='conversations-title'>Replies to Annotations</h2>";
	$output .= views_embed_view('replies_to_annotations_view', 'block');
	$output .= "</div>";
	$output .= "<div class='annotations-view-block'><h2 class='conversations-title'>Annotations on Responses</h2>";
	$output .= views_embed_view('annotations_on_responses_view_2', 'block');
	$output .= "</div>";
	$output .= "<div class = 'comments-responses-block'><h2 class='conversations-title'>Comments on Responses</h2>";
	$output .= views_embed_view('comments_on_responses_view_2', 'block');
	$output .= "</div>";
	$output .= "<div class = 'comments-threads-block'><h2 class='conversations-title'>Comments on Threads</h2>";
	$output .= views_embed_view('comments_on_threads_view', 'block');
	$output .= "</div>";

	return $output;
}

