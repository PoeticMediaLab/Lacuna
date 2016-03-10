@api
  Feature: manage_enrollment
    As an instructor
    In order to manage my student's accounts
    I should be able to approve/block them from my courses

    Scenario:
      Given an "Instructor" user named "Instructor A" exists
      And I am logged in as "Instructor A"
      And "course" content:
        | title         | author        |
        | Course Alpha  | Instructor A  |
      And my currently selected course is "Course Alpha"
      And a "Student" user named "Student A" exists
      And "Student A" is pending enrollment in the "Course Alpha" course
      When I am on "/manage-students"
      Then I should see "Status: Pending" in the "View Content"
      And I should see "Student A" in the "View Content"
      And I should see the "Approve" button
      And I should see the "Block" button
