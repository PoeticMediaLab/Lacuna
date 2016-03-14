@api
  Feature: course_cm
    As a Content Manager
    In order to manage course content
    I should be able to access courses whether they are published or private

  Scenario: Private course
    Given I am logged in as a user with the "Content Manager" role
    And course content:
    | title           | group_access  |
    | Course Private  | Private: visible only to group members          |
    When I go to the "course" node named "Course Private"
    Then I should see "Course Private" in the "Page Title" region