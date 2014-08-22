(function ($) {
  Drupal.behaviors.MMextra = { 
    attach: function(context,settings) {
      $('ul.menu li').click(function(){
        window.location.href = $(this).children('a').first().attr('href');
      });
      $('ul.menu li a').click(function(e){
        e.stopProgagation();
      });
      
      //Adding classes to menu items for coloring. This is a hack, but I haven't yet thought
      //of a better way within drupal to do this...
      /*$("#block-menu-menu-top-right .content .menu li a").each(function(index){
        var menu_text = $(this).text();
        switch(menu_text)
        {
        case "Topics":
          $(this).addClass("lacuna-color-orange");
          break;
        case "Sewing Kit":
          $(this).addClass("lacuna-color-light-blue");
          break;
        case "Help":
          $(this).addClass("lacuna-color-purple");
          break;
        case "My Account":
          $(this).addClass("lacuna-color-green");
          break;
        case "Logout":
          $(this).addClass("lacuna-color-light-grey");
          break;
        default:
          $(this).addClass("lacuna-color-light-grey");
        }
      });
      $("#block-menu-menu-left-menu .content .menu li a").each(function(index){
        var menu_text = $(this).text();
        switch(menu_text)
        {
        case "Documents":
          $(this).addClass("lacuna-color-orange");
          break;
        case "Responses":
          $(this).addClass("lacuna-color-light-blue");
          break;
        case "Bibliography":
          $(this).addClass("lacuna-color-light-grey");
          break;
        case "Your Story":
          $(this).addClass("lacuna-color-purple");
          break;
        case "Forum":
          $(this).addClass("lacuna-color-dark-blue");
          break;
        case "Wiki":
          $(this).addClass("lacuna-color-green");
          break;
        default:
          $(this).addClass("lacuna-color-light-grey");
        }
      });*/
      
      //$('.page-forum #page-title').after('<a href="../node/add/forum/1" class="lacuna-button lacuna-button-blue">Make new topic</a>');
      
      /*var color_array_menu_top=["orange","light-blue","dark-blue","green","purple","light-grey"];
      $("#block-menu-menu-top-right .content .menu li a").each(function(index){
        $(this).addClass("lacuna-color-"+color_array_menu_top[index%color_array.length]);
      });
      var color_array_menu_left=["orange","light-blue","dark-blue","light-grey","green","purple"];
      $("#block-menu-menu-left-menu .content .menu li a").each(function(index){
        $(this).addClass("lacuna-color-"+color_array_menu_left[index%color_array.length]);
      });*/      
    }
  };
}) (jQuery);
