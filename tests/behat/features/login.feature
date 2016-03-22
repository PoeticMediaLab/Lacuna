Feature: login
  In order to access the website
  As an anonymous user
  I need to be able to use the login form

  Scenario: An anonymous user should see the Log In link
    Given I am not logged in
    When I am on the homepage
    Then I should see the link "Log In" in the "header" region

  Scenario: An anonymous user should be able to access the login form
    Given I am not logged in
    When I am on the homepage
    And I click "Log In" in the "header"
    Then I should see "You are not logged in." in the "Content" region

  @api
  Scenario: A logged in user should not see "Log In"
    Given I am logged in as a user with the "Student" role
    When I am on the homepage
    Then I should not see the link "Log In" in the "header"