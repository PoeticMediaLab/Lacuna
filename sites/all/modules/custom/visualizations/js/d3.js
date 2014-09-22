/**
 * @file
 * Integrates d3 library and functionality with D7 core javascript
 */

(function($, Drupal) {

  /**
   * Global object for holding d3 internal and visualization style methods.
   */
  Drupal.d3 = {
    draw: function(element, settings) {
      // Invoke JavaScript library function, if it exists.
      if (Drupal.d3[settings.type]) {
        Drupal.d3[settings.type](element, settings);
      }
    }
  };

  /**
   * Drupal behaviors for D3 module.
   */
  Drupal.behaviors.d3 = {
    attach: function(context, settings) {
      var id, $context = $(context);
      // Check to see if there are visualizations that have been set.
      if (settings.d3 && settings.d3.inventory) {
        // Iterate over each of the visualizations set in inventory.
        for (id in settings.d3.inventory) {
          // Only process the visualization once, if it exists.
          $context.find('#' + id).once('d3', function () {
            Drupal.d3.draw(id, settings.d3.inventory[id]);
          });
        }
      }
    }
  };

})(jQuery, Drupal);
