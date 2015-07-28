
Session Cache API Installation
==============================
You typically use this module for one of two reasons:
a) because another module tells you to, i.e. it may list Session Cache API as
   a dependency;
b) you are a Drupal/PHP programmer who is contemplating to take advantage of the
   API to create a light-weight transparent HTTP session storage mechanism that
   continues to work well on Drupal sites if/when Varnish is introduced.

In either case, simply enable the module like any other and visit its 
configuration page, admin/config/development/session_cache.

If Varnish isn't used on your system, the default configuration settings are
fine, i.e. do nothing.
If Varnish is used, read the Varnish section further down this page.

About sessions
==============

When it comes to session data (aka $_SESSION data) Drupal core interacts with
the PHP runtime system session, registering with PHP the six functions
responsible for the opening, closing, reading, writing, garbage-collecting and
destroying of sessions. This happens during Drupal's bootstrap process, prior
to it even considering what to do with the HTTP request it just received.
[See drupal_session_initialize() in includes/session.inc, if you're interested]

For instance _drupal_session_read() is "... to support database-backed sessions.
It is called on every page load by PHP as it sets up $_SESSION. This is an
internal function and must not be called directly. Session data must always be
accessed via the $_SESSION super global."

Programmers save session data simply by assigning values to the super global
$_SESSION. This data is backed by Drupal's {sessions} db table, at least for
authenticated users...

When an authenticated user logs off and thus becomes anonymous their $_SESSION
gets destroyed via core's user_logout() function.

This can be a pain for programmer and end user alike as it causes a
discontinuity in the user experience in terms of the session data present before
and after logout.

The Session API module, drupal.org/project/session_api, helps. It returns as an
identifier not the internal session_id(), but instead an id it generates and
stores in a cookie on the user's computer. That cookie exists before AND after
logout. So while the PHP/Drupal-core generated $_SESSION gets destroyed, Session
API will return to the programmer an equivalent sid that is valid for both the
logged-in and logged-out situations.
Neat.

However Session API has limited scope (as it should) and does not itself
implement any storage against this "unified" sid. You have to do that yourself.
That's where the Session Cache API module comes in.

Session Cache API
=================

The Session Cache API is a super-simple two-function API for programmers to
access small amounts of user-specific "state". Examples are the user's
changing geographic location or a drop-down selection that is made upon first
visit and needs to be remembered for the remainder of the session, or beyond.

The module comes in particularly handy when anonymous session data needs to be
stored, which may or may not be viable using the standard $_SESSION way, due to
system infrastructure constraints imposed by a caching engine or web accelerator
like Varnish.

While this module was partly designed for the use-case of anonymous users and
caching engines, it is itself NOT for caching pages, nodes, menus or large
volumes of data. Nor should you use it to hold sensitive data like passwords,
as there is no encryption.

This module does one small job: help create a smooth experience for both users
and programmers when it comes to anonymous user session management.
You do NOT need the Session API module.

This API is independent of the underlying session storage mechanism. In fact the
storage model does not enter the API. Instead it is selected through the
administrative UI to best suit the deployed system configuration.
The storage mechanisms available are:

 o cookie, i.e. store session on the user's computer
 o database, i.e. store session on the server, in a cache table
 o $_SESSION, i.e. store in server RAM, backed by core's {sessions} table
 o file, i.e. store on the server, one tiny file per session -- enable the
   session_cache_file submodule for this option

Administrators may switch the storage mechanism on the module's configuration
page at any time.

For the database and file storage mechanisms the site administrator may pick
what source is used to create the session identifier:
- cookie for everyone (default)
- user id for logged-in users, cookie for anonymous users
- IP address for everyone

Unlike $_SESSION, the cookie, database and file storage mechanisms offer
seamless user experiences across login/logout boundaries.

With cookies being configured for use as session ids, the database mechanism,
if selected, stills work when cookies are disabled on the client, except there
will be a discontinuity of the session data across login and logout.

Cookies have a size limitation of about 4k.

Varnish or similar engine
-------------------------
The $_SESSION option may be unsuitable when used in combination with a caching
engine like Varnish. The cookie option can be a good solution, also because it
distributes storage foot print from the server to its clients. However you may
have to combine it with a page exclusion strategy whereby no caching takes
place for some pages, thus allowing for cookies to exist.
By default, all mechanisms require anonymous users to have cookies enabled in
their browser, unless the IP address is chosen as the session identifier in the
database or file storage approaches -- something to consider when using Varnish.
In the cookie mechanism the session data itself is stored in a cookie, while in
the database and $_SESSION mechanisms a smaller cookie is used just to hold the
key to the session data, unless the IP address is used as a session identifier.

NOTE: visitors who have cookies switched off will not be able to login, so are
doomed to remain anonymous AND will not have their session states remembered,
unless their IP address is used as the source to identify their sessions.

The API to read and write user session data is the same in all cases and
comprises these two functions:

  session_cache_set($bin, $data)
  session_cache_get($bin)

Further API details are in the session_cache.api.php file.
