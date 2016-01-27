<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Table of Contents**  *generated with [DocToc](https://github.com/thlorenz/doctoc)*

- [What is Lacuna Stories?](#what-is-lacuna-stories)
- [Overview](#overview)
  - [Technical Details](#technical-details)
  - [Annotation in Drupal](#annotation-in-drupal)
  - [Annotator.js Plugins](#annotatorjs-plugins)
- [How to Use Lacuna Stories](#how-to-use-lacuna-stories)
  - [Installation Instructions](#installation-instructions)
  - [Post-Installation Tasks](#post-installation-tasks)
  - [Adding Courses and Documents](#adding-courses-and-documents)
    - [Setting up a Course](#setting-up-a-course)
    - [Adding Users](#adding-users)
      - [Site Administrator](#site-administrator)
      - [Content Mananger](#content-mananger)
      - [Instructor](#instructor)
      - [Student](#student)
    - [Add Students and Instructors to a Course](#add-students-and-instructors-to-a-course)
  - [Reading, Annotating, and Writing](#reading-annotating-and-writing)
- [Staying Up to Date](#staying-up-to-date)
  - [Drupal core and contributed modules](#drupal-core-and-contributed-modules)
  - [Lacuna Stories updates](#lacuna-stories-updates)
- [How to Contribute](#how-to-contribute)
  - [Use Lacuna Stories and Provide Feedback](#use-lacuna-stories-and-provide-feedback)
  - [Submit a Bug Report](#submit-a-bug-report)
  - [Suggest New Features](#suggest-new-features)
  - [Submit a Pull Request](#submit-a-pull-request)
- [Credits](#credits)
- [Supporters](#supporters)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->

# What is Lacuna Stories?
Lacuna Stories is a platform designed to enhance reading, connected learning, and discussion in the classroom by allowing students and instructors to engage deeply with their course materials through annotation. We have found it to be particularly popular in discussion-based classrooms, in language instruction, and in many other formats. Students are able to read socially, which means that they can have conversations about the readings outside of the classroom. Students can also use their annotations as the basis for longer, possibly more formal written responses by using our innovative Sewing Kit. Instructors are able to see not only how their students are engaging with the texts, but also what annotation skills they are developing. Thanks to our Annotations Dashboard, instructors can see in real-time who has annotated which documents, who is sharing their comments with others, and many other facets of student engagement.

# Overview
## Technical Details
Lacuna Stories is built with [Drupal](http://www.drupal.org), [Annotator.js](http://annotatorjs.org/), and [D3.js](http://d3js.org/). It has the same requirements as a standard Drupal installation, namely, a web server, a database (typically MySQL or MariaDB), and PHP 5.3+. You can read more about the [technical requirements on the Drupal website](https://www.drupal.org/requirements).

## Annotation in Drupal
Although two modules already exist that enable annotation in Drupal ([Annotator](https://www.drupal.org/project/annotator) and [Annotation](https://www.drupal.org/project/annotation)), neither is fully functional out of the box. So, we have forked both modules and made many significant improvements, which we will be offering back to the maintainers of those projects. If you just want to enable annotation in a Drupal site, but don't want the entire Lacuna Stories experience, you can grab those modules from our repository. They're under sites/all/modules/custom/. You will need both the Annotator and the Annotation module. The first enables Annotator.js. The second allows you to store annotations as regular Drupal nodes. You may want to use the versions of these modules from [Lacuna Stories v1.0](https://github.com/PoeticMediaLab/LacunaStories/tree/v1.0), which has fewer features, but less integration with courses and several new plugins than the 2.0 versions.

## Annotator.js Plugins
Speaking of plugins, we've developed a number of new ones for the 1.2.x branch of Annotator.js. These plugins include advanced filters, histograms, categories, fine-grained permissions, and categorized annotation tags. Some are more integrated into Drupal than others, but if you just want to see the Annotator.js plugins, they are in the Annotator module directory.

# How to Use Lacuna Stories

## Installation Instructions

Follow the standard [Drupal installation process](https://www.drupal.org/documentation/install), but instead of downloading the code as stated in Step 1, download our code instead:

```
git clone https://github.com/PoeticMediaLab/LacunaStories.git
```

You could, of course, download a zipfile of all the code, but we recommend using Git, which will make it easier to get updates. If you choose to use git, you will want to add this repository as a remote:

```
git remote add origin https://github.com/PoeticMediaLab/LacunaStories.git
```

Proceed with the installation process. Lacuna Stories will be automatically configured.

We highly recommend that you install [Drush](http://www.drush.org/en/master/) to help you manage updates to the site. We will assume Drush is available later in this document.

## Post-Installation Tasks

After installing, there are a few steps you will want to take to improve the user experience.

* Disable warnings and error messages (admin/config/development/logging)
* Enable compression and caching (admin/config/development/performance)

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
This role has full access to manage the entire site, which includes enabling or disabling modules, backing up the database, creating and deleting users, and adding or deleting any and all types of content. It is recommended that only people with technical expertise managing and building Drupal sites have this role.

*Note*: If visitors cannot register accounts, then only Site Administrators are able to add new users.

#### Content Mananger
This role can add, delete, and edit courses and materials within courses. They do not need to be enrolled in a course to make changes to it. Typically, these users may be research assistants or others who help your team set up and manage courses for instructors.

#### Instructor
Users with this role can create new courses, add materials to courses, manage the taxonomies that organize those materials, and add or drop students from the courses they have created. Instructors can also see all email addresses for students enrolled in their courses.

#### Student
Students can enroll in a course, read and annotate course materials, write responses, comment on the responses of others in their course, create peer groups for smaller group work, and manage their own profiles.

### Add Students and Instructors to a Course
After users have accounts on the site, they need to be members of a course to access materials. From the "About this Course" page, click on the "Group" tab (we use [Organic Groups](https://www.drupal.org/project/og) to organize courses). Next, click "Add people". Under the "User name" field, start typing the names of students and instructors who should be part of this course. For instructors, check the "administrator member" box before submitting the form. When ready, click the "Add users" button. Repeat as needed.

## Reading, Annotating, and Writing
Please see the Instructor's Guide, Student Guide, and FAQ that come included with Lacuna Stories under the "Help" menu. We also have several helpful videos and other documentation on our [project website](http://www.lacunastories.com).

# Staying Up to Date
## Drupal core and contributed modules
Like any software, Drupal has frequent updates to maintain security and to add new features. Although we will try to keep this repository up-to-date with the latest versions of all included modules and to ensure that the site continues to work, it should generally be safe for you to run standard updates on your own site (with the usual caveat that you should test on a development copy first, not on your production server). I do it all the time and the updates work fine. If you find that an update somehow breaks Lacuna Stories, please file a bug report.

## Lacuna Stories updates
As we add new features and fix bugs, we will increment the Lacuna Stories version number and update the GitHub repository. To include these changes on your site, you will need to update your copy of the software by running the following commands within your installion directory:

```
git pull origin master
drush updb -y
drush fra -y
```

If you do not have Drush available or have not used git, you can download the latest version of the software as a zipfile. Then, enable any updates by going to the Features administration page (/admin/structure/features), clicking on the "Lacuna Stories" tab, and reverting each changed feature. Next, run the update script (update.php).

_Note_: If you have made significant customizations of your copy of Lacuna Stories, you may not want to run these updates automatically. It would be better, in that case, to check the changelog and determine if any changes will overwrite your customizations. Keep in mind, if you have made customizations that you think would be broadly useful, feel free to send us a pull request to include your code into the main distribution.

# How to Contribute
The primary avenue for support and contributions to Lacuna Stories will be through our GitHub repository. Please use the [issues feature](https://github.com/PoeticMediaLab/LacunaStories/issues) to contact us.

## Use Lacuna Stories and Provide Feedback
Using Lacuna Stories in your teaching and research will help us learn more about how we can improve the experience... but only if you let us know! Please get in touch either through our GitHub repository or via email to info@lacunastories.com.

## Submit a Bug Report
If you find a bug, please submit [create a bug report](https://github.com/PoeticMediaLab/LacunaStories/issues/new). Be sure to provide enough information so that we can duplicate the problem. If you're not sure how to write a good bug report, read [Mozilla's excellent guide](https://developer.mozilla.org/en-US/docs/Mozilla/QA/Bug_writing_guidelines) first.

## Suggest New Features
Do you find yourself trying to do something over and over that Lacuna Stories either doesn't make easy or won't let you do at all? Great! Let us know about it, again by submitting an issue. Please label it as an "enhancement" and we can start to discuss your idea.

## Submit a Pull Request
Want to improve or extend Lacuna Stories yourself? That's great! Please, don't keep the changes to yourself. Fork our repository and send a pull request. If it's something we agree should be in the main distribution, we'd love to merge your request and will gladly give you credit for the work.

# Credits
Many people have put time and effort into this project. For a fuller list of the credits, see the official announcement of Lacuna Stories 2.0. Here are just the people who contributed code to the project, in boring alphabetical order:

* Ben Allen
* Daniel Bush
* Shiraz Dindar
* Zhila Emadi
* Cody Leff
* Tim Loudon
* Matt Mowers
* Rhea Pokorny
* Adi Singh
* Hayk Tepanyan
* Amanda Visconti
* Michael Widner
* Max Wolff

# Supporters
These organizations at Stanford University all contributed in substantial ways to making Lacuna Stories possible:
* [The Center for Interdisciplinary Digital Research (CIDR)](https://cidr.stanford.edu), Stanford University Libraries
* [The Center for Spatial and Textual Analysis (CESTA)](https://cesta.stanford.edu)
* [The Dean of Research](https://doresearch.stanford.edu/research-offices/dor-office-vice-provost-and-dean-research)
* [The Division of Literatures, Cultures, and Languages](https://dlcl.stanford.edu)
* [The Knut and Alice Wallenberg Foundation](https://www.wallenberg.com/kaw/en)
* [The Office of the Vice Provost for Teaching and Learning](https://vptl.stanford.edu/)
* [The Office of the Vice Provost for Undergraduate Education](https://undergrad.stanford.edu/about)

