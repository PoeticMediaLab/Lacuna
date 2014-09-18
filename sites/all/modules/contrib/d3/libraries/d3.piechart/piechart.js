/**
 * @file
 * Adds a function to generate a column chart to the `Drupal` object.
 */

/**
 * Notes on data formatting:
 * legend: array of text values. Length is number of data types.
 * rows: array of arrays. One array for each point of data
 * arrays have format array(label, data1, data2, data3, ...)
 */


(function($) {

  Drupal.d3.piechart = function (select, settings) {

    var wedges = settings.rows,
      // Each wedge has a label and a value
      key = wedges.map(function(d) { return String(d[0]); }),
      // Padding is top, right, bottom, left as in css padding.
      p = [10, 50, 15, 15],
      w = 700,
      h = 400,
      // Chart diameter is w or h, (whichever is smaller) - padding.
      radius = Math.min((w - p[1] - p[3]), (h - p[0] - p[2])) / 2,
      // Maximum width and height for the legend minus padding.
      legend = {w: (w - p[3] - p[1] - radius * 2), h: h - p[0] - p[2]},
      color = d3.scale.ordinal().range(['blue', 'red', 'orange', 'green', 'purple', 'lightblue', 'palevioletred', 'orangered', 'mediumpurple', 'pink', 'yellow', 'olive', 'mediumorchid']),
      div = (settings.id) ? settings.id : 'visualization';

    var svg = d3.select('#' + div).append("svg")
      .attr("width", w)
      .attr("height", h)
      .append("g")
      .attr("transform", "translate(" + p[3] + "," + p[0] + ")");

    var graph = svg.append("g")
      .attr("class", "chart")
      .attr('transform', 'translate(' + radius + ',' + radius + ')');

    var arc = d3.svg.arc()
        .outerRadius(radius - 10)
        .innerRadius(0);

    // Background arc that will act as a rollover.
    var arc_effect = d3.svg.arc()
        .outerRadius(radius)
        .innerRadius(radius - 10);

    // Main arc that will be visible at all time.
    var circle = d3.svg.arc()
        .outerRadius(radius - 10)
        .innerRadius(radius - 10);

    var pie = d3.layout.pie()
        .sort(null)
        .value(function(d) { return Number(d[1]); });

    /* MAIN CHART */
    var g = graph.selectAll(".arc")
        .data(pie(wedges))
      .enter().append("g")
        .attr("class", function(d, i) { return "arc arc-" + i; });

    g.append("path")
        .attr("d", arc_effect)
        .attr('fill', '#fff')
        .attr('fill-opacity', 0)
        .attr('class', function(d, i) { return 'arc-' + i + '-over'; });

    g.append("path")
        .attr("d", arc)
        .style("fill", function(d, i) { return color(i); })
        .style('stroke', '#fff')
        .style('stroke-width', 1)
        .on('mouseover', function(d, i) { interact('over', i); })
        .on('mouseout', function(d, i) { interact('out', i); })
        .attr('class', function(d, i) { return 'color_' + color(i) + ' arc-' + i; });

    g.append("text")
        .attr("transform", function(d) { return "translate(" + arc.centroid(d) + ")"; })
        .attr("dy", ".35em")
        .style("text-anchor", "middle")
        .style('fill', 'white')
        .text(function(d, i) { return percent(i); });

    /* LEGEND */
    var legend = svg.append("g")
      .attr("class", "legend")
      .attr("transform", "translate(" + (radius * 2 + p[3]) + "," + p[0] + ")");

    var keys = legend.selectAll("g")
      .data(key)
      .enter().append("g")
      .attr("transform", function(d,i) { return "translate(0," + d3.tileText(d,15) + ")"});

    keys.append("rect")
      .attr("fill", function(d,i) { return d3.rgb(color(i)); })
      .attr("class", function(d,i) {return "color_" + color(i); })
      .attr("width", 16)
      .attr("height", 16)
      .attr("y", 0)
      .attr("x", 0)
      .on('mouseover', function(d, i) { interact('over', i); })
      .on('mouseout', function(d, i) { interact('out', i); });

    var labelWrapper = keys.append("g");

    labelWrapper.selectAll("text")
      .data(function(d,i) { return d3.splitString(key[i], 15); })
      .enter().append("text")
      .text(function(d,i) { return d})
      .attr("x", 20)
      .attr("y", function(d,i) { return i * 20})
      .attr("dy", "1em");

    /**
     * Wrapper function for all rollover functions.
     *
     * @param string text
     *   Current state, 'over', or 'out'.
     * @param int i
     *   Current index of the current data row.
     * @return none
     */
    function interact(state, i) {
      if (state == 'over') {
        showToolTip(i);
        highlightSlice(i);
      }
      else {
        hideToolTip(i);
        unhighlightSlice(i);
      }
      return true;
    }

    /**
     * Displays a tooltip on the centroid of a pie slice.
     *
     * @param int i
     *   Index of the current data row.
     * @return none
     */
    function showToolTip(i) {
      var data = pie(wedges);
      var tooltip = graph.append('g')
        .attr('class', 'tooltip')
        // move to the x position of the parent group
          .append('g')
        // now move to the actual x and y of the bar within that group
        .attr('transform', function(d) { return 'translate(' + circle.centroid(data[i]) + ')'; });

      d3.tooltip(tooltip, Number(wedges[i][1]));
    }

    /**
     * Hides tooltip for a given class. Each slice has a unique class in
     * this chart.
     *
     * @param int i
     *   Index of the current data row.
     * @return none
     */
    function hideToolTip(i) {
      var group = d3.select('g.arc-' + i);

      var bar = d3.selectAll('.color_' + color(i));
      bar.attr('stroke-width', '0')
        .attr('opacity', 1);

      graph.select('g.tooltip').remove();

    }

    /**
     * Changes appearance of group to have an outer border.
     *
     * @param int i
     *   Index of the current data row.
     * @return none
     */
    function highlightSlice(i) {
      d3.selectAll('.arc-' + i + '-over')
        .attr('fill', color(i))
        .attr('fill-opacity', 0.3);
    }

    /**
     * Revert slice back to init state.
     *
     * @param int i
     *   Index of the current data row.
     * @return none
     */
    function unhighlightSlice(i) {
      d3.selectAll('.arc-' + i + '-over')
        .attr('fill', 'white')
        .attr('fill-opacity', 0);
    }

    function percent(i) {
      var sum = d3.sum(wedges.map(function(d,i) { return Number(d[1]); }));
      var val = Number(wedges[i][1]);

      return ((val / sum) ? Math.round((val / sum) * 100) : 0) + '%';
    }
  }

})(jQuery);
