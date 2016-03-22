@api
  Feature: threads
    As an authenticated user
    In order to organize annotations
    I should be able to create threads

    Background:
      Given an "Instructor" user named "Instructor A" exists
      And an "Instructor" user named "Instructor B" exists
      And "course" content:
        | title         | author        |
        | Course Alpha  | Instructor A  |
        | Course Beta   | Instructor B  |
      And a "Student" user named "Student A" exists
      And "Student A" is enrolled in the "Course Alpha" course
      And a "Student" user named "Student B" exists
      And "Student B" is enrolled in the "Course Beta" course
      And "thread" content:
        | title       | author    | thread_description|
        | Thread A    | Student A | Student B smells  |
        | Thread B    | Student B | Student A stinks  |
      And thread "Thread A" is content for course "Course Alpha"
      And thread "Thread B" is content for course "Course Beta"

    Scenario: Thread visibility
      Given I am logged in as "Student A"
      And my currently selected course is "Course Alpha"
      When I visit "/threads"
      Then I should see "Threads" in the "Page Title"
      And I should see "Course Alpha" in the "Course Selected"
      And I should not see "No threads have been created"
      And I should see "Thread A" in the "View Content"

    Scenario: Thread access denied
      Given I am logged in as "Student B"
      When I go to the "thread" node titled "Thread A"
      Then I should see "Access denied" in the "Page Title"
