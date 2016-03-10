@api
  Feature: switch_course
    As a Content Manager or Instructor
    In order to add materials to the correct course
    I should be able to switch between courses I am authorized to update

    Background:
      Given an "Instructor" user named "Instructor A" exists
      And an "Instructor" user named "Instructor B" exists
      # Note: the users need to exist first so authors can be assigned
      And "course" content:
        | title         | author        |
        | Course Alpha  | Instructor A  |
        | Course Beta   | Instructor B  |
      And "Instructor A" is the instructor of the "Course Alpha" course
      And "Instructor B" is the instructor of the "Course Beta" course

    Scenario Outline:
      Given I am logged in as "Instructor A"
      When I go to the "course" node named "Course Alpha"
      Then I should see <link> in the "Main Menu" region

      Examples:
        | link    |
        | Explore |
        | Create  |
        | Connect |
        | Reflect |
        | Account |
        | Help    |

    Scenario Outline:
      Given I am logged in as "Instructor A"
      When I go to the "course" node named "Course Beta"
      Then I should not see <link> in the "Main Menu" region

      Examples:
        | link    |
        | Explore |
        | Create  |
        | Connect |
        | Reflect |
        | Account |
        | Help    |

    Scenario Outline:
      Given I am logged in as a user with the "Content Manager" role
      When I go to the "course" node named "Course Alpha"
      Then I should see <link> in the "Main Menu" region

      Examples:
        | link    |
        | Explore |
        | Create  |
        | Connect |
        | Reflect |
        | Account |
        | Help    |

#    Scenario:
#      Given I am logged in as "Instructor A"