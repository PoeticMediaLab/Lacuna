# Welcome

# What is Lacuna Stories?

## Overview
## Technical Details
Lacuna Stories is built with Drupal, Annotator.js, and some scattered d3.js.
### Annotation in Drupal
Although two modules already exist that enable annotation in Drupal (Annotator and Annotation), neither works as well as we hoped. So, we have forked both modules and made many significant improvements, which we will be offering back to the maintainers of those projects. If you just want to enable annotation in a Drupal site, but don't want the entire Lacuna Stories experience, you can grab those modules from our repository. They're under sites/all/modules/custom/. You will need both the Annotator and the Annotation module. The first enables Annotator.js. The second allows you to store annotations as regular Drupal nodes. You may want to use the versions of these modules from Lacuna Stories v1.0, which has fewer features, but less integration with courses and several new plugins than the 2.0 versions.

### Annotator.js Plugins
Speaking of plugins, we've developed a number of new ones for the 1.x branch of Annotator.js. These plugins include advanced filters, histograms, categories, fine-grained permissions, and categorized annotation tags. Some are more integrated into Drupal than others, but if you just want to see the Annotator.js plugins, they are in the Annotator module directory.

### Staying Up to Date
#### Drupal core and contributed modules
Like any software, Drupal has frequent updates to maintain security and to add new features. Although we will try to keep this repository up-to-date with the latest versions of all included modules and to ensure that the site continues to work, it should generally be safe for you to run standard updates on your own site (with the usual caveat that you should test on a development copy first, not on your production server). I do it all the time and the updates work fine. If you find that an update somehow breaks Lacuna Stories, please file a bug report.

#### Lacuna Stories updates


# How to Use Lacuna Stories

## Installation Instructions

Follow the standard Drupal installation process (https://www.drupal.org/documentation/install), but instead of downloading the code as stated in Step 1, download our code instead:

'''
git clone https://github.com/PoeticMediaLab/LacunaStories.git
'''

Proceed with the installation process. Lacuna Stories will be automatically configured. You may encounter a few PHP notices at the last stage, which you can safely ignore.

## Post-Installation Tasks

After installing, there are a few steps you will want to take to improve the user experience.

* Disable warnings and error messages (admin/config/development/logging)
* Enabled compression and caching (admin/config/development/performance)

* Review the Course Creation settings (admin/config/content/lacuna-courses). These are the settings that determine the defaults for new courses. You may wish to require a password before instructors can create new courses. If so, you can set that here. You can also set the default genres, media, and priorities for documents. Be sure to click "Submit" at the bottom of the page after confirming these settings, even if you haven't changed anything; this will ensure that your site has initial values for these items.

* Review the Page Turner settings (admin/config/user-interface/page-turner). We recommend that you enable the Page Turner for documents or other node types that may be too long to read in an infinite scrolling window.

* If you don't want to share user data with our research team, disable the IRB Form by going to Structure -> Features -> Lacuna Stories and then unchecking the "IRB Form" feature. Click "Save Settings".

* Determine user registration settings (admin/config/people/accounts). By default, anyone can register for an account with Lacuna Stories, though they won't be able to do much with it. This can lead to many spam accounts. Although we have added features to mitigate against spam registrations, we cannot guarantee that none will get through. If you would prefer to create all accounts manually, then change the "Registration and Cancellation" settings.

## Adding Courses and Documents
### Setting up a Course
Lacuna Stories is designed to be used for courses, so all documents that you would like to annotate must be "within" a course. To create a course, go to SITEURL/course-setup and follow the steps. The setup will walk you through the process of creating a course and adding materials for reading and annotation. Only users with the "Instructor", "Site Administrator", or "Content Manager" roles can create courses and add materials to courses.

### Adding Users
Unless you are the only person who will be using your instance Lacuna Stories, you'll probably want to add new users. There are four main roles that users can have: "Site Administrator", "Content Manager", "Instructor", and "Student":

#### Site Administrator
This role has full access to manage the entire site, which includes enabling or disabling modules, backing up the database, creating and deleting users, and adding or deleting any and all types of content. It is recommended that only people with technical expertise managing and building Drupal sites have this role. NOTE: If visitors cannot register accounts, then only Site Administrators are able to add new users.

#### Content Mananger
This role can add, delete, and edit courses and materials within courses. They do not need to be enrolled in a course to make changes to it. Typically, these users may be research assistants or others who help your team set up and manage courses for instructors.

#### Instructor
Users with this role can create new courses, add materials to courses, manage the taxonomies that organize those materials, and add or drop students from the courses they have created. Instructors can also see all email addresses for students enrolled in their courses.

#### Student
Students can enroll in a course, read and annotate course materials, write responses, comment on the responses of others in their course, create peer groups for smaller group work, and manage their own profiles.

### Add Students and Instructors to a Course

# Reading, Annotating, and Writing
Please see the Instructor's Guide, Student Guide, and FAQ that come included with Lacuna Stories under the "Help" menu. We also have several helpful videos and other documentation on our [project website](http://www.lacunastories.com).

# How to Contribute

## Use the Platform and Provide Feedback

## Submit a Bug Report

## Submit a Pull Request

# Credits
Many people have put time and effort into this project. For a fuller list of the credits, see the official announcement of Lacuna Stories 2.0. Here are just the people who contributed code to the project, in boring alphabetical order.

Ben Allen
Daniel Bush
Shiraz Dindar
Zhila Emadi
Cody Leff
Tim Loudon
Rhea Pokorny
Adi Singh
Hayk Tepanyan
Amanda Visconti
Michael Widner
Max Wolff

# Supporters
These organizations at Stanford University all contributed in substantial ways to making Lacuna Stories possible:
* The Division of Literatures, Cultures, and Languages
* Stanford University Libraries
* The Office of the Vice Provost of Teaching and Learning
* The Center for Spatial and Textual Analysis (CESTA)
