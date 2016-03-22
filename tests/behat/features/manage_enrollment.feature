@api
  Feature: manage_enrollment
    As an instructor
    In order to manage my student's accounts
    I should be able to approve/block them from my courses

    Background:
      Given an "Instructor" user named "Instructor A" exists
      And "course" content:
        | title         | author        |
        | Course Alpha  | Instructor A  |
        | Course Beta   | Instructor A  |
      And "Instructor A" is the instructor of the "Course Alpha" course
      And "Instructor A" is the instructor of the "Course Beta" course
      And a "Student" user named "Student A" exists
      And "Student A" is pending enrollment in the "Course Alpha" course
      And a "Student" user named "Student B" exists
      And "Student B" is enrolled in the "Course Beta" course

    Scenario: Approve and block students
      Given I am logged in as "Instructor A"
      When I am on "/manage-students"
      Then I should see "Status: Pending" in the "View Content"
      And I should see "Student A" in the "View Content"
      And I should see the "Approve" button
      And I should see the "Block" button
      And I should not see "Student B" in the "View Content"

    Scenario: Manage students only in current course
      Given I am logged in as "Instructor A"
      And my currently selected course is "Course Beta"
      When I am on "/manage-students"
      Then I should not see "Status: Pending" in the "View Content"
      And I should see "Status: Active" in the "View Content"
      And I should not see "Student A" in the "View Content"
      And I should see "Student B" in the "View Content"

    Scenario: Manage students help text
      Given I am logged in as "Instructor A"
      When I am on "/manage-students"
      Then I should see "When students sign up for your course"