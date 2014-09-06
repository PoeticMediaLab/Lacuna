(function ($) {  

	Drupal.behaviors.annotator_test = {

		attach: function (context, settings) {
			Drupal.Annotator = $(Drupal.settings.annotator.element).annotator();
			$('.content').click(function(){
				$(this).find('.annotator-adder').css('display', 'inline');

			});

		}

	}

})(jQuery);