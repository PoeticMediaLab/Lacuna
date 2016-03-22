<?php

use Drupal\DrupalExtension\Context\DrupalContext;
use Behat\Behat\Context\SnippetAcceptingContext;
use Behat\Gherkin\Node\TableNode;

/**
 * Defines application features from the specific context.
 */
class FeatureContext extends DrupalContext implements SnippetAcceptingContext {

  /**
   * Initializes context.
   *
   * Every scenario gets its own context instance.
   * You can also pass arbitrary arguments to the
   * context constructor through behat.yml.
   */
  public function __construct() {
  }

  /**
   * @When I edit my profile
   */
  public function iEditMyProfile() {
    if (!$this->user->uid) {
      throw new \Exception('Cannot edit user profile when not logged in.');
    }
    $this->getSession()->visit('/user/' . $this->user->uid . '/edit');
  }

  /**
   * @Given a/an :role user named :username exists
   */
  public function userOfRoleExists($role_name, $username) {
    $role = user_role_load_by_name($role_name);
    $user = (object) array(
      'name' => $username,
      'pass' => user_password(),
      'email' =>  preg_replace('/\s+/', '_', $username) . '@lacunastories.com',
      'roles' => array(
        $role->rid => $role->name
      ),
    );
    $this->userCreate($user);
  }

  /**
   * @param $node_type
   * @param $node_title
   *
   * @throws \Exception
   * Find a node by its title. If duplicate node titles, will return the first.
   * @return bool|mixed
   */
  public function findNodeByTitle($node_type, $node_title) {
    $found_node = FALSE;
    // First check our test-generated nodes
    foreach ($this->nodes as $node) {
      if ($node->type == $node_type and $node->title == $node_title) {
        $found_node = $node;
        break;
      }
    }
    // Not found there. Query for existing nodes.
    if (!$found_node) {
      $query = new EntityFieldQuery();
      $result = $query->entityCondition('entity_type', 'node')
        ->propertyCondition('type', $node_type)
        ->propertyCondition('title', $node_title)
        ->propertyCondition('status', 1)
        ->range(0,1)
        ->execute();

      if (!empty($result['node'])) {
        $found_node = array_pop($result['node']);
      } else {
        throw new \Exception(sprintf('Could not find node %s of type %s!', $node_title, $node_type));
      }
    }
    return $found_node;
  }

  /**
   * @When I go to the :type node named/titled :node_title
   */
  public function iGoToNodeTypeNamed($node_type, $node_title) {
    $node = $this->findNodeByTitle($node_type, $node_title);
    if (!$node) {
      throw new \Exception(sprintf('No %s node with title %s exists!', $node_type, $node_title));
    }
    $this->getSession()->visit('/node/' . $node->nid);
  }

  /**
   * @param $user
   * @param $course_title
   * @return bool
   * @throws \Exception
   * @throws \OgException
   */
  private function enrollUserInCourse($user, $course_title, $state = OG_STATE_ACTIVE) {
    $group = $this->findNodeByTitle('course', $course_title);
    $membership = og_group('node', $group->nid, array(
      "entity type" => "user",
      "entity" => $user,
      "field_name" => "og_user_node",
      "state" => $state
    ));
    if (!$membership) {
      throw new \Exception(sprintf("User %s could not be enrolled in course %s", $user->name, $group->title));
    }
    return TRUE;
  }

  /**
   * @param $user
   * @param $course_title
   * @throws \Exception
   */
  private function makeInstructorOfCourse($user, $course_title) {
    // For now, instructors are all admins of the group
    $group_role = 'administrator member';
    $group = $this->findNodeByTitle('course', $course_title);
    $roles = og_roles('node', $group->type, $group->nid);
    $rid = array_search($group_role, $roles);

    if (!$rid) {
      throw new \Exception(sprintf("'%s' is not a valid group role.", $group_role));
    }

    og_role_grant('node', $group->nid, $user->uid, $rid);
  }

  /**
   * @Given :username is enrolled in the :course_title course
   */
  public function isEnrolledInCourse($username, $course_title) {
    $user = user_load_by_name($username);
    $this->enrollUserInCourse($user, $course_title);
  }

  /**
   * @Given I am enrolled in the :course_title course
   */
  public function iAmEnrolledInCourse($course_title) {
    $this->enrollUserInCourse($this->user, $course_title);
  }

  /**
   * @param $username
   * @param $course_title
   * @throws \Exception
   * @Given :username is an/the instructor in/of the :course_title course
   */
  public function isInstructorOfCourse($username, $course_title) {
    $user = user_load_by_name($username);
    $this->enrollUserInCourse($user, $course_title);
    $this->makeInstructorOfCourse($user, $course_title);
  }


  /**
   * Associates a given node with a course
   * Necessary because we add that context on form submit
   * which doesn't happen when the API creates nodes
   * @Given :type :title is content for course :course_title
   */
  public function nodeIsContentOfCourse($node_type, $node_title, $course_title) {
    $node = $this->findNodeByTitle($node_type, $node_title);
    $course = $this->findNodeByTitle('course', $course_title);
    $membership = og_group('node', $course->nid,
      array(
        'entity_type' => 'node',
        'entity' => $node,
        'field_name' => 'og_group_ref',
        'state' => OG_STATE_ACTIVE
      )
    );
    if (!$membership) {
      throw new \Exception(sprintf("Could not add %s '%s' to course '%s'"), $node_type, $node_title, $course_title);
    }
  }

  /**
   * @Given I am pending enrollment in the :course_title course
   */
  public function IAmPendingEnrollment($course_title) {
    $this->enrollUserInCourse($this->user, $course_title, OG_STATE_PENDING);
  }

  /**
   * @Given :user is pending enrollment in the :course_title course
   */
  public function userIsPendingEnrollment($username, $course_title) {
    $user = user_load_by_name($username);
    $this->enrollUserInCourse($user, $course_title, OG_STATE_PENDING);
  }

  /**
   * @Given My currently selected course is :course_title
   */
  public function myCurrentCourseIs($course_title) {
    $course = $this->findNodeByTitle('course', $course_title);
    if (! course_set_selected_course($course->nid, $this->user->uid, FALSE)) {
      throw new Exception('Could not set current course');
    }
  }

  /**
   * @Then I should be denied access
   */
  public function IAmDeniedAccess() {
    // Note: if the access denied page changes, change this
//    new Call\Then
//    \Drupal\DrupalExtension\Context\MinkContext::assertRegionText('Access denied', 'Page Title');
//    throw new Exception('I was not denied access');
  }

  /**
   *
   * Creates an annotation by current user with values set:
   * | audience     | category      | tags       | text             |
   * | private, peer-groups, instructor, everyone|
   * @Given annotations on :document:
   */
  public function createAnnotations($document_title, TableNode $annotationsTable) {
    global $user;
    // Need to load the user from the Author field in this case
    $user = $this->user;  // Needed for module's routines
    $document = $this->findNodeByTitle('document', $document_title);
    // Access the Annotation Store functions
    include_once(DRUPAL_ROOT . '/sites/all/modules/custom/annotation/annotation.store.inc');
    foreach ($annotationsTable->getHash() as $data) {
      $annotation = (object) $data;
      if (isset($annotation->audience)) {
        // Special case for audience
        // default; must have all values set
        $audiences = array(
          'private' => 0 ,
          'instructor' => 0,
          'peer-groups' => 0,
          'everyone' => 0
        );
        $annotation->privacy_options['audience'] = $audiences;
        foreach (explode(',', $annotation->audience) as $audience) {
          $annotation->privacy_options['audience'][strtolower($audience)] = 1;
        }
        unset($annotation->audience);
      }
      // Annotator.js formats the URI this way
      global $base_root;
      $uri = entity_uri('node', $document);
      $annotation->uri = $base_root . base_path() . $uri['path'];
      $annotation = annotation_drupal_format($annotation);
      $annotation->uid = $this->user->uid;
      $annotation = node_submit($annotation);
      node_save($annotation);
    }
  }

  /**
   * @param \Behat\Gherkin\Node\TableNode $tagsTable
   * @throws \Exception
   * @Given tag <tag> for course <course>:
   */
  public function createTags(TableNode $tagsTable) {
    foreach ($tagsTable->getHash() as $data) {
      if (!isset($data['tag']) or !isset($data['course'])) {
        throw new Exception('Missing information to create tags. Need tag and course.');
      }
      $vocab = taxonomy_vocabulary_machine_name_load('annotation_tags');
      $course = $this->findNodeByTitle('course', $data['course']);
      $term = new stdClass();
      $term->name = $data['tag'];
      $term->vid = $vocab->vid;
      $term->field_term_course[LANGUAGE_NONE][0]['target_id'] = $course->nid;

      if (!taxonomy_term_save($term)) {
        throw new Exception(sprintf('Could not create term %s'), $data['tag']);
      }
    }
  }

  /**
   * @param $option
   * @param $field
   * @throws \Exception
   *
   * @Then I should be able to select :option in the :field field
   */
  public function iShouldBeAbleToSelect($option, $field) {
    $select = $this->getSession()->getPage()->find('css', $field);
    if (!$select->find('named', array('option', $option))) {
      throw new \Exception(sprintf("Could not select '%s' in '%s'", $option, $field));
    }
  }

  /**
   * @param $option
   * @param $field
   * @throws \Exception
   *
   * @Then I should not be able to select :option in the :field field
   */
  public function iShouldNotBeAbleToSelect($option, $field) {
    $select = $this->getSession()->getPage()->find('css', $field);
    if ($select->find('named', array('option', $option))) {
      throw new \Exception(sprintf("Was able to select '%s' in '%s'", $option, $field));
    }
  }

  /**
   * @AfterScenario
   *
   * Clean up the tags we added
   */
  public function cleanUpTags() {
//    $vocab = taxonomy_vocabulary_machine_name_load('annotation_tags');
//    $tree = taxonomy_get_tree($vocab->vid);
  }
}

