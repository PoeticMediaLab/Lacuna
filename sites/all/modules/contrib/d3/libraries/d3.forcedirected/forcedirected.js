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

    // Add definitions
    var defs = svg.append("defs");

    defs.selectAll("marker")
        .data([
          { id: 'arrow', path : "M-5,-5L5,0L-5,5"},
          { id: 'circle', path: 'M 0, 0  m -5, 0  a 5,5 0 1,0 10,0  a 5,5 0 1,0 -10,0'}
        ])
      .enter().append("marker")
        .attr("id", function (d) {
            return d.id;
        })
        .attr("viewBox", "-5 -5 10 10")
        .attr("refX", 10)
        .attr("refY", 0)
        .attr("markerWidth", 10)
        .attr("markerHeight", 10)
        .attr("orient", "auto")
        .append("path")
        .attr("d", function(d){return d.path;})
        .attr('class', function(d){return 'marker marker-' + d.id})
        .style('fill', '#000')
    ;

    var graph = svg.append("g")
        .attr("class", "data");

    force
        .nodes(nodes)
        .links(links)
        .start();

    var link = graph.selectAll("line.link")
        .data(links)
      .enter().append("line")
        .attr("marker-end", function (d) {
            return "url(#arrow)";
        })
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

    // filter on items that have and don't have an d.data.uri
    var hasUri = function(d) { return d.data && d.data.uri && d.data.uri.length > 0;};
    var noUri = function(d) { return !hasUri(d)};
    node.filter(hasUri)
      .append("svg:a")
        .attr("xlink:href", function(d) {
          return d.data.uri;
        })
      .append("svg:text")
        .attr("class", "nodetext")
        .attr("dx", 10)
        .attr("dy", ".35em")
        .attr('font-size', '10')
        .text(function(d) { return d.name });

    node.filter(noUri)
      .append("svg:text")
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
