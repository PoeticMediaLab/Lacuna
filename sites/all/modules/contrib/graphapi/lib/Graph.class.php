<?php

namespace GraphAPI\Component\Graph;

/**
 * @file
 *   Provides Graph class.
 *
 * This implementation uses the terms node and links.
 * A node is also called vertice while a link is equivalent with edge
 *
 * @see DirectedGraph
 * @see DirectedAcyclicGraph
 *
 * @see http://en.wikipedia.org/wiki/Graph_%28data_structure%29
 * @see http://en.wikipedia.org/wiki/Graph_%28mathematics%29
 */

/**
 * A graph is a list of links between nodes.
 *
 * Each link is bidirectional.
 */
class Graph {

  const GRAPH_LINKS = '_links';
  const GRAPH_DATA = '_data';
  const GRAPH_LINK_NO_KEY = '_link_no_key';

  /**
   * _list contains a pair of (node id, array of links to node id)
   *
   *  A graph like a -- b -- c -- a can be stored as
   *  (a, (b))
   *  (b, (c))
   *  (c, (a))
   *
   * but also like
   *  (a, (b,c))
   *  (b, (c))
   *  (c, ())
   *
   * @var array()
   *
   */
  protected $_list = array();

  protected $_data = NULL;

  public function getData() {
    return $this->_data;
  }

  public function setData($data) {
    $this->_data = $data;
  }

  /**
   * Adds id to the list of nodes.
   *
   * The data is only added when the node was non-existing yet.
   *
   * @param String $id
   *   The Id of the node to add.
   * @return Graph
   */
  public function addNode($id, $data = NULL) {
    if (!isset($this->_list[$id])) {
      $this->_list[$id] = array();
      $this->_list[$id][Graph::GRAPH_LINKS] = array();
      $this->_list[$id][Graph::GRAPH_DATA] = $data;
    }
    return $this;
  }

  /**
   * Deletes a node from the graph
   *
   * @param type $id
   * @return Graph
   */
  public function deleteNode($id) {
    if (isset($this->_list[$id])) {
      unset($this->_list[$id]);
      foreach ($this->getNodeIds() as $nid) {
        unset($this->_list[$nid][Graph::GRAPH_LINKS][$id]);
      }
    }
    return $this;
  }

  public function hasNode($id) {
    return isset($this->_list[$id]);
  }

  /**
   * Returns the IDs of the added nodes.
   *
   * @return array with IDs as values
   */
  public function getNodeIds() {
    return array_keys($this->_list);
  }

  public function getNodeData($id) {
    return $this->_list[$id][Graph::GRAPH_DATA];
  }

  public function setNodeData($id, $data) {
    $this->_list[$id][Graph::GRAPH_DATA] = $data;
  }

  /**
   * Adds a link between two node ids.
   *
   * We allow for multigraph vertices or multiple links between 2 nodes
   *
   * @param String $from_id
   *   The start point of the link.
   * @param String $to_id
   *   The end point of the link.
   * @param any $data
   *   Can hold anything. Note this get's duplicate unless it's a reference.
   * @param string $key
   *   Unique key to identify this particular link relation.
   * @return Graph
   */
  public function addLink($from_id, $to_id, $data = NULL, $key = GRAPH::GRAPH_LINK_NO_KEY) {
    $this->addNode($from_id);
    $this->addNode($to_id);
    $this->_addLink($from_id, $to_id, $data, $key);
    return $this;
  }

  /**
   * Returns the array keys of the multigraph between given node ids.
   *
   * @param string $from_id
   * @param string $to_id
   * @return array
   */
  public function getLinkIds($from_id, $to_id) {
    $result = $this->getLinks($from_id);
    if (is_array($result) && isset($this->_list[$from_id][Graph::GRAPH_LINKS][$to_id])) {
      return array_keys($this->_list[$from_id][Graph::GRAPH_LINKS][$to_id]);
    }
  }

  /**
   * Returns the data element of the given node ids and link id.
   *
   * @param string $from_id
   * @param string $to_id
   * @param string $key
   *
   * @return any
   */
  public function getLinkData($from_id, $to_id, $key = GRAPH::GRAPH_LINK_NO_KEY) {
    return $this->_list[$from_id][Graph::GRAPH_LINKS][$to_id][$key][GRAPH::GRAPH_DATA];
  }

  public function setLinkData($from_id, $to_id, $data, $key = GRAPH::GRAPH_LINK_NO_KEY) {
    $this->_setLinkData($from_id, $to_id, $data, $key);
  }

  /**
   * Adds a list of links to a node.
   *
   * This is a utility function ignoring data or multilinks.
   *
   * @param string $from_id
   * @param array $to_ids
   *
   * @return $this
   */
  public function addLinks($from_id, $to_ids) {
    foreach ($to_ids as $to_id) {
      $this->addLink($from_id, $to_id);
    }
    return $this;
  }

  /**
   * Returns all links from the give node id.
   *
   * @param string $from_id
   * @return array of node ids leaving the given node id.
   */
  public function getLinks($id) {
    if (isset($this->_list[$id])) {
      return array_keys($this->_list[$id][Graph::GRAPH_LINKS]);
    }
  }

  /**
   * Gives all participants related to the given node(s).
   *
   * @param array $list
   *   The list of Ids interested in.
   * @return array
   *   All Ids related to the given list.
   */
  public function getParticipants($list = array()) {
    if (empty($list)) {
      return $this->getNodeIds();
    }
    $visited = array();
    $agenda = array_values($list);
    while ($id = array_shift($agenda)) {
      if (!$this->hasNode($id)) {
        continue;
      }
      // Prevent infinite looping
      if (!isset($visited[$id])) {
        $visited[$id] = TRUE;
        $links = $this->getLinks($id);
        if (is_array($links)) {
          $agenda = array_merge($agenda, $links);
        }
      }
    }
    return array_keys($visited);
  }

  public function isCircularMember($id) {
    $route = $this->getParticipants(array($id));
    foreach ($route as $visited_id) {
      $links = $this->getLinks($visited_id);
      if (is_array($links) && in_array($id, $links)) {
        return TRUE;
      }
    }
    return FALSE;
  }

  /**
   * Adds a root to the graph connecting islands or loops
   *
   * A graph may have disconnected sub graphs or be one big loop. So there is
   * no single entry point into the graph.
   *
   * @param type $root_id
   */
  public function addRoot($root_id) {
    $p = $this->getParts();
    foreach ($p as $nid) {
      $this->addLink($root_id, $nid);
    }
    return $this;
  }

  /**
   * A Graph is split when having disconnected subgraphs.
   *
   * @return type
   */
  public function isSplit() {
    return count($this->getParts()) > 1;
  }

  /**
   * Gets list or IDs one for each subgraph.
   *
   * @return type
   */
  public function getParts() {
    $nids = $this->getNodeIds();
    $parts = array();
    while (!empty($nids)) {
      $nid = array_shift($nids);
      $p = $this->getParticipants(array($nid));
      $nids = array_diff($nids, $p);
      $parts = array_diff($parts, $p);
      $parts[] = $nid;
    }
    return $parts;
  }

  /**
   * Get a simple representation of the graph as a string.
   *
   * This contains a(b,c) like fragments indicating a connects to b and c.
   *
   * @return string
   */
  public function __toString() {
    $result = array();
    foreach (array_keys($this->_list) as $id) {
      $row = $id . '(';
      $links = $this->getLinks($id);
      if (is_array($links)) {
        $row .= join(',', $links);
      }
      $row .= ')';
      $result[] = $row;
    }
    return join(",", $result);
  }

  /**
   * Implementation of bidirection links between the given node ids.
   *
   * A Graph is bidirectional so we need to store the link twice.
   *
   * @param string $from_id
   * @param string $to_id
   * @param any $data
   *   Can hold anything. Note this get's duplicate unless it's a reference.
   * @param string $key
   *   Unique key to identify this particular link relation.
   */
  protected function _addLink($from_id, $to_id, $data, $key) {
    $this->_list[$from_id][Graph::GRAPH_LINKS][$to_id][$key]['_id'] = $to_id;
    $this->_list[$to_id][Graph::GRAPH_LINKS][$from_id][$key]['_id'] = $from_id;
    $this->_setLinkData($from_id, $to_id, $data, $key);
  }

  protected function _setLinkData($from_id, $to_id, $data, $key) {
    $this->_list[$from_id][Graph::GRAPH_LINKS][$to_id][$key][GRAPH::GRAPH_DATA] = $data;
    $this->_list[$to_id][Graph::GRAPH_LINKS][$from_id][$key][GRAPH::GRAPH_DATA] = $data;
  }

  protected function getId() {
    return spl_object_hash($this);
  }
}
