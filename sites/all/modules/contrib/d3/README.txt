Welcome to the Drupal D3 module!

USING THE API
=============
- Download d3 library and install it into your libraries module.
  Latest version can be found at https://github.com/mbostock/d3/wiki
  To download the library using the provided example makefile and drush, use:
  drush make --no-core d3.make.example
  If you're creating a distribution, simply copy the example makefile
  into your own makefile.
- Enable d3 module and dependencies
- If you're not familiar with the API, see the d3_examples module
  for various code examples of the d3 API.

CUSTOM LIBRARY
==============
Instructions on how to create a new custom d3 library:
- In your sites libraries folder (e.g. sites/all/libraries) create a new
  directory for your library with the prefix d3. (e.g. d3.mylibrary).
- Create your .info file.
  @see libraries.api.php for information on parameters.
- Use javascript enclosure around your js code, and extend the global Drupal.d3
  variable using your unique library name. E.g. 
  @code
    (function($) {

      Drupal.d3.mylibraryname = function (select, settings) {
        // javascript code
      }
    })(jQuery);
  @endcode
- In your d3_draw API call, set 'type' => 'libraryname'.
- Any variable you include in the d3_draw() arguments, will be included in
  the settings variable. For example:
  @code
    $args = array(
      'type' => 'myviz',
      'id' => 'testvis',
      'foo' => 'bar',
    );
    return d3_draw($args);
  @endcode

  Inside your js function, 'foo' will be available as settings.foo.

GRAPHAPI
========
The d3 module comes with support for the graphapi module.
http://drupal.org/project/graphapi

Instructions on how to use d3 with graphapi:

- Enable graphapi, and set d3 as the engine in the api call. 
- An example of a graphapi call, using d3, is also available in
  the d3_examples module.

VIEWS
=====
All support for views is handled in the d3_views module.

Instructions on how to use d3 in views:
- Enable the d3_views module.
- Create the view you'd like to render with d3.
  The view must have fields.
- Under "Format", choose "D3 Visualization".
- Click "Settings".
- Choose which library you'd like to use for this particular view. If
  you are creating your own custom D3 library, and you'd like to integrate
  it with views, make sure in the info file you include views = [version #].
- Select which fields you want to use for display, (i.e. on an axis),
  and which fields you'd like to use for values, (i.e. a bar or line value). 
