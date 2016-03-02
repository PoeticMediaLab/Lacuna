@api
  Feature: admin_menu
    In order to administer the site
    As a Site Administrator
    I should be able to access the administrative menu

    Scenario Outline:
      Given I am logged in as a user with the "Site Administrator" role
      When I am on the homepage
      Then I should see <link> in the "Admin Menu"

      Examples:
      | link          |
      | Dashboard     |
      | Content       |
      | Structure     |
      | Appearance    |
      | People        |
      | Modules       |
      | Configuration |
      | "Advanced Help" |
      | Reports       |
      | Help          |
