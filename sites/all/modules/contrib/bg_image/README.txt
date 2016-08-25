BACKGROUND IMAGE
----------------

In the simplest terms, Background Image provides tools to add background images to pages using the css "background" property. An exisiting content type with an image or media field, can be used as the interface to manage the images, but is not required. Modules implementing bg_image can use their own interface for image uploads if they don't want to bother with nodes.

The content type, as well as the default css settings can be set on the Background Image configuration page (admin/config/content/background-image).


Configuration Page
------------------

On the configuration page, you can configure which content type and field to use for managing the images. You can also provide default css settings for the css selector as well as each css "background" property.


Adding a Background Image
-------------------------

Once the settings have been configured, you can add a background image two different ways:

a) If you know the path of the image, you can just call bg_image_add_background_image($path, $css_settings) where $path is the path to the image, and $css_settings is an array css settings (see below for description)

b) If you're using nodes to manage the images you can call bg_image_add_background_image_from_node($nid, $css_settings) where $nid is the node id and $css_settings is an array css settings (see below for description)

  - $css_settings: An array of css settings with any or all of the following keys:
      bg_image_selector: (string) The css selector to use
      bg_image_color: (string) The background color formatted as any valid css color format (e.g. hex, rgb, text, hsl) http://www.w3schools.com/css/pr_background-color.asp
      bg_image_x: (string) The horizontal alignment of the background image formatted as any valid css alignment. http://www.w3schools.com/css/pr_background-position.asp
      bg_image_y: (string) The vertical alignment of the background image formatted as any valid css alignment. http://www.w3schools.com/css/pr_background-position.asp
      bg_image_attachment: (string) The attachment setting for the background image. http://www.w3schools.com/css/pr_background-attachment.asp
      bg_image_repeat: (string) The repeat settings for the background image. http://www.w3schools.com/css/pr_background-repeat.asp
      bg_image_important: (boolean) Add !important to the background property to help override any other background images added in the theme. <link to w3schools>
      bg_image_background_size: (string) The CSS3 size property to use for the background image.
      bg_image_background_size_ie8: (boolean) Use a workaround for IE using Internet Explorer's built-in filters (http://msdn.microsoft.com/en-us/library/ms532969%28v=vs.85%29.aspx). Sometimes it works well, sometimes it doesn't. Use at your own risk
      bg_image_media_query: (string) The media query to use, if at all. E.G. 'all' or 'screen'.
    The default values will be used for any settings not provided.

After calling the function, a css statement will be concatenated, using the path of the image on the node and the css settings provided, and added to the page:

@code
bg_image_selector {
  background: bg_image_color url(image_path) bg_image_attachment bg_image_repeat bg_image_x bg_image_y bg_image_important;
}
@endcode

Using some real settings:

@code
$nid = 1; // Let's pretend this node has an image stored in /sites/default/files/image.jpg
$css_settings = array(
  'bg_image_selector' => 'body #main',
  'bg_image_color' => 'transparent',
  'bg_image_x' => 'center',
  'bg_image_y' => 'center',
  'bg_image_attachment' => 'fixed',
  'bg_image_repeat' => 'no-repeat',
  'bg_image_important' => TRUE,
);
bg_image_add_background_image($nid, $css_settings);
@endcode

The above php code would output the following css:

@code
body #main {
  background: transparent url(http://example.com/sites/default/files/image.jpg) fixed no-repeat center center !important;
}
@endcode
