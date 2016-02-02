@api
Feature: courses_student
  In order to participate in a course
  As a student
  I should be able to read course texts and responses and write responses

  Background:
    Given "course" content:
    | title     |
    | Course A  |
    | Course B  |
    And a "Student" user named "Student A" exists
    And a "Student" user named "Student B" exists
    And an "Instructor" user named "Instructor A" exists
    And an "Instructor" user named "Instructor B" exists

  Scenario Outline:
    Given I am logged in as "Student A"
    And I am enrolled in the "Course A" course
    When I go to "course/course-a"
    Then I should see <link> in the "header" region
    And I should not see <admin_link> in the "header" region

    Examples:
    | link    | admin_link  |
    | Explore | Manage      |
    | Create  | Manage      |
    | Connect | Manage      |
    | Reflect | Manage      |
    | Account | Manage      |
    | Help    | Manage      |