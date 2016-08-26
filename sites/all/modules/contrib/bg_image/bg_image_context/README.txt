## BACKGROUND IMAGE CONTEXT ##

This module defines a new context reaction called "Background Image" which will let you change the background image based on any criteria you can craft with context's conditions.

## Requirements ##

This module part of the background images project and is included with bg_image and bg_image_ui. It requires bg_image in order to work.

Background Image Context uses nodes as the interface for managing images. This means that you have to have a content type with an image upload field set up already, and have that content type (and image field) configured on the bg_image settings page. See the bg_image module's README.txt file for more information.

## Usage ##

Once you've configured Background Image, all you need to do is create a context and add the reaction 'Background Image'. You may need to clear the cache before the reaction becomes available in the reaction list. There will be a select list with all the nodes of the specified type to choose from. Additionally you can override any css setting here as well. The css settings will be concatenated to create a css statement using the "background" property. More information on this can be found in the bg_image module's README.txt file.

If you want, you can also set a weight for the background image. The weight helps the module decide which background image to use if there are overlapping contexts. Useful if you want to setup a default image as a site-wide context, and have other more specific contexts override it.