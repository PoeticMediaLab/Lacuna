/*
    Display a heatmap of annotations
    Note: this code is not as loosely coupled as it could be
    Depends on knowing about the classes used by Annotator Filters and Page Turner

    Original code: Rhea Pokorny
    Drupal integration: Mike Widner <mikewidner@stanford.edu>
 */
(function ($) {
    'use strict';
    Drupal.behaviors.heatmap = {
        attach: function (context, settings) {
            // finds the next node to check. If the lCount>= increment it will return the element itself
            // Note: this is a recursive function
            function findNext(curN, lCount) {
                //if lCount is bigger than the increment (meaning that it is between the increment and error bounds) return this element
                if (lCount >= increment - error || curN == articleNode) return curN;

                //options for element nodes (text nodes do not have classLists or children)
                if (curN.nodeType == Node.ELEMENT_NODE) {
                    //if not checked, return element
                    if (checked.indexOf(curN) == -1) return curN;

                    //if not all the child nodes have been checked and the element has child nodes, look at the first child
                    //note: there will never be the case where function refers to the parent when only some of their children have been checked
                    if (done.indexOf(curN) == -1 && curN.childNodes.length > 0) return curN.childNodes[0];
                }

                //check next to see if text/element node has a sibling
                if (curN.nextSibling != null) return curN.nextSibling;

                //if not, add "done" to the parent because all children have been checked, find next
                done.push(curN.parentNode);
                return findNext(curN.parentNode);
            }

            //counts the annotations up to the increment
            function getIncrementDensity(curN, lCount, anCount) {
                //if current node is the article node then back at the beginning or if increment is full
                //return object: density: # of annotations, node: current node being examined, overflow: amount that text node went over increment
                if (curN == articleNode || lCount >= increment - error) return {density: anCount, node: curN, overflow: lCount - increment};

                //if a text node, will always add to increment even if overflow
                if (curN.nodeType == Node.TEXT_NODE) {
                    lCount += curN.length;
                } else {
                    // indicate that element node has been visited.
                    checked.push(curN);

                    // adds one to annotation count if it is an annotation element
                    // Only include currently active annotations
                    // Annotation Filters hides them with the 'af-annotation-hide' class
                    if (curN.tagName == "SPAN" &&
                        curN.classList.contains('annotator-hl') &&
                        !curN.classList.contains('af-annotation-hide'))
                    {
                        anCount++;
                    }

                    //if the whole text associated with the element can fit into the increment, adds
                    if (curN.textContent.length + lCount <= increment + error) {
                        // TODO: fix this; it won't work because we need only specific spans
                        var numAnEl = document.querySelectorAll('span.annotator-hl').length;
                        //var numAnEl = document.evaluate('count(.//span)', curN, null, XPathResult.ANY_TYPE, null).numberValue;
                        anCount += numAnEl;
                        lCount += curN.textContent.length;
                        done.push(curN);
                    }
                }
                var next = findNext(curN, lCount);
                return getIncrementDensity(next, lCount, anCount);
            }

//counts the annotations associated with a particular node by counting the number of direct ancestors that are annotations
            function countAnnotations(curN) {
                var count = 0;
                var node = curN;
                while (node != null && node != articleNode) {
                    if (node.nodeType != Node.TEXT_NODE &&
                        node.tagName == "SPAN" &&
                        node.classList.contains('annotator-hl') &&
                        !node.classList.contains('af-annotation-hide'))
                    {
                        count++;
                    }
                    node = node.parentNode;
                }
                return count;
            }

            function calculateDensity() {
                var i,
                    currentNode = articleNode.childNodes[0];
                aDen = [], done = [], checked = [];
                lCount = 0, anCount = 0;
                for (i = 0; i < width; i++) {
                    currentNode = findNext(currentNode);
                    if (currentNode == articleNode) break;

                    var entry = getIncrementDensity(currentNode, lCount, anCount);
                    currentNode = entry.node;
                    aDen.push(entry.density); //push density to array

                    lCount = (entry.overflow >= error) ? entry.overflow : 0; //reset lCount
                    anCount = (lCount > 0) ? countAnnotations(currentNode) : 0; //if element also exists in next, reset to associated annotations
                }
            }

            function setupChart() {
                var graphH = (horizontal) ? height : width;
                var graphW = (horizontal) ? width : height;
                d3.select(svgContainer)
                    .attr('width', graphW)
                    .attr('height', graphH);
                ;

                //creates a group element to contain all the rectangles in the bar chart. if horizontal, rotates the elements
                var chart = d3.select(svgContainer).insert('g', ':first-child')
                    .attr('transform', function () {
                        if (horizontal) return 'rotate(0)'
                        else return 'translate(0, -50) rotate(90, 0, 50)';
                    });

                barWidth = width / aDen.length; //making up for the fact that aDen can vary in length
                //use first if you want
                colors = d3.scale.linear()
                        //   .domain([0, d3.max(aDen)])
                        //   .range(['#FFFFFF', '#191970'])
                        .domain([0, 2, 6, 10, d3.max(aDen)])
                        .range(["#eff3ff","#bdd7e7","#6baed6","#3182bd","#08519c"]) // colorbrewer blues
                //.range(['#FFFFFF', '#ADD8E6', '#4169E1', '#0000FF', '#191970']);
                    ;

                //use first domain and range if you want a perfectly scaled bar chart
                yScale = d3.scale.linear()
                    //.domain([0, d3.max(aDen)])
                    //.range([0, height])
                    .domain([0, 2, 6, 10, d3.max(aDen)])
                    .range([0, height / 2, height, height * 2, height * 4]);

                return chart;
            }

            function updateChart() {
                var heatmap = chart.selectAll('rect.heatmap')
                    .data(aDen);

                heatmap.enter().append('rect')
                    //.style('fill', colors)
                    .style('fill', 'black')
                    .classed('heatmap', true)
                    .attr('width', function (d) {
                        return barWidth;
                    })
                    .attr('x', function (d, i) {
                        return barWidth * i;
                    })
                    //if no bar chart, replace function with graphH
                    .attr('height', function (d) {
                        return yScale(d);
                    })
                    //if no bar chart, replace function with 0
                    .attr('y', function (d) {
                        return height - yScale(d);
                    })
                ;
                heatmap.exit().remove();
            }

            // Note: height/width refer to graph as if it was horizontal
            var height = 50,
                width = 900, //also length of aDen array
                error = 5, //how much over or under the increment allowed
                extra = -6, //can play around to get closer to 900 entries
                incrementScale = 4, // bigger scale = bigger bar width
                horizontal = true, //switch
                // xpath to select the annotated content
                articlePath = '//body[1]/div[1]/div[1]/div[1]/article[1]/div[1]/div[1]/div[1]/div[1]',
                pageContainer,
                articleNode, //article node = node where content starts
                aDen = [], // array of density of annotations in each increment
                increment, // increment is ~length of the text divided into "width" increments
                lCount = 0, //represents how much text has been included so far
                anCount = 0, //represents the number of annotations included so far
                locationSelectors = ['page-turner-nav-parent', 'content'], // where to place the heatmap
                svgContainer,
                chart,
                checked, // array to store all the checked nodes
                done,   // array to store all the done parent nodes
                barWidth, // width of bars in chart
                colors,  // color scale for chart
                yScale  // y-axis scale for bar heights
                ;

            svgContainer = context.getElementById(locationSelectors[0]);
            if (!svgContainer) {
                svgContainer = context.getElementById(locationSelectors[1]);
            }
            width = svgContainer.offsetWidth;
            pageContainer = document.evaluate(articlePath, document, null, XPathResult.UNORDERED_NODE_ITERATOR_TYPE, null);
            articleNode = pageContainer.iterateNext();
            increment = incrementScale * Math.round(articleNode.textContent.length / width) + extra;

            calculateDensity();
            checked.push(articleNode);
            //articleNode.classList.add("checked");
            chart = setupChart();
            updateChart();

            $(document).bind('annotation-filters-changed', function () {
                calculateDensity();
                updateChart();
            });
        }
    }
})(jQuery);