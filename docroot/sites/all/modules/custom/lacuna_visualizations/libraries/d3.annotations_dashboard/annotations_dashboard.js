(function ($) {
"use strict";

/**
 * Dashboard Model
 * Data Management
 **/
function DashboardModel(annotations){
	var self = this;

	self.annotations = Array.from(annotations);
	self.all_annotations = Array.from(annotations);

	console.log("Annotations: ", self.annotations);
	
	// self.annotations = Array();
	// self.annotations.push(annotations);
	// self.all_annotations = Array();
	// self.all_annotations.push(annotations);

	self.timeFilter = null;

	self.text_length_scale = d3.scale.threshold()
				.domain([1,51,101])
				.range(['Zero','Short','Medium','Long']);

	self.all_annotations.forEach(function (a) {
		if (typeof a.text === 'undefined') {
			a.text = "";
		}
		a.text_length = self.text_length_scale(a.text.length);
		if (!a.category.length || typeof a.category === 'undefined' || a.category == null) {
			a.category = 'Highlight';
		}
	});

	self.pie_labels = {'category': 'Category', 'text_length': 'Length', 'audience': 'Sharing', 'annotation_tags': 'Tags'};	// yeah, yeah; see? it's already ugly code
	self.pie_defaults = {'category': 'Highlight', 'length': 'Zero', 'audience': 'Everyone', 'annotation_tags': 'None'}; //no value given, give these

	self.pie_types = ['category', 'text_length', 'audience'];
	self.pie_current = self.pie_types[0]; // Set the current pie-type selection
	console.log("pie_types: ", self.pie_types);
	
	self.pie_slices = {};
	self.pie_types.forEach(function(pie_type) {
		self.pie_slices[pie_type] = Array();
	});

	self.pie_slice_keys = Array();
	self.pie_data_aggregate = Array();	// Used for pop-up details
		
	self.graph = [];
	self.pie_node_data = [];

	self.focused_on = null;

	self.timeFormat = d3.time.format("%y-%m-%d");
	self.parseDate = self.timeFormat.parse;
}

DashboardModel.prototype = {

	addFilter: function (data) {
		this.annotations.push(data);
	},

	current: function (ignore_time_filter) {
		console.log('ignore_time_filter: ', ignore_time_filter); //GOAL: show true
		
		if (!ignore_time_filter && this.timeFilter !== null) {
			console.log('current return1:', this.timeFilter);
			return this.timeFilter;
		}

		console.log('current return2: ', this.annotations[this.annotations.length - 1]);
		return new Array(this.annotations[this.annotations.length - 1]);
	},

	// The first entry should be *all* annotations
	unfiltered: function () {
		return this.all_annotations;
	},

	removeFilter: function () {
		return this.annotations.pop();
	},

	removeAllFilters: function () {
		this.annotations = new Array();
		this.annotations.push(this.all_annotations);
		this.timeFilter = null;
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

	init_graph: function () {
		var nodes = Array();
		var edges = Array();
		var nodes_unique = Array();	// tracks unique nodes
		var edges_unique = Array();	// tracks unique edges
		var proto = this;
		this.current().forEach(function (a) {
			// Add nodes into lookup table and the nodes array
			// The "type" attribute is *very* important
			var source = proto.add_to_graph(nodes_unique, nodes, a.username, {type: "user", uid : a.uid});
			var target = proto.add_to_graph(nodes_unique, nodes, a.documentTitle, {type: "doc", doc_id : a.doc_id});

			// Add new edges, combine duplicate edges and increment weight & count
			var edge_id = source.id + "," + target.id;
			var edge = {source: source,
						target: target,
						id: edge_id,
						count: 1};
			edge = proto.add_to_graph(edges_unique, edges, edge_id, edge);
		});
		return {nodes: nodes, edges: edges};
	}, 

	gen_pie_nodes: function (attrib) {
		var groups = {};
		// var total_slices = Array();
		// Initialize groups object and reduce into counts
		attrib = attrib.toLowerCase();
		var proto = this;
		proto.current(true).forEach(function (a) {
			if (typeof a[attrib] === "undefined") {
				a[attrib] = proto.pie_defaults.category;
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
			if (proto.pie_slices[attrib].indexOf(a[attrib]) == -1) {
				proto.pie_slices[attrib].push(a[attrib]);
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
			this.pie_slices[attrib].forEach(function (slice) {
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

	fill_empty_dates: function (data) {
		var d = [];
		var lastDate = false;
		var proto = this;
		data.forEach(function(el, i) {
		  if (lastDate) {
			var dateRange = d3.time.day.range(lastDate, proto.parseDate(el.key));
		    // Skip the first array item; it equals lastDate
		    for (var i = 1; i < dateRange.length; ++i) {
			      d.push({x: proto.timeFormat(dateRange[i]), y: 0});
		    }
		  }
		  d.push({x: el.key, y: el.value});
		  lastDate = proto.parseDate(el.key);
		});
		console.log("array being pushed to x-axis ticks: ", d);
		return d;
	},

	focus_toggle: function (d) {
		if (this.focused_on != d) {
			this.focus_on(d);
			this.focused_on = d;
			window.scrollTo(0,0);
		}
	},

	manageURLQuery: function () {
	    var params = this.get_url_vars();
	    var typeMap = { doc_id : "doc", uid : "user" };
	    for (var id in typeMap) {
	        if (params[id] && !isNaN(params[id])) {
	            var node = this.find_node_by_id(params[id], typeMap[id]);
	            if (node) {
	                this.focus_toggle(node);
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
	  	var idMap = {user : "uid", doc : "doc_id" };
	  	for (var i = 0; i < this.graph.nodes.length; ++i) {
	  		if (this.graph.nodes[i].type == type && this.graph.nodes[i][idMap[type]] == id) {
	            return this.graph.nodes[i];
	        }
	  	}
	  	return false;
	},

	update_view_all: function () {
    	var sewing_kit = $('a#view_annotations');
    	var href = sewing_kit.attr('href');
        var current = this.current(); //current isn't what it used to be. REVISIT REDEFINED CURRENT
        var doc_ids,
            users,
            dates,
            sortedDates,
            query = [];

        href = href.split('?')[0];   // drop query string
        if (current.length == this.all_annotations.length) {
            // Avoid calculating all this when there's no filter
            sewing_kit.attr('href', href);
            return;
        }

        // Get unique doc ids in current annotations
        doc_ids = current.map(function (value, index) { return value['doc_id']})
                    .filter(function (value, index, self) { return self.indexOf(value) === index;});
        // get unique uids
        users = current.map(function (value, index) { return value['uid']})
            .filter(function (value, index, self) { return self.indexOf(value) === index;});

        dates = current.map(function (value, index) { return parseInt(value['created'], 10) } );

        if (doc_ids.length) {
			for (var i = 0; i < doc_ids.length; i++) {
                query.push('document[]=' + doc_ids[i]);
			}
        }
        if (users.length) {
			for (var i = 0; i < users.length; i++) {
                query.push('author_select[]=' + users[i]);
			}
        }
        if (dates.length) {
            var date = new Date(Math.min.apply(Math, dates));
            query.push('posted_after=' + date.toISOString());
            date = new Date(Math.max.apply(Math, dates));
            query.push('posted_before=' + date.toISOString());
        }
        sewing_kit.attr('href', href + '?' + query.join('&'));
	},

	count_pie_data: function(pie_type) {
		var count = Array();
		if (typeof this.pie_slice_keys[pie_type] === "undefined") {
			this.pie_slice_keys[pie_type] = Array();	// don't clobber; set once then leave alone
		}
		var proto = this;
		// Relies on fields in annotation data that match pie types
		// Those fields are added in pre-processing
		this.current().forEach(function (a) {
			if (typeof count[a[pie_type]] === "undefined") {
				count[a[pie_type]] = 0;
				// BUG: This doesn't work right
				if (pie_type == 'annotation_tags' && typeof a[pie_type] === 'array') {
					// loop through tags array
					//console.log(a.annotation_tags, 'annotation_tags');
					a.annotation_tags.forEach(function (tag) {
						proto.pie_slice_keys['annotation_tags'].push(tag);
					})
				} else {
					proto.pie_slice_keys[pie_type].push(a[pie_type]);
				}
			}
			++count[a[pie_type]];
		});
		// zero-fill missing keys
		// TODO: skip step for tags
		this.pie_slice_keys[pie_type].forEach(function (key) {
			if (typeof count[key] === "undefined") {
				count[key] = 0;
			}
		});
		return (count);
	},
}; // END: DashboardModel


/**
 * Dashboard View
 * Updates DOM
 **/
function DashboardView(model, settings){
	var self = this;
	self.model = model;
	
	self.size = { //moved from DashboardView
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
		graph: {
			width: 700,
			height: 5000,
			padding: 50
		},
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

	d3.select("div#network")
		.append("p")
		.text("People")
		.style("font-size", "16pt")
		//.style("font-weight", "bold")
		.style("padding-left", (self.size.column.user - self.size.graph.padding) + 'px')
		.append("p")
		.text("Materials")
		// .style("left", size.column.doc)
		.style("font-size", "16pt")
		//.style("font-weight", "bold")
		.style("padding-left", (self.size.column.user + (self.size.graph.padding * 5)) + 'px')
        //.style("padding-left", size.column.doc / 2 + "px")
		.style("display", "inline");

	self.network = d3.select("div#network")
		.append("svg:svg")
		.attr("id", "network")
		.attr("width", self.size.graph.width)
		.attr("height", self.size.graph.height);

  	// Divs for tooltips that show annotation counts, et al.
	self.tooltips = d3.select("body").append("div")
			.attr("class", "tooltip")
			.style("opacity", self.opacity.hidden);

	self.pie_choices = d3.select("div#pie_types").append("svg:svg")
		.attr("id", "pie_choices")
		.attr("height", self.size.summary_pie.height)
		.attr("width", self.size.summary_pie.width + self.size.summary_pie.padding * 2);

	self.pie_g = self.pie_choices.selectAll("g.pie")
					.data(self.model.pie_types)
					.enter()
					.append("g")
					.attr("id", function (d) { return d; })
					.attr("class", "pie");
	
	// arc is only for the network graphs, because outerRadius changes
	self.arc = d3.svg.arc().outerRadius(self.size.radius).innerRadius(0);
	
	// pie is re-used for the summary pies
	self.pie = d3.layout.pie().value(function (d) { return d.value; });
	
	//Creates final pie. Am working on this
	self.final_pie = self.pie_g.attr("d", self.arc)
							   .style("fill", function(d, i) {
								   return self.color_scale(i);
							   })
							   .style("opacity", 1);

	self.legend = d3.select('#legend')
		.append("svg:svg")
		.attr("id", "legend")
		.attr("height", self.size.legend.height)
		.attr("width", self.size.legend.width);

	self.bar_x = null;	// scoped here because we don't want to reset it on updates
	self.xAxis = null;
	self.xAxisTicks = null;
	self.bar_chart = null;
	self.brush = null;

	d3.select('.fa-spinner').remove();
}

DashboardView.prototype = {
    // Widths are hard-coded in because
    // they're pretty tricky to determine programmatically, and I
    // thought this way would actually be more maintainable than
    // including a bunch of complex queries.
	scale_dashboard: function() {
		var dashboard_width = 1162; 
    	var container = document.querySelector('#annotations_dashboard');
    	var inner_container = container.querySelector('#dashboard');

      	var container_width = container.getBoundingClientRect().width;

		if (container_width < dashboard_width) {

			var ratio = container_width / dashboard_width;
			inner_container.style.transform = 'scale(' + ratio + ')';

		} else inner_container.style.transform = 'none';
	},

	// REVIEW 
	tooltip_on: function (d) {
		// fade in our tooltips
		this.tooltips.transition()
			.duration(200)
			.style("opacity", 1);
		var type = this.getAttribute("class");
		var text = "<h4>";
		if (type == "node" || type == "pie_total") {
			var total;
			var data;
			if (type == "node") {
				total = d.count;
				data = this.model.pie_node_data[d.id];
				text += total + " annotation";
				if (total > 1) {
					text += "s";
				}
			} else if (type == "pie_total") {
				var total = 0;
				// crazy fragile; depends on div ids in DOM
				var pie_type = this.parentNode.getAttribute("id"); // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
				for (var key in this.model.pie_data_aggregate[pie_type]) {
					total += this.model.pie_data_aggregate[pie_type][key].value;
				}
				var title = this.model.pie_labels[pie_type];
				data = this.model.pie_data_aggregate[pie_type];
				text += title + "</h4>";
			}
			text += "</h4>";
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

		this.tooltips.html(text)
			.style("left", (d3.event.pageX + 15) + "px")
			.style("top", (d3.event.pageY + 15) + "px");
	},

	tooltip_off: function () {
		this.tooltips.transition()
			.duration(500)
			.style("opacity", this.opacity.hidden);
	},

	// REVIEW
	// Add annotation counts on edges
	draw_edge_weights: function () {
		this.remove_edge_weights();
		// Firefox's implementation of getTotalLength() is bugged
		if (navigator.userAgent.toLowerCase().indexOf('firefox') > -1) {  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			return;
		}
		d3.selectAll("path.edge").each(function (p) {
				this.network.append("text")  
				    .attr("x", this.getTotalLength() / 2)
				    .attr("class", "edge_weight")
				.append("textPath")
					.attr("stroke", "black")
					.attr("xlink:href", "#" + p.id)
					.text(p.count);
			});
	}, 

	remove_edge_weights: function () {
		d3.selectAll("text.edge_weight").remove();
	},

	// REVIEW
	brush_clear: function () {
		d3.select("a.dashboard-button#reset_brush").style("visibility", "hidden");
		d3.selectAll("rect.extent").remove();
		d3.selectAll("g.resize").remove();
		this.brush.clear();                        // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		this.model.timeFilter = null;
	},
	
	// calculate height of the network graph based on nodes number and node radius
	calculate_height: function (graph) {
	 	if(!(graph && graph.nodes && this.size && this.size.radius))	return 0;
	  	var counts = {user : 0, doc : 0};
	  	graph.nodes.forEach(function(node){		counts[node.type]++;	});
	  	return 3 * this.size.radius * (1 + Math.max(counts.user, counts.doc));			//adding 1 for padding
	},

	help_on: function(curr_help) {
		d3.select(curr_help)
				.select('.help_text') // VIEW
				.style("visibility", "visible")
				.style("left", (d3.event.layerX) + "px")
				.style("top", (d3.event.layerY) + "px");
	},

	help_off: function(curr_help){
		d3.select(curr_help)
			.select('.help_text')
			.style("visibility", "hidden");
	},

	label_pie_charts: function () {
		for (var i = 0; i < this.pie_types.length; i++) {
		  this.pie_choices
		  	.append("text")
		  	.attr("transform", "translate(" + ((this.size.summary_pie.radius * (i + 1)) + ((this.size.summary_pie.radius + (this.size.summary_pie.padding * 2)) * i)) + ",125)")
		  	.attr('font-size', '12pt')
		  	.text(this.pie_labels[this.pie_types[i]]);
		}
	},

	// REVIEW
	update_graph: function () {
		this.model.graph = this.model.init_graph();  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		this.network.attr("height", this.calculate_height(this.model.graph)); // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		this.model.pie_node_data = this.model.gen_pie_nodes(this.model.pie_current);  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		this.y_coords = {};	// clear our positions, if set
		var edges = this.network.selectAll("path.edge").data(this.model.graph.edges);
		edges.exit().remove();
		edges.enter()
			.append("svg:path")
			.attr("class", "edge")
			.style("stroke", this.colors.link.active)
			.style("stroke-opacity", this.opacity.normal)
			.style("fill", "none")
			.on("mouseover", this.tooltip_on)
			.on("mouseout", this.tooltip_off);
		// update edges
		var edge_scale = d3.scale.linear().range([.02,.15]);
		edges.attr("id", function(d) { return d.id; })
			.style("stroke-width", function(d) { return edge_scale(d.count); });

		var nodes = this.network.selectAll("g").data(this.model.graph.nodes);
	  	nodes.exit().remove();
		nodes.enter()
			.append("g")
			.attr("class","node")
			.on("mouseover", this.tooltip_on)  // !!!!!!!!!!!!! CONTROLLER  !!!!!!!!!!!!!!!!
			.on("mouseout", this.tooltip_off)
			.on("click", this.model.focus_toggle);

		var proto = this;
		nodes.sort(function (a,b) { // !!!!!!!!!!!!!!!!!!!!!!!! MODEL  !!!!!!!!!!!!!!!!
				if (a.count < b.count) { return 1; }
				else if (a.count > b.count) { return -1; }
				return 0;
			})
			.each(function (d) { d.x = proto.node_x(d); d.y = proto.node_y(d); }) // VIEW
			.attr("transform", function (d) {
					return "translate(" + d.x + "," + d.y + ")";});

		// // Must draw *after* setting nodes' x/y, but must define first for z
		edges.attr("d", d3.svg.diagonal());

		// Draw nodes
		var pies = nodes.selectAll("path")
			.data(function (d) {
				if (typeof proto.model.pie_node_data[d.id] === "undefined") {
					return proto.pie(Array());
				} else {
					return proto.pie(proto.model.pie_node_data[d.id])
				}});

		pies.exit().remove();
	    pies.enter()
			.append("svg:path")
			.attr("class", "node_pie");

		pies.attr("d", this.arc)
	  		.style("fill", function(d, i) { return proto.color_scale(i); });

	  	// Add node labels
	  	nodes.selectAll("text.node_label").remove();
	  	var labels = nodes.append("text")
	  		.attr("class", "node_label")
				.text(function(d) {
					return d.id.substring(0, proto.size.string.length);
				});
	},	
	
	update_timebrush: function () {
		// TODO: refactor to global variables, relative to one another for
		// more dynamic layout
		// var margin = {top: 20, right: 20, bottom: 80, left: 20},
		// 	width = size.bar.width - size.bar.padding.left - size.bar.padding.right,
		// 	height = size.bar.height - size.bar.padding.top - size.bar.padding.bottom;
		var cf = crossfilter(this.model.current()); // outside library;
		var proto = this;
		var dim = cf.dimension(function(d) {
			// time stored as Unix epoch time
			return proto.model.timeFormat(new Date(d.created));
		});
		
		//Commented code creates array of date information plus number of annotations per date.
		var g = dim.group();
		var data = this.model.fill_empty_dates(g.all());
		/**var data = [];
		function countNumOccurrences(dataset, someDate) {
			var count = 0;
			for (var index = 0; index < dataset.length; index++) {
				var rawDate = proto.model.annotations[index].created;
				var formattedDate = proto.model.timeFormat(new Date(rawDate));
				if (formattedDate == someDate) {
					count++;
				}
			}
			return count;
		}
		for (var i = 0; i < proto.model.annotations.length; i++) {
				var rawDate = proto.model.annotations[i].created;
				var formattedDate = proto.model.timeFormat(new Date(rawDate));
				var numOccurrences = countNumOccurrences(proto.model.annotations, formattedDate);
				if (i === 0) {
					data.push({date: formattedDate, occurrences: numOccurrences});
				}
				if (i >= 1) {
					var prevRawDate = proto.model.annotations[i-1].created;
					var prevForDate = proto.model.timeFormat(new Date(prevRawDate));
					if (prevForDate != formattedDate) {
						data.push({date: formattedDate, occurrences: numOccurrences});
					}
				}
		}**/
		console.log("data: ", data);

		if (this.bar_chart === null) {
			this.bar_chart = d3.select("div#time_brush").append("svg")
			    .attr("width", this.size.bar.width + this.size.bar.padding.left + this.size.bar.padding.right)
			    .attr("height", this.size.bar.height + this.size.bar.padding.top + this.size.bar.padding.bottom);
		}
		// Create x-axis, but only once
		if (this.bar_x === null) { 
			this.bar_x = d3.scale.ordinal()
				.domain(data.map(function (d) { return d.x; })) //previously returned d.date
		    	.rangeBands([this.size.bar.padding.left, this.size.bar.width - this.size.bar.padding.right - this.size.bar.padding.left], 0.1);

			//	Create ticks
		    var factor = (data.length > 16 ? Math.floor(data.length / 8) : 1);
		    var ticks = [];
		    for (var j = 0; j < data.length; j += factor) { //was j+=1
				ticks.push(data[j].x);
				//ticks.push(data[j].date);
			}
			this.xAxisTicks = ticks;
			console.log("ticks array: ", this.xAxisTicks),

			this.xAxis = d3.svg.axis()
				    .scale(this.bar_x)
				    .orient("bottom")
				    .tickValues(ticks);

	  		this.bar_chart.append("g")
					.attr("class", "x axis")
					.attr("transform", "translate(0," + this.size.bar.height + ")")
					.call(this.xAxis)
					.selectAll("text")
					.style("text-anchor", "end")
					.attr("transform", "rotate(-65)");
	    }

    	var bar_width = this.bar_x.rangeBand() - 1;

		var bar_y = d3.scale.linear()
			.domain([0, d3.max(data, function (d) { return d.y; })]) //returned d.y
			.range([this.size.bar.height, this.size.bar.padding.top]);

		var yAxis = d3.svg.axis()
				    .scale(bar_y)
				    .orient("left")
				    .tickFormat(d3.format("2i"))
				    .ticks(7);

		this.bar_chart.select("g.yAxis").remove();
		this.bar_chart.append("g")
					.attr("class", "yAxis axis")
					.attr("transform", "translate(" + this.size.bar.padding.left + ",0)")
					.call(yAxis)
				.append("text")
			  	.attr("class", "y axis")
			  	.attr("transform", "rotate(-90)")
			  	.style("text-anchor", "end")
			  	.attr("y", 6)
			  	.attr("x", -40)
			  	.attr("dy", ".35em")
			  	.text("Annotations");

    	var bars = this.bar_chart.selectAll("rect.bar").data(data);

		bars.enter()
			.append("rect")
  			.attr("class", "bar");

	    bars.exit().remove();

	  	bars.attr("width", bar_width)
	  		.attr("y", function (d) { return bar_y(d.y); })
	  		.attr("x", function (d) { return proto.bar_x(d.x); })
	  		.attr("height", function (d) { return proto.size.bar.height - bar_y(d.y); });

	  	var bar_labels = this.bar_chart.selectAll("text.bar_label").data(data);
	  	bar_labels.exit().remove();
	  	bar_labels.enter()
	  		.append("text")
	  		.attr("class", "bar_label")
	  		.attr("fill", "black")
	  		.attr("font-size", bar_width / 2 )
	  		.attr("text-anchor", "middle")
	  		.style("transform", "rotate(-90)");

		// Add the brush for filtering by time
		this.brush = d3.svg.brush()
			.on("brush", this.brushed)
			.on("brushend", this.brushed)
			.x(this.bar_x);

		var handle = d3.svg.arc()
			.outerRadius(this.size.bar.height / 3)
			.startAngle(0)
			.endAngle(function (d,i) { return i ? -Math.PI : Math.PI; });

	    var brushg = this.bar_chart
	        	.append("g")
	    		.attr("class", "brush")
	    		.call(this.brush);

			brushg.selectAll("rect")
		    	.attr("height", this.size.bar.height);

		this.brushed();
	},

	brushed: function() {
		d3.select("a.dashboard-button#reset_brush").style("visibility", "visible"); // CONTROLLER
    	var extent = this.brush.extent();
		console.log("extent", extent);
    	var start = extent[0];
    	var end = extent[1];
		if (end === 0) {
			end = 1000;
		}
    	var bar_width = this.bar_x.rangeBand() - 1;
		console.log("bar_width", bar_width); //this returns 342.63! Wow.
    	//var dates = this.xAxisTicks; //Old code.
		var dates = [];
    	var proto = this;
		
		//Populates dates array with dates within the brush
    	d3.selectAll("rect.bar").each(function (d) {
    		var x = proto.bar_x(d.x); //this is undefined.
			console.log("x", x);
    		if ((x + bar_width) >= start && x <= end) {
				console.log("d.x", d.x);
    			dates.push(d.x);
	    	}
    	});
		/**d3.selectAll(".x axis").each(function (d) {
    		var x = proto.bar_x(d.x); //??
    		if ((x + bar_width) >= start && x <= end) {
    			dates.push(d.x);
	    	}
    	});**/
		console.log("dates array:", dates);
		
    	// Filter our annotations by selected dates
    	var filter = []; // MODEL
    	this.model.current(true).forEach(function (a) {
		//dates.forEach(function (a) {
    		var date = proto.model.timeFormat(new Date(a.created));
    		if (dates.indexOf(date) != -1 && filter.indexOf(a) == -1) {
    			filter.push(a);
    		}
    	});
    	this.model.timeFilter = filter;
		console.log("filter: ", this.model.timeFilter);

    	// Update the other parts of the display
    	// Call these updates here because we don't want to update the bar chart, too
    	this.update_graph();
    	this.update_summary_pies();
    	this.model.update_view_all();
    	// Are we focused on a node? If so, update the edge labels
    	if (this.model.focused_on !== null) {
	    	this.draw_edge_weights();
	    }
	},

	update_legend: function() {
		var item = this.legend.selectAll("g.legend_item")
			.data(this.model.pie_data_aggregate[this.model.pie_current]); 
		
		var proto = this;
		item.exit().remove();
		item.selectAll("text").remove();
		item.enter()
			.append("g")
			.attr("class", "legend_item")
			.attr("transform", function(d, i) { return "translate(0," + i * (proto.size.legend.square.height + 2) + ")"; })
			.append("rect")
			.attr("x", 0)
			.attr("width", proto.size.legend.square.width)
			.attr("height", proto.size.legend.square.height)
			.style("fill", function(d,i) { return proto.color_scale(i); });

		item.append("text")
			.attr("x", proto.size.legend.square.width + 10)
			.attr("y", proto.size.legend.square.height / 2)
			.attr("dy", ".35em")
			.style("text-anchor", "start")
			.text(function(d) { return d.key; });
	},
	
	update_summary_pies: function() { //moved from DashboardModel
		var x = 0;	// to keep track of order; drawing doesn't know how many it has done
		this.model.pie_data_aggregate = Array();	// reset data counts  
		var proto = this;

		proto.model.pie_types.forEach(function(pie_type) { //Problem: pie_types is undefined
			var count = proto.model.count_pie_data(pie_type);

			console.log("count: ", count);
			
			for (var key in count) {
				if (typeof proto.model.pie_data_aggregate[pie_type] === "undefined") {
					proto.model.pie_data_aggregate[pie_type] = Array();
					console.log('count is working');	
				}
				proto.model.pie_data_aggregate[pie_type].push({key: key, value: count[key]});
			}
			// Must sort to keep colors consistent
			// TODO: refactor into a single sort function called by all pies
			
			proto.model.pie_data_aggregate[pie_type].sort(function (a,b) {
				if (a.key < b.key) { return -1; }
				else if (a.key > b.key ) { return 1;}
				return 0;
			});
			proto.draw_summary_pie(pie_type, x);
			++x;
		});
		console.log("pie_data_aggregate in model", proto.model.pie_data_aggregate);
	},
	
	draw_summary_pie: function (pie_type, x) {
		var proto = this;
		
		var arc = d3.svg.arc()
			.outerRadius(this.size.summary_pie.radius)
			.innerRadius(0);

		var my_pie = d3.select('g#' + pie_type).selectAll("path")
						.data(this.pie(this.model.pie_data_aggregate[pie_type])); //pie() is not defined...
	    my_pie.enter()
				.append("svg:path")
				.attr("class", "pie_total")
				.attr("transform", function (d) {
					var str = "translate(";
					var pie_x = proto.size.summary_pie.radius * 2 * x + 55;
					pie_x += proto.size.summary_pie.padding * (x + 1) * 2;
					str += pie_x + "," + proto.size.summary_pie.radius + ")";
					return str;
					})
				.on("mouseover", this.tooltip_on)  // !!!!!!CONTROLLER...!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
				.on("mouseout", this.tooltip_off)
				.on("click", this.select_pie);

		my_pie.attr("d", arc)
	  		.style("fill", function(d, i) { return proto.color_scale(i); })
			.style("opacity", 1);

	  	if (pie_type !== this.pie_current) {
	  		var color = my_pie.style("fill");
	  		my_pie.style("fill", function (d,i) {
	  			return d3.rgb(proto.color_scale(i)).darker();
	  		}).style("opacity", .5);
	  	}
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

	// Remove time filter
	$('a.dashboard-button#reset_brush').click(function() { 
		self.view.brush_clear();
   		this.update();
		if (self.model.focused_on != null) {
			self.view.draw_edge_weights();
		}
	});

	// Remove all filters
	$('a.dashboard-button#reset_all').click(function() { 
		self.reset_all();
	});

	// "View Annotations" button clicked; update data table
	// We only update when this button is clicked because it's too slow to update all the time
	//$('a.dashboard-button#view_annotations').click(update_annotations_table);

	$('a.dashboard-button#return_to_vis').click(function() { 
		// annotations_table.destroy();
	    d3.select("#annotations_table_draw_wrapper").style("visibility", "hidden"); // !!!!!!! VIEW !!!!!!!!!!!
	    d3.select("#annotations_table_draw").style("visibility", "hidden");
	    d3.selectAll("a#return_to_vis").style("visibility", "hidden");
	})

	d3.selectAll('.help')
		.on("mouseover", function() { self.view.help_on(this); })
		.on("mouseout", function() { self.view.help_off(this); });

	this.view.scale_dashboard();
	window.addEventListener('resize', this.view.scale_dashboard);
}

DashboardController.prototype = {
	update: function() {
	  	this.model.update_view_all();
	  	this.view.update_graph();
		this.view.update_timebrush();
		this.view.update_summary_pies();
	  	this.view.update_legend();
  	},

  	// REVIEW
  	select_pie: function(d) {   
		var parent = this.parentNode; // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		var pid = parent.getAttribute("id");
		if (this.model.pie_current != pid) {
			this.model.pie_current = pid;
			this.view.update_graph();
			this.view.update_summary_pies();
			this.view.update_legend();
			// window.scrollTo(0,400);
		}
	},

	focus_on: function (node) { // !!!!!!!!!! FIX THIS WITH focus_toggle !!!!!!!!!!!!
		// filter our annotations to include only the active ones
		// documents are always targets, users are always sources
		this.view.tooltip_off();
		var filter = Array();
		this.reset_all();	// HACK: doesn't work with time filters, so reset
		this.model.unfiltered().forEach(function (a) {
			this.model.graph.edges.forEach(function (edge) {
				if ((node.id == edge.source.id && node.id == a.username) ||
					(node.id == edge.target.id && node.id == a.documentTitle))
				{
					if (filter.indexOf(a) == -1) {
						filter.push(a);
					}
				}
			});
		});
		this.model.addFilter(filter);
		// Ego network removes time filter
		// d3.select("a.dashboard-button#reset_brush").style("visibility", "hidden");
		this.update();
		this.view.draw_edge_weights();
	}, 

	reset_all: function() { 
		this.view.remove_edge_weights();
		this.view.brush_clear();
		this.model.focused_on = null;
		this.model.removeAllFilters();
		this.update();
	},
}; // END: DashboardController


Drupal.d3.annotations_dashboard = function (select, settings) {

	function init(data) {
		var temp = Array();
		temp.push(data);
		var annotations = temp[0];
		// var annotations = Array();
		// annotations.push(data);

		var model = new DashboardModel(annotations);
		var view = new DashboardView(model, settings);
		var controller = new DashboardController(model, view);

		// Initial creation
		controller.update(true);
		//view.label_pie_charts(); // only need to label them once
		model.manageURLQuery();

		console.log('yayy');
	}

	d3.json(settings.config.data_url, function (error, original_data) {
		if (error) {
			console.error(error);
		} else {
			init(original_data);
		}
    });	 

};
})(jQuery);