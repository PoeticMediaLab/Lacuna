/**
 * @file
 * D3 Force Directed library
 */

(function($) {
  Drupal.d3.forcedirected = function (select, settings) {

    var width  = (settings.config.width || 300),
        height = (settings.config.height || 300),
        nodes  = settings.nodes,
        links  = settings.links,
        z      = d3.scale.ordinal().range(["blue", "red", "orange", "green"]),
        k      = Math.sqrt(nodes.length / (width * height)),
        color  = d3.scale.category20();

    var force = d3.layout.force()
      .size([width, height]);

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

    force.charge(-100);
    force.distance(100);
    force.gravity(.05);
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
      .attr("r", function(d) { return (d.data.d) ? d.data.d : 5; })
      .style("fill", d3.hsl('white'))
      .style("stroke", function(d) { return d3.hsl(d.data.fill); })
      .style("stroke-width", 3);

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
