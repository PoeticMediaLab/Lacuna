BACKGROUND IMAGE UI (bg_image_ui)
---------------------------------------

This module provides an interface to apply background images 
on specific pages.


Dependencies
------------

This module depends on the background images (bg_image)
module.

Configuration
-------------

bg_image_ui uses nodes as the interface for managing images. 
This means that you have to have a content type with
an image upload field set up already, and have that content
type (and image field) configured on the bg_image settings page.
See the bg_image module's README.txt file for more information.

Also, The default css settings on the bg_image settings page 
will be used to apply the background image so double check that
that is set up properly as well.


Usage
-----

The background image paths administration page can be found at
admin/content/background-images.

Here, you can pair up a path with a node. When that path is
reached, the node's image field will be used to apply a css
background image on the page (using the bg_image default css
settings)

Paths can contain wildcards by using the asterix (*) symbol.
For example the path node/* can be used to match any path that
starts with node/ (i.e. node/1).

Only one background image will be applied to a page at a time.
In the case that two paths overlap (for example, an item with
the path "node/*" and another one with the path "node/1") the
item appearing higher in the list will take precedence. The
table is draggable to allow for easy sorting of items.
