(function ($) {
    // Make collapsible side bars
    // Mike Widner
	$('div#block-menu-menu-left-menu h2').click(function() {
	console.log('click');
        $(this).parent().children().animate({
            width: 'toggle',
            direction: 'left'
        }, 5000, 'swing');
    });
}) (jQuery);
