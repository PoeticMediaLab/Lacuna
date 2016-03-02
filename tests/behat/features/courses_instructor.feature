@api
  Feature: Courses as Instructor
    Background:
      Given "course" content:
        | title         |
        | Course Alpha  |
        | Course Beta   |
      And an "Instructor" user named "Instructor A" exists
      And "Instructor A" is an instructor in the "Course Alpha" course
      And an "Instructor" user named "Instructor B" exists
      And "Instructor B" is an instructor in the "Course Beta" course