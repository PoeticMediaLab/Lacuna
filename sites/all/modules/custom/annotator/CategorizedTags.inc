<?php
/**
 * Re-usable routine for getting a list of tags and categories
 */

function categorize_tags() {
	$loaded_tags = array();

	// Get the course context to know which tags to load into the annotator. If there is no context set (which should never happen when creating/editing an annotation) then do not load any tags.
	if ($current_course = course_get_selected_course()) {
		// MLW - Load tags for autocomplete in Annotator window

		// Possible refactor for speed? EFQ is slower than db_select -- Shiraz recommends stay with EFQ. The EFQ load increase is minimal relative to other stuff that's going on, and the abstraction is strongly encouraged in Drupal land. EFQs were added to D7 specifically for this kind of use case. If performance is a concern, not having the annotator plugins load on every page load seems like a higher priority.
		$tags = taxonomy_vocabulary_machine_name_load('annotation_tags');
		$query = new EntityFieldQuery();
		$result = $query->entityCondition('entity_type', 'taxonomy_term')
			->propertyCondition('vid', (int) $tags->vid, '=')
			->fieldCondition('field_annotation_tag_course', 'target_id', $current_course)
			->execute();
		$flag = flag_get_flag('curated_tag');
		if (!empty($result['taxonomy_term'])) {
			$terms = taxonomy_term_load_multiple(array_keys($result['taxonomy_term']));
			foreach ($terms as $term) {
				if ($flag && $flag->is_flagged($term->tid)) {
					// Warning: hard-coded labels here - MLW
					$category = 'curated tags';
				}
				else {
					$category = 'custom tags';
				}
				array_push($loaded_tags, array(
					'label' => $term->name,
					'category' => $category
				));
			}
		}

		// Sort so that "curated tags" are on top
		// NB: curated comes before custom in alphabetical sort
		// if these labels change, then this sort algorithm needs
		// to update, too
		usort($loaded_tags, function ($a, $b) {
			if ($a['category'] == $b['category']) {
				return (strtolower($a['label']) < strtolower($b['label'])) ? -1 : 1;
			}
			return ($a['category'] < $b['category']) ? -1 : 1;
		});
	}
	return $loaded_tags;
}