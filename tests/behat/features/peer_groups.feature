@api
  Feature: peer_groups
    As a student user
    In order to collaborate in small groups
    I should be able to create and join peer groups

  Background:
    Given an "Instructor" user named "Instructor A" exists
    And an "Instructor" user named "Instructor B" exists
    # Note: the users need to exist first so authors can be assigned
    And "course" content:
      | title         | author        |
      | Course Alpha  | Instructor A  |
      | Course Beta   | Instructor B  |
    And a "Student" user named "Student A" exists
    And "Student A" is enrolled in the "Course Alpha" course
    And a "Student" user named "Student B" exists
    And "Student B" is enrolled in the "Course Beta" course
    And a "Student" user named "Student X" exists
    And "Student X" is enrolled in the "Course Alpha" course
    And "Student X" is enrolled in the "Course Beta" course
    And "peer_group" content:
      | title           | author    | group_access                            |
      | Group A Private | Student A | Private: visible only to group members  |
      | Group A Public  | Student A | Public: visible to all course users     |
      | Group B Public  | Student B | Public: visible to all course users     |
    # Note: the assignment of content to a course has to come after it's been created
    And peer_group "Group A Public" is content for course "Course Alpha"
    And peer_group "Group A Private" is content for course "Course Alpha"
    And peer_group "Group B Public" is content for course "Course Beta"

    Scenario: Peer group visibility
      Given I am logged in as "Student X"
      And My currently selected course is "Course Alpha"
      When I visit "/peer-groups"
      Then I should see "Group A Public" in the "Content" region
      And I should not see "Group A Private" in the "Content" region
      And I should not see "Group B Public" in the "Content" region

    Scenario: Peer group cross-course visibility
      Given I am logged in as "Student B"
      When I visit "/peer-groups"
      Then I should not see "Group A Public" in the "Content" region
      And I should see "Group B Public" in the "Content" region

    Scenario: Private group visibility
      Given I am logged in as "Student A"
      When I visit "/peer-groups"
      Then I should see "Group A Private" in the "Content" region

    Scenario: Join a group
      Given I am logged in as "Student X"
      And my currently selected course is "Course Alpha"
      When I go to the "peer_group" node named "Group A Public"
      # This is string overrides being overzealous
      And I follow "Enroll in this course" in the "Content" region
      And I press the "Join" button
      Then I should see "Group A Public" in the "Page Title"
      And I should see "Unenroll from this course"