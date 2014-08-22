<?php
/**
 * @file
 * lacuna_stories.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function lacuna_stories_default_rules_configuration() {
  $items = array();
  $items['rules_redirect_document_content_to_bibliographic_entries'] = entity_import('rules_config', '{ "rules_redirect_document_content_to_bibliographic_entries" : {
      "LABEL" : "Redirect Document content to Bibliographic Entries",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules" ],
      "ON" : { "node_view--document" : { "bundle" : "document" } },
      "DO" : [ { "redirect" : { "url" : [ "node:field-bibliographic-entry:url" ] } } ]
    }
  }');
  return $items;
}
