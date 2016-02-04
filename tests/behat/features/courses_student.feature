@api
Feature: Courses as Student
  In order to participate in a course
  As a student
  I should be able to read course texts and responses and write responses

  Background:
    Given "course" content:
    | title         |
    | Course Alpha  |
    | Course Beta   |
    And a "Student" user named "Student A" exists
#    And a "Student" user named "Student B" exists
#    And an "Instructor" user named "Instructor A" exists
#    And an "Instructor" user named "Instructor B" exists

  Scenario Outline:
    Given I am logged in as "Student A"
    And I am enrolled in the "Course Alpha" course
    When I go to the "course" node named "Course Alpha"
    Then I should see "Course Alpha" in the "Page Title" region
    And I should see "Course Alpha" in the "Course Selected" region
    And I should see <link> in the "Main Menu" region

    Examples:
    | link    |
    | Explore |
    | Create  |
    | Connect |
    | Reflect |
    | Account |
    | Help    |

   Scenario Outline:
     Given I am logged in as "Student A"
     When I go to the "course" node named "Course Beta"
     Then I should see "Course Beta" in the "Page Title"
     And I should not see <link> in the "Main Menu" region

     Examples:
       | link    |
       | Explore |
       | Create  |
       | Connect |
       | Reflect |
       | Account |
       | Help    |
