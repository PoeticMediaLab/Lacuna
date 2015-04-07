<?php

use Drupal\DrupalExtension\Context\RawDrupalContext;
use Behat\Behat\Context\SnippetAcceptingContext;
use Behat\Gherkin\Node\PyStringNode;
use Behat\Gherkin\Node\TableNode;

/**
 * Defines application features from the specific context.
 */
class FeatureContext extends RawDrupalContext implements SnippetAcceptingContext {

  protected $screenshot_dir = '/tmp';

  /**
   * Initializes context.
   *
   * Every scenario gets its own context instance.
   * You can also pass arbitrary arguments to the
   * context constructor through behat.yml.
   */
  public function __construct($parameters) {
    $this->parameters = $parameters;
    if (isset($parameters['screenshot_dir'])) {
      $this->screenshot_dir = $parameters['screenshot_dir'];
    }
  }

  /**
   * Take screenshot when step fails. Works only with Selenium2Driver.
   * Screenshot is saved at [Date]/[Feature]/[Scenario]/[Step].jpg
   *  @AfterStep
   */
  public function after(Behat\Behat\Hook\Scope\AfterStepScope $scope) {
    if ($scope->getTestResult()->getResultCode() === 99) {
      $driver = $this->getSession()->getDriver();
      if ($driver instanceof Behat\Mink\Driver\Selenium2Driver) {
        $fileName = date('d-m-y') . '-' . uniqid() . '.png';
        $this->saveScreenshot($fileName, $this->screenshot_dir);
        print 'Screenshot at: '.$this->screenshot_dir.'/' . $fileName;
      }
    }
  }

}
