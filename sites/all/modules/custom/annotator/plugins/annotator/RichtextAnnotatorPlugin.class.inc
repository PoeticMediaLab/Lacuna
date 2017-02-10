<?php

/*
Adds CKEditor to the Annotator window
*/

class RichtextAnnotatorPlugin extends AnnotatorPlugin {
  public function settings($defaults = array()) {
    // settings are in the richtext plugin
    return parent::settings($defaults);
  }

  /*  Allows an admistrator to include an iframe.ly API key for
  *   automatic content embedding over SSL.  */
  public function settingsForm() {
    $defaults = $this->settings();
    if (!isset($defaults['iframely_api_key'])) {
      $defaults['iframely_api_key'] = '';
    }
    $form['iframely_api_key'] = array(
      '#type' => 'textfield',
      '#title' => t('Iframely API key'),
      '#default_value' => $defaults['iframely_api_key'],
      '#description' => t("To automatically embed content when the URL is pasted into the rich text editor, Annotator uses the Iframely service.  If your installation of Lacuna uses the https:// protocol, you'll need to sign up for your own Iframely API key at <a href=\"https://iframely.com/signup\">https://iframely.com/signup</a>, then enter the key here to enable this functionality." )
    );
    return $form;
  }

  public function setup() {
    // adds Iframely API key to Drupal.settings.annotator_richtext
    $settings = parent::settings();
    drupal_add_js(array('annotator_richtext' => (array) $settings), 'setting');
		// When javascript is aggregated, CKEditor needs to know where its libraries are
		drupal_add_js('window.CKEDITOR_BASEPATH="' . base_path() . libraries_get_path('ckeditor_annotator') . '/";', 'inline', array('weight' => -100));
		drupal_add_js(libraries_get_path('ckeditor_annotator') . '/ckeditor.js', array('weight' => 8));
		drupal_add_js(drupal_get_path('module', 'annotator') . '/js/annotator_richtext.js', array('weight' => 9));
    drupal_add_js(drupal_get_path('module', 'annotator') . '/js/richtext.js', array('weight' => 10));
	}
}
