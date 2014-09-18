/**
 * @file
 * D3 Module Depedencies library
 */

(function($) {
  Drupal.d3.module_dependencies = function (select, settings) {
    var width   = (settings.config.width || 300),
        height  = (settings.config.height || 300),
        nodes   = settings.nodes,
        links   = settings.links,
        z       = d3.scale.ordinal().range(["blue", "red", "orange", "green"]),
        k       = Math.sqrt(nodes.length / (width * height)),
        color   = d3.scale.category20();

    // Add an attribute to each node that is a source node so that we can
    // use that attribute to style them differently.
    links.map(function(d) { nodes[d.target].is_source = true; });

    var force = d3.layout.force()
      .size([width, height])
      .charge(-100)
      .distance(100)
      .gravity(.05);

    // additional settings for the advanced force directed graphs
    if (settings.gravity) {
      force.gravity(settings.gravity)
    }
    if (settings.friction) {
      force.friction(settings.friction)
    }
    if (settings.theta) {
      force.theta(settings.theta)
    }
    if (settings.charge) {
      force.charge(settings.charge)
    }
    if (settings.linkDistance) {
      force.linkDistance(settings.linkDistance)
    }

    var svg = d3.select('#' + settings.id).append("svg")
        .attr("width", width)
        .attr("height", height);

    var graph = svg.append("g")
        .attr("class", "data");

    force
        .nodes(nodes)
        .links(links)
        .start();

    var link = graph.selectAll("line.link")
        .data(links)
      .enter().append("line")
        .attr("class", "link")
        .style("stroke", function(d) {  return d3.hsl(d.data.fill); })
        .style("stroke-width", 1);

    var node = graph.selectAll("g.node")
        .data(nodes)
      .enter().append("svg:g")
        .attr("class", "node")
        .call(force.drag);

    node.append("svg:circle")
      .attr("class", "node")
      .attr("r", function(d) { return (d.is_source) ? 7 : 5; })
      .style("fill", function (d) { return (d.is_source) ? d3.hsl('black') : d3.hsl('white'); })
      .style("stroke", function(d) { return d3.hsl(d.data.fill); })
      .style("stroke-width", function(d) { return (d.is_source) ? 0 : 3; });

    node.append("svg:text")
        .attr("class", "nodetext")
        .attr("dx", 10)
        .attr("dy", ".35em")
        .attr('font-size', '10')
        .text(function(d) { return d.name });

    force.on("tick", function() {
      link.attr("x1", function(d) { return d.source.x; })
          .attr("y1", function(d) { return d.source.y; })
          .attr("x2", function(d) { return d.target.x; })
          .attr("y2", function(d) { return d.target.y; });

      node.attr("cx", function(d) { return d.x; })
          .attr("transform", function(d) { return "translate(" + d.x + "," + d.y + ")"; })
          .attr("cy", function(d) { return d.y; });
    });

  }

})(jQuery);
