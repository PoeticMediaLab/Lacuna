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
        self.all = self.all.push(original_data);
      }
    });	

    console.log(self.data);
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

	gen_pie_nodes: function () {

	},

	fill_empty_dates: function () {

	},

	manageURLQuery: function () {

	},

	getURLVars: function () {

	},

	findNodeById: function () {

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
	self.duration = {normal: 750};
	self.text_length_scale = d3.scale.threshold()
		.domain([1,51,101])
		.range(['Zero','Short','Medium','Long']);
	

    /*
    * Widths are hard-coded in because
    * they're pretty tricky to determine programmatically, and I
    * thought this way would actually be more maintainable than
    * including a bunch of complex queries.
    */
	self.dashboard_width = 1162; 
    var scale_dashboard = function() {
    	var container = document.querySelector('#annotations_dashboard');
    	var inner_container = container.querySelector('#dashboard');

      	var container_width = container.getBoundingClientRect().width;

		if (container_width < self.dashboard_width) {

			var ratio = container_width / self.dashboard_width;
			inner_container.style.transform = 'scale(' + ratio + ')';

		} else inner_container.style.transform = 'none';
    };

    scale_dashboard();
    window.addEventListener('resize', scale_dashboard);

	
	if (settings.config.size.graph.width) {
		self.size.graph.width = settings.config.size.graph.width;
	}
	if (settings.config.size.graph.height) {
		self.size.graph.height = settings.config.size.graph.height;
	}

}

DashboardView.prototype = {
	tooltip_on: function () {

	},

	tooltip_off: function () {

	},

	focus_on: function () {

	}, 

	focus_toggle: function () {

	},

	draw_edge_weights: function () {

	}, 

	remove_edge_weights: function () {

	},

	brush_clear: function () {

	}, 

	update_graph: function () {

	},

	draw_summary_pie: function () {

	},

	label_pie_charts: function () {

	},

	update_timebrush: function () {

	},

	enableDynamicResizing: function (){

	},

	calculate_height: function () {

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
	// other class variables
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