<?php
/**
 * @file
 * lacuna_stories_irb_form.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function lacuna_stories_irb_form_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: main-menu_digital-research-consent-form:node/1
  $menu_links['main-menu_digital-research-consent-form:node/1'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'node/1',
    'router_path' => 'node/%',
    'link_title' => 'Digital Research Consent Form',
    'options' => array(
      'identifier' => 'main-menu_digital-research-consent-form:node/1',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -47,
    'customized' => 1,
    'parent_identifier' => 'main-menu_account:<nolink>',
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Digital Research Consent Form');

  return $menu_links;
}
