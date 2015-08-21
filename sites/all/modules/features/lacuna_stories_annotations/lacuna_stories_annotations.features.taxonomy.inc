<?php
/**
 * @file
 * lacuna_stories_annotations.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function lacuna_stories_annotations_taxonomy_default_vocabularies() {
  return array(
    'annotation_categories' => array(
      'name' => 'Annotation Categories',
      'machine_name' => 'annotation_categories',
      'description' => 'Categories for annotations',
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
