<?php

function lacuna_lti_canvas_admin() {
  lacuna_lti_canvas_xml('admin');
}

function lacuna_lti_canvas_student() {
  lacuna_lti_canvas_xml('student');
}

/***
 * Generate XML to configure Lacuna as an app for Canvas
 */
function lacuna_lti_canvas_xml($menu_choice) {
  global $base_url;
  /* create a dom document with encoding utf8 */
  $domtree = new DOMDocument('1.0', 'UTF-8');
  /* create the root element of the xml tree */
  $xmlRoot = $domtree->createElement("cartridge_basiclti_link");
  /* append it to the document created */
  $xmlRoot = $domtree->appendChild($xmlRoot);
  $xmlRoot = lacuna_lti_canvas_xml_namespaces($domtree, $xmlRoot);
  $element = $domtree->createElement('blti:title', 'Lacuna');
  $xmlRoot->appendChild($element);
  $f = $domtree->createDocumentFragment();
  $f->appendXML('<!--[CDATA[Lacuna is an open-source, online learning tool focused on tools for digital annotation. Lacuna allows instructors, students, and co-learners to discover different ways of reading, interpreting, and discussing course materials.]]-->');
  $element = $domtree->createElement('blti:description');
  $element->appendChild($f);
  $xmlRoot->appendChild($element);
  $element = $domtree->createElement('blti:launch_url', $base_url . '/lti');
  $xmlRoot->appendChild($element);
  $iconUrl = $base_url . '/' . drupal_get_path('theme', 'lacuna_stories') . '/favicon.ico';
  $element = $domtree->createElement('blti:icon', $iconUrl);
  $xmlRoot->appendChild($element);
  $extensions = $domtree->createElement('blti:extensions');
  $attr = $domtree->createAttribute('platform');
  $attr->value = "canvas.instructure.com";
  $xmlRoot->appendChild($extensions);
  $extensions->appendChild($attr);
  if ($menu_choice == 'admin') {
    $extension_settings = lacuna_lti_canvas_xml_admin_values($iconUrl);
  } elseif ($menu_choice == 'student') {
    $extension_settings = lacuna_lti_canvas_xml_student_values($iconUrl);
  }
  foreach ($extension_settings as $key => $value) {
    if (!is_array($value)) {
      lacuna_lti_canvas_xml_add_property($domtree, $extensions, $key, $value);
    } else {
      foreach ($value as $values) {
        $options = $domtree->createElement('lticm:options');
        $attr = $domtree->createAttribute('name');
        $attr->value = $values['name'];
        unset($values['name']);
        $options->appendChild($attr);
        $extensions->appendChild($options);
        lacuna_lti_canvas_xml_add_property($domtree, $options, $attr->value, $values);
      }
    }
  }
  $domtree->preserveWhiteSpace = true;
  $domtree->formatOutput = true;
  $xmlstring = $domtree->saveXML();
  drupal_add_http_header('Content-Type' ,'text/xml; utf-8');
  print($xmlstring);
  drupal_exit();
}

/***
 * @param $domtree
 * @param $element
 * @param $name
 * @param $value
 *
 * Add a property with name and value to the given element.
 */
function lacuna_lti_canvas_xml_add_property($domtree, $element, $name, $value) {
  if (is_array($value)) {
    $attr = $domtree->createAttribute('name');
    $attr->value = $name;
    $element->appendChild($attr);
    foreach ($value as $key => $val) {
      lacuna_lti_canvas_xml_add_property($domtree, $element, $key, $val);
    }
  } else {
    $property = $domtree->createElement('lticm:property', $value);
    $attr = $domtree->createAttribute('name');
    $attr->value = $name;
    $element->appendChild($property);
    $property->appendChild($attr);
  }
}

/***
 * @param $xmlRoot
 * @return mixed
 *
 * Set all the namespace attributes that Canvas wants
 */
function lacuna_lti_canvas_xml_namespaces($domtree, $xmlRoot) {
  $attributes = array(
    'xmlns' => "http://www.imsglobal.org/xsd/imslticc_v1p0",
    'xmlns:blti'=> "http://www.imsglobal.org/xsd/imsbasiclti_v1p0",
    'xmlns:lticm' => "http://www.imsglobal.org/xsd/imslticm_v1p0",
    'xmlns:lticp' => "http://www.imsglobal.org/xsd/imslticp_v1p0",
    'xmlns:xsi' => "http://www.w3.org/2001/XMLSchema-instance",
    'xsi:schemalocation' => "http://www.imsglobal.org/xsd/imslticc_v1p0 http://www.imsglobal.org/xsd/lti/ltiv1p0/imslticc_v1p0.xsd http://www.imsglobal.org/xsd/imsbasiclti_v1p0 http://www.imsglobal.org/xsd/lti/ltiv1p0/imsbasiclti_v1p0p1.xsd http://www.imsglobal.org/xsd/imslticm_v1p0 http://www.imsglobal.org/xsd/lti/ltiv1p0/imslticm_v1p0.xsd http://www.imsglobal.org/xsd/imslticp_v1p0 http://www.imsglobal.org/xsd/lti/ltiv1p0/imslticp_v1p0.xsd"
  );
  foreach ($attributes as $key => $value) {
    $attr = $domtree->createAttribute($key);
    $attr->value = $value;
    $xmlRoot->appendChild($attr);
  }
  return $xmlRoot;
}

/***
 * @return array
 * Provides the property names, values, and options for Canvas configuration
 */
function lacuna_lti_canvas_xml_admin_values($iconUrl) {
  global $base_url;
  return array(
    'tool_id' => 'lacuna',
    'icon_url' => $iconUrl,
    'privacy_level' => 'admins',
    'options' => array(
      array(
        'name' => 'resource_selection',
        'enabled' => 'true',
        'url' => $base_url . '/lti?destination=/lti_resource_list',
        'text' => 'Add resources from Lacuna',
        'selection_width' => 800,
        'selection_height' => 600,
      ),
      array(
        'name' => 'course_navigation',
        'text' => 'Manage Lacuna',
        'enabled' => 'true',
        'url' => $base_url . '/lti?destination=/lti/course/setup',
        'visibility' => 'admins',
      ),
    ),
  );
}

/***
 * @param $iconUrl
 * @return array
 * Return XML settings for the optional student menu
 */
function lacuna_lti_canvas_xml_student_values($iconUrl) {
  global $base_url;
  return array(
    'tool_id' => 'lacuna_student',
    'icon_url' => $iconUrl,
    'privacy_level' => 'members',
    'options' => array(
      array(
        'name' => 'course_navigation',
        'text' => 'Lacuna',
        'enabled' => 'true',
        'url' => $base_url . '/lti?destination=/lti/landing',
        'visibility' => 'members',
      )
    ));
}