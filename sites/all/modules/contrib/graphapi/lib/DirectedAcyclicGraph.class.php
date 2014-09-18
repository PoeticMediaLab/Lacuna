<?php

namespace GraphAPI\Component\Graph;

use GraphAPI\Component\Graph\DirectedGraph;

class DirectedAcyclicGraph extends DirectedGraph {

  /**
   * Prevent adding a cycle.
   *
   * @param type $from_id
   * @param type $to_id
   */
  function addLink($from_id, $to_id) {
    $sub = $this->subGraph(array($to_id));
    $p = $sub->getParticipants();
    if (in_array($from_id, $p)) {
      throw new \Exception("Cannot add Cycle '$from_id' -> '$to_id' to " . $this);
    }
    else {
      parent::addLink($from_id, $to_id);
    }
  }

  /**
   * Converts a DirectedGraph into a DirectedAcyclicGraph.
   *
   * A DirectedGraph can be converted into a DirectedAcyclicGraph when
   * is does not contain any cycle.
   *
   * @param \GraphAPI\Component\Graph\DirectedGraph $g
   * @param type $ignore_exception
   * @throws \GraphAPI\Component\Graph\Exception
   */
  static function fromDirectedGraph(DirectedGraph $g, $ignore_exception = FALSE) {
    $d = new DirectedAcyclicGraph();
    foreach ($g->getNodeIds() as $id) {
      $links = $g->getLinks($id);
      foreach ($links as $link) {
        try {
          $d->addLink($id, $link);
        }
        catch (\Exception $exc) {
          if (!$ignore_exception) {
            throw $exc;
          }
        }
      }
    }
    return $d;
  }

  /**
   * Calculates the Topological Sorted List.
   *
   * A Topological Sorted List is a Depth First Search (DFS) ordered
   * list of participants.
   *
   * TODO: Do we need this method for DirectedGraph?
   * If there are cycles/loops then the algorithme does not loop forever.
   * But the TSL is not really a TSL.
   *
   * The algorithme is based on the Iterator example from
   * the book Higher Order Perl where a recusive function
   * can be rewritten into a loop.
   *
   * @param array $ids
   *   List of nodes interested in.
   * @return array
   *   The TSL ordered list of participants
   */
  public function getTSL($ids = array()) {
    $g = $this->subGraph($ids);
    // By adding a root the DFS is more cleaner/predictable for tests
    $root = $g->getId();
    $g->addRoot($root);
    $agenda = array($root);

    $visited = array();
    $tsl = array();
    while ($inspect = array_pop($agenda)) {
      if (!isset($visited[$inspect])) {
        $visited[$inspect] = TRUE;
        $links = $g->getLinks($inspect);
        if (!empty($links)) {
          array_push($agenda, $inspect);
          foreach ($links as $id) {
            if (!isset($visited[$id])) {
              $agenda[] = $id;
            }
          }
        }
        else {
          // We are done with this node.
          $tsl[] = $inspect;
        }
      }
      else {
        // Already inspected so spit it out.
        $tsl[] = $inspect;
      }
    }
    return array_diff($tsl, array($root));
  }

}
