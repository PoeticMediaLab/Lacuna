<?php

namespace GraphAPI\Component\Graph;

use GraphAPI\Component\Graph\Graph;

class DirectedGraph extends Graph {

  /**
   * Builds a reversed graph without data elements or multigraph.
   *
   * By reversing a graph one can easily add a root or do other calculations.
   * This method is a helper utility.
   *
   * Note: It is of no use to reverse a Graph.
   * Note: data items especially link data is semantic useless when reversed.
   *
   * @return DirectedGraph
   * @see DirectedGraph::addRoot
   *
   */
  public function getReversedGraph() {
    $g = new DirectedGraph();
    foreach (array_keys($this->_list) as $from_id) {
      $g->addNode($from_id);
      foreach ($this->getLinks($from_id) as $to_id) {
        $g->addLink($to_id, $from_id);
      }
    }
    return $g;
  }

  /**
   * A subgraph is calculated based on the participants collected based on the given node ids.
   *
   * @param array $ids
   *   The nodes interested in.
   * @return DirectedGraph
   *   The subgraph with all participants
   */
  public function subGraph($ids = array()) {
    $g = new DirectedGraph();
    $participants = $this->getParticipants($ids);
    foreach ($participants as $id) {
      $g->addNode($id);
      // Only participating links are added.
      $links = $this->getLinks($id);
      if (is_array($links)) {
        $g->addLinks($id, array_intersect($participants, $links));
      }
    }
    return $g;
  }

  /**
   * Implementation of uni directed link between two nodes
   *
   * @see addLink()
   *
   * @param string $from_id
   * @param string $to_id
   */
  protected function _addLink($from_id, $to_id, $data, $key) {
    $this->_list[$from_id][Graph::GRAPH_LINKS][$to_id][$key]['_id'] = $to_id;
    $this->_setLinkData($from_id, $to_id, $data, $key);
  }

  protected function _setLinkData($from_id, $to_id, $data, $key) {
    $this->_list[$from_id][Graph::GRAPH_LINKS][$to_id][$key][GRAPH::GRAPH_DATA] = $data;
  }

}
