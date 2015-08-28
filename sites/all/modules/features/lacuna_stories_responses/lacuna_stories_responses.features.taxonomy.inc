<?php
/**
 * @file
 * lacuna_stories_responses.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function lacuna_stories_responses_taxonomy_default_vocabularies() {
  return array(
    'genre_response' => array(
      'name' => 'Genre - Responses',
      'machine_name' => 'genre_response',
      'description' => 'Genres for student responses',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
      'rdf_mapping' => array(
        'rdftype' => array(
          0 => 'skos:ConceptScheme',
        ),
        'name' => array(
          'predicates' => array(
            0 => 'dc:title',
          ),
        ),
        'description' => array(
          'predicates' => array(
            0 => 'rdfs:comment',
          ),
        ),
      ),
    ),
  );
}
