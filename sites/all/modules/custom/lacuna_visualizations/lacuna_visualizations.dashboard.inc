<?php
/**
 * Routines for loading and caching dashboard data
 *
 */

// an array map function to return the document id
function get_doc_id($annotation) {
  return $annotation->field_annotation_reference[$annotation->language][0]['target_id'];
}

function get_uid($annotation) {
  return $annotation->uid;
}

function lacuna_visualizations_annotation_dashboard() {
  // Load the dashboard visualization
  global $base_url;
  // settings.config
  $settings = array(
    'config' => array(
      'size' => array(
        'graph' => array(
          'width' => 800,
          'height' => 5000,
        ),
      ),
      'data_url' => $base_url . '/visualization/dashboard/data.json',
    ),
    'id' => 'annotations_dashboard',
    'type' => 'annotations_dashboard',
  );
  drupal_add_js($settings, 'setting');
  // Dashboard uses Crossfilter
  drupal_add_library('lacuna_visualizations', 'crossfilter', FALSE);
  // We don't need the Graph API for this part, so go straight to d3
  return d3_draw($settings);
}

function lacuna_visualizations_annotation_dashboard_build_data($course_id) {
  // Prepare the data for the dashboard
  // Get all annotations that are on a document or response in the current course
  $query = db_query('
    SELECT entity_id
    FROM {field_data_field_annotation_reference} AS ar
    LEFT JOIN {og_membership} AS og
    ON ar.field_annotation_reference_target_id = og.etid
    WHERE og.gid = :gid
    AND og.entity_type = :node', array(':gid' => $course_id, ':node' => 'node'));
  $annotation_ids = array_keys($query->fetchAllAssoc('entity_id'));

  $userNames = array();   // only load users once
  $results = array();
  // Fields need for db query:
  // created, uid, annotation_reference, text, quote, private, annotation_tags, category
  $annotations = node_load_multiple($annotation_ids); // Most costly function in entire routine

  // Load all document and users at once to speed up query time
  $documents = node_load_multiple(array_map("get_doc_id", $annotations));
  $annotators = user_load_multiple(array_map("get_uid", $annotations));
  foreach ($annotators as $annotator) {
    $userNames[$annotator->uid] = format_username($annotator);
  }
  $terms = array();
  $field_prefix = 'field_annotation_';	// to convert from Drupal field names to viz
  // Convert from Drupal format to a simpler data format for viz
  foreach ($annotations as $annotation) {
    // Create a new data object, populate only with necessary data
    // Make it harder to leak unintended data
    $data = new StdClass();
    $data->id = $annotation->nid;
    $data->created = $annotation->created * 1000; // convert to milliseconds for d3
    $data->updated = $annotation->changed * 1000;
    $data->uid = $annotation->uid;

    $target_id = $annotation->field_annotation_reference[$annotation->language][0]['target_id'];
    $data->doc_id = $target_id;
    $data->documentTitle = $documents[$target_id]->title;

    // Text content
    $fields = array('text', 'quote');
    foreach ($fields as $field) {
      if (isset($annotation->{$field_prefix . $field}[$annotation->language][0]['value'])) {
        $data->{$field} = $annotation->{$field_prefix . $field}[$annotation->language][0]['value'];
      }
    }

    // Sharing options; we just need the overall option (Private, Everyone, etc.), not details
    if (isset($annotation->field_annotation_audience[$annotation->language])) {
      $data->audience = ucfirst($annotation->field_annotation_audience[$annotation->language][0]['value']);
    } else {
      $data->audience = 'Unknown';
    }

    // Taxonomies: tags and categories
    // Note: removed tags for now; not shown, so no need to load them
    $fields = array('category');
    foreach ($fields as $field) {
      $data->{$field} = array();
      if (isset($annotation->{$field_prefix . $field}[$annotation->language][0]['tid'])) {
        foreach ($annotation->{$field_prefix . $field}[$annotation->language] as $tag) {
          if (!isset($terms[$tag['tid']])) {
            $term = taxonomy_term_load($tag['tid']);
            $terms[$tag['tid']] = $term;
          } else {
            $term = $terms[$tag['tid']];
          }
          array_push($data->{$field}, $term->name);
        }
      }
    }
    if ($data->category) {
      $data->category = $data->category[0];	// set default to first category
    }

    // Remove or sanitize data we don't want to expose: annotations, usernames, etc.
    if (!empty($data->text)) {
      $data->text = str_repeat("x", strlen($data->text)); // provide length w/o exposing data
    }
    unset($data->quote);
    unset($data->tags);

    $data->username = $userNames[$annotation->uid];
    array_push($results, $data);
  }
  return $results;
}

function lacuna_visualizations_annotation_dashboard_cache_get($course_id) {
  return cache_get("lacuna_visualization_dashboard_data:$course_id");
}

function lacuna_visualizations_annotation_dashboard_cache_set($course_id, $data) {
  if (count($data) >= variable_get('lacuna_visualizations_cache_threshold', 1000)) {
    $cache_hours = (int) variable_get('lacuna_visualizations_cache_ttl');
    cache_set("lacuna_visualization_dashboard_data:$course_id", $data, 'cache', time() + $cache_hours * 60 * 60);
  }
}

function lacuna_visualizations_annotation_dashboard_data() {
  $course_id = course_get_selected_course();
  // Check for cached data first
  if ($cached = lacuna_visualizations_annotation_dashboard_cache_get($course_id)) {
    drupal_json_output($cached->data);
    drupal_exit();
  }
  $results = lacuna_visualizations_annotation_dashboard_build_data($course_id);
  lacuna_visualizations_annotation_dashboard_cache_set($course_id, $results);
  drupal_json_output($results);
  drupal_exit();
}
