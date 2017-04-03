<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Table of Contents**  *generated with [DocToc](https://github.com/thlorenz/doctoc)*

- [Overview](#overview)
    - [What is Lacuna?](#what-is-lacuna)
    - [Who is this README for?](#who-is-this-readme-for)
- [How to Install Lacuna](#how-to-install-lacuna)
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
- [Canvas / LTI Support](#canvas--lti-support)
    - [Enable LTI Support](#enable-lti-support)
    - [Add LTI Tool Consumer](#add-lti-tool-consumer)
    - [Add Lacuna as a Canvas app](#add-lacuna-as-a-canvas-app)
    - [Using Lacuna in Canvas](#using-lacuna-in-canvas)
- [Staying Up to Date](#staying-up-to-date)
    - [Drupal core and contributed modules](#drupal-core-and-contributed-modules)
    - [Lacuna updates](#lacuna-updates)
- [How to Contribute](#how-to-contribute)
    - [Use Lacuna and Provide Feedback](#use-lacuna-and-provide-feedback)
    - [Submit a Bug Report](#submit-a-bug-report)
    - [Suggest New Features](#suggest-new-features)
    - [Submit a Pull Request](#submit-a-pull-request)
- [Credits](#credits)
- [Supporters](#supporters)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->

# Overview
### What is Lacuna?
Lacuna is a platform designed to enhance reading, connected learning, and discussion in the classroom by allowing students and instructors to engage deeply with their course materials through annotation. We have found it to be particularly popular in discussion-based classrooms, in language instruction, and in many other formats. Students are able to read socially, which means that they can have conversations about the readings outside of the classroom. Students can also use their annotations as the basis for longer, possibly more formal written responses by using our innovative Sewing Kit. Instructors are able to see not only how their students are engaging with the texts, but also what annotation skills they are developing. Thanks to our Annotations Dashboard, instructors can see in real-time who has annotated which documents, who is sharing their comments with others, and many other facets of student engagement.

### Who is this README for?
This README is primarily aimed at technologists who might be installing Lacuna or who might need to support instructors using it. If you're just interested in trying it out, [contact our team](https://www.lacunastories.com/contact/) and we can set you up on our [Demo site](https://demo.lacunastories.com).


# How to Install Lacuna
Lacuna is built with [Drupal](http://www.drupal.org), [Annotator.js](http://annotatorjs.org/), and [D3.js](http://d3js.org/). It has the same requirements as a standard Drupal installation, namely, a web server, a database (typically MySQL or MariaDB), and PHP 5.3+. You can read more about the [technical requirements on the Drupal website](https://www.drupal.org/requirements).

### Installation Instructions

**NOTE**: You very much need to perform the tasks listsed in our [Post-Installation Tasks[(#post-installation-tasks) section. 
Follow the standard [Drupal installation process](https://www.drupal.org/documentation/install), but instead of downloading the code as stated in Step 1, download our code instead:

```
git clone https://github.com/PoeticMediaLab/LacunaStories.git
```

You could, of course, download a zipfile of all the code, but we recommend using Git, which will make it easier to get updates. 

Proceed with the installation process. Lacuna will be automatically configured.

We highly recommend that you install [Drush](http://www.drush.org/en/master/) to help you manage updates to the site. We will assume Drush is available later in this document.

NOTE: [Clean URLs](https://www.drupal.org/getting-started/clean-urls) are *required* for annotations to work.

### Post-Installation Tasks

After installing, there are a few steps you must still take.

* Disable warnings and error messages (admin/config/development/logging)
* Enable compression and caching (admin/config/development/performance)

* Review the Course Creation settings (admin/config/content/lacuna-courses). These are the settings that determine the defaults for new courses. You may wish to require a password before instructors can create new courses. If so, you can set that here. You can also set the default genres, media, and priorities for documents. **Be sure to click "Submit" at the bottom of the page after confirming these settings, even if you haven't changed anything**; this will ensure that your site has initial values for these items.

* Review the Page Turner settings (admin/config/user-interface/page-turner). We recommend that you enable the Page Turner for documents or other node types that may be too long to read in an infinite scrolling window.

* If you don't want to share user data with our research team, disable the IRB Form by going to Structure -> Features -> Lacuna and then unchecking the "IRB Form" feature. Click "Save Settings".

* Determine user registration settings (admin/config/people/accounts). By default, anyone can register for an account with Lacuna, though they won't be able to do much with it. This can lead to many spam accounts. Although we have added features to mitigate against spam registrations, we cannot guarantee that none will get through. If you would prefer to create all accounts manually, then change the "Registration and Cancellation" settings.

## Adding Courses and Documents
### Setting up a Course
Lacuna is designed to be used for courses, so all documents that you would like to annotate must be "within" a course. To create a course, go to SITEURL/course-setup and follow the steps. The setup will walk you through the process of creating a course and adding materials for reading and annotation. Only users with the "Instructor", "Site Administrator", or "Content Manager" roles can create courses and add materials to courses.

### Adding Users
Unless you are the only person who will be using your instance Lacuna, you'll probably want to add new users. There are four main roles that users can have: "Site Administrator", "Content Manager", "Instructor", and "Student":

##### Site Administrator
This role has full access to manage the entire site, which includes enabling or disabling modules, backing up the database, creating and deleting users, and adding or deleting any and all types of content. It is recommended that only people with technical expertise managing and building Drupal sites have this role.

*Note*: If visitors cannot register accounts, then only Site Administrators are able to add new users.

##### Content Mananger
This role can add, delete, and edit courses and materials within courses. They do not need to be enrolled in a course to make changes to it. Typically, these users may be research assistants or others who help your team set up and manage courses for instructors.

##### Instructor
Users with this role can create new courses, add materials to courses, manage the taxonomies that organize those materials, and add or drop students from the courses they have created. Instructors can also see all email addresses for students enrolled in their courses.

##### Student
Students can enroll in a course, read and annotate course materials, write responses, comment on the responses of others in their course, create peer groups for smaller group work, and manage their own profiles.

### Add Students and Instructors to a Course
After users have accounts on the site, they need to be members of a course to access materials. From the "About this Course" page, click on the "Group" tab (we use [Organic Groups](https://www.drupal.org/project/og) to organize courses). Next, click "Add people". Under the "User name" field, start typing the names of students and instructors who should be part of this course. For instructors, check the "administrator member" box before submitting the form. When ready, click the "Add users" button. Repeat as needed.

## Reading, Annotating, and Writing
Please see the Instructor's Guide, Student Guide, and FAQ that come included with Lacuna under the "Help" menu. We also have several helpful videos and other documentation on our [project website](http://www.lacunastories.com).

# Canvas / LTI Support
As of version 2.2, Lacuna supports integration with Canvas and other Learning Management Systems that support the [Learning Tools Interoperability] (https://www.imsglobal.org/activity/learning-tools-interoperability) standards. This section of the guide describes how to enable and configure this support, with a focus on Canvas. If you are an instructor, you probably will need to consult with your local Lacuna site administrator to enable this support. *NOTE*: It is strongly recommended that you serve Lacuna through the HTTPS protocol. Most LMSes will complain or refuse to work if you don't. 

### Enable LTI Support
The first step is to enable the 'LTI Support' Feature, which can be found at '/admin/structure/features' under the 'Lacuna Stories' section. This feature will allow your Lacuna instance to accept LTI requests from any LMS that supports it. If you have made any changes to Lacuna's default roles and user permissions, you will need to review all the LTI settings so that they reflect your customized configuration.  

### Add LTI Tool Consumer
Next, you must add an LTI Tool Consumer by visiting '/admin/config/lti-tool-provider/lti-tool-consumers' and clicking 'Add a new LTI Tool Consumer'. This step requires you to generate a secure key and secret, which will be shared with any instructors who wish to add Lacuna as an extension to your institution's LMS. These values can be whatever you like, but should be [cryptographically secure] (https://xkcd.com/936/). You may also create a new Tool Consumer for each instructor that will use Lacuna. This ensures that you are not sharing secrets and keys among multiple users.

### Add Lacuna as a Canvas app
Lacuna provides a URL that makes it easy to add it as an app to Canvas. The path is SITE_URL/lti/canvas.xml. See [How do I configure an external app for an account using a URL] (https://guides.instructure.com/m/4214/l/74559-how-do-i-configure-an-external-app-for-an-account-using-a-url) for details about how to configure Canvas with this URL. Be sure to set the "Privacy" option for Lacuna to "Public". This ensures that students' names and correct email addresses will be used in Lacuna; it will *not* expose their information to the public or to members of other courses.

Site administrators, please note: Canvas will attempt to embed Lacuna within an iFrame. By default, Drupal will not permit this behavior for security reasons. If you want to use Lacuna within Canvas, add the following line to your settings.php file:

  <code>$conf['x_frame_options'] = '';</code>
  
  For more information about this issue, see [this post](https://www.drupal.org/node/2735873). 
 
### Using Lacuna in Canvas
Once configured as a Canvas app, Lacuna will add a menu item 'Lacuna Course Setup', which is visible only to instructors and administrators. Instructors should first click on this link to get started setting up their course and materials within Lacuna. They will be guided through the process and may return at any time. Once documents have been added to Lacuna, they will be available as a resource for assignments. Read [How do I add an external app as an assignment submission type?](https://guides.instructure.com/m/4152/l/501360?data-resolve-url=true&data-manual-id=4152) for details about how to integrate Lacuna into an assignment. *NOTE*: We recommend that assignments using Lacuna open the app in a new tab for the best user experience. 


# Staying Up to Date
### Drupal core and contributed modules
Like any software, Drupal has frequent updates to maintain security and to add new features. Although we will try to keep this repository up-to-date with the latest versions of all included modules and to ensure that the site continues to work, it should generally be safe for you to run standard updates on your own site (with the usual caveat that you should test on a development copy first, not on your production server). I do it all the time and the updates work fine. If you find that an update somehow breaks Lacuna, please file a bug report.

### Lacuna updates
As we add new features and fix bugs, we will increment the Lacuna version number and update the GitHub repository. To include these changes on your site, you will need to update your copy of the software by running the following commands within your installation directory:

```
git pull origin master
drush updb -y
drush fra -y
```

If you do not have Drush available or have not used git, you can download the latest version of the software as a zipfile. Then, enable any updates by going to the Features administration page (/admin/structure/features), clicking on the "Lacuna" tab, and reverting each changed feature. Next, run the update script (update.php).

_Note_: If you have made significant customizations of your copy of Lacuna, you may not want to run these updates automatically. It would be better, in that case, to check the changelog and determine if any changes will overwrite your customizations. Keep in mind, if you have made customizations that you think would be broadly useful, feel free to send us a pull request to include your code into the main distribution.

# How to Contribute
The primary avenue for support and contributions to Lacuna will be through our GitHub repository. Please use the [issues feature](https://github.com/PoeticMediaLab/LacunaStories/issues) to contact us.

### Use Lacuna and Provide Feedback
Using Lacuna in your teaching and research will help us learn more about how we can improve the experience... but only if you let us know! Please get in touch either through our GitHub repository or via email to info@lacunastories.com.

### Submit a Bug Report
If you find a bug, please submit [create a bug report](https://github.com/PoeticMediaLab/LacunaStories/issues/new). Be sure to provide enough information so that we can duplicate the problem. If you're not sure how to write a good bug report, read [Mozilla's excellent guide](https://developer.mozilla.org/en-US/docs/Mozilla/QA/Bug_writing_guidelines) first.

### Suggest New Features
Do you find yourself trying to do something over and over that Lacuna either doesn't make easy or won't let you do at all? Great! Let us know about it, again by submitting an issue. Please label it as an "enhancement" and we can start to discuss your idea.

### Submit a Pull Request
Want to improve or extend Lacuna yourself? That's great! Please, don't keep the changes to yourself. Fork our repository and send a pull request. If it's something we agree should be in the main distribution, we'd love to merge your request and will gladly give you credit for the work.

# Credits
Many people have put time and effort into this project. For a fuller list of the credits, see the official announcement of Lacuna 2.0. Here are just the people who contributed code to the project, in boring alphabetical order:

* Ben Allen
* Daniel Bush
* Shiraz Dindar
* Zhila Emadi
* Irene Hsu
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
These organizations at Stanford University all contributed in substantial ways to making Lacuna possible:
* [The Center for Interdisciplinary Digital Research (CIDR)](https://cidr.stanford.edu), Stanford University Libraries
* [The Center for Spatial and Textual Analysis (CESTA)](https://cesta.stanford.edu)
* [The Dean of Research](https://doresearch.stanford.edu/research-offices/dor-office-vice-provost-and-dean-research)
* [The Division of Literatures, Cultures, and Languages](https://dlcl.stanford.edu)
* [The Knut and Alice Wallenberg Foundation](https://www.wallenberg.com/kaw/en)
* [The Office of the Vice Provost for Teaching and Learning](https://vptl.stanford.edu/)
* [The Office of the Vice Provost for Undergraduate Education](https://undergrad.stanford.edu/about)

