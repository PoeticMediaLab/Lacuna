@api
  Feature: response_tags
    As a student user
    In order to organize my content
    I should be able to create and use my course's tags

    Background:
      Given "course" content:
        | title         |
        | Course Alpha  |
        | Course Beta   |
      And tag <tag> for course <course>:
        | tag         | course        |
        | Thing One   | Course Alpha  |
        | Thing Two   | Course Beta   |

    Scenario: Creating a response
      Given I am logged in as a user with the "Student" role
      And I am enrolled in the "Course Alpha" course
      When I visit "/node/add/response"
      Then I should be able to select "Thing One" in the "#edit-field-tags-und" field
      And I should not be able to select "Thing Two" in the "#edit-field-tags-und" field
