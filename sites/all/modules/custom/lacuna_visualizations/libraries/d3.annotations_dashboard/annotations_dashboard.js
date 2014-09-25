/*
 * Creates a network graph of annotations
 * Lays out users and documents in two columns, sorted by count
 * Each node is a pie chart based on the type of chart the user selects
 * Also provides a time brush for filtering by date
 * and pie chart summaries to select what kind of node pies to display
 *
 * Understanding some of the code requires knowledge of the Annotator data structure
 *
 * NB: "annotations" is a global variable set in global.js and contains all
 * initial annotations data
 *
 * Also: this entire script needs to be refactored to use dispatches
 * As is, the logic is pretty convoluted and fragile; too many updates need to be called
 *
 * Mike Widner <mikewidner@stanford.edu>
 *
 * Special thanks to Elijah Meeks for advice and a few lines of code
 */

(function ($) {  // Namespace wrapper for Drupal
Drupal.d3.annotations_dashboard = function (select, settings) {
"use strict";

console.log(settings, 'settings');
d3.json(settings.config.data_url, function (error, data) {
    if (error) {
        console.error(error);
    } else {
        main(data);
    }
});
/***************
 *
 * An object to manage the annotation filter stack
 * all functions assume they can access this
 * TODO: refactor to use Object.create and prototypes
 *
 **************/
function Annotations(data) {
	this.data = new Array();
	this.data.push(data);
	this.all = data;
	this.timeFilter = null;	// because time filters are unique

	this.addFilter = function (data) {
		this.data.push(data);
	};

	this.current = function (ignore_time_filter) {
		if (!ignore_time_filter && this.timeFilter != null) {
			return this.timeFilter;
		}
		return this.data[this.data.length - 1];
	};

	// The first entry should be *all* annotations
	this.unfiltered = function () {
		return this.all;
	}

	this.removeFilter = function () {
		return this.data.pop();
	};

	this.removeAllFilters = function () {
		this.data = new Array();
		this.data.push(this.all);
		this.timeFilter = null;
	}
}

/****************
 *
 * Global variables (I know, I know; it's all javascript's fault!)
 *
 ****************/

var annotations;
// Fields in the annotations from which we'll create pie charts
// All are added by pre-processing, not native to Annotator data structure
var pie_types = ['category', 'text_length', 'privacy'];
var pie_labels = {'category': 'Categories', 'text_length': 'Length of Annotation', 'privacy': 'Sharing'};	// yeah, yeah; see? it's already ugly code
var pie_current = pie_types[0]; // Set the current pie-type selection
// Default values if attribute missing from annotation data
var pie_defaults = {'category': 'Highlight', 'length': 'Zero', 'privacy': 'Private'};
var pie_slices = {};
pie_types.forEach(function(pie_type) {
	pie_slices[pie_type] = Array();
})

/***************
 *
 * BEGIN data management section
 * manipulates internal data representations of annotations
 * other state information
 *
 ****************/
// Add both edges and nodes to the graph array
function add_to_graph(map, list, key, data) {
	var item = data || {};
	if (typeof map[key] === "undefined") {
		item.id = key;
		item.count = 1;
		list.push(item);	// it's just easier to also make the array here
		map[key] = item;
	} else {
		map[key].count++;	// for annotation counts
	}
	return(map[key]);
}

// Initialize the graph; returns arrays with nodes and edges
function init_graph() {
	var nodes = Array();
	var edges = Array();
	var nodes_unique = Array();	// tracks unique nodes
	var edges_unique = Array();	// tracks unique edges
	annotations.current().forEach(function (a) {
		// if (typeof a.title === "undefined") {
		// 	title = a.uri.replace("http://annotate.lacunastories.com/documents/","");
		// } else {
		// 	title = a.title
		// }
		var title = a.docTitle;
		// Add nodes into lookup table and the nodes array
		// The "type" attribute is *very* important
		var source = add_to_graph(nodes_unique, nodes, a.username, {type: "user"});
		var target = add_to_graph(nodes_unique, nodes, title, {type: "doc"});

		// Add new edges, combine duplicate edges and increment weight & count
		var edge_id = source.id + "," + target.id;
		var edge = {source: source,
					target: target,
					id: edge_id,
					count: 1};
		edge = add_to_graph(edges_unique, edges, edge_id, edge);
	});
	return {nodes: nodes, edges: edges};
}

// Generate data for pie chart nodes (not summary pie charts)
function gen_pie_nodes(attrib) {
	var groups = {};
	// var total_slices = Array();
	// Initialize groups object and reduce into counts
	attrib = attrib.toLowerCase();
	annotations.current().forEach(function (a) {
		if (typeof a[attrib] === "undefined") {
			a[attrib] = pie_defaults[attrib];
		}
		if (typeof a.title === "undefined") {
			a.title = a.uri;
		}
		if (typeof groups[a.username] === "undefined") {
			groups[a.username] = {};
		}
		if (typeof groups[a.username][a[attrib]] === "undefined") {
			groups[a.username][a[attrib]] = 0;
		}
		if (typeof groups[a.title] === "undefined") {
			groups[a.title] = {};
		}
		if (typeof groups[a.title][a[attrib]] === "undefined") {
			groups[a.title][a[attrib]] = 0;
		}
		groups[a.username][a[attrib]]++;
		groups[a.title][a[attrib]]++;
		// Find the total number of slices for later fill of zero values
		if (pie_slices[attrib].indexOf(a[attrib]) == -1) {
			pie_slices[attrib].push(a[attrib]);
		}
	});
	// Transform counts into format that works for pie charts
	var data = Array();
	for (var key in groups) {
		for (var cat in groups[key]) {
			if (typeof data[key] === "undefined") {
				data[key] = Array();
			}
			data[key].push({value: groups[key][cat], key: cat});
		}
		// zero-fill missing slices
		// BUG: this doesn't work on smaller selections
		// init once with full data, compare against that
		pie_slices[attrib].forEach(function (slice) {
			if (typeof groups[key][slice] === "undefined") {
				data[key].push({value: 0, key: slice});
			}
		});
		// Sort the array by key names so pie colors are consistent
		data[key].sort(function (a,b) {
			if (a.key < b.key) { return -1; }
			else if (a.key > b.key ) { return 1;}
			return 0;
		});
	}
    return(data);
}

/****************
 *
 * END data manipulation
 *
 ****************/

// Does the actual d3 work to draw the graph
function main(data) {
	/*
	 *
	 * Definitions of variables and helper functions for the graph
	 *
	 */
	annotations = new Annotations(data);
	// Define all our attributes
	// TODO: override these with settings from module
	var size = {
				graph: {
					width: 700,
					height: 5000,
					padding: 50
				},
				summary_pie: {
					padding: 15,
					height: 200,
					width: 600,
					radius: 50
				},
				bar: {
					width: 550,
					height: 250,
					padding: {
						top: 40,
						right: 20,
						bottom: 160,
						left: 20
					},
				},
				node: {	max: .5,
						min: .1 },
				string: {length: 40},
				radius: 25,
				column: {user: 100, doc: 400}	// X coords for the two columns
				};
	// TODO: loop through settings; overwrite matching variables
	for (var key in settings) {
		// console.log(key, 'settings key');
	}
	if (settings.config.size.graph.width) {
		size.graph.width = settings.config.size.graph.width;
	}
	if (settings.config.size.graph.height) {
		size.graph.height = settings.config.size.graph.height;
	}
	var colors = {
				user: "steelblue",
				doc: "yellowgreen",
				active: "crimson",
				inactive: "gray",
				link: {
					active: "steelblue",
					inactive: "gray",
					focus: "red"
					}
				};
	var opacity = {focus: .8, normal: .2, hidden: 0};
	var color_scale = d3.scale.category10();
	var duration = {normal: 750};

	// Functions to calculate x and y values for layout
	var node_x = function(d) { return size.column[d.type] };
	var y_coords = {};
	// TODO: change so that y is dynamic based on number of items in column
	// relative to total chart height
	var node_y = function(d) {
		if (typeof y_coords[d.type] === "undefined") {
			y_coords[d.type] = {};
		}
		if (typeof y_coords[d.type][d.id] === "undefined") {
			var last_y = d3.max(d3.values(y_coords[d.type]));
			if (typeof last_y === "undefined") { last_y = 0; }
			// TODO: make size.radius based on the variable scale
			y_coords[d.type][d.id] = last_y + size.radius * 3;
		}
		return y_coords[d.type][d.id];
	}

	// Initialize data for the charts
	// var graph = init_graph(annotations);
	var graph = [];
	var pie_node_data = [];

	/*
	 * Mouse event functions
	 */
	// Fade in tool tips with detailed numbers
	function tooltip_on(d) {
		// fade in our tooltips
		tooltips.transition()
			.duration(200)
			.style("opacity", 1)
			;
		var type = this.getAttribute("class");
		var text = "<h3>";
		if (type == "node" || type == "pie_total") {
			var total;
			var data;
			if (type == "node") {
				total = d.count;
				data = pie_node_data[d.id];
				text += total + " annotation";
				if (total > 1) {
					text += "s";
				}
			} else if (type == "pie_total") {
				var total = 0;
				// crazy fragile; depends on div ids in DOM
				var pie_type = this.parentNode.getAttribute("id");
				for (var key in pie_data_aggregate[pie_type]) {
					total += pie_data_aggregate[pie_type][key].value;
				}
				var title = pie_labels[pie_type];
				data = pie_data_aggregate[pie_type];
				text += title + "</h3>";
			}
			text += "</h3>";
			text += "<table>";
			data.forEach(function (p,i) {
				text += "<tr style='color:" + color_scale(i);
				text += "'><td>";
				text += p.key + "</td><td class='value'>" + p.value + "</td></tr>";
			});
			text += "</table>";
		} else if (type == "edge") {
			text = d.count + " annotation";
			if (d.count > 1) {
				text += "s";
			}
		}

		tooltips.html(text)
			.style("left", (d3.event.pageX + 15) + "px")
			.style("top", (d3.event.pageY + 15) + "px")
			;
	}

	// fade out tooltips
	function tooltip_off() {
		tooltips.transition()
			.duration(500)
			.style("opacity", opacity.hidden)
			;
	}

	// Click focus on a node
	// Highlights the ego network for a selected node
	// Shows numbers on edges
	function focus_on(node) {
		// filter our annotations to include only the active ones
		// documents are always targets, users are always sources
		tooltip_off();
		var filter = Array();
		reset_all();	// HACK: doesn't work with time filters, so reset
		annotations.unfiltered().forEach(function (a) {
			graph.edges.forEach(function (edge) {
				if ((node.id == edge.source.id && node.id == a.username) ||
					(node.id == edge.target.id && node.id == a.title))
				{
					if (filter.indexOf(a) == -1) {
						filter.push(a);
					}
				}
			});
		});
		annotations.addFilter(filter);
		// Ego network removes time filter
		// d3.select("a.button#reset_brush").style("visibility", "hidden");
		update();
		draw_edge_weights();
	}

	var focused_on = null;
	function focus_toggle(d) {
		if (focused_on != this) {
			focus_on(d);
			focused_on = this;
			window.scrollTo(0,0);
		}
	}

	// Add annotation counts on edges
	function draw_edge_weights() {
		remove_edge_weights();
		// Firefox's implementation of getTotalLength() is bugged
		if (navigator.userAgent.toLowerCase().indexOf('firefox') > -1) {
			return;
		}
		d3.selectAll("path.edge").each(function (p) {
				network.append("text")
				    .attr("x", this.getTotalLength() / 2)
				    .attr("class", "edge_weight")
				.append("textPath")
					.attr("stroke", "black")
					.attr("xlink:href", "#" + p.id)
					.text(p.count)
			});
	}

	function remove_edge_weights() {
		d3.selectAll("text.edge_weight").remove();
	}

	function brush_clear() {
		d3.select("a.button#reset_brush").style("visibility", "hidden");
		d3.selectAll("rect.extent").remove();
		d3.selectAll("g.resize").remove();
		brush.clear();
		annotations.timeFilter = null;
	}

	// Remove time filter
	$('a.button#reset_brush').click(function() {
		brush_clear();
   		update();
		if (focused_on != null) {
			draw_edge_weights();
		}
	});

	function reset_all() {
		remove_edge_weights();
		brush_clear();
		focused_on = null;
		annotations.removeAllFilters();
		update();
	}

	// Remove all filters
	$('a.button#reset_all').click(function() {
		reset_all();
	});

	// "View Annotations" button clicked; update data table
	// We only update when this button is clicked because it's too slow to update all the time
	$('a.button#view_annotations').click(update_annotations_table);

	$('a.button#return_to_vis').click(function() {
		// annotations_table.destroy();
	    d3.select("#annotations_table_draw_wrapper").style("visibility", "hidden");
	    d3.select("#annotations_table_draw").style("visibility", "hidden");
	    d3.selectAll("a#return_to_vis").style("visibility", "hidden");
	})

	// Show help text
	// $('img.help').click(function() {
	d3.selectAll('img.help')
		.on("mouseover", function() {
			d3.select(this.parentNode)
				.select('div.help_text')
				.style("visibility", "visible")
				.style("position", "absolute"
)				.style("left", (d3.event.pageX + 55) + "px")
				.style("top", d3.event.pageY + "px")
			;
		})
		.on("mouseout", function() {
			d3.select(this.parentNode)
				.select('div.help_text')
				.style("visibility", "hidden")
			;
		});


	/***
	 *
	 * BEGIN Network graph
	 *
	 ***/


	d3.select("div#network")
		.append("p")
		.text("Students")
		.style("font-size", "18pt")
		.style("font-weight", "bold")
		.style("padding-left", size.column.user - size.graph.padding)
		.append("p")
		.text("Resources")
		// .style("left", size.column.doc)
		.style("font-size", "18pt")
		.style("font-weight", "bold")
		.style("padding-left", size.column.user + (size.graph.padding * 2))
		.style("display", "inline")
		;

	var network = d3.select("div#network")
		.append("svg:svg")
		.attr("id", "network")
		.attr("width", size.graph.width)
		.attr("height", size.graph.height)
	  	;

  	// Divs for tooltips that show annotation counts, et al.
	var tooltips = d3.select("body").append("div")
			.attr("class", "tooltip")
			.style("opacity", opacity.hidden)
			;

	// pie is re-used for the summary pies
	var pie = d3.layout.pie().value(function (d) { return d.value; });
	// arc is only for the network graphs, because outerRadius changes
	var arc = d3.svg.arc().outerRadius(size.radius).innerRadius(0);

	// Create and update graph
	// TODO: change x/y positions and radii to be variable by number of items
	// TODO: Fix update so that paths are always drawn first
	function update_graph() {
		graph = init_graph();
		pie_node_data = gen_pie_nodes(pie_current);
		y_coords = {};	// clear our positions, if set
		var edges = network.selectAll("path.edge").data(graph.edges);
		edges.exit().remove();
		edges.enter()
			.append("svg:path")
			.attr("class", "edge")
			.style("stroke", colors.link.active)
			.style("stroke-opacity", opacity.normal)
			.style("fill", "none")
			.on("mouseover", tooltip_on)
			.on("mouseout", tooltip_off)
			;

		// update edges
		var edge_scale = d3.scale.linear().range([.01,.2]);
		edges.attr("id", function(d) { return d.id; })
			.style("stroke-width", function(d) { return edge_scale(d.count); })
			;

		var nodes = network.selectAll("g").data(graph.nodes);
	  	nodes.exit().remove();
		nodes.enter()
			.append("g", function(d) { return d.uid; })	// d.uid is set in Annotation Studio
			.attr("class","node")
			.on("mouseover", tooltip_on)
			.on("mouseout", tooltip_off)
			.on("click", focus_toggle)
			;

		nodes.sort(function (a,b) {
				if (a.count < b.count) { return 1; }
				else if (a.count > b.count) { return -1; }
				return 0;
			})
			.each(function (d) { d.x = node_x(d); d.y = node_y(d); })
			.attr("transform", function (d) {
					return "translate(" + d.x + "," + d.y + ")";})
			;

		// // Must draw *after* setting nodes' x/y, but must define first for z
		edges.attr("d", d3.svg.diagonal());

		// Draw nodes
		var pies = nodes.selectAll("path")
			.data(function (d) {
				if (typeof pie_node_data[d.id] === "undefined") {
					return pie(Array());
				} else {
					return pie(pie_node_data[d.id])
				}});
		pies.exit().remove();
	    pies.enter()
			.append("svg:path")
			.attr("class", "node_pie")
			;

		pies.attr("d", arc)
	  		.style("fill", function(d, i) { return color_scale(i); })
	  		;

	  	// Add node labels
	  	nodes.selectAll("text.node_label").remove();
	  	var labels = nodes.append("text")
	  		.attr("class", "node_label")
			.text(function(d) { return d.id.substring(0, size.string.length); });

	} // end update_graph()

    // fill empty days with zeros
	function fill_empty_dates (data) {
		var d = [];
		var lastDate = false;
		data.forEach(function(el, i) {
		  if (lastDate) {
			var dateRange = d3.time.day.range(lastDate, parseDate(el.key));
		    // Skip the first array item; it equals lastDate
		    for (var i = 1; i < dateRange.length; ++i) {
			      d.push({x: timeFormat(dateRange[i]), y: 0});
		    }
		  }
		  d.push({x: el.key, y: el.value})
		  lastDate = parseDate(el.key);
		});
		return d;
	};

	/**************
	 *
	 * END network graph
	 *
	 **************/

	/**************
	 *
	 * BEGIN side bar pie chart summary section
	 *
	 **************/

	// Change the type of pie chart to display
	// TODO: bring selected pie type to the top; dim the others
	function select_pie(d) {
		var parent = this.parentNode;
		var pid = parent.getAttribute("id");
		if (pie_current != pid) {
			pie_current = pid;
			update_graph();
			update_summary_pies();
			// window.scrollTo(0,400);
		}
	};

	var pie_choices = d3.select("div#pie_types").append("svg:svg")
		.attr("id", "pie_choices")
		.attr("height", size.summary_pie.height)
		.attr("width", size.summary_pie.width + size.summary_pie.padding * 2);

	var pie_data_aggregate = Array();	// Used for pop-up details
	var pie_slice_keys = Array();
	// Create g element for each summary pie
	var pie_g = pie_choices.selectAll("g.pie")
					.data(pie_types)
					.enter()
					.append("g")
					.attr("id", function (d) { return d; })
					.attr("class", "pie")
					;

	// Draw one summary pie chart
	function draw_summary_pie(pie_type, x) {
		var arc = d3.svg.arc()
			.outerRadius(size.summary_pie.radius)
			.innerRadius(0);

		var my_pie = d3.select('g#' + pie_type).selectAll("path")
						.data(pie(pie_data_aggregate[pie_type]));
	    my_pie.enter()
			.append("svg:path")
			.attr("class", "pie_total")
			.attr("transform", function (d) {
				var str = "translate(";
				var pie_x = size.summary_pie.radius * 2 * x + 55;
				pie_x += size.summary_pie.padding * (x + 1) * 2;
				str += pie_x + "," + size.summary_pie.radius + ")";
				 // + radius * x * 2 + ",50)";
				// var pad = radius * x * 2 + radius;
				// 	// if (x > 0) {
				// 		pad += x * size.summary_pie.padding;
				// 	// }
				// str += pad + ")";
				return str;
				})
			.on("mouseover", tooltip_on)
			.on("mouseout", tooltip_off)
			.on("click", select_pie)
			.text(pie_type);
			;

		my_pie.attr("d", arc)
	  		.style("fill", function(d, i) { return color_scale(i); })
			.style("opacity", 1)
	  		;

	  	if (pie_type !== pie_current) {
	  		var color = my_pie.style("fill");
	  		my_pie.style("fill", function (d,i) {
	  			return d3.rgb(color_scale(i)).darker();
	  		})
	  			.style("opacity", .5);
	  	}
	}

	// Loops through the different pie types for the side bar summary view
	function update_summary_pies() {
		var x = 0;	// to keep track of order; drawing doesn't know how many it has done
		pie_data_aggregate = Array();	// reset data counts
		pie_types.forEach(function(pie_type) {
			var count = count_pie_data(pie_type);
			for (var key in count) {
 				if (typeof pie_data_aggregate[pie_type] === "undefined") {
					pie_data_aggregate[pie_type] = Array();
				}
				pie_data_aggregate[pie_type].push({key: key, value: count[key]});
			}
			// TODO: add in zero-fill of data
			// Must sort to keep colors consistent
			// TODO: refactor into a single sort function called by all pies
			pie_data_aggregate[pie_type].sort(function (a,b) {
				if (a.key < b.key) { return -1; }
				else if (a.key > b.key ) { return 1;}
				return 0;
			});
			draw_summary_pie(pie_type, x);
			++x;
		});
	}

	var pie_slice_keys = Array();
	function count_pie_data(pie_type) {
		var count = Array();
		if (typeof pie_slice_keys[pie_type] === "undefined") {
			pie_slice_keys[pie_type] = Array();	// don't clobber; set once then leave alone
		}
		// Relies on fields in annotation data that match pie types
		// Those fields are added in pre-processing
		annotations.current().forEach(function (a) {
			if (typeof count[a[pie_type]] === "undefined") {
				count[a[pie_type]] = 0;
				pie_slice_keys[pie_type].push(a[pie_type]);
			}
			++count[a[pie_type]];
		});
		// zero-fill missing keys
		pie_slice_keys[pie_type].forEach(function (key) {
			if (typeof count[key] === "undefined") {
				count[key] = 0;
			}
		});
		return(count);
	}

	/**************
	 *
	 * END: summary pie charts
	 *
	 **************/

	/**************
	 *
	 * BEGIN: Time-based bar chart and brush section
	 *
	 **************/

	// Create bar chart of historical data
	// Used as a time brush to filter annotations
	// TODO: grid lines like nvd3
	// TODO: convert into stacked bars based on current pie type
	// TODO: Add day of week pop-ups?
	var timeFormat = d3.time.format("%y-%m-%d");
	var parseDate = timeFormat.parse;
	var bar_x = null;	// scoped here because we don't want to reset it on updates
	var xAxis = null;
	var bar_chart = null;
	var brush = null;
	function update_timebrush() {
		// TODO: refactor to global variables, relative to one another for
		// more dynamic layout
		// var margin = {top: 20, right: 20, bottom: 80, left: 20},
		// 	width = size.bar.width - size.bar.padding.left - size.bar.padding.right,
		// 	height = size.bar.height - size.bar.padding.top - size.bar.padding.bottom;
		var cf = crossfilter(annotations.current());
		var dim = cf.dimension(function(d) {
			// time stored as Unix epoch time
			return timeFormat(new Date(d.created["$date"]));
		});
		var g = dim.group();
		var data = fill_empty_dates(g.all());

		if (bar_chart === null) {
			bar_chart = d3.select("div#time_brush").append("svg")
			    .attr("width", size.bar.width + size.bar.padding.left + size.bar.padding.right)
			    .attr("height", size.bar.height + size.bar.padding.top + size.bar.padding.bottom);
		}
		// Create x-axis, but only once
		if (bar_x === null) {
			bar_x = d3.scale.ordinal()
				.domain(data.map(function (d) { return d.x; }))
		    	.rangeRoundBands([20, size.bar.width - size.bar.padding.right - size.bar.padding.left], .1);

			xAxis = d3.svg.axis()
			    .scale(bar_x)
			    .orient("bottom")
			    // Only display every other label
			    .tickValues(data.map(function (d,i) {
			    	if (i % 7 === 0) { return d.x}
			    }))
			;

    		bar_chart.append("g")
				.attr("class", "x axis")
				.attr("transform", "translate(0," + size.bar.height + ")")
				// .transition()
				// .duration(duration.normal)
				.call(xAxis)
				.selectAll("text")
				.style("text-anchor", "end")
				.attr("transform", "rotate(-65)");
	    }

	    var bar_width = bar_x.rangeBand() - 1;

		var bar_y = d3.scale.linear()
			.domain([0, d3.max(data, function (d) { return d.y; })])
		    .range([size.bar.height, size.bar.padding.top]);

		var yAxis = d3.svg.axis()
		    .scale(bar_y)
		    .orient("right")
		    .tickFormat(d3.format("2i"))
		    .ticks(7)
		    // .attr("transform", "translate(-10,0)")
		    ;

		bar_chart.select("g.yAxis").remove();
		bar_chart.append("g")
			.attr("class", "yAxis axis")
			.attr("transform", "translate(" + size.bar.padding.left + ",0)")
			.call(yAxis)
			;

	    var bars = bar_chart.selectAll("rect.bar").data(data);

  		bars.enter()
			.append("rect")
      		.attr("fill", "steelblue")
      		.attr("class", "bar")
    	;

	    bars.exit().remove();

      	bars.attr("width", bar_width)
      		.attr("y", function (d) { return bar_y(d.y) })
      		.attr("x", function (d) { return bar_x(d.x) })
      		.attr("height", function (d) { return size.bar.height - bar_y(d.y) })
      		;

      	var bar_labels = bar_chart.selectAll("text.bar_label").data(data);
      	bar_labels.exit().remove();
      	bar_labels.enter()
      		.append("text")
      		.attr("class", "bar_label")
      		.attr("fill", "black")
      		.attr("font-size", bar_width / 2 )
      		.attr("text-anchor", "middle")
      		.style("transform", "rotate(-90)")
      	;

		// Add the brush for filtering by time
		brush = d3.svg.brush()
			.on("brush", brushed)
			.on("brushend", brushed)
			.x(bar_x);

		var handle = d3.svg.arc()
			.outerRadius(size.bar.height / 3)
			.startAngle(0)
			.endAngle(function (d,i) { return i ? -Math.PI : Math.PI; });

	    var brushg = bar_chart
	        .append("g")
      		.attr("class", "brush")
      		.call(brush);

		brushg.selectAll("rect")
      		.attr("y", -6)
	    	.attr("height", size.bar.height + 7);

	    function brushed() {
	    	d3.select("a.button#reset_brush").style("visibility", "visible");
	    	var extent = brush.extent();
	    	var start = extent[0];
	    	var end = extent[1];
	    	var bar_width = bar_x.rangeBand() - 1;
	    	var dates = Array();
	    	d3.selectAll("rect.bar").each(function (d) {
	    		var x = bar_x(d.x);
	    		if ((x + bar_width) >= start && x <= end) {
	    			dates.push(d.x);
		    	}
	    	});
	    	// Filter our annotations by selected dates
	    	var filter = Array();
	    	annotations.current(true).forEach(function (a) {
	    		var date = timeFormat(new Date(a.created["$date"]));
	    		if (dates.indexOf(date) != -1 && filter.indexOf(a) == -1) {
	    			filter.push(a);
	    		}
	    	});
	    	annotations.timeFilter = filter;

	    	// Update the other parts of the display
	    	// Call these updates here because we don't want to update the bar chart, too
	    	update_graph();
	    	update_summary_pies();
	    	update_total();
	    	// Are we focused on a node? If so, update the edge labels
	    	if (focused_on !== null) {
		    	draw_edge_weights();
		    }
	    }
	}
	/*************
	 *
	 * END: bar chart
	 *
	 *************/

	 // Show all annotations in current selection
	var annotations_table;
	function update_annotations_table() {
		if (typeof annotations_table === "object") {
			annotations_table.destroy();
		}
		annotations_table = $('#annotations_table_draw').DataTable({
	    	"processing": true,
	    	"dom": 'T<"clear">lfrtip',
	    	"tableTools": {
            	"sSwfPath": "lib/js/DataTables/extras/TableTools/media/swf/copy_csv_xls_pdf.swf"
        	},
	        "data": annotations.current(),
	        "order": [[7, "asc"]],
	        "columns": [
		        { "data": "username"},
		        { "data": "category"},
		        { "data": "title"},
		        { "data": "text"},
		        { "data": "quote"},
		        { "data": "tags"},
		        { "data": "privacy"},
		        { "data": "created.$date",
		    	  "render": function (data, type, full, meta) {
		    	  	var d = new Date(data);
		    	  	return d.toDateString();
		    	  }}
	           ]
	    });
	    d3.select("#annotations_table_draw").style("visibility", "visible");
	    d3.select("#annotations_table_draw_wrapper").style("visibility", "visible");
	    d3.selectAll("a#return_to_vis").style("visibility", "visible");
	}

	function update_total() {
    	var total = $('a#view_annotations');
    	total.empty();
    	// var str = "<h2>";
    	var str = "View "
		str += annotations.current().length + " annotation";
    	if (annotations.current().length != 1) {
    		str += "s";
    	}
    	// str += "</h2>";
    	total.text(str);
	}

    // update all graphs with the most recent filter
    function update() {
    	update_total();
    	update_graph();
    	update_timebrush();
    	update_summary_pies();
    }

	// Initial creation
	update();
} // end main()
} // Drupal.d3.annotations
})(jQuery);	// End of Drupal wrapper
