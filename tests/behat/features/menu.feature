@api
Feature: Main Menu
  In order to navigate the website
  As an authenticated user
  I need to be able to access all the menu items

  Scenario Outline: Main Menu
    Given I am logged in as a user with the "authenticated user" role
    When I am on the homepage
    Then I should see the link <link> in the "Main Menu" region

    Examples:
      | link      |
      | About     |
      | Courses   |
      | "Log Out" |