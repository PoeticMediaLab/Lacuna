@api
Feature: consent_form
  In order to control the use of my data
  As a Student user
  I need to be able to access and fill out the Digital Research Consent Form

  # NOTE: We cannot actually test that the form shows up for new users
  # Because a check on / for the "Log out" link confirms being logged in
  Scenario: Students should be able to access the Digital Research Consent Form
    Given I am logged in as a user with the "Student" role
    When I go to "/webform/digital-research-consent-form"
    Then I should see "Digital Research Consent Form" in the "Page Title"

  Scenario: Students should be able to fill out the form
    Given I am logged in as a user with the "Student" role
    When I go to "/webform/digital-research-consent-form"
    And I select "yes" from "edit-submitted-agree-1"
    And I select "yes" from "edit-submitted-over-18-1"
    And I press the "Submit" button
    Then I should see the success message "Welcome to Lacuna Stories"
