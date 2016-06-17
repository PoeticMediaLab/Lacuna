@javascript
Feature: drush site-install validation
  In order to prove Drupal 7 was installed properly
  As a developer
  I need to user the step definitions of this context

  Scenario: Open home page and find text
    Given I am on the homepage
    And I am not logged in
    Then I should see the heading "Welcome to My Drupal 7 Site"

  Scenario: Error messages
    Given I am on "/user"
    When I press "Log in"
    Then I should see the error message "Password field is required"
    And I should not see the error message "Sorry, unrecognized username or password"
    And I should see the following error messages:
    | error messages             |
    | Username field is required |
    | Password field is required |
    And I should not see the following error messages:
    | error messages                                                                |
    | Sorry, unrecognized username or password                                      |
    | Unable to send e-mail. Contact the site administrator if the problem persists |

  Scenario: Messages
    Given I am on "/user/register"
    When I press "Create new account"
    Then I should see the message "Username field is required"
    But I should not see the message "Registration successful. You are now logged in"
