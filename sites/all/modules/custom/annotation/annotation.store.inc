<?php

/**
 * Annotator Store API
 * @see https://github.com/okfn/annotator/wiki/Storage
 */

/**
 * Annotation API main endpoint
 */
define('ANNOTATION_TAXONOMY_NAME', 'tags'); // needs to match name in annotation.install
define('ANNOTATION_CATEGORY_TAXONOMY', 'annotation_categories');

function annotation_api_endpoint($id = NULL) {
  $method = $_SERVER['REQUEST_METHOD'];
  switch ($method) {
    case 'GET':
      if (isset($id) && is_numeric($id)) {
        annotation_api_read($id);
      }
      else {
        annotation_api_index();
      }
      break;
    case 'POST':
      annotation_api_create();
      break;
    case 'PUT':
      annotation_api_update($id);
      break;
    case 'DELETE':
      annotation_api_destroy($id);
      break;
  }
}

/**
 * Annotation API root
 */
function annotation_api() {
  drupal_json_output(
    array(
      'name' => 'Annotator Store API',
      'version' => ANNOTATOR_VERSION,
      )
    );
}

/**
 * Annotation API index
 */
function annotation_api_index() {
  // access check unnecessary: we're using EFQ, which checks permissions
  // if (annotation_access('view')) {
    $query = new EntityFieldQuery();
    $query->entityCondition('entity_type', 'node');
    $query->entityCondition('bundle', 'annotation');
    $records = $query->execute();
    foreach ($records as $rid => $record) {
      $records[$rid] = annotation_api_entity_prepare($record, 'read');
    }
    // Send response
    return drupal_json_output(array_values($records));
  // }
  // return FALSE;
}

/**
 * Collapse all URL aliases into a single URL for Annotator
 * Annotator.js uses window.location.href
 * We use the canonical Drupal path instead
 */
function annotation_sanitize_uri($uri) {
    global $base_root;  // for parsing the URI
    $root = $base_root . base_path();
    $parsed = drupal_parse_url($uri);
    $uri = $parsed['path'];
    $uri = preg_replace("/#.*$/", "", $uri);  // sanitize
    $path = str_replace($root, "", $uri);
    $real_path = drupal_lookup_path('source', $path); // in case of aliases
    if ($real_path) {
      $path = $real_path;
    }
    // Sometimes we need only the internal path; sometimes we need the full URL
    return(array('root' => $root, 'path' => $path));
}

function get_term_id($term_name, $taxonomy_name) {
  $taxonomy = taxonomy_vocabulary_machine_name_load($taxonomy_name);
  $terms = taxonomy_get_term_by_name($term_name, $taxonomy_name);
  $tid = NULL;
  foreach ($terms as $term) {
    if ($term->vid == $taxonomy->vid) {
      $tid = $term->tid;
      break;  // go with the first match
    }
  }
  return($tid);
}

/**
 * Convert plain text tags into Drupal taxonomy terms
 **/
function annotation_format_tags(&$entity, $tags) {
  // Load, create, and format taxonomy term references
  $taxonomy = taxonomy_vocabulary_machine_name_load(ANNOTATION_TAXONOMY_NAME);
  $entity->field_annotation_tags = array(); // we'll be re-adding terms if they already exist
  foreach (array_values($tags) as $raw_tag) { // Annotator passes them as array
    $tid = NULL;
    // Expect comma-separated values
    $tags = explode(',', $raw_tag);
    foreach (array_values($tags) as $tag) {
      $tag = trim($tag);
      if (strlen($tag)) {
        $tid = get_term_id($tag, ANNOTATION_TAXONOMY_NAME);
        if (!$tid) {
          // add new term to taxonomy
          $term = new stdClass();
          $term->name = $tag;
          $term->vid = $taxonomy->vid;
          taxonomy_term_save($term);
          $tid = $term->tid;
        }
        $entity->field_annotation_tags[$entity->language][]['tid'] = $tid;
      }
    }
  }
}

/**
 * Convert JSON annotation data into Drupal data structures
 **/
function annotation_drupal_format($entity, $update = FALSE) {
  global $user;

  if (!$update) {
    // Not an update; initialize the annotation object
    $annotation = new stdClass();
    $annotation->type = 'annotation';
    $annotation->uid = $user->uid;
    $annotation->created = REQUEST_TIME;
    $annotation->language = LANGUAGE_NONE;
    // Get real Drupal URL of the annotated content, plus our base path
    $result = annotation_sanitize_uri($entity->uri);
    $uri = $result['root'] . $result['path'];
    $node = menu_get_object($type = 'node', $position = 1, $result['path']);
    $annotation->uri = array();
    $annotation->uri[$annotation->language][0]['url'] = $uri;  // formatted for Link field
    $annotation->uri[$annotation->language][0]['title'] = $node->title;
    $annotation->field_annotation_reference[$annotation->language][] = array(
      'target_id' => (int) $node->nid,
      'target_type' => 'node'
    );
    $annotation->title = 'Annotation of ' . $node->title; // add document name and author?
  }
  else {
    $annotation = node_load($entity->id);
    // Wipe all values that users might change
    // They'll be added back in the switch below
    // Probably a better way to do this
    unset($annotation->text);
    // unset($annotation->permissions);
  }
  $annotation->updated = REQUEST_TIME;

  $fields = array_keys(field_info_instances('node', 'annotation'));
  foreach ($entity as $key => $val) {
    switch($key) {

      case 'tags':
        annotation_format_tags($annotation, $val);
        break;

      case 'category':
        // Categories are taxonomy references
        $tid = get_term_id($val, ANNOTATION_CATEGORY_TAXONOMY);
        if (isset($tid)) {
          $annotation->field_annotation_category[$annotation->language][0]['tid'] = $tid;
        }
        break;

      case 'ranges':
        if (!$update) {
          $annotation->field_annotation_ranges[$annotation->language][0]['value'] = json_encode($val);
        }
        break;

      case 'privacy_options':
        dpm($val, 'selected privacy options');

        // Private
        if ($val['private'] == 1) {
          $annotation->field_annotation_private[$annotation->language][0] = array('value' => 1);
        }

        // Not private
        else {
          $annotation->field_annotation_private[$annotation->language][0] = array('value' => 0);

          // Co-learners
          if ($val['audience']['co-learners'] == 1) {
            $users_groups = og_get_groups_by_user();
            $possible_groups =  array_replace ($val['groups']['peer_groups'], $val['groups']['course_groups']);
            $groups_to_set = array();
            foreach ($possible_groups as $possible_group_nid => $possible_group_properties) {
              if ($possible_group_properties['selected'] == 1) {
                // In case the user hacked the JS, make sure they are only adding the annotation to groups they are a member of.
                // This is in fact necessary because OG will not catch these (because it's the annotator, ie. system, creating the group ref here, not the user submitting the annotation, which OG would catch)
                if (in_array($possible_group_nid, $users_groups['node'])) {
                  $groups_to_set[] = array('target_id' => $possible_group_nid);
                }
              }
            }
            $annotation->og_group_ref[$annotation->language] = $groups_to_set;
          }
        }

        // TODO: Not sure if this field is relevant given our own permission handling. Leaving unset for now
        // $annotation->group_content_access[$annotation->language][0]['value'] = $val['group_visibility'];

        break;

      default:
        // Only prepare fields that exist in the annotation node
        if (in_array('field_annotation_' . $key, $fields) & ($val != NULL) & !isset($annotation->{'field_annotation_' . $key})) {
          $annotation->{'field_annotation_' . $key} = array();
          $annotation->{'field_annotation_' . $key}[$annotation->language][0]['value'] = $val;
        }
    }
  }
  // Sanitize the category input (i.e., server-side validation)
  // Can't be done reliably in an Annotator plugin
  // @see https://lists.okfn.org/pipermail/annotator-dev/2014-May/000935.html
  if (empty($annotation->field_annotation_text)) {
    // Just a highlight, no category
    unset($annotation->field_annotation_category);
  } elseif (empty($annotation->field_annotation_category)) {
    // Text, but no category; choose the first one as default
    $categories = taxonomy_vocabulary_machine_name_load(ANNOTATION_CATEGORY_TAXONOMY);
    $category_terms = taxonomy_get_tree($categories->vid);
    $annotation->field_annotation_category[$annotation->language][0]['tid'] = $category_terms[0]->tid;
  }

  return($annotation);
}

/**
 * Annotation API create and update
 */
function annotation_api_create() {
  if (annotation_access('create')) {
    $entity = annotation_api_from_stdin();
    $annotation = annotation_drupal_format($entity);
    $annotation->comment = 2; // enable comments
    $annotation = node_submit($annotation);
    node_save($annotation);
    $annotation->id = $annotation->nid; // set ID for Annotator
    // Send response
    // ddl($annotation, 'create');
    return drupal_json_output($annotation);
  }
  return FALSE;
}

/**
 * Annotation API read
 */
function annotation_api_read($id) {
  if ($annotation = node_load($id)) {
    if (annotation_access('view', $annotation)) {
      $record = annotation_api_entity_prepare($annotation, 'read');
      // Send response
      return drupal_json_output($record);
    }
  }
  return FALSE;
}

/**
 * Annotation API update
 */
function annotation_api_update($id) {
  $annotation = node_load($id);
  if ($annotation != FALSE) {
    if (annotation_access('edit', $annotation)) {
      $entity = annotation_api_from_stdin();
      $annotation = annotation_drupal_format($entity, TRUE);
      node_save($annotation);
      // Send response
      drupal_goto('annotation/api/annotations/' . $id, array(), 303);
      return TRUE;
    }
  }
  return FALSE;
}

/**
 * Annotation API destroy
 */
function annotation_api_destroy($id) {
  $annotation = node_load($id);
  if ($annotation != FALSE) {
    if (annotation_access('delete', $annotation)) {
      node_delete($id);
      // Send response
      drupal_add_http_header('Status', '204 NO CONTENT');
      return drupal_json_output(NULL);
    }
  }
  return FALSE;
}

/**
 * Annotation API search
 */
function annotation_api_search() {
  $total = 0;
  $records = array();
  if (user_access('access content')) {
    if (isset($_GET['user'])) {
      $username = $_GET['user'];
      $account = user_load(array('name' => check_plain($username)));
      $uid = $account->uid;
    }
  }
  else {
    global $user;
    if (isset($user->name)) {
      $uid = $user->uid;
    }
    else {
      $output = array(
        'total' => 0,
        'rows' => array(),
        );
      return drupal_json_output($output);
    }
  }

  // $uid     = isset($_GET['uid'])     ? $_GET['uid']        : $uid;
  $limit   = isset($_GET['limit'])   ? $_GET['limit']      : 20;
  $offset  = isset($_GET['offset'])  ? $_GET['offset']     : 0;
  $id      = isset($_GET['id'])      ? $_GET['id']         : NULL;
  $nid     = isset($_GET['nid'])     ? $_GET['nid']        : NULL;
  $created = isset($_GET['created']) ? $_GET['created']    : NULL;
  $updated = isset($_GET['updated']) ? $_GET['updated']    : NULL;
  $text    = isset($_GET['text'])    ? $_GET['text']       : NULL;
  $quote   = isset($_GET['quote'])   ? $_GET['quote']      : NULL;
  $uri     = isset($_GET['uri'])     ? $_GET['uri']        : NULL;
  $tags    = isset($_GET['tags'])    ? explode(',', $tags) : NULL;
  $category= isset($_GET['category'])     ? $_GET['category']        : NULL;

  $uri_result = annotation_sanitize_uri($uri);  // get the Drupal path
  $uri = $uri_result['root'] . $uri_result['path'];
  // Initiate query
  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'annotation');

  // Add conditions to query
  if ($id) {
    $query->propertyCondition('nid', $id);  // changed from 'uri' - mlw
  }
  if (isset($uid)) {
    // Use uid instead of user
    $query->propertyCondition('uid', $uid);
  }

  if ($created) {
    $query->propertyCondition('created', $created);
  }
  if ($updated) {
    $query->propertyCondition('updated', $updated);
  }
  if ($text) {
    $query->fieldCondition('text', 'value', $text, 'LIKE');
  }
  if ($quote) {
    $query->fieldCondition('quote', 'value', $quote, 'LIKE');
  }

  if ($uri) {
    // Note: The URL field is provided by the Link module (https://www.drupal.org/project/link)
    // This module has several values for each entry, not stored in the "value" column
    // Instead, stored in the "url" column - MLW
    $query->fieldCondition('uri', 'url', $uri, '=');
  }

  // TODO: convert this to a term reference query
  if (is_array($tags)) {
    foreach($tags as $tag) {
      $query->fieldCondition('field_annotation_tags', '"' . $tag . '"', 'LIKE');
    }
  }
  if ($category) {
    // This will need adjustment for explode/implode of categories
    $query->fieldCondition('field_annotation_category', $category);
  }

  // Get the total
  $count_query = clone $query;
  $total = $count_query->count()->execute();

  // Set query range
  if ($limit > 0) {
    $query->range($offset, $limit);
  }
  $result = $query->execute();
  if (isset($result['node'])) {
    // Load all the annotation nodes by nid
    // nid appears in the query results as the keys
    $records = node_load_multiple(array_keys($result['node']));
  }

  foreach ($records as $rid => $record) {
    $records[$rid] = annotation_api_entity_prepare($record, 'read');
  }

  $output = array(
    'total' => $total,
    'rows' => array_values($records),
    );
  return drupal_json_output($output);
}

/**
 * Get data from stdin
 * @see http://php.net/manual/en/features.file-upload.put-method.php
 */
function annotation_api_from_stdin() {
  $json = '';
  // PUT data comes in on the stdin stream
  $put = fopen('php://input', 'r');
  // Read the data 1 KB at a time and write to the file
  while ($chunk = fread($put, 1024)) {
    $json .= $chunk;
  }
  fclose($put);

  $entity = (object) drupal_json_decode($json);
  // $entity = annotation_api_entity_prepare($entity); // does nothing; no $op
  return $entity;
}

/**
 * Prepare entity for api usage
 */
function annotation_api_entity_prepare($annotation, $op) {
  $entity = new stdClass();
  $entity->id = $annotation->nid; // Annotator wants our nid in the id field
  $annotation_wrapper = entity_metadata_wrapper ('node', $annotation);
  global $user;
  switch($op) {
    case 'read':
      $account = user_load($annotation->uid);
      $entity->user = array(
        'uid' => $account->uid,
        'name' => format_username($account),
        'roles' => array_values($account->roles),
        );

      // Translate Drupal-encoded content back into something Annotator.js can use

      // Ranges
      $entity->ranges = drupal_json_decode($annotation->field_annotation_ranges[$annotation->language][0]['value']);

      // Text
      if (isset($annotation->field_annotation_text[$annotation->language]) && count($annotation->field_annotation_text[$annotation->language])) {
        $entity->text = $annotation->field_annotation_text[$annotation->language][0]['value'];
      } else {
        $entity->text = null; // Otherwise, Annotator chokes on an empty array
      }

      // Quote
      $entity->quote = $annotation->field_annotation_quote[$annotation->language][0]['value'];

      // Category is for the Category plugin
      // Uses a Drupal taxonomy, like tags
      if (isset($annotation->field_annotation_category) && !empty($annotation->field_annotation_category)) {
        $category = taxonomy_term_load($annotation->field_annotation_category[$annotation->language][0]['tid']);
        if ($category) {
          $entity->category = $category->name;
        }
      }

      // Tags
      if (isset($annotation->field_annotation_tags[$annotation->language])) {
        $entity->tags = array();
        foreach(array_values($annotation->field_annotation_tags[$annotation->language]) as $item) {
          $term = taxonomy_term_load($item['tid']);
          array_push($entity->tags, $term->name);
        }
      }

			// Privacy options

      $entity->privacy_options['audience'] = array(
        'private' => 0,
        'co-learners' => 1,
        'everyone' => 0,
        'instructor' => 0,
      );

      // Groups
      if ($referenced_node = $annotation_wrapper->field_annotation_reference->value()) {

        // Get selected groups
        if (isset($annotation->og_group_ref)) {
          $selected_groups = array();
          foreach ($annotation->og_group_ref[$annotation->language] as $group) {
            $selected_groups[] = $group['target_id'];
          }
        }

        // Get possible groups, and unmark those that are not selected for this annotation
        $possible_groups = annotation_get_possible_groups_for_document($referenced_node);
        foreach ($possible_groups as $group_type => $group_type_possible_groups) {
          foreach ($group_type_possible_groups as $group_nid => $group_properties) {
            if (!in_array($group_nid, $selected_groups)) {

              $possible_groups[$group_type][$group_nid]['selected'] = 0;
            }
          }
        }
        $entity->privacy_options['groups'] = $possible_groups;
      }


      /////////////////////////////////////////////////////////////////////////////////////
      //
      // TODO: REVIEW
      //

      //Private
      if (isset($annotation->field_annotation_private)) {
        // Format permissions for the Annotator Permissions plugin
        // We only implement "read" permissions right now
        // This setting is strictly to respect the current checkbox settings
        // Drupal permissions control what is actually shown
        $entity->permissions = array();
        if ($annotation->field_annotation_private[$annotation->language][0]['value'] == 0) {
          $entity->permissions['read'] = array();
        }
        else {
          $entity->permissions['read'][] = $account->uid;
        }
      }

			// Sharing
      // Currently not implemented: sharing edit permission
      $entity->permissions['update'][] = $account->uid;
      $entity->permissions['delete'][] = $account->uid;
      // Check privileges, but don't duplicate uids
      if (user_access('edit any annotations') && $user->uid != $account->uid) {
        array_push($entity->permissions['update'], $user->uid);
        array_push($entity->permissions['delete'], $user->uid);
      }
      //
      //
      //
      /////////////////////////////////////////////////////////////////////////////////////

      // Links
      $entity->links[] = array(
        'href' => url('node/' . $annotation->nid),
        'rel' => 'alternate',
        'type' => 'text/html',
        );

    break;

    // These two cases handled by annotation_drupal_format
    case 'create':
      break;
    case 'update':
      break;
  }
  // ddl($entity, 'entity after prep');
  return $entity;
}
