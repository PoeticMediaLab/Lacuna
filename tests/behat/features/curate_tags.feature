@api
  Feature: curate_tags
    As an instructor
    In order to manage the tags students use in their annotations
    I should be able to add and curate tags for my course

    Background:
      Given an "Instructor" user named "Instructor A" exists
      And "course" content:
        | title         | author        |
        | Course Alpha  | Instructor A  |
      And "Instructor A" is the instructor of the "Course Alpha" course

    Scenario: Add Tag from an empty Curate Tags
      Given I am logged in as "Instructor A"
      And My currently selected course is "Course Alpha"
      When I visit "/curate-tags"
      Then I should see "Add a New Tag"

    Scenario: Submit a new annotation tag
      Given I am logged in as "Instructor A"
      And My currently selected course is "Course Alpha"
      When I visit "/annotation_tags/add"
      And I fill in "Tag name" with "testing"
      And I press the "Submit" button
      Then I should see the following success messages:
      | "testing" has been added to the list of tags |