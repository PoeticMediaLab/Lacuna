@api
  Feature: annotator
    As an enrolled student user
    In order to annotate texts
    I should be able to create annotations with different sharing options

    Background:
      Given an "Instructor" user named "Instructor A" exists
      # Note: the users need to exist first so authors can be assigned
      And "course" content:
        | title         | author        |
        | Course Alpha  | Instructor A  |
      And "document" content:
        | title       | author       | body                                |
        | Document A  | Instructor A | This is your reading for the week.  |
      # Note: the assignment of content to a course has to come after it's been created
      And document "Document A" is content for course "Course Alpha"
      And a "Student" user named "Student A" exists
      And annotations on "Document A":
        | audience     | text                          | author     |
        | Private      | This is a private annotation  | Student A  |
        | Instructor   | This is for teacher           | Student A  |
        | Everyone     | This is for everyone          | Student A  |

    Scenario:
      Given I am logged in as a user with the "Student" role
      And I am enrolled in the "Course Alpha" course
      And my currently selected course is "Course Alpha"
      And I am on "/sewing-kit"
      Then I should see "This is a private annotation" in the "View Content" region
      And I should see "This is for teacher" in the "View Content" region
      And I should see "This is for everyone" in the "View Content" region

