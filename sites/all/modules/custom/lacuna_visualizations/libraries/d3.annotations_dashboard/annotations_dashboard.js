(function ($) {
"use strict";


/**
 * Dashboard Model
 * Data Management
 **/
function DashboardModel(settings){
	var self = this;
	self.data = Array();
	self.all = Array();
	self.timeFilter = null;

	d3.json(settings.config.data_url, function (error, original_data) { // MODEL
		if (error) {
			self.data = null;
			self.all = null;
			console.error(error);
		} else {
			self.data = self.data.push(original_data);
			self.all = self.all.push(self.data);
		}
    });	

    self.all.forEach(function (a) {
		if (typeof a.text === 'undefined') {
			a.text = "";
		}
		a.text_length = text_length_scale(a.text.length);
		if (!a.category.length || typeof a.category === 'undefined' || a.category == null) {
			a.category = 'Highlight';
		}
	});
}

DashboardModel.prototype = {
	addFilter: function (data) {
		this.data.push(data);
	},

	current: function (ignore_time_filter) {
		if (!ignore_time_filter && this.timeFilter != null) {
			return this.timeFilter;
		}
		return this.data[this.data.length - 1];
	},

	// The first entry should be *all* annotations
	unfiltered: function () {
		return this.all;
	},

	removeFilter: function () {
		return this.data.pop();
	},

	removeAllFilters: function () {
		this.data = new Array();
		this.data.push(this.all);
		this.timeFilter = null;
	},

	init_graph: function () {
		var nodes = Array();
		var edges = Array();
		var nodes_unique = Array();	// tracks unique nodes
		var edges_unique = Array();	// tracks unique edges
		this.current().forEach(function (a) {
			// Add nodes into lookup table and the nodes array
			// The "type" attribute is *very* important
			var source = this.add_to_graph(nodes_unique, nodes, a.username, {type: "user", uid : a.uid});
			var target = this.add_to_graph(nodes_unique, nodes, a.documentTitle, {type: "doc", doc_id : a.doc_id});

			// Add new edges, combine duplicate edges and increment weight & count
			var edge_id = source.id + "," + target.id;
			var edge = {source: source,
						target: target,
						id: edge_id,
						count: 1};
			edge = this.add_to_graph(edges_unique, edges, edge_id, edge);
		});
		return {nodes: nodes, edges: edges};
	}, 

	add_to_graph: function (map, list, key, data) {
		var item = data || {};
		if (typeof key === "undefined" || !key) {
			key = "Unknown";
		}
		if (typeof map[key] === "undefined") {
			item.id = key;
			item.count = 1;
			list.push(item);	// it's just easier to also make the array here
			map[key] = item;
		} else {
			map[key].count++;	// for annotation counts
		}
		return(map[key]);
	},

	gen_pie_nodes: function (attrib) {
		var groups = {};
		// var total_slices = Array();
		// Initialize groups object and reduce into counts
		attrib = attrib.toLowerCase();
		annotations.current().forEach(function (a) {
			if (typeof a[attrib] === "undefined") {
				a[attrib] = pie_defaults[attrib];
			}
			if (typeof a.documentTitle === "undefined") {
				a.documentTitle = a.uri;
			}
			if (typeof groups[a.username] === "undefined") {
				groups[a.username] = {};
			}
			if (typeof groups[a.username][a[attrib]] === "undefined") {
				groups[a.username][a[attrib]] = 0;
			}
			if (typeof groups[a.documentTitle] === "undefined") {
				groups[a.documentTitle] = {};
			}
			if (typeof groups[a.documentTitle][a[attrib]] === "undefined") {
				groups[a.documentTitle][a[attrib]] = 0;
			}
			groups[a.username][a[attrib]]++;
			groups[a.documentTitle][a[attrib]]++;
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
	},

	fill_empty_dates: function () {

	},

	manageURLQuery: function () {
	    var params = this.get_url_vars();
	    var typeMap = { doc_id : "doc", uid : "user" };
	    for (var id in typeMap) {
	        if (params[id] && !isNaN(params[id])) {
	            var node = this.find_node_by_id(params[id], typeMap[id]);
	            if (node) {
	                focus_toggle(node);                             // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	            }
	        }
	    }
	},

	get_url_vars: function () {
		var vars = [], hash;
		var hashes = window.location.href.slice(window.location.href.indexOf('?') + 1).split('&');
		for (var i = 0; i < hashes.length; i++) {
			hash = hashes[i].split('=');
			vars.push(hash[0]);
			vars[hash[0]] = hash[1];
		}
		return vars;
	},

	find_node_by_id: function (id, type) {
	  	var idMap = { user : "uid", doc : "doc_id" };
	  	for (var i = 0; i < graph.nodes.length; ++i) {
	  		if (graph.nodes[i].type == type && graph.nodes[i][idMap[type]] == id) {
	            return graph.nodes[i];
	        }
	  	}
	  	return false;
	},

	update_view_all: function () {

	},

}; // END: DashboardModel



/**
 * Dashboard View
 * Updates DOM
 **/
function DashboardView(model, settings){
	var self = this;
	self.model = model;

	self.size = {
		graph: {
			width: 700,
			height: 5000,
			padding: 50
		},
		summary_pie: {
			padding: 15,
			height: 150,
			width: 600,
			radius: 50
		},
		bar: {
			width: 500,
			height: 250,
			padding: {
				top: 40,
				right: 20,
				bottom: 160,
				left: 30
			},
		},
		legend: {
			height: 150,
			width: 100,
			square: {
				height: 20,
				width: 20,
			},
		},
		node: {	max: .5,
				min: .1 },
		string: { length: 38 },
		radius: 25,
		column: {user: 100, doc: 450}	// X coords for the two columns
	};

	self.colors = {
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

	self.opacity = {focus: .8, normal: .2, hidden: 0};
	self.color_scale = d3.scale.category10();
	self.text_length_scale = d3.scale.threshold()
				.domain([1,51,101])
				.range(['Zero','Short','Medium','Long']);
	
	self.duration = {normal: 750};

	self.node_x = function(d) { return self.size.column[d.type] };
	self.y_coords = {};
	// TODO: change so that y is dynamic based on number of items in column
	// relative to total chart height
	self.node_y = function(d) {
		if (typeof self.y_coords[d.type] === "undefined") {
			self.y_coords[d.type] = {};
		}
		if (typeof self.y_coords[d.type][d.id] === "undefined") {
			var last_y = d3.max(d3.values(self.y_coords[d.type]));
			if (typeof last_y === "undefined") { last_y = 0; }
			// TODO: make size.radius based on the variable scale
			self.y_coords[d.type][d.id] = last_y + self.size.radius * 3;
		}
		return self.y_coords[d.type][d.id];
	}

	if (settings.config.size.graph.width) {
		self.size.graph.width = settings.config.size.graph.width;
	}
	if (settings.config.size.graph.height) {
		self.size.graph.height = settings.config.size.graph.height;
	}

	self.legend = d3.select('#legend')
		.append("svg:svg")
		.attr("id", "legend")
		.attr("height", self.size.legend.height)
		.attr("width", self.size.legend.width);

	self.enable_dynamic_resizing();

	d3.select('.fa-spinner').remove();
}

DashboardView.prototype = {
    // Widths are hard-coded in because
    // they're pretty tricky to determine programmatically, and I
    // thought this way would actually be more maintainable than
    // including a bunch of complex queries.
	enable_dynamic_resizing: function (){
		var dashboard_width = 1162; 
	    var scale_dashboard = function() {
	    	var container = document.querySelector('#annotations_dashboard');
	    	var inner_container = container.querySelector('#dashboard');

	      	var container_width = container.getBoundingClientRect().width;

			if (container_width < dashboard_width) {

				var ratio = container_width / dashboard_width;
				inner_container.style.transform = 'scale(' + ratio + ')';

			} else inner_container.style.transform = 'none';
	    };

	    scale_dashboard();
	    window.addEventListener('resize', scale_dashboard);
	},

	tooltip_on: function () {

	},

	tooltip_off: function () {

	},

	focus_on: function () {

	}, 

	focus_toggle: function () {

	},

	// Add annotation counts on edges
	draw_edge_weights: function () {
		this.remove_edge_weights();
		// Firefox's implementation of getTotalLength() is bugged
		if (navigator.userAgent.toLowerCase().indexOf('firefox') > -1) {
			return;
		}
		d3.selectAll("path.edge").each(function (p) {
				network.append("text")                        // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
				    .attr("x", this.getTotalLength() / 2)
				    .attr("class", "edge_weight")
				.append("textPath")
					.attr("stroke", "black")
					.attr("xlink:href", "#" + p.id)
					.text(p.count)
			});
	}, 

	remove_edge_weights: function () {
		d3.selectAll("text.edge_weight").remove();
	},

	brush_clear: function () {
		d3.select("a.dashboard-button#reset_brush").style("visibility", "hidden");
		d3.selectAll("rect.extent").remove();
		d3.selectAll("g.resize").remove();
		brush.clear();							// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		annotations.timeFilter = null;
	}, 

	update_graph: function () {

	},

	draw_summary_pie: function () {

	},

	label_pie_charts: function () {

	},

	update_timebrush: function () {

	},

	update_legend: function() {
		var item = self.legend.selectAll("g.legend_item")
			.data(pie_data_aggregate[pie_current]);  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

		item.exit().remove();
		item.selectAll("text").remove();
		item.enter()
			.append("g")
			.attr("class", "legend_item")
			.attr("transform", function(d, i) { return "translate(0," + i * (self.size.legend.square.height + 2) + ")"; })
			.append("rect")
			.attr("x", 0)
			.attr("width", self.size.legend.square.width)
			.attr("height", self.size.legend.square.height)
			.style("fill", function(d,i) { return color_scale(i) });

		item.append("text")
			.attr("x", self.size.legend.square.width + 10)
			.attr("y", self.size.legend.square.height / 2)
			.attr("dy", ".35em")
			.style("text-anchor", "start")
			.text(function(d) { return d.key; });
	},

	// calcualte height of the network graph based on nodes number and node radius
	calculate_height: function (graph) {
	 	if(!(graph && graph.nodes && size && this.size.radius))	return 0;
	  	var counts = {user : 0, doc : 0};
	  	graph.nodes.forEach(function(node){		counts[node.type]++;	});
	  	return 3 * this.size.radius * (1 + Math.max(counts.user, counts.doc));			//adding 1 for padding
	},

}; // END: DashboardView


/**
 * Dashboard Controller
 * Handles user interactions
 * Communications between Model and View
 **/
function DashboardController(model, view){
	var self = this;
	self.model = model;
    self.view = view;

    function update() {                      // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	  	update_view_all();
	  	update_graph();
	  	update_timebrush();
	  	update_summary_pies();
	  	update_legend();
  	}

	// Remove time filter
	$('a.dashboard-button#reset_brush').click(function() { 
		self.view.brush_clear();
   		update();                          // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		if (focused_on != null) {
			self.view.draw_edge_weights();
		}
	});

	function reset_all() { 
		self.view.remove_edge_weights();
		self.view.brush_clear();
		focused_on = null;
		self.model.removeAllFilters();
		update();                       // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	}

	// Remove all filters
	$('a.dashboard-button#reset_all').click(function() { 
		reset_all();
	});

	// "View Annotations" button clicked; update data table
	// We only update when this button is clicked because it's too slow to update all the time
	//$('a.dashboard-button#view_annotations').click(update_annotations_table);

	$('a.dashboard-button#return_to_vis').click(function() { 
		// annotations_table.destroy();
	    d3.select("#annotations_table_draw_wrapper").style("visibility", "hidden"); // functions in VIEW
	    d3.select("#annotations_table_draw").style("visibility", "hidden");
	    d3.selectAll("a#return_to_vis").style("visibility", "hidden");
	})
}

DashboardController.prototype = {
	
}; // END: DashboardController


Drupal.d3.annotations_dashboard = function (select, settings) {
	var model = new DashboardModel(settings);
	var view = new DashboardView(model, settings);
	var controller = new DashboardController(model, view);

	console.log('yayy');
};
})(jQuery);