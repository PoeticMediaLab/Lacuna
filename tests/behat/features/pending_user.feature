@api
  Feature: pending_user
    As a Student user pending approval to join a course
    In order not to expose user information
    I should be denied access to course-related content

    Background:
      Given an "Instructor" user named "Instructor A" exists
      And "course" content:
        | title         | author        |
        | Course Alpha  | Instructor A  |

    Scenario Outline:
      Given I am logged in as a user with the "Student" role
      And I am pending enrollment in the "Course Alpha" course
      When I am on <url>
      # 403 == Access denied
      Then the response status code should be 403

      Examples:
      | url                                   |
      | "/visualization/responses"            |
      | "/visualization/dashboard"            |
      | "/visualization/dashboard/data.json"  |

    Scenario Outline:
      Given I am logged in as a user with the "Student" role
      And I am pending enrollment in the "Course Alpha" course
      When I visit <url>
      # Refactor to have a "Then the view should be empty" step
      Then I should not see a "div.view-content" element

      Examples:
      | url                                   |
      | "/materials"                          |
      | "/responses"                          |
      | "/people"                             |
      | "/threads"                            |
      | "/peer-groups"                        |
      | "/my-writing"                         |


    # Sewing Kit uses VBO, shows empty views differently
    Scenario:
      Given I am logged in as a user with the "Student" role
      And I am pending enrollment in the "Course Alpha" course
      When I visit "/sewing-kit"
      # Refactor to have a "Then the view should be empty" step
      Then I should see a "div.vbo-views-form-empty" element