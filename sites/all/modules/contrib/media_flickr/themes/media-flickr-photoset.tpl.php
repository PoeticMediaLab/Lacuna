<?php

/**
 * @file
 * Template file for theme('media_flickr_photoset');
 */
?>
<object width="<?php print $width; ?>" height="<?php print $height; ?>"> <param name="flashvars" value="<?php print $flashvars; ?>"></param> <param name="movie" value="http://www.flickr.com/apps/slideshow/show.swf?v=104087"></param> <param name="allowFullScreen" value="true"></param><embed type="application/x-shockwave-flash" src="http://www.flickr.com/apps/slideshow/show.swf?v=104087" allowFullScreen="true" flashvars="<?php print $flashvars; ?>" width="<?php print $width; ?>" height="<?php print $height; ?>"></embed></object>
