/**
 * @file
 * D3 Line Graph library js file.
 */

(function($) {

  Drupal.d3.linegraph = function (select, settings) {
    var labels = [],
      key = settings.legend || [],
      rows = settings.rows,
      p = settings.padding || [10, 50, 70, 50],
      w = (settings.width || 900) - p[1] - p[3],
      h = (settings.height || 400),
      chart = settings.chart || {w: w * .60, h: h - p[0] - p[2] },
      legend = {w: w * .25, h:h},
      x = d3.scale.linear().domain([0,rows.length - 1]).range([20,chart.w]),
      y = d3.scale.linear().domain([0,maxValue(rows)]).range([chart.h, 0]),
      z = d3.scale.ordinal().range(["blue", "red", "orange", "green"]);

    var svg = d3.select('#' + settings.id).append("svg")
        .attr("width", w)
        .attr("height", h)
        .attr('class', 'container')
      .append("g");

    var graph = svg.append("g")
      .attr("class", "chart")
      .attr('height', chart.h)
      .attr("transform", "translate(" + p[3] + "," + p[0] + ")");

    var data = (key.map(function(value,index) {
      return rows.map(function(d,i) {
        labels[i] = d[0];
        return {x: i, y: + d[index + 1], index: index};
      });
    }));

    // LINES
    graph.selectAll("path.line")
        .data(data)
      .enter().append("path")
        .attr("class", "line")
        .style("stroke", function(d, i) { return d3.rgb(z(i)); })
        .style("stroke-width", 3)
        .attr("d", d3.svg.line()
        .x(function(d,i) { return x(i); })
        .y(function(d) { return y(d.y); }));

    // Creates a container for each group of circles.
    var circles = graph.selectAll("g.circles")
        .data(data)
      .enter().append("g")
        .attr('class', function(d,i) { return 'circle-group-' + i; })
        .attr("fill", function(d, i) { return d3.rgb(z(i)); });

    // Container for each circle to have a outer circle, a main one, and a rollover circle.
    var circle = circles.selectAll('g')
        .data(function(d) { return d; })
      .enter().append('g');

    var defaultSize = 6;
    var expandedSize = 9;
    var sensitiveSize = 50;
    // This is the outer circle that is not visible on init.
    circle.append('circle')
        .attr('class', function(d,i) { return 'circle-outer circle-' + i + '-outer'; })
        .attr("cx", function(d,i) { return x(i); })
        .attr("cy", function(d,i) { return y(d.y); })
        .attr('fill-opacity', 0.2)
        .attr("r", defaultSize);

    circle.append('circle')
        .attr("class", function(d,i) { return 'circle circle-' + i; })
        .attr("cx", function(d,i) { return x(i); })
        .attr("cy", function(d,i) { return y(d.y); })
        .attr("r", defaultSize);


    var mouseover = function (d, i) {
      if ($.isArray(d)) d = d[i];
      // Find the sibling circle, expand radius.

      var circle = d3.select(this.parentNode.parentNode).select('.circle-outer');
      circle.attr('r', expandedSize);

      var tip = graph.select('.tooltip')
        .attr('visibility', 'visible')
        .attr('transform', function(d,i) { return 'translate(' + circle.attr('cx') + ',' + circle.attr('cy') + ')'})
        .select('.text text:last-child').text(d.y);

      var textWidth = graph.select('.tooltip .text :last-child')[0][0].getComputedTextLength();
      textWidth = textWidth < 55 ? 55 : textWidth;
      graph.select('.tooltip .text').attr('transform', 'translate(' + (10 - 5 - textWidth / 2) + ",-40)");
      graph.select('.tooltip').selectAll('path').attr("d", d3.tooltip.tooltipPath({ w: textWidth + 10, h: 40}));
    };
    var mouseout = function (d, i) {
      if ($.isArray(d)) d = d[i];
      // Find the sibling circle and reset its radius.
      d3.select(this.parentNode.parentNode).select('.circle-outer')
        .attr('r', defaultSize);

      graph.select('.tooltip').attr('visibility', 'hidden');
    };
    circle.append('clipPath').attr("id", function (d, i) { return "clip-" + d.index + "-" + i;}).append('circle')
      .attr("class", function(d,i) { return 'circle-mouse circle-' + i + '-mouse'; })
      .attr("fill", "#000000")
      .attr("color", "#000000")
      .attr("cx", function(d,i) { return x(d.x); })
      .attr("cy", function(d,i) { return y(d.y); })
      .attr("r", sensitiveSize)
      .on("mouseover", mouseover)
      .on("mouseout", mouseout);


    d3.tooltip(graph.append('g')
      .attr('class', 'tooltip')
      .attr('visibility', 'hidden'), "");

    var voronoi = d3.geom.voronoi()
      .clipExtent([[0, 0], [w, h * 0.75]])
      .x(function (d) { return x(d.x); })
      .y(function (d) { return y(d.y); });

    var vertices = data.map(function (d, i) {
      return d.map(function (d, j) {
        var result = d;
        result.i = i;
        result.j = j;
        return result;
      });
    }).reduce(function (a, b) { return a.concat(b); });

    graph.append('g')
        .attr('class', 'voronoi')
        .attr('opacity', 0)
      .selectAll('g.voronoi').data(voronoi(vertices).map(function (d, i) {
        return {path: "M" + d.join("L") + "Z", vertex: vertices[i]}; }).filter(function(n) { return n != undefined }))
        .enter().append('path')
          .attr('class', 'voronoi')
          .attr('d', function (d) { return d.path; })
          .attr('clip-path', function (d, i) { return "url(#clip-" + d.vertex.i + "-" + d.vertex.j + ")"; })
          .on('mouseover', function (d, i) {
            var circle = graph.select('.circle-group-' + d.vertex.i).select('.circle-' + d.vertex.j + '-mouse')[0][0];
            mouseover.bind(circle)(d.vertex);
          })
          .on('mouseout', function (d, i) {
            var circle = graph.select('.circle-group-' + d.vertex.i).select('.circle-' + d.vertex.j + '-mouse')[0][0];
            mouseout.bind(circle)(d.vertex);
          });

    /* X AXIS */
    var xTicks = graph.selectAll("g.ticks")
        .data(x.ticks(rows.length - 1))
      .enter().append("g")
        .attr("class","ticks")
        .attr('transform', function(d,i) { return 'translate(' + x(d) + ',' + (chart.h) + ')'});

    xTicks.append('text')
        .text(function(d,i) { return labels[i]; })
        .attr("text-anchor", "end")
        .attr('dy', '.71em')
        .attr('transform', function(d) { return "rotate(-40)"; });

    /* Y AXIS */
    var rule = graph.selectAll("g.rule")
        .data(y.ticks(8))
      .enter().append("g")
        .attr("class", "rule")
        .attr("transform", function(d) { return "translate(0," + y(d) + ")"; });

    rule.append("line")
      .attr("x2", chart.w)
      .style("stroke", function(d) { return d ? "#ccc" : "#000"; })
      .style("stroke-opacity", function(d) { return d ? .7 : null; });

    rule.append("text")
      .attr("x", -15)
      .attr("dy", ".35em")
      .attr("text-anchor", "end")
      .text(d3.format(",d"));

    /* LEGEND */
    var legend = svg.append("g")
      .attr("class", "legend")
      .attr('width', legend.w)
      .attr("transform", "translate(" + (w - legend.w) + "," + 0 + ")");

    var keys = legend.selectAll("g")
        .data(key)
      .enter().append("g")
        .attr("transform", function(d,i) { return "translate(0," + i*25 + ")"});
        // FIXME
//        .attr("transform", function(d,i) { return "translate(0," + d3.tileText(d,15) + ")"});

    keys.append("rect")
      .attr("fill", function(d,i) { return d3.rgb(z(i)); })
      .attr("width", 16)
      .attr("height", 16)
      .attr("y", 0)
      .attr("x", 0)
      .on('mouseover', function(d,i) {
        var group = graph.select('g.circle-group-' + i);
        group.selectAll('g').select('.circle-outer').attr('r', expandedSize);
      })
      .on('mouseout', function(d,i) {
        var group = graph.select('g.circle-group-' + i);
        group.selectAll('g').select('.circle-outer').attr('r', defaultSize);
      });

    var labelWrapper = keys.append("g");

    labelWrapper.selectAll("text")
        .data(function(d,i) { return d3.splitString(key[i], 15); })
      .enter().append("text")
        .text(function(d,i) { return d})
        .attr("x", 20)
        .attr("y", function(d,i) { return i * 20})
        .attr("dy", "1em");

    function maxValue(rows) {
      var data = jQuery.extend(true, [], rows);
      data = d3.merge(data);
      var max = d3.max(data.map(function(d) {
        return + d;
      }));
      return max;
    }

  }

})(jQuery);
