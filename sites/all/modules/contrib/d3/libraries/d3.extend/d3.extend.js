/**
 * @file
 * Extends d3 with helper functions.
 */

/**
 * helper function to adjust Y axis based on how many text lines
 */
d3.tileText = function(str, w) {
  this.y = (!this.y) ? 0 : this.y;

  var store = this.y;
  this.y += d3.splitString(str, w).length * 25;
  return store;
}
/**
 * helper function to split a text string into an array based on a length
 */
d3.splitString = function(str, w) {
  var strArray = str.split(" ");
  var endArray = [];
  var pos = 0;

  for(var i = 0; i < strArray.length; i++) {
    if (!endArray[pos]) {
      endArray[pos] = "";
    }

    if (endArray[pos].length + strArray[i].length + 1 <= w) {
      endArray[pos] = [endArray[pos],strArray[i]].join(" ");
    }
    else {
      pos++;
      endArray[pos] = strArray[i];
    }
  }

  return endArray;
}

/**
 * Helps create blocks of text that word wrap correctly using font size.
 * 
 * @param string str
 *   String to split into multiple text elements.
 * @param number w
 *   Maximum width of a line in pixels
 * @param function addText
 *   Adds another text element to the document.
 *   @param object currentText
 *     Object containing the current text element's svg object.
 *   @param int totalBoxes
 *     The total number of boxes currently displayed.
 *   @returns object currentText
 *     Returns the new text element's svg object.
 * @returns int totalBoxes
 *   The total number of boxes used to display the string.
 */
d3.svgSplitString = function(str, w, addText) {
  var text = str.split(" ");
  var pos = 0;
  var box;
  var total = 0;
  while (pos < text.length) {
    if (!box) {
      box = addText(box, total);
      total++;
    }
    var old_HTML = box.textContent;
    box.textContent += ' ' + text[pos];
    var length = box.getComputedTextLength();
    if (length > w) {
      box.textContent = old_HTML;
      box = addText(box, total);
      box.textContent = text[pos];
      total++;
    }
    pos++;
  }
  return total;
}

/**
 * Provides a maximum width that a text box should be, and iterates from the
 * end of the text value (textContent) to the beginning until the width matches
 * the parameter.
 *
 * @param int|function value 
 *   Either a dynamic function that calculates a width, or a static number.
 *
 * @return none.
 */
d3.selection.prototype.ellipsis = function(value) {
  return arguments.length ? this.each(typeof value === "function" ? function() {
    // If a dynamic function was passed
  } : value == null ? function() {
    this.textContent = "";
  } : function() {
    // If this is just a static value and not a function

    // Do not do anything if this is already the right length.
    if (this.getComputedTextLength() > value) {
      // Starting string.
      this.textContent += '...';
      // Index of the last character of the string (without the ...).
      var index = this.textContent.length - 3;
      while (this.getComputedTextLength() >= value) {
        // Shrink string by one character, and add in again the ellipsis.
        this.textContent = this.textContent.substr(0, index) + '...';
        index--;
      }
    }
  }) : this.node().textContent;
}

/**
 * Takes a text element, and adds ellipses if it goes over a certain length.
 *
 * @param string str
 *   The string to display
 * @param svgObject box
 *   The text element that the text will go into.
 * @param float width
 *   The maximum width of the text element.
 *
 * @return none.
 */
d3.ellipses = function(str, box, width) {
  box.textContent = str;
  if (box.getComputedTextLength() > width){
    var index = 0;
    var text = '';
    var elipses = '...';
    box.textContent = text + elipses;
    var oldContent;
    while (box.getComputedTextLength() <= width) {
      text += str[index];
      index += 1;
      var oldContent = box.textContent;
      box.textContent = text + elipses;
    }
    if (oldContent) {
      box.textContent = oldContent;
    }
  }
}
