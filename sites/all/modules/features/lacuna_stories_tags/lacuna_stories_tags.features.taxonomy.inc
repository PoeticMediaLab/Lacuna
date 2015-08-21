<?php
/**
 * @file
 * lacuna_stories_tags.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function lacuna_stories_tags_taxonomy_default_vocabularies() {
  return array(
    'annotation_tags' => array(
      'name' => 'Annotation Tags',
      'machine_name' => 'annotation_tags',
      'description' => 'User-generated tags for annotations',
      'hierarchy' => 0,
      'module' => 'annotation',
      'weight' => 1,
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
