/* Provide autocompleted, categorized tags in Annotator window
// @see https://github.com/openannotation/annotator/issues/92#issuecomment-3985124
// @see https://jqueryui.com/autocomplete/#multiple-remote
// @see https://jqueryui.com/autocomplete/#categories
//
// Mike Widner <mikewidner@stanford.edu>
*/
(function ($) {
  Drupal.behaviors.annotatorTags = {
    attach: function (context, settings) {
      Drupal.Annotator.annotator('addPlugin', 'Tags');
      // Note: split needs to match parseTags() in tags.coffee
      function split( val ) {
        return val.split( /,\s*/ );
      }
      function extractLast( term ) {
        return split( term ).pop();
      }

      if (typeof Drupal.Annotator.data('annotator') !== 'undefined') {
        Drupal.Annotator.data('annotator').plugins.Tags.input.catcomplete({
            minLength: 0,
            delay: 0,
            // source: Drupal.settings.annotator_tags,
            source: function( request, response ) {
              // TODO: Create filter callback
              // https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Array/filter
              // Get new data object
              // check list from split(this.value)
              // Pass it to catcomplete
              // var data = Drupal.settings.annotator_tags.filter(
              //   function( val ) {

              //   });
              // response(data);
              response( $.ui.autocomplete.filter(
                Drupal.settings.annotator_tags.tags, extractLast( request.term ) )
              );
            },
            select: function( event, ui ) {
              var terms = split( this.value );
              // remove the current input
              terms.pop();
              // add the selected item
              terms.push( ui.item.value );
              // add placeholder to get the comma-and-space at the end
              terms.push( "" );
              this.value = terms.join( ", " );
              return false;
            },
        })
          .focus(function () {
              $(this).catcomplete("search", "");
            });
      }
    }
  };
})(jQuery);
