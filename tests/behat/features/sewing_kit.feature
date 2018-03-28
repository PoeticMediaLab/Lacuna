@api
  Feature: sewing_kit
    As a student or instructor
    In order to organize annotations
    I should be able to use the Sewing Kit to create threads

    Background:
      Given an "Instructor" user named "Instructor A" exists
      And "course" content:
        | title         | author        |
        | Course Alpha  | Instructor A  |
      And "Instructor A" is the instructor of the "Course Alpha" course
      And "document" content:
        | title       | author       | body                                |
        | Document A  | Instructor A | This is your reading for the week.  |
      And document "Document A" is content for course "Course Alpha"
      And a "Student" user named "Student A" exists
      And "Student A" is enrolled in the "Course Alpha" course
      And annotations on document "Document A":
        | audience     | text                          | author     |
        | Private      | This is a private annotation  | Student A  |
        | Instructor   | This is for teacher           | Student A  |
        | Everyone     | This is for everyone          | Student A  |

    Scenario: Create a thread
      Given I am logged in as "Student A"
      And my currently selected course is "Course Alpha"
      And I am on "/sewing-kit"
      # The first annotation's checkbox
      When I check the box "edit-views-bulk-operations-0"
      # The second annotation's checkbox
      And I check the box "edit-views-bulk-operations-1"
      # The third annotation's checkbox
      And I check the box "edit-views-bulk-operations-2"
      And I press the "Add to Thread" button
      # -1 is the value for "---- Create New Thread ----"
      And I select "-1" from "edit-thread-add"
      And I press the "Next" button
      # "My New Thread" is the default title of a new thread
      Then I should see the success message "Your thread My New Thread has been saved"