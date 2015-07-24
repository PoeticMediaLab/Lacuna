/**
 * @file
 * Lacuna journeys visualization.
 */

(function($) {

	// using bostock's d3 margin convention
	// (http://bl.ocks.org/mbostock/3019563)
	// 
	// bottom needs to be fairly large so that the axis labels don't
	// run off the edge when in months with long names.
	// TODO actually fix this, I've broken out the brush and axis into
	// their own svgs.
	var margin = {top: 20, right: 10, bottom: 60, left: 30};


 Drupal.d3.journeys = function (select, settings) {

	function stripHtml(html) {
		return jQuery(html).text();
	}


	var sessionTimeout = 7200000; 	// two hours in seconds.
	var selectedUsers = [];
	var userNamesColors = [];
    var color  = d3.scale.category20();
	var colorsCounter = 0;
	var foundUserFlag = false;
	var allNodes = [];  // complete roster of all nodes visited. used
						// when building links.
	var foundNodeFlag = false;
	var uniqueNodes = []; // only unique nodes; used when rendering.
	var allLinks = []; // used when rendering. no need for allLinks list.

	function jsonParser(json) { 

		var stopParsing = 2000;
		for (var i = 0; i < json.length; i++) {
			//console.log(i);
			 var node = new Object();
			 // many of the assignments directly below are just
			 // stuff that's required to make the visualization,
			 // currently awkwardly adapted from the maps
			 // visualization, go.  Once it's actually working in some
			 // capacity, I'll take them out.
			  node["data"] = new Object();
			  node["data"]["date"] = json[i]["Timestamp"];
			  node["data"]["author"] = stripHtml(json[i]["Name"]);


			  // begin the real things.

			  // title is name and title. Blame drupal.
			  // Fortunately you don't have to think about this after
			  // these two lines.
			  node["data"]["title"] = stripHtml(json[i]["Page Title"]);
			  node["name"] = stripHtml(json[i]["Page title"]);
			  node["thisURL"] = json[i]["Path"];
			  //console.log(node.thisURL);
	//		  console.log("node name: ");
	//		  console.log(node.name);

			  node["visitList"] = []			// array of all visits.
			  var visit = new Object(); 		// visit, representing an
												// individual visit to
												// the node, contains
												// .date and .user.
												// visit is pushed to
												// the node.visitList
												// array.

			 visit.userName;					// many users can
			 visit.date;						// visit. We want all
												// their names. and
												// their times.
			 
			 visit.userName = stripHtml(json[i].Name); 
			 visit.date = (json[i]["Timestamp"]);		

			 node["visitList"].push(visit);

			// everything goes into allNodes.
			 allNodes.push(node);
			
			// if there's already a node with this title in
			// uniqueNodes, don't add it. Otherwise, add the whole
			// node to uniqueNodes. 
			  for(var j = 0; j < uniqueNodes.length; j++) {
				foundNodeFlag = false;
				if(node["name"] == uniqueNodes[j]["name"]){
					uniqueNodes[j].visitList.push(visit);
					foundNodeFlag = true;
					break;
				}
			  }
			  if(!foundNodeFlag){
				uniqueNodes.push(node);
			  }
			 // is it a visitor we haven't seen at all?? if so, add to userNamesColors.
			 // (yes, this array is how we keep track of users). TODO
			 // this is damage from when I was writing maps.js too
			 // fast. Fix after everything works -- userList should
			 // be an array storing user objects, with user objects
			 // having properties .name and .color.
			 foundUserFlag = false;
			 for(var j = 0; j < userNamesColors.length; j++){
				if(userNamesColors[j][0] == visit.userName){
					foundUserFlag = true;
					break;
				}
			}
			if(!foundUserFlag){
				// I'm keeping this just for the sake of the
				// stuff left over from maps. TODO delete or change
				// after it works.
				// selectedUsers.push(visit.userName);

				userNamesColors.push([visit.userName, color(colorsCounter % 20)]);
				colorsCounter++;
			}
		} // we now have allNodes and uniqueNodes populated.

		// --------- BUILD LINKS ------

		// for each user, get a sublist of the allNodes array of nodes they've visited.
		for (var i = 0; i < userNamesColors.length; i++) {
			var visitedByUser = [];
			for (var j = 0; j < allNodes.length; j++) {
				if(allNodes[j].visitList[0].userName == userNamesColors[i][0])
				{
					visitedByUser.push(allNodes[j]);
				}
				
			}
			// we now have a list of nodes visited by one user. 
			// continue by actually building the links for this user and pushing them to 
			// the links array. 

			for (var k = 1; k < visitedByUser.length; k++){
				console.log(i);
				var link  = new Object();
				link.data = new Object();
				link.visitList = [];		// so I can use the same function to filter links and nodes, 
											// the date/userName of the visit is also stored here.
				link.target = visitedByUser[k];
			//	 console.log("link: " + i);
			//	console.log("link.target is: ");
			//	console.log(link.target); 
				link.source = visitedByUser[k - 1];
			//	console.log("link.source is: ");
			//	console.log(link.source); 
				var date = visitedByUser[k].visitList[0].date;
				link.date = date;
				link.data.date = date;
				link.visitList.push(visitedByUser[k].visitList[0]);

				//	HIGH PRIORITY TODO if target.visitList[0].date is too far after
				//	source.visitList[0].date, don't make a link.
				//	HIGH PRIORITY TODO if link and target weren't visited by the same person, 
				// they're not part of anyone's "journey." don't add them to the list of links. 
				if ((link.source.visitList[0].date * 1000 + sessionTimeout > link.target.visitList[0].date * 1000) &&
					(link.source.name != link.target.name) &&
					(link.source.visitList[0].userName == link.target.visitList[0].userName))
					 {

					allLinks.push(link);
				} 
				//console.log(allLinks);

			}
		} // we've stepped through each username
			//console.log(allLinks);
//		console.log(allLinks);
	} // end of jsonParser.

	d3.json("./misc/journeys.json", function(json) {

	//		console.log("testnew");
			// this sets up: uniqueNodes, allLinks
			 jsonParser(json);

			 var links = allLinks;
			 //console.log(links);
			 var nodes = allNodes;
			 console.log(allNodes);

			// console.log(links);
			// console.log(nodes);
			
			// console.log(links);

		var initialWidth  = (settings.config.width || 800),
			initialHeight = (settings.config.height || 800),
		// no longer used
		// userList = settings.config.userList,


		// drawDocumentCircle never makes sense for journeys
		drawDocumentCircle = false; //settings.config.drawDocumentCircle;
		
		var linkedNodesOnly = !drawDocumentCircle;


		// set up the actual width/height to conform to margin
		// convention.
		var width = initialWidth - margin.left - margin.right;
		var height = initialHeight - margin.top - margin.bottom;


		var force = d3.layout.force(height)
		  .size([width, height]);

		var timeout = null; // used in mouseover and mouseout events on
		var delay = 400;	// nodes

	// begin displayTooltip
	 function displayTooltip(d) {

		//console.log(d);
		xPos = d.x;
		yPos = d.y;
		d3.select("#journeys-tooltip")
		.style("left", xPos + 50 + "px") 
		.style("top", yPos + 70 + "px")
			;
		d3.select("#journeys-tooltip")
			.select("#title")
			.text(d.name)
			// get title working, then pull out thisURL
			.attr("href", d.thisURL)
			;

		// create list of times accessed.
		var accessDates = [];
		for (var i = 0; i < d.visitList.length; i++){
			accessDates.push(d.visitList[i].date)
		}
	/*	
		d3.select("#journeys-tooltip")
			.select("#dates")
			.text(function() {
				var textString = "";
				for (var i = 0; i < accessDates.length; i++){

					var date = new Date(accessDates[i] * 1000);

					textString = textString + " "  + date + "\r";
				}
				return textString;
			})
			; */

		d3.select("#journeys-tooltip")
			.classed("hidden", false)
			.on("mouseover", function() {
				d3.select("#journeys-tooltip")
					.classed("hidden", false)
					;
				})
			.on("mouseout", function() {
				d3.select("#journeys-tooltip")
					.classed("hidden", true);
					; 
			}); 
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
	
    force.charge(-300);
    force.distance(50);
    force.gravity(.25);

	// div containing: 
	// 1. various toggleable features (biblio circle... more to come)
	// 2. selectable names of all users who've navigated around the site. 
	var controlPanelDiv = d3.select("#" + settings.id).append("div")
		.classed("controlPanelDiv", true)
		.style("height", "70%")
		.style("width", "200px")
		.style("float", "right")
		;
	
	var controlPanelFontSize = 20;
	var userSelectorSvg = d3.select(".controlPanelDiv").append("svg")
		.attr("id", "userSelectorSvg")
		.attr("height", "80%")
		.attr("width", "200px")
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
	playFromStart.append("circle")
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
			;

	// TODO: arrangeDocumentNodes is now misnamed -- actually - remove from journeys


	// console.log(userNamesColors);

	var userSelectionEnterSelection = userSelectorSvg.selectAll("g.userListItem")
		.data(userNamesColors)
		.enter()
		;

	var foundUserFlag = false;
	// remember that each entry in userNamesColors is an array
	// containing the name at [0] and the associated color at [1]
	var userSelectionGroup = userSelectionEnterSelection.append("g")
			.classed("userListItem", true)
			// unSelected vs. selected because it makes the css
			// slightly less complicated.
			.classed("unSelected", true) 
			// stripping spaces, lest we accidentally assign two ids
			// instead of one.
			.attr("id", function(d) { return d[0].replace(/\s+/g, '')});
	

		userSelectionGroup.on("click", function(d) { 
			foundUserFlag = false;
			for (var i = 0; i < selectedUsers.length; i++){
				// unselect if already selected
				if (selectedUsers[i] == d[0])  {
					selectedUsers.splice(i, 1);
					foundUserFlag = true;
					d3.select("#" + d[0].replace(/\s+/g, ''))
						.classed("unSelected", true);
					break;
				}
			}
			// not found, select.
			if (!foundUserFlag){
				selectedUsers.push(d[0]);
				d3.select("#" + d[0].replace(/\s+/g, ''))
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

	// --- DRAW FORCE DIRECTED DIAGRAM ITSELF.  
	// draw an svg for the graph display, using values from
	// "settings", which is passed in by drupal. the var svg actually
	// ends up referring to a g element within the svg, following bostock's
	// margin convention.
    var svg = d3.select('#' + settings.id).append("svg")
        .attr("width", initialWidth)
        .attr("height", initialHeight)
		.attr("float", "left")
            .on("mouseleave", function() {
              d3.select("#journeys-tooltip")
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

    var brushSvg = d3.select('#' + settings.id).append("svg")
        .attr("width", width)
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

	var allDates = [];

	for (var i = 0; i < allNodes.length; i++){
		allDates.push(allNodes[i].visitList[0].date);
	}


	var firstNode = d3.min(allDates, function(d) 
		{ 
			return d;
		});
	var lastNode  = d3.max(allDates, function(d) {
		 return d;
		 });

	// currently link dates are assigned based on the date of the
	// link's source node, meaning that it's not necessary to check
	// for links before or after the last nodes.
	var startDate = new Date(firstNode * 1000);
	var endDate = new Date(lastNode * 1000); 


	// create time scale used by xAxis
	var timeScale = d3.time.scale()
						.domain([startDate, endDate])
						.range([0 + margin.left, width - margin.right])
					;
	// create axis using time scale and draw it at the bottom of the
	// graph.
	var xAxis = d3.svg.axis();
	xAxis.scale(timeScale)
			.orient("bottom")
			// one tick a week -- subject to change.
			.ticks(d3.time.monday)
			.tickFormat(d3.time.format("%B %e"))
			;
	brushSvg.append("g") 
		.classed("axis", true)
		// move to bottom of graph.
		.attr("transform", "translate(0," + (brushSvgHeight - (margin.bottom)) + ")")
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
		} // end brushPlayFromStart()

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
			// first, get a list of the selected links.

			var selectedLinks = links.filter(inTimeFrame); //.filter(inSelectedUsers);
			// return only those nodes that are either the source
			// or target of at least one link.
			for (var i = 0; i < selectedLinks.length; i++) {
				if (d.id == selectedLinks[i].source.id || d.id == selectedLinks[i].target.id) {
					return true;
				}
			}
			return false;
		}

		// not used in journeys.js -- use visitorSelected instead.
		function inSelectedUsers(d) {
			// see if the visitor is in selectedUsers; if so, it's selected.
			// "author" means visitor TODO change after everything's working.
			for (var i = 0; i < selectedUsers.length; i++) {
				if (d.data.author == selectedUsers[i]) {
					return true;
				}
			}	// didn't find it.
			return false;
		}


		// inTimeFrame only returns nodes where a visit by a selectedUser happens within timeFrame.
		function inTimeFrame(d) {
			var datesList = [];
			for(var i = 0; i < d.visitList.length; i++){

				// times 1000, because js stores dates in milliseconds since epoch, not seconds.
				var date = new Date(d.visitList[0].date * 1000);
				if (date >= timeFrame[0] && date < timeFrame[1]) {
					//console.log("in timeFrame!");
					return true;
				} 
			} // end for loop
			// nothing selected; return false.
			//console.log("not in timeFrame!");
			return false;
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
		gBrush.selectAll("rect")
						.attr("height", 25 )
						.attr("y", brushSvgHeight - margin.bottom * 1.5)
						;

		function redrawGraph() {
			filteredNodes = [];
			filteredLinks = [];
			// inTimeFrame now filters by user itself.
			filteredNodes = nodes.filter(inTimeFrame).filter(inSelectedUsers); 
			if (linkedNodesOnly) {
				filteredNodes = filteredNodes.filter(isLinked);
			}
			filteredLinks = links.filter(inTimeFrame).filter(inSelectedUsers);
			//console.log(filteredLinks);
			//start(filteredNodes, filteredLinks);
			start(filteredNodes, filteredLinks);
		}

		
		// here's where the magic happens -- actually draws nodes and
		// links to the svg.
		function start(startNodes, startLinks) {
			//console.log("startNodes: ");
			//console.log(startNodes);
			//console.log("startLinks: ");
			//console.log(startLinks);

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
				  .attr("class", "response")
				  .attr("fill", function(d) {
					for(var i = 0; i < userNamesColors.length; i++){
						if(userNamesColors[i][0] == d.data.author){
							return userNamesColors[i][1];
						}
					} // didn't find it
					return "green";
				  })
				  .attr("r", function(d) { return (d.data.d) ? d.data.d : 7; })
				  // Display tooltip div on mouseover, after 1 second delay.
				  .on("mouseover", function(d) {
					  timeout = setTimeout(function() {displayTooltip(d);}, delay);

					// Hide tooltip on mouseout. Also clear any active timers
					// -means the tooltip doesn't display unless you hover for one
					// second.
				  })
				 .on("mouseout", function() {
					clearTimeout(timeout);
					d3.select("#journeys-tooltip")
						.classed("hidden", true);
				})
					;

				node.attr("class", "response")
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
					for (var i = 0; i < uniqueNodes.length; i++)
					{
						// biblio nodes are fixed if we're using the circle layout.
						if (uniqueNodes[i].data.itemType == "biblio") {
							if (drawDocumentCircle)
								uniqueNodes[i].fixed = true;
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
					for (var i = 0; i < uniqueNodes.length; i++) {
						if(uniqueNodes[i].data.itemType == "biblio")
						{
							uniqueNodes[i].px = backgroundCx + (Math.cos(theta * biblioCount) * backgroundR);
							uniqueNodes[i].py = backgroundCy + (Math.sin(theta * biblioCount) * backgroundR);
							biblioCount--;
						}
					}
			} else { // not drawing document circle; make sure biblio
					 //nodes are unfixed
				for (var i = 0; i < uniqueNodes.length; i++) {
					uniqueNodes[i].fixed = false;
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

			 });
	}
})(jQuery);




