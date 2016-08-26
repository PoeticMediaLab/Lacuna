<?php
/**
 * Routines for the Responses visualization
 *
 * Mostly developed by Ben Allen
 */

/**
 * Visualization showing links between student responses and primary
 * sources.
 */
function lacuna_visualizations_responses() {

  $nids = array();
  $graph = graphapi_new_graph();
  $gid = course_get_selected_course();

  // Because OG has no API for getting all group content per group ಠ_ಠ
  $sql = "SELECT nid FROM node n
               INNER JOIN og_membership ogm ON n.nid = ogm.etid
               WHERE ogm.gid = '" . $gid . "'
               AND ogm.entity_type = 'node'
               AND n.type IN ('document', 'response')
               AND n.status = '" . NODE_PUBLISHED . "'";
  $result = db_query($sql)->fetchAll();
  $nids = array();
  foreach ($result as $row) {
    $nids[] = $row->nid;            // i'm guessing nid has to do with the id of each node
  }

  // All documents and responses for current course
  $nodes = node_load_multiple($nids);

  $biblio_ids = array();
  foreach ($nodes as $node) {
    if ($node->type == 'document') {
      $biblio_ids[] = $node->field_bibliographic_entry[$node->language][0]['target_id'];
    }
  }

  // Load all relevant bibliography references           // <--does this refer to bibliography (as in mention of doc in resposne), as well as responses, as well as docs?
  $biblios = node_load_multiple($biblio_ids);
  $nodes = array_merge($nodes, $biblios);

  // Generate document->bibliography mappings
  foreach ($nodes as $node) {
    if ($node->type == 'document') {
      $doc_ids[$node->field_bibliographic_entry[$node->language][0]['target_id']] = $node->nid;
      // maybe need to change $node->biblio_ids..............
    }
  }

  foreach ($nodes as $item) {
    // this array will eventually contain all relevant info about responses and document: author, timestamp, etc.
    // added to nodes before graphapi passes off to d3.
    if ($item->type == 'response') {
      // Note the different field name for biblio refs in Responses
      $docId = $doc_ids[$item->field_bibliographic_item[$item->language][0]['target_id']]; // right now this only saves ONE biblio reference id#; but the biblio references are stored in this index ^^^
      /*
      DEBUGGING:
      print_r($item->title);
      print_r('(');
      print_r($item->nid);
      print_r('&');
      print_r($docId);
      print_r('&');
      print_r($item->field_bibliographic_item[$item->language][0]['target_id']);
      print_r(')'); */
    }
    if ($item->type == 'biblio') {
      $docId = $doc_ids[$item->nid];
      // print_r('b');
    }
    if ($item->type == 'document') {
      // print_r('d');
      continue; // we just load those for ease of setup
    }
    $dataArray = array(
      'itemType' => $item->type,
      // author set below -- $item->name for responses, but
      // more complicated for biblio entries.
      'author'=> null,
      'u_id' => $item->uid,
      'title' => $item->title,
      'linksTitles' => array(),
      // 'thisURL' => get_link_url($docId, $item->nid),       // this was the original, but changed it to the following so that response nodes' popups still hyperlink to the response URL when a bibliographic item is set, rather than the bibliography url:
      'thisURL' => get_link_url($docId, $item->nid, $item->type),          // links to the document node...
      'image' => get_image($item, $docId),
      'linksURL' => array(get_link_url($docId, $item->nid, 'biblio')),     // hard sets $item->type to 'biblio' to account for responses that need to hyperlink to documents, not themselves
      'biblio' => array(),
      'document_abstract' => null,
      'date' => $item->created,
    );

    // added to all links before graphapi passes off to d3.
    // Currently only contains a date (the time that the source
    // node was created; currently assuming that all links are
    // created at the same time as the response they're
    // associated with.

    $title = $item->title;
    /* pull out data needed for biblio nodes and add it to
     * $dataArray */
    if ($item->type == "biblio") {
      $document_abstract = strip_tags($item->biblio_abst_e);
      $dataArray['document_abstract'] = $document_abstract;
      if (isset($item->biblio_contributors[0])) {
        $count = count($item->biblio_contributors);
        for ($i = 0; $i < $count; $i++) {
          $author = $item->biblio_contributors[$i]['name'];
          $dataArray['author'] .= $author;
          if ($i != $count-1) {
            $dataArray['author'] .= "; ";
          }
          else {
            $dataArray['author'] .= " (" . $item->biblio_year . ")";
          }
        }
      }
      else {
        $dataArray['author'] = "None";
      }
    }


    if ($item->type == "response") {
      $dataArray['author'] = $item->name;

      // draw links based off of node's field_bibliographic_entry.
      // this is a rewrite of the below outcommented code
      // which essentialy changes references to $field_bibliographic_entry to $docId
      // (NOTE: THIS DOES NOT WORK FOR RESPONSES THAT HAVE MULTIPLE BIBLIO LINKS):
      /*
      DEBUGGING:
      print_r(isset($item->field_bibliographic_item[$item->language][0]['target_id']));
      print_r('-');
      */
      if (isset($item->field_bibliographic_item)) {// !empty($docId)) {   //OKAY NEVER MIND: FIELD_BIBLIOGRAPHIC_ITEM, NOT FIELD_BIBLIOGRAPHIC_ENTRY
        $linkArray = $item->field_bibliographic_item;// $docId;

        // not sure what this does...
        for ($i = 0; $i < count($linkArray[LANGUAGE_NONE]); $i++) {// count($linkArray[LANGUAGE_NONE]); $i++) {                       // i think linkArray is supposed to store multiple $docIds, or at least an array of docIds...need to check how many $field_bibliographic_entry's there are
          // $linkedNid = $linkArray[LANGUAGE_NONE][$i]['target_id'];
          $linkedNid = $linkArray[LANGUAGE_NONE][$i]['target_id'];
          /* DEBUGGING:
          print_r($linkedNid);
          print_r('/');
          print_r($item->nid);
          print_r('//'); */
          if (array_key_exists($linkedNid, $nodes)) {
            // graphapi_add_link($graph, $title, $nodes[$linkedNid]->title);
            graphapi_add_link($graph, $item->nid, $linkedNid);                                // added this
            $linkedNid_title = '';
            foreach($nodes as $node) {
              if ($node->type == 'document') {
                if ($node->nid == $linkedNid) {
                  $linkedNid_title = $node->title;                                           // sets title
                }
              }
            }
            // array_push($dataArray['linksTitles'], $nodes[$linkedNid]->title);              // original of below
            array_push($dataArray['linksTitles'], $linkedNid_title);                 // changed $linkedNid to $item->nid
            array_push($dataArray['linksURL'], $GLOBALS['base_url'] . '/node/' . $linkedNid);
            graphapi_set_link_data($graph, $title, $nodes[$linkedNid]->title, $item->created);
          }
        }
      } // end if($item->field_bibliographic_item)

      /*
      if (isset($item->field_bibliographic_entry)) {
        $linkArray = $item->field_bibliographic_entry;
        for ($i = 0; $i < count($linkArray[LANGUAGE_NONE]); $i++) {
          $linkedNid = $linkArray[LANGUAGE_NONE][$i]['target_id'];
          if (array_key_exists($linkedNid, $nodes)) {
            // graphapi_add_link($graph, $title, $nodes[$linkedNid]->title);
            array_push($dataArray['linksTitles'], $nodes[$linkedNid]->title);
            array_push($dataArray['linksURL'], $GLOBALS['base_url'] . '/node/' . $linkedNid);
          	graphapi_set_link_data($graph, $title, $nodes[$linkedNid]->title, $item->created);
          }
        }
      } // end if($item->field_bibliographic_item)
      */
    }	// end if($item->type == "response")
    graphapi_set_node_data($graph, $title, $dataArray);
  }

  $usersQuery = new EntityFieldQuery();
  $usersQuery->entityCondition('entity_type', 'user');
  $usersResult = $usersQuery->execute();
  $uids = array_keys($usersResult['user']);
  $users = array();
  if (!empty($uids)) {
    $users = user_load_multiple($uids);
  }
  // settings.config
  $options = array(
    'width' => 800,
    'height' => 600,
    'item-width' => 45,
    'engine' => 'd3',
    'library' => 'maps',
    'userList' => $users,
    'drawDocumentCircle' => true,
  );
  return theme('graphapi_dispatch', array('graph' => $graph, 'config' => $options));
}  // end function lacuna_visualizations_responses()
