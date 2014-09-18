<?php

$lib_path = dirname(__FILE__) . '/../lib/';

require_once $lib_path . 'Graph.class.php';
require_once $lib_path . 'DirectedGraph.class.php';
require_once $lib_path . 'DirectedAcyclicGraph.class.php';

use GraphAPI\Component\Graph\Graph;
use GraphAPI\Component\Graph\DirectedGraph;
use GraphAPI\Component\Graph\DirectedAcyclicGraph;

testDelete();
testGraph();
testDirectedGraph();
testDirectedAcyclicGraph();

echo "\n\n";

function testDelete() {
  $g = new Graph();
  $g->addLink('a', 'b');
  echo $g . "\n";
  $g->deleteNode('a');
  echo $g . "\n";
  $g->deleteNode('b');
  echo $g . "\n";
}

function testGraph() {
  $g = new Graph();
  buildCyclicGraph($g);
  dumpGraph($g, 'Cyclic');

  $g = new Graph();
  buildACyclicGraph($g);
  dumpGraph($g, 'A-Cyclic');

  $g = new Graph();
  buildDisjunctCyclicGraph($g);
  dumpGraph($g, 'Disjunct Cyclic');

  $g = new Graph();
  buildDisjunctACyclicGraph($g);
  dumpGraph($g, 'Disjunct A-Cyclic');
}

function testDirectedGraph() {
  $g = new DirectedGraph();
  buildCyclicGraph($g);
  dumpGraph($g, 'Cyclic');

  $g = new DirectedGraph();
  buildACyclicGraph($g);
  dumpGraph($g, 'A-Cyclic');

  $g = new DirectedGraph();
  buildDisjunctCyclicGraph($g);
  dumpGraph($g, 'Disjunct Cyclic');

  $g = new DirectedGraph();
  buildDisjunctACyclicGraph($g);
  dumpGraph($g, 'Disjunct A-Cyclic');
}

function testDirectedAcyclicGraph() {
  $g = new DirectedAcyclicGraph();
  $message = "CyclicGraph";
  try {
    buildCyclicGraph($g);
    echo "\nERROR : ($message) should throw an exception.";
  }
  catch (\Exception $exc) {
    echo "\nOK : ($message) " . $exc->getMessage();
  }

  $g = new DirectedGraph();
  buildCyclicGraph($g);
  $message = "Unable to convert CyclicGraph from DG to DAG";
  try {
    $d = DirectedAcyclicGraph::fromDirectedGraph($g);
    echo "\nERROR : ($message) should throw an exception.";
  }
  catch (Exception $exc) {
    echo "\nOK : ($message) " . $exc->getMessage();
  }

  $g = new DirectedGraph();
  buildCyclicGraph($g);
  $message = "Converting CyclicGraph from DG to DAG";
  try {
    $d = DirectedAcyclicGraph::fromDirectedGraph($g, TRUE);
    echo "\nOK : ($message) $g trasnformed into $d";
  }
  catch (\Exception $exc) {
    echo "\nERROR : ($message) " . $exc->getMessage();
  }

  $g = new DirectedAcyclicGraph();
  buildACyclicGraph($g);
  dumpGraph($g, 'A-Cyclic');

  $g = new DirectedAcyclicGraph();
  try {
    buildDisjunctCyclicGraph($g);
    dumpGraph($g, 'Disjunct Cyclic');
  }
  catch (Exception $exc) {
    dumpGraph($g, 'Disjunct Cyclic');
    echo "\n" . $exc->getMessage() . "\n\n";
  }

  $g = new DirectedAcyclicGraph();
  buildDisjunctACyclicGraph($g);
  dumpGraph($g, 'Disjunct A-Cyclic');

  $g = new DirectedAcyclicGraph();
  buildModuleVersionDependency($g);
  dumpGraph($g, 'Module version dependency');
}

function dumpRooted($g) {
  $g->addRoot('ROOT');
  echo "\nROOTED: " . $g;
  $g->addRoot('ROOT-WOOT');
  echo "\nROOT-WOOTED: " . $g;
}

function buildModuleVersionDependency(Graph $g) {
  $g->addLink('views', 'ctools', array('testing'), '>=2.x');
  $g->addLink('views_ui', 'views', array('testing'), '>=2.x');
}

function dumpGraph(Graph $g, $message) {
  $c = get_class($g);
  echo "\n\n\n====== " . get_class($g) . " : $message ======\n\n";
  echo $g . "\n";

  dumpRooted($g);
  $ids = $g->getNodeIds();
  // Add non existing node to the list.
  $ids[] = 'z';
  dumpParticipants($g);
  showParts($g);
  if ($g instanceof DirectedGraph) {
    dumpReverse($g);
  }
  if ($g instanceof DirectedAcyclicGraph) {
    dumpTSL($g);
  }
}

function showParts(Graph $g) {
  echo "\nDisjunct: " . ($g->isSplit() ? "YES" : "NO");
  $p = $g->getParts();
  echo "\nParts: " . join(",", $p);
}

function dumpReverse(DirectedGraph $g) {
  echo "\nReversed: " . $g->getReversedGraph() . "\n";
}

function dumpTSL(DirectedAcyclicGraph $g) {
  echo "\nTSL: " . join(',', $g->getTSL()) . "\n";
}

function dumpLink(Graph $g, $id) {
  $arr = $g->getLinks($id);
  if (is_null($arr)) {
    echo "\nLinks $id: NULL";
  }
  else {
    echo "\nLinks $id: " . join(',', $arr);
  }
}

function dumpParticipants(Graph $g) {
  $nids = $g->getNodeIds();

  $parts = array();
  foreach ($nids as $id) {
    $p = $g->getParticipants(array($id));
    asort($p);
    $key = join(',', $p);
    $parts[$key] = "Participating group: $key";
  }
  echo "\n" . join("\n", $parts);
  // All
  $p = $g->getParticipants();
  asort($p);
  $key = join(',', $p);

  echo "\nParticipants ALL   : $key";
}

function buildCyclicGraph(Graph $g) {
  $g->addLink('a', 'b');
  $g->addLink('b', 'c');
  $g->addLink('c', 'a');
  $g->addLink('a', 'b', 'DATA', 'KEY');
}

function buildACyclicGraph(Graph $g) {
  $g->addLink('a', 'b');
  $g->addLink('b', 'c');
  $g->addLink('a', 'c');
  $g->addLink('a', 'b', 'DATA', 'KEY');
}

/**
 * Graph has disconnected subgraphs.
 *
 * @param type $g
 */
function buildDisjunctCyclicGraph(Graph $g) {
  buildCyclicGraph($g);
  $g->addLink('p', 'q');
}

function buildDisjunctACyclicGraph(Graph $g) {
  buildACyclicGraph($g);
  $g->addLink('p', 'q');
}
