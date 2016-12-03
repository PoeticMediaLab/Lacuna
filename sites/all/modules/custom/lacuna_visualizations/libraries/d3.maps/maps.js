/**
 * @file
 * Lacuna maps visualization.
 *
 * Creates a network graph of responses and their references
 *
 * Ben Allen <benallen@stanford.edu> 2014
 *
 */


(function($) {

	// using bostock's d3 margin convention
	// (http://bl.ocks.org/mbostock/3019563)
	//
	// bottom needs to be fairly large so that the axis labels don't
	// run off the edge when in months with long names.
	// TODO actually fix this, I've broken out the brush and axis into
	// their own svgs.
	var margin = {top: 20, right: 10, bottom: 90, left: 10};


 Drupal.d3.maps = function (select, settings) {
    var initialWidth  = (settings.config.width || 800),
        initialHeight = (settings.config.height || 800),
        nodes  = settings.nodes,
        links  = settings.links,
        z      = d3.scale.ordinal().range(["blue", "red", "orange", "green"]),
        k      = Math.sqrt(nodes.length / (width * height)),
		testString = settings.config.testString,
		userList = settings.config.userList,
        color  = d3.scale.category20(),
		drawDocumentCircle = settings.config.drawDocumentCircle;

	var linkedNodesOnly = !drawDocumentCircle;


		// TODO: so this probably should be an object or an
		// associative array one of these days. but for now, it's an
		// array of two-entry arrays (does javascript have tuples?) --
		// 0th item the name, 1st item the color associated with it.
		var userNamesColors = [];
		// the users that are actually selected in the user interface.
		// Starting filled for testing purposes; will likely start
		// empty.
		var selectedUsers = [];

		var colorsCounter = 0;
		for (userObject in userList) {
			var field_display_name = userList[userObject].field_display_name;
			var username = userList[userObject].name.trim();
			if(field_display_name.length != 0){
				// TODO: will crash if und[0].safe_value doesn't
				// exist, and I'm not certain it's guaranteed to
				// exist.
				// MLW: It will exist unless we start translating languages
				// "und" is Drupal's LANGUAGE_NONE constant
 				var safeName = field_display_name.und[0].safe_value.trim();
				// look for a node with an author matching safeName.
				// If it exists, add safeName to the list of user
				// names. If it doesn't, don't. (this keeps admin
				// accounts, etc. out of the user list).
				for(var i = 0; i < nodes.length; i++){
					// DELETE (ih) : links.push([nodes[i].data.title, nodes[i].edges.)
					if (nodes[i].data.author == username) {
						// Change "username" to "Display Name" as needed
						// Allows students to control how their work appears to others
						nodes[i].data.author = safeName;
					}
					if (nodes[i].data.author === safeName) {

						userNamesColors.push([safeName, color(colorsCounter % 20), nodes[i].data.u_id]);
						// for debugging purposes.
						colorsCounter++;
						selectedUsers.push(nodes[i].data.u_id);
						break;
					}
				}
			}
		}


	// set up the actual width/height to conform to margin
	// convention.
	var width = initialWidth - margin.left - margin.right;
	var height = initialHeight - margin.top - margin.bottom;

	// assign date for links as the date of creation for the source node.
	if(links)
	{
		 for (var i = 0; i < links.length; i++) {
			links[i].data.date = nodes[links[i].source].data.date;
		}
	} else {
		links = [];
	}

    var force = d3.layout.force(height)
      .size([width, height]);

	var timeout = null; // used in mouseover and mouseout events on
	var delay = 300;	// nodes

	// begin displayTooltip
	 function displayTooltip(d) {
		xPos = d.x;
		yPos = d.y;

		d3.select("#maps-tooltip")
		.style("left", xPos + 30 + "px")
		.style("top", yPos + 70 + "px")
			;
		d3.select("#maps-tooltip")
			.select("#title")
			.text(d.data.title)
			.attr("href", d.data.thisURL)
			;
		d3.select("#maps-tooltip")
			.select("#author")
			.text(function() {
				for(var i = 0; i < userNamesColors.length; i++) {			// ih: retrieves the user's display name from userNamesColors
					if(userNamesColors[i][2] == d.data.u_id) {
						return userNamesColors[i][0]
					}
				}
				return d.data.author;
			})
			// .text(d.data.author)
			;
		d3.select("#maps-tooltip")
		.select("#image")
		.html(d.data.image)
		;
		if(d.data.document_abstract){
			d3.select("#maps-tooltip")
				.select("#abstract")
				.text(d.data.document_abstract)
				;
			d3.select("#maps-tooltip")
				.select("#abstract")
				.classed("hidden", false)
				;
		}  else {
			d3.select("#maps-tooltip")
				.select("#abstract")
				.classed("hidden", true)
				;
		}

		// times 1000, because js stores time in milliseconds since
		// unix epoch, whereas Drupal gives time based on seconds
		// since unix epoch.
		var date = new Date(d.data.date * 1000);

		// clear out the html links, then add links based on what the
		// node actually links to.
		// --
		d3.select("#links")
			.selectAll("a")
			.remove()
		;
		d3.select("#links")
			.selectAll("br")
			.remove()
		;
		if (d.data.linksTitles.length != 0)
		{
			for (var i = 0; i < d.data.linksTitles.length; i++){
				if (i != d.data.linksTitles.length){
					d3.select("#links")
						.append("br")
						;
				}
				d3.select("#links")
					.append("a")
					.attr("href", d.data.linksURL[i])
					.text(d.data.linksTitles[i])
					;
			}
			d3.select("#maps-tooltip")
				.select("#links")
				.classed("hidden", false)
				;

		// if there are no links, hide the links span
		// altogether.
		}
		else {
			d3.select("#maps-tooltip")
				.selectAll("#links")
				.classed("hidden", true)
			;
		}
		d3.select("#maps-tooltip")
			.classed("hidden", false)
			.on("mouseover", function() {
				d3.select("#maps-tooltip")
					.classed("hidden", false)
					;
				})
			.on("mouseout", function() {
				d3.select("#maps-tooltip")
					.classed("hidden", true);
					;
			});

		// For bottom half of circle, show tooltip above mouse rather than below.
		if (yPos > initialHeight/2) {
			var height = $("#maps-tooltip").outerHeight();
			d3.select("#maps-tooltip").style("top", (yPos + 80 - height) + "px");
		}
  }; // end displayTooltip

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

    force.charge(-40);
    force.distance(50);
    force.gravity(.09);


	// div containing:
	// 1) various toggleable features (biblio circle... more to come)
	// 2) selectable names of all students w/ response posts.
	var controlPanelDiv = d3.select("#" + settings.id).append("div")
		.classed("controlPanelDiv", true)
		.style("height", "70%")
		.style("width", "200px")
/*		.style("border", "2px solid")
		.style("border-color", "black")  */
		.style("float", "right")
		;

	var controlPanelFontSize = 20;
	var userSelectorSvg = d3.select(".controlPanelDiv").append("svg")
		.attr("id", "userSelectorSvg")
		.attr("height", initialHeight)
		.attr("width", "200px")
		.attr("overflow", "scroll")
		;


	var playingFlag = false;
	var playFromStart = userSelectorSvg.append("g")
							.attr("id", "playFromStart")
							.classed("selected", function() {
								return playingFlag;
							})
							.on("click", function() {
								if (!playingFlag){
									playingFlag = true;
									playFromStart.classed("selected", function () {return playingFlag; })
									brushPlayFromStart();
									setTimeout(function() {
										playingFlag = false;
										playFromStart.classed("selected", function () { return playingFlag; });
									}, 3000);
								}
							})
							;
/*	playFromStart.append("circle")
		.attr("id", "playFromStartCircle")
		.attr("cx", "12px")
		.attr("cy", "45px")
		.attr("r", 10)
		.attr("stroke-width", 3)
		;
	playFromStart.append("text")
			.attr("id", "playFromStartText")
			.attr("font-size", controlPanelFontSize)
			.attr("font-family", "serif")
			.attr("x", "25px")
			.attr("y", "50px")
			.text(function(d) {
				if (!playingFlag){
					return "Play from start";
					}
				else {
					return "Pause playback";
				}
			})
			; */


	// TODO: arrangeDocumentNodes is now misnamed
	var arrangeDocumentNodes = userSelectorSvg.append("g")
								.attr("id", "arrangeDocumentNodes")
								.classed("selected", function() {
									if(drawDocumentCircle){
										return false;
									} else {
										return true;
									}
								})
								.on("click", function() {
									if(drawDocumentCircle){
										drawDocumentCircle = false;
										linkedNodesOnly = !drawDocumentCircle;
										arrangeDocumentNodes.classed("selected", true);
										arrangeDocuments();

									} else {
										drawDocumentCircle = true;
										linkedNodesOnly = !drawDocumentCircle;
										arrangeDocumentNodes.classed("selected", false);
										arrangeDocuments();
									}
								})
								;

	arrangeDocumentNodes.append("circle")
			.attr("id", "arrangeDocumentNodesCircle")
			.attr("cx", "12px")
			.attr("cy", "15px")
			.attr("r", 10)
			.attr("stroke-width", 3)
			;

	arrangeDocumentNodes.append("text")
				.attr("id", "arrangeDocumentNodesText")
				.attr("font-size", controlPanelFontSize)
				.attr("font-family", "serif")
				.attr("x", "25px")
				.attr("y", "20px")
				.text(function(d) {
					return "Linked nodes only";})
			;


	var userSelectionEnterSelection = userSelectorSvg.selectAll("g.userListItem")
		.data(userNamesColors)
		.enter()
		;

	// remember that each entry in userNamesColors is an array
	// containing the name at [0] and the associated color at [1]
	var userSelectionGroup = userSelectionEnterSelection.append("g")
			.classed("userListItem", true)
			// unSelected vs. selected because it makes the css
			// slightly less complicated.
			.classed("unSelected", false)
			// stripping spaces, lest we accidentally assign two ids
			// instead of one.
			.attr("id", function(d) { return "user"+d[2];});

		userSelectionGroup.on("click", function(d) {
			var foundUserFlag = false;
			for (var i = 0; i < selectedUsers.length; i++){
				// unselect if already selected
				if (selectedUsers[i] == d[2])  {
					selectedUsers.splice(i, 1);
					foundUserFlag = true;
					d3.select("#" + "user" + d[2])
						.classed("unSelected", true);
					break;
				}
			}
			// not found, select.
			if (!foundUserFlag){
				selectedUsers.push(d[2]);
				d3.select("#" + "user" + d[2])
					.classed("unSelected", false);
			}
			// either way, update the force diagram to reflect newly
			// selected/unselected user.
			redrawGraph();
		})
		.attr("transform", function(d, i) {
			return ("translate(0," + (100 + (i * (controlPanelFontSize * 2))) + ")");
		});

	userSelectionGroup.append("text")
				.attr("font-size", controlPanelFontSize)
				.attr("font-family", "serif")
				.attr("id", "userSelectionText")
				.attr("x", "25px")
				.text(function(d) {
					return d[0];})
			;

	userSelectionGroup.append("circle")
			.attr("id", "userSelectionCircle")
			.attr("cx", "12px")
			.attr("cy", function(d, i) {
				return -5;
			})
			.attr("r", 10)
			.attr("fill", function(d, i) {
				return d[1];
			})
			.attr("stroke", "black")
			.attr("stroke-width", 3)
			;

	var userItems = userSelectorSvg.selectAll(".userListItem");

	// draw an svg for the graph display, using values from
	// "settings", which is passed in by drupal. the var svg actually
	// ends up referring to a g element within the svg, following bostock's
	// margin convention.
    var svg = d3.select('#' + settings.id).append("svg")
        .attr("width", initialWidth)
        .attr("height", initialHeight)
		.attr("float", "left")
            .on("mouseleave", function() {
              d3.select("#maps-tooltip")
             .classed("hidden", true)
             ;
             }) // hide tooltips when mousing out of the svg
				// altogether.
			.append("g")
				.attr("transform", "translate(" + margin.left + "," + margin.top + ")")
	;

	// putting in a <br/> to ensure the control div shows up below the
	// graph div.
	d3.select("#" + settings.id).append("br");

	var brushSvgHeight = 100;
	var timeRectHeight = 25;

    var brushSvg = d3.select('#' + settings.id).append("svg")
        .attr("width", width+120) //Moved over to account for rotated labels.
        .attr("height", brushSvgHeight)
		;

	for (var i = 0; i < nodes.length; i++) {
		// assign ids to each node; once the array is dynamic, we can't
		// simply refer to nodes by position.
		 nodes[i].id = i;
	}

    var graph = svg.append("g")
        .attr("class", "data")
        ;

	// groups for drawing links and nodes in. Necessary to keep new
	// links from being drawn on top of old nodes.
	graph.append("g").attr("id", "links");
	graph.append("g").attr("id", "nodes");

	function tick() {

		link.attr("x1", function(d) { return d.source.x; })
          .attr("y1", function(d) { return d.source.y; })
          .attr("x2", function(d) { return d.target.x; })
          .attr("y2", function(d) { return d.target.y; });

		  node.attr("cx", function(d) { return d.x; })
          .attr("transform", function(d) { return "translate(" + d.x + "," + d.y + ")"; })
          .attr("cy", function(d) { return d.y; });

	}

	// currently sets startDate as date of earliest post and
	// endDate as date of latest. May change to reflect class
	// structure better -- like, startDate could be specified as
	// the first day of the class, and endDate as startDate + 12
	// weeks or whatever.
	var firstNode = d3.min(nodes, function(d) { return d.data.date; });
	var lastNode  = d3.max(nodes, function(d) { return d.data.date; });

	// currently link dates are assigned based on the date of the
	// link's source node, meaning that it's not necessary to check
	// for links before or after the last nodes.
	var startDate = new Date(firstNode * 1000);
	var endDate = new Date(lastNode * 1000);
	//console.log(startDate);
	//console.log(endDate);

	var dateList = nodes.filter(function(d) {return d.data.itemType != 'biblio';})
						.map(function(d) {return new Date(d.data.date*1000);});

	// create time scale used by xAxis
	var timeScale = d3.time.scale()
						.domain([startDate, endDate])
						.range([0 + margin.left, width - margin.right])
					;
	var ticks = timeScale.ticks(d3.time.day);
	var data = d3.layout.histogram()
	    .bins(ticks)
	    (dateList);

	var y = d3.scale.linear()
	    .domain([0, d3.max(data, function(d) { return d.y; })])
	    .range([timeRectHeight, 0]);

	var tickDist = 	timeScale(ticks[1])-timeScale(ticks[0]);

	var bar = brushSvg.selectAll(".bar")
	    .data(data)
	  .enter().append("g")
	    .attr("class", "bar")
	    .attr("transform", function(d) { return "translate(" + (timeScale(d.x)+40) + "," + (y(d.y)+10) + ")"; });

	bar.append("rect")
	    .attr("x", 1)
	    .attr("width", tickDist)
	    .attr("height", function(d) { return timeRectHeight - y(d.y); });

	 // create axis using time scale and draw it at the bottom of the
	// graph.
	var xAxis = d3.svg.axis();
	xAxis.scale(timeScale)
			.orient("bottom")
			// one tick a day -- subject to change.
			.ticks(d3.time.week)
			.tickFormat(d3.time.format("%B %e"))
			;

	brushSvg.append("g")
		.classed("axis", true)
		// move to bottom of graph.
		.attr("transform", "translate(40," + (brushSvgHeight - margin.bottom * 0.7) + ")")
		.call(xAxis)
		// rotate the labels
		.selectAll("text")
		.style("text-anchor", "end")
		.attr("dx", "-.8em")
		.attr("dy", ".15em")
		.attr("transform", function(d) {
			return "rotate(-45)";
		})
		;


		// controlled by the playFromStart button
		function brushPlayFromStart() {
			// 1. clear the brush.

			brush.clear();

			gBrush.transition()
				.call(brush)
				.call(brush.event)
				;

			// 1.5. set the first entry in brushextent to margin.left.
			// 2. set brush to ignore mouse events  (TODO)
			// 3. set a transition on brush.

		   setTimeout(function() {
			   brush.extent([timeScale.invert(margin.left), timeScale.invert(width - margin.right) ]);
				gBrush.transition().duration(2000)
					.call(brush)
					.call(brush.event)
				;
			}, 1000);


	/*		gBrush.transition()
				.call(brush)
				.call(brush.event)
				; */
			// 5. rejoice.
		}

		// brushStart and brushEnd, two functions used
		// by the time brush.
		function brushStart () {
		//	console.log("brushStart!"); // currently does nothing
		};


		function brushUpdate() {
			var extent = brush.extent();
			timeFrame = extent;

			redrawGraph();

		};

		// The selected time frame. Set by the extent of the brush
		// defined below.
		var timeFrame = [timeScale.invert(0), timeScale.invert(500)];


		// --------- FILTERS -----------
		// functions for filtering which nodes are displayed.

		function isLinked(d) {

			if (d.data.itemType == 'biblio'){
				return true;
			}

			// first, get a list of the selected links.
			var selectedLinks = links.filter(inSelectedUsersLink).filter(inTimeFrameLink);
			// return only those nodes that are either the source
			// or target of at least one link.
			for (var i = 0; i < selectedLinks.length; i++) {
				if (d.id == selectedLinks[i].source.id) {
					return true;
				}
			}
			return false;
		}

		function inSelectedUsers(d) {
			// biblio nodes are always rendered
			if (d.data.itemType == 'biblio'){
				return true;
			}
			// okay, it's not a biblio node. see if the author is in
			// selectedUsers; if so, render it.
			for (var i = 0; i < selectedUsers.length; i++) {
				if (d.data.u_id == selectedUsers[i]) {
					return true;
				}
			}	// didn't find it.
			return false;
		}

		function inTimeFrame(d) {
			var date = new Date(d.data.date * 1000);
			// always display document nodes.
			if ( d.data.itemType == "biblio") {
				return true;
			}
			else {
				if (date >= timeFrame[0] && date <= timeFrame[1]) {
					return true;
				} else {
					return false
				};
			}
		}

		function inSelectedUsersLink(d) {
			return inSelectedUsers(d.source);
		}

		function inTimeFrameLink(d) {
			return inTimeFrame(d.source);
		}


		// Now, actually create brush.
		var brush = d3.svg.brush()
						.x(timeScale)
						.extent([timeScale.invert(margin.left), timeScale.invert(width - margin.right)])
						;
		var gBrush = brushSvg.append("g")
						.classed("brush", true)
						.call(brush)
						.call(brush.event)
						;
		gBrush.attr("transform", "translate(40,0)");
		gBrush.selectAll("rect")
						.attr("height", timeRectHeight )
						.attr("y", brushSvgHeight - 60  * 1.5)
						;

		function redrawGraph() {
			filteredNodes = [];
			filteredLinks = [];
			filteredNodes = nodes.filter(inTimeFrame).filter(inSelectedUsers);
			if (linkedNodesOnly) {
				filteredNodes = filteredNodes.filter(isLinked).filter(inSelectedUsers);
			}
			filteredLinks = links.filter(inTimeFrameLink).filter(inSelectedUsersLink);
			start(filteredNodes, filteredLinks);
		}


		// here's where the magic happens -- actually draws nodes and
		// links to the svg.
		function start(startNodes, startLinks) {

			force.nodes(startNodes)
				.links(startLinks)
				.on("tick", tick)
				;

			link = graph.select("#links").selectAll("line.link")
				.data(startLinks, function(d) {
					return d.source.id + '-' + d.target.id;
					});
			link.enter().append("line")
				;
			link.classed("link", true)
				;
			link.exit().transition()
				.attr("stroke-width", 0)
				.attr("stroke", "white")
				.remove()
				;


				// bind data from settings to node. node is a g-element, not a
				// circle; circles are added to the node g-element below.
				node = graph.select("#nodes").selectAll("g")
							.data(startNodes, function(d) {return d.id;})
							;

				// append a g element, put a circle in it.

				node.enter().append("g")
				.append("circle")
				  .attr("class", function(d) { return d.data.itemType; })
				  .attr("fill", function(d) {
					for(var i = 0; i < userNamesColors.length; i++){
						if(userNamesColors[i][2] == d.data.u_id){					// ih: this compares the user id, rather than the usernames
						// if(userNamesColors[i][0] == d.data.author){
							return userNamesColors[i][1];
						}
					} // didn't find it
					return "green";
				  })
				  .attr("r", function(d) { return (d.data.d) ? d.data.d : 10; })
				  // Display tooltip div on mouseover, after 1 second delay.
				  .on("mouseover", function(d) {
					  timeout = setTimeout(function() {displayTooltip(d);}, delay);

					// Hide tooltip on mouseout. Also clear any active timers
					// (means the tooltip doesn't display unless you hover for one
					// second.
				  })
				 .on("mouseout", function() {
					clearTimeout(timeout);
					d3.select("#maps-tooltip")
						.classed("hidden", true);
				})
				;

					;

				node.attr("class", function(d) { return d.data.itemType;} )
					;

				var exitSelection = node.exit();

				exitSelection.selectAll("circle")
						.transition()
						.duration(250)
						.attr("r", 0)
						.remove()
					;
				exitSelection
					.transition()
					.duration(250)
					.remove()
					;

				// only responses are moveable -- document nodes are fixed.
				graph.selectAll(".response")
					.call(force.drag);

				// aw, let's let 'em move biblio posts, too.
				graph.selectAll(".biblio")
					.call(force.drag);

				// _actually_ start the force diagram (finally!)
				force.start();
			}

			// if this appears earlier, confusion results from the
			// call to start() in brushUpdate().
			brush.on('brushstart', function() { brushStart(); })
				 .on('brush', function() { brushUpdate(); })
				;

			// biblio nodes are arranged in a circle. this defines the
			// position and radius of that circle. This is a
			// non-elegant way of doing this, but my inner C
			// programmer expressed itself here.  magic numbers
			// arrived at through trial and error.

			// TODO: rewrite this function to fix object constancy
			// problems.
			function arrangeDocuments() {

				var backgroundCx = width / 2;
				var backgroundCy = height / 2 + 70;
				var backgroundR = (height / 3) + 20;

				if (drawDocumentCircle){

					force.charge(-40);
					var biblioCount = 0;
					for (var i = 0; i < nodes.length; i++)
					{
						// biblio nodes are fixed if we're using the circle layout.
						if (nodes[i].data.itemType == "biblio") {
							if (drawDocumentCircle)
								nodes[i].fixed = true;
							biblioCount++;
						}
					}
					// let's do some trigonometry.
					// theta is not to be confused with settings.theta.
					var theta = (Math.PI * 2) / biblioCount;

					// TODO: this needs to be done the d3 way, rather
					// than what I'm doing here -- this worked fine
					// when drawCircle wasn't user-toggleable, but
					// makes it impossible to maintain object
					// constancy now that it is toggleable.
					for (var i = 0; i < nodes.length; i++) {
						if(nodes[i].data.itemType == "biblio")
						{
							nodes[i].px = backgroundCx + (Math.cos(theta * biblioCount) * backgroundR);
							nodes[i].py = backgroundCy + (Math.sin(theta * biblioCount) * backgroundR);
							biblioCount--;
						}
					}
			} else { // not drawing document circle; make sure biblio
					 //nodes are unfixed
				for (var i = 0; i < nodes.length; i++) {
					nodes[i].fixed = false;
				}
			} // end else
			// either way, redraw.
			redrawGraph();
		} // end arrangeDocuments()



			start(nodes, links); // start with all the nodes in, then
								 // restart with only the
								 // appropriately filtered nodes.
								 // Otherwise, not all nodes are
								 // assigned force-layout related
								 // variables.

			// this simplifies the inSelectedUsers function; I don't
			// have to treat nodes and links differently. (has to
			// happen after the layout is started for the first time)
			for (var i = 0; i < links.length; i++) {
				links[i].data.author = links[i].source.data.author;
			}


			brushUpdate();
			// restarts the force layout with filteredNodes and
			// filteredLinks, places biblio nodes in arrangement (if
			// drawDocumentCircle)
			arrangeDocuments();
			manageURLQuery();

	function manageURLQuery()
	{
		var params = getURLVars();
		if(params["u_id"] && !isNaN(params["u_id"]))
		{
			var userToFilter = 	d3.select("#" + "user" + params["u_id"]);
			if(userToFilter.empty())	return;
			d3.selectAll(".userListItem").classed("unSelected", true);
			userToFilter.classed("unSelected", false);
			selectedUsers = [params["u_id"]];
			redrawGraph();
		}
	}

	function getURLVars()
	{
		var vars = [], hash;
		var hashes = window.location.href.slice(window.location.href.indexOf('?') + 1).split('&');
		for(var i = 0; i < hashes.length; i++)
		{
			hash = hashes[i].split('=');
			vars.push(hash[0]);
			vars[hash[0]] = hash[1];
		}
		return vars;
	}

	/*
	* Transforms map when containing element is less than the
	* width of the map contents.
	*/
	function enableDynamicResizing() {
	  
	  /*
	  * Widths are hard-coded in because
	  * they're pretty tricky to determine programmatically, and I
	  * thought this way would actually be more maintainable than
	  * including a bunch of complex queries.
	  */
	  var containerThreshold = 1020;
	  var innerContainerMinWidth = 1000;

	  var container = document.querySelector('#content');
	  var innerContainer = container.querySelector('.d3.maps');

	  var scaleMap = function() {

	    var containerWidth = container.getBoundingClientRect().width;

	    if (containerWidth < containerThreshold) {

	      var ratio = containerWidth / containerThreshold;
	      innerContainer.style.width = innerContainerMinWidth + 'px';
	      innerContainer.style.transform = 'scale(' + ratio + ')';

	    } else {

	    	innerContainer.style.transform = 'none';
	    	innerContainer.style.width = 'auto';

	    }

	  };

	  innerContainer.style.transformOrigin = 'left top';

	  scaleMap();
	  window.addEventListener('resize', scaleMap);

	}

	enableDynamicResizing();

}

})(jQuery);




