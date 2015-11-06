
GLOBAL FILTER FOR VIEWS & CONTEXTS (D7)
=======================================

This module remembers your visitors' filter settings while they are on your site
and beyond (i.e. until they return). The filter settings can be used to filter
views across multiple pages and to switch "contexts", like page layouts, see
http://drupal.org/project/context.
 
Global Filter takes advantage of the small Session Cache API module,
http://drupal.org/project/session_cache. Please enable it. Its out-of-the-box
configuration is fine for now.

The values that may be selected from a global filter are based on either a field
or a view. A search term text box may also be used as a global filter. It is
treated like a field. If you have the Location or Geofield modules installed
then you may also globally filter by proximity. See the special section below
for details.
Fields execute just that little faster and are more straight-forward to use than
views, so pick a field as your global filter unless you want to reduce the set
of field values that may be selected, in which case you'll generally have to
resort to a view.

Fields are defined on the Structure >> Content types >> Manage fields and
Configuration >> Account settings >> Manage fields pages. An overview of all
fields on your system can be viewed via a link on the Administer >> Reports
page.

GLOBAL FILTER FOR VIEWS
=======================
1) A couple of filter blocks, named "Global filter block 1" and "Global filter
block 2" will now be available at Structure >> Blocks. If you want to use more
than two global filter blocks, you can create more blocks at Configuration >>
Global Filter. Place the block or blocks anywhere on your site.

2a) You may use either a field or the output of a view to drive a global filter.
Use the radio buttons on the block configuration page to select which one and
inspect the drop-down to see the fields available for use. If none of the node
properties/fields match what you're after, use a view. If you decide on a view
to populate the global filter, make sure that in the driving view the Format is
set to Unformatted and select "Show: Fields". Be aware that it will be the first
item under the view's Fields heading that will populate the filter widget, so
re-order your items if necessary. The remaining items will be ignored. The view
does not need to have a page or block display associated with it and may even
be disabled -- it will still operate correctly as a global filter.
2b) After you have selected a widget, press "Save block". The page will refresh
and you will be able to add more filters to the same block by opening the next
field set under the one just saved.
2c) After saving the block you can also select global filter defaults. The
default will remain active until the user makes a different filter selection. If
the global filter is a field that also appears on user profiles, then
authenticated users can override the global filter default with their personal
choice on their profile.

3) With your global filter block(s) configured, you can now use them to channel
the selected values into a view's Contextual Filter (as opposed to a regular
filter).
On the View edit page, open the Advanced field-set on the right. Then next to
Contextual Filters click Add and select the item corresponding to the global
filter source in the previous step. If you selected a View in step 2) then tick
a suitable ID option, e.g. if the view outputs taxonomy terms, then tick
"Taxonomy: Term ID" (not "Taxonomy: Term", i.e not the name/description).
After pressing "Add and configure..." on the next panel, press the radio button
"Provide default value".
3a) When you chose a field as the source for the global filter, select Type
"Global filter (field or search term)".
3b) When you chose a View as the source for the global filter, select Type
"Global filter (view)" and then select the View(s) driving this filter.

4) Apply and Save the view.

That's it. Repeat steps 3) and 4) for the remaining views that need to use your
global filters.

Make sure that under "Page Settings" the Path does NOT contain percent signs for
arguments that you wish to apply a Global Filter to. In other words, the percent
signs in the Path should stop at the first Global Filter. So, if you have one
normal contextual filter, followed by one global filter, you'll have one percent
sign. When typing the view's path in your browser address bar, append arguments
for the normal contextual filters that precede the global filter. Use "all" to
skip a filter: /your-view-with-contextual-filters/all. If you type a URL
argument in the position of a global filter, you temporarily override the
current global filter value without setting it.

By default each global filter widget comes with a Set button to activate the
selection. However if you tick the appropriate check-box on the filter's
block page, the Set button does not appear and the filter is activated
immediately upon release of the mouse button.

In addition to the regular widgets you can also place links of the form
"/somepage?field_myfield=10" anywhere on your site, e.g. in menus, to set
global filters. You can set multiple values too, by separating them by commas:
"/somepage?field_myfield=10,17". You can also insert these links on other sites
or in emails to direct the reader to a pre-filtered view of your site.

You can have a total of up to 20 global filters across 1-20 global filter
blocks.

GLOBAL FILTER TO SET CONTEXTS
=============================
Instead of using a global filter to simultaneously filter views, you can use it
with the Context module, http://drupal.org/project/context, as a condition for
setting contexts.
For instance you can create a global filter block with a drop-down of
countries and then create session conditions for various country names, so that
your site reacts to the globally selected country. And using a PHP code snippet
for the default you could pre-select the drop-down with the visitor's country
based on their IP address, via http://drupal.org/project/smart_ip. See:
http://drupal.org/node/2318193

To set up a session condition you need to install and enable Session Context,
http://drupal.org/project/session_context.
Then at admin/structure/context/settings/session, use the following format to
create a condition: global_filter:field_NAME=VALUE  (no spaces, except in VALUE)
This condition will then be available at /admin/structure/context/add, when you
select Session as the condition from the drop-down.

For instance, to make the Context module react to taxonomy term 21 being
globally selected by the visitor, enter in the text area at
admin/structure/context/settings/session:
  global_filter:field_tags=21
Ignore the note below the text area.
You can require multiple values being set on the filter by using a comma:
   global_filter:field_tags=21,36,9
This means: react with the selected context only when all three taxonomy terms
are selected in a multi-valued widget, like a combo-box or check boxes.
You can achieve OR-logic (i.e. "one of") by adding single-valued session
conditions separately:
  global_filter:field_tags=21
  global_filter:field_tags=36

CAVEAT: the Context Session module currently does not support any of the caching
options available through Session Cache API, except for "session". Verify that
at admin/config/development/session_cache, the radio button "on the server,
in $_SESSION memory" is pressed, when you use Context Session.

GLOBAL FILTER TAXONOMY WITH HIERARCHICAL SELECT
===============================================
If you wish to use the taxonomy selection widget provided by the Hierarchical
Select module, you can. When configuring the Hierarchical Select widget on the
field, you will be prompted to press either "Save term lineage" or "Save only
the deepest term". Both work with Global Filter, but "Save term lineage"
gives you greater flexibility when using the hierarchical select as the widget
for your global filters.
Say you have a three-tiered taxonomy of Country, State and City and created a
field for it on some content type. If you created a piece of content with
"Australia, Victoria, Melbourne" as the taxonomy lineage on the field, then that
content will be returned in the view results when the global filter is set to
either just "Australia" or "Australia, Victoria" or "Australia, Victoria,
Melbourne". With "Save only the deepest term" pressed on the widget
configuration page that content will only be returned when the global filter is
set to "Australia, Victoria, Melbourne".
When you use the Hierarchical Select widget you do NOT need to tick "Allow
multiple values" on the contextual filter configuration panel.

GLOBAL FILTER FOR DATES OR DATE RANGES
======================================
The "created (posted)" and "updated (modified)" node PROPERTIES are
architecturally different from Date FIELDS (discussed below). When used as
contextual filters "created" and "updated" are supported as single values only.
However you can use them as contextual ranges via the Views Contextual Range
Filter module. When used this way, you can enter ranges for "created" and
"updated" dates via the Range widget in Global Filter.

As far as general date FIELDS go, here is how it works.
We assume that in addition to Views you have the Date module enabled. If your
content does not already have a date field attached, add one as per normal via
the Manage Fields tab on the content type page. You may pick any of the three
Date types, i.e. plain, ISO or Unix Timestamp. Just be aware of this bug
in the Date module: drupal.org/project/node/1477180. So until this is fixed,
maybe avoid Unix Timestamp. When prompted pick any of the available date
selection widgets, e.g popup calendar or the triple select list. You may tick
the "Collect an End date" box too, if you wish. After you have configured on
the block configuration page a global filter for the selected date field or
range, the global filter will render itself using the same widget you picked for
the field on the content type. However, the global filter will always appear as
a date range. Filtering on a single date would be a little restrictive!
Finally, as with any other global filter you need to hook it into your view as
a contextual filter. Use either just the field start date or create a second
contextual filter to also require the content's end date being inside the
filter range. In either case scroll down the bottom of the contextual filter
panel to the heading "Dates to compare". Press the button "Only this field".

GLOBAL FILTER FOR SEARCH TERMS
==============================
To configure a global filter as a global keyword search, select as the driver
the pseudo-field "Search: Search terms". The widget will always be a text field
regardless of which radio button you press.
In your View, after pressing "Add" in the Contextual Filter tick the check box
"Search: Search terms", followed as per usual by the "Provide default value"
radio button. Select "Global filter (field or search terms)" from the drop-down.
Press Apply at the bottom of the panel.
If you have the Search API module enabled the process is the same.

GLOBAL FILTER FOR RANGES
========================
With the "Contextual Range Filter" module enabled and your contextual filter
converted to a contextual range filter, you may use any of the following
widgets to enter filter ranges as opposed to single filter values:
o text field, enter ranges by separating "from" and "to" by a double hyphen,
  for example 0.5--2.5 or a--k or, if the field is a list, use either the keys,
  e.g., 3--7 or the list names, e.g. toddler--teenager
o range, i.e. separate "from" and "to" text fields, no need to enter the
  separator
o inherit range slider (requires the Slide with Style module from the project
  http://drupal.org/project/select_with_style)

GLOBAL FILTER FOR PROXIMITY USING LOCATION MODULE
=================================================
If you have the Location module enabled you can globally filter content or user
accounts based on a distance from a postcode or lat/lon pair of coordinates
as entered by the visitor.
If you wish to base proximity on a postcode the visitor enters, then make sure
that you are connected to the Internet and have selected an appropriate web
service on the Location configuration page
admin/config/content/location/geocoding.
When using the Google geocoding service entering a blank API key usually works.
To configure the global filter block select as the driver the pseudo-field
"Location module: Distance/Proximity". The widget in this case will be a single
text field -- for an alternative option, see the next section.
As far as the Contextual Filter in Views is concerned, tick "Provide default
value" as per normal, then select "Global filter (proximity)" and enter a
default distance. Scroll down the panel to select whether you want the user to
enter a lat,long pair or a postcode in the global filter text field. Also select
the unit (km or mile) and the shape of the proximity area (circular or
rectangular). Press Apply at the bottom and you're done.
The proximity filter presents itself as a textfield for the visitor to enter
their postcode or lat/lon pair (separated by a comma). Visitors may optionally
append a space or underscore and a distance. If the distance is omitted, then
the default as set on the Views "Global filter (proximity)" configuration panel
is taken.
If you have "IP Geolocation Views and Maps" enabled then you can set as an
initial default the postal code to that of the visitor's location upon first
visit. To do this enter this code snippet as the global filter global default:

<?php
  $location = ip_geoloc_get_visitor_location();
  return $location['postal_code'];
?>

GLOBAL FILTER FOR ADDRESS OR VISITOR'S LOCATION (GEOFIELD, LOCATION MODULES)
============================================================================
To configure the global filter block for use with the Location module select as
before as the driver the pseudo-field "Location module: Distance/Proximity".
When using Geofield, select the name of the correct field from the drop-down.
For the widget select "Proximity (reference location and distance)".
The widget renders as a small form with two fields. The first is to specify a
distance, in km or miles as configured on the Views contextual filter UI panel.
The second field when left blank will default to the user's current position
as retrieved by module IPGV&M (drupal.org/project/ip_geoloc), if enabled. If
an address or approximate address, like "Melbourne, Australia" is entered, then
the Google geocoding service will be used to obtain lat/lon. This requires the
Geocoder module.

GLOBAL FILTER FOR CITY, NOT USING LOCATION OR GEOFIELD MODULES
==============================================================
Here are three examples. For an IP-based lookup of the visitor's location
configure either Smart IP or GeoIP API. For an HTML5 (i.e GPS) location based
approach also configure IPGV&M. We assume that you have already defined a
field named "City" (field_city) on one or more of your content types. This
field may be either a text field or taxonomy term reference.
At /admin/structure/block find a block named "Global filter block # (not
configured)". Press "configure".
Enter <none> in the "Block title" box.
In the dropdown "Choose the field to be used as a global filter" find your
city field: "Field: City (field_city)". Widget: "Inherit from field".
Under "Alternatively specify a default through PHP code" enter a code snippet
as per below.
When using Smart IP, enter:
  <?php return $_SESSION['smart_ip']['location']['city']; ?>

When using GeoIP API enter:
  <?php $loc = geoip_city(); return empty($loc) ? 'default' : $loc->city; ?>

Or when using IPGV&M:
  <?php $loc = ip_geoloc_get_visitor_location(); return $loc['locality']; ?>

For the "Region setting" select "Content". Finally press "Show block only on the
listed pages" and enter the path to your View. Click "Save block".
Now go back to edit your View.
In the "Advanced" fieldset on the right "Add" a Contextual Filter for "Content:
City (field_city)". On the next panel press "Provide default value", then for
the Type select "Global filter (field or search terms)". Click "Apply".
Save the View.
That should be it. Log out. Go to the URL associated with the View and it
should be filtered by your city. You should also see a text box there to filter
the View by any city you type. This should work for both logged-in and anonymous
users. A further option is that if the same field_city is also added to the user
profile at admin/config/people/accounts/fields, (e.g. "My favourite city"), then
the value entered by the account holder on the "Edit account" page will become
the initial value of the exposed filter.
Note: this solution may not work when you're not connected to the Internet and
your IP address is "localhost", 127.0.0.1.

USEFUL VIEW OPTIONS
===================
On the View edit page, in the contextual filter configuration panel, after you
have selected a global filter to provide the default value, scroll down the
panel and expand the More field-set for a couple of additional useful options.
"Allow multiple values" is MANDATORY when you configured your global filter to
render as a multi choice widget.
"Exclude" is nice to populate a view with the compliment of the global filter
selection (e.g. all countries except South American countries).

ADVANCED OPTIONS: ROTATING BLOCK CONTENT
========================================
A special auto-cycle filter is available under the "Advanced configuration"
fieldset on the Configuration >> Global Filter page. You can use this to create
block content that changes with every click on the site. Examples are ads, news
items or user profile pictures, that have to follow a specific logical sequence,
for instance chronological, alphabetical, by section or chapter number, or by
vocabulary term order.

You normally need two views for this (although at the bottom of this page we'll
mention a short-cut alternative for the second view). Let's call these the
filter view and the block/page view.

The filter view simply needs to return in the desired order, the nodes (or
users or etc.) that you wish to rotate through the block. This view does not
need page or block displays and doesn't have to output any fields, as the nids
are silently output anyway. However, to verify the view correctly returns the
nodes in the order you wish them to cycle through the block, we suggest to
configure the view format to output titles or teasers. Save this view.
Activate this view as the driver for the auto-cycle filter at Configuration >>
Global Filter, opening the "Advanced configuration" fieldset. Select the view
you've just created and press "on every page load".

The block/page view needs to produce at least as much content as the filter
view. In fact you could start by cloning the filter view and use it as a base.
Select any display format and any fields you like to display for the block of
rotating content. Don't forget to add a block or page display to this view!
Remember that only one of these pieces of content will be shown at any one time,
as auto-selected by the above filter view. This is established by adding a
Contextual Filter to the block/page view (Advanced fieldset, upper right
corner). Tick "Content: Nid" and "Apply...". Press "Provide default value" and
then select "Global filter (view)" from the Type drop-down. Your auto-cycle view
should appear in the next drop-down. Press "Apply...". Save this view.

Finally, if you went for a view with a block rather than page display at
Structure >> Blocks, move your block from the Disabled section into the desired
page region.

Verify the view appears and note that with every new page you visit the
page/block view displays another piece of content.

Shortcut: if you're happy to have just the title show in the block, you could
do the following. Don't create a second view. Create a block instead, select
"PHP code" for the block text format and enter in the block body text area:

<?php
  $node = node_load(global_filter_get_session_value('view_autocycle'));
  print theme('node', array('elements' => array('#node' => $node, '#view_mode' => 'teaser')));
?>

Depending on how your theme's node.tpl.php is organised this will most likely
show just the hyperlinked title of the next piece of auto-selected content.
