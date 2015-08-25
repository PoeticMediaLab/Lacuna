$ = jQuery;

$.widget( "custom.catcomplete", $.ui.autocomplete, {
    _create: function() {
      this._super();
      this.widget().menu( "option", "items", "> :not(.ui-autocomplete-category)" );
    },
    _renderMenu: function( ul, items ) {
        var that = this,
            currentCategory = "",
            categoryLabels = Drupal.settings.annotator_tags.flagged;
      $.each( items, function( index, item ) {
        var li;
          if (typeof(item.flagged) == 'undefined') {
              item.flagged = 0;
          }
          item.category = categoryLabels[item.flagged];
        if ( item.category != currentCategory ) {
          ul.append( "<li class='ui-autocomplete-category'>" + item.category + "</li>" );
          currentCategory = item.category;
        }
        li = that._renderItemData( ul, item );
        if ( item.category ) {
          li.attr( "aria-label", item.category + " : " + item.label );
          $(li).addClass('annotator-tags-item');
        }
      });
    }
  });
