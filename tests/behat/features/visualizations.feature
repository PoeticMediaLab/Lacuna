@api
  Feature: visualizations
    As a student or instructor
    In order to visualize annotations
    I should be able to view the data visualizations

    Background:
      Given an "Instructor" user named "Instructor A" exists
      And "course" content:
        | title         | author        |
        | Course Alpha  | Instructor A  |
      And a "Student" user named "Student A" exists
      And "Student A" is enrolled in the "Course Alpha" course

    Scenario: Annotations Dashboard
      Given I am logged in as "Student A"
      When I visit "visualization/dashboard"
      Then I should see "Annotations Dashboard" in the "Page Title"
      And I should see a "div#annotations_dashboard" element
