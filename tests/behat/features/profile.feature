@api
Feature: user_profile
  In order to manage my user profile
  As an authenticated user
  I need to be able to edit my profile

  Scenario Outline: Users should be able to fill out all the fields in their profiles
#    Given I am on "/user/login"
#    And I fill in "Username" with "Student A"
#    And I fill in "Password" with "studenta"
#    And I click "Log in"
#    Given users:
#    | name      | status  |
#    | Student A | 1       |
    When I am logged in as a user with the "authenticated user" role
    And I edit my profile
    Then I should see <field>

    Examples:
    | field           |
    | "Display Name"  |

