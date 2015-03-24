Feature: Demo Behat Test
  Demo a simple test case using Behat

  Scenario: Open home page and find text
    Given I am on the homepage
    And I am not logged in
    Then I should see the heading "Welcome to Site-Install"
