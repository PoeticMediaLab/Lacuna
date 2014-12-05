/**
 * @file
 * A JavaScript file for the theme.
 *
 * In order for this JavaScript to be loaded on pages, see the instructions in
 * the README.txt next to this file.
 */

// JavaScript should be made compatible with libraries other than jQuery by
// wrapping it with an "anonymous closure". See:
// - https://drupal.org/node/1446420
// - http://www.adequatelygood.com/2010/3/JavaScript-Module-Pattern-In-Depth
(function ($, Drupal, window, document, undefined) {
// To understand behaviors, see https://drupal.org/node/756722#behaviors
Drupal.behaviors.my_custom_behavior = {
  attach: function(context, settings) {

$(document).ready(function() {
	// Tooltip only Text
// 	$('img').hover(function(){
//         // Hover over code
//         var title = $(this).attr('title');
//         console.log(title)
//         $(this).data('tipText', title).removeAttr('title');
//         $('<p class="tooltip"></p>')
//         .text(title)
//         .appendTo('body')
//         .fadeIn('slow');
// 	}, function() {
// 	    // Hover out code
// 	    $(this).attr('title', $(this).data('tipText'));
// 	    $('.tooltip').remove();
// 		}).mousemove(function(e) {
// 	        var mousex = e.pageX + 20; //Get X coordinates
// 	        var mousey = e.pageY + 10; //Get Y coordinates
// 			$('.tooltip')
// 			.css({ top: mousey, left: mousex })
// 		});
// });

// $(document).ready(function() {
// 	$('img').hover(function() {
// 		$('img').hide();
//         var title = $(this).attr('title');
//         console.log(title)

// 	});
// });







// 	$(window).load(function() {
// 	    // $outer_container=$("#outer_container");
// 	    $imagePan_panning=$("#imagePan .panning img");
// 	    $imagePan=$("img");
// 	    $imagePan_container=$("#imagePan .container img");
	 
// 	    $imagePan_panning.css("margin-top",($imagePan.height()-$imagePan_panning.height())/2+"px");
// 	    containerWidth=$imagePan.width();
// 	    containerHeight=$imagePan.height();
// 	    totalContentW=$imagePan_panning.width();
// 	    totalContentH=$imagePan_panning.height();
// 	    $imagePan_container.css("width",totalContentW).css("height",totalContentH);
	 
// 	    function MouseMove(e){
// 	        var mouseCoordsX=(e.pageX - $imagePan.offset().left);
// 	        var mouseCoordsY=(e.pageY - $imagePan.offset().top);
// 	        var mousePercentX=mouseCoordsX/containerWidth;
// 	        var mousePercentY=mouseCoordsY/containerHeight;
// 	        var destX=-(((totalContentW-(containerWidth))-containerWidth)*(mousePercentX));
// 	        var destY=-(((totalContentH-(containerHeight))-containerHeight)*(mousePercentY));
// 	        var thePosA=mouseCoordsX-destX;
// 	        var thePosB=destX-mouseCoordsX;
// 	        var thePosC=mouseCoordsY-destY;
// 	        var thePosD=destY-mouseCoordsY;
// 	        var marginL=$imagePan_panning.css("marginLeft").replace("px", "");
// 	        var marginT=$imagePan_panning.css("marginTop").replace("px", "");
// 	        var animSpeed=500; //ease amount
// 	        var easeType="easeOutCirc";
// 	        if(mouseCoordsX>destX || mouseCoordsY>destY){
// 	            $imagePan_container.stop().animate({left: -thePosA-marginL, top: -thePosC-marginT}, animSpeed,easeType); //with easing
// 	        } else if(mouseCoordsX<destX || mouseCoordsY<destY){
// ］	            $imagePan_container.stop().animate({left: thePosB-marginL, top: thePosD-marginT}, animSpeed,easeType); //with easing
// 	        } else {
// 	            $imagePan_container.stop();
// 	        }
// 	    }
	 
// 	    $imagePan_panning.css("margin-left",($imagePan.width()-$imagePan_panning.width())/2).css("margin-top",($imagePan.height()-$imagePan_panning.height())/2);
	 
// 	    $imagePan.bind("mousemove", function(event){
// 	        MouseMove(event);
// 	    });
	// });

	// $(window).resize(function() {
	//     $imagePan.unbind("mousemove");
	//     $imagePan_container.css("top",0).css("left",0);
	//     $(window).load();
	// });


    // Place your code here.

  }
};


})(jQuery, Drupal, this, this.document);
