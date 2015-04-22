<?php

/**
 * @file
 * Default provider configuration for the most popular resource providers.
 */

/**
 * Implements hook_default_media_oembed_provider().
 */
function media_oembed_default_media_oembed_provider() {
  $providers = array();

  $provider = new stdClass();
  $provider->disabled = FALSE; /* Edit this to true to make a default provider disabled initially */
  $provider->api_version = 1;
  $provider->name = 'deviantart';
  $provider->admin_title = 'Deviantart';
  $provider->admin_description = 'DeviantArt is an online community showcasing various forms of user-made artwork.';
  $provider->endpoint = 'http://backend.deviantart.com/oembed';
  $provider->scheme = 'http://*.deviantart.com/art/*
https://*.deviantart.com/art/*
http://*.deviantart.com/*#/d*
https://*.deviantart.com/*#/d*
http://fav.me/*
http://sta.sh/*';
  $providers['deviantart'] = $provider;

  $provider = new stdClass();
  $provider->disabled = FALSE; /* Edit this to true to make a default provider disabled initially */
  $provider->api_version = 1;
  $provider->name = 'flickr';
  $provider->admin_title = 'Flickr';
  $provider->admin_description = 'Flickr is an image hosting and video hosting website, and web services suite.';
  $provider->endpoint = 'http://www.flickr.com/services/oembed/';
  $provider->scheme = 'http://*.flickr.com/*
https://*.flickr.com/*
http://flickr.com/*
https://flickr.com/*
http://flic.kr/*
https://flic.kr/*';
  $providers['flickr'] = $provider;

  $provider = new stdClass();
  $provider->disabled = FALSE; /* Edit this to true to make a default provider disabled initially */
  $provider->api_version = 1;
  $provider->name = 'hulu';
  $provider->admin_title = 'Hulu';
  $provider->admin_description = 'Hulu is a website and over-the-top (OTT) subscription service offering ad-supported on-demand streaming video of TV shows, movies, webisodes and other new media, trailers, clips, and behind-the-scenes footage from NBC, Fox, ABC, TBS, WWE, and many other networks and studios.';
  $provider->endpoint = 'http://www.hulu.com/api/oembed.xml';
  $provider->scheme = 'http://www.hulu.com/watch/*
https://www.hulu.com/watch/*';
  $providers['hulu'] = $provider;

  $provider = new stdClass();
  $provider->disabled = FALSE; /* Edit this to true to make a default provider disabled initially */
  $provider->api_version = 1;
  $provider->name = 'ifttt';
  $provider->admin_title = 'IFTTT';
  $provider->admin_description = 'IFTTT is a service that enables users to connect different web applications (e.g., Facebook, Evernote, Weather, Dropbox, etc.) together through simple conditional statements known as "Recipes".';
  $provider->endpoint = 'http://www.ifttt.com/oembed/';
  $provider->scheme = 'http://ifttt.com/recipes/*
https://ifttt.com/recipes/*';
  $providers['ifttt'] = $provider;

  $provider = new stdClass();
  $provider->disabled = FALSE; /* Edit this to true to make a default provider disabled initially */
  $provider->api_version = 1;
  $provider->name = 'instagram';
  $provider->admin_title = 'Instagram';
  $provider->admin_description = 'Instagram is an online photo-sharing, video-sharing and social networking service that enables its users to take pictures and videos, apply digital filters to them, and share them on a variety of social networking services, such as Facebook, Twitter, Tumblr and Flickr.';
  $provider->endpoint = 'http://api.instagram.com/oembed';
  $provider->scheme = 'http://instagram.com/p/*
https://instagram.com/p/*
http://instagr.am/p/*
https://instagr.am/p/*';
  $providers['instagram'] = $provider;

  $provider = new stdClass();
  $provider->disabled = FALSE; /* Edit this to true to make a default provider disabled initially */
  $provider->api_version = 1;
  $provider->name = 'nfb';
  $provider->admin_title = 'National Film Board of Canada';
  $provider->admin_description = 'The National Film Board of Canada is Canada\'s twelve-time Academy Award-winning public film and digital media producer and distributor.';
  $provider->endpoint = 'http://www.nfb.ca/remote/services/oembed/';
  $provider->scheme = 'http://www.nfb.ca/film/*
https://www.nfb.ca/film/*';
  $providers['nfb'] = $provider;

  $provider = new stdClass();
  $provider->disabled = TRUE; /* Edit this to true to make a default provider disabled initially */
  $provider->api_version = 1;
  $provider->name = 'noembed';
  $provider->admin_title = 'Noembed';
  $provider->admin_description = 'Noembed provides a single url to get embeddable content from a large list of sites, even sites without oEmbed support.';
  $provider->endpoint = 'http://noembed.com/embed';
  $provider->scheme = 'http://*
https://*';
  $providers['noembed'] = $provider;

  $provider = new stdClass();
  $provider->disabled = FALSE; /* Edit this to true to make a default provider disabled initially */
  $provider->api_version = 1;
  $provider->name = 'revision3';
  $provider->admin_title = 'Revision3';
  $provider->admin_description = 'Revision3 is a multi-channel internet television network that creates, produces and distributes web television shows on niche topics.';
  $provider->endpoint = 'http://revision3.com/api/oembed/';
  $provider->scheme = 'http://*.revision3.com/*
https://*.revision3.com/*
http://revision3.com/*
https://revision3.com/*';
  $providers['revision3'] = $provider;

  $provider = new stdClass();
  $provider->disabled = FALSE; /* Edit this to true to make a default provider disabled initially */
  $provider->api_version = 1;
  $provider->name = 'scribd';
  $provider->admin_title = 'Scribd';
  $provider->admin_description = 'Scribd is a digital library, featuring a subscription service with premier books including New York Times bestsellers and classics.';
  $provider->endpoint = 'http://www.scribd.com/services/oembed';
  $provider->scheme = 'http://scribd.com/doc/*
https://scribd.com/doc/*
http://www.scribd.com/doc/*
https://www.scribd.com/doc/*
http://scribd.com/mobile/documents/*
https://scribd.com/mobile/documents/*
http://www.scribd.com/mobile/documents/*
https://www.scribd.com/mobile/documents/*';
  $providers['scribd'] = $provider;

  $provider = new stdClass();
  $provider->disabled = FALSE; /* Edit this to true to make a default provider disabled initially */
  $provider->api_version = 1;
  $provider->name = 'slideshare';
  $provider->admin_title = 'SlideShare';
  $provider->admin_description = 'SlideShare is a web-based slide hosting service.';
  $provider->endpoint = 'http://www.slideshare.net/api/oembed/2';
  $provider->scheme = 'http://www.slideshare.net/*/*
https://www.slideshare.net/*/*
http://www.slideshare.net/mobile/*/*
https://www.slideshare.net/mobile/*/*
http://slidesha.re/*
https://slidesha.re/*';
  $providers['slideshare'] = $provider;

  $provider = new stdClass();
  $provider->disabled = FALSE; /* Edit this to true to make a default provider disabled initially */
  $provider->api_version = 1;
  $provider->name = 'smugmug';
  $provider->admin_title = 'SmugMug';
  $provider->admin_description = 'SmugMug is a paid digital photo sharing website, which allows users to upload both HD photos and videos to their SmugMug sites.';
  $provider->endpoint = 'http://api.smugmug.com/services/oembed/';
  $provider->scheme = 'http://*.smugmug.com/*
https://*.smugmug.com/*
http://*.smugmug.com/*#*
https://*.smugmug.com/*#*';
  $providers['smugmug'] = $provider;

  $provider = new stdClass();
  $provider->disabled = FALSE; /* Edit this to true to make a default provider disabled initially */
  $provider->api_version = 1;
  $provider->name = 'soundcloud';
  $provider->admin_title = 'SoundCloud';
  $provider->admin_description = 'SoundCloud is an online audio distribution platform that enables its users to upload, record, promote and share their originally-created sounds.';
  $provider->endpoint = 'http://soundcloud.com/oembed';
  $provider->scheme = 'http://soundcloud.com/*
https://soundcloud.com/*
http://soundcloud.com/*/*
https://soundcloud.com/*/*
http://soundcloud.com/*/sets/*
https://soundcloud.com/*/sets/*
http://soundcloud.com/groups/*
https://soundcloud.com/groups/*
http://snd.sc/*
https://snd.sc/*';
  $providers['soundcloud'] = $provider;

  $provider = new stdClass();
  $provider->disabled = FALSE; /* Edit this to true to make a default provider disabled initially */
  $provider->api_version = 1;
  $provider->name = 'twitter';
  $provider->admin_title = 'Twitter';
  $provider->admin_description = 'Twitter is an online social networking and microblogging service that enables users to send and read short 140-character text messages.';
  $provider->endpoint = 'https://api.twitter.com/1/statuses/oembed.json';
  $provider->scheme = 'http://twitter.com/*/status/*
https://twitter.com/*/status/*
http://twitter.com/*/statuses/*
https://twitter.com/*/statuses/*
http://www.twitter.com/*/status/*
https://www.twitter.com/*/status/*
http://www.twitter.com/*/statuses/*
https://www.twitter.com/*/statuses/*
http://mobile.twitter.com/*/status/*
https://mobile.twitter.com/*/status/*
http://mobile.twitter.com/*/statuses/*
https://mobile.twitter.com/*/statuses/*';
  $providers['twitter'] = $provider;

  $provider = new stdClass();
  $provider->disabled = FALSE; /* Edit this to true to make a default provider disabled initially */
  $provider->api_version = 1;
  $provider->name = 'ustream';
  $provider->admin_title = 'Ustream';
  $provider->admin_description = 'Ustream provides video streaming services to viewers and broadcasters. ';
  $provider->endpoint = 'http://www.ustream.tv/oembed';
  $provider->scheme = 'http://*.ustream.tv/*
https://*.ustream.tv/*
http://*.ustream.com/*
https://*.ustream.com/*';
  $providers['ustream'] = $provider;

  $provider = new stdClass();
  $provider->disabled = FALSE; /* Edit this to true to make a default provider disabled initially */
  $provider->api_version = 1;
  $provider->name = 'viddler';
  $provider->admin_title = 'Viddler';
  $provider->admin_description = 'Viddler is an interactive online video platform for uploading, managing, viewing, and tagging/commenting on videos.';
  $provider->endpoint = 'http://lab.viddler.com/services/oembed/';
  $provider->scheme = 'http://*.viddler.com/*
https://*.viddler.com/*';
  $providers['viddler'] = $provider;

  $provider = new stdClass();
  $provider->disabled = FALSE; /* Edit this to true to make a default provider disabled initially */
  $provider->api_version = 1;
  $provider->name = 'vimeo';
  $provider->admin_title = 'Vimeo';
  $provider->admin_description = 'Vimeo is a video-sharing website on which users can upload, share and view videos.';
  $provider->endpoint = 'http://vimeo.com/api/oembed.json';
  $provider->scheme = 'http://vimeo.com/*
https://vimeo.com/*
http://www.vimeo.com/*
https://www.vimeo.com/*
http://vimeo.com/groups/*/videos/*
https://vimeo.com/groups/*/videos/*
http://www.vimeo.com/groups/*/videos/*
https://www.vimeo.com/groups/*/videos/*
http://vimeo.com/m/#/*
https://vimeo.com/m/#/*';
  $providers['vimeo'] = $provider;

  $provider = new stdClass();
  $provider->disabled = FALSE; /* Edit this to true to make a default provider disabled initially */
  $provider->api_version = 1;
  $provider->name = 'youtube';
  $provider->admin_title = 'YouTube';
  $provider->admin_description = 'YouTube is a video-sharing website on which users can upload, view and share videos.';
  $provider->endpoint = 'http://www.youtube.com/oembed';
  $provider->scheme = 'http://*youtube.com/watch*
https://*youtube.com/watch*
http://*.youtube.com/v/*
https://*.youtube.com/v/*
http://youtu.be/*
https://youtu.be/*
http://*.youtube.com/user/*
https://*.youtube.com/user/*
http://*.youtube.com/*#*/*
https://*.youtube.com/*#*/*
http://m.youtube.com/watch*
https://m.youtube.com/watch*
http://m.youtube.com/index*
https://m.youtube.com/index*
http://*.youtube.com/profile*
https://*.youtube.com/profile*
http://*.youtube.com/view_play_list*
https://*.youtube.com/view_play_list*
http://*.youtube.com/playlist*
https://*.youtube.com/playlist*';
  $providers['youtube'] = $provider;

  return $providers;
}
